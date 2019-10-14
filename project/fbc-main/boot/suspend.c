#include <string.h>
#include <stdlib.h>
#include <serial.h>
#include <common.h>
#include <reboot.h>
#include <remote.h>
#include <clock.h>
#include <customer_key_conf.h>
#include <gpio.h>
#include <inputdata.h>


#define DEVICE_UART_PORT_0       0
#define DEVICE_UART_PORT_1       1
#define DEVICE_UART_PORT_2       2

#define CONFIG_POWER_KEY 		16



static void udelay(int us)
{
    register int n= (us)*105;
    while(n--);
}

void suspend_power_on(void)
{
    *P_PREG_PAD_GPIO0_EN_N &= (~(1<<1));
    *P_PREG_PAD_GPIO0_O |= (1<<1);
}

void suspend_power_off(void)
{
    *P_PREG_PAD_GPIO0_EN_N &= (~(1<<1));
    *P_PREG_PAD_GPIO0_O &= (~(1<<1));
}
void reset_sw_high(void)
{
    *P_PERIPHS_PIN_MUX_0 &=(~(1<<15)); //disable UART_CTS_AO_C
    *P_PERIPHS_PIN_MUX_0 &=(~(1<<22)); //disable JTAG_TDI
    *P_PREG_PAD_GPIO0_EN_N &= (~(1<<15));
    *P_PREG_PAD_GPIO0_O |= (1<<15);
}

void reset_sw_low(void)
{
    *P_PERIPHS_PIN_MUX_0 &=(~(1<<15)); //disable UART_CTS_AO_C
    *P_PERIPHS_PIN_MUX_0 &=(~(1<<22)); //disable JTAG_TDI
    *P_PREG_PAD_GPIO0_EN_N &= (~(1<<15));
    *P_PREG_PAD_GPIO0_O &= (~(1<<15));
}

int main(int argc, char *argv[])
{
    int  i,key_value;
    unsigned int pin_mux_1_value = 0;

    //serial_init(DEVICE_UART_PORT_0);
    //serial_puts("enter suspend main...\n");

    if(calibrate_internal_osc()) {
        //serial_puts("calibrate internal osc failed.\n");
        reboot(0);
    }

    //serial_puts("calibrate internal osc sucess.\n");
    //
    pin_mux_1_value = *P_PERIPHS_PIN_MUX_1;
    *P_PERIPHS_PIN_MUX_1 = 0x0;

    reset_sw_low();
    udelay(20);
    suspend_power_off();

    //switch_clk_to_32k();
    //ctrl_crystal_pad(0);
	switch_clk_to_24m();
    resume_remote(REMOTE_TYPE);
	sar_adc_init();
//  ir_remote_init_32k_mode();
	INPUTDATA inputdata;
	set_redetect_flag();
    do {
        for(i=0; i<4000; i++);

        //printf("key_value: 0x%x, status: 0x%x\n", key_value, Rd(AO_MF_IR_DEC_STATUS));
        key_value = query_key_value();
        if(customer_key_map[10][0] == key_value) {
            //serial_puts("press power key exit suspend and reboot\n");
            break;
        }

		//switch_clk_to_24m()
		if(!detect_adc_key(1, &inputdata))
		{
			//printf("data: 0x%x, type: %d\n", inputdata.input_data, inputdata.input_type);
			if(inputdata.input_type == 0 && adc2key(1, &inputdata) == CONFIG_POWER_KEY)
			{
				//switch_clk_to_32k();
				break;
			}
		}
		//switch_clk_to_32k();
		
    } while(1);
    //ctrl_crystal_pad(1);
    suspend_power_on();
    //udelay(100);
    *P_PERIPHS_PIN_MUX_1 = pin_mux_1_value ;

    for(i=0; i<5000; i++);

    //switch_clk_to_24m();

	udelay(200);

    reset_spi();
    reset_ee();
    reset_ir();

    reboot_sw(0x87654321);

    return 0;
}

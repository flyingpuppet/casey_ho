#include <string.h>
#include <malloc.h>
#include <common.h>
#include <task.h>
#include <timer.h>
#include <input.h>
#include <remote.h>
#include <uart_api.h>
#include <version.h>
#include <log.h>
#include <i2c.h>
#include <XYmemoryMapping.h>
#include <pwm.h>
#include <customer_key_conf.h>
#include <panel.h>
#include <reboot.h>
#include <user_setting.h>

#define __TEST_RUNNING_ON_SPI_CODE__
//#define CLK_TEST

extern void print_build_version_info(void);
extern void init_ui(void);
extern void init_timer(void);
extern void init_log();
extern void sar_adc_init(void);
extern void init_display(void);
extern void init_vpp(void);
extern void start_vpp(void);
extern int i2s_audio_init(void);
extern void init_spi_flash();
extern int console_enable();
extern void dbg_task_init();
extern void uart_communication_task_init();
extern void i2c_master_init(unsigned char i2c_m_module);
extern void init_setting_task(void);
extern void panel_init(void);
extern int hdmirx_get_clock(int index);
extern void vpu_pq_set(void);

#ifdef __TEST_RUNNING_ON_SPI_CODE__

extern int test_running_spi_code(int x);

void __attribute__((section(".running.on.spi"))) test_section_attr()
{
    printf("test_section_attr is running on spi\n");
    return;
}

#endif

static char TAG[]= "main" ;

extern int KeyFunc(unsigned int input_type,unsigned int customer_code,unsigned int key_value,unsigned int repeatstatus);


int main(int argc, char *argv[])
{
    char *p = NULL;
    int cur_id = 0;

    printf("%s\n\n", FBC_BOOT_VERSION);

    printf("fbc main code version:\n");
    print_build_version_info();

    printf("Power on.\n");
    power_on_aml();

    printf("Enter main.\n");
    p = calloc(1024, 1);
    printf("calloc returned %x\n", (unsigned)p);
    if (p) {
        strcpy(p, "Hello World!\n");
        printf(" %x:%s", (unsigned)p, p);
    }

    printf("Init spi flash.\n");
    init_spi_flash();

#ifdef __TEST_RUNNING_ON_SPI_CODE__
    test_section_attr();
    test_running_spi_code(12345);
#endif

    printf("Init timer.\n");
    init_timer();

    printf("Init task.\n");
    InitTask();

    printf("Init uart.\n");
    console_enable();

    printf("Init uart communication task.\n");
    uart_communication_task_init();

    printf("Init log.\n");
    init_log();

    printf("Init user setting. \n");
    init_setting_task();

    printf("Init Panel.\n");
    panel_init();

    printf("Init Display.\n");
    init_display();

	printf("Init OSD.\n");
	init_ui();

	printf("Panel power on.\n");
    //panel_power_on_aml();
    //panel_power(read_project_id(), on);
	
	//printf("Backlight power on.\n");
    //backlight_power_on_aml();	
	panel_resume();

    printf("Init Vpp.\n");
    init_vpp();    

    printf("set bri con sat hue & wb.\n");
    vpu_pq_set();
    //mdelay(400);    

    printf("Init remote.\n");
    remote_init();
    set_remote_mode(REMOTE_TYPE);

    printf("Init saradc.\n");
    sar_adc_init();

    printf("Init i2s audio\n");
    int ret = i2s_audio_init();
    if(ret < 0)
        printf("Init i2s audio failed\n");

    printf("Init debug task.\n");
    dbg_task_init();

    printf("Init PWM.\n");
    pwm_init();

    printf("Start Vpp.\n");
    start_vpp();

    printf("Init key func\n");
    registKeyProcess(KeyFunc);

    /*  int i = 0;
        unsigned *pp = (unsigned *)0x8002f000;
        for(i = 0; i < 64; i++)
        {
            *pp = 0x0;
            pp++;
        }
        for(i = 0; i < 64; i++)
        {
            *pp = 0xffffffff;
            pp++;
        }
        for(i = 0; i < 64; i++)
        {
            *pp = 0xa5a5a5a5;
            pp++;
        }
        for(i = 0; i < 64; i++)
        {
            *pp = 0x5a5a5a5a;
            pp++;
        }
    */
    /*printf("register mask 0  0x%8x\n", Rd(INTR_MASK_0));
    printf("register int sel 0 0x%8x\n", Rd(INTR_FIRQ_SEL_0));
    printf("register timemux 0x%8x\n", Rd(TIMER_MUX));
    //printf("register int clr 0 0x%8x\n", Rd(INTR_STAT_CLR_0));
    printf("register int stat 0 0x%8x\n", Rd(INTR_STAT_0));
    printf("register timera counter 0x%8x\n", Rd(TIMERA));
    printf("register timerb counter 0x%8x\n", Rd(TIMERB));
    printf("register timerc counter 0x%8x\n", Rd(TIMERC));
    printf("register timerd counter 0x%8x\n", Rd(TIMERD));
    printf("register timere counter 0x%8x\n", Rd(TIMERE));*/
    printf("Enter task main loop.\n");
#ifdef CLK_TEST
    printf("**********************clock**********************************\n");
    int vx1_clk = hdmirx_get_clock(33);
    int vid_clk = hdmirx_get_clock(30);
    int test_ok = 0;
    if(((vx1_clk / 1000000) == 292)&&((vid_clk / 1000000) == 585)) {
        test_ok = 1;
    }
    printf("vx1_fifo_clk = %d\n",vx1_clk);
    printf("vid_pll_clk = %d\n",vid_clk);
    //printf("vx1 %d\n",(vx1_clk / (1000000)));
    //printf("vid %d\n",(vid_clk / (1000000)));
    if(1 == test_ok) {
        printf("OK OK OK OK OK OK OK OK OK OK OK OK OK OK OK OK OK OK \n");
    } else {
        printf("Failed Failed Failed Failed Failed Failed Failed Failed \n");
    }
    printf("*************************************************************\n");
#endif

    // register tasks
    //int uart_console_task_id = RegisterTask(uart_console, NULL, 1<<IRQ_UART_A, 1);
    //int audio_in_task_id = RegisterTask(audio_in_process, NULL, 1<<IRQ_I2S_IN, 8);
    //int led_task_id = RegisterTask(led_precess, 1<<IRQ_TIMER, 15);
    MainTask();
    return 0;
}

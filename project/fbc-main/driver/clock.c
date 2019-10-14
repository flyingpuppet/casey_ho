#include <clock.h>
#include <register.h>
#include <reboot.h>
#include <c_arc_pointer_reg.h>

#define M_HZ			(1000*1000)
#define XTAL_24M		(24)

static void udelay(int us)
{
	 register int n= (us)*105;
	 while(n--);
}

void set_sys_pll(int M, int N, int OD, int reset, int enable)
{
#if 0
	VX1_LVDS_PLL_CTL3 0x80030674 == 0xF0000000
	
	SYS_PLL_CTL  0x800305c0 == 0x40020664
	
	SYS_PLL_CTL1 0x800305c4 == 0x1065c488
	
	SYS_PLL_CTL2 0x800305c8 == 0x4175a250
	
	SYS_PLL_CTL2 0x800305cc == 0x0000040a
#endif
	unsigned i, delay;

	Wr_reg_bits(SYS_PLL_CTL,M,0,9); 
	Wr_reg_bits(SYS_PLL_CTL,N,9,5);
	Wr_reg_bits(SYS_PLL_CTL,OD,16,2);
	
reset_pll:
	Wr_reg_bits(SYS_PLL_CTL,enable,30,1);
	for(i=100; i>0; i--);
	
	Wr(SYS_PLL_CTL1, 0x1065c488);
//	Wr(SYS_PLL_CTL2, 0x4175a250);
	Wr(SYS_PLL_CTL2, 0x0175a250);
	Wr(SYS_PLL_CTL3, 0x0000040a);
	
	Wr_reg_bits(VX1_LVDS_PLL_CTL3, 0xf, 28, 4);
	
	Wr_reg_bits(SYS_PLL_CTL,reset,29,1);
	for(i=100; i>0; i--);
	Wr_reg_bits(SYS_PLL_CTL,0,29,1);
	
	//wait lock
	delay = 1500;
	while( ((*P_SYS_PLL_CTL) & (1<<31)) == 0)
	{
		if(delay < 10)
			goto reset_pll;
		
		delay--;
	}
	
}

static void clocks_set_sys_defaults(void)
{
    Wr_reg_bits(SYS_CLK_CNTL,0,15,1); //switch to osc_in
    int i=0;
    for(i=0;i<10;i=i+1){}
    Wr_reg_bits(SYS_CLK_CNTL,0,13,1); //disable clk_mux_div

    //set spi flash clock to div 4
    Wr_reg_bits(SPI_FLASH_CTRL,0,12,1);

    //set system pll to 0.8GHz
    set_sys_pll( 100,//M
		 3, //N
		 0, //OD
		 0, //reset
		 1  //enable
		);

    Wr_reg_bits(SYS_CLK_CNTL,1,11,2);  //select source 1: sys_pll
    Wr_reg_bits(SYS_CLK_CNTL,3,0,11);  //div=4
    Wr_reg_bits(SYS_CLK_CNTL,1,13,1);  //enable clk_mux_div

    for(i=0;i<10;i=i+1){}

    Wr_reg_bits(SYS_CLK_CNTL,1,15,1); //switch from osc_in to pll clock

}

void ctrl_crystal_pad(int on)
{
	if(on)
		Wr_reg_bits(AO_SYS_CONTROL_REG0, 1, 1, 1); //enable crystal pad
	else
		Wr_reg_bits(AO_SYS_CONTROL_REG0, 0, 1, 1); //disable crystal pad

	return;
}

int calibrate_internal_osc()
{
	int i;
	for(i=10; i>0; i--)
	{
		*P_INTER_OSC_CTL0 = 0x64054377;
		udelay(250);
		*P_INTER_OSC_CTL1 = 0x127625;
		udelay(250);
		*P_INTER_OSC_CTL0 = 0x44054377;
		udelay(500);
		if(*P_INTER_OSC_CTL0 >> 31 == 0x1)
			return 0;
	}
	
	return -1;
}

int switch_clk_to_32k()
{
	int i;
	
	reset_iosc();
	
	Wr_reg_bits(SYS_CLK_CNTL,0,15,1); //switch 24m osc
	
	Wr_reg_bits(SYS_CLK_CNTL,0x0,0,11); //div = 1

	//config internal osc freq: 32k
	*P_INTER_OSC_CTL0 = 0x64054377;
	*P_INTER_OSC_CTL1 = 0x00127625;
	*P_INTER_OSC_CTL0 = 0x44054377;
	
	Wr_reg_bits(SYS_CLK_CNTL,2,11,2); //select internal osc.
	
	for(i=0; i<10; i++);	
	
	Wr_reg_bits(SYS_CLK_CNTL,1,15,1); //switch internal osc.

	for(i=0; i<10; i++);

	ctrl_crystal_pad(0);
	
	return 0;
}

int switch_clk_to_24m()
{
	int i;
	
	ctrl_crystal_pad(1);
	
	for(i=0; i<10; i++);
	
	Wr_reg_bits(I2S_READ_ADR_1C, 1, 15, 1);
	Wr_reg_bits(SYS_CLK_CNTL, 0, 15, 1);

	for(i=0; i<10; i++);
	
	return 0;
}

int clk_get_rate(unsigned clksrc)
{
	int ret = -1;
	switch(clksrc)
	{
		case SYS_PLL_CLK_SRC:
			int M = Rd_reg_bits(SYS_PLL_CTL, 0, 9);
			int N = Rd_reg_bits(SYS_PLL_CTL, 9, 5);
			int OD = Rd_reg_bits(SYS_PLL_CTL, 16, 2);
			int DIV = Rd_reg_bits(SYS_CLK_CNTL, 0, 11) + 1;
//			printf("M: %d, N: %d, OD: %d, DIV: %d\n", M, N, OD, DIV);
			int od = 1;
			if(OD == 1)
				od = 2;
			else if(OD == 2)
				od = 4;
			
			ret = ((XTAL_24M*M)/N/od/DIV)*M_HZ;
			break;
	}
	
	return ret;
}

void clock_init()
{
	clocks_set_sys_defaults();
}


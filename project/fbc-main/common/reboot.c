#include <c_arc_pointer_reg.h>
#include <spi_regional_division.h>
#include <reboot.h>

int reboot(unsigned reson)
{
	*P_PREG_STICKY_REG0 = reson;

	
	//*P_PERIPHS_WATCHDOG_CTL &= (~(1<<19));
	
	//*P_PERIPHS_WATCHDOG_CTL &= (~(1<<18));
	//*P_PERIPHS_WATCHDOG_CTL |= (*P_PERIPHS_WATCHDOG_CTL&0xffff0000) | 10;
	//*P_PERIPHS_WATCHDOG_CTL |= (1<<19);
	//*P_PERIPHS_WATCHDOG_CTL &= (~(1<<20));	
	//*P_PERIPHS_WATCHDOG_CTL |= (1<<20);
	//for(int i=0; i<100; i++);
	//*P_PERIPHS_WATCHDOG_CTL &= (~(1<<20));
	disable_watchdog();
	set_watchdog_threshold(10);
	enable_watchdog();
	reset_watchdog();
	
	while(1);

	return 0;
}

void reset_ee()
{
	int delay;
	for(delay = 100; delay > 0; delay--);
	
	*P_RESET_EE_LEVEL &= (~(0x1 << 0));
	
	for(delay = 100; delay > 0; delay--);
	
	*P_RESET_EE_LEVEL |= 0x1;
	
	return;
}

void reset_spi()
{
	int delay;
	for(delay = 100; delay > 0; delay--);
	
	*P_RESET0_REGISTER &= (~(0x1 << 1));
	
	for(delay = 100; delay > 0; delay--);
	
	*P_RESET0_REGISTER |= (0x1 << 1);
	
	return;
}

void reset_ir()
{
	int delay;
	for(delay = 100; delay > 0; delay--);
	
	*P_RESET0_LEVEL &= (~(0x1 << 6));
	
	for(delay = 100; delay > 0; delay--);
	
	*P_RESET0_LEVEL |= (0x1 << 6);
	
	return;
}

void reset_iosc()
{
	int delay;
	for(delay = 100; delay > 0; delay--);
	
	*P_RESET0_LEVEL &= (~(0x1 << 9));
	
	for(delay = 100; delay > 0; delay--);
	
	*P_RESET0_LEVEL |= (0x1 << 9);
	
	return;
}

int reboot_sw(unsigned reson)
{
	*P_PREG_STICKY_REG0 = reson;
	
	typedef void (*reboot)(void);
	((reboot)SPI_BASE)();
	
	return 0;
}

unsigned get_boot_flag()
{
	return *P_PREG_STICKY_REG0;
}

int set_boot_flag(unsigned int num)
{
	*P_PREG_STICKY_REG0 = num;
	return 0;
}

int reset_watchdog()
{
	int i;
	
	*P_PERIPHS_WATCHDOG_CTL &= (~(1<<20));
	
	*P_PERIPHS_WATCHDOG_CTL |= (1<<20);
	for(i=0; i<100; i++);
	*P_PERIPHS_WATCHDOG_CTL &= (~(1<<20));
	
	return 0;
}

int enable_watchdog()
{
	*P_PERIPHS_WATCHDOG_CTL |= (1 << 19);
	return 0;
}

int enable_watchdog_interrupt()
{
	*P_PERIPHS_WATCHDOG_CTL |= (1 << 18);
	return 0;
}

int disable_watchdog()
{
	*P_PERIPHS_WATCHDOG_CTL &= ~(1 << 19);
	return 0;
}

int disable_watchdog_interrupt()
{
	*P_PERIPHS_WATCHDOG_CTL &= ~(1 << 18);
	return 0;
}

int set_watchdog_threshold(unsigned short th)
{
	*P_PERIPHS_WATCHDOG_CTL = *P_PERIPHS_WATCHDOG_CTL & (~0xffff) | th;
	return 0;
}

unsigned get_watchdog_threshold()
{
	unsigned ret = 0;

	ret = *P_PERIPHS_WATCHDOG_CTL & 0xffff;

	return ret;
}

unsigned get_watchdog_current_count()
{
	unsigned ret = 0;

	ret = *P_PERIPHS_WATCHDOG_CNT & 0xffff;

	return ret;
}


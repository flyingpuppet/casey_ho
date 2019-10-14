#ifndef __FBC_REBOOT_H__
#define __FBC_REBOOT_H__

#define REBOOT_FLAG_NORMAL		0x00000000
#define REBOOT_FLAG_UPGRADE		0x80808080
#define REBOOT_FLAG_UPGRADE2	0x88888888	// reserved
#define REBOOT_FLAG_SUSPEND		0x12345678

int reboot(unsigned reson);
unsigned get_boot_flag();
int set_boot_flag(unsigned int num);

void reset_spi();
void reset_iosc();
void reset_ir();
void reset_ee();
int reboot_sw(unsigned reson);

int reset_watchdog();	//feed the dog
int enable_watchdog();
int enable_watchdog_interrupt();
int disable_watchdog();
int disable_watchdog_interrupt();
int set_watchdog_threshold(unsigned short th);
unsigned get_watchdog_threshold();
unsigned get_watchdog_current_count();

#endif	//__FBC_REBOOT_H__
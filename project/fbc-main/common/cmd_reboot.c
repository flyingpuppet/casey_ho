#include <string.h>
#include <common.h>
#include <command.h>
#include <reboot.h>


extern void jump_0();

int do_reboot(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	serial_puts("enter reboot\n");
	if(argc == 1)
	{
		return reboot(0);
	}
	else
	{
		if(argc >= 3)
		{
			if(!strcmp("-r", argv[1]))
			{
				if(!strcmp("upgrade", argv[2]))
				{
					if(argc > 3 && !strcmp("uart1", argv[3]))
					{
						return reboot(0x88888888);
					}

					return reboot(0x80808080);
				}
				else if(!strcmp("suspend", argv[2]))
				{
					return reboot(0x12345678);
				}
				else if(!strcmp("sw_reboot", argv[2]))
				{
					return reboot_sw(0x0);
				}
#ifndef IN_FBC_MAIN_CONFIG
				else if(!strcmp("loadu", argv[2]))
				{
					jump_0();
					//*P_PREG_STICKY_REG0 = 0x80808080;
					return 0x80808080;
				}
				else if(!strcmp("loadm", argv[2]))
				{
					jump_0();
					return 0;
				}
#endif
			}
			
		}
		
	}

	return cmd_usage(cmdtp);
}

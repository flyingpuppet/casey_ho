#include <common.h>
#include <command.h>
#include <ctype.h>
#include <stdlib.h>
#include <serial.h>
#include <spi_flash.h>

int do_spi_flash(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	const char *cmd;
	
	if (argc < 2)
		goto usage;

	cmd = argv[1];

	unsigned offset;
	unsigned len;
	char *endp;
	int ret;
		
	if (strcmp(cmd, "read") == 0 || strcmp(cmd, "write") == 0)
	{
		unsigned addr;
		void *buf;
		
		if (argc < 5)
			goto usage;

		addr = strtoul(argv[2], &endp, 16);
		if (*argv[2] == 0 || *endp != 0)
			goto usage;
		offset = strtoul(argv[3], &endp, 16);
		if (*argv[3] == 0 || *endp != 0)
			goto usage;
		len = strtoul(argv[4], &endp, 16);
		if (*argv[4] == 0 || *endp != 0)
			goto usage;

		buf = (unsigned *)addr;
		if (strcmp(argv[1], "read") == 0)
		{
			ret = spi_flash_read(get_spi_flash_device(0), offset, len, buf);
		}
		else
	    {
	    	if(len != spi_flash_write(get_spi_flash_device(0), offset, len, buf))
			{
    			printf("spi flash %s failed\n", argv[1]);
				return 1;
    		}
			printf("spi flash write success!\n");
		}
		
		return 0;
		
	}
	else if(strcmp(cmd, "erase") == 0)
	{
		if (argc < 4)
			goto usage;

		offset = strtoul(argv[2], &endp, 16);
		if (*argv[2] == 0 || *endp != 0)
			goto usage;
		len = strtoul(argv[3], &endp, 16);
		if (*argv[3] == 0 || *endp != 0)
			goto usage;

		ret = spi_flash_erase(get_spi_flash_device(0), offset, len);
		if (ret) {
			printf("SPI flash %s failed\n", argv[1]);
			return 1;
		}

		return 0;
	}

	
usage:
	return cmd_usage(cmdtp);

}


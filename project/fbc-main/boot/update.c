#include <string.h>
#include <stdlib.h>
#include <serial.h>
#include <common.h>
#include <spi_flash.h>
#include <spi_regional_division.h>
#include <update.h>
#include <reboot.h>
#include <crc.h>

struct serial_device *serial_dev;
extern int sprintf(char * buffer, const char *__fmt, ...);
extern int vsprintf(char *buf, const char *fmt, va_list args);
extern "C" int printfx(const char *__fmt, ...)
{
	va_list args;
	unsigned int i;
	char printbuffer[256];
	va_start(args, __fmt);
	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf(printbuffer, __fmt, args);
	va_end(args);
	/* Print the string */
	serial_dev->puts(printbuffer);
	return i;
}


static int send_response(struct serial_device *sd, unsigned res)
{
	char cmd[6] = {0};
	
	if(!sd) return -1;

	if(CONFIG_ERROR_RESP == res)
		memset(cmd, 0xa5, sizeof(cmd));
	else
		memset(cmd, 0x5a, sizeof(cmd));
	
	cmd[5] = 0;
	
	sd->puts(cmd);
	
	return 0;
}

static int data_stream_read(update_ctrl_t *update_ctrl)
{
	unsigned i = 0;
	unsigned ret = 0;
	char c;
	char crc[5] = {0};
	
	if(!update_ctrl) return -1;
	
	printfx("enter data read update_ctrl->flag: 0x%x\n", update_ctrl->flag);
	do
	{
		c = update_ctrl->serial_dev->getc();
		if(rc_pkg_state == update_ctrl->flag)
		{
			if(i < MAX_BUF_SIZE)
			{
				update_ctrl->buf[i] = c;
			}
			
			update_ctrl->received_cnt++;
			
			if(i%256 == 0)
			{
#ifdef _DEBUG_UPGRADE_
				printfx("buf[%d] = 0x%x, rcnt = %d\n", i, update_ctrl->buf[i], update_ctrl->received_cnt);
#else
				printfx(".");
#endif
			}
			
			if(MAX_BUF_SIZE - 1 == i || update_ctrl->received_cnt == update_ctrl->total)
			{
				serial_putc('\n');
				break;
			}
			
		}
		else if(rc_cmd_state == update_ctrl->flag)
		{
			if(c == '\n' || c == '\r' || i == MAX_CMD_LENGTH)
			{
				if(i == MAX_CMD_LENGTH)
				{
					update_ctrl->buf[MAX_CMD_LENGTH-1] =  '\0';
				}
				update_ctrl->buf[i] = '\0';
				
				update_ctrl->serial_dev->putc('\n');
				
				i++;
				break;
			}
			
			update_ctrl->serial_dev->putc(c);
			
			update_ctrl->cmd[i] = c;		
				
		}
		else if(rc_crc_state == update_ctrl->flag)
		{
			crc[i] = c;
			update_ctrl->serial_dev->putc(c);
			printfx("received crc: 0x%x\n", c);
			if(i == sizeof(crc) - 2)
			{
				memcpy(&(update_ctrl->crc), crc, sizeof(unsigned));
				break;
			}
		}
		i++, ret++;
	}
	while(1);
	
	return (ret + 1);
}

static int move_image(struct spi_flash *flash, unsigned s_offs, unsigned b_offs, unsigned size)
{
	char buf[SPI_BLOCK_SIZE];
	unsigned base;
	unsigned erase_size;
	
	base = s_offs;
	
	for(erase_size = SPI_FLASH_SECTOR_SIZE; erase_size < size; erase_size += SPI_FLASH_SECTOR_SIZE);

	if(spi_flash_erase(flash, b_offs, erase_size))
	{
		printfx("In backup_image erase failed!\n");
		return -1;
	}
	
	while(s_offs >= base + erase_size)
	{
		spi_flash_read(flash, s_offs, SPI_BLOCK_SIZE, buf);
		spi_flash_write(flash, b_offs, SPI_BLOCK_SIZE, buf);
		s_offs += SPI_BLOCK_SIZE;
		b_offs += SPI_BLOCK_SIZE;
	}
	
	printfx("backup image success!\n");
	
	return 0;
}

static int parse_cmd_line (char *line, char *argv[])
{
    int nargs = 0;

    while (nargs < CONFIG_UPDATE_CMD_MAXARGS)
	{

        while ((*line == ' ') || (*line == '\t')) {
            ++line;
        }

        if (*line == '\0') {
            argv[nargs] = NULL;
            return (nargs);
        }

        argv[nargs++] = line;

        while (*line && (*line != ' ') && (*line != '\t')) {
            ++line;
        }

        if (*line == '\0') {
            argv[nargs] = NULL;
            return (nargs);
        }

        *line++ = '\0';
    }
	
    return (nargs);
}

int parse_cmd(update_ctrl_t *update_ctrl)
{
	if(!update_ctrl) return -1;

	data_stream_read(update_ctrl);
	
	return parse_cmd_line(update_ctrl->cmd, update_ctrl->argv);
	
}

int handle_cmd(update_ctrl_t *update_ctrl)
{
	unsigned response = 0;
	int ret = 0;
	
	if(update_ctrl->channel == CONSOLE_CHANNEL_DEV)
		serial_dev = get_serial_device(G9TV_CHANNEL_DEV);
	else
		serial_dev = get_serial_device(CONSOLE_CHANNEL_DEV);
	
	serial_dev->init();
	
	if(!update_ctrl) return -1;
	
	if(update_ctrl->new_line_flag)
	{
		update_ctrl->new_line_flag = 0;
		
		update_ctrl->serial_dev->puts(CONFIG_SYS_PROMPT);
	}
	
	if(parse_cmd(update_ctrl) == -1)
	{
		update_ctrl->serial_dev->puts("\nunknown cmd!\n");
		update_ctrl->new_line_flag = 1;
		return 0;
	}
	
	if(update_ctrl->argv[0] && (!strcmp(CONFIG_REBOOT_CMD, update_ctrl->argv[0]) || !strcmp(CONFIG_EXIT_CMD, update_ctrl->argv[0])))
	{
		update_ctrl->serial_dev->puts("\nexit upgrade!\n");
		return 1;
	}
	else if(update_ctrl->argv[0] && (!strcmp(CONFIG_UPDATE_CMD, update_ctrl->argv[0])))
	{
		if(update_ctrl->argv[1] && update_ctrl->argv[2])
		{
			update_ctrl->s_offs = strtoul(update_ctrl->argv[1], NULL, 16);
			update_ctrl->total = strtoul(update_ctrl->argv[2], NULL, 16);
		}
		else
		{
			update_ctrl->serial_dev->puts("\ncmd format error!\n");
			init_update_ctrl_t(update_ctrl);
			return 0;
		}
	}
	else
	{
		init_update_ctrl_t(update_ctrl);
		return 0;
	}

	if(update_ctrl->do_backup && !(update_ctrl->do_backup(update_ctrl)))
	{
		if(update_ctrl->do_update) 
		{
			ret = update_ctrl->do_update(update_ctrl);
		}

/*		if(-1 != ret && update_ctrl->do_check)
		{
			printfx("start check write data.\n");
			ret = update_ctrl->do_check(update_ctrl);
		}
		
		if(!ret || (update_ctrl->do_check && update_ctrl->do_check(update_ctrl)))
		{
			printf("check img failed!\n");
//			update_ctrl->do_restore(update_ctrl);

			send_response(update_ctrl->serial_dev, CONFIG_ERROR_RESP);
		}
		else
		{
//			send_response(update_ctrl->serial_dev, CONFIG_OK_RESP);
		}*/
	}
	else
	{
		update_ctrl->serial_dev->puts("backup image failed!\n");
		send_response(update_ctrl->serial_dev, CONFIG_ERROR_RESP);
	}
	
	init_update_ctrl_t(update_ctrl);
	if(ret != -1)
	{
		printfx("send -- ok response: %x ok.\n", CONFIG_OK_RESP);
		send_response(update_ctrl->serial_dev, CONFIG_OK_RESP);
	}
	else
	{
		printfx("send -- response: %x failed.\n", CONFIG_ERROR_RESP);
		send_response(update_ctrl->serial_dev, CONFIG_ERROR_RESP);		
	}
	
	return 0;
}

int handle_backup(struct update_ctrl *ctrl)
{
	if(!ctrl) return -1;
	
//	return move_image(ctrl->flash_dev, ctrl->s_offs, ctrl->b_offs, ctrl->total);
	return 0;
}

int handle_restore(struct update_ctrl *ctrl)
{
	if(!ctrl) return -1;
	
	return move_image(ctrl->flash_dev, ctrl->b_offs, ctrl->s_offs, ctrl->total);
}

int handle_update(struct update_ctrl *ctrl)
{
	int ret =0;
	int wlen = 0;
	int read_stream_size = 0;
	unsigned erase_size;
	unsigned crc = 0;
	char msg_buf[256];

	if(!ctrl) return -1;

	if(ctrl->show_progress && ctrl->show_progress(er_spi_state, 15));
	
	for(erase_size = SPI_FLASH_SECTOR_SIZE; erase_size < ctrl->total; erase_size += SPI_FLASH_SECTOR_SIZE);

	ctrl->flag = rc_pkg_state;
	printfx("enter handle_update.\n");
	do
	{
		ret = data_stream_read(ctrl);
		if(ret == -1)
		{
			printfx("In start_update serial_stream_read error!\n");
			if(ctrl->show_update_msg) {
				sprintf(msg_buf, "serial data receive error!!!");
				ctrl->show_update_msg(1, msg_buf);
			}
			return -1;
		}

		if(ctrl->show_update_msg) {
			sprintf(msg_buf, "serial data receive ok!");
			ctrl->show_update_msg(0, msg_buf);
		}
		printfx("receive data ok!\n");
		
		ctrl->flag = rc_crc_state;

		data_stream_read(ctrl);	
		printfx("receive crc value ok!\n");
		
		printfx("length = %d\n", (ctrl->received_cnt >= MAX_BUF_SIZE) ? MAX_BUF_SIZE : ctrl->received_cnt);
		crc = crc32(0, ctrl->buf, (ctrl->received_cnt >= MAX_BUF_SIZE) ? MAX_BUF_SIZE : ctrl->received_cnt);		
		if(crc != ctrl->crc)
		{
			printfx("crc: 0x%x, ctrl->crc: 0x%x\n", crc, ctrl->crc);
			if(ctrl->show_update_msg) {
				sprintf(msg_buf, "CRC error!!! calculate crc = 0x%X, receive crc = 0x%X", crc, ctrl->crc);
				ctrl->show_update_msg(1, msg_buf);
			}
			return -1;
		}
		
		ctrl->flag = rc_pkg_state;

		printfx("start erase! offs: 0x%x, size: 0x%x\n", ctrl->s_offs, erase_size);
rewrite:
		spi_flash_erase(ctrl->flash_dev, ctrl->s_offs, erase_size);

		printfx("offs: 0x%x, len: 0x%x\n", ctrl->s_offs + ctrl->write_spi_cnt, ret);
		wlen = spi_flash_write(ctrl->flash_dev, ctrl->s_offs + ctrl->write_spi_cnt, ret, ctrl->buf);
		printfx("pre write offset: 0x%X, write size: 0x%X\n", ctrl->s_offs, erase_size);
		ctrl->write_spi_cnt += ret;

		if(ctrl->do_check)
		{
			printfx("enter check write data.\n");
			if(ctrl->do_check(ctrl) == -1)
			{
				printfx("write data error!\n");
				ctrl->d_rewrite_cnt ++;
				if(ctrl->d_rewrite_cnt <= MAX_REWRITE_CNT)
				{
					ctrl->write_spi_cnt -= ret;
					printfx("rewrite data to flash!\n");
					goto rewrite;
				}
				printfx("rewrite data failed!\n");
				return -1;
			}
		}
		
		if(ctrl->show_update_msg) {
			sprintf(msg_buf, "write offset: 0x%X, size: 0x%X", ctrl->s_offs, erase_size);
			ctrl->show_update_msg(0, msg_buf);
		}

		printfx("ctrl->write_spi_cnt = %d, ctrl->total = 0x%x, wlen = 0x%x\n", ctrl->write_spi_cnt, ctrl->total, wlen);
		
	}
	while(ctrl->received_cnt != ctrl->total);

	printfx("write spi: 0x%x\n", ctrl->write_spi_cnt);
	return ctrl->write_spi_cnt;
}

int handle_check(struct update_ctrl *ctrl)
{
	int offset, len, total;
	unsigned s_cmp;
	int ret = 0;
	
	if(!ctrl) return -1;

	for(s_cmp = 0, offset = ctrl->s_offs, total = ctrl->write_spi_cnt; total > 0; offset += len, total -= len, s_cmp += len)
	{
		len = MAX_EXT_BUF_SIZE <= total ? MAX_EXT_BUF_SIZE : total;
		spi_flash_read(ctrl->flash_dev, offset, len, ctrl->ext_buf);
		ret = memcmp(ctrl->buf+s_cmp, ctrl->ext_buf, len);
		
		if(ret != 0)
		{
			ret = -1;
			break;
		}
	}
	
	return ret;
}

void init_update_ctrl_t(update_ctrl_t *update_ctrl)
{
	if(!update_ctrl) return;
	
	memset(update_ctrl, 0, sizeof(update_ctrl_t));
	update_ctrl->new_line_flag = 1;
	update_ctrl->channel = get_boot_flag();
	update_ctrl->flag = rc_cmd_state;
	update_ctrl->buf = (unsigned char *)BUF_ADDR;
	update_ctrl->ext_buf = (unsigned char *)EXT_BUF_ADDR;
	update_ctrl->flash_dev = get_spi_flash_device(0);
		
	if(CONSOLE_CHANNEL == update_ctrl->channel)
	{
		update_ctrl->serial_dev = get_serial_device(CONSOLE_CHANNEL_DEV);
	}
	else
	{
		serial_init(G9TV_CHANNEL_DEV);
		update_ctrl->serial_dev = get_serial_device(G9TV_CHANNEL_DEV);
	}
	
	update_ctrl->do_backup = handle_backup;	
	update_ctrl->do_update = handle_update;
	update_ctrl->do_check = handle_check;
	update_ctrl->do_restore = handle_restore;

	return;
}


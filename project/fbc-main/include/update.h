#ifndef __UPDATE_H__
#define __UPDATE_H__

#ifndef NULL
#define NULL	0
#endif

#define ERROR						-1
#define MAX_BUF_SIZE				0x10000
#define CHECK_INFO_SIZE				0x20
#define BUF_ADDR					0x80020000
#define MAX_EXT_BUF_SIZE			0x2000
#define EXT_BUF_ADDR				(0xFFFF0000 + UPDATE_DATA_SIZE)
#define TOTAL_BUF_SIZE				(MAX_BUF_SIZE + MAX_EXT_BUF_SIZE)

#define CONSOLE_CHANNEL				0x80808080
#define G9TV_CHANNEL				0x88888888
#define CONSOLE_CHANNEL_DEV			0x0
#define G9TV_CHANNEL_DEV			0x1	
#define CONFIG_UPDATE_CMD_MAXARGS	5

#define MAX_CMD_LENGTH              0x40
#define MAX_REWRITE_CNT             0x1

#define CONFIG_REBOOT_CMD			"reboot"
#define CONFIG_EXIT_CMD				"exit"
#define CONFIG_UPDATE_CMD			"upgrade"
#define CONFIG_NEXT_TRANS_CMD		"next transimission"
#define CONFIG_SYS_PROMPT			"fbc-upgrade#"

#define CONFIG_ERROR_RESP			0xa5a5a5a5
#define CONFIG_OK_RESP				0x5a5a5a5a

enum {
	rc_cmd_state = 0x0,
	rc_pkg_header_state,
	rc_pkg_state,
	rc_crc_state,
	backup_state = 0x10,
	er_spi_state,
	wr_spi_state,
	check_state,
};

typedef struct update_ctrl {
	unsigned channel;	//channel select.
	unsigned s_offs;	//update offset.
	unsigned b_offs;	//backup offset.
	unsigned write_spi_cnt;
	unsigned received_cnt;
	unsigned total;
	unsigned crc;
	unsigned char flag;
	unsigned char new_line_flag;
	unsigned char d_rewrite_cnt;
	char cmd[MAX_CMD_LENGTH];
	char *argv[CONFIG_UPDATE_CMD_MAXARGS + 1];
	unsigned char *buf;
	unsigned char *ext_buf;

	struct serial_device *serial_dev;
	struct spi_flash *flash_dev;
	
	int (*do_backup)(struct update_ctrl *ctrl);
	int (*do_restore)(struct update_ctrl *ctrl);
	int (*do_update)(struct update_ctrl *ctrl);
	int (*do_check)(struct update_ctrl *ctrl);
	int (*show_progress)(unsigned state, unsigned progress);
	int (*show_update_msg)(int msg_type, const char *msg);
} update_ctrl_t;

void init_update_ctrl_t(update_ctrl_t *ctrl);
int handle_cmd(update_ctrl_t *ctrl);
#endif

#define CMD_PACKAGE		0x01
#define CMD_RESPONSE_PACKAGE	0x02
#define DATA_PACKAGE	0x03
#define DATA_RESPONSE_PACKAGE	0x04
#define INFO_PACKAGE	0x05
#define SYNC_HEAD_SIZE	0x4

#define CMD_SYNC_HEAD	"CMD:"
#define CMD_RES_SYNC_HEAD	"RSP:"
#define DATA_SYNC_HEAD	"DAT:"
#define DATA_HEAD_FLAG	"5AA5"
#define DATA_TAIL_FLAG	"A55A"
#define DATA_RES_SYNC_HEAD	"RCV:"
#define INFO_SYNC_HEAD	"INF:"

struct cmd_package {
	char cmd_sn[4];
	char cmd_id[8];
	char param_type_cnt[4];
	void *param;
	char crc[4];
};

struct cmd_response_package {
	char sync[4];
	char cmd_sn[4];
	char type[4];
	char *data;
};

struct data_package {
	char data_sn[4];
	char data_len[4];
	char *data;
	char crc[4];
};

struct data_response_package {
	char sync[4];
	char data_sn[4];
	char result[4];
};

struct info_package {
	char info_id[4];
	char info_type_cnt[4];
	char *param;
};


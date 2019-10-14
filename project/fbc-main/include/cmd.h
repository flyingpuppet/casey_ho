#ifdef CMD_H
#else
#define CMD_H

#include <listop.h>

#define MAX_CMD 256
#define CMD_CALL_TASK_MAX   8

/*#define CMD_SET_DEVICE_ID			0x10
#define CMD_DEVICE_ID				0x11
#define CMD_CLIENT_TYPE				0x12
#define CMD_DEVICE_NUM				0x13
#define CMD_ACTIVE_KEY				0x14
#define CMD_ACTIVE_STATUS			0x15
#define CMD_DBG_REGISTER_ACCESS		0x18
#define CMD_DBG_MEMORY_ACCESS		0x19
#define CMD_DBG_SPI_ACCESS			0x1a
#define CMD_DBG_VPU_MEMORY_ACCESS	0x1b
#define CMD_DBG_MEMORY_TRANSFER		0x1c
#define CMD_INPUT_DOWN      		0x1d
#define CMD_INPUT_UP        		0x1e*/

typedef enum fbc_command_e{
	VPU_CMD_NULL = 0,
	FBC_REBOOT_UPGRADE = 0x1,
	FBC_USER_SETTING_DEFAULT = 0x02,
	FBC_USER_SETTING_SET,
	FBC_GET_HDCP_KEY,
	FBC_PANEL_POWER,
	FBC_SUSPEND_POWER,
	//TOP CMD num:6
	VPU_CMD_INIT = 0x8,	//parameter num 0
	VPU_CMD_ENABLE, 	//parameter num 1;bit0~6:module;bit7:enable(1) or disable(0)
	VPU_CMD_BYPASS, 	//parameter num 1;bit0~6:module;bit7:bypass(1) or not(0)
	VPU_CMD_OUTPUT_MUX,	//parameter num 1;1:lvds;2:vx1;3:minilvds
	VPU_CMD_TIMING,		//parameter num 1;reference vpu_timing_t
	VPU_CMD_SOURCE,		//parameter num 1;reference vpu_source_t
	VPU_CMD_GAMMA_MOD,	//parameter num 1;reference vpu_gammamod_t
	VPU_CMD_D2D3 = 0xf, 	//0xf:D2D3
	//

	CMD_SET_DEVICE_ID =	0x10,
	CMD_DEVICE_ID,
	CMD_CLIENT_TYPE,
	CMD_DEVICE_NUM,
	CMD_ACTIVE_KEY,
	CMD_ACTIVE_STATUS,
	CMD_PANEL_INFO,
	CMD_LVDS_SSG_SET,

	CMD_DBG_REGISTER_ACCESS = 0x18,
	CMD_DBG_MEMORY_ACCESS,
	CMD_DBG_SPI_ACCESS,
	CMD_DBG_VPU_MEMORY_ACCESS,
	CMD_DBG_MEMORY_TRANSFER,
	CMD_INPUT_DOWN,
	CMD_INPUT_UP,
	CMD_FBC_MAIN_CODE_VERSION,

	//0x1f reserved
	//PQ+debug CMD num:32
	VPU_CMD_NATURE_LIGHT_EN = 0x20,	//0 or 1;on or off  ????
	VPU_CMD_BACKLIGHT_EN,		//0 or 1;on or off
	VPU_CMD_BRIGHTNESS,	//parameter num 2;parameter1:distinguish two modules;parameter2:ui value
	VPU_CMD_CONTRAST,	//parameter num 2;parameter1:distinguish two modules;parameter2:ui value
	VPU_CMD_BACKLIGHT,	//parameter num 1;
	VPU_CMD_RES1,		//reserved
	VPU_CMD_SATURATION,	//parameter num 1;
	VPU_CMD_DYNAMIC_CONTRAST,	//0 or 1;??
	VPU_CMD_PICTURE_MODE,	//??
	VPU_CMD_PATTERN_EN,	//0 or 1;on or off
	VPU_CMD_PATTEN_SEL,	//0x2a parameter num 1;PATTEN SELECT
	VPU_CMD_COLOR_SURGE,
	VPU_CMD_RES3,
	VPU_CMD_RES4,
	VPU_CMD_RES5,
	VPU_CMD_USER_GAMMA = 0x2f,
	//0x30:sound_mode_def
	VPU_CMD_COLOR_TEMPERATURE_DEF = 0x31,	//def:factory setting
	VPU_CMD_BRIGHTNESS_DEF,
	VPU_CMD_CONTRAST_DEF,
	VPU_CMD_COLOR_DEF,
	VPU_CMD_HUE_DEF,
	VPU_CMD_BACKLIGHT_DEF,
	VPU_CMD_RES7,
	VPU_CMD_AUTO_LUMA_EN = 0x38,//0 or 1;on or off;appoint to backlight?
	VPU_CMD_HIST,		//parameter num 0;read hist info
	VPU_CMD_BLEND,		//parameter num ?;
	VPU_CMD_DEMURA, 	//parameter num ?;
	VPU_CMD_CSC,		//parameter num ?;
	VPU_CMD_CM2,		//parameter num 1;index
	VPU_CMD_GAMMA,		//parameter num 1;index
	VPU_CMD_SRCIF,
	//WB CMD num:10
	VPU_CMD_RED_GAIN_DEF = 0x40,
	VPU_CMD_GREEN_GAIN_DEF,
	VPU_CMD_BLUE_GAIN_DEF,
	VPU_CMD_PRE_RED_OFFSET_DEF,
	VPU_CMD_PRE_GREEN_OFFSET_DEF,
	VPU_CMD_PRE_BLUE_OFFSET_DEF,
	VPU_CMD_POST_RED_OFFSET_DEF,
	VPU_CMD_POST_GREEN_OFFSET_DEF,
	VPU_CMD_POST_BLUE_OFFSET_DEF,
	VPU_CMD_RES9,
	VPU_CMD_WB = 0x4a,
	//DNLP PARM
	VPU_CMD_DNLP_PARM,
	VPU_CMD_WB_VALUE,
	VPU_CMD_GRAY_PATTERN,
	VPU_CMD_BURN,
	CMD_HDMI_STAT,
	VPU_CMD_READ = 0x80,
	//VPU_CMD_HUE_ADJUST,	//parameter num 1;
	//VPU_CMD_WB,		//parameter num 3;one parameter include two items so that six items can all be included
	VPU_CMD_MAX = 50,//temp define 50		//

	//audio cmd
	AUDIO_CMD_SET_SOURCE = 0x50,
	AUDIO_CMD_SET_MASTER_VOLUME,
	AUDIO_CMD_SET_CHANNEL_VOLUME,
	AUDIO_CMD_SET_SUBCHANNEL_VOLUME,
	AUDIO_CMD_SET_MASTER_VOLUME_GAIN,
	AUDIO_CMD_SET_CHANNEL_VOLUME_INDEX,
	AUDIO_CMD_SET_VOLUME_BAR,
	AUDIO_CMD_SET_MUTE,
	AUDIO_CMD_SET_EQ_MODE,
	AUDIO_CMD_SET_BALANCE,
	AUDIO_CMD_GET_SOURCE,
	AUDIO_CMD_GET_MASTER_VOLUME,
	AUDIO_CMD_GET_CHANNEL_VOLUME,
	AUDIO_CMD_GET_SUBCHANNEL_VOLUME,
	AUDIO_CMD_GET_MASTER_VOLUME_GAIN,
	AUDIO_CMD_GET_CHANNEL_VOLUME_INDEX,
	AUDIO_CMD_GET_VOLUME_BAR,
	AUDIO_CMD_GET_MUTE,
	AUDIO_CMD_GET_EQ_MODE,
	AUDIO_CMD_GET_BALANCE,
	
	VPU_CMD_AUTO_ELEC_MODE =0x64,
	
	CMD_SET_FACTORY_SN = 0x66,
	CMD_GET_FACTORY_SN,
}fbc_command_t;


typedef struct {
	  unsigned int      cmd_owner ;
	  void *   data ;
}CMD_MODULE_DATA;

typedef struct {
	  list_t                  list;
	  CMD_MODULE_DATA       cmd_data ;
}CMD_LIST;



typedef struct {
//first 32 bits for input data.(G9)
	unsigned short len; // number bytes for this command
	unsigned short num_param; // number params for this command
	unsigned short type; // parameter format for this command: each 2 bit for 1 param(max 8 param), 1:byte, 2:word, 3:dword, 0:no available, LSB means param0's type

	//another 32 bits for return data.(FBC)
	unsigned short ret_len; // number bytes for this command
	unsigned short ret_num; // number retval for this command
	unsigned short retval_type; // return data format for this command: each 2 bit for 1 param(max 8 param), 1:byte, 2:word, 3:dword, 0:no available, LSB means param0's type
}cmd_def_t; // 64bit for each command


#define CmdID(s) s[0] // get id
#define LEN(s) cmd_def[CmdID(s)].len// get num bytes
#define NumParam(s) cmd_def[CmdID(s)].num_param// get num param
#define Type(s, index) ((cmd_def[CmdID(s)].type >> (index *2)) & 0x03)//get param[index] type

#define RET_LEN(s) cmd_def[CmdID(s)].ret_len// get num bytes
#define Ret_NumParam(s) cmd_def[CmdID(s)].ret_num// get num param
#define Ret_Type(s, index) ((cmd_def[CmdID(s)].retval_type >> (index *2)) & 0x03)//get param[index] type

int GetParam(unsigned char *s, int index); // get param[index]
int * GetParams(unsigned char *s); // get params

unsigned char * GetReturns(int cmd);
int GetReturnValue(unsigned char *s, int index); // get return[index]
int * GetReturnValues(unsigned char *s); // get returns

int SendCmd(int task_id, unsigned int cmd_owner, int cmd, int* params);
int SendReturn(int task_id, unsigned int cmd_owner, int cmd, int* params);

int *RunCommand(int id, int *params);
unsigned int CmdChannelAddData(unsigned int cmd_owner, unsigned char * data);
void freeCmdList(CMD_LIST * list);

typedef unsigned int (* save_parameter)(unsigned char * s);
//typedef unsigned int (* read_parameter)(unsigned char * s, int * returns);
typedef void (* backlight_func)(char val);


typedef int (* channel_send_data)(unsigned char *s, unsigned short len);
int RegisterChannel(unsigned int cmd_owner, channel_send_data func);

typedef int (* is_cmd_supported)(int cmd);
typedef unsigned int (* cmd_process_func)(unsigned char * s, int * returns);
unsigned int RegisterCmd(list_t * cmd_list, unsigned int task_id, unsigned int input_mask, is_cmd_supported func,cmd_process_func run_command);
unsigned int UnregisterCmd(unsigned int task_id);

extern const cmd_def_t cmd_def[MAX_CMD];

#endif //CMD_H


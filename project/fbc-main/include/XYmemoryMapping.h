#ifndef XY_MEMORY_MAPPING_H
#define XY_MEMORY_MAPPING_H

#include <cmd.h>

//DMA _USED: DMA audio i2s data from AUDIO_IN_FIFO to XY memory
//#define DMA_USED

// X Memory: Bank0: 256~512
#define XMEM_START				0
	#define INPUT_DATA			(XMEM_START + 512)
	#define END_OF_INPUT_DATA	(INPUT_DATA + 256)
#define XMEM_END				1024

// Y Memory: all Bank1 for output data
#define YMEM_START				0
	#define OUTPUT_DATA			(YMEM_START + 256)
	#define END_OF_OUTPUT_DATA	(OUTPUT_DATA + 256*3)
#define YMEM_END				1024

/*
*	If external codec driver is registed in system, internal codec drivers is disable.
* 	When no external codec driver, choice audio codec name below.
*/
#define TAS5707		0
#define TAS5711		1
#define CODEC_NAME	TAS5707

//Don't change the structs.
struct audio_effect{
	int (*init)(void);
#ifdef DMA_USED
	int (*audio_process)(unsigned int, unsigned int, int);
#else
	int (*audio_process)(short *, short *, int);
#endif
	int (*set_parameter)(unsigned char);
};

struct codec_control{
	int (*init)(void);
	int (*set_mute)(void); //set master volume to silence.
	int (*set_master_vol)(unsigned char);
	int (*set_channel_vol)(unsigned char, unsigned char);
	int (*set_subchannel_vol)(unsigned char);
	int (*set_EQ_mode)(unsigned char);
	int (*set_user_parameters)(unsigned char*);
	int (*set_fine_volume)(unsigned char);
};

/*codec state*/
#define MUTE		0
#define UNMUTE		1

/*EQ mode*/
#define TABLE_MODE	0
#define WALL_MODE	1

/*audio source of volume mapping*/
#define HDMI_SOURCE	0
#define ATV_SOURCE	1
#define AV_SOURCE	2
#define MPEG_SOURCE	3
#define MAX_SOURCE	4


struct audio_control{
	unsigned char source;
	unsigned char mute_state;
	unsigned char master_volume;
	unsigned char L_channel_volume;
	unsigned char R_channel_volume;
	unsigned char sub_channel_volume;
	unsigned char L_channel_index;
	unsigned char R_channel_index;
	unsigned char volume_bar;
	unsigned char EQ_mode;
	unsigned char balance;
	char master_volume_gain;
};


void register_audio_save(save_parameter func);


extern void RigisterAudioProcess(struct audio_effect *ptr);
extern void RegisterCodec(struct codec_control *ptr);

// 0: HDMI_SOURCE, 1: ATV_SOURCE, 2: AV_SOURCE, 3: MPEG_SOURCE. 
extern void set_audioin_source(unsigned char source);
extern int set_master_vol(unsigned char volume);
extern int set_channel_vol(unsigned char L_volume,unsigned char R_volume);
extern int set_subchannel_vol(unsigned char sub_volume);
extern int set_volume_mute(unsigned char mute_state);
extern int set_EQ_mode(unsigned char eq_mode);	//0: table mode, 1: wall mode. only two mode
extern int set_balance(unsigned char balance); //0~100, default:50
extern unsigned char get_audioin_source(void);
extern unsigned char get_master_vol(void);
extern void get_channel_vol(unsigned char *L_volume, unsigned char *R_volume);
extern unsigned char get_subchannel_vol(void);
extern unsigned char get_mute_state(void);
extern unsigned char get_EQ_mode(void);
extern unsigned char get_balance(void);

#endif

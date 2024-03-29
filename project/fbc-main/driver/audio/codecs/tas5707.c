#include <string.h>
#include <register.h>
#include <c_arc_pointer_reg.h>
#include <log.h>
#include <i2c.h>
#include <XYmemoryMapping.h>

#include "../audio_control.h"
#include "tas5707.h"

static char TAG[] = "tas5707";

extern void sleep(int us);

struct tas5707_parameters customer_parameter = {
	.DRC_enable = 0,
	.EQ_enable = 0,
};

static unsigned char TAS5707_drc1_table[3][8]={
	{0x00, 0x70, 0x0F, 0xE8, 0x00, 0x0F, 0xF0, 0x17},//0x3A---drc1_ae
	{0x00, 0x02, 0xA3, 0x99, 0x00, 0x7D, 0x5C, 0x65},//0x3B---drc1_aa
	{0x00, 0x00, 0x02, 0x46, 0x00, 0x7F, 0xFD, 0xB9},//0x3C---drc1_ad
};
static unsigned char tas5707_drc1_tko_table[3][4]={
	{0xFD, 0xF9, 0x3F, 0x6A},//0x40---drc1_t
	{0x0F, 0x81, 0x47, 0xAF},//0x41---drc1_k
	{0x00, 0x08, 0x42, 0x10},//0x42---drc1_o
};
static unsigned char tas5707_eq_table[2][14][20]={
//Table mode
{
	{0x00,0x7F,0x54,0x6E,0x0F,0x01,0x57,0x24,0x00,0x7F,0x54,0x6E,0x00,0xFE,0xA7,0x12,0x0F,0x81,0x55,0x5B},//0x29---ch1_bq[0] 
	{0x00,0x7E,0x82,0x6C,0x0F,0x05,0x3B,0x46,0x00,0x7C,0x89,0xA6,0x00,0xFA,0xC4,0xBA,0x0F,0x84,0xF3,0xEE},//0x2A---ch1_bq[1] 
	{0x00,0x7E,0x1B,0x07,0x0F,0x06,0xBF,0x57,0x00,0x7B,0x99,0x7B,0x00,0xF9,0x40,0xA9,0x0F,0x86,0x4B,0x7E},//0x2B---ch1_bq[2] 
	{0x00,0x83,0x8D,0x55,0x0F,0x1B,0x0D,0xBC,0x00,0x6B,0x3A,0x2E,0x00,0xE4,0xF2,0x44,0x0F,0x91,0x38,0x7D},//0x2C---ch1_bq[3] 
	{0x00,0x87,0x38,0x4D,0x0F,0x4D,0x35,0x96,0x00,0x55,0xC7,0x0A,0x00,0xB2,0xCA,0x6A,0x0F,0xA3,0x00,0xA8},//0x2D---ch1_bq[4] 
	{0x00,0x89,0xFB,0xFD,0x0F,0x81,0x9F,0xB6,0x00,0x45,0x9C,0x76,0x00,0x7E,0x60,0x4A,0x0F,0xB0,0x67,0x8D},//0x2E---ch1_bq[5] 
	{0x00,0x97,0x2F,0x9A,0x0F,0xCD,0x29,0xD7,0x00,0x2D,0x3B,0x42,0x00,0x32,0xD6,0x29,0x0F,0xBB,0x95,0x24},//0x2F---ch1_bq[6] 
	{0x00,0x7F,0x54,0x6E,0x0F,0x01,0x57,0x24,0x00,0x7F,0x54,0x6E,0x00,0xFE,0xA7,0x12,0x0F,0x81,0x55,0x5B},//0x29---ch1_bq[0]  
	{0x00,0x7E,0x82,0x6C,0x0F,0x05,0x3B,0x46,0x00,0x7C,0x89,0xA6,0x00,0xFA,0xC4,0xBA,0x0F,0x84,0xF3,0xEE},//0x2A---ch1_bq[1]  
	{0x00,0x7E,0x1B,0x07,0x0F,0x06,0xBF,0x57,0x00,0x7B,0x99,0x7B,0x00,0xF9,0x40,0xA9,0x0F,0x86,0x4B,0x7E},//0x2B---ch1_bq[2]  
	{0x00,0x83,0x8D,0x55,0x0F,0x1B,0x0D,0xBC,0x00,0x6B,0x3A,0x2E,0x00,0xE4,0xF2,0x44,0x0F,0x91,0x38,0x7D},//0x2C---ch1_bq[3]  
	{0x00,0x87,0x38,0x4D,0x0F,0x4D,0x35,0x96,0x00,0x55,0xC7,0x0A,0x00,0xB2,0xCA,0x6A,0x0F,0xA3,0x00,0xA8},//0x2D---ch1_bq[4]  
	{0x00,0x89,0xFB,0xFD,0x0F,0x81,0x9F,0xB6,0x00,0x45,0x9C,0x76,0x00,0x7E,0x60,0x4A,0x0F,0xB0,0x67,0x8D},//0x2E---ch1_bq[5]  
	{0x00,0x97,0x2F,0x9A,0x0F,0xCD,0x29,0xD7,0x00,0x2D,0x3B,0x42,0x00,0x32,0xD6,0x29,0x0F,0xBB,0x95,0x24},//0x2F---ch1_bq[6]  
},
//Wall mode
{
	{0x00,0x7F,0x54,0x6E,0x0F,0x01,0x57,0x24,0x00,0x7F,0x54,0x6E,0x00,0xFE,0xA7,0x12,0x0F,0x81,0x55,0x5B},//0x29---ch1_bq[0] 
	{0x00,0x7F,0x42,0x1F,0x0F,0x03,0x21,0xC3,0x00,0x7D,0xC4,0x90,0x00,0xFC,0xDE,0x3D,0x0F,0x82,0xF9,0x50},//0x2A---ch1_bq[1] 
	{0x00,0x7E,0x82,0x6C,0x0F,0x05,0x3B,0x46,0x00,0x7C,0x89,0xA6,0x00,0xFA,0xC4,0xBA,0x0F,0x84,0xF3,0xEE},//0x2B---ch1_bq[2] 
	{0x00,0x7E,0x1B,0x07,0x0F,0x06,0xBF,0x57,0x00,0x7B,0x99,0x7B,0x00,0xF9,0x40,0xA9,0x0F,0x86,0x4B,0x7E},//0x2C---ch1_bq[3] 
	{0x00,0x87,0x38,0x4D,0x0F,0x4D,0x35,0x96,0x00,0x55,0xC7,0x0A,0x00,0xB2,0xCA,0x6A,0x0F,0xA3,0x00,0xA8},//0x2D---ch1_bq[4] 
	{0x00,0x89,0xFB,0xFD,0x0F,0x81,0x9F,0xB6,0x00,0x45,0x9C,0x76,0x00,0x7E,0x60,0x4A,0x0F,0xB0,0x67,0x8D},//0x2E---ch1_bq[5] 
	{0x00,0x99,0x3F,0x11,0x0F,0xCE,0x88,0xA9,0x00,0x25,0xE0,0x51,0x00,0x31,0x77,0x57,0x0F,0xC0,0xE0,0x9D},//0x2F---ch1_bq[6] 
	{0x00,0x7F,0x54,0x6E,0x0F,0x01,0x57,0x24,0x00,0x7F,0x54,0x6E,0x00,0xFE,0xA7,0x12,0x0F,0x81,0x55,0x5B},//0x30---ch2_bq[0] 
	{0x00,0x7F,0x42,0x1F,0x0F,0x03,0x21,0xC3,0x00,0x7D,0xC4,0x90,0x00,0xFC,0xDE,0x3D,0x0F,0x82,0xF9,0x50},//0x31---ch2_bq[0] 
	{0x00,0x7E,0x82,0x6C,0x0F,0x05,0x3B,0x46,0x00,0x7C,0x89,0xA6,0x00,0xFA,0xC4,0xBA,0x0F,0x84,0xF3,0xEE},//0x32---ch2_bq[0] 
	{0x00,0x7E,0x1B,0x07,0x0F,0x06,0xBF,0x57,0x00,0x7B,0x99,0x7B,0x00,0xF9,0x40,0xA9,0x0F,0x86,0x4B,0x7E},//0x33---ch2_bq[0] 
	{0x00,0x87,0x38,0x4D,0x0F,0x4D,0x35,0x96,0x00,0x55,0xC7,0x0A,0x00,0xB2,0xCA,0x6A,0x0F,0xA3,0x00,0xA8},//0x34---ch2_bq[0] 
	{0x00,0x89,0xFB,0xFD,0x0F,0x81,0x9F,0xB6,0x00,0x45,0x9C,0x76,0x00,0x7E,0x60,0x4A,0x0F,0xB0,0x67,0x8D},//0x35---ch2_bq[0] 
	{0x00,0x99,0x3F,0x11,0x0F,0xCE,0x88,0xA9,0x00,0x25,0xE0,0x51,0x00,0x31,0x77,0x57,0x0F,0xC0,0xE0,0x9D},//0x36---ch2_bq[0] 
},
};

static int tas5707_set_master_vol(unsigned char volume){
	int ret = 0;
	LOGI(TAG, "Set tas5707 master volume!\n");
	ret = codec_write_byte(TAS5707_I2C_ADDR, DDX_MASTER_VOLUME, (0xff - volume));
	if(ret < 0)
		LOGE(TAG, "set audio master volume failed!\n");
	return ret;
}

static int tas5707_set_mute(void){
	int ret = 0;
	LOGI(TAG, "Set tas5707 mute!\n");
	ret = codec_write_byte(TAS5707_I2C_ADDR, DDX_MASTER_VOLUME, 0xff);
	if(ret < 0)
		LOGE(TAG, "set audio mute failed!\n");
	return ret;
}

static int tas5707_set_channel_vol(unsigned char L_volume,unsigned char R_volume){
	int ret = 0;
	LOGI(TAG, "Set tas5707 channel volume!\n");
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_CHANNEL1_VOL, (0xff - L_volume));
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_CHANNEL2_VOL, (0xff - R_volume));
	if(ret < 0)
		LOGE(TAG, "set audio channel volume failed!\n");
	return ret;
}

static int tas5707_set_fine_volume(unsigned char value){
	int ret = 0;
	LOGI(TAG, "Set tas5707 fine volume!\n");
	ret = codec_write_byte(TAS5707_I2C_ADDR, DDX_MASTER_FINE_VOLUME_REGISTER, value);
	if(ret < 0)
		LOGE(TAG, "set audio fine volume failed!\n");
	return ret;
}

static int tas5707_set_DRC(void){
	int ret = 0;
	LOGI(TAG, "Set tas5707 DRC parameters!\n");
	unsigned char tas5707_drc_ctl_table[] = {0x00,0x00,0x00,0x01};
	char *ptr;
	ptr = TAS5707_drc1_table[0];
	ret = codec_write(TAS5707_I2C_ADDR, DDX_DRC1_AE, ptr, 8);
	printf("addr[%x] = %x,%x,%x,%x,%x,%x,%x,%x\n",DDX_DRC1_AE,
		*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5),*(ptr+6),*(ptr+7));
	ptr = TAS5707_drc1_table[1];
	ret |= codec_write(TAS5707_I2C_ADDR, DDX_DRC1_AA, ptr, 8);
	printf("addr[%x] = %x,%x,%x,%x,%x,%x,%x,%x\n",DDX_DRC1_AA,
		*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5),*(ptr+6),*(ptr+7));
	ptr = TAS5707_drc1_table[2];
	ret |= codec_write(TAS5707_I2C_ADDR, DDX_DRC1_AD, ptr, 8);
	printf("addr[%x] = %x,%x,%x,%x,%x,%x,%x,%x\n",DDX_DRC1_AD,
		*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5),*(ptr+6),*(ptr+7));

	ptr = tas5707_drc1_tko_table[0];
	ret |= codec_write(TAS5707_I2C_ADDR, DDX_DRC1_T, ptr, 4);
	printf("addr[%x] = %x,%x,%x,%x\n",DDX_DRC1_T,*ptr,*(ptr+1),*(ptr+2),*(ptr+3));
	ptr = tas5707_drc1_tko_table[1];
	ret |= codec_write(TAS5707_I2C_ADDR, DDX_DRC1_K, ptr, 4);
	printf("addr[%x] = %x,%x,%x,%x\n",DDX_DRC1_K,*ptr,*(ptr+1),*(ptr+2),*(ptr+3));
	ptr = tas5707_drc1_tko_table[2];
	ret |= codec_write(TAS5707_I2C_ADDR, DDX_DRC1_O, ptr, 4);
	printf("addr[%x] = %x,%x,%x,%x\n",DDX_DRC1_O,*ptr,*(ptr+1),*(ptr+2),*(ptr+3));
	ret |= codec_write(TAS5707_I2C_ADDR, DDX_DRC_CTL, tas5707_drc_ctl_table, 4);
	if(ret < 0)
		LOGE(TAG, "set audio DRC failed!\n");
	return ret;
}

static int tas5707_set_EQ_mode(unsigned char eq_mode){
	int ret = 0;
	LOGI(TAG,"Set tas5707 EQ parameters!\n");
	if(eq_mode != 0 && eq_mode != 1 && customer_parameter.EQ_enable != 1){
		LOGE(TAG,"Unkonwn EQ mode or EQ disable!\n");
		return -1;
	}
	unsigned char tas5707_eq_ctl_table[] = {0x00,0x00,0x00,0x00};
	int i = 0, j = 0, addr = 0;
	char *ptr;
	for(i = 0;i < 2;i++){
		for(j = 0;j < 7;j++){
			addr = (DDX_CH1_BQ_0 + i*7 + j);
			ptr = tas5707_eq_table[eq_mode][j];
			ret |= codec_write(TAS5707_I2C_ADDR, addr, ptr, 20);
			printf("addr[%x] = %x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x \n",
			addr,*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5),*(ptr+6),
			*(ptr+7),*(ptr+8),*(ptr+9),*(ptr+10),*(ptr+11),*(ptr+12),*(ptr+13),
			*(ptr+14),*(ptr+15),*(ptr+16),*(ptr+17),*(ptr+18),*(ptr+19));
		}
	}
	ret |= codec_write(TAS5707_I2C_ADDR, DDX_BANKSWITCH_AND_EQCTL, tas5707_eq_ctl_table, 4);
	if(ret < 0)
		LOGE(TAG, "set audio EQ failed!\n");
	return ret;
}

static int reset_tas5707_GPIO(void){
	
	*P_PREG_PAD_GPIO4_EN_N &= (~(1<<3));
	*P_PREG_PAD_GPIO4_O &= (~(1<<3));
	Delay_ms(1);
	*P_PREG_PAD_GPIO4_EN_N &= (~(1<<3));
	*P_PREG_PAD_GPIO4_O |= (1<<3);
	Delay_ms(15);
	
	return 0;
}
static int tas5707_init(void){
	int ret = 0;
	unsigned char burst_data[][4]= {
		{0x00,0x01,0x77,0x72},
		{0x01,0x02,0x13,0x45},
	};
	
	LOGI(TAG, "tas5707_init!\n");

//	i2c_probe(TAS5707_I2C_ADDR);
	reset_tas5707_GPIO();
	
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_OSC_TRIM, 0x00);
	Delay_ms(50); //50ms
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_CLOCK_CTL, 0x6c);//0x74 = 512fs; 0x6c = 256fs 
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_SYS_CTL_1, 0xa0);
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_SERIAL_DATA_INTERFACE, 0x03); //0x03: i2s 16bit, 0x05: i2s 24bit
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_BKND_ERR, 0x02);

	ret |= codec_write(TAS5707_I2C_ADDR, DDX_INPUT_MUX, burst_data[0], 4);
	ret |= codec_write(TAS5707_I2C_ADDR, DDX_PWM_MUX, burst_data[1], 4);

	//drc
	if(customer_parameter.DRC_enable == 1){
		ret |= tas5707_set_DRC();
	}
	
	//eq
	if(customer_parameter.EQ_enable == 1){
		ret |= tas5707_set_EQ_mode(1);
	}
	
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_VOLUME_CONFIG, 0x91);
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_SYS_CTL_2, 0x00);
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_START_STOP_PERIOD, 0x95);
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_MODULATION_LIMIT, 0x02);

	ret |= tas5707_set_channel_vol(207, 207);	//set default channel volume
	ret |= tas5707_set_master_vol(0);		//mater voiume mute
	
	ret |= codec_write_byte(TAS5707_I2C_ADDR, DDX_SOFT_MUTE, 0x00);

	return ret;
}

static int tas5707_set_user_parameters(unsigned char *ptr){
	unsigned char *des, *source;
	source = ptr;
	if(*source == 'E' && *(source+1) == 'e' && *(source+2) == 'n' && *(source+3) == '='){
		source += 4;
		customer_parameter.EQ_enable = *source;
		source += 1;
	}
	LOGI(TAG, "User set EQ enable value: %d \n",customer_parameter.EQ_enable);
	
	if(*source == 'D' && *(source+1) == 'e' && *(source+2) == 'n' && *(source+3) == '='){
		source += 4;
		customer_parameter.DRC_enable = *source;
		source += 1;
	}
	LOGI(TAG, "User set DRC enable value: %d \n",customer_parameter.DRC_enable);
	
	if(*source == 'T' && *(source+1) == 'K' && *(source+2) == 'O' && *(source+3) == '='){
		source += 4;
		des = &tas5707_drc1_tko_table[0][0];
		memcpy(des,source,3*4);
		source += 3*4;
	}
	if(*source == 'T' && *(source+1) == 'A' && *(source+2) == 'B' && *(source+3) == '='){
		source += 4;
		des = &TAS5707_drc1_table[0][0];
		memcpy(des,source,3*8);
		source += 3*8;
	}
	if(*source == 'E' && *(source+1) == 'Q' && *(source+2) == 'p' && *(source+3) == '='){
		source += 4;
		des = &tas5707_eq_table[0][0][0];
		memcpy(des,source,2*14*20);
		source += 2*14*20;
	}
	return 0;
}

struct codec_control tas5707 = {
	.init = tas5707_init,
	.set_mute = tas5707_set_mute,
	.set_master_vol = tas5707_set_master_vol,
	.set_channel_vol = tas5707_set_channel_vol,
	.set_subchannel_vol = NULL,
	.set_EQ_mode = tas5707_set_EQ_mode,
	.set_user_parameters = tas5707_set_user_parameters,
	.set_fine_volume = tas5707_set_fine_volume,
};


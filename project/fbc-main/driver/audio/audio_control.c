#include <string.h>
#include <log.h>
#include <i2c.h>
#include <task.h>
#include <listop.h>
#include <inputdata.h>
#include <key_const.h>
#include <input.h>
#include <malloc.h>
#include <cmd.h>
#include <task_priority.h>
#include <XYmemoryMapping.h>

#include "audio_control.h"
#include "spi_flash.h"
#include "spi_regional_division.h"

#include "codecs/tas5707.h"
#include "codecs/tas5711.h"

static LIST_HEAD(audio_input_data_list);
static LIST_HEAD(audio_cmd_list);

static char TAG[] = "audio_control";

int AudioCecControlTaskID = -1;

static unsigned char amplifier[MAX_SOURCE][101] = {

		{0,68,75,82,88,95,105,114,134,144,154, /*0~10*/
		159,161,163,165,168,170,172,174,178,180, /*11~20*/
		181,182,183,184,185,186,187,188,189,190, /*21~30*/
		191,192,192,193,193,194,194,195,195,196, /*31~40*/
		196,197,197,197,198,198,199,199,200,200, /*41~50*/
		200,201,201,202,202,202,203,203,203,204, /*51~60*/
		204,204,205,205,206,206,207,207,208,208, /*61~70*/
		208,209,209,209,209,210,210,210,211,211, /*71~80*/
		211,212,112,212,213,213,213,214,214,215, /*81~90*/
		215,216,216,217,217,217,218,218,219,219}, /*91~100*/

		{0,68,75,82,88,95,105,114,134,144,154, /*0~10*/
		159,161,163,165,168,170,172,174,178,180, /*11~20*/
		181,182,183,184,185,186,187,188,189,190, /*21~30*/
		191,192,192,193,193,194,194,195,195,196, /*31~40*/
		196,197,197,197,198,198,199,199,200,200, /*41~50*/
		200,201,201,202,202,202,203,203,203,204, /*51~60*/
		204,204,205,205,206,206,207,207,208,208, /*61~70*/
		208,209,209,209,209,210,210,210,211,211, /*71~80*/
		211,212,112,212,213,213,213,214,214,215, /*81~90*/
		215,216,216,217,217,217,218,218,219,219}, /*91~100*/

		{0,68,75,82,88,95,105,114,134,144,154, /*0~10*/
		159,161,163,165,168,170,172,174,178,180, /*11~20*/
		181,182,183,184,185,186,187,188,189,190, /*21~30*/
		191,192,192,193,193,194,194,195,195,196, /*31~40*/
		196,197,197,197,198,198,199,199,200,200, /*41~50*/
		200,201,201,202,202,202,203,203,203,204, /*51~60*/
		204,204,205,205,206,206,207,207,208,208, /*61~70*/
		208,209,209,209,209,210,210,210,211,211, /*71~80*/
		211,212,112,212,213,213,213,214,214,215, /*81~90*/
		215,216,216,217,217,217,218,218,219,219}, /*91~100*/

		{0,68,75,82,88,95,105,114,134,144,154, /*0~10*/
		159,161,163,165,168,170,172,174,178,180, /*11~20*/
		181,182,183,184,185,186,187,188,189,190, /*21~30*/
		191,192,192,193,193,194,194,195,195,196, /*31~40*/
		196,197,197,197,198,198,199,199,200,200, /*41~50*/
		200,201,201,202,202,202,203,203,203,204, /*51~60*/
		204,204,205,205,206,206,207,207,208,208, /*61~70*/
		208,209,209,209,209,210,210,210,211,211, /*71~80*/
		211,212,112,212,213,213,213,214,214,215, /*81~90*/
		215,216,216,217,217,217,218,218,219,219}, /*91~100*/
};

static unsigned char fine_volume[4][101] = {
		{0,0,0,0,0,0,0,0,0,0,0,  /*0~10*/
		0,0,0,0,0,0,0,0,0,0, /*11~20*/
		0,0,0,0,0,0,0,0,0,0, /*21~30*/
		0,0,0,0,0,0,0,0,0,0, /*31~40*/
		0,0,0,0,0,0,0,0,0,0, /*41~50*/
		0,0,0,0,0,0,0,0,0,0, /*51~60*/
		0,0,0,0,0,0,0,0,0,0, /*61~70*/
		0,0,0,0,0,0,0,0,0,0, /*71~80*/
		0,0,0,0,0,0,0,0,0,0, /*81~90*/
		0,0,0,0,0,0,0,0,0,0}, /*91~100*/
		
		{0,0,0,0,0,0,0,0,0,0,0,  /*0~10*/
		0,0,0,0,0,0,0,0,0,0, /*11~20*/
		0,0,0,0,0,0,0,0,0,0, /*21~30*/
		0,0,0,0,0,0,0,0,0,0, /*31~40*/
		0,0,0,0,0,0,0,0,0,0, /*41~50*/
		0,0,0,0,0,0,0,0,0,0, /*51~60*/
		0,0,0,0,0,0,0,0,0,0, /*61~70*/
		0,0,0,0,0,0,0,0,0,0, /*71~80*/
		0,0,0,0,0,0,0,0,0,0, /*81~90*/
		0,0,0,0,0,0,0,0,0,0}, /*91~100*/
		
		{0,0,0,0,0,0,0,0,0,0,0,  /*0~10*/
		0,0,0,0,0,0,0,0,0,0, /*11~20*/
		0,0,0,0,0,0,0,0,0,0, /*21~30*/
		0,0,0,0,0,0,0,0,0,0, /*31~40*/
		0,0,0,0,0,0,0,0,0,0, /*41~50*/
		0,0,0,0,0,0,0,0,0,0, /*51~60*/
		0,0,0,0,0,0,0,0,0,0, /*61~70*/
		0,0,0,0,0,0,0,0,0,0, /*71~80*/
		0,0,0,0,0,0,0,0,0,0, /*81~90*/
		0,0,0,0,0,0,0,0,0,0}, /*91~100*/
		
		{0,0,0,0,0,0,0,0,0,0,0,  /*0~10*/
		0,0,0,0,0,0,0,0,0,0, /*11~20*/
		0,0,0,0,0,0,0,0,0,0, /*21~30*/
		0,0,0,0,0,0,0,0,0,0, /*31~40*/
		0,0,0,0,0,0,0,0,0,0, /*41~50*/
		0,0,0,0,0,0,0,0,0,0, /*51~60*/
		0,0,0,0,0,0,0,0,0,0, /*61~70*/
		0,0,0,0,0,0,0,0,0,0, /*71~80*/
		0,0,0,0,0,0,0,0,0,0, /*81~90*/
		0,0,0,0,0,0,0,0,0,0}, /*91~100*/
};

extern struct codec_control tas5707;
extern struct codec_control tas5711;

struct codec_control audio_codec = {
	.init = NULL,
	.set_mute = NULL,
	.set_master_vol = NULL,
	.set_channel_vol = NULL,
	.set_subchannel_vol = NULL,
	.set_EQ_mode = NULL,
	.set_user_parameters = NULL,
	.set_fine_volume = NULL,
};
struct codec_control *codec = &audio_codec;

struct audio_control audio_state = {
	.source = HDMI_SOURCE,
	.mute_state = UNMUTE,
	.master_volume = 207,
	.L_channel_volume = 207,
	.R_channel_volume = 207,
	.sub_channel_volume = 207,
	.L_channel_index = 65,
	.R_channel_index = 65,
	.volume_bar = 12,
	.EQ_mode = WALL_MODE,
	.balance = 50,
	.master_volume_gain = 0,
};

static save_parameter save = NULL;
void register_audio_save(save_parameter func)
{
	save = func;
}


void RegisterCodec(struct codec_control *ptr){
	LOGI(TAG, "Register audio codec driver!\n");

	codec->init = ptr->init;
	codec->set_mute = ptr->set_mute;
	codec->set_master_vol = ptr->set_master_vol;
	codec->set_channel_vol = ptr->set_channel_vol;
	codec->set_subchannel_vol = ptr->set_subchannel_vol;
	codec->set_EQ_mode = ptr->set_EQ_mode;
	codec->set_user_parameters = ptr->set_user_parameters;
	codec->set_fine_volume = ptr->set_fine_volume;
	
	return;
}

int load_spi_data(void){
	unsigned char temp_data[AUDIO_PARAM_AREA_SIZE];
	unsigned char *des1 = &amplifier[0][0];
	unsigned char *des2 = &fine_volume[0][0];
	unsigned char *source = &temp_data[0];

	LOGI(TAG, "Load audio user paramters from spi flash!\n");

	spi_flash_read(get_spi_flash_device(0), AUDIO_PARAM_AREA_BASE_OFFSET, AUDIO_PARAM_AREA_SIZE, &temp_data[0]);

	if(temp_data[0] == 'A' && temp_data[1] == 'M' && temp_data[2] == 'P' && temp_data[3] == '='){
		source += 4;
		memcpy(des1,source,4*101);
		source += 404;
	}

	if(*source == 'F' && *(source + 1) == 'v' && *(source + 2) == 'l' && *(source + 3) == '='){
		source += 4;
		memcpy(des2,source,4*101);
		source += 404;
	}
	
	if(!codec->set_user_parameters){
		LOGE(TAG, "Get codec->set_user_parameters failed!\n");
		return -1;
	}
	(codec->set_user_parameters)(source);
	return 0;
}

void set_audioin_source(unsigned char source){
	 if(source < MAX_SOURCE){
	 	audio_state.source = source;
	 }else{
	 	LOGE(TAG, "Unknown audio source!\n");
	 }
	 return;
}

int set_master_vol(unsigned char volume){
	if(!codec->set_master_vol){
		LOGE(TAG, "Get codec->set_master_vol failed!\n");
		return -1;
	}
	int ret = (codec->set_master_vol)(volume);
	if(!ret){
		audio_state.master_volume = volume;
	}
	return ret;
}

int set_volume_mute(unsigned char mute_state){
	if((!codec->set_mute) || (!codec->set_master_vol)){
		LOGE(TAG, "Get codec->set_mute failed!\n");
		return -1;
	}
	int ret = 0;
	if(mute_state == MUTE){
		ret = (codec->set_mute)();
		if(!ret){
			audio_state.mute_state = MUTE;
		}
	}else if(mute_state == UNMUTE){
		ret = (codec->set_master_vol)(audio_state.master_volume);
		if(!ret){
			audio_state.mute_state = UNMUTE;
		}
	}else{
		LOGE(TAG, "Unknown mute state. 0:mute, 1:unmute!\n");
	}
	return ret;
}

int set_channel_vol(unsigned char L_volume,unsigned char R_volume){
	if(!codec->set_channel_vol){
		LOGE(TAG, "Get codec->set_channel_vol failed!\n");
		return -1;
	}

	int ret = (codec->set_channel_vol)(L_volume,R_volume);
	if(!ret){
		audio_state.L_channel_volume = L_volume;
		audio_state.R_channel_volume = R_volume;
	}
	return ret;
}

int set_subchannel_vol(unsigned char sub_volume){
	if(!codec->set_subchannel_vol){
		LOGE(TAG, "Get set_subchannel_vol failed!\n");
		return -1;
	}

	int ret = (codec->set_subchannel_vol)(sub_volume);
	if(!ret){
		audio_state.sub_channel_volume = sub_volume;
	}
	return ret;
}

int set_EQ_mode(unsigned char eq_mode){
	if(!codec->set_EQ_mode){
		LOGE(TAG, "Get set_EQ_mode failed!\n");
		return -1;
	}
	int ret = (codec->set_EQ_mode)(eq_mode);
	if(!ret){
		audio_state.EQ_mode = eq_mode;
	}
	return ret;
}

int set_channel_vol_index(unsigned char L_volume_index,unsigned char R_volume_index){
	if(L_volume_index > 100 || R_volume_index > 100 ){
		LOGE(TAG, "It is invalid index value: L = %u, R = %u !\n", L_volume_index, R_volume_index);
		return -1;
	}
	unsigned char L_vol = amplifier[audio_state.source][L_volume_index];
	unsigned char R_vol = amplifier[audio_state.source][R_volume_index];
	int ret = set_channel_vol(L_vol,R_vol);
	if(!ret){
		audio_state.L_channel_index = L_volume_index;
		audio_state.R_channel_index = R_volume_index;
	}
	return ret;
}

static int CalculateBalanceVol(unsigned char bar_value, unsigned char balance_val,
								unsigned char *left_index, unsigned char *right_index) {

 	int tmp = (int)bar_value;
	if (balance_val > 100 || bar_value > 100) {
		return -1;
	}

	if (balance_val == 50) {
		*left_index = bar_value;
		*right_index = bar_value;
	} else if (balance_val < 50) {
		*right_index = (unsigned char)(tmp * balance_val / 50);
		*left_index = bar_value;
	} else if (balance_val > 50) {
		*right_index = bar_value;
		*left_index = (unsigned char)(tmp * (100 - balance_val) / 50);
	}
	return 0;
}

int set_balance(unsigned char balance){
	if(balance > 100){
		LOGE(TAG, "It is invalid balance value: Balance = %u\n", balance);
		return -1;
	}

	unsigned char L_channel_index = 0;
	unsigned char R_channel_index = 0;
	int ret = CalculateBalanceVol(audio_state.volume_bar, balance, &L_channel_index, &R_channel_index);
	if(!ret){
		set_channel_vol_index(L_channel_index, R_channel_index);
		audio_state.balance = balance;
	}
	return 0;
}
int set_volume_bar(unsigned char volume_bar){

	unsigned char L_channel_index = 0;
	unsigned char R_channel_index = 0;

	int ret = CalculateBalanceVol(volume_bar, audio_state.balance, &L_channel_index, &R_channel_index);
	if(!ret){
		set_channel_vol_index(L_channel_index, R_channel_index);
		audio_state.volume_bar = volume_bar;
	}
	if(!codec->set_fine_volume){
		LOGE(TAG, "Get codec->set_fine_volume failed!\n");
		return ret;
	}
	codec->set_fine_volume(fine_volume[audio_state.source][volume_bar]);
	return ret;
}
int set_master_vol_gain(char gain){

	int tmp = (int)audio_state.master_volume;
	tmp += gain;
	if(tmp > 255 || tmp < 0){
		return -1;
	}
	set_master_vol((unsigned char)tmp);
	return 0;
}

unsigned char get_audioin_source(void){
	return audio_state.source;
}
unsigned char get_master_vol(void){
	return audio_state.master_volume;
}
void get_channel_vol(unsigned char *L_volume, unsigned char *R_volume){
	*L_volume = audio_state.L_channel_volume;
	*R_volume = audio_state.R_channel_volume;
	return;
}
unsigned char get_subchannel_vol(void){
	return audio_state.sub_channel_volume;
}
void get_channel_vol_index(unsigned char *L_volume_index, unsigned char *R_volume_index){
	*L_volume_index = audio_state.L_channel_index;
	*R_volume_index = audio_state.R_channel_index;
	return;
}
unsigned char get_mute_state(void){
	return audio_state.mute_state;
}
unsigned char get_EQ_mode(void){
	return audio_state.EQ_mode;
}
unsigned char get_balance(void){
	return audio_state.balance;
}
unsigned char get_volume_bar(void){
	return audio_state.volume_bar;
}

char get_master_vol_gain(void){
	return audio_state.master_volume_gain;
}

int audio_codec_init(void){

	int ret = 0;

	if(codec->init != NULL){
		LOGI(TAG, "External audio codec driver is registed in system!\n");
	}else if((CODEC_NAME == TAS5707)){
		RegisterCodec(&tas5707);
		LOGI(TAG, "Internal audio codec driver Tas5707 is registed in system!\n");
	}else if(CODEC_NAME == TAS5711){
		RegisterCodec(&tas5711);
		LOGI(TAG, "Internal audio codec driver Tas5711 is registed in system!\n");
	}else{
		LOGE(TAG, "NO audio codec driver is registed in system!\n");
	}

	load_spi_data();

	if(!codec->init){
		LOGE(TAG, "Get codec->init failed!\n");
		return -1;
	}

	ret = (codec->init)();
	if(ret){
		LOGE(TAG, "audio codec init failed!\n");
		return ret;
	}

	set_channel_vol_index(audio_state.L_channel_index,audio_state.R_channel_index);
	set_master_vol(audio_state.master_volume);

	return ret;
}

static int audio_key_process(int key){

	LOGD(TAG, "Audio Key Process %d\n", key);

	switch(key){
		case AMLKEY_MUTE:
			unsigned char mute_state = (audio_state.mute_state+1)%2;
			set_volume_mute(mute_state);
			LOGI(TAG, "set remote mute flag : %d!\n",mute_state);
			break;
		case AMLKEY_VOL_MINUS:
			if(audio_state.volume_bar > 0){
				audio_state.volume_bar--;
				set_volume_bar(audio_state.volume_bar);
			}
			LOGI(TAG, "set remote volume minus, volume: %d!\n",audio_state.volume_bar);
			break;
		case AMLKEY_VOL_PLUS:
			if(audio_state.volume_bar < 100){
				audio_state.volume_bar++;
				set_volume_bar(audio_state.volume_bar);
			}
			LOGI(TAG, "set remote volume plus, volume: %d!\n",audio_state.volume_bar);
			break;
		default:
			LOGE(TAG, "Unknown Key command for audio!\n");
			break;
	}
	return 0;
}

static int Audio_Control_NEC_Task_Handler(int task_id, void *param){
	int cmd;
	list_t *plist = list_dequeue(&audio_input_data_list);

	LOGI(TAG,"run audio input Data task %d from input 0x%x\n", task_id, plist);

	if (plist) {
		INPUT_LIST *input_list = list_entry(plist, INPUT_LIST, list);
		if (input_list){
			cmd = input_list->input_data.data;
			free(input_list);
			audio_key_process(cmd);
		}
	}
	return 0;
}

static int audio_key_filter(int key){
	if(key == AMLKEY_MUTE || key == AMLKEY_VOL_MINUS || key == AMLKEY_VOL_PLUS){
		return 1;
	}
	return 0;
}

int init_audio_nec_control_task(void){

	LOGI(TAG, "init audio nec control task!\n");

	int AudioNecControlTaskID = -1;
	AudioNecControlTaskID = RegisterTask(Audio_Control_NEC_Task_Handler, NULL, 0, TASK_PRIORITY_AUDIO_NEC_CONTROL);
	if(AudioNecControlTaskID < 0){
		LOGE(TAG,"Register Audio nec control Task fail!\n");
		return AudioNecControlTaskID;
	}

	int AudioInputID = -1;
	AudioInputID = RegisterInput(&audio_input_data_list, AudioNecControlTaskID,
										INPUT_REMOTE|INPUT_SARADC, audio_key_filter);
	if(AudioInputID < 0){
		LOGE(TAG,"Register Audio Input fail!\n");
		return AudioInputID;
	}
	return 0;
}

unsigned int audio_handle_cmd(unsigned char *s, int *rets){
	if(s == NULL){
		return -1;
	}

	switch(*s){
		case AUDIO_CMD_SET_SOURCE:
			unsigned char source = (unsigned char)GetParam(s, 0);
			set_audioin_source(source);
			break;
		case AUDIO_CMD_SET_MASTER_VOLUME:
			unsigned char master_volume = (unsigned char)GetParam(s, 0);
			set_master_vol(master_volume);
			break;
		case AUDIO_CMD_SET_CHANNEL_VOLUME:
			unsigned char L_volume = (unsigned char)GetParam(s, 0);
			unsigned char R_volume = (unsigned char)GetParam(s, 1);
			set_channel_vol(L_volume, R_volume);
			break;
		case AUDIO_CMD_SET_SUBCHANNEL_VOLUME:
			unsigned char sub = (unsigned char)GetParam(s, 0);
			set_subchannel_vol(sub);
			break;
		case AUDIO_CMD_SET_MASTER_VOLUME_GAIN:
			char gain = (char)GetParam(s, 0);
			set_master_vol_gain(gain);
			break;
		case AUDIO_CMD_SET_CHANNEL_VOLUME_INDEX:
			unsigned char L_vol_index = (unsigned char)GetParam(s, 0);
			unsigned char R_vol_index = (unsigned char)GetParam(s, 1);
			set_channel_vol_index(L_vol_index, R_vol_index);
			break;
		case AUDIO_CMD_SET_VOLUME_BAR:
			unsigned char volume_bar = (unsigned char)GetParam(s, 0);
			set_volume_bar(volume_bar);
			break;
		case AUDIO_CMD_SET_MUTE:
			unsigned char mute = (unsigned char)GetParam(s, 0);
			set_volume_mute(mute);
			break;
		case AUDIO_CMD_SET_EQ_MODE:
			unsigned char EQ_mode = (unsigned char)GetParam(s, 0);
			set_EQ_mode(EQ_mode);
			break;
		case AUDIO_CMD_SET_BALANCE:
			unsigned char balance = (unsigned char)GetParam(s, 0);
			set_balance(balance);
			break;
		case AUDIO_CMD_GET_SOURCE:
			*rets = get_audioin_source();
			break;
		case AUDIO_CMD_GET_MASTER_VOLUME:
			*rets = get_master_vol();
			break;
		case AUDIO_CMD_GET_CHANNEL_VOLUME:
			unsigned char L_vol = 0;
			unsigned char R_vol = 0;
			get_channel_vol(&L_vol,&R_vol);
			*rets = (int)L_vol;
			*(rets + 1) = (int)R_vol;
			break;
		case AUDIO_CMD_GET_SUBCHANNEL_VOLUME:
			*rets = (int)get_subchannel_vol();
			break;
		case AUDIO_CMD_GET_MASTER_VOLUME_GAIN:
			*rets = (int)get_master_vol_gain();
			break;
		case AUDIO_CMD_GET_CHANNEL_VOLUME_INDEX:
			unsigned char L_index = 0;
			unsigned char R_index = 0;
			get_channel_vol_index(&L_index,&R_index);
			*rets = (int)L_index;
			*(rets + 1) = (int)R_index;
			break;
		case AUDIO_CMD_GET_VOLUME_BAR:
			*rets = (int)get_volume_bar();
			break;
		case AUDIO_CMD_GET_MUTE:
			*rets = (int)get_mute_state();
			break;
		case AUDIO_CMD_GET_EQ_MODE:
			*rets = (int)get_EQ_mode();
			break;
		case AUDIO_CMD_GET_BALANCE:
			*rets = (int)get_balance();
			break;
		default :
			break;
	}
	if(NULL != save){
		save(s);
	}

	return 0;
}

static int Audio_Control_CEC_Task_Handler(int task_id, void *param){

	list_t *plist = list_dequeue(&audio_cmd_list);
	if(plist != NULL)
	{
		CMD_LIST *clist = list_entry(plist, CMD_LIST, list);
		if(clist != NULL)
		{
			unsigned char *cmd = (unsigned char *)(clist->cmd_data.data);
			if(cmd != NULL)
			{
				int rcmd_len = RET_LEN(cmd);
				if(rcmd_len > 0)
				{
					void *params = (void *)malloc(rcmd_len);
					audio_handle_cmd(cmd, (int *)params);
					SendReturn(AudioCecControlTaskID, clist->cmd_data.cmd_owner, *cmd, (int *)params);
					free(params);
					params = NULL;
				}
				else
				{
					audio_handle_cmd(cmd, NULL);
				}
			}
			freeCmdList(clist);
		}
	}
	return 0;
}

static int audio_cmd_check(int cmd){
	switch(cmd)
	{
		case AUDIO_CMD_SET_SOURCE:
		case AUDIO_CMD_SET_MASTER_VOLUME:
		case AUDIO_CMD_SET_CHANNEL_VOLUME:
		case AUDIO_CMD_SET_SUBCHANNEL_VOLUME:
		case AUDIO_CMD_SET_MASTER_VOLUME_GAIN:
		case AUDIO_CMD_SET_CHANNEL_VOLUME_INDEX:
		case AUDIO_CMD_SET_VOLUME_BAR:
		case AUDIO_CMD_SET_MUTE:
		case AUDIO_CMD_SET_EQ_MODE:
		case AUDIO_CMD_SET_BALANCE:
		case AUDIO_CMD_GET_SOURCE:
		case AUDIO_CMD_GET_MASTER_VOLUME:
		case AUDIO_CMD_GET_CHANNEL_VOLUME:
		case AUDIO_CMD_GET_SUBCHANNEL_VOLUME:
		case AUDIO_CMD_GET_MASTER_VOLUME_GAIN:
		case AUDIO_CMD_GET_CHANNEL_VOLUME_INDEX:
		case AUDIO_CMD_GET_VOLUME_BAR:
		case AUDIO_CMD_GET_MUTE:
		case AUDIO_CMD_GET_EQ_MODE:
		case AUDIO_CMD_GET_BALANCE:
			return 1;
		default :
			break;
	}
	return 0;
}

int init_audio_cec_control_task(void){

	LOGI(TAG, "init audio cec control task!\n");

	AudioCecControlTaskID = RegisterTask(Audio_Control_CEC_Task_Handler,
										NULL, 0, TASK_PRIORITY_AUDIO_CEC_CONTROL);
	if(AudioCecControlTaskID < 0){
		LOGE(TAG,"Register Audio CEC control Task fail!\n");
		return AudioCecControlTaskID;
	}

	int AudioCmdID = -1;
	AudioCmdID = RegisterCmd(&audio_cmd_list, AudioCecControlTaskID, INPUT_CEC | INPUT_UART_HOST ,
										audio_cmd_check, audio_handle_cmd);
	if(AudioCmdID < 0){
		LOGE(TAG,"Register Audio cmd fail!\n");
		return AudioCmdID;
	}
	return 0;
}


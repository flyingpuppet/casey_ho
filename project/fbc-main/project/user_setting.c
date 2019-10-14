#include <user_setting.h>
#include <task_priority.h>
#include <string.h>
#include <malloc.h>
#include <spi_flash.h>
#include <task.h>
#include <timer.h>
#include <cmd.h>
#include <vpp_api.h>
#include <inputdata.h>
#include <XYmemoryMapping.h>
#include <gpio.h>
#include <project.h>
#include <reboot.h>


#define HDCP_KEY_PARA 0x5A




struct system_setting {
    unsigned char sleep_time;
    unsigned char power_on_mode;//0 direct suspend, 1 direct power on
    unsigned char watch_dog;
};

struct vpp_switch {
    /*VPU_MODULE_VPU,       //vpu uint
    VPU_MODULE_TIMGEN,
    VPU_MODULE_PATGEN,
    VPU_MODULE_GAMMA,
    VPU_MODULE_WB,      //WhiteBalance
    VPU_MODULE_BC,      //Brightness&Contrast
    VPU_MODULE_BCRGB,   //RGB Brightness&Contrast
    VPU_MODULE_CM2,
    VPU_MODULE_CSC1,
    VPU_MODULE_DNLP,
    VPU_MODULE_CSC0,
    VPU_MODULE_OSD,
    VPU_MODULE_BLEND,
    VPU_MODULE_DEMURE,  //15
    VPU_MODULE_OUTPUT,  //LVDS/VX1 output
    VPU_MODULE_OSDDEC,  //OSD decoder*/
    //unsigned char vpu_enable;
    //unsigned char timgen_enable;
    //unsigned char patgen_enable;
    unsigned char gamma_enable;
    unsigned char wb_enable;
    //unsigned char bc_enable;
    //unsigned char bcrgb_enable;
    unsigned char cm2_enable;
    //unsigned char csc1_enable;
    unsigned char dnlp_enable;
    //unsigned char csc0_enable;
    //unsigned char osd_enable;
    //unsigned char blend_enable;
    //unsigned char demura_enable;
    //unsigned char output_enable;
    //unsigned char osddec_enable;
};

struct systems {
    unsigned version;
    unsigned project_id;
    char device_id[128];
    char factory_sn[20];
    struct system_setting system;
    struct vpp_switch vpp;
};

struct user_setting {
    unsigned char change_flag;
    struct systems * system;
    struct audio_control * audio;
    vpu_fac_pq_t * pq;
};

struct user_setting_save {
    struct systems system;
    struct audio_control audio;
    vpu_fac_pq_t pq;
};

struct wb_setting {
    unsigned adjusted;
    vpu_colortemp_table_t cold;
    vpu_colortemp_table_t warm;
    vpu_colortemp_table_t standard;
    vpu_colortemp_table_t user;
};


extern vpu_fac_pq_t vpu_fac_pq_setting;
extern struct audio_control audio_state;
static struct systems cur_system;
extern vpu_colortemp_table_t colortemp_table[COLOR_TEMP_MAX];
extern vpu_picmod_table_t picmod_table[PICMOD_MAX];
static void load_user_wb_setting();




static const struct audio_control audio_state_def = {
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
static const vpu_fac_pq_t pq_def = {
    128,128,128,128,128,
    {128,128,128,128,128,128,127,127,127},
    COLOR_TEMP_STD,
    PICMOD_STD,
    5,
};
static const struct systems system_default = {
    .version = 0x00000001,
#ifdef PROJECT_ID
    .project_id = PROJECT_ID,
#else
    .project_id = 0,
#endif
#ifdef DEVICE_ID
    .device_id = DEVICE_ID,
#else
    .device_id = "test12345678",
#endif
    .system = {
        .sleep_time = 0,
        .power_on_mode = USER_POWER_ON_MODE,
        .watch_dog = 0,
    },
    .vpp = {
        .gamma_enable = 1,
        .wb_enable = 1,
        .cm2_enable = 1,
        .dnlp_enable = 1,
    },
};

static const vpu_picmod_table_t pic_table_def[PICMOD_MAX]= {
    {PICMOD_STD,128,128,128},
    {PICMOD_BRI,138,138,138},
    {PICMOD_SOFT,118,118,130},
    {PICMOD_MOVIE,110,110,130},
    {PICMOD_USER,128,128,128},
};

static struct wb_setting g_wb_setting = {0};
static struct user_setting g_user_setting = {0};
static struct user_setting_save g_user_setting_save = {0};

int setting_task_id = -1;
#ifndef FBC_USER_WITHOUT_SAVE
int save_task_id = -1;
#endif
static LIST_HEAD(setting_list);


extern vpu_config_t vpu_config_table;
extern unsigned int pq_data_mapping(unsigned int wb_gain, unsigned int ui_range,unsigned int max_range, int enable);



unsigned int write_user_setting(unsigned char *s)
{
    switch(CmdID(s)) {
    case VPU_CMD_NATURE_LIGHT_EN:
    case VPU_CMD_BACKLIGHT_EN:
    case VPU_CMD_BRIGHTNESS:
    case VPU_CMD_CONTRAST:
    case VPU_CMD_BACKLIGHT:
    case VPU_CMD_SATURATION:
    case VPU_CMD_DYNAMIC_CONTRAST:
    case VPU_CMD_PICTURE_MODE:
    case VPU_CMD_PATTERN_EN:
    case VPU_CMD_PATTEN_SEL:
    case VPU_CMD_USER_GAMMA:
    case VPU_CMD_COLOR_TEMPERATURE_DEF:
    case VPU_CMD_BRIGHTNESS_DEF:
    case VPU_CMD_CONTRAST_DEF:
    case VPU_CMD_COLOR_DEF:
    case VPU_CMD_HUE_DEF:
    case VPU_CMD_BACKLIGHT_DEF:
    case VPU_CMD_AUTO_LUMA_EN:
    //case VPU_CMD_AUTO_ELEC_MODE:
        //wb
    case VPU_CMD_RED_GAIN_DEF:
    case VPU_CMD_GREEN_GAIN_DEF:
    case VPU_CMD_BLUE_GAIN_DEF:
    case VPU_CMD_PRE_RED_OFFSET_DEF:
    case VPU_CMD_PRE_GREEN_OFFSET_DEF:
    case VPU_CMD_PRE_BLUE_OFFSET_DEF:
    case VPU_CMD_POST_RED_OFFSET_DEF:
    case VPU_CMD_POST_GREEN_OFFSET_DEF:
    case VPU_CMD_POST_BLUE_OFFSET_DEF:
    case VPU_CMD_WB:
        //audio
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
        g_user_setting.change_flag = 1;
        break;
    case VPU_CMD_ENABLE:
        int * params = GetParams(s);
        switch(params[0]) {
        case VPU_MODULE_GAMMA:
            cur_system.vpp.gamma_enable = params[1];
            break;
        case VPU_MODULE_WB:
            cur_system.vpp.wb_enable = params[1];
            break;
        case VPU_MODULE_CM2:
            cur_system.vpp.cm2_enable = params[1];
            break;
        case VPU_MODULE_DNLP:
            cur_system.vpp.dnlp_enable = params[1];
            break;
        default:
            break;
        }
        g_user_setting.change_flag = 1;
        break;
    default:
        break;
    }

    return 0;
}

unsigned char read_user_setting(unsigned char *s, int * returns)
{
    int * params = GetParams(s);
    if(params == NULL) {
        return 1;
    }
    switch(CmdID(s)) {
    case (VPU_CMD_ENABLE | VPU_CMD_READ):

        switch(params[0]) {
        case VPU_MODULE_GAMMA:
            returns[0] = cur_system.vpp.gamma_enable;
            break;
        case VPU_MODULE_WB:
            returns[0] = cur_system.vpp.wb_enable;
            break;
        case VPU_MODULE_CM2:
            returns[0] = cur_system.vpp.cm2_enable;
            break;
        case VPU_MODULE_DNLP:
            returns[0] = cur_system.vpp.dnlp_enable;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    free(params);
    return 0;
}

unsigned read_project_id()
{
    return cur_system.project_id;
}

int write_project_id(unsigned val)
{
    cur_system.project_id = val;
    g_user_setting.change_flag = 1;
    return 0;
}

char * read_device_id()
{
    return cur_system.device_id;
}

int write_device_id( char * device)
{
    strcpy(cur_system.device_id, device);
    g_user_setting.change_flag = 1;
    return 0;
}

char * read_factory_sn()
{
    return cur_system.factory_sn;
}

int write_factory_sn( char * pSn)
{
    strcpy(cur_system.factory_sn, pSn);
	printf("AAAA %s\n",cur_system.factory_sn);
    g_user_setting.change_flag = 1;
    return 0;
}
unsigned char read_power_on_mode()
{
	return cur_system.system.power_on_mode;
}
int write_power_on_mode(unsigned char mode)
{
	cur_system.system.power_on_mode = mode;
	g_user_setting.change_flag = 1;
	return 0;
}



char * read_HDCP_KEY()
{
    char * key = calloc(USER_HDCPKEY_SIZE, 1);
    if(key <= 0) {
        return NULL;
    }
    if(spi_flash_read(get_spi_flash_device(0),USER_HDCPKEY,USER_HDCPKEY_SIZE,(void *)key)<=0) {
        printf("read_HDCP_KEY£¬spi read failed!\n");
        free(key);
        return NULL;
    }
    for(int i=0; i<USER_HDCPKEY_SIZE; i++) {
        key[i] = key[i] ^ HDCP_KEY_PARA;
    }
    return key;
}

int write_HDCP_KEY(const char * key, int len)
{
    char * p = (char *)calloc(USER_HDCPKEY_SIZE, 1);
    int length = len>USER_HDCPKEY_SIZE? USER_HDCPKEY_SIZE:len;
    for(int i=0; i<length; i++) {
        p[i] = key[i] ^ HDCP_KEY_PARA;
    }
#ifdef CONFIG_RANDOM_WRITE
    int ret = spi_flash_random_write(get_spi_flash_device(0), USER_HDCPKEY, USER_HDCPKEY_SIZE, (void *)p);
    free(p);
    return ret;
#else
    free(p);
    return 0;
#endif
}

void d2d3_select(int mode)
{
    *P_PREG_PAD_GPIO3_EN_N &= (~(1<<2));

    if(mode)
        *P_PREG_PAD_GPIO3_O |= (1<<2);
    else
        *P_PREG_PAD_GPIO3_O &= (~(1<<2));
}


int write_wb_setting(vpu_colortemp_t mode, white_balance_setting_t * val)
{
    g_wb_setting.adjusted = 1;
    switch(mode) {
    case COLOR_TEMP_COLD:
        g_wb_setting.cold.color_temp = COLOR_TEMP_COLD;
        g_wb_setting.cold.wb_param.gain_r = val->r_gain;
        g_wb_setting.cold.wb_param.gain_g = val->g_gain;
        g_wb_setting.cold.wb_param.gain_b = val->b_gain;
        g_wb_setting.cold.wb_param.pre_offset_r = val->r_offset;
        g_wb_setting.cold.wb_param.pre_offset_g = val->g_offset;
        g_wb_setting.cold.wb_param.pre_offset_b = val->b_offset;
        break;
    case COLOR_TEMP_WARM:
        g_wb_setting.warm.color_temp = COLOR_TEMP_WARM;
        g_wb_setting.warm.wb_param.gain_r = val->r_gain;
        g_wb_setting.warm.wb_param.gain_g = val->g_gain;
        g_wb_setting.warm.wb_param.gain_b = val->b_gain;
        g_wb_setting.warm.wb_param.pre_offset_r = val->r_offset;
        g_wb_setting.warm.wb_param.pre_offset_g = val->g_offset;
        g_wb_setting.warm.wb_param.pre_offset_b = val->b_offset;
        break;
    case COLOR_TEMP_STD:
        g_wb_setting.standard.color_temp = COLOR_TEMP_STD;
        g_wb_setting.standard.wb_param.gain_r = val->r_gain;
        g_wb_setting.standard.wb_param.gain_g = val->g_gain;
        g_wb_setting.standard.wb_param.gain_b = val->b_gain;
        g_wb_setting.standard.wb_param.pre_offset_r = val->r_offset;
        g_wb_setting.standard.wb_param.pre_offset_g = val->g_offset;
        g_wb_setting.standard.wb_param.pre_offset_b = val->b_offset;
        break;
    case COLOR_TEMP_USER:
        g_wb_setting.user.color_temp = COLOR_TEMP_USER;
        g_wb_setting.user.wb_param.gain_r = val->r_gain;
        g_wb_setting.user.wb_param.gain_g = val->g_gain;
        g_wb_setting.user.wb_param.gain_b = val->b_gain;
        g_wb_setting.user.wb_param.pre_offset_r = val->r_offset;
        g_wb_setting.user.wb_param.pre_offset_g = val->g_offset;
        g_wb_setting.user.wb_param.pre_offset_b = val->b_offset;
        break;
    default:
        break;
    }
    load_user_wb_setting();
    return write_wb_setting_flash();
    //return 0;
}

white_balance_setting_t * read_wb_setting(vpu_colortemp_t mode)
{
    white_balance_setting_t * val = (white_balance_setting_t *)malloc(sizeof(white_balance_setting_t));
    switch(mode) {
    case COLOR_TEMP_COLD:
        val->r_gain = g_wb_setting.cold.wb_param.gain_r;
        val->g_gain = g_wb_setting.cold.wb_param.gain_g;
        val->b_gain = g_wb_setting.cold.wb_param.gain_b;
        val->r_offset = g_wb_setting.cold.wb_param.pre_offset_r;
        val->g_offset = g_wb_setting.cold.wb_param.pre_offset_g;
        val->b_offset = g_wb_setting.cold.wb_param.pre_offset_b;
        break;
    case COLOR_TEMP_WARM:
        val->r_gain = g_wb_setting.warm.wb_param.gain_r;
        val->g_gain = g_wb_setting.warm.wb_param.gain_g;
        val->b_gain = g_wb_setting.warm.wb_param.gain_b;
        val->r_offset = g_wb_setting.warm.wb_param.pre_offset_r;
        val->g_offset = g_wb_setting.warm.wb_param.pre_offset_g;
        val->b_offset = g_wb_setting.warm.wb_param.pre_offset_b;
        break;
    case COLOR_TEMP_STD:
        val->r_gain = g_wb_setting.standard.wb_param.gain_r;
        val->g_gain = g_wb_setting.standard.wb_param.gain_g;
        val->b_gain = g_wb_setting.standard.wb_param.gain_b;
        val->r_offset = g_wb_setting.standard.wb_param.pre_offset_r;
        val->g_offset = g_wb_setting.standard.wb_param.pre_offset_g;
        val->b_offset = g_wb_setting.standard.wb_param.pre_offset_b;
        break;
    case COLOR_TEMP_USER:
        val->r_gain = g_wb_setting.user.wb_param.gain_r;
        val->g_gain = g_wb_setting.user.wb_param.gain_g;
        val->b_gain = g_wb_setting.user.wb_param.gain_b;
        val->r_offset = g_wb_setting.user.wb_param.pre_offset_r;
        val->g_offset = g_wb_setting.user.wb_param.pre_offset_g;
        val->b_offset = g_wb_setting.user.wb_param.pre_offset_b;
        break;
    default:
        free(val);
        val = NULL;
        break;
    }
    return val;
}

int write_wb_setting_flash()
{
#ifdef CONFIG_RANDOM_WRITE
    return spi_flash_random_write(get_spi_flash_device(0), USER_WB_SETTING_START, sizeof(struct wb_setting), &g_wb_setting);
#else
    return 0;
#endif
}

int write_picmod_setting(vpu_picmod_t mode, vpu_picmod_table_t * val)
{
    if(val == NULL) return -1;
    memcpy((void *)&picmod_table[mode], (void *)val, sizeof(vpu_picmod_table_t));
    return spi_flash_random_write(get_spi_flash_device(0), USER_PIC_SETTING_START, PICMOD_MAX*sizeof(vpu_picmod_table_t), &picmod_table);
}

vpu_picmod_table_t * read_picmod_setting(vpu_picmod_t mode)
{
    return &picmod_table[mode];
}


int load_default_user_setting()
{
    memcpy((void *)&g_user_setting_save.system, (void *)&system_default, sizeof(struct systems));
    memcpy((void *)&g_user_setting_save.pq, (void *)&pq_def, sizeof(vpu_fac_pq_t));
    memcpy((void *)&g_user_setting_save.audio, (void *)&audio_state_def, sizeof(struct audio_control));
#ifdef CONFIG_RANDOM_WRITE
    printf("user start addr is 0x%08x, size is 0x%08x\n",USER_SETTING_START, sizeof(struct user_setting_save));
    return spi_flash_random_write(get_spi_flash_device(0), USER_SETTING_START, sizeof(struct user_setting_save), &g_user_setting_save);
#else
    return 0;
#endif
}



int load_default_wb_setting()
{
  if (WB_DATA_FROM_DB) {
    g_wb_setting.cold.color_temp = COLOR_TEMP_COLD;
    g_wb_setting.cold.wb_param.gain_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].gain_r,256,2048,0);
    g_wb_setting.cold.wb_param.gain_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].gain_g,256,2048,0);
    g_wb_setting.cold.wb_param.gain_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].gain_b,256,2048,0);
    g_wb_setting.cold.wb_param.pre_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].pre_offset_r,256,2048,1);
    g_wb_setting.cold.wb_param.pre_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].pre_offset_g,256,2048,1);
    g_wb_setting.cold.wb_param.pre_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].pre_offset_b,256,2048,1);
    g_wb_setting.cold.wb_param.post_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].post_offset_r,256,2048,1);
    g_wb_setting.cold.wb_param.post_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].post_offset_g,256,2048,1);
    g_wb_setting.cold.wb_param.post_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].post_offset_b,256,2048,1);

    g_wb_setting.standard.color_temp = COLOR_TEMP_STD;
    g_wb_setting.standard.wb_param.gain_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_r,256,2048,0);
    g_wb_setting.standard.wb_param.gain_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_g,256,2048,0);
    g_wb_setting.standard.wb_param.gain_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_b,256,2048,0);
    g_wb_setting.standard.wb_param.pre_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_r,256,2048,1);
    g_wb_setting.standard.wb_param.pre_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_g,256,2048,1);
    g_wb_setting.standard.wb_param.pre_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_b,256,2048,1);
    g_wb_setting.standard.wb_param.post_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_r,256,2048,1);
    g_wb_setting.standard.wb_param.post_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_g,256,2048,1);
    g_wb_setting.standard.wb_param.post_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_b,256,2048,1);

    g_wb_setting.warm.color_temp = COLOR_TEMP_WARM;
    g_wb_setting.warm.wb_param.gain_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].gain_r,256,2048,0);
    g_wb_setting.warm.wb_param.gain_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].gain_g,256,2048,0);
    g_wb_setting.warm.wb_param.gain_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].gain_b,256,2048,0);
    g_wb_setting.warm.wb_param.pre_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].pre_offset_r,256,2048,1);
    g_wb_setting.warm.wb_param.pre_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].pre_offset_g,256,2048,1);
    g_wb_setting.warm.wb_param.pre_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].pre_offset_b,256,2048,1);
    g_wb_setting.warm.wb_param.post_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].post_offset_r,256,2048,1);
    g_wb_setting.warm.wb_param.post_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].post_offset_g,256,2048,1);
    g_wb_setting.warm.wb_param.post_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].post_offset_b,256,2048,1);

    g_wb_setting.user.color_temp = COLOR_TEMP_USER;
    g_wb_setting.user.wb_param.gain_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_r,256,2048,0);
    g_wb_setting.user.wb_param.gain_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_g,256,2048,0);
    g_wb_setting.user.wb_param.gain_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_b,256,2048,0);
    g_wb_setting.user.wb_param.pre_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_r,256,2048,1);
    g_wb_setting.user.wb_param.pre_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_g,256,2048,1);
    g_wb_setting.user.wb_param.pre_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_b,256,2048,1);
    g_wb_setting.user.wb_param.post_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_r,256,2048,1);
    g_wb_setting.user.wb_param.post_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_g,256,2048,1);
    g_wb_setting.user.wb_param.post_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_b,256,2048,1);
  } else {
	  g_wb_setting.cold.color_temp = COLOR_TEMP_COLD;
	  g_wb_setting.cold.wb_param.gain_r = colortemp_table[COLOR_TEMP_COLD].wb_param.gain_r;
	  g_wb_setting.cold.wb_param.gain_g = colortemp_table[COLOR_TEMP_COLD].wb_param.gain_g;
	  g_wb_setting.cold.wb_param.gain_b = colortemp_table[COLOR_TEMP_COLD].wb_param.gain_b;
	  g_wb_setting.cold.wb_param.pre_offset_r = colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_r;
	  g_wb_setting.cold.wb_param.pre_offset_g = colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_g;
	  g_wb_setting.cold.wb_param.pre_offset_b = colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_b;
	  g_wb_setting.cold.wb_param.post_offset_r = colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_r;
	  g_wb_setting.cold.wb_param.post_offset_g = colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_g;
	  g_wb_setting.cold.wb_param.post_offset_b = colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_b;

	  g_wb_setting.standard.color_temp = COLOR_TEMP_STD;
	  g_wb_setting.standard.wb_param.gain_r = colortemp_table[COLOR_TEMP_STD].wb_param.gain_r;
	  g_wb_setting.standard.wb_param.gain_g = colortemp_table[COLOR_TEMP_STD].wb_param.gain_g;
	  g_wb_setting.standard.wb_param.gain_b = colortemp_table[COLOR_TEMP_STD].wb_param.gain_b;
	  g_wb_setting.standard.wb_param.pre_offset_r = colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_r;
	  g_wb_setting.standard.wb_param.pre_offset_g = colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_g;
	  g_wb_setting.standard.wb_param.pre_offset_b = colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_b;
	  g_wb_setting.standard.wb_param.post_offset_r = colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_r;
	  g_wb_setting.standard.wb_param.post_offset_g = colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_g;
	  g_wb_setting.standard.wb_param.post_offset_b = colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_b;

	  g_wb_setting.warm.color_temp = COLOR_TEMP_WARM;
	  g_wb_setting.warm.wb_param.gain_r = colortemp_table[COLOR_TEMP_WARM].wb_param.gain_r;
	  g_wb_setting.warm.wb_param.gain_g = colortemp_table[COLOR_TEMP_WARM].wb_param.gain_g;
	  g_wb_setting.warm.wb_param.gain_b = colortemp_table[COLOR_TEMP_WARM].wb_param.gain_b;
	  g_wb_setting.warm.wb_param.pre_offset_r = colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_r;
	  g_wb_setting.warm.wb_param.pre_offset_g = colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_g;
	  g_wb_setting.warm.wb_param.pre_offset_b = colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_b;
	  g_wb_setting.warm.wb_param.post_offset_r = colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_r;
	  g_wb_setting.warm.wb_param.post_offset_g = colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_g;
	  g_wb_setting.warm.wb_param.post_offset_b = colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_b;

	  g_wb_setting.user.color_temp = COLOR_TEMP_USER;
	  g_wb_setting.user.wb_param.gain_r = colortemp_table[COLOR_TEMP_USER].wb_param.gain_r;
	  g_wb_setting.user.wb_param.gain_g = colortemp_table[COLOR_TEMP_USER].wb_param.gain_g;
	  g_wb_setting.user.wb_param.gain_b = colortemp_table[COLOR_TEMP_USER].wb_param.gain_b;
	  g_wb_setting.user.wb_param.pre_offset_r = colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_r;
	  g_wb_setting.user.wb_param.pre_offset_g = colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_g;
	  g_wb_setting.user.wb_param.pre_offset_b = colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_b;
	  g_wb_setting.user.wb_param.post_offset_r = colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_r;
	  g_wb_setting.user.wb_param.post_offset_g = colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_g;
	  g_wb_setting.user.wb_param.post_offset_b = colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_b;
  }
    //memcpy((void *)&g_wb_setting, (void *)&wb_default, sizeof(struct wb_setting));
#ifdef CONFIG_RANDOM_WRITE
    printf("wb start addr is 0x%08x, size is 0x%08x\n",USER_WB_SETTING_START, sizeof(struct wb_setting));
    return spi_flash_random_write(get_spi_flash_device(0), USER_WB_SETTING_START, sizeof(struct wb_setting), &g_wb_setting);
#else
    return 0;
#endif
}

int load_default_picmod_setting()
{
    memcpy((void *)&picmod_table, (void *)&pic_table_def, PICMOD_MAX*sizeof(vpu_picmod_table_t));
#ifdef CONFIG_RANDOM_WRITE
    return spi_flash_random_write(get_spi_flash_device(0), USER_PIC_SETTING_START, PICMOD_MAX*sizeof(vpu_picmod_table_t), &picmod_table);
#else
    return 0;
#endif
}

int load_default_setting()
{
    load_default_user_setting();
    load_default_picmod_setting();
    return 0;
}

static void load_user_setting()
{
    g_user_setting.pq = &vpu_fac_pq_setting;
    g_user_setting.audio = &audio_state;
    g_user_setting.system = &cur_system;
    memcpy((void *)g_user_setting.system, (void *)&g_user_setting_save.system, sizeof(struct systems));
    memcpy((void *)g_user_setting.pq, (void *)&g_user_setting_save.pq, sizeof(vpu_fac_pq_t));
    memcpy((void *)g_user_setting.audio, (void *)&g_user_setting_save.audio, sizeof(struct audio_control));
}

static void load_user_wb_setting()
{
    memcpy((void *)&colortemp_table[COLOR_TEMP_COLD],(void *)&g_wb_setting.cold, sizeof(vpu_colortemp_table_t));
    memcpy((void *)&colortemp_table[COLOR_TEMP_STD],(void *)&g_wb_setting.standard, sizeof(vpu_colortemp_table_t));
    memcpy((void *)&colortemp_table[COLOR_TEMP_WARM],(void *)&g_wb_setting.warm, sizeof(vpu_colortemp_table_t));
    memcpy((void *)&colortemp_table[COLOR_TEMP_USER],(void *)&g_wb_setting.user, sizeof(vpu_colortemp_table_t));
}

void pq_load_spi_data(void)
{
    //LOGI(TAG_VPP, "load pq data from spi!\n");
    unsigned char *des = (unsigned char*)&vpu_config_table;
    spi_flash_read(get_spi_flash_device(0), PQ_PARAM_AREA_BASE_OFFSET, sizeof(vpu_config_t), des);
    //LOGI(TAG_VPP, "load pq data from spi over!\n");
}

static int check_cmd_is_supported(int cmd)
{
    switch(cmd) {
    case (VPU_CMD_ENABLE | VPU_CMD_READ):
    case VPU_CMD_WB_VALUE:
    case (VPU_CMD_WB_VALUE | VPU_CMD_READ):
    case CMD_LVDS_SSG_SET:
        return 1;

    default :
        return 0;
    }
}

static int set_lvds_ssg(int level)
{
    //printf("set_lvds_ssg level:%d\n",level);
    Spread_spectrum(level);
    return 0;
}
static unsigned int handle_setting_cmd(unsigned char *s, int *rets)
{
    white_balance_setting_t * wbs;
    int * params = GetParams(s);

    if(params == NULL) {
        return -1;
    }

    switch(CmdID(s)) {
    case VPU_CMD_WB_VALUE:
        int mode = params[0];
        wbs = (white_balance_setting_t *) malloc(sizeof(white_balance_setting_t));
        wbs->r_gain = params[1];
        wbs->g_gain = params[2];
        wbs->b_gain = params[3];
        wbs->r_offset= params[4];
        wbs->g_offset = params[5];
        wbs->b_offset = params[6];
        write_wb_setting(mode, wbs);
        free(wbs);
        break;
    case (VPU_CMD_WB_VALUE | VPU_CMD_READ):
        wbs = read_wb_setting(params[0]);
        if(wbs == NULL) {
            break;
        }
        rets[0] = params[0];
        rets[1] = wbs->r_gain;
        rets[2] = wbs->g_gain;
        rets[3] = wbs->b_gain;
        rets[4] = wbs->r_offset;
        rets[5] = wbs->g_offset;
        rets[6] = wbs->b_offset;
        free(wbs);
        break;
    case (VPU_CMD_ENABLE | VPU_CMD_READ):
        read_user_setting(s,rets);
        break;
    case CMD_LVDS_SSG_SET:
           set_lvds_ssg(params[0]);
        break;

    default :
        break;
    }
    free(params);
    return 0;
}

static int setting_task_handle(int task_id, void *param)
{
    list_t *plist = list_dequeue(&setting_list);
    if(plist != NULL) {
        CMD_LIST *clist = list_entry(plist, CMD_LIST, list);
        if(clist != NULL) {
            unsigned char *cmd = (unsigned char *)(clist->cmd_data.data);
            if(cmd != NULL) {
                int rcmd_len = Ret_NumParam(cmd);
                if(rcmd_len > 0) {
                    int *params = (int *)malloc(rcmd_len*sizeof(int));
                    handle_setting_cmd(cmd, params);
                    SendReturn(setting_task_id, clist->cmd_data.cmd_owner, *cmd, (int *)params);
                    free(params);
                    params = NULL;
                } else {
                    handle_setting_cmd(cmd, NULL);
                }
            }
            freeCmdList(clist);
        }
    }

    return 0;
}

int save_task_handle(int task_id, void * param)
{
#ifdef CONFIG_RANDOM_WRITE

    if(1 == g_user_setting.change_flag) {
        g_user_setting.change_flag = 0;
        memcpy((void *)&g_user_setting_save.system, (void *)g_user_setting.system, sizeof(struct systems));
        memcpy((void *)&g_user_setting_save.pq, (void *)g_user_setting.pq, sizeof(vpu_fac_pq_t));
        memcpy((void *)&g_user_setting_save.audio, (void *)g_user_setting.audio, sizeof(struct audio_control));
        if(spi_flash_random_write(get_spi_flash_device(0), USER_SETTING_START, sizeof(struct user_setting_save), &g_user_setting_save)<=0) {
            printf("write user setting failed!\n");
            g_user_setting.change_flag = 1;
        }
    }
#endif

    return 0;

}

void init_setting_task(void)
{

    register_vpp_save(write_user_setting);
    register_audio_save(write_user_setting);
    pq_load_spi_data();
    spi_flash_read(get_spi_flash_device(0),USER_SETTING_START,sizeof(struct user_setting_save),(void *)&g_user_setting_save);
    spi_flash_read(get_spi_flash_device(0),USER_WB_SETTING_START,sizeof(struct wb_setting),(void *)&g_wb_setting);
    spi_flash_read(get_spi_flash_device(0),USER_PIC_SETTING_START,PICMOD_MAX*sizeof(vpu_picmod_table_t),(void *)&picmod_table);

    if(g_user_setting_save.system.version!= system_default.version) {
        printf("current version is 0x%08x, default version is 0x%08x\n", g_user_setting_save.system.version, system_default.version);
        load_default_user_setting();
        load_default_picmod_setting();
    }
    load_user_setting();

    if(g_wb_setting.adjusted != 1) {
        printf("current wb adjusted is 0x%08x\n", g_wb_setting.adjusted);
        g_wb_setting.adjusted = 1;
        load_default_wb_setting();

    }
    load_user_wb_setting();

	if(get_boot_flag() == 0)
	{
		if(cur_system.system.power_on_mode == POWER_ON_MODE_SUSPEND)
		{
			reboot(0x12345678);
			return;
		}
	}

    setting_task_id = RegisterTask(setting_task_handle, NULL, 0, TASK_PRIORITY_USER);
    if(setting_task_id > 0) {
        RegisterCmd(&setting_list, setting_task_id, INPUT_CEC | INPUT_UART_HOST, check_cmd_is_supported, handle_setting_cmd);

    }
#ifndef FBC_USER_WITHOUT_SAVE
    save_task_id = RegisterTask(save_task_handle, NULL, 0, TASK_PRIORITY_USER);
    if(save_task_id > 0) {
        request_timer(save_task_id,500);//5s
    }
#endif
}

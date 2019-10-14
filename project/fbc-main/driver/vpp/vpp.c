#include <common.h>
#include <register.h>
#include <c_arc_pointer_reg.h>
#include <clk_vpp.h>
#include <hdmi.h>
#include <hdmirx.h>
#include <vpu_util.h>
#include <srcif.h>
#include <interrupt.h>
#include <vpp.h>
#include <vpp_api.h>
#include <log.h>
#include <timer.h>
#include <gamma_lut.h>
#include <cm2_lut.h>
#include <listop.h>
#include <inputdata.h>
#include <key_const.h>
#include <task.h>
#include <input.h>
#include <malloc.h>
#include <command.h>
#include <stdlib.h>
#include <cmd.h>
#include <task_priority.h>
#include <spi_flash.h>
#include <spi_regional_division.h>
#include <panel.h>
#include <vbyone.h>
#include <project.h>

// -----------------------------------------------
// Global variables
// -----------------------------------------------

static unsigned int (*save)(unsigned char * s) = NULL;
//static read_parameter vpp_read_param = NULL;
//void register_vpp_save(save_parameter save_func, read_parameter read_func)
void register_vpp_save(save_parameter save_func)
{
    save = save_func;
    //vpp_read_param = read_func;
}


int vpp_task_id;
vpu_timing_t timing_cur;
vpu_outputmode_t port_cur;
unsigned int vpu_tm_revy_data;
vpu_timing_table_t timing_table[TIMING_MAX]= {
    {TIMING_NULL,0,0,0,0},
    {TIMING_1366x768P60,1366,768,1792,798},
    {TIMING_1920x1080P50,1920,1080,2640,1125},
    {TIMING_1920x1080P60,1920,1080,2200,1125},
    {TIMING_1920x1080P100,1920,1080,2640,1125},
    {TIMING_1920x1080P120,1920,1080,2200,1125},
    {TIMING_1920x1080P60_3D_SG,0,0,0,0},
    {TIMING_1920x1080P240,0,0,0,0},
    {TIMING_1920x1080P120_3D_SG,0,0,0,0},
    {TIMING_3840x2160P60,3840,2160,4400,2250},
    {TIMING_3840x2160P50,3840,2160,4400,2250},
    {TIMING_3840x2160P24,3840,2160,5500,2250},
    {TIMING_3840x2160P30,3840,2160,4400,2250},
    {TIMING_4kx1kP120_3D_SG,3840,1080,4400,1125},
    {TIMING_4kxd5kP240_3D_SG,0,0,0,0},
};

vpu_srcif_mode_t srcif_mode = SRCIF_PURE_SOFTWARE;
//to check the ic whether it is revA or revB: revA = 0, revB = 1
int get_metal_revision(void)
{
	int revision_id = 0;

	revision_id = Rd(METAL_REVISION);

	if(revision_id == 0)
		return 0;
	else
		return 1;
}


#ifdef IN_FBC_MAIN_CONFIG
int panel_id = 0;
vpu_source_t source_cur = SOURCE_HDMI;
vpu_gammamod_t gammamod_cur = GAMMA_AFTER;
unsigned int auto_backlight_en = 1;//for nature light on/off
vpu_colortemp_t colortemp_cur = COLOR_TEMP_STD;
vpu_picmod_t picmod_cur = PICMOD_STD;
vpu_gammalever_t gammalever_cur = GAMMA_LEVER1;
extern vframe_hist_t local_hist;
int setpatternflag = 0;
int vbyone_reset_flag = 0;
int csc_config = 0;//0:default setting,1:force output black;2:force set csc1 to default;3:pretect mode
int csc_config_cnt = 0;

int burn_task_id = -1;
int burn_pattern_mode=2;
int ret_burn_id =-1;
static int do_flag = 1;
extern unsigned char customer_ptn; 

int vbyone_counter_option = 0;

vpu_fac_pq_t vpu_fac_pq_setting = {
    128,128,128,128,128,
    {128,128,128,128,128,128,127,127,127},
    COLOR_TEMP_STD,
    PICMOD_STD,
    5,
};
#if 0
vpu_fac_pq_t vpu_fac_pq_def = {
    128,128,128,128,128,
    {128,128,128,128,128,128},
    COLOR_TEMP_STD,
    PICMOD_STD,
    5,
};
#endif
vpu_picmod_table_t picmod_table[PICMOD_MAX]= {
    {PICMOD_STD,128,128,128},
    {PICMOD_BRI,138,138,138},
    {PICMOD_SOFT,118,118,130},
    {PICMOD_MOVIE,110,110,130},
    {PICMOD_USER,128,128,128},
};
vpu_colortemp_table_t colortemp_table[COLOR_TEMP_MAX]={
    {COLOR_TEMP_COLD,{128,128,128,128,128,128,128,128,128}},
    {COLOR_TEMP_STD,{128,128,128,128,128,128,128,128,128}},
    {COLOR_TEMP_WARM,{128,128,128,128,128,128,128,128,128}},
    {COLOR_TEMP_USER,{128,128,128,128,128,128,128,128,128}},
};

static int reg_CM2_Adj_SatGLBgain_via_Y[9];
static int reg_CM2_global_HUE;
static int reg_CM2_global_Sat;
static int reg_CM2_EN;
static int reg_CM2_Filter_EN;
static int reg_CM2_Lum_adj_EN;
static int reg_CM2_Hue_adj_EN;
static int reg_CM2_Sat_adj_EN;

vpu_config_t vpu_config_table = {
    .version = 20140708,    //version
    .ctrl_flag = 0,     //ctrl_flag
    .bri_con_index = 11,    //bri_con_index
    .bri_con = {    //bri_con[11];brightness:-1024~1023;contrast:0~511
        0xffc00000, //brightness:-1024;contrast:0
        0xfccd0033, //brightness:-819;contrast:51
        0xfd9a0066, //brightness:-614;contrast:102
        0xfe670099, //brightness:-409;contrast:153
        0xff3400cc, //brightness:-204;contrast:204
        0x100,      //brightness:0;contrast:256
        0xcd00133,  //brightness:205;contrast:307
        0x19a0166,  //brightness:410;contrast:358
        0x2670199,  //brightness:615;contrast:409
        0x33401cc,  //brightness:820;contrast:460
        0x3ff01ff   //brightness:1023;contrast:511
    },
    .wb = {0},      //wb[3]
     .gamma_index = 1,   //gamma_index
      .gamma = {0},       //gamma[9]
       .cm2 = {0},     //cm2[188]
        .dnlp = {0},        //dnlp
         .sat_hue = {0},
      };


unsigned int pq_data_mapping(unsigned int wb_gain, unsigned int ui_range,unsigned int max_range, int enable)
{
    unsigned int ret_value;
    if (enable) {
        if((wb_gain>>10)&0x1) {
            wb_gain = wb_gain&0x3ff;
        } else {
            wb_gain = wb_gain + 1024;
        }
    }

    ret_value= wb_gain*ui_range/max_range;

    return ret_value;
}



void vpu_pq_data_init(void)
{
    int i;

    if(NULL == save) {
	  if (WB_DATA_FROM_DB)
	     {
	        colortemp_table[COLOR_TEMP_COLD].color_temp = COLOR_TEMP_COLD;
	        colortemp_table[COLOR_TEMP_COLD].wb_param.gain_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].gain_r,256,2048,0);
	        colortemp_table[COLOR_TEMP_COLD].wb_param.gain_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].gain_g,256,2048,0);
	        colortemp_table[COLOR_TEMP_COLD].wb_param.gain_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].gain_b,256,2048,0);
	        colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].pre_offset_r,256,2048,1);
	        colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].pre_offset_g,256,2048,1);
	        colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].pre_offset_b,256,2048,1);
	        colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].post_offset_r,256,2048,1);
	        colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].post_offset_g,256,2048,1);
	        colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[2].post_offset_b,256,2048,1);

	        colortemp_table[COLOR_TEMP_STD].color_temp = COLOR_TEMP_STD;
	        colortemp_table[COLOR_TEMP_STD].wb_param.gain_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_r,256,2048,0);
	        colortemp_table[COLOR_TEMP_STD].wb_param.gain_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_g,256,2048,0);
	        colortemp_table[COLOR_TEMP_STD].wb_param.gain_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_b,256,2048,0);
	        colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_r,256,2048,1);
	        colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_g,256,2048,1);
	        colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_b,256,2048,1);
	        colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_r,256,2048,1);
	        colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_g,256,2048,1);
	        colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_b,256,2048,1);

	        colortemp_table[COLOR_TEMP_WARM].color_temp = COLOR_TEMP_WARM;
	        colortemp_table[COLOR_TEMP_WARM].wb_param.gain_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].gain_r,256,2048,0);
	        colortemp_table[COLOR_TEMP_WARM].wb_param.gain_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].gain_g,256,2048,0);
	        colortemp_table[COLOR_TEMP_WARM].wb_param.gain_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].gain_b,256,2048,0);
	        colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].pre_offset_r,256,2048,1);
	        colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].pre_offset_g,256,2048,1);
	        colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].pre_offset_b,256,2048,1);
	        colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].post_offset_r,256,2048,1);
	        colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].post_offset_g,256,2048,1);
	        colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[1].post_offset_b,256,2048,1);

	        colortemp_table[COLOR_TEMP_USER].color_temp = COLOR_TEMP_USER;
	        colortemp_table[COLOR_TEMP_USER].wb_param.gain_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_r,256,2048,0);
	        colortemp_table[COLOR_TEMP_USER].wb_param.gain_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_g,256,2048,0);
	        colortemp_table[COLOR_TEMP_USER].wb_param.gain_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].gain_b,256,2048,0);
	        colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_r,256,2048,1);
	        colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_g,256,2048,1);
	        colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].pre_offset_b,256,2048,1);
	        colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_r = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_r,256,2048,1);
	        colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_g = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_g,256,2048,1);
	        colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_b = (unsigned short)pq_data_mapping((unsigned int)vpu_config_table.wb[0].post_offset_b,256,2048,1);
		} else{
			colortemp_table[COLOR_TEMP_COLD].color_temp = COLOR_TEMP_COLD;
			colortemp_table[COLOR_TEMP_COLD].wb_param.gain_r = colortemp_table[COLOR_TEMP_COLD].wb_param.gain_r;
			colortemp_table[COLOR_TEMP_COLD].wb_param.gain_g = colortemp_table[COLOR_TEMP_COLD].wb_param.gain_g;
			colortemp_table[COLOR_TEMP_COLD].wb_param.gain_b = colortemp_table[COLOR_TEMP_COLD].wb_param.gain_b;
			colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_r = colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_r;
			colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_g = colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_g;
			colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_b = colortemp_table[COLOR_TEMP_COLD].wb_param.pre_offset_b;
			colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_r = colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_r;
			colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_g = colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_g;
			colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_b = colortemp_table[COLOR_TEMP_COLD].wb_param.post_offset_b;

			colortemp_table[COLOR_TEMP_STD].color_temp = COLOR_TEMP_STD;
			colortemp_table[COLOR_TEMP_STD].wb_param.gain_r = colortemp_table[COLOR_TEMP_STD].wb_param.gain_r;
			colortemp_table[COLOR_TEMP_STD].wb_param.gain_g = colortemp_table[COLOR_TEMP_STD].wb_param.gain_g;
			colortemp_table[COLOR_TEMP_STD].wb_param.gain_b = colortemp_table[COLOR_TEMP_STD].wb_param.gain_b;
			colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_r = colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_r;
			colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_g = colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_g;
			colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_b = colortemp_table[COLOR_TEMP_STD].wb_param.pre_offset_b;
			colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_r = colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_r;
			colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_g = colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_g;
			colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_b = colortemp_table[COLOR_TEMP_STD].wb_param.post_offset_b;

			colortemp_table[COLOR_TEMP_WARM].color_temp = COLOR_TEMP_WARM;
			colortemp_table[COLOR_TEMP_WARM].wb_param.gain_r = colortemp_table[COLOR_TEMP_WARM].wb_param.gain_r;
			colortemp_table[COLOR_TEMP_WARM].wb_param.gain_g = colortemp_table[COLOR_TEMP_WARM].wb_param.gain_g;
			colortemp_table[COLOR_TEMP_WARM].wb_param.gain_b = colortemp_table[COLOR_TEMP_WARM].wb_param.gain_b;
			colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_r = colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_r;
			colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_g = colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_g;
			colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_b = colortemp_table[COLOR_TEMP_WARM].wb_param.pre_offset_b;
			colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_r = colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_r;
			colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_g = colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_g;
			colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_b = colortemp_table[COLOR_TEMP_WARM].wb_param.post_offset_b;

			colortemp_table[COLOR_TEMP_USER].color_temp = COLOR_TEMP_USER;
			colortemp_table[COLOR_TEMP_USER].wb_param.gain_r = colortemp_table[COLOR_TEMP_USER].wb_param.gain_r;
			colortemp_table[COLOR_TEMP_USER].wb_param.gain_g = colortemp_table[COLOR_TEMP_USER].wb_param.gain_g;
			colortemp_table[COLOR_TEMP_USER].wb_param.gain_b = colortemp_table[COLOR_TEMP_USER].wb_param.gain_b;
			colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_r = colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_r;
			colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_g = colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_g;
			colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_b = colortemp_table[COLOR_TEMP_USER].wb_param.pre_offset_b;
			colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_r = colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_r;
			colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_g = colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_g;
			colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_b = colortemp_table[COLOR_TEMP_USER].wb_param.post_offset_b;
		}
	}

    for(i=0; i<2; i++) {
        reg_CM2_Adj_SatGLBgain_via_Y[i*4]=vpu_config_table.cm2[160+i]&0xff;
        reg_CM2_Adj_SatGLBgain_via_Y[i*4+1]=(vpu_config_table.cm2[160+i]>>8)&0xff;
        reg_CM2_Adj_SatGLBgain_via_Y[i*4+2]=(vpu_config_table.cm2[160+i]>>16)&0xff;
        reg_CM2_Adj_SatGLBgain_via_Y[i*4+3]=(vpu_config_table.cm2[160+i]>>24)&0xff;
    }
    reg_CM2_Adj_SatGLBgain_via_Y[8]=vpu_config_table.cm2[162]&0xff;

    reg_CM2_global_HUE = vpu_config_table.cm2[167]&0xfff;
    reg_CM2_global_Sat = (vpu_config_table.cm2[167]>>16)&0xfff;

    reg_CM2_EN = (vpu_config_table.cm2[168]>>1)&0x1;
    reg_CM2_Filter_EN = (vpu_config_table.cm2[168]>>2)&0x1;
    reg_CM2_Lum_adj_EN = (vpu_config_table.cm2[168]>>4)&0x1;
    reg_CM2_Sat_adj_EN = (vpu_config_table.cm2[168]>>5)&0x1;
    reg_CM2_Hue_adj_EN = (vpu_config_table.cm2[168]>>6)&0x1;

    vpu_wb_offset_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.post_offset_r,WBSEL_R,WBOFFSET_POST);
    vpu_wb_offset_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.post_offset_g,WBSEL_G,WBOFFSET_POST);
    vpu_wb_offset_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.post_offset_b,WBSEL_B,WBOFFSET_POST);
}

void vpu_pq_set(void)
{
    fbc_adj_bri(vpu_fac_pq_setting.bri_ui);
    fbc_adj_con(vpu_fac_pq_setting.con_ui);
    fbc_adj_sat(vpu_fac_pq_setting.satu_ui);
    fbc_adj_hue(vpu_fac_pq_setting.hue_ui);

    vpu_wb_gain_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.gain_r,WBSEL_R);
    vpu_wb_gain_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.gain_g,WBSEL_G);
    vpu_wb_gain_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.gain_b,WBSEL_B);
    vpu_wb_offset_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.pre_offset_r,WBSEL_R,WBOFFSET_PRE);
    vpu_wb_offset_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.pre_offset_g,WBSEL_G,WBOFFSET_PRE);
    vpu_wb_offset_adj(colortemp_table[vpu_fac_pq_setting.colortemp_mod].wb_param.pre_offset_b,WBSEL_B,WBOFFSET_PRE);
}

static LIST_HEAD(vpp_cmd_list);
unsigned char vpp_debug[4];

#if 0
void vpu_factory_init(void)
{
    //init parameters
    memcpy(&vpu_fac_pq_setting,&vpu_fac_pq_def,sizeof(vpu_fac_pq_t));
    //brightness
    vpu_bri_adj(vpu_fac_pq_setting.bri_ui);
    //contrast
    vpu_con_adj(vpu_fac_pq_setting.con_ui);
    //hue
    vpu_hue_adj(vpu_fac_pq_setting.hue_ui);
    //saturation
    vpu_saturation_adj(vpu_fac_pq_setting.satu_ui);
    //picmod
    vpu_picmod_adj(vpu_fac_pq_setting.picmod);
    //colortemp
    vpu_colortemp_adj(vpu_fac_pq_setting.colortemp_mod);
    //backlight
    vpu_backlight_adj(vpu_fac_pq_setting.backlight_ui,timing_cur);
    //wb gain
    vpu_wb_gain_adj(vpu_fac_pq_setting.colortemp_user.gain_r,WBSEL_R);
    vpu_wb_gain_adj(vpu_fac_pq_setting.colortemp_user.gain_g,WBSEL_G);
    vpu_wb_gain_adj(vpu_fac_pq_setting.colortemp_user.gain_b,WBSEL_B);
    //wb offset
    vpu_wb_offset_adj(vpu_fac_pq_setting.colortemp_user.pre_offset_r,WBSEL_R,WBOFFSET_PRE);
    vpu_wb_offset_adj(vpu_fac_pq_setting.colortemp_user.pre_offset_g,WBSEL_G,WBOFFSET_PRE);
    vpu_wb_offset_adj(vpu_fac_pq_setting.colortemp_user.pre_offset_b,WBSEL_B,WBOFFSET_PRE);

}
#endif

void vpp_module_enable_bypass(vpu_modules_t module,int enable)
{
    printf("[vpp.c]%s,module:%d,enable:%d.\n",__func__,module,enable);
    switch(module) {
    case VPU_MODULE_VPU:
        enable_vpu(enable);
        break;
    case VPU_MODULE_TIMGEN:
        enable_timgen(enable);
        break;
    case VPU_MODULE_PATGEN:
        enable_patgen(enable);
        break;
    case VPU_MODULE_GAMMA:
        enable_gamma(enable);
        break;
    case VPU_MODULE_WB:
        enable_wb(enable);
        break;
    case VPU_MODULE_BC:
        enable_bst(enable);
        break;
    case VPU_MODULE_BCRGB:
        enable_rgbbst(enable);
        break;
    case VPU_MODULE_CM2:
        enable_cm2(enable);
        break;
    case VPU_MODULE_CSC1:
        enable_csc1(enable);
        break;
    case VPU_MODULE_DNLP:
        enable_dnlp(enable);
        break;
    case VPU_MODULE_CSC0:
        enable_csc0(enable);
        break;
    case VPU_MODULE_OSD:
        break;
    case VPU_MODULE_BLEND:
        enable_blend(enable);
        break;
    case VPU_MODULE_DEMURE:
        enable_demura(enable);
        break;
    case VPU_MODULE_OUTPUT:
        enable_output(enable);
        break;
    case VPU_MODULE_OSDDEC:
        break;

    default:
        break;
    }
}
void vpp_process_wb_getting(vpu_message_t message,int *rets)
{
    switch(message.cmd_id&0x7f) {
    case VPU_CMD_RED_GAIN_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.gain_r;
        break;
    case VPU_CMD_GREEN_GAIN_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.gain_g;
        break;
    case VPU_CMD_BLUE_GAIN_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.gain_b;
        break;
    case VPU_CMD_PRE_RED_OFFSET_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.pre_offset_r;
        break;
    case VPU_CMD_PRE_GREEN_OFFSET_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.pre_offset_g;
        break;
    case VPU_CMD_PRE_BLUE_OFFSET_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.pre_offset_b;
        break;
    case VPU_CMD_POST_RED_OFFSET_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.post_offset_r;
        break;
    case VPU_CMD_POST_GREEN_OFFSET_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.post_offset_g;
        break;
    case VPU_CMD_POST_BLUE_OFFSET_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_user.post_offset_b;
        break;
    case VPU_CMD_WB:
        rets[0] = vpu_whitebalance_status();
        break;
    default:
        break;
    }
}

void vpp_process_wb_setting(vpu_message_t message)
{
    switch(message.cmd_id) {
    case VPU_CMD_RED_GAIN_DEF:
        vpu_fac_pq_setting.colortemp_user.gain_r = message.parameter1;
        vpu_wb_gain_adj(message.parameter1,WBSEL_R);
        break;
    case VPU_CMD_GREEN_GAIN_DEF:
        vpu_fac_pq_setting.colortemp_user.gain_g = message.parameter1;
        vpu_wb_gain_adj(message.parameter1,WBSEL_G);
        break;
    case VPU_CMD_BLUE_GAIN_DEF:
        vpu_fac_pq_setting.colortemp_user.gain_b = message.parameter1;
        vpu_wb_gain_adj(message.parameter1,WBSEL_B);
        break;
    case VPU_CMD_PRE_RED_OFFSET_DEF:
        vpu_fac_pq_setting.colortemp_user.pre_offset_r = message.parameter1;
        vpu_wb_offset_adj(message.parameter1,WBSEL_R,WBOFFSET_PRE);
        break;
    case VPU_CMD_PRE_GREEN_OFFSET_DEF:
        vpu_fac_pq_setting.colortemp_user.pre_offset_g = message.parameter1;
        vpu_wb_offset_adj(message.parameter1,WBSEL_G,WBOFFSET_PRE);
        break;
    case VPU_CMD_PRE_BLUE_OFFSET_DEF:
        vpu_fac_pq_setting.colortemp_user.pre_offset_b = message.parameter1;
        vpu_wb_offset_adj(message.parameter1,WBSEL_B,WBOFFSET_PRE);
        break;
    case VPU_CMD_POST_RED_OFFSET_DEF:
        vpu_fac_pq_setting.colortemp_user.post_offset_r = message.parameter1;
        vpu_wb_offset_adj(message.parameter1,WBSEL_R,WBOFFSET_POST);
        break;
    case VPU_CMD_POST_GREEN_OFFSET_DEF:
        vpu_fac_pq_setting.colortemp_user.post_offset_g = message.parameter1;
        vpu_wb_offset_adj(message.parameter1,WBSEL_G,WBOFFSET_POST);
        break;
    case VPU_CMD_POST_BLUE_OFFSET_DEF:
        vpu_fac_pq_setting.colortemp_user.post_offset_b = message.parameter1;
        vpu_wb_offset_adj(message.parameter1,WBSEL_B,WBOFFSET_POST);
        break;
    case VPU_CMD_WB:
        vpu_whitebalance_init();
        break;
    default:
        break;
    }
}

////to check the ic whether it is T101 or T102: T101 = 1, T102 = 2
int get_ic_version(void)
{
	int vision_id = 0;

	vision_id = Rd(PREG_PAD_GPIO2_I);

	if((vision_id>>16)&0x1 == 1)
		return 1;
	else
		return 2;
}

void vpp_dump_hist(void)
{
    vframe_hist_t hist_info;
    int i;
    memcpy(&hist_info,&local_hist,sizeof(vframe_hist_t));
    printf("\n*************%s:show begin*************\n",__func__);
    printf("\t width:%d,height:%d,pixel_sum:%d,hist_pow:%d\n",
           hist_info.width,hist_info.height,hist_info.pixel_sum,hist_info.hist_pow);
    for(i=0; i<66; i++) {
        printf("0x%-8x\t",hist_info.gamma[i]);
        if((i+1)%8==0)
            printf("\n");
    }
    printf("\n*************%s:show end*************\n",__func__);
}
void vpp_dump_gamma(void)
{
    enable_gamma (0);//must disable gamma before change gamma table!!!
    int gamma_buf[(GAMMA_ITEM+1)/2],Idx,i;
    printf("*************%s:show begin*************\n",__func__);
    for(Idx = 0; Idx < GAMMA_MAX; Idx++) {
        vpu_get_gamma_lut(Idx, gamma_buf, GAMMA_ITEM);
        printf("gamma_index:%d\n",Idx);
        for(i = 0; i < (GAMMA_ITEM+1)/2; i++) {
            printf("0x%-8x\t",gamma_buf[i]);
            if((i+1)%8==0)
                printf("\n");
        }
        printf("\n");
    }
    printf("*************%s:show end*************\n",__func__);
    enable_gamma (1);
}
void vpp_set_gamma(char* color,char* buf)
{
    char *parm = buf;
    int *gamma_buf;
    unsigned int i,gamma_count;
    char gamma[4];
    gamma_buf = malloc(GAMMA_ITEM * sizeof(int));
    memset(gamma_buf, 0, GAMMA_ITEM * sizeof( int));
    gamma_count = (strlen(parm) + 2) / 3;
    printf("%s:gamma_count = %d\n",__func__,gamma_count);
    if (gamma_count > GAMMA_ITEM)
        gamma_count = GAMMA_ITEM;
    for (i = 0; i < gamma_count; ++i) {
        gamma[0] = parm[3 * i + 0];
        gamma[1] = parm[3 * i + 1];
        gamma[2] = parm[3 * i + 2];
        gamma[3] = '\0';
        gamma_buf[i] = strtol(gamma, NULL, 16);
    }
    enable_gamma (0);//must disable gamma before change gamma table!!!
    switch(color[0]) {
    case 'r':
        printf("set r Gamma Lookup Table!\n");
        vpu_set_gamma_lut(GAMMA_R,gamma_buf,gamma_count);
        break;
    case 'g':
        printf("set g Gamma Lookup Table!\n");
        vpu_set_gamma_lut(GAMMA_G,gamma_buf,gamma_count);
        break;
    case 'b':
        printf("set b Gamma Lookup Table!\n");
        vpu_set_gamma_lut(GAMMA_B,gamma_buf,gamma_count);
        break;
    case 'd':
        // LINEAR_GAMMA
        printf("using linear Gamma Lookup Table!\n");
        for (i=0; i<256; i+=2) {
            gamma_r_lut[i/2] = (4*i)| ((4*(i+1))<<16);
            gamma_g_lut[i/2] = (4*i)| ((4*(i+1))<<16);
            gamma_b_lut[i/2] = (4*i)| ((4*(i+1))<<16);
        }
        gamma_r_lut[256/2]   = 1023;
        gamma_g_lut[256/2]   = 1023;
        gamma_b_lut[256/2]   = 1023;
        config_gamma_lut(0,gamma_r_lut,257);  //R
        config_gamma_lut(1,gamma_g_lut,257);  //G
        config_gamma_lut(2,gamma_b_lut,257);  //B
        break;
    case '1':
        // black
        printf("using whole zero Gamma Lookup Table!\n");
        for (i=0; i<256; i+=2) {
            gamma_r_lut[i/2] = 0;
            gamma_g_lut[i/2] = 0;
            gamma_b_lut[i/2] = 0;
        }
        gamma_r_lut[256/2]   = 0;
        gamma_g_lut[256/2]   = 0;
        gamma_b_lut[256/2]   = 0;
        config_gamma_lut(0,gamma_r_lut,257);  //R
        config_gamma_lut(1,gamma_g_lut,257);  //G
        config_gamma_lut(2,gamma_b_lut,257);  //B
        break;
    default:
        break;
    }
//  printf("set  Gamma  line 1-3!\n");
    enable_gamma (1);
    free(gamma_buf);
}
void vpp_get_gamma(char* color)
{
    int gamma_buf[GAMMA_ITEM],index,i;
    if(color[0] == 'r')
        index = 0;
    else if(color[0] == 'g')
        index = 1;
    else if(color[0] == 'b')
        index = 2;
    else {
        LOGE(TAG_VPP, "%s:no support cmd!\n",__func__);
        return;
    }
    printf("gamma:");
    enable_gamma (0);//must disable gamma before change gamma table!!!
    vpu_get_gamma_lut_pq(index, gamma_buf, GAMMA_ITEM);
    for(i = 0; i < GAMMA_ITEM; i++) {
        printf_pq("%03x",gamma_buf[i]);
    }
    printf("\n");
    enable_gamma (1);
}

void vpp_set_demura(unsigned int index,unsigned int offset,char* data_in)
{
    char *parm = data_in;
    int *demura_buf;
    unsigned int i,demura_count,res_count,loop_cnt;
    char demura_data_temp[5];
    demura_buf = malloc(DEMURA_DEBUG_DATA_NUM * sizeof(int));
    memset(demura_buf, 0, DEMURA_DEBUG_DATA_NUM * sizeof( int));
    demura_count = (strlen(parm) + 3) / 4;
    res_count = demura_count;
    loop_cnt = 0;
    printf("%s:demura_count = %d\n",__func__,demura_count);
    while(res_count) {
        if(res_count > DEMURA_DEBUG_DATA_NUM)
            demura_count = DEMURA_DEBUG_DATA_NUM;
        else
            demura_count = res_count;
        for(i = 0; i < demura_count; ++i) {
            demura_data_temp[0] = parm[loop_cnt*DEMURA_DEBUG_DATA_NUM*4 + 4 * i + 0];
            demura_data_temp[1] = parm[loop_cnt*DEMURA_DEBUG_DATA_NUM*4 + 4 * i + 1];
            demura_data_temp[2] = parm[loop_cnt*DEMURA_DEBUG_DATA_NUM*4 + 4 * i + 2];
            demura_data_temp[3] = parm[loop_cnt*DEMURA_DEBUG_DATA_NUM*4 + 4 * i + 3];
            demura_data_temp[4] = '\0';
            demura_buf[i] = strtol(demura_data_temp, NULL, 16);
        }
        if(vpu_write_lut_new(index,demura_count,offset + loop_cnt*DEMURA_DEBUG_DATA_NUM,demura_buf,0) == 1)
            LOGE(TAG_VPP, "%s :demura write time out!\n",__func__);
        loop_cnt ++;
        res_count = res_count - demura_count;
    }
    free(demura_buf);
}
void vpp_get_demura(unsigned int index,unsigned int offset,unsigned int size)
{
    int *demura_buf;
    unsigned int i,resv_size,out_size,loop_cnt;
    resv_size = size;
    out_size = 0;
    loop_cnt = 0;
    printf("demura:");
    demura_buf = malloc(DEMURA_DEBUG_DATA_NUM * sizeof(int));
    while(resv_size) {
        memset(demura_buf, 0, DEMURA_DEBUG_DATA_NUM * sizeof( int));
        if(resv_size > DEMURA_DEBUG_DATA_NUM)
            out_size = DEMURA_DEBUG_DATA_NUM;
        else
            out_size = resv_size;
        if(vpu_read_lut_new(index,out_size,offset + loop_cnt*DEMURA_DEBUG_DATA_NUM,demura_buf,0) == 1) {
            LOGE(TAG_VPP, "%s :demura read time out!\n",__func__);
            return;
        }
        for(i = 0; i < out_size; i++) {
            printf_pq("%04x",demura_buf[i]);
        }
        loop_cnt ++;
        resv_size = resv_size - out_size;
    }
    printf("\n");
    free(demura_buf);
}

void vpu_pattern_Switch(pattern_mode_t mode)
{
   vpu_fac_pq_setting.test_pattern_mod = mode;
   setpatternflag = 1;
}

int burn_task_handle(int task_id, void * param)
{
    if (burn_pattern_mode >=9)
        burn_pattern_mode = 2;
	
    set_patgen(burn_pattern_mode++);
	
    return 0;
}

int burn_mode(int enable)
{
    if(!enable){
        if (ret_burn_id>=0){
          release_timer(ret_burn_id);
          ret_burn_id =-1;
        }
    }else{
        burn_task_id = RegisterTask(burn_task_handle, NULL, 0, TASK_PRIORITY_BURN);
        if (burn_task_id > 0){
           ret_burn_id = request_timer(burn_task_id,200);//2s
        }
    }

    return 0;
}


void vpp_process_debug(vpu_message_t message)
{
    switch(message.cmd_id) {
    case VPU_CMD_HIST:
        vpp_dump_hist();
        break;
    case VPU_CMD_BLEND:
        enable_blend(message.parameter1);
        break;
    case VPU_CMD_DEMURA:
        break;
    case VPU_CMD_CSC:
        break;
    case VPU_CMD_CM2:
        break;
    case VPU_CMD_GAMMA:
        vpp_dump_gamma();
        break;
    case VPU_CMD_SRCIF:
        vpu_srcif_debug(message.parameter1,message.parameter2);
        break;
    case VPU_CMD_D2D3:
        d2d3_select(message.parameter1);
        break;
    default:
        break;
    }
}
void vpp_process_pq_getting(vpu_message_t message,int *rets)
{
    switch(message.cmd_id&0x7f) {
    case VPU_CMD_NATURE_LIGHT_EN:
        break;
    case VPU_CMD_BACKLIGHT_EN:
        break;
    case VPU_CMD_BRIGHTNESS:
    case VPU_CMD_BRIGHTNESS_DEF:
        rets[0] = vpu_fac_pq_setting.bri_ui;
        break;
    case VPU_CMD_CONTRAST:
    case VPU_CMD_CONTRAST_DEF:
        rets[0] = vpu_fac_pq_setting.con_ui;
        break;
    case VPU_CMD_BACKLIGHT:
    case VPU_CMD_BACKLIGHT_DEF:
        rets[0] = vpu_fac_pq_setting.backlight_ui;
        break;
    case VPU_CMD_SATURATION:
    case VPU_CMD_COLOR_DEF:
        rets[0] = vpu_fac_pq_setting.satu_ui;
        break;
    case VPU_CMD_HUE_DEF:
        rets[0] = vpu_fac_pq_setting.hue_ui;
        break;
    case VPU_CMD_DYNAMIC_CONTRAST:
    case VPU_CMD_AUTO_LUMA_EN:  //can be reserved
        break;
    case VPU_CMD_PICTURE_MODE:
        rets[0] = vpu_fac_pq_setting.picmod;
        break;
    case VPU_CMD_PATTERN_EN:
        break;
    case VPU_CMD_PATTEN_SEL:
        rets[0] = vpu_fac_pq_setting.test_pattern_mod;
        break;
    case VPU_CMD_USER_GAMMA:
        break;
    case VPU_CMD_COLOR_TEMPERATURE_DEF:
        rets[0] = vpu_fac_pq_setting.colortemp_mod;
        break;
    default:
        vpp_process_wb_getting(message,rets);
        break;
    }
}
void vpp_process_pq_setting(vpu_message_t message)
{
    switch(message.cmd_id) {
    case VPU_CMD_NATURE_LIGHT_EN:
        auto_backlight_en = message.parameter1&0x1;
        break;
    case VPU_CMD_BACKLIGHT_EN:
        enable_backlight(message.parameter1&0x1);
        break;
    /*case VPU_CMD_AUTO_ELEC_MODE:
        printf("-------------------------auto save electricity mode:%d\n",message.parameter1);
        break;*/
    case VPU_CMD_BRIGHTNESS:
    case VPU_CMD_BRIGHTNESS_DEF:
        vpu_fac_pq_setting.bri_ui = message.parameter1;
        fbc_adj_bri(message.parameter1);
        break;
    case VPU_CMD_CONTRAST:
    case VPU_CMD_CONTRAST_DEF:
        vpu_fac_pq_setting.con_ui = message.parameter1;
        fbc_adj_con(message.parameter1);
        break;
    case VPU_CMD_BACKLIGHT:
    case VPU_CMD_BACKLIGHT_DEF:
        vpu_fac_pq_setting.backlight_ui = message.parameter1;
        vpu_backlight_adj(message.parameter1&0xff,timing_cur);
        break;
    case VPU_CMD_SATURATION:
    case VPU_CMD_COLOR_DEF:
        vpu_fac_pq_setting.satu_ui = message.parameter1;
        fbc_adj_sat(message.parameter1&0xff);
        break;
    case VPU_CMD_HUE_DEF:
        vpu_fac_pq_setting.hue_ui = message.parameter1;
        fbc_adj_hue(message.parameter1&0xff);
        break;
    case VPU_CMD_DYNAMIC_CONTRAST:
    case VPU_CMD_AUTO_LUMA_EN:  //can be reserved
        enable_dnlp(message.parameter1&0x1);
        break;
    case VPU_CMD_PICTURE_MODE:
        vpu_fac_pq_setting.picmod = message.parameter1;
        vpu_picmod_adj((vpu_picmod_t)message.parameter1&0xff);
        picmod_cur =(vpu_picmod_t)message.parameter1;
        break;
    case VPU_CMD_PATTERN_EN:
        enable_patgen(message.parameter1&0x1);
        break;
    case VPU_CMD_PATTEN_SEL:
        vpu_pattern_Switch((pattern_mode_t)message.parameter1);
        break;
    case VPU_CMD_USER_GAMMA:
        gammalever_cur = (vpu_gammalever_t)message.parameter1;
        break;
    case VPU_CMD_COLOR_TEMPERATURE_DEF:
        vpu_fac_pq_setting.colortemp_mod = (vpu_colortemp_t)message.parameter1;
        vpu_colortemp_adj((vpu_colortemp_t)message.parameter1);
        colortemp_cur = (vpu_colortemp_t)message.parameter1;
        break;
	case VPU_CMD_GRAY_PATTERN:
        vpu_patgen_bar_set(message.parameter1,message.parameter2,message.parameter3);
        vpu_color_bar_mode();
        break;
	case VPU_CMD_BURN:
		burn_mode(message.parameter1);
		break;
	case VPU_CMD_COLOR_SURGE:
		vpu_set_color_surge(message.parameter1,timing_cur);
		break;
    default:
        vpp_process_wb_setting(message);
        break;
    }
}
void vpp_process_pq(vpu_message_t message,int *rets)
{
    if(message.cmd_id&VPU_CMD_READ)
        vpp_process_pq_getting(message,rets);
    else
        vpp_process_pq_setting(message);
}
void vpp_process_top_getting(vpu_message_t message,int *rets)
{
    switch(message.cmd_id&0x7f) {
    case VPU_CMD_INIT:
    case VPU_CMD_ENABLE:
    case VPU_CMD_BYPASS:
    case VPU_CMD_OUTPUT_MUX:
        break;
    case VPU_CMD_TIMING:
        rets[0] = timing_cur;
        break;
    case VPU_CMD_SOURCE:
        rets[0] = source_cur;
        break;
    case VPU_CMD_GAMMA_MOD:
        rets[0] = gammamod_cur;
        break;
	case CMD_HDMI_STAT:
		rets[0] = get_hdmi_stat();
		printf("hdmi stat = [%d]", rets[0]);
		break;
    default:
        break;
    }
}
void vpp_process_top_setting(vpu_message_t message)
{
    switch(message.cmd_id) {
    case VPU_CMD_INIT:
        init_display();
        init_vpp();
        break;
    case VPU_CMD_ENABLE:
        vpp_module_enable_bypass((vpu_modules_t)message.parameter1&0x7f,message.parameter2);
        break;
    case VPU_CMD_BYPASS:
        break;
    case VPU_CMD_OUTPUT_MUX:
        port_cur = (vpu_outputmode_t)message.parameter1;
        set_vpu_output_mode(port_cur);
        if(port_cur == OUTPUT_LVDS) {
            vclk_set_encl_lvds(timing_cur,LVDS_PORTS);
            lvds_init();
            set_LVDS_output(LVDS_PORTS);
        } else if(port_cur == OUTPUT_VB1) {
            //timing_cur = TIMING_3840x2160P60;
            vclk_set_encl_vx1(timing_cur,VX1_LANE_NUM, VX1_BYTE_NUM);
            vx1_init();
            set_VX1_output(VX1_LANE_NUM, VX1_BYTE_NUM, VX1_REGION_NUM, VX1_COLOR_FORMAT, timing_table[timing_cur].hactive, timing_table[timing_cur].vactive);
        }
        break;
    case VPU_CMD_TIMING:
        if(timing_cur != (vpu_timing_t)message.parameter1) {
            timing_cur = (vpu_timing_t)message.parameter1;
            vpu_timing_change_process();
        }
        break;
    case VPU_CMD_SOURCE:
        source_cur = (vpu_source_t)message.parameter1;
        break;
    case VPU_CMD_GAMMA_MOD:
        gammamod_cur = (vpu_gammamod_t)message.parameter1;
        config_gamma_mod(gammamod_cur);
        break;
    default:
        break;
    }
}
void vpp_process_top(vpu_message_t message,int *rets)
{
    if(message.cmd_id&VPU_CMD_READ)
        vpp_process_top_getting(message,rets);
    else
        vpp_process_top_setting(message);
}

void vpp_process(vpu_message_t message,int *rets)
{
    switch(message.cmd_id&0x7f) {
        //top
    case VPU_CMD_INIT:
    case VPU_CMD_ENABLE:
    case VPU_CMD_BYPASS:
    case VPU_CMD_OUTPUT_MUX:
    case VPU_CMD_TIMING:
    case VPU_CMD_SOURCE:
    case VPU_CMD_GAMMA_MOD:
	case CMD_HDMI_STAT:
        vpp_process_top(message,rets);
        break;
        //PQ
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
    case VPU_CMD_GRAY_PATTERN:
	case VPU_CMD_BURN:
	case VPU_CMD_COLOR_SURGE:
        vpp_process_pq(message,rets);
        break;
        //debug
    case VPU_CMD_HIST:
    case VPU_CMD_BLEND:
    case VPU_CMD_DEMURA:
    case VPU_CMD_CSC:
    case VPU_CMD_CM2:
    case VPU_CMD_GAMMA:
    case VPU_CMD_SRCIF:
    case VPU_CMD_D2D3:
        vpp_process_debug(message);
        break;
    default:
        break;
    }
}
static unsigned int vpp_handle_cmd(unsigned char *s, int *rets)
{
    vpu_message_t cmd = {0};
    int i,type,charIndex;
    unsigned int * paramter;
    cmd.cmd_id = (fbc_command_t)s[0];
    charIndex = 1;
    for(i=0; i<cmd_def[cmd.cmd_id].num_param; i++) {
        if(i == 0)
            paramter = &cmd.parameter1;
        else if(i == 1)
            paramter = &cmd.parameter2;
        else if(i == 2) 
	        paramter = &cmd.parameter3;		
	    else
            break;
        type = (cmd_def[cmd.cmd_id].type >> (i*2)) & 0x03;
        switch(type) {
        case 1:
            *paramter = (unsigned int)s[charIndex];
            charIndex++;
            break;
        case 2:
            *paramter = ((unsigned int)s[charIndex]&0xff) |
                        ((unsigned int)s[charIndex+1]&0xff << 8);
            charIndex += 2;
            break;
        case 3:
            *paramter = ((unsigned int)s[charIndex]&0xff) |
                        ((unsigned int)s[charIndex+1]&0xff << 8)|
                        ((unsigned int)s[charIndex+2]&0xff << 16)|
                        ((unsigned int)s[charIndex+3]&0xff << 24);
            charIndex += 4;
            break;
        default:
            break;
        }
    }
    vpp_process(cmd,rets);
    if(NULL != save) {
        save(s);
    }
    LOGI(TAG_VPP,"vpu_cmd_id:0x%x process done.\n", cmd.cmd_id);
    return 0;

}

int vpp_task_handle(int task_id, void * param)
{
    list_t *plist = list_dequeue(&vpp_cmd_list);
    if(plist != NULL) {
        CMD_LIST *clist = list_entry(plist, CMD_LIST, list);
        if(clist != NULL) {
            unsigned char *cmd = (unsigned char *)(clist->cmd_data.data);
            if(cmd != NULL) {
                int rcmd_num = Ret_NumParam(cmd);
                if(rcmd_num > 0) {
                    void *params = (void *)malloc((rcmd_num+1)*sizeof(int));
                    vpp_handle_cmd(cmd, (int *)params);
                    SendReturn(vpp_task_id, clist->cmd_data.cmd_owner, *cmd, (int *)params);
                    free(params);
                    params = NULL;
                } else {
                    vpp_handle_cmd(cmd, NULL);
                }
            }
            freeCmdList(clist);
        }
    }
    return 0;
}
int do_gamma_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * argv[])
{
    char *cmd,*color,*gamma;
    //printf("[vpp]%s cmd_id = %s.\n",__func__,argv[1]);
    if(argc < 2) {
        return -1;
    }
    cmd = argv[1];
    color = argv[2];
    if(*cmd == 'w') {
        gamma = argv[3];
        vpp_set_gamma(color,gamma);
        return -1;
    } else if(*cmd == 'r') {
        vpp_get_gamma(color);
    } else
        LOGE(TAG_VPP, "[VPP.C] cmd err.\n");
    return -1;
}
int do_cm_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * argv[])
{
    int cm2_data[5],cm2_addr;
    char *cmd;
    //printf("[vpp]%s cmd_id = %s.\n",__func__,argv[1]);
    if(argc < 2) {
        return -1;
    }
    cmd = argv[1];
    cm2_addr = strtoul(argv[2],NULL,16);
    if(*cmd == 'w') {
        cm2_data[0] = strtoul(argv[3],NULL,16);
        cm2_data[1] = strtoul(argv[4],NULL,16);
        cm2_data[2] = strtoul(argv[5],NULL,16);
        cm2_data[3] = strtoul(argv[6],NULL,16);
        cm2_data[4] = strtoul(argv[7],NULL,16);

        if(vpu_write_lut_new(0x24,sizeof(cm2_data)/sizeof(int),cm2_addr,cm2_data,0) == 1)
            LOGE(TAG_VPP, "%s : cm write time out!\n",__func__);

    } else if(*cmd == 'r') {
        if(vpu_read_lut_new(0x24,sizeof(cm2_data)/sizeof(int),cm2_addr,cm2_data,0) == 1)
            LOGE(TAG_VPP, "%s :cm read time out!\n",__func__);

        printf("cm:0x%x 0x%x 0x%x 0x%x 0x%x\n",
               cm2_data[0],cm2_data[1],cm2_data[2],cm2_data[3],cm2_data[4]);

    } else
        LOGE(TAG_VPP, "[VPP.C] cmd err.\n");
    return -1;
}
int do_demura_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * argv[])
{
    unsigned int index,offset,size;
    char *cmd,*demura_data;
    //printf("[vpp]%s cmd_id = %s.\n",__func__,argv[1]);
    if(argc < 2) {
        return -1;
    }
    cmd = argv[1];
    index = strtoul(argv[2],NULL,16);
    offset = strtoul(argv[3],NULL,16);
    if(*cmd == 'w') {
        demura_data = argv[4];
        vpp_set_demura(index,offset,demura_data);
    } else if(*cmd == 'r') {
        size = strtoul(argv[4],NULL,16);
        vpp_get_demura(index,offset,size);
    } else
        LOGE(TAG_VPP, "[VPP.C] cmd err.\n");
    return -1;
}
int do_dnlp_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * argv[])
{
    char *cmd;
    //printf("[vpp]%s cmd_id = %s.\n",__func__,argv[1]);
    if(argc < 2) {
        return -1;
    }
    cmd = argv[1];
    if(*cmd == 'w')
        set_dnlp_parm(strtoul(argv[2],NULL,16),strtoul(argv[3],NULL,16));
    else if(*cmd == 'r')
        get_dnlp_parm();
    else
        LOGE(TAG_VPP, "[VPU_UTIL.C] cmd err.\n");

    return -1;
}

int do_vpp_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * argv[])
{
    unsigned int data_in,cmd_id,i,type,charIndex;
    printf("[vpp]%s cmd_id = %s.\n",__func__,argv[1]);
    if(argc < 2) {
        return -1;
    }
    cmd_id = strtoul(argv[1],NULL,10);//cmd_id
    vpp_debug[0] = (unsigned char)cmd_id;
    charIndex = 1;
    for(i=0; i<cmd_def[cmd_id].num_param; i++) {
        data_in = strtoul(argv[2+i],NULL,10);//paramter
        type = (cmd_def[cmd_id].type >> (i*2)) & 0x03;
        switch(type) {
        case 1:
            if(data_in > 0xff) {
                LOGE(TAG_VPP,"[vpp]error:parameter over flow limit one byte!!!\n");
                return -1;
            }
            vpp_debug[charIndex] = (unsigned char)data_in;
            charIndex++;
            break;
        case 2:
            if(data_in > 0xffff) {
                LOGE(TAG_VPP,"[vpp]error:parameter over flow limit two bytes!!!\n");
                return -1;
            }
            vpp_debug[charIndex] = (unsigned char)(data_in & 0xff);
            vpp_debug[charIndex+1] = (unsigned char)((data_in >> 8)&0xff);
            charIndex += 2;
            break;
        case 3:
            if(data_in > 0xffffffff) {
                LOGE(TAG_VPP,"[vpp]error:parameter over flow limit four bytes!!!\n");
                return -1;
            }
            vpp_debug[charIndex] = (unsigned char)(data_in & 0xFF);
            vpp_debug[charIndex+1] = (unsigned char)((data_in >> 8) & 0xFF);
            vpp_debug[charIndex+2] = (unsigned char)((data_in >> 16) & 0xFF);
            vpp_debug[charIndex+3] = (unsigned char)((data_in >> 24) & 0xFF);
            charIndex += 4;
            break;
        default:
            break;
        }
    }
    CmdChannelAddData(INPUT_VPP_DEBUG, vpp_debug);
    return -1;
}
static int vpp_check_cmd_is_supported(int cmd)
{
    if(cmd == (VPU_CMD_ENABLE | VPU_CMD_READ)) {
        return 0;
    }
    switch(cmd&0x7f) {
        //top
    case VPU_CMD_INIT:
    case VPU_CMD_ENABLE:
    case VPU_CMD_BYPASS:
    case VPU_CMD_OUTPUT_MUX:
    case VPU_CMD_TIMING:
    case VPU_CMD_SOURCE:
    case VPU_CMD_GAMMA_MOD:
        //PQ
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
    case VPU_CMD_GRAY_PATTERN:
    //case VPU_CMD_AUTO_ELEC_MODE:
	case VPU_CMD_BURN:
	case VPU_CMD_COLOR_SURGE:
        //debug
    case VPU_CMD_HIST:
    case VPU_CMD_BLEND:
    case VPU_CMD_DEMURA:
    case VPU_CMD_CSC:
    case VPU_CMD_CM2:
    case VPU_CMD_GAMMA:
    case VPU_CMD_SRCIF:
    case VPU_CMD_D2D3:
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
	case CMD_HDMI_STAT:
        return 1;
    default :
        return 0;
    }
}
/*
static void HDMIRX_IRQ_Handle(void *arg)
{
    static unsigned int hdmi_irq_cnt = 0;
    if(hdmi_irq_cnt > 10240)
        hdmi_irq_cnt = 0;
    hdmi_irq_cnt++;
    //LOGD(TAG_VPP, "[vpp.c]process in HDMIRX_IRQ_Handle\n");
}
*/
static void VPU_VS_IRQ_Handle(void *arg)
{
    static unsigned int vpu_irq_cnt = 0;
    unsigned int vpu_tm_revy_cmp_data= 0;
    vpu_tm_revy_cmp_data = Rd_reg_bits(VP_CTRL, 3, 11);
    if(vpu_irq_cnt > 10240)
        vpu_irq_cnt = 0;
    vpu_irq_cnt++;
    vpu_get_hist_info();//get hist info
    ve_dnlp_cal();

    if (vpu_tm_revy_cmp_data != vpu_tm_revy_data) {
        vpu_tm_revy_data = vpu_tm_revy_cmp_data;
        set_tm_rcvy(1,16,3);
    }
	if (setpatternflag==1){
        setpatternflag = 0;
        set_patgen(vpu_fac_pq_setting.test_pattern_mod);
	}
    if (vbyone_reset_flag >= 1){
		vbyone_reset_flag--;
		if(vbyone_reset_flag == 0)
		{
			Wr(VBO_SOFT_RST, 0x000001ff);
			//Delay_ms(1);
			delay_us(2);
			Wr(VBO_SOFT_RST, 0);
		}
        //Wr(VBO_SOFT_RST, 0x000001ff);
        //Wr(VBO_SOFT_RST, 0);
        //vbyone_reset_flag = 0;
	}
	if(csc_config == 1) {
		csc_config = 2;
		vpu_csc_config(1);
	}
	if (csc_config == 3) {
		csc_config_cnt ++;
		if (csc_config_cnt >= 20) {
			vpu_csc_config(0);
			csc_config = 0;
			csc_config_cnt  = 0;
		}
	}
	if (csc_config == 2) {
		vpu_csc_config(0);
		csc_config = 0;
		csc_config_cnt = 0;
	}
	if((1 == do_flag) && (0 == customer_ptn)){
		srcif_fsm_init();
	    //srcif_fsm_fc_unstbl();  //assume hdmi is not ready
	    if((timing_cur >= TIMING_1920x1080P50)&&(timing_cur <= TIMING_1920x1080P120_3D_SG))
	        srcif_tmg_on(0);    //enable timgen default is 1080p setting
	    else if((timing_cur >= TIMING_3840x2160P60)&&(timing_cur <= TIMING_4kxd5kP240_3D_SG))
	        srcif_tmg_on(2);    //enable timgen to 4k2k setting
	    if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
	        srcif_pure_sw_ptn();
	    } else {
	        srcif_fsm_on();       //enable SRCIF FSM
	    }
		do_flag = 0;
	}
    //LOGD(TAG_VPP, "[vpp.c]process in VPU_VS_IRQ_Handle.version:%s\n",VPU_VER);
}

static void LOCKN_IRQ_Handle(void *arg)
{
	if(0 == vbyone_counter_option)
	{
		Wr(VBO_SOFT_RST, 0x000001ff);
		//Delay_ms(1);
		delay_us(2);
		Wr(VBO_SOFT_RST, 0);
		printf("vx1 rst--lockn\n");
		LOGD(TAG_VPP, "[vpp.c]LOCKN IRQ IN:%s\n",VPU_VER);
	}else
	{	
		vbyone_reset_flag = vbyone_counter_option;
	}
}
/*
static void HPDN_IRQ_Handle(void *arg)
{
	if(0 == vbyone_counter_option)
	{
		Wr(VBO_SOFT_RST, 0x000001ff);
		//Delay_ms(1);
		delay_us(2);
		Wr(VBO_SOFT_RST, 0);
		printf("vx1 rst--hpdn\n");
	    LOGD(TAG_VPP, "[vpp.c]HPDN IRQ IN:%s\n",VPU_VER);
	}else
	{
		vbyone_reset_flag = vbyone_counter_option;
	}
}
*/
void setVx1CounterOption(int val)
{
	vbyone_counter_option = val;
}

void SRCIF_FSM_STATE_Handle(void *arg)
{
    if(srcif_mode == SRCIF_HYBRID) {
        srcif_hybrid_fsm_ctrl();
    }
    //LOGD(TAG_VPP, "[vpp.c]process in SRCIF_FSM_STATE_Handle.\n");
}
void vpp_load_spi_data(void)
{
    LOGI(TAG_VPP, "load pq data from spi!\n");
    unsigned char *des = (unsigned char*)&vpu_config_table;
    spi_flash_read(get_spi_flash_device(0), PQ_PARAM_AREA_BASE_OFFSET, sizeof(vpu_config_t), des);
    LOGI(TAG_VPP, "load pq data from spi over!\n");
}
#endif
// --------------------------------------------------------
//                     init vpp
// --------------------------------------------------------
#ifdef IN_FBC_MAIN_CONFIG
static void init_cm2(int hsize,int vsize)
{
    int i,cm2_cfg_lut[8*32];
    for(i=0; i<32; i++) {
        cm2_cfg_lut[i*8]= vpu_config_table.cm2[i*5];
        cm2_cfg_lut[i*8+1]= vpu_config_table.cm2[i*5+1];
        cm2_cfg_lut[i*8+2]= vpu_config_table.cm2[i*5+2];
        cm2_cfg_lut[i*8+3]= vpu_config_table.cm2[i*5+3];
        cm2_cfg_lut[i*8+4]= vpu_config_table.cm2[i*5+4];
        cm2_cfg_lut[i*8+5] = 0;
        cm2_cfg_lut[i*8+6] = 0;
        cm2_cfg_lut[i*8+7] = 0;
    }

    config_cm2_lut(cm2_cfg_lut,sizeof(cm2_cfg_lut)/sizeof(int));
    cm2_config(hsize,vsize,
               reg_CM2_Adj_SatGLBgain_via_Y,
               reg_CM2_global_HUE,
               reg_CM2_global_Sat,
               reg_CM2_EN,
               reg_CM2_Filter_EN,
               reg_CM2_Hue_adj_EN,
               reg_CM2_Sat_adj_EN,
               reg_CM2_Lum_adj_EN); //cm2_en=1;hue_adj_en=1;sat_adj_en=1;luma_adj_en=1;
    enable_cm2(1);
}
static init_gamma(void)
{
    int i;
    //linear Gamma
    enable_gamma (0);
    int gamma_r_table[129];
    int gamma_g_table[129];
    int gamma_b_table[129];

    for(i=0; i<128; i++) {
        gamma_r_table[i]=(vpu_config_table.gamma[4].gamma_r[2*i+1]<<16)|vpu_config_table.gamma[4].gamma_r[2*i];
        gamma_g_table[i]=(vpu_config_table.gamma[4].gamma_g[2*i+1]<<16)|vpu_config_table.gamma[4].gamma_g[2*i];
        gamma_b_table[i]=(vpu_config_table.gamma[4].gamma_b[2*i+1]<<16)|vpu_config_table.gamma[4].gamma_b[2*i];
    }
    gamma_r_table[128]= vpu_config_table.gamma[4].gamma_r[256];
    gamma_g_table[128]= vpu_config_table.gamma[4].gamma_g[256];
    gamma_b_table[128]= vpu_config_table.gamma[4].gamma_b[256];

    config_gamma_lut(0,gamma_r_table,257);  //R
    config_gamma_lut(1,gamma_g_table,257);  //G
    config_gamma_lut(2,gamma_b_table,257);  //B
    config_gamma_mod(GAMMA_BEFORE);//1:after blender
    enable_gamma (1);
}

void init_display(void)
{
    int hsize,vsize;
    int ret = -2;

    timing_cur = get_timing_mode();
    port_cur = get_output_mode();

    hsize = timing_table[timing_cur].hactive;
    vsize = timing_table[timing_cur].vactive;

    clock_set_srcif_ref_clk();

    if(port_cur == OUTPUT_LVDS) {
        //if cable clk > 130M.
        //if(clk_util_clk_msr(29, 50) > 130000000) {
            //printf("source --> cable 148.5M\n");
            //hdmirx_set_DPLL();
		vclk_set_lvds_hdmi(0,0,panel_param->ports);
        //} else {
            //printf("source --> OSC 24M\n");
            //vclk_set_encl_lvds(timing_cur,LVDS_PORTS);
        //}
        lvds_init();
    } else if(port_cur == OUTPUT_VB1) {
    	vclk_set_vx1_hdmi(0, 0, panel_param->lane_num, panel_param->byte_num);
        //vclk_set_encl_vx1(timing_cur, panel_param->lane_num, panel_param->byte_num);
        vx1_init();
    }

    LOGI(TAG_VPP, "initial VPU!\n");
    vpu_initial(hsize,vsize);

    enable_patgen(1); //0: disable; 1: enable; 2: bypass;


    if(port_cur == OUTPUT_LVDS) {
        set_LVDS_output_ex(panel_param->clk,panel_param->repack,panel_param->odd_even,panel_param->hv_invert,
                           panel_param->lsb_first,panel_param->pn_swap,panel_param->ports,panel_param->bit_size,
                           panel_param->b_select,panel_param->g_select,panel_param->r_select,panel_param->reg_de_exten,
                           panel_param->reg_blank_align,panel_param->lvds_swap,panel_param->clk_pin_swap);
    } else if(port_cur == OUTPUT_VB1) {
        set_VX1_output(panel_param->lane_num, panel_param->byte_num, panel_param->region_num,
                       panel_param->color_fmt, hsize, vsize);
    }

	if(1 == customer_ptn)
	{
		srcif_fsm_init();
		//srcif_fsm_fc_unstbl();  //assume hdmi is not ready
		if((timing_cur >= TIMING_1920x1080P50)&&(timing_cur <= TIMING_1920x1080P120_3D_SG))
		    srcif_tmg_on(0);    //enable timgen default is 1080p setting
		else if((timing_cur >= TIMING_3840x2160P60)&&(timing_cur <= TIMING_4kxd5kP240_3D_SG))
		    srcif_tmg_on(2);    //enable timgen to 4k2k setting
		if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
		    srcif_pure_sw_ptn();
		} else {
		    srcif_fsm_on();       //enable SRCIF FSM
		}
	}

    delay_us(20);
    enable_vpu(1);
}

void init_vpp(void)
{
    int hsize,vsize;
    int ret = -2;
    LOGI(TAG_VPP, "cpu run to init_vpp!\n");

    timing_cur = get_timing_mode();
    port_cur = get_output_mode();

#if (FBC_TOOL_EN ==1)
    if(NULL == save) {
        vpp_load_spi_data();
    }
#endif

    vpu_pq_data_init();

    /*
    ret = RegisterInterrupt(INT_HDMIRX_VS_IRQ, INT_TYPE_IRQ, (interrupt_handler_t)HDMIRX_IRQ_Handle);
    if(ret == 0){
        SetInterruptEnable(INT_HDMIRX_VS_IRQ, 1);
        LOGD(TAG_VPP, "[VPP.C] Enable interrupts: hdmi_rx_interrupt\n");
    }
    */

    LOGI(TAG_VPP, "initial hdmirx!\n");
    hdmirx_init();

    hsize = timing_table[timing_cur].hactive;
    vsize = timing_table[timing_cur].vactive;

    //PATGEN
    LOGI(TAG_VPP, "=== configure PATGEN!\n");
	if(1 == customer_ptn)
		set_patgen(PATTERN_MODE_BLUE);
	else
    	set_patgen(PATTERN_MODE_BLACK);

    //CSC0
    LOGI(TAG_VPP, "=== configure CSC0!\n");
    enable_csc0  (1);

    //DPLN
    LOGI(TAG_VPP, "=== configure DPLN!\n");
    enable_dnlp  (1);
    init_dnlp_para();
    dnlp_config(hsize,vsize,1,1,1); //dnlp_en=1; hist_win_en=1;luma_hist_spl_en=1;

    //CM2
    LOGI(TAG_VPP, "=== configure CM2!\n");
    LOGI(TAG_VPP, "Fill CM2 LUT...\n");
    init_cm2(hsize,vsize);

    //BST/CSC1/RGBBST
    LOGI(TAG_VPP, "=== configure BST,CSC1,RGBBST!\n");
    enable_bst   (1);
    enable_csc1  (1);
    enable_rgbbst(1);

    //OSD
#if 0
    LOGI(TAG_VPP, "=== configure OSD!\n");
    LOGI(TAG_VPP, "Fill OSD Char LUT 0...\n");
    Wr_reg_bits(OSD_RAM_REG0,(0<<1)|1,24,2); //ram_char_sel=1 (write ram_0); ram_char_sync_mode = 0;
    config_sosd_char_lut(sosd_char_lib0_lut,sizeof(sosd_char_lib0_lut)/sizeof(int)*2); //two datas in one item
    LOGI(TAG_VPP, "Fill OSD font LUT...\n");
    config_sosd_font_lut(sosd_font_lib_lut, sizeof(sosd_font_lib_lut)/sizeof(int));
    sosd_config(hsize,vsize,0,sosd_ram_char_sel,1); //3d_mode=0; ram_char_sel=0;
    enable_sosd  (1);
#endif

    //Blend
    LOGI(TAG_VPP, "=== configure Blend!\n");
//  enable_blend (2);

    //WB
    LOGI(TAG_VPP, "=== configure WB!\n");
    enable_wb    (1);

    //Gamma
    LOGI(TAG_VPP, "=== configure Gamma!\n");
    init_gamma();

    //Demura
    LOGI(TAG_VPP, "=== configure Demura!\n");
    enable_demura(0);

    set_tm_rcvy(1,16,3);

    //pwm
    config_pwm(panel_param->pwm_hz , timing_cur, panel_param->pwm_duty);
    config_3dsync_3dgls();

}

void start_vpp(void)
{
    int ret = -2;
    LOGI(TAG_VPP, "set up VSYNC interrupt!\n");

    ret = RegisterInterrupt(INT_VPU_VSYNC, INT_TYPE_IRQ, (interrupt_handler_t)VPU_VS_IRQ_Handle);
    if(ret == 0) {
        SetInterruptEnable(INT_VPU_VSYNC, 1);
        LOGD(TAG_VPP, "[VPP.C] Enable interrupts: vpu_vsync_interrupt\n");
    }
    if(srcif_mode == SRCIF_HYBRID) {
        srcif_hybrid_fsm_init();
        if((timing_cur >= TIMING_1920x1080P50)&&(timing_cur <= TIMING_1920x1080P120_3D_SG))
            srcif_tmg_on(0);    //enable timgen default is 1080p setting
        else if((timing_cur >= TIMING_3840x2160P60)&&(timing_cur <= TIMING_4kxd5kP240_3D_SG))
            srcif_tmg_on(2);    //enable timgen to 4k2k setting
        ret = RegisterInterrupt(INT_VPU_FSM_STATE_CHG_IRQ, INT_TYPE_IRQ, (interrupt_handler_t)SRCIF_FSM_STATE_Handle);
        if(ret == 0) {
            SetInterruptEnable(INT_VPU_FSM_STATE_CHG_IRQ, 1);
            LOGD(TAG_VPP, "[VPP.C] Enable interrupts: vpu_fsm_state_chg_interrupt\n");
        }
    }
    Wr_reg_bits(INTR_EDGE_0,1,16,1);  //edge trigger


    ret = RegisterInterrupt(INT_TIMERB, INT_TYPE_IRQ, (interrupt_handler_t)hdmirx_handler);
    if(ret == 0) {
        SetInterruptEnable(INT_TIMERB, 1);
        printf("Enable hdmirx timerB interrupts\n");
    }
    ret = RegisterInterrupt(INT_HDMIRX, INT_TYPE_IRQ, (interrupt_handler_t)HDMIRX_IRQ_Handle);
    if(ret == 0) {
        SetInterruptEnable(INT_HDMIRX, 1);
        LOGD(TAG_VPP, "[VPP.C] Enable interrupts: hdmi_rx_interrupt\n");
    }

	{
		Wr_reg_bits(GPIO_INTR_GPIO_SEL0,54,0,8); //[7:0]
		Wr_reg_bits(GPIO_INTR_EDGE_POL,1,0,1); //edge interrupt [0]
		Wr_reg_bits(GPIO_INTR_EDGE_POL,0,16,1); //raise edge[16]

		Wr_reg_bits(GPIO_INTR_GPIO_SEL0,53,8,8); //[15:8]
		Wr_reg_bits(GPIO_INTR_EDGE_POL,1,1,1); //edge interrupt [1]
		Wr_reg_bits(GPIO_INTR_EDGE_POL,0,17,1); //raise edge[17]

	ret = RegisterInterrupt(96, INT_TYPE_IRQ, (interrupt_handler_t)LOCKN_IRQ_Handle);
	if(ret == 0) {
		SetInterruptEnable(96, 1);
		LOGD(TAG_VPP, "[VPP.C] Enable interrupts: lockn_interrupt\n");
	}
	/*
	ret = RegisterInterrupt(97, INT_TYPE_IRQ, (interrupt_handler_t)HPDN_IRQ_Handle);
	if(ret == 0) {
		SetInterruptEnable(97, 1);
		LOGD(TAG_VPP, "[VPP.C] Enable interrupts: hpdn_interrupt\n");
	}
	*/
    }

    //register vpp task
    vpp_task_id = RegisterTask(vpp_task_handle, NULL, 0, TASK_PRIORITY_VPP);
    RegisterCmd(&vpp_cmd_list, vpp_task_id, INPUT_CEC | INPUT_UART_HOST |INPUT_UART_CONSOLE | INPUT_VPP_DEBUG, vpp_check_cmd_is_supported,vpp_handle_cmd);

    vpu_tm_revy_data = Rd_reg_bits(VP_CTRL, 3, 11);
}
#else
void init_vpp(void)
{
    int hsize,vsize;
    int ret = -2;

    timing_cur = get_timing_mode();
    port_cur = get_output_mode();

    hsize = timing_table[timing_cur].hactive;
    vsize = timing_table[timing_cur].vactive;

    clock_set_srcif_ref_clk();

    if(port_cur == OUTPUT_LVDS) {
        //if cable clk > 130M.
        //if(clk_util_clk_msr(29, 50) > 130000000) {
            //printf("source --> cable 148.5M\n");
            //hdmirx_set_DPLL();
		vclk_set_lvds_hdmi(0,0,panel_param->ports);
        //} else {
            //printf("source --> OSC 24M\n");
            //vclk_set_encl_lvds(timing_cur,LVDS_PORTS);
        //}
        lvds_init();
    } else if(port_cur == OUTPUT_VB1) {
    	vclk_set_vx1_hdmi(0, 0, panel_param->lane_num, panel_param->byte_num);
        //vclk_set_encl_vx1(timing_cur, panel_param->lane_num, panel_param->byte_num);
        vx1_init();
    }

    LOGI(TAG_VPP, "initial VPU!\n");
    vpu_initial(hsize,vsize);

    enable_patgen(1); //0: disable; 1: enable; 2: bypass;


    if(port_cur == OUTPUT_LVDS) {
        set_LVDS_output_ex(panel_param->clk,panel_param->repack,panel_param->odd_even,panel_param->hv_invert,
                           panel_param->lsb_first,panel_param->pn_swap,panel_param->ports,panel_param->bit_size,
                           panel_param->b_select,panel_param->g_select,panel_param->r_select,panel_param->reg_de_exten,
                           panel_param->reg_blank_align,panel_param->lvds_swap,panel_param->clk_pin_swap);
    } else if(port_cur == OUTPUT_VB1) {
        set_VX1_output(panel_param->lane_num, panel_param->byte_num, panel_param->region_num,
                       panel_param->color_fmt, hsize, vsize);
    }

    srcif_fsm_init();
    //srcif_fsm_fc_unstbl();  //assume hdmi is not ready
    if((timing_cur >= TIMING_1920x1080P50)&&(timing_cur <= TIMING_1920x1080P120_3D_SG))
        srcif_tmg_on(0);    //enable timgen default is 1080p setting
    else if((timing_cur >= TIMING_3840x2160P60)&&(timing_cur <= TIMING_4kxd5kP240_3D_SG))
        srcif_tmg_on(2);    //enable timgen to 4k2k setting
    if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
        srcif_pure_sw_ptn();
    } else {
        srcif_fsm_on();       //enable SRCIF FSM
    }

    //Gamma
    LOGI(TAG_VPP, "=== configure Gamma!\n");
    enable_gamma (0);

    set_tm_rcvy(1,16,3);

    delay_us(20);
    enable_vpu(1);
	//pwm
    config_pwm(panel_param->pwm_hz , timing_cur, panel_param->pwm_duty);
}

#endif


#ifndef VPP_API_H
#define VPP_API_H

#include <cmd.h>

/*for factory menu begin*/
#define FBC_BRI_RANGE_UI 255		//brightness range:0~255
#define FBC_CON_RANGE_UI 255		//contrast range:0~255
#define FBC_SAT_RANGE_UI 255		//saturation range:0~255
#define FBC_HUE_RANGE_UI 255		//hue range:0~255
#define FBC_SHARPNESS_RANGE_UI 255	//sharpness range:0~255
#define FBC_BACKLIGHT_RANGE_UI 255	//backlight range:0~255
#define FBC_WB_GAIN_RANGE_UI 255	//wihte balance gain range:0~255
#define FBC_WB_OFFSET_RANGE_UI 255	//wihte balance offset range:0~255
#define FBC_BACKLIGHT_RANGE_REG 255	//backlight reg_val for naturelight range:0~255
/*for factory menu end*/

typedef enum demura_lutidx_e{
	FBC_DEMURE_BLREF_ODD_TABLE = 0x10,
	FBC_DEMURE_R_GAMMA_ODD_TABLE,
	FBC_DEMURE_R_DE_GAMMA_ODD_TABLE,
	FBC_DEMURE_LU_COEFF_ODD_TABLE,
	FBC_DEMURE_G_GAMMA_ODD_TABLE,
	FBC_DEMURE_G_DE_GAMMA_ODD_TABLE,
	FBC_DEMURE_B_GAMMA_ODD_TABLE,
	FBC_DEMURE_B_DE_GAMMA_ODD_TABLE,//0x17
	FBC_DEMURE_BLREF_EVEN_TABLE,
	FBC_DEMURE_R_GAMMA_EVEN_TABLE,
	FBC_DEMURE_R_DE_GAMMA_EVEN_TABLE,
	FBC_DEMURE_G_GAMMA_EVEN_TABLE,
	FBC_DEMURE_G_DE_GAMMA_EVEN_TABLE,
	FBC_DEMURE_B_GAMMA_EVEN_TABLE,
	FBC_DEMURE_B_DE_GAMMA_EVEN_TABLE,
	FBC_DEMURE_LU_COEFF_EVEN_TABLE,//0x1f
}demura_lutidx_t;
typedef struct fbc_hist_s{
	int  hist_data[34];
} fbc_hist_t;

//for PQ 

typedef enum vpu_modules_e{
	VPU_MODULE_NULL = 0,
	VPU_MODULE_VPU,		//vpu uint
	VPU_MODULE_TIMGEN,
	VPU_MODULE_PATGEN,
	VPU_MODULE_GAMMA,
	VPU_MODULE_WB,		//WhiteBalance
	VPU_MODULE_BC,		//Brightness&Contrast
	VPU_MODULE_BCRGB,	//RGB Brightness&Contrast 
	VPU_MODULE_CM2,
	VPU_MODULE_CSC1,	
	VPU_MODULE_DNLP,
	VPU_MODULE_CSC0,
	VPU_MODULE_OSD,
	VPU_MODULE_BLEND,	
	VPU_MODULE_DEMURE,	//15
	VPU_MODULE_OUTPUT,	//LVDS/VX1 output
	VPU_MODULE_OSDDEC,	//OSD decoder
	VPU_MODULE_MAX,
}vpu_modules_t;


typedef enum vpu_colortemp_e{	//color temperature
	COLOR_TEMP_COLD = 0,
	COLOR_TEMP_STD,
	COLOR_TEMP_WARM,
	COLOR_TEMP_USER,
	COLOR_TEMP_MAX,
}vpu_colortemp_t;

typedef enum vpu_picmod_e{	//picture mode
	PICMOD_STD = 0,		//standard
	PICMOD_BRI,		//brightness
	PICMOD_SOFT,		//soft
	PICMOD_MOVIE,		//movie
	PICMOD_USER,		//user
	PICMOD_MAX,
}vpu_picmod_t;

typedef struct vpu_picmod_table_s {
    vpu_picmod_t picmod;
    unsigned int bright;
    unsigned int contrast;
    unsigned int saturation;
} vpu_picmod_table_t;



typedef struct vpu_gamma_s{
	unsigned short gamma_r[257];
	unsigned short gamma_g[257];
	unsigned short gamma_b[257];
}vpu_gamma_t;

typedef struct vpu_bri_con_s{
	unsigned int bri_con;
}vpu_bri_con_t;

typedef struct vpu_wb_s{
	unsigned short gain_r;
	unsigned short gain_g;
	unsigned short gain_b;
	unsigned short pre_offset_r;
	unsigned short pre_offset_g;
	unsigned short pre_offset_b;
	unsigned short post_offset_r;
	unsigned short post_offset_g;
	unsigned short post_offset_b;
}vpu_wb_t;

typedef struct vpu_colortemp_table_s{
	vpu_colortemp_t color_temp;
	vpu_wb_t wb_param;
}vpu_colortemp_table_t;

typedef struct vpu_dnlp_table_s {
	unsigned int hist_ctrl;
	char method;
	char cliprate;
	char lowrange;
	char hghrange;
	char lowalpha;
	char midalpha;
	char hghalpha;
	char adj_level;
} vpu_dnlp_table_t;

typedef struct vpu_fac_pq_s{//for factory menu
	unsigned short bri_ui;//0~255
	unsigned short con_ui;//0~255
	unsigned short satu_ui;//0~255
	unsigned short hue_ui;//0~255
	unsigned short backlight_ui;//0~255
	vpu_wb_t colortemp_user;//0~255
	vpu_colortemp_t colortemp_mod;
	vpu_picmod_t picmod;
	unsigned short test_pattern_mod;
}vpu_fac_pq_t;

typedef struct vpu_sat_hue_s{
	unsigned short hue;
	unsigned short sat;
}vpu_sat_hue_t;

#pragma pack(2)
typedef struct vpu_config_s{
	//version info
	unsigned int version;
	//top ctrl flag
	unsigned int ctrl_flag;
	//brihtness&contrast
	unsigned int bri_con_index;
	vpu_bri_con_t bri_con[11];
	//wb
	vpu_wb_t wb[3];
	//gamma
	unsigned int gamma_index;
	vpu_gamma_t gamma[9];
	//cm2
	unsigned int cm2[188];
	//dnlp
	vpu_dnlp_table_t dnlp;
	unsigned int sat_hue_index;
	vpu_sat_hue_t sat_hue[11];
}vpu_config_t;

typedef struct vpu_pwm_channel_set_s
{
   unsigned char pwm_channel; ///< pwm channel
   unsigned int period; ///< pwm period
   unsigned int duty; ///< pwm duty
} vpu_pwm_channel_set_t;

#pragma pack()

//extern void register_vpp_save(save_parameter func, read_parameter read_func);
extern void register_vpp_save(save_parameter func);
extern void setVx1CounterOption(int val);
extern void register_backlight_func(backlight_func func);

extern fbc_hist_t* fbc_hist_info(void);
extern int fbc_avg_lut(void);
extern int fbc_bri_convert(int ui_val);
extern int fbc_con_convert(int ui_val);
extern int fbc_backlight_convert(int ui_val);
extern void fbc_bri_set(int reg_val);
extern void fbc_con_set(int reg_val);
extern void fbc_backlight_set(int reg_val);
extern void fbc_demura_enable(unsigned int en);
extern void fbc_demura_set(unsigned int leak_light,unsigned int threshold);
extern void fbc_demura_load_table(demura_lutidx_t table_index,int *data,int sizeItem);
extern void fbc_dynamic_contrast_enable(int enable);
extern void fbc_backlight_enable(int enable);
extern int fbc_backlight_status(void);
extern void fbc_switch_to_hdmi(int enable);
extern void fbc_set_gamma(int index);
extern int fbc_get_gamma(void);
extern void fbc_adj_bri(unsigned int bri_ui);
extern void fbc_adj_con(unsigned int con_ui);
extern void fbc_adj_sat(unsigned int sat_ui);
extern void fbc_adj_hue(unsigned int hue_ui);
extern void vpu_wb_gain_r(unsigned int gain_ui);
extern void vpu_wb_gain_g(unsigned int gain_ui);
extern void vpu_wb_gain_b(unsigned int gain_ui);
extern void vpu_wb_preoffset_r(unsigned int offset_ui);
extern void vpu_wb_preoffset_g(unsigned int offset_ui);
extern void vpu_wb_preoffset_b(unsigned int offset_ui);
extern void Spread_spectrum(int mode);
extern int fbc_system_pwm_set(vpu_pwm_channel_set_t pwm_set);
#endif


#ifndef _VPU_UTIL_H_
#define _VPU_UTIL_H_
#include <vpp.h>

//===== sub-unit: PatternGen
//mode == 10, default value, it's ramp
//mode == 11, grid9
//mode == 12, cir15
//mode == 13, palette
//mode == 14, triangle
//mode == 15, colorbar
//mode == 16, colorbar, LR
//mode == 17, two color TB
//mode == 18, two color line by line
//mode == 19, two color pixel by pixel
//===new pattern for client==
//mode == 0, off
//mode == 1, cir9
//mode == 2, 100% grey
//mode == 3, 20% grey
//mode == 4, black
//mode == 5, red
//mode == 6, green
//mode == 7, blue
//mode == 8, grey level
//mode == 9, pallet

typedef enum pattern_mode_e{
    PATTERN_MODE_OFF = 0,
    PATTERN_MODE_CIR9,
    PATTERN_MODE_GREY100,
    PATTERN_MODE_GREY20,
    PATTERN_MODE_BLACK,
    PATTERN_MODE_RED,
    PATTERN_MODE_GREEN,
    PATTERN_MODE_BLUE,
    PATTERN_MODE_GREYLEVEL,
    PATTERN_MODE_PALLET,
    PATTERN_MODE_RAMP,
    PATTERN_MODE_GRID9,
    PATTERN_MODE_CIR15,
    PATTERN_MODE_PALETTE,
    PATTERN_MODE_TRIANGLE,
    PATTERN_MODE_COLORBAR,
    PATTERN_MODE_COLORBAR_LR,
    PATTERN_MODE_COLORBAR_TB,
    PATTERN_MODE_TWO_COLOR_LINE_BY_LINE,
    PATTERN_MODE_TWO_COLOR_PIXEL_BY_PIXEL,
    PATTERN_MODE_AX,
}pattern_mode_t;


int vpu_read_lut_new (int lutIdx, int size, int saddr, int *pData, int twoDatas);
int vpu_write_lut_new(int lutIdx, int size, int saddr, int *pData, int twoDatas);

//=======================================
void vpu_initial(int hsize, int vsize);
void enable_vpu(int enable);
void set_init_tm_rcvy(int enable, int hs_width, int vs_width);
void set_tm_rcvy(int enable, int hs_width, int vs_width);


void enable_patgen(int enable);
void set_patgen(pattern_mode_t mode);
void set_patgen_yuv(pattern_mode_t mode);
void enable_csc0(int enable);
void enable_dpln(int enable);
void dnlp_config(int hsize, int vsize, int dnlp_en, int hist_win_en, int luma_hist_spl_en);
void dnlp_set_3dmode(int hist_3dmode, int hist_3dmodelr_xmid);
void enable_cm2(int enable);
int config_cm2_lut(int *pBuf, int sizeItem);
void cm2_config(int hsize, int vsize, const int CM2_SatGLBgain_via_Y[9], int hue, int sat, int cm2_en, int cm2_filter_en, int hue_adj_en, int sat_adj_en, int luma_adj_en);
void enable_bst(int enable);
void enable_csc1(int enable);
void enable_rgbbst(int enable);
void enable_blend(int enable);
#if 0
void enable_sosd(int enable);
void config_sosd_char_lut(int *pBuf, int sizeItem);
void config_sosd_font_lut(int *pBuf, int sizeItem);
void config_sosd_char_ram(int ram_char_sel);
void sosd_config(int hsize, int  vsize, int sosd_3d_mode, int ram_char_sel, int ram_char_sync_mode);
#endif
void enable_wb(int enable);
void enable_gamma(int enable);
void config_gamma_mod(vpu_gammamod_t mode);
void config_gamma_lut(int Idx, int *pBuf, int sizeItem);
void enable_demura(int enable);

void config_pwm(unsigned short pwm_freq, vpu_timing_t timing, unsigned short pwm_duty);
void config_3dsync_3dgls();

//Output
void set_vpu_output_mode (int mode);
void set_LVDS_output(int ports);
void set_LVDS_output_ex(unsigned char clk, unsigned char repack, unsigned char odd_even,
                        unsigned char hv_invert, unsigned char lsb_first, unsigned char pn_swap, unsigned char ports,
                        unsigned char bit_size, unsigned char b_sel, unsigned char g_sel, unsigned char r_sel,
                        unsigned char de_exten, unsigned char blank_align, unsigned char lvds_swap, unsigned char clk_pin_swap);

/*kuka@20140618 add begin*/
typedef struct vframe_hist_s {
    unsigned int   hist_pow;
    unsigned int   luma_sum;
    unsigned int   chroma_sum;
    unsigned int   pixel_sum;  // [31:30] POW [21:0] PIXEL_SUM
    unsigned int   height;
    unsigned int   width;
    unsigned char  luma_max;
    unsigned char  luma_min;
    unsigned short gamma[66];
} vframe_hist_t;
extern void vpu_get_hist_info(void);
extern void init_dnlp_para(void);
extern void ve_dnlp_cal(void);
extern void vpu_get_gamma_lut(int Idx, int *pBuf, int sizeItem);
extern void vpu_get_gamma_lut_pq(int Idx, int *pBuf, int sizeItem);
extern void vpu_set_gamma_lut(int Idx, int *pBuf, int sizeItem);
extern void enable_output(int enable);
extern void enable_timgen(int enable);
extern void enable_dnlp(int enable);
extern void set_dnlp_parm(int param1, int param2);
extern void get_dnlp_parm(void);
extern void enable_backlight(int enable);
extern void vpu_backlight_adj(unsigned int val_ui,vpu_timing_t timing);
extern void vpu_bri_adj(unsigned int bri_ui);
extern void vpu_con_adj(unsigned int con_ui);
extern void vpu_wb_gain_adj(unsigned int gain_ui,vpu_wbsel_t rgb_sel);
extern void vpu_wb_offset_adj(int offset_ui,vpu_wbsel_t rgb_sel,vpu_wboffset_pos_t pre_post);
extern void vpu_saturation_adj(unsigned int val_ui);
extern void vpu_hue_adj(unsigned int val_ui);
extern void vpu_picmod_adj(vpu_picmod_t val_ui);
extern void vpu_colortemp_adj(vpu_colortemp_t val_ui);
extern void vpu_color_bar_mode(void);
extern void vpu_patgen_bar_set(unsigned int r_val,unsigned int g_val,unsigned int b_val);
extern void vpu_testpat_def(void);
extern void vpu_whitebalance_init(void);
extern int vpu_whitebalance_status(void);
extern void vpu_timing_change_process(void);
extern void vpu_csc_config(unsigned int sel);
extern void vpu_srcif_debug(unsigned int mode,unsigned int mux);
extern vpu_srcif_mode_t vpu_get_srcif_mode(void);
extern void fbc_demura_set(unsigned int leak_light,unsigned int threshold);
extern void fbc_adj_bri(unsigned int bri_ui);
extern void fbc_adj_con(unsigned int con_ui);
extern void fbc_adj_sat(unsigned int sat_ui);
extern void fbc_adj_hue(unsigned int hue_ui);
extern void set_color_gamut(int mode);
extern void vpu_set_color_surge(unsigned int mode, vpu_timing_t timing_cur);
/*kuka@20140618 add end*/


#endif


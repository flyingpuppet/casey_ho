#include <register.h>
#include <common.h>
#include <vpu_util.h>
#include <srcif.h>
#include <clk_vpp.h>
#include <log.h>
#include <vpp_api.h>
#include <timer.h>
#include <project.h>

#ifdef IN_FBC_MAIN_CONFIG
#include <interrupt.h>
#include <string.h>
#include <malloc.h>
#endif
#define TIME_OUT_VALUE 5000 //5S
extern vpu_timing_table_t timing_table[TIMING_MAX];
extern vpu_picmod_table_t picmod_table[PICMOD_MAX];
extern vpu_colortemp_table_t colortemp_table[COLOR_TEMP_MAX];
extern vpu_timing_t timing_cur;
extern vpu_config_t vpu_config_table;
int cur_gamma_index = 4;
static int mode_flag = 0;
unsigned char con_auto_hdmi = 1;
//initial vpu
void vpu_initial(int hsize, int vsize)
{
    Wr(VP_CTRL,(1<<29));
    //Wr(VP_ENM_SYNC_MODE,0xffffdff8); //vpu/demura/tmgen/patgen not use gofld to sync
    Wr(VP_ENM_SYNC_MODE,0xffffdff0);
    Wr(VP_BPM_SYNC_MODE,0xffffffff);
    Wr(VP_IMG_SIZE,((vsize-1)<<16)|(hsize-1));
    set_init_tm_rcvy(1,16,3);
    //srcif_fsm_init();
}

void enable_vpu(int enable)
{
    Wr_reg_bits(VP_CTRL,(enable&0x1),0,1);
}


static int get_vpu_pipe_delays(int unit_en)
{
    int i, delays;
    static unsigned int fbc_vpu_unit_delays[] = {3,  //gamma
            3,  //wb
            3,  //bright adj
            8,  //rgb bright adj
            28, //cm2
            2,  //csc1
            9,  //dnlp
            2,  //csc0
            0,  //osd
            2,  //blend
            11   //demura
                                                };

    delays  = 0;
    unit_en = unit_en>>3;
    for(i=0; i<11; i++) {
        if(unit_en&0x1) {
            delays += fbc_vpu_unit_delays[i];
        }
        unit_en = unit_en>>1;
    }


    return delays;
}

//timing recovery
void set_init_tm_rcvy(int enable, int hs_width, int vs_width)
{
    Wr(VP_TM_RCVY_HSYNC,(53<<16)|(53+hs_width));
    Wr(VP_TM_RCVY_VSYNC,(2<<16) |(2+vs_width));

    Wr_reg_bits(VP_TM_RCVY_CTRL,2,0,14);            //reg_tm_rcvy_go_fld_vstart
    Wr_reg_bits(VP_TM_RCVY_CTRL,53+hs_width,16,14); //reg_tm_rcvy_go_fld_hstart

    Wr_reg_bits(VP_TM_RCVY_CTRL,0,14,1);  //reg_tm_rcvy_force_go_fld = 0;
    Wr_reg_bits(VP_TM_RCVY_CTRL,0,15,1);  //reg_tm_rcvy_force_go_fld_val = 0;
    Wr_reg_bits(VP_TM_RCVY_CTRL,1,30,1);  //reg_tm_rcvy_go_fld_dly_en = 1;
    Wr_reg_bits(VP_TM_RCVY_CTRL,1,31,1);  //reg_tm_rcvy_en = 1;
}

void set_tm_rcvy(int enable, int hs_width, int vs_width)
{

    unsigned int i,sync_offs;

    i = Rd(VP_CTRL);  //get unit enable info

    i = i&(~(1<<9))|(((Rd(HIST_CTRL)>>15)&0x1)<<9);  //get DNLP enable info
    sync_offs = get_vpu_pipe_delays(i)+1;
    Wr(VP_TM_RCVY_HSYNC,(sync_offs<<16)|(sync_offs+hs_width)); //hs_width = 16

    Wr_reg_bits(VP_TM_RCVY_CTRL,sync_offs+hs_width,16,14); //reg_tm_rcvy_go_fld_hstart
}



//===== sub-unit: PatternGen
void enable_patgen(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,    2,1);   //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1,0,1);   //bypass
}

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
void set_patgen(pattern_mode_t mode)
{
    unsigned int h_cal,v_cal;
    enable_patgen(1);
    vpu_testpat_def();//reset patgen
    if (mode == 0) {//disable patgen
        enable_patgen(0);
    } else if(mode == 1) { //cir9 whith 50% white field as background
        //vpu_patgen_bar_set(128,128,128);
        Wr(VP_PAT_BAR_R_0_3,0x80ff8000);//cir1 2 3
        Wr(VP_PAT_BAR_R_4_7,0x80ff0080);//cir4 5 6 7
        Wr(VP_PAT_BAR_R_8_11,0xff8000ff);//cir8 9 10 11
        Wr(VP_PAT_BAR_R_12_15,0x800080ff);//cir12 13 14 15

        Wr(VP_PAT_BAR_G_0_3,0x80ff80ff);
        Wr(VP_PAT_BAR_G_4_7,0x80ffff80);
        Wr(VP_PAT_BAR_G_8_11,0xff80ffff);
        Wr(VP_PAT_BAR_G_12_15,0x80ff80ff);

        Wr(VP_PAT_BAR_B_0_3,0x80ff8000);
        Wr(VP_PAT_BAR_B_4_7,0x80ff0080);
        Wr(VP_PAT_BAR_B_8_11,0xff8000ff);
        Wr(VP_PAT_BAR_B_12_15,0x800080ff);
        vpu_color_bar_mode();
        Wr_reg_bits(VP_PAT_XY_MODE,3,5,3);
        Wr_reg_bits(VP_CIR15_RAD,1,0,1);
    } else if(mode == 2) { //white field
        vpu_patgen_bar_set(255,255,255);
        vpu_color_bar_mode();
    } else if(mode == 3) { //20% white field
        vpu_patgen_bar_set(51,51,51);
        vpu_color_bar_mode();
    } else if(mode == 4) { //black field
        vpu_patgen_bar_set(0,0,0);
        vpu_color_bar_mode();
    } else if(mode == 5) { //red field
        vpu_patgen_bar_set(255,0,0);
        vpu_color_bar_mode();
    } else if(mode == 6) { //green field
        vpu_patgen_bar_set(0,255,0);
        vpu_color_bar_mode();
    } else if(mode == 7) { //blue field
        vpu_patgen_bar_set(0,0,255);
        vpu_color_bar_mode();
    } else if(mode == 8) { //triangle
        Wr_reg_bits(VP_CTRL,1,25,3);
    } else if(mode == 9) { //pallet ??
        Wr_reg_bits(VP_PAT_XY_MODE,1,5,3);
        Wr_reg_bits(VP_PAT_XY_MODE,0,2,3);
        Wr_reg_bits(VP_CTRL,0,25,3);
        if((timing_cur >=9)&&(timing_cur <=12)) {
            Wr_reg_bits(VP_PAT_XY_OF_SHFT,1,0,2);
            h_cal = ((1 << 15)*10/(timing_table[timing_cur].hactive/2) + 5)/10;
            v_cal = ((1 << 15)*10/(timing_table[timing_cur].vactive) +5)/10;
            Wr_reg_bits(VP_PAT_XY_SCL,v_cal,0,12);
            Wr_reg_bits(VP_PAT_XY_SCL,h_cal,16,12);
            Wr(VP_PAT_BAR_R_0_3,0xffffffff);//cir1 2 3
            Wr(VP_PAT_BAR_R_4_7,0xffffffff);//cir4 5 6 7
            Wr(VP_PAT_BAR_R_8_11,0x0);//cir8 9 10 11
            Wr(VP_PAT_BAR_R_12_15,0x0);//cir12 13 14 15

            Wr(VP_PAT_BAR_G_0_3,0xffffffff);
            Wr(VP_PAT_BAR_G_4_7,0x0);
            Wr(VP_PAT_BAR_G_8_11,0xffffffff);
            Wr(VP_PAT_BAR_G_12_15,0x0);

            Wr(VP_PAT_BAR_B_0_3,0xffffffff);
            Wr(VP_PAT_BAR_B_4_7,0x0);
            Wr(VP_PAT_BAR_B_8_11,0x0);
            Wr(VP_PAT_BAR_B_12_15,0xffffffff);
        } else {
            h_cal = ((1 << 15)*10/timing_table[timing_cur].hactive + 5)/10;
            v_cal = ((1 << 15)*10/(timing_table[timing_cur].vactive*2) +5)/10;
            Wr_reg_bits(VP_PAT_XY_SCL,v_cal,0,12);
            Wr_reg_bits(VP_PAT_XY_SCL,h_cal,16,12);
            Wr(VP_PAT_BAR_G_0_3,0xff00ff00);
            Wr(VP_PAT_BAR_B_0_3,0xff0000ff);
        }
    }
    //================old pattern reserved=================
    else if (mode == 11) {
        Wr_reg_bits(VP_CTRL,3,25,3);
        Wr_reg_bits(VP_CTRL,1,24,1);
        Wr_reg_bits(VP_CTRL,1,23,1);
        Wr_reg_bits(VP_CTRL,1,22,1);
        Wr_reg_bits(VP_CTRL,1,21,1);
        Wr_reg_bits(VP_CTRL,1,20,1);
        Wr_reg_bits(VP_CTRL,1,19,1);
    } else if (mode == 12) {
        Wr_reg_bits(VP_PAT_XY_MODE,1,2,3);
        Wr_reg_bits(VP_PAT_XRMP_SCL,0,0,8);
        Wr_reg_bits(VP_PAT_XRMP_SCL,0,8,8);
        Wr_reg_bits(VP_PAT_XRMP_SCL,0,16,8);
        Wr_reg_bits(VP_PAT_YRMP_SCL,0,0,8);
        Wr_reg_bits(VP_PAT_YRMP_SCL,0,8,8);
        Wr_reg_bits(VP_PAT_YRMP_SCL,0,16,8);
        Wr_reg_bits(VP_CIR15_RAD,1,0,1);
    } else if (mode == 13) {
        Wr_reg_bits(VP_CTRL,2,25,3);
    } else if (mode == 14) {
        Wr_reg_bits(VP_CTRL,1,25,3);
    } else if (mode == 15) {
        vpu_color_bar_mode();
    } else if (mode == 16) {
        Wr_reg_bits(VP_PAT_3D_MOD,1,2,3);
        vpu_color_bar_mode();
    } else if (mode == 17) {
        Wr_reg_bits(VP_PAT_3D_MOD,1,1,1);
        Wr_reg_bits(VP_PAT_3D_MOD,2,2,3);
        Wr_reg_bits(VP_PAT_3D_MOD,0,8,12);
        vpu_color_bar_mode();
    } else if (mode == 18) {
        Wr_reg_bits(VP_PAT_3D_MOD,1,1,1);
        Wr_reg_bits(VP_PAT_3D_MOD,3,2,3);
        Wr_reg_bits(VP_PAT_3D_MOD,0,8,12);
        vpu_color_bar_mode();
    } else if (mode == 19) {
        Wr_reg_bits(VP_PAT_3D_MOD,1,1,1);
        Wr_reg_bits(VP_PAT_3D_MOD,4,2,3);
        Wr_reg_bits(VP_PAT_3D_MOD,0,8,12);
        vpu_color_bar_mode();
    }

}

//===== sub-unit: YUV PatternGen  
//mode == 0, off
//mode == 2, white field
//mode == 4, black
//mode == 5, red
//mode == 6, green
//mode == 7, blue

void set_patgen_yuv(pattern_mode_t mode)
{
    enable_patgen(1);
    vpu_testpat_def();//reset patgen
    if (mode == 0) {//disable patgen
        enable_patgen(0);
    } else if(mode == 2) {
        vpu_patgen_bar_set(255,128,128);
        vpu_color_bar_mode();
    }  else if(mode == 4) {
        vpu_patgen_bar_set(0,128,128);
        vpu_color_bar_mode();
    }  else if(mode == 5) {
        vpu_patgen_bar_set(54,98,255);
        vpu_color_bar_mode();
    } else if(mode == 6) {
        vpu_patgen_bar_set(183,30,12);
        vpu_color_bar_mode();
    } else if(mode == 7) {
        vpu_patgen_bar_set(18,255,117);
        vpu_color_bar_mode();
    }
}

//===== sub-unit: CSC0
void enable_csc0(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,    10,1);   //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1, 8,1);   //bypass
}
#ifdef IN_FBC_MAIN_CONFIG
//===== sub-unit: DNLP
void enable_dnlp(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,     9,1);   //enable  useless
    Wr_reg_bits(HIST_CTRL,        enable&0x1,     15,1);   //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1, 7,1);   //bypass
}

void dnlp_config(int hsize, int vsize, int dnlp_en, int hist_win_en, int luma_hist_spl_en)
{
    unsigned int record_len = 0,pixel_sum = 0,hist_pow = 0;
    record_len = 0xffff<<3;
    pixel_sum = hsize*vsize;
    while ((pixel_sum > record_len) && (hist_pow < 3)) {
        hist_pow++;
        record_len <<= 1;
    }
    Wr_reg_bits(HIST_CTRL,hist_pow,5,3);          //hist_pow
    Wr_reg_bits(HIST_CTRL,dnlp_en,15,1);          //dnlp_en
    Wr_reg_bits(HIST_CTRL,hist_win_en,1,1);       //hist_win_en
    Wr_reg_bits(HIST_CTRL,luma_hist_spl_en,0,1);  //luma_hist_spl_en
    Wr(HIST_H_START_END,(0<<16)|((hsize-1)&0x3fff));
    Wr(HIST_V_START_END,(0<<16)|((vsize-1)&0x3fff));
    Wr(HIST_PIC_SIZE,((vsize&0x3fff)<<16)|(hsize&0x3fff));
    Wr(HIST_BLACK_WHITE_VALUE, 0xe010);
    Wr(HIST_3DMODE , 0x0);
    Wr(DNLP_CTRL_00, 0x08060402);
    Wr(DNLP_CTRL_01, 0x100e0c0a);
    Wr(DNLP_CTRL_02, 0x1a171412);
    Wr(DNLP_CTRL_03, 0x2824201d);
    Wr(DNLP_CTRL_04, 0x3834302c);
    Wr(DNLP_CTRL_05, 0x4b45403c);
    Wr(DNLP_CTRL_06, 0x605b5550);
    Wr(DNLP_CTRL_07, 0x80787068);
    Wr(DNLP_CTRL_08, 0xa0989088);
    Wr(DNLP_CTRL_09, 0xb8b2aca6);
    Wr(DNLP_CTRL_10, 0xc8c4c0bc);
    Wr(DNLP_CTRL_11, 0xd4d2cecb);
    Wr(DNLP_CTRL_12, 0xdad8d7d6);
    Wr(DNLP_CTRL_13, 0xe2e0dedc);
    Wr(DNLP_CTRL_14, 0xf0ece8e4);
    Wr(DNLP_CTRL_15, 0xfffcf8f4);
}

void dpln_set_3dmode(int hist_3dmode, int hist_3dmodelr_xmid)
{
    Wr(HIST_3DMODE,hist_3dmodelr_xmid|(hist_3dmode<<16));
}

//===== sub-unit: CM2
void enable_cm2(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,     7,1);   //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1, 5,1);   //bypass
}

int config_cm2_lut(int *pBuf, int sizeItem)
{
    int i;
    for(i=0; i<4; i++) {
        if(0 == vpu_write_lut_new (0x24,sizeItem,0,pBuf,0)) //each one 32bits items
            break;
        LOGE(TAG_VPP,"%s:time out!!\n",__func__);
    }
    return (i==4) ? 1 : 0;
}

void cm2_config(int hsize, int vsize, const int CM2_SatGLBgain_via_Y[9], int hue, int sat, int cm2_en, int cm2_filter_en, int hue_adj_en, int sat_adj_en, int luma_adj_en)
{
    Wr(VP_CM2_ADDR_PORT, CM_ENH_CTL_REG);
    Wr(VP_CM2_DATA_PORT, (((hue_adj_en &0x1)<<6)  |
                          ((sat_adj_en &0x1)<<5) |
                          ((luma_adj_en&0x1)<<4) |
                          ((cm2_filter_en&0x1)<<2) |
                          ((cm2_en     &0x1)<<1) ) );

    Wr(VP_CM2_ADDR_PORT, SAT_BYYB_NODE_REG0);
    Wr(VP_CM2_DATA_PORT, (((CM2_SatGLBgain_via_Y[3]&0xff)<<24) |
                          ((CM2_SatGLBgain_via_Y[2]&0xff)<<16) |
                          ((CM2_SatGLBgain_via_Y[1]&0xff)<< 8) |
                          ((CM2_SatGLBgain_via_Y[0]&0xff)    ) ) );

    Wr(VP_CM2_ADDR_PORT, SAT_BYYB_NODE_REG1);
    Wr(VP_CM2_DATA_PORT, (((CM2_SatGLBgain_via_Y[7]&0xff)<<24) |
                          ((CM2_SatGLBgain_via_Y[6]&0xff)<<16) |
                          ((CM2_SatGLBgain_via_Y[5]&0xff)<< 8) |
                          ((CM2_SatGLBgain_via_Y[4]&0xff)    ) ) );

    Wr(VP_CM2_ADDR_PORT, SAT_BYYB_NODE_REG2);
    Wr(VP_CM2_DATA_PORT, ((CM2_SatGLBgain_via_Y[8]&0xff)) );

    //Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
    //Wr(VP_CM2_DATA_PORT,  ((sat<<16) | hue));

    Wr(VP_CM2_ADDR_PORT, FRM_SIZE_REG);
    Wr(VP_CM2_DATA_PORT, (((vsize&0x1fff)<<16) |
                          ((hsize&0x1fff)    ) ) );

    Wr(VP_CM2_ADDR_PORT, CM_ENH_SFT_MODE_REG);
    Wr(VP_CM2_DATA_PORT, 0x90);
}
#endif

//===== sub-unit: BST
void enable_bst(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,     5,1);   //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1, 3,1);   //bypass
}

//===== sub-unit: CSC1
void enable_csc1(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,     8,1);   //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1, 6,1);   //bypass
}

//===== sub-unit: RGBBST
void enable_rgbbst(int enable)
{
    Wr_reg_bits(VP_CTRL,       enable&0x1,      6,1);   //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1, 4,1);   //bypass
}

//===== sub-unit: BLEND
void enable_blend(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,     12,1);   //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1, 10,1);   //bypass
}
#if 0
//===== sub-unit: SOSD
void enable_sosd(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,     11,1);  //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1,  9,1);  //bypass
}

void config_sosd_char_lut(int *pBuf, int sizeItem)
{
    int lutIdx;
    lutIdx = 0x20|0x1;
    vpu_write_lut_new (lutIdx,sizeItem,0,pBuf,1); //each two 16bits items
}

void config_sosd_font_lut(int *pBuf, int sizeItem)
//each data 32bits
{
    int lutIdx;
    lutIdx = 0x20|0x0;
    vpu_write_lut_new (lutIdx,sizeItem,0,pBuf,0); //each one 32bits items
}

void config_sosd_char_ram(int ram_char_sel)
{
    if(ram_char_sel==0)
        config_sosd_char_lut(sosd_char_lib0_lut,sizeof(sosd_char_lib0_lut)/sizeof(int)*2); //two datas in one item
    else
        config_sosd_char_lut(sosd_char_lib1_lut,sizeof(sosd_char_lib1_lut)/sizeof(int)*2); //two datas in one item
}
void sosd_config(int hsize, int  vsize, int sosd_3d_mode, int ram_char_sel, int ram_char_sync_mode)
//sosd_3d_mode:0-No, 1-left/right, 2-top/bot
{
    int i,j;
    int reg_osd_xstart,reg_osd_xend,reg_osd_ystart,reg_osd_yend;
    int reg_osd_3d_xsplit,reg_osd_3d_xintlv,reg_osd_3d_xintlv_phase;
    int reg_osd_3d_ysplit,reg_osd_3d_yintlv,reg_osd_3d_yintlv_phase;
    int reg_osd_font_xsize,reg_osd_font_xscal,reg_osd_font_xintm;
    int reg_osd_font_ysize,reg_osd_font_yscal,reg_osd_font_yintm;
    int reg_osd_font_bgfginvert,reg_osd_font_size;
    int reg_osd_font_bound_xpad[2], reg_osd_font_bound_ypad[2];
    int reg_osd_align_mode,reg_osd_align_bcindex,reg_osd_code_return;
    int ram_char_num,ram_font_lib_max;
    int reg_osd_hct;

    static int nRGBA1[16][4] = {{64,64,80,110},
        {0,0,192,110},
        {0,192,0,110},
        {0,192,192,110},
        {192,0,0,110},
        {192,0,192,110},
        {192,192,0,110},
        {192,192,192,110},
        {192,224,192,128},
        {192,224,32,128},
        {192,32,192,128},
        {192,0,32,128},
        {0,192,224,128},
        {0,192,32,128},
        {0,32,192,128},
        {32,80,32,128}
    };

    //----------------------------------------
    //character color
    for(i=0; i<16; i++) {
        Wr(OSD_COLOR_RGBA0+i,(nRGBA1[i][0]<<24)|(nRGBA1[i][1]<<16)|
           (nRGBA1[i][2]<< 8)|(nRGBA1[i][3]<<0));
    }
    for(i=0; i<32; i++) {
        reg_osd_hct = 0x33333333;
        Wr(OSD_FONT_HCT0+i,reg_osd_hct);
    }

    reg_osd_xstart=200+24;         // u14, osd text region xstart
    reg_osd_ystart=21;             // u14, osd text region ystart
    reg_osd_xend=hsize-100; // u14, osd text region xend
    reg_osd_yend=vsize-100;              // u14, osd text region yend

    reg_osd_3d_xsplit=hsize; //u14, (hsize/2) for LR 3D
    reg_osd_3d_ysplit=vsize; //u14, (vsize/2) for TB 3D
    reg_osd_3d_xintlv=0; //u1
    reg_osd_3d_yintlv=0; //u1
    reg_osd_3d_xintlv_phase = 0; //u1 collum interleave 3D mode phase offset
    reg_osd_3d_yintlv_phase = 0; //u1 row interleave 3D mode phase offset

    if(sosd_3d_mode==1) { //0-No, 1-left/right, 2-top/bot
        reg_osd_3d_xsplit = ((hsize>>2)<<1); //can only be even numbers
        reg_osd_xstart = reg_osd_xstart>>1;
        reg_osd_xend = reg_osd_xend>>1;
    } else if(sosd_3d_mode==2) { //3D: top/bot mode
        reg_osd_3d_ysplit = ((vsize>>2)<<1);
        reg_osd_ystart = reg_osd_ystart>>1;
        reg_osd_yend = reg_osd_yend>>1;
    } else if(sosd_3d_mode==3) { //3D x interleave mode
        reg_osd_3d_xintlv = 1; //u1
    } else if(sosd_3d_mode==4) { //3D y interleave mode
        reg_osd_3d_yintlv = 1; //u1
    }
    Wr(OSD_TXT_REGION_X,(reg_osd_xend<<16)|reg_osd_xstart);
    Wr(OSD_TXT_REGION_Y,(reg_osd_yend<<16)|reg_osd_ystart);
    Wr(OSD_3D_CTRL,(reg_osd_3d_xintlv<<31)|(reg_osd_3d_xintlv_phase<<30)|(reg_osd_3d_xsplit<<16)|
       (reg_osd_3d_yintlv<<15)|(reg_osd_3d_yintlv_phase<<14)|(reg_osd_3d_ysplit));

    reg_osd_font_xsize=30; //u6
    reg_osd_font_ysize=30; //u6
    reg_osd_font_xscal=2; //u2---
    reg_osd_font_yscal=2; //u2---
    reg_osd_font_xintm=1; //u1
    reg_osd_font_yintm=1; //u1
    reg_osd_font_bgfginvert=1; //u1
    reg_osd_font_size = reg_osd_font_xsize * reg_osd_font_ysize;
    Wr(OSD_FONT_REG0,(reg_osd_font_xscal<<30)|(reg_osd_font_xsize<<24)|(reg_osd_font_yscal<<22)|(reg_osd_font_ysize<<16)|
       (reg_osd_font_xintm<<14)|(reg_osd_font_yintm<<13)|(reg_osd_font_bgfginvert<<12)|(reg_osd_font_size));

    reg_osd_font_bound_xpad[0]=0; //u8
    reg_osd_font_bound_xpad[1]=0; //u8
    reg_osd_font_bound_ypad[0]=10; //u8
    reg_osd_font_bound_ypad[1]=10; //u8
    Wr(OSD_FONT_PAD,(reg_osd_font_bound_xpad[0]<<24)|(reg_osd_font_bound_xpad[1]<<16)|(reg_osd_font_bound_ypad[0]<<8)|
       (reg_osd_font_bound_ypad[1]));

    //aligned region
    reg_osd_align_mode = 1;  //u1 mode for right/bottom of the non filled osd region fill with bkgrnd, 0-no fill, 1-filling
    reg_osd_align_bcindex =0; //u4 bkrnd rgb index
    reg_osd_code_return=18;  //nFnt-1; // u8, return symbol (for simulation, the last one in lib is return symbol
    Wr(OSD_CHAR_REG0,(reg_osd_code_return<<16)|(reg_osd_align_mode<<8)|(reg_osd_align_bcindex));

    //text(characters) coding (OSD)
    ram_char_num=204;  //u12, number of character, max=(1920/30)*(1080/30)=2304;
    ram_font_lib_max = 104;
    Wr(OSD_RAM_REG0,(ram_char_sync_mode<<25)|(ram_char_sel<<24)|(ram_font_lib_max<<16)|(ram_char_num ));

    Wr(OSD_PSIZE,(vsize<<16)|hsize);
}
#endif

//===== sub-unit: WB
void enable_wb(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,      4,1);    //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1,  2,1);    //bypass
}

//===== sub-unit: Gamma
void enable_gamma(int enable)
{
    Wr_reg_bits(VP_CTRL,        enable&0x1,      3,1);    //enable
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1,  1,1);    //bypass
}
#ifdef IN_FBC_MAIN_CONFIG

void config_gamma_mod(vpu_gammamod_t mode)
{
    Wr_reg_bits(VP_CTRL,        mode& 0x1,      16,1);    //gamma mode
}
void config_gamma_lut(int Idx, int *pBuf, int sizeItem)
{
    int lutIdx;
    lutIdx = 0x00|Idx;
    if(vpu_write_lut_new (lutIdx,sizeItem,0,pBuf,1) == 1) //each 2 10bits items
        LOGE(TAG_VPP,"%s:time out!!\n",__func__);
}
#endif
//===== sub-unit: pwm
void config_pwm(unsigned short pwm_freq, vpu_timing_t timing, unsigned short pwm_duty)
{
    unsigned int val_v_reg,val_h_reg,val_v_range;
   // unsigned int i,data;

    if(panel_param->pwm_hz == 60) {
        if(panel_param->bl_inverter) {
            val_v_reg = (timing_table[timing].vtotal*(FBC_BACKLIGHT_RANGE_UI-pwm_duty)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = (timing_table[timing].vtotal*pwm_duty/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
        val_h_reg = (timing_table[timing].htotal/2 -1)<< 16;//one clock two pixels
    } else if (panel_param->pwm_hz == 120) {
        if(panel_param->bl_inverter) {
            val_v_reg = ((timing_table[timing].vtotal/2-1)*(FBC_BACKLIGHT_RANGE_UI-pwm_duty)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = ((timing_table[timing].vtotal/2-1)*pwm_duty/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
		val_v_range = timing_table[timing].vtotal/2;
        val_h_reg = (timing_table[timing].htotal/2 -1)<< 16;//one clock two pixels
    } else if (panel_param->pwm_hz == 240) {
        if(panel_param->bl_inverter) {
            val_v_reg = ((timing_table[timing].vtotal/4-1)*(FBC_BACKLIGHT_RANGE_UI-pwm_duty)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = ((timing_table[timing].vtotal/4-1)*pwm_duty/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
		val_v_range = timing_table[timing].vtotal/4;
        val_h_reg = (timing_table[timing].htotal/2 -1)<< 16;//one clock two pixels
    } else {
        if(panel_param->bl_inverter) {
            val_v_reg = (timing_table[timing].vtotal*(FBC_BACKLIGHT_RANGE_UI-pwm_duty)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = (timing_table[timing].vtotal*pwm_duty/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
        val_h_reg = (timing_table[timing].htotal/2 -1)<< 16;//one clock two pixels
    }

    Wr_reg_bits(PERIPHS_PIN_MUX_3, 1, 10, 1);
    Wr_reg_bits(PERIPHS_PIN_MUX_3, 0, 17, 1);

    if(pwm_freq == 60) {
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0);
        Wr(VP_PWM_DATA_PORT,val_v_reg);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H0);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H1);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H2);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);

        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V0);
        Wr(VP_PWM_DATA_PORT,0x00804010);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H0);
        Wr(VP_PWM_DATA_PORT,0x4400000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V1);
        Wr(VP_PWM_DATA_PORT,0x01a00128);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H1);
        Wr(VP_PWM_DATA_PORT,0x4300000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V2);
        Wr(VP_PWM_DATA_PORT,0x02bc0240);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H2);
        Wr(VP_PWM_DATA_PORT,0x42c0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V3);
        Wr(VP_PWM_DATA_PORT,0x03d40358);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);

        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V0);
        Wr(VP_PWM_DATA_PORT,0x0117408c);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H0);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V1);
        Wr(VP_PWM_DATA_PORT,0x022f01a4);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H1);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V2);
        Wr(VP_PWM_DATA_PORT,0x034702bc);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H2);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V3);
        Wr(VP_PWM_DATA_PORT,0x046003d4);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
    } else if(pwm_freq == 120) {
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0);
        Wr(VP_PWM_DATA_PORT,val_v_reg);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H0);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1);
        Wr(VP_PWM_DATA_PORT,val_v_reg+((val_v_range<<16)|val_v_range));
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H1);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H2);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H3);
        Wr(VP_PWM_DATA_PORT,0xffffffff);

        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V0);
        Wr(VP_PWM_DATA_PORT,0x00804010);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H0);
        Wr(VP_PWM_DATA_PORT,0x4400000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V1);
        Wr(VP_PWM_DATA_PORT,0x01a00128);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H1);
        Wr(VP_PWM_DATA_PORT,0x4300000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V2);
        Wr(VP_PWM_DATA_PORT,0x02bc0240);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H2);
        Wr(VP_PWM_DATA_PORT,0x42c0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V3);
        Wr(VP_PWM_DATA_PORT,0x03d40358);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);

        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V0);
        Wr(VP_PWM_DATA_PORT,0x0117408c);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H0);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V1);
        Wr(VP_PWM_DATA_PORT,0x022f01a4);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H1);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V2);
        Wr(VP_PWM_DATA_PORT,0x034702bc);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H2);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V3);
        Wr(VP_PWM_DATA_PORT,0x046003d4);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
    } else if(pwm_freq == 240) {
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0);
        Wr(VP_PWM_DATA_PORT,val_v_reg);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H0);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1);
        Wr(VP_PWM_DATA_PORT,val_v_reg+((val_v_range<<16)|val_v_range));
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H1);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2);
        Wr(VP_PWM_DATA_PORT,val_v_reg+(((2*val_v_range)<<16)|(2*val_v_range)));
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H2);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3);
        Wr(VP_PWM_DATA_PORT,val_v_reg+(((3*val_v_range)<<16)|(3*val_v_range)));
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
    	
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V0);
        Wr(VP_PWM_DATA_PORT,0x00804010);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H0);
        Wr(VP_PWM_DATA_PORT,0x4400000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V1);
        Wr(VP_PWM_DATA_PORT,0x01a00128);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H1);
        Wr(VP_PWM_DATA_PORT,0x4300000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V2);
        Wr(VP_PWM_DATA_PORT,0x02bc0240);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H2);
        Wr(VP_PWM_DATA_PORT,0x42c0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V3);
        Wr(VP_PWM_DATA_PORT,0x03d40358);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);

        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V0);
        Wr(VP_PWM_DATA_PORT,0x0117408c);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H0);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V1);
        Wr(VP_PWM_DATA_PORT,0x022f01a4);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H1);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V2);
        Wr(VP_PWM_DATA_PORT,0x034702bc);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H2);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V3);
        Wr(VP_PWM_DATA_PORT,0x046003d4);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
    } else { //default 60
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0);
        Wr(VP_PWM_DATA_PORT,val_v_reg);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H0);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H1);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H2);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3);
        Wr(VP_PWM_DATA_PORT,0xffffffff);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM0_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);

        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V0);
        Wr(VP_PWM_DATA_PORT,0x00804010);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H0);
        Wr(VP_PWM_DATA_PORT,0x4400000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V1);
        Wr(VP_PWM_DATA_PORT,0x01a00128);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H1);
        Wr(VP_PWM_DATA_PORT,0x4300000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V2);
        Wr(VP_PWM_DATA_PORT,0x02bc0240);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H2);
        Wr(VP_PWM_DATA_PORT,0x42c0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_V3);
        Wr(VP_PWM_DATA_PORT,0x03d40358);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM1_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);

        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V0);
        Wr(VP_PWM_DATA_PORT,0x0117408c);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H0);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V1);
        Wr(VP_PWM_DATA_PORT,0x022f01a4);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H1);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V2);
        Wr(VP_PWM_DATA_PORT,0x034702bc);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H2);
        Wr(VP_PWM_DATA_PORT,0x44b0000);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_V3);
        Wr(VP_PWM_DATA_PORT,0x046003d4);
        Wr(VP_PWM_ADDR_PORT,VPU_PWM2_H3);
        Wr(VP_PWM_DATA_PORT,0x44b0000);

    }

}
#ifdef IN_FBC_MAIN_CONFIG
//===== sub-unit: 3d sync
void config_3dsync_3dgls()
{
    Wr(VP_PWM_ADDR_PORT,VPU_PWM_HVSIZE_M1);
    Wr(VP_PWM_DATA_PORT,0x464044b);
    Wr(VP_PWM_ADDR_PORT,VPU_3DSYNC_CTRL);
    Wr(VP_PWM_DATA_PORT,0x01000100);
    Wr(VP_PWM_ADDR_PORT,VPU_3DSYNC_HVSTART);
    Wr(VP_PWM_DATA_PORT,0x00000000);

    Wr(VP_PWM_ADDR_PORT,VPU_3DGLS_CTRL);
    Wr(VP_PWM_DATA_PORT,0x01000100);
    Wr(VP_PWM_ADDR_PORT,VPU_3DGLS_HVSTART);
    Wr(VP_PWM_DATA_PORT,0x00000000);

    Wr(VP_PWM_ADDR_PORT,VPU_3DSYNC_CTRL);
    Wr(VP_PWM_DATA_PORT,0x81000100);
    Wr(VP_PWM_ADDR_PORT,VPU_3DGLS_CTRL);
    Wr(VP_PWM_DATA_PORT,0x81000100);
}

//===== sub-unit: Demura
void enable_demura(int enable)
//dm_res_sel: (1366x768)->0; FHD(1920x1080)->1; UHD(4K*2K)->2; U3D(4K*1K)->4
{
    int dm_res_sel;
    if(timing_cur == TIMING_1366x768P60)
        dm_res_sel = 0;
    else if((timing_cur >= TIMING_1920x1080P50)&&(timing_cur <= TIMING_1920x1080P120_3D_SG))
        dm_res_sel = 1;
    else if((timing_cur >= TIMING_3840x2160P60)&&(timing_cur <= TIMING_3840x2160P30))
        dm_res_sel = 2;
    else if(timing_cur == TIMING_4kx1kP120_3D_SG)
        dm_res_sel = 4;
    else
        dm_res_sel = 1;
    Wr(VP_DEMURA_CTRL,1|(dm_res_sel<<1)|(80<<4)|(0<<16));
    Wr_reg_bits(VP_CTRL,       (enable&0x1),   13,1);
    Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1,11,1);
}
#endif
//===== sub-unit: PTC
//void enable_ptc_path(int enable_minLvds, int enable_ptc2vx1)
//{
//  Wr_reg_bits(VP_CTRL,(enable_minLvds & 0x1),18,1);
//  Wr_reg_bits(VP_CTRL,(enable_ptc2vx1 ? 1 : 0),17,1);
//}

//===========

//---------------------------------------------------------------
//Output
void set_vpu_output_mode (int mode)
//0: LVDS; 1: VbyOne; 2: MinLvds
{
    if(mode == 0 || mode == 1) {
        //Wr_reg_bits(VP_CTRL,0,18,1);                      // set reg_minlvds_sel = 0
        Wr_reg_bits(VP_CTRL,1,14,1);                        // set reg_vx1lvds_en  = 1
        if(mode==0) {
            Wr_reg_bits(LVDS_CTRL,1,0,1);                   // set reg_lvds_enable = 1
            Wr_reg_bits(VXLVS_CTRL,1,0,1);
        } else {
            Wr_reg_bits(VBO_CTRL,1,0,1);                    // set reg_vbo_enable = 1
            Wr_reg_bits(VXLVS_CTRL,0,0,1);
        }
    } else {
        //Wr_reg_bits(VP_CTRL,1,18,1);                        // set reg_minlvds_sel = 1
        //Wr_reg_bits(VP_CTRL,0,14,1);                        // set reg_vx1lvds_en  = 0
    }
}
void panel_on(void)
{
    //panel pwr
    Wr_reg_bits(PREG_PAD_GPIO3_EN_N, 0, 0, 1);
    Wr_reg_bits(PREG_PAD_GPIO3_EN_N, 0, 5, 1);
    Wr_reg_bits(PREG_PAD_GPIO3_EN_N, 0, 12, 1);
    //panel on
    Wr_reg_bits(PREG_PAD_GPIO3_O, 0, 5, 1);
    delay_us(500);
    Wr_reg_bits(PREG_PAD_GPIO3_O, 0, 12, 1);
}

//ports:
//0-> 1 ports; 1-> 2 ports; 2-> 4ports;
void set_LVDS_output(int ports)
{
    int data32;
    Wr(LVDS_CLK_VALUE, (0x63)|(0x63<<8)|(0x63<<16)|(0x63<<24));
    Wr(LVDS_PACK_CNTL,
       ( 1 )    | // repack[1:0]
       ( 0<<2 ) | // odd_even
       ( 0<<3 ) | // reserve
       ( 0<<4 ) | // lsb first
       ( 0<<5 ) | // pn swap
       ( ports<<6 ) | // dual port[1:0]
       ( 0<<8 ) |  // bit_size[1:0] 0:10bits, 1:8bits, 2:6bits, 3:4bits.
       ( 0<<10 ) | // b_select[1:0] 0:R, 1:G, 2:B, 3:0
       ( 1<<12 ) | // g_select[1:0] 0:R, 1:G, 2:B, 3:0
       ( 2<<14 ) | // r_select[1:0] 0:R, 1:G, 2:B, 3:0
       ( 0<<16 ) | // reg_de_exten
       ( 0<<17 ) | // reserve
       ( 0<<18)  | // reg_blank_align
       ( 7<<23)  | // port revert[3:0]
       ( 0<<27)  );// clock pin swap
    data32 = (1<<ports); //ports
    Wr_reg_bits(VX1_LVDS_PHY_CNTL1,(1<<(data32*7))-1,0,16); //enable phy output
    //panel sequence
    //panel_on();
    set_vpu_output_mode(0); //LVDS
}

void set_LVDS_output_ex(unsigned char clk, unsigned char repack, unsigned char odd_even,
                        unsigned char hv_invert, unsigned char lsb_first, unsigned char pn_swap, unsigned char ports,
                        unsigned char bit_size, unsigned char b_sel, unsigned char g_sel, unsigned char r_sel,
                        unsigned char de_exten, unsigned char blank_align, unsigned char lvds_swap, unsigned char clk_pin_swap)
{
    int data32;
    Wr(LVDS_CLK_VALUE, (clk)|(clk<<8)|(clk<<16)|(clk<<24));
    Wr(LVDS_PACK_CNTL,
       ( repack )    | // repack[1:0]
       ( odd_even<<2 ) | // odd_even
       ( hv_invert<<3 ) | // reserve
       ( lsb_first<<4 ) | // lsb first
       ( pn_swap<<5 ) | // pn swap
       ( ports<<6 ) | // dual port[1:0]
       ( bit_size<<8 ) |  // bit_size[1:0]
       ( b_sel<<10 ) | // b_select[1:0]
       ( g_sel<<12 ) | // g_select[1:0]
       ( r_sel<<14 ) | // r_select[1:0]
       ( de_exten<<16 ) | // reg_de_exten
       ( 0<<17 ) | // reserve
       ( blank_align<<18)  | // reg_blank_align
       ( lvds_swap<<23)  | // port revert[3:0]
       ( clk_pin_swap<<27)  );// clock pin swap
    data32 = (1<<ports); //ports
    Wr_reg_bits(VX1_LVDS_PHY_CNTL1,(1<<(data32*7))-1,0,16); //enable phy output
    //panel sequence
    //panel_on();
    set_vpu_output_mode(0);
}

//===========================================================================
//      Function for LUT Access
//===========================================================================
//return 0:ok;1:time out
int vpu_write_lut_new (int lutIdx, int sizeItem, int saddr, int *pData, int twoDatas)
{
    int cmd_op, addr_mode,d16_num, d32_num;
    int temp,i, cnt;
    int size16b, size32b;
    unsigned long timeCnt1,timeCnt2,time_delta;
    cmd_op    = 0; //write
    addr_mode = 0; //incr
    cnt       = 0;
    if(twoDatas == 1) {
        size32b = sizeItem/2;
        size16b = sizeItem & 0x1;
        while (size32b) {
            d32_num = (size32b>=8) ? 8 : size32b;  //each 8 operations
            temp = (1<<31)|(cmd_op<<30)|(addr_mode<<28)|(d32_num<<24)| (1<<23)|(lutIdx<<16)|((saddr<<1)&0xffff);
            Wr(VP_LUT_ADDR_PORT,temp);
            for(i=0; i<d32_num; i++)
                Wr(VP_LUT_DATA_PORT,pData[cnt++]);
            size32b  -= d32_num;
            saddr    += d32_num;
            timeCnt1 = OSTimeGet();
            time_delta = 0;
            do {
                temp = Rd(VP_LUT_ADDR_PORT);
                timeCnt2 = OSTimeGet();
                if(timeCnt2 > timeCnt1)
                    time_delta = timeCnt2 - timeCnt1;
                else {
                    timeCnt1 = OSTimeGet();
                    time_delta = 0;
                }
                if(time_delta >= TIME_OUT_VALUE) {
                    LOGE(TAG_VPP,"%s:time out!!\n",__func__);
                    return 1;
                }
            }  while(temp&(1<<31));
        }
        if(size16b) {
            temp = (1<<31)|(cmd_op<<30)|(addr_mode<<28)|(1<<24)| (0<<23)|(lutIdx<<16)|((saddr<<1)&0xffff);
            Wr(VP_LUT_ADDR_PORT,temp);
            Wr(VP_LUT_DATA_PORT,pData[cnt++]);
            timeCnt1 = OSTimeGet();
            time_delta = 0;
            do {
                temp = Rd(VP_LUT_ADDR_PORT);
                timeCnt2 = OSTimeGet();
                if(timeCnt2 > timeCnt1)
                    time_delta = timeCnt2 - timeCnt1;
                else {
                    timeCnt1 = OSTimeGet();
                    time_delta = 0;
                }
                if(time_delta >= TIME_OUT_VALUE) {
                    LOGE(TAG_VPP,"%s:time out!!\n",__func__);
                    return 1;
                }
            }  while(temp&(1<<31));
        }
    } else {  //twoDatas == 0
        while (sizeItem) {
            d16_num = (sizeItem>=8) ? 8 : sizeItem;  //each 8 operations
            temp = (1<<31)|(cmd_op<<30)|(addr_mode<<28)|(d16_num<<24)| (0<<23)|(lutIdx<<16)| (saddr&0xffff);
            Wr(VP_LUT_ADDR_PORT,temp);
            for(i=0; i<d16_num; i++) {
                Wr(VP_LUT_DATA_PORT, pData[cnt++]);
            }
            sizeItem  -= d16_num;
            saddr     += d16_num;
            timeCnt1 = OSTimeGet();
            time_delta = 0;
            do {
                temp = Rd(VP_LUT_ADDR_PORT);
                timeCnt2 = OSTimeGet();
                if(timeCnt2 > timeCnt1)
                    time_delta = timeCnt2 - timeCnt1;
                else {
                    timeCnt1 = OSTimeGet();
                    time_delta = 0;
                }
                if(time_delta >= TIME_OUT_VALUE) {
                    LOGE(TAG_VPP,"%s:time out!!\n",__func__);
                    return 1;
                }
            } while(temp&(1<<31));
        }
    }
	if(lutIdx == 0x20 || lutIdx == 0x21){
		//sleep(200);
		int *pBuf_read = (int *)malloc((257+1)/2*sizeof(int));
		if(!pBuf_read)
		{
			printf("memory is not enough!!!\n");
		}
		//enable_gamma(0);
		vpu_read_lut_new(0, 257, 0, pBuf_read, 1);
		//unsigned int crc_r =  crc32(0, (unsigned char *)pBuf_read, 129*sizeof(int));
		vpu_read_lut_new(1, 257, 0, pBuf_read, 1);
		//unsigned int crc_g =  crc32(0, (unsigned char *)pBuf_read, 129*sizeof(int));
		vpu_read_lut_new(2, 257, 0, pBuf_read, 1);
		//unsigned int crc_b =  crc32(0, (unsigned char *)pBuf_read, 129*sizeof(int));
		//enable_gamma(1);

		//printf("crc_r = %08x, crc_g = %08x, crc_b = %08x, write_index = %d\n",crc_r, crc_g, crc_b, lutIdx);
		free(pBuf_read);
	}
    return 0;
}

int vpu_read_lut_new(int lutIdx, int sizeItem, int saddr, int *pData, int twoDatas)
{
    int cmd_op, addr_mode, d16_num, d32_num;
    int temp,i, cnt, size32b, size16b;
    unsigned long timeCnt1,timeCnt2,time_delta;
    cmd_op    = 1; //read
    addr_mode = 0; //incr
    cnt       = 0;
    if(twoDatas) {
        size32b = sizeItem/2;
        size16b = sizeItem&0x1;
        while (size32b) {
            d32_num = (size32b>=4) ? 4 : size32b;  //each 4 operations
            temp = (1<<31)|(cmd_op<<30)|(addr_mode<<28)|(d32_num<<24)| (1<<23)| (lutIdx<<16)| ((saddr<<1)&0xffff);
            Wr(VP_LUT_ADDR_PORT,temp);
            timeCnt1 = OSTimeGet();
            time_delta = 0;
            do {
                temp = Rd(VP_LUT_ADDR_PORT);
                timeCnt2 = OSTimeGet();
                if(timeCnt2 > timeCnt1)
                    time_delta = timeCnt2 - timeCnt1;
                else {
                    timeCnt1 = OSTimeGet();
                    time_delta = 0;
                }
                if(time_delta >= TIME_OUT_VALUE) {
                    LOGE(TAG_VPP,"%s:time out!!\n",__func__);
                    return 1;
                }
            } while(temp&(1<<31));
            for(i=0; i<d32_num; i++)
                pData[cnt++] = Rd(VP_LUT_DATA_PORT);
            size32b  -= d32_num;
            saddr    += d32_num;
        }
        if(size16b) {
            d16_num = 1;
            temp = (1<<31)|(cmd_op<<30)|(addr_mode<<28)|(d16_num<<24)| (0<<23)| (lutIdx<<16)| ((saddr<<1)&0xffff);
            Wr(VP_LUT_ADDR_PORT,temp);
            timeCnt1 = OSTimeGet();
            time_delta = 0;
            do {
                temp = Rd(VP_LUT_ADDR_PORT);
                timeCnt2 = OSTimeGet();
                if(timeCnt2 > timeCnt1)
                    time_delta = timeCnt2 - timeCnt1;
                else {
                    timeCnt1 = OSTimeGet();
                    time_delta = 0;
                }
                if(time_delta >= TIME_OUT_VALUE) {
                    LOGE(TAG_VPP,"%s:time out!!\n",__func__);
                    return 1;
                }
            } while(temp&(1<<31));
            pData[cnt] = Rd(VP_LUT_DATA_PORT) & 0xffff;
        }
    } else {  //twoDatas=0
        size16b = sizeItem;
        while (size16b) {
            d16_num = (size16b>=4) ? 4 : size16b;  //each 4 operations
            temp = (1<<31)|(cmd_op<<30)|(addr_mode<<28)|(d16_num<<24)|(0<<23)|(lutIdx<<16)|(saddr&0xffff);
            Wr(VP_LUT_ADDR_PORT,temp);
            timeCnt1 = OSTimeGet();
            time_delta = 0;
            do {
                temp = Rd(VP_LUT_ADDR_PORT);
                timeCnt2 = OSTimeGet();
                if(timeCnt2 > timeCnt1)
                    time_delta = timeCnt2 - timeCnt1;
                else {
                    timeCnt1 = OSTimeGet();
                    time_delta = 0;
                }
                if(time_delta >= TIME_OUT_VALUE) {
                    LOGE(TAG_VPP,"%s:time out!!\n",__func__);
                    return 1;
                }
            } while(temp&(1<<31));
            for(i=0; i<d16_num; i++)
                pData[cnt++] =  Rd(VP_LUT_DATA_PORT);
            size16b  -= d16_num;
            saddr    += d16_num;
        }
    }
    return 0;
}
#ifdef IN_FBC_MAIN_CONFIG
/*kuka@20140618 add begin*/
vframe_hist_t local_hist;
void vpu_white_patch(void)
{
    unsigned int hist_mode,sum_white_limit_l,sum_white_limit_h,data_white_hist;
    hist_mode = Rd_reg_bits(HIST_CTRL,14,1);//1:32bin mode;0:64bin mode;
    /*if HIST_BLACK_WHITE_VALUE or DNLP_CTRL_XX is changed below should be change too!!*/
    if(hist_mode == 1) {
        sum_white_limit_l = local_hist.gamma[31];
        sum_white_limit_l += local_hist.gamma[30];
        sum_white_limit_l += local_hist.gamma[29];
        sum_white_limit_l += local_hist.gamma[28];
        sum_white_limit_l += local_hist.gamma[27];
        sum_white_limit_h = sum_white_limit_l + local_hist.gamma[26];
    } else {
        sum_white_limit_l = local_hist.gamma[63];
        sum_white_limit_l += local_hist.gamma[62];
        sum_white_limit_l += local_hist.gamma[61];
        sum_white_limit_l += local_hist.gamma[60];
        sum_white_limit_l += local_hist.gamma[59];
        sum_white_limit_l += local_hist.gamma[58];
        sum_white_limit_l += local_hist.gamma[57];
        sum_white_limit_l += local_hist.gamma[56];
        sum_white_limit_l += local_hist.gamma[55];
        sum_white_limit_l += local_hist.gamma[54];
        sum_white_limit_h = sum_white_limit_l + local_hist.gamma[53];
    }
    data_white_hist = 0;
    if(local_hist.gamma[65] >= local_hist.gamma[64]/2)
        data_white_hist = (local_hist.gamma[65] - local_hist.gamma[64]/2)*2;
    if((data_white_hist >= sum_white_limit_l)&&(data_white_hist <= sum_white_limit_h))
        local_hist.gamma[65] = data_white_hist;
    else {
        local_hist.gamma[65] = sum_white_limit_l;
    }
}
void vpu_get_hist_info(void)
{

    // fetch hist info
    //local_hist.luma_sum   = READ_CBUS_REG_BITS(HIST_SPL_VAL,     HIST_LUMA_SUM_BIT,    HIST_LUMA_SUM_WID   );
    local_hist.hist_pow   = Rd_reg_bits(HIST_CTRL, 5, 3);
    local_hist.luma_sum   = Rd(HIST_SPL_VAL);
    //local_hist.chroma_sum = READ_CBUS_REG_BITS(HIST_CHROMA_SUM,  HIST_CHROMA_SUM_BIT,  HIST_CHROMA_SUM_WID );
    local_hist.chroma_sum = Rd(HIST_CHROMA_SUM);
    local_hist.pixel_sum  = Rd_reg_bits(HIST_SPL_PIX_CNT, 0, 22);
    local_hist.height     = Rd_reg_bits(HIST_V_START_END,0,13) -
                            Rd_reg_bits(HIST_V_START_END,16,13)+1;
    local_hist.width      = Rd_reg_bits(HIST_H_START_END,0,13) -
                            Rd_reg_bits(HIST_H_START_END,16,13)+1;
    local_hist.luma_max   = Rd_reg_bits(HIST_MAX_MIN, 8, 8);
    local_hist.luma_min   = Rd_reg_bits(HIST_MAX_MIN, 0, 8);
    local_hist.gamma[0]   = Rd_reg_bits(DNLP_HIST00, 0, 16);
    local_hist.gamma[1]   = Rd_reg_bits(DNLP_HIST00, 16, 16);
    local_hist.gamma[2]   = Rd_reg_bits(DNLP_HIST01, 0, 16);
    local_hist.gamma[3]   = Rd_reg_bits(DNLP_HIST01, 16, 16);
    local_hist.gamma[4]   = Rd_reg_bits(DNLP_HIST02, 0, 16);
    local_hist.gamma[5]   = Rd_reg_bits(DNLP_HIST02, 16, 16);
    local_hist.gamma[6]   = Rd_reg_bits(DNLP_HIST03, 0, 16);
    local_hist.gamma[7]   = Rd_reg_bits(DNLP_HIST03, 16, 16);
    local_hist.gamma[8]   = Rd_reg_bits(DNLP_HIST04, 0, 16);
    local_hist.gamma[9]   = Rd_reg_bits(DNLP_HIST04, 16, 16);
    local_hist.gamma[10]  = Rd_reg_bits(DNLP_HIST05, 0, 16);
    local_hist.gamma[11]  = Rd_reg_bits(DNLP_HIST05, 16, 16);
    local_hist.gamma[12]  = Rd_reg_bits(DNLP_HIST06, 0, 16);
    local_hist.gamma[13]  = Rd_reg_bits(DNLP_HIST06, 16, 16);
    local_hist.gamma[14]  = Rd_reg_bits(DNLP_HIST07, 0, 16);
    local_hist.gamma[15]  = Rd_reg_bits(DNLP_HIST07, 16, 16);
    local_hist.gamma[16]  = Rd_reg_bits(DNLP_HIST08, 0, 16);
    local_hist.gamma[17]  = Rd_reg_bits(DNLP_HIST08, 16, 16);
    local_hist.gamma[18]  = Rd_reg_bits(DNLP_HIST09, 0, 16);
    local_hist.gamma[19]  = Rd_reg_bits(DNLP_HIST09, 16, 16);
    local_hist.gamma[20]  = Rd_reg_bits(DNLP_HIST10, 0, 16);
    local_hist.gamma[21]  = Rd_reg_bits(DNLP_HIST10, 16, 16);
    local_hist.gamma[22]  = Rd_reg_bits(DNLP_HIST11, 0, 16);
    local_hist.gamma[23]  = Rd_reg_bits(DNLP_HIST11, 16, 16);
    local_hist.gamma[24]  = Rd_reg_bits(DNLP_HIST12, 0, 16);
    local_hist.gamma[25]  = Rd_reg_bits(DNLP_HIST12, 16, 16);
    local_hist.gamma[26]  = Rd_reg_bits(DNLP_HIST13, 0, 16);
    local_hist.gamma[27]  = Rd_reg_bits(DNLP_HIST13, 16, 16);
    local_hist.gamma[28]  = Rd_reg_bits(DNLP_HIST14, 0, 16);
    local_hist.gamma[29]  = Rd_reg_bits(DNLP_HIST14, 16, 16);
    local_hist.gamma[30]  = Rd_reg_bits(DNLP_HIST15, 0, 16);
    local_hist.gamma[31]  = Rd_reg_bits(DNLP_HIST15, 16, 16);
    local_hist.gamma[32]  = Rd_reg_bits(DNLP_HIST16, 0, 16);
    local_hist.gamma[33]  = Rd_reg_bits(DNLP_HIST16, 16, 16);
    local_hist.gamma[34]  = Rd_reg_bits(DNLP_HIST17, 0, 16);
    local_hist.gamma[35]  = Rd_reg_bits(DNLP_HIST17, 16, 16);
    local_hist.gamma[36]  = Rd_reg_bits(DNLP_HIST18, 0, 16);
    local_hist.gamma[37]  = Rd_reg_bits(DNLP_HIST18, 16, 16);
    local_hist.gamma[38]  = Rd_reg_bits(DNLP_HIST19, 0, 16);
    local_hist.gamma[39]  = Rd_reg_bits(DNLP_HIST19, 16, 16);
    local_hist.gamma[40]  = Rd_reg_bits(DNLP_HIST20, 0, 16);
    local_hist.gamma[41]  = Rd_reg_bits(DNLP_HIST20, 16, 16);
    local_hist.gamma[42]  = Rd_reg_bits(DNLP_HIST21, 0, 16);
    local_hist.gamma[43]  = Rd_reg_bits(DNLP_HIST21, 16, 16);
    local_hist.gamma[44]  = Rd_reg_bits(DNLP_HIST22, 0, 16);
    local_hist.gamma[45]  = Rd_reg_bits(DNLP_HIST22, 16, 16);
    local_hist.gamma[46]  = Rd_reg_bits(DNLP_HIST23, 0, 16);
    local_hist.gamma[47]  = Rd_reg_bits(DNLP_HIST23, 16, 16);
    local_hist.gamma[48]  = Rd_reg_bits(DNLP_HIST24, 0, 16);
    local_hist.gamma[49]  = Rd_reg_bits(DNLP_HIST24, 16, 16);
    local_hist.gamma[50]  = Rd_reg_bits(DNLP_HIST25, 0, 16);
    local_hist.gamma[51]  = Rd_reg_bits(DNLP_HIST25, 16, 16);
    local_hist.gamma[52]  = Rd_reg_bits(DNLP_HIST26, 0, 16);
    local_hist.gamma[53]  = Rd_reg_bits(DNLP_HIST26, 16, 16);
    local_hist.gamma[54]  = Rd_reg_bits(DNLP_HIST27, 0, 16);
    local_hist.gamma[55]  = Rd_reg_bits(DNLP_HIST27, 16, 16);
    local_hist.gamma[56]  = Rd_reg_bits(DNLP_HIST28, 0, 16);
    local_hist.gamma[57]  = Rd_reg_bits(DNLP_HIST28, 16, 16);
    local_hist.gamma[58]  = Rd_reg_bits(DNLP_HIST29, 0, 16);
    local_hist.gamma[59]  = Rd_reg_bits(DNLP_HIST29, 16, 16);
    local_hist.gamma[60]  = Rd_reg_bits(DNLP_HIST30, 0, 16);
    local_hist.gamma[61]  = Rd_reg_bits(DNLP_HIST30, 16, 16);
    local_hist.gamma[62]  = Rd_reg_bits(DNLP_HIST31, 0, 16);
    local_hist.gamma[63]  = Rd_reg_bits(DNLP_HIST31, 16, 16);
    local_hist.gamma[64]  = Rd_reg_bits(DNLP_HIST32, 0, 16);//black
    local_hist.gamma[65]  = Rd_reg_bits(DNLP_HIST32, 16, 16);//white
    vpu_white_patch();
}

void GetWgtLst(unsigned int *iHst, unsigned int tAvg, unsigned int nLen, unsigned int alpha)
{
    unsigned int iMax=0;
    unsigned int iMin=0;
    unsigned int iPxl=0;
    unsigned int iT=0;

    for(iT=0; iT<nLen; iT++) {
        iPxl = iHst[iT];
        if(iPxl>tAvg) {
            iMax=iPxl;
            iMin=tAvg;
        } else {
            iMax=tAvg;
            iMin=iPxl;
        }

        if(alpha<16) {
            iPxl = ((16-alpha)*iMin+8)>>4;
            iPxl += alpha*iMin;
        } else if(alpha<32) {
            iPxl = (32-alpha)*iMin;
            iPxl += (alpha-16)*iMax;
        } else {
            iPxl = (48-alpha)+4*(alpha-32);
            iPxl *= iMax;
        }

        iPxl = (iPxl+8)>>4;

        iHst[iT] = iPxl<1 ? 1 : iPxl;
    }
}

static int dnlp_respond = 0;
static int dnlp_debug = 0;
static unsigned char dnlp_adj_level;
static unsigned char ve_dnlp_cliprate;
static unsigned char ve_dnlp_lowrange;
static unsigned char ve_dnlp_hghrange;
static unsigned char ve_dnlp_lowalpha;
static unsigned char ve_dnlp_midalpha;
static unsigned char ve_dnlp_hghalpha;

unsigned int ve_dnlp_luma_sum;
unsigned int ve_dnlp_rt = 0;
static unsigned char ve_dnlp_tgt[64];
static unsigned int ve_dnlp_lpf[64], ve_dnlp_reg[16];

void init_dnlp_para(void)
{
    dnlp_adj_level   = vpu_config_table.dnlp.adj_level;
    ve_dnlp_cliprate = vpu_config_table.dnlp.cliprate;
    ve_dnlp_lowrange = vpu_config_table.dnlp.lowrange;
    ve_dnlp_hghrange = vpu_config_table.dnlp.hghrange;
    ve_dnlp_lowalpha = vpu_config_table.dnlp.lowalpha;
    ve_dnlp_midalpha = vpu_config_table.dnlp.midalpha;
    ve_dnlp_hghalpha = vpu_config_table.dnlp.hghalpha;
    Wr_reg_bits(HIST_CTRL,vpu_config_table.dnlp.hist_ctrl,0,22);
}


static void ve_dnlp_calculate_tgtx(void)
{
    //struct vframe_hist_t *p = &local_hist;
    unsigned int iHst[64];
    unsigned int oHst[64];
    static unsigned int sum_b = 0, sum_c = 0;
    unsigned int i = 0, j = 0, sum = 0, max = 0;
    unsigned int cLmt=0, nStp=0, stp=0, uLmt=0;
    long nExc=0;

    unsigned char clip_rate = ve_dnlp_cliprate; //8bit
    unsigned char low_range = ve_dnlp_lowrange;//18; //6bit [0-54]
    unsigned char hgh_range = ve_dnlp_hghrange;//18; //6bit [0-54]
    unsigned char low_alpha = ve_dnlp_lowalpha;//24; //6bit [0--48]
    unsigned char mid_alpha = ve_dnlp_midalpha;//24; //6bit [0--48]
    unsigned char hgh_alpha = ve_dnlp_hghalpha;//24; //6bit [0--48]
    //-------------------------------------------------
    unsigned int tAvg=0;
    unsigned int nPnt=0;
    unsigned int mRng=0;


    // old historic luma sum
    sum_b = sum_c;
    sum_c = ve_dnlp_luma_sum;
    // new historic luma sum
    ve_dnlp_luma_sum = local_hist.luma_sum;
    if(dnlp_debug)
        ;//printk("ve_dnlp_luma_sum=%x,sum_b=%x,sum_c=%x\n",ve_dnlp_luma_sum,sum_b,sum_c);

    // picture mode: freeze dnlp curve
    if(dnlp_respond) {
        if (// new luma sum is 0, something is wrong, freeze dnlp curve
            (!ve_dnlp_luma_sum)
        )
            return;
    } else {
        if (// new luma sum is 0, something is wrong, freeze dnlp curve
            (!ve_dnlp_luma_sum) ||
            // new luma sum is closed to old one (1 +/- 1/64), picture mode, freeze curve
            ((ve_dnlp_luma_sum < sum_b + (sum_b >> dnlp_adj_level)) &&
             (ve_dnlp_luma_sum > sum_b - (sum_b >> dnlp_adj_level))
            )
        )
            return;
    }

    // 64 bins, max, ave
    for (i = 0; i < 64; i++) {
        iHst[i] = (unsigned int)local_hist.gamma[i];

        if(i>=4 && i<=58) { //55 bins
            oHst[i] = iHst[i];

            if (max < iHst[i])
                max = iHst[i];
            sum += iHst[i];
        } else {
            oHst[i] = 0;
        }
    }
    cLmt = (clip_rate*sum)>>8;
    tAvg = sum/55;


    // invalid histgram: freeze dnlp curve
    if (max<=55)
        return;

    // get 1st 4 points
    for (i = 4; i <= 58; i++) {
        if(iHst[i]>cLmt)
            nExc += (iHst[i]-cLmt);
    }
    nStp = (nExc+28)/55;
    uLmt = cLmt-nStp;

    if(clip_rate<=4 || tAvg<=2) {
        cLmt = (sum+28)/55;
        sum = cLmt*55;

        for(i=4; i<=58; i++) {
            oHst[i] = cLmt;
        }
    } else if(nStp!=0) {
        for(i=4; i<=58; i++) {
            if(iHst[i]>=cLmt)
                oHst[i] = cLmt;
            else {
                if(iHst[i]>uLmt) {
                    oHst[i] = cLmt;
                    nExc -= cLmt-iHst[i];
                } else {
                    oHst[i] = iHst[i]+nStp;
                    nExc -= nStp;
                }
                if(nExc<0 )
                    nExc = 0;
            }
        }

        j=4;
        while(nExc>0) {
            if(nExc>=55) {
                nStp = 1;
                stp = nExc/55;
            } else {
                nStp = 55/nExc;
                stp = 1;
            }
            for(i=j; i<=58; i+=nStp) {
                if(oHst[i]<cLmt) {
                    oHst[i] += stp;
                    nExc -= stp;
                }
                if(nExc<=0)
                    break;
            }
            j += 1;
            if(j>58)
                break;
        }
    }
    if(low_range==0 && hgh_range==0)
        nPnt = 0;
    else {
        if(low_range==0 || hgh_range==0) {
            nPnt = 1;
            mRng = (hgh_range>low_range ? hgh_range : low_range); //max
        } else if(low_range+hgh_range>=54) {
            nPnt = 1;
            mRng = (hgh_range<low_range ? hgh_range : low_range); //min
        } else
            nPnt = 2;
    }
    if(nPnt==0 && low_alpha>=16 && low_alpha<=32) {
        sum = 0;
        for(i=5; i<=59; i++) {
            j = oHst[i]*(32-low_alpha)+tAvg*(low_alpha-16);
            j = (j+8)>>4;
            oHst[i] = j;
            sum += j;
        }
    } else if(nPnt==1) {
        GetWgtLst(oHst+4, tAvg, mRng, low_alpha);
        GetWgtLst(oHst+4+mRng, tAvg, 54-mRng, hgh_alpha);
    } else if(nPnt==2) {
        mRng = 55-(low_range+hgh_range);
        GetWgtLst(oHst+4, tAvg, low_range, low_alpha);
        GetWgtLst(oHst+4+low_range, tAvg, mRng, mid_alpha);
        GetWgtLst(oHst+4+mRng+low_range, tAvg, hgh_range, hgh_alpha);
    }
    sum=0;
    for(i=4; i<=58; i++) {
        if(oHst[i]>cLmt)
            oHst[i] = cLmt;
        sum += oHst[i];
    }

    nStp = 0;
    //sum -= oHst[4];
    for(i=5; i<=59; i++) { //5,59
        nStp += oHst[i-1];
        //nStp += oHst[i];

        j = (236-16)*nStp;
        j += (sum>>1);
        j /= sum;

        ve_dnlp_tgt[i] = j + 16;
        //LOGD(TAG_VPP, "[vpp.c]ve_dnlp_tgt[%d]=%x\n",i,ve_dnlp_tgt[i]);
    }
    return;
}

static void ve_dnlp_calculate_lpf(void) // lpf[0] is always 0 & no need calculation
{
    unsigned int i = 0;

    for (i = 0; i < 64; i++) {
        ve_dnlp_lpf[i] = ve_dnlp_lpf[i] - (ve_dnlp_lpf[i] >> ve_dnlp_rt) + ve_dnlp_tgt[i];
    }
}

static void ve_dnlp_calculate_reg(void)
{
    unsigned int i = 0, j = 0, cur = 0, data = 0, offset = ve_dnlp_rt ? (1 << (ve_dnlp_rt - 1)) : 0;

    for (i = 0; i < 16; i++) {
        ve_dnlp_reg[i] = 0;
        cur = i << 2;
        for (j = 0; j < 4; j++) {
            data = (ve_dnlp_lpf[cur + j] + offset) >> ve_dnlp_rt;
            if (data > 255)
                data = 255;
            ve_dnlp_reg[i] |= data << (j << 3);
        }
    }
}

static void ve_dnlp_load_reg(void)
{
    Wr(DNLP_CTRL_00, ve_dnlp_reg[0]);
    Wr(DNLP_CTRL_01, ve_dnlp_reg[1]);
    Wr(DNLP_CTRL_02, ve_dnlp_reg[2]);
    Wr(DNLP_CTRL_03, ve_dnlp_reg[3]);
    Wr(DNLP_CTRL_04, ve_dnlp_reg[4]);
    Wr(DNLP_CTRL_05, ve_dnlp_reg[5]);
    Wr(DNLP_CTRL_06, ve_dnlp_reg[6]);
    Wr(DNLP_CTRL_07, ve_dnlp_reg[7]);
    Wr(DNLP_CTRL_08, ve_dnlp_reg[8]);
    Wr(DNLP_CTRL_09, ve_dnlp_reg[9]);
    Wr(DNLP_CTRL_10, ve_dnlp_reg[10]);
    Wr(DNLP_CTRL_11, ve_dnlp_reg[11]);
    Wr(DNLP_CTRL_12, ve_dnlp_reg[12]);
    Wr(DNLP_CTRL_13, ve_dnlp_reg[13]);
    Wr(DNLP_CTRL_14, ve_dnlp_reg[14]);
    Wr(DNLP_CTRL_15, ve_dnlp_reg[15]);
}

void ve_dnlp_cal(void)
{
    unsigned int i = 0;
    ve_dnlp_luma_sum = 0;
    // init tgt & lpf
    for (i = 0; i < 64; i++) {
        ve_dnlp_tgt[i] = i << 2;
        ve_dnlp_lpf[i] = ve_dnlp_tgt[i] << ve_dnlp_rt;
    }
    ve_dnlp_calculate_tgtx();
    ve_dnlp_calculate_lpf();
    ve_dnlp_calculate_reg();
    ve_dnlp_load_reg();
}

void set_dnlp_parm(int param1, int param2)
{
    LOGD(TAG_VPP, "[VPU_UTIL.C] param1=%x,param2=%x\n",param1,param2);
    ve_dnlp_cliprate = (param1&0x00ff0000) >> 16;
    ve_dnlp_hghrange = (param1&0x0000ff00) >> 8;
    ve_dnlp_lowrange = (param1&0x000000ff) >> 0;
    ve_dnlp_hghalpha = (param2&0xff000000) >> 24;
    ve_dnlp_midalpha = (param2&0x00ff0000) >> 16;
    ve_dnlp_lowalpha = (param2&0x0000ff00) >> 8;
    dnlp_adj_level   = (param2&0x000000ff) >> 0;
}

void get_dnlp_parm(void)
{
    unsigned int data1,data2;
    data1 = (ve_dnlp_cliprate << 16) |
            (ve_dnlp_hghrange << 8)  |
            (ve_dnlp_lowrange << 0);
    data2 = (ve_dnlp_hghalpha << 24) |
            (ve_dnlp_midalpha << 16) |
            (ve_dnlp_lowalpha << 8)  |
            (dnlp_adj_level   << 0);
    printf("dnlp:0x%x 0x%x\n",data1,data2);
}
void vpu_get_gamma_lut_pq(int Idx, int *pBuf, int sizeItem)
{
    int lutIdx;
    lutIdx = 0x00|Idx;
    vpu_read_lut_new (lutIdx,sizeItem,0,pBuf,0); //each 1 10bits items
}
void vpu_get_gamma_lut(int Idx, int *pBuf, int sizeItem)
{
    int lutIdx;
    lutIdx = 0x00|Idx;
    vpu_read_lut_new (lutIdx,sizeItem,0,pBuf,1); //each 2 10bits items
}
void vpu_set_gamma_lut(int Idx, int *pBuf, int sizeItem)
{
    int lutIdx;
    lutIdx = 0x00|Idx;
    if(vpu_write_lut_new (lutIdx,sizeItem,0,pBuf,0) == 1) //each 1 10bits items
        LOGE(TAG_VPP,"%s:time out!!\n",__func__);
}

void enable_output(int enable)
{
    Wr_reg_bits(VP_CTRL,enable,14,1);    // set reg_vx1lvds_en  = 1
}
void enable_timgen(int enable)
{
    Wr_reg_bits(VP_CTRL,enable,1,1);    // set tmgen  = 1
}
void enable_backlight(int enable)
{
    if(enable) {
        Wr_reg_bits(PREG_PAD_GPIO3_EN_N, 0, 12, 1);

        Wr_reg_bits(PREG_PAD_GPIO3_O, 0, 12, 1);
    } else {
        Wr_reg_bits(PREG_PAD_GPIO3_EN_N, 0, 12, 1);

        Wr_reg_bits(PREG_PAD_GPIO3_O, 1, 12, 1);
    }


    /*
        unsigned int data,i,port;
        //pwm0 1 2 & 3d
        for(i = 0;i < 5;i++){
            port = VPU_PWM0_V0 + i*8;
            if(i == 3)
                port = VPU_3DSYNC_CTRL;
            if(i == 4)
                port = VPU_3DGLS_CTRL;
            Wr(VP_PWM_ADDR_PORT,port);
            data = Rd(VP_PWM_DATA_PORT);
            Wr(VP_PWM_ADDR_PORT,port);
            if((enable&0x1) == 1){
                if((port == VPU_3DSYNC_CTRL)||(port == VPU_3DGLS_CTRL))
                    Wr(VP_PWM_DATA_PORT,data|(1 << 31));
                else
                    Wr(VP_PWM_DATA_PORT,data|(1 << 30));
            }else{
                if((port == VPU_3DSYNC_CTRL)||(port == VPU_3DGLS_CTRL))
                    Wr(VP_PWM_DATA_PORT,data&(0 << 31));
                else
                    Wr(VP_PWM_DATA_PORT,data&(0 << 30));
            }
        }
    */
}
void vpu_backlight_adj(unsigned int val_ui,vpu_timing_t timing)
{
    if(val_ui > FBC_BACKLIGHT_RANGE_UI)
        return;

    unsigned int val_v_reg,val_h_reg,val_v_range;
    unsigned int i,data;

    if(panel_param->pwm_hz == 60) {
        if(panel_param->bl_inverter) {
            val_v_reg = (timing_table[timing].vtotal*(FBC_BACKLIGHT_RANGE_UI-val_ui)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = (timing_table[timing].vtotal*val_ui/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
        val_h_reg = (timing_table[timing].htotal/2 -1)<< 16;//one clock two pixels
    } else if (panel_param->pwm_hz == 120) {
        if(panel_param->bl_inverter) {
            val_v_reg = ((timing_table[timing].vtotal/2-1)*(FBC_BACKLIGHT_RANGE_UI-val_ui)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = ((timing_table[timing].vtotal/2-1)*val_ui/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
		val_v_range = timing_table[timing].vtotal/2;
        val_h_reg = (timing_table[timing].htotal/2 -1)<< 16;//one clock two pixels
    } else if (panel_param->pwm_hz == 240) {
        if(panel_param->bl_inverter) {
            val_v_reg = ((timing_table[timing].vtotal/4-1)*(FBC_BACKLIGHT_RANGE_UI-val_ui)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = ((timing_table[timing].vtotal/4-1)*val_ui/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
		val_v_range = timing_table[timing].vtotal/4;
        val_h_reg = (timing_table[timing].htotal/2 -1)<< 16;//one clock two pixels
    } else {
        if(panel_param->bl_inverter) {
            val_v_reg = (timing_table[timing].vtotal*(FBC_BACKLIGHT_RANGE_UI-val_ui)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = (timing_table[timing].vtotal*val_ui/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
        val_h_reg = (timing_table[timing].htotal/2 -1)<< 16;//one clock two pixels
    }


    for(i = 0; i < 3; i++) { //pwm0/1/2
        if (panel_param->pwm_hz == 60) {

            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0 );
            Wr(VP_PWM_DATA_PORT,val_v_reg);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
        } else if (panel_param->pwm_hz == 120) {

            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0 );
            Wr(VP_PWM_DATA_PORT,val_v_reg);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1 + i*8);
            Wr(VP_PWM_DATA_PORT,val_v_reg+((val_v_range<<16)|val_v_range));
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);

        } else if(panel_param->pwm_hz == 240) {
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0 );
            Wr(VP_PWM_DATA_PORT,val_v_reg);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1 + i*8);
            Wr(VP_PWM_DATA_PORT,val_v_reg+((val_v_range<<16)|val_v_range));
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2 + i*8);
            Wr(VP_PWM_DATA_PORT,val_v_reg+(((2*val_v_range)<<16)|(2*val_v_range)));
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3 + i*8);
            Wr(VP_PWM_DATA_PORT,val_v_reg+(((3*val_v_range)<<16)|(3*val_v_range)));

        } else { //default 60
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0 );
            Wr(VP_PWM_DATA_PORT,val_v_reg);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
        }

    }
    data = ((timing_table[timing].vtotal-1) << 16)|(timing_table[timing].htotal/2 - 1);
    Wr(VP_PWM_ADDR_PORT,VPU_PWM_HVSIZE_M1);
    Wr(VP_PWM_DATA_PORT,data);
    //for 3d reserved
}

/*
bri_ui:0~255
*/
void vpu_bri_adj(unsigned int bri_ui)
{
    int bri_reg;
    if(bri_ui > FBC_BRI_RANGE_UI)
        return;
    bri_reg = 2047*bri_ui/FBC_BRI_RANGE_UI - 1024;
    Wr_reg_bits(VP_BST,bri_reg&0x7ff,16,11);
}
void vpu_con_adj(unsigned int con_ui)
{
    int con_reg;
    if(con_ui > FBC_CON_RANGE_UI)
        return;
    con_reg = 511*con_ui/FBC_CON_RANGE_UI;
    Wr_reg_bits(VP_BST,con_reg&0x3ff,0,9);
}
void vpu_wb_gain_r(unsigned int gain_ui)
{
	int val_reg;
	if(gain_ui<=128){
		val_reg = 1024*gain_ui/128;
	}else {
		val_reg = (2047-1024)*(gain_ui-128)/(FBC_WB_GAIN_RANGE_UI-128)+1024;
	}
    //int val_reg = 2047*gain_ui/FBC_WB_GAIN_RANGE_UI;
    if(gain_ui > FBC_WB_GAIN_RANGE_UI)
        return;
    Wr_reg_bits(VP_WB_GAIN01,val_reg&0x7ff,16,11);
}

void vpu_wb_gain_g(unsigned int gain_ui)
{
	int val_reg;
	if(gain_ui<=128){
		val_reg = 1024*gain_ui/128;
	}else {
		val_reg = (2047-1024)*(gain_ui-128)/(FBC_WB_GAIN_RANGE_UI-128)+1024;
	}
    //int val_reg = 2047*gain_ui/FBC_WB_GAIN_RANGE_UI;
    if(gain_ui > FBC_WB_GAIN_RANGE_UI)
        return;
    Wr_reg_bits(VP_WB_GAIN01,val_reg&0x7ff,0,11);
}

void vpu_wb_gain_b(unsigned int gain_ui)
{
	int val_reg;
	if(gain_ui<=128){
		val_reg = 1024*gain_ui/128;
	}else {
		val_reg = (2047-1024)*(gain_ui-128)/(FBC_WB_GAIN_RANGE_UI-128)+1024;
	}
    //int val_reg = 2047*gain_ui/FBC_WB_GAIN_RANGE_UI;
    if(gain_ui > FBC_WB_GAIN_RANGE_UI)
        return;
    Wr_reg_bits(VP_WB_GAIN2_PRE_OFF0,val_reg&0x7ff,16,11);
}

void vpu_wb_preoffset_r(unsigned int offset_ui)
{
	int val_reg;
	if (WB_DATA_FROM_DB)
		{
			if(offset_ui<=128){
				val_reg = 1024*offset_ui/128-1204;
			}else {
				val_reg = (2047-1024)*(offset_ui-128)/(FBC_WB_GAIN_RANGE_UI-128);
			}
		} else {
		    val_reg = offset_ui - 128;
		}
    //int val_reg = 2047*offset_ui/FBC_WB_GAIN_RANGE_UI-1024;
    if(offset_ui > FBC_WB_GAIN_RANGE_UI)
        return;
    Wr_reg_bits(VP_WB_GAIN2_PRE_OFF0,val_reg&0x7ff,0,11);
}

void vpu_wb_preoffset_g(unsigned int offset_ui)
{
	int val_reg;
	if (WB_DATA_FROM_DB)
		{
			if(offset_ui<=128){
				val_reg = 1024*offset_ui/128-1024;
			}else {
				val_reg = (2047-1024)*(offset_ui-128)/(FBC_WB_GAIN_RANGE_UI-128);
			}
		} else {
		     val_reg = offset_ui - 128;
        }
    //int val_reg = 2047*offset_ui/FBC_WB_GAIN_RANGE_UI-1024;
    if(offset_ui > FBC_WB_GAIN_RANGE_UI)
        return;
    Wr_reg_bits(VP_WB_PRE_OFF12,val_reg&0x7ff,16,11);
}

void vpu_wb_preoffset_b(unsigned int offset_ui)
{
	int val_reg;
	if (WB_DATA_FROM_DB)
		{
			if(offset_ui<=128){
				val_reg = 1024*offset_ui/128-1024;
			}else {
				val_reg = (2047-1024)*(offset_ui-128)/(FBC_WB_GAIN_RANGE_UI-128);
			}
		} else {
		     val_reg = offset_ui - 128;
		}
    //int val_reg = 2047*offset_u/FBC_WB_GAIN_RANGE_UI-1024;
    if(offset_ui > FBC_WB_GAIN_RANGE_UI)
        return;
    Wr_reg_bits(VP_WB_PRE_OFF12,val_reg&0x7ff,0,11);
}


//gain_ui:0~255
void vpu_wb_gain_adj(unsigned int gain_ui,vpu_wbsel_t rgb_sel)
{
	int val_reg;
	if(gain_ui<=128){
		val_reg = 1024*gain_ui/128;
	}else {
		val_reg = (2047-1024)*(gain_ui-128)/(FBC_WB_GAIN_RANGE_UI-128)+1024;
	}
   // int val_reg = 2047*gain_ui/FBC_WB_GAIN_RANGE_UI;
    if(gain_ui > FBC_WB_GAIN_RANGE_UI)
        return;
    if(rgb_sel == WBSEL_R)
        Wr_reg_bits(VP_WB_GAIN01,val_reg&0x7ff,16,11);
    else if(rgb_sel == WBSEL_G)
        Wr_reg_bits(VP_WB_GAIN01,val_reg&0x7ff,0,11);
    else if(rgb_sel == WBSEL_B)
        Wr_reg_bits(VP_WB_GAIN2_PRE_OFF0,val_reg&0x7ff,16,11);
    else
        LOGE(TAG_VPP, "[VPU_UTIL.C] vpu_wb_gain_adj\n");
}
//offset_ui:0~255
void vpu_wb_offset_adj(int offset_ui,vpu_wbsel_t rgb_sel,vpu_wboffset_pos_t pre_post)
{
	int val_reg;
	if (WB_DATA_FROM_DB)
		{
			if(offset_ui<=128){
				val_reg = 1024*offset_ui/128-1024;
			}else {
				val_reg = (2047-1024)*(offset_ui-128)/(FBC_WB_GAIN_RANGE_UI-128);
			}
		} else {
			val_reg = offset_ui - 128;
		}
    //int val_reg = 2047*offset_ui/FBC_WB_OFFSET_RANGE_UI - 1024;
    if(offset_ui > FBC_WB_OFFSET_RANGE_UI)
        return;
    if(pre_post == WBOFFSET_PRE) {
        if(rgb_sel == WBSEL_R)
            Wr_reg_bits(VP_WB_GAIN2_PRE_OFF0,val_reg&0x7ff,0,11);
        else if(rgb_sel == WBSEL_G)
            Wr_reg_bits(VP_WB_PRE_OFF12,val_reg&0x7ff,16,11);
        else if(rgb_sel == WBSEL_B)
            Wr_reg_bits(VP_WB_PRE_OFF12,val_reg&0x7ff,0,11);
        else
            LOGE(TAG_VPP, "[VPU_UTIL.C] vpu_wb_offset_adj\n");
    } else if(pre_post == WBOFFSET_POST) {
        if(rgb_sel == WBSEL_R)
            Wr_reg_bits(VP_WB_OFF01,val_reg&0x7ff,16,11);
        else if(rgb_sel == WBSEL_G)
            Wr_reg_bits(VP_WB_OFF01,val_reg&0x7ff,0,11);
        else if(rgb_sel == WBSEL_B)
            Wr_reg_bits(VP_WB_OFF2,val_reg&0x7ff,0,11);
        else
            LOGE(TAG_VPP, "[VPU_UTIL.C] vpu_wb_offset_adj\n");
    }
}
void vpu_saturation_adj(unsigned int val_ui)
{
    unsigned int val_reg,data;
    if(val_ui > FBC_SAT_RANGE_UI)
        return;
    val_reg = (val_ui*4095/FBC_SAT_RANGE_UI)&0xfff;
    Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
    data = Rd(VP_CM2_DATA_PORT)&0xfff;
    Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
    Wr(VP_CM2_DATA_PORT,  ((val_reg<<16) | data));

}
void vpu_hue_adj(unsigned int val_ui)
{
    unsigned int val_reg,data;
    if(val_ui > FBC_HUE_RANGE_UI)
        return;
    val_reg = (val_ui*4095/FBC_HUE_RANGE_UI)&0xfff;
    Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
    data = (Rd(VP_CM2_DATA_PORT)>>16)&0xfff;
    Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
    Wr(VP_CM2_DATA_PORT,  (val_reg | (data<<16)));

}

void vpu_picmod_adj(vpu_picmod_t val_ui)
{
    if(val_ui >= PICMOD_MAX)
        return;
    fbc_adj_bri(picmod_table[val_ui].bright);
    fbc_adj_con(picmod_table[val_ui].contrast);
    fbc_adj_sat(picmod_table[val_ui].saturation);
}
void vpu_colortemp_adj(vpu_colortemp_t val_ui)
{
    if(val_ui >= COLOR_TEMP_MAX)
        return;
    vpu_wb_gain_adj(colortemp_table[val_ui].wb_param.gain_r,WBSEL_R);
    vpu_wb_gain_adj(colortemp_table[val_ui].wb_param.gain_g,WBSEL_G);
    vpu_wb_gain_adj(colortemp_table[val_ui].wb_param.gain_b,WBSEL_B);
    vpu_wb_offset_adj(colortemp_table[val_ui].wb_param.pre_offset_r,WBSEL_R,WBOFFSET_PRE);
    vpu_wb_offset_adj(colortemp_table[val_ui].wb_param.pre_offset_g,WBSEL_G,WBOFFSET_PRE);
    vpu_wb_offset_adj(colortemp_table[val_ui].wb_param.pre_offset_b,WBSEL_B,WBOFFSET_PRE);
    vpu_wb_offset_adj(colortemp_table[val_ui].wb_param.post_offset_r,WBSEL_R,WBOFFSET_POST);
    vpu_wb_offset_adj(colortemp_table[val_ui].wb_param.post_offset_g,WBSEL_G,WBOFFSET_POST);
    vpu_wb_offset_adj(colortemp_table[val_ui].wb_param.post_offset_b,WBSEL_B,WBOFFSET_POST);
}
#endif
void vpu_color_bar_mode(void)
{
    unsigned int h_cal,v_cal;
    h_cal = ((1 << 15)*10/timing_table[timing_cur].hactive + 5)/10;
    v_cal = ((1 << 15)*10/timing_table[timing_cur].vactive +5)/10;
    Wr_reg_bits(VP_PAT_XY_MODE,0,5,3);
    Wr_reg_bits(VP_PAT_XY_SCL,v_cal,0,12);
    Wr_reg_bits(VP_PAT_XY_SCL,h_cal,16,12);
}
void vpu_patgen_bar_set(unsigned int r_val,unsigned int g_val,unsigned int b_val)
{
    unsigned int r_reg,g_reg,b_reg;
    r_reg = r_val&0xff;
    r_reg = r_reg | (r_reg << 8) | (r_reg << 16) | (r_reg << 24);
    g_reg = g_val&0xff;
    g_reg = g_reg | (g_reg << 8) | (g_reg << 16) | (g_reg << 24);
    b_reg = b_val&0xff;
    b_reg = b_reg | (b_reg << 8) | (b_reg << 16) | (b_reg << 24);
    Wr(VP_PAT_BAR_R_0_3,r_reg);
    Wr(VP_PAT_BAR_R_4_7,r_reg);
    Wr(VP_PAT_BAR_R_8_11,r_reg);
    Wr(VP_PAT_BAR_R_12_15,r_reg);

    Wr(VP_PAT_BAR_G_0_3,g_reg);
    Wr(VP_PAT_BAR_G_4_7,g_reg);
    Wr(VP_PAT_BAR_G_8_11,g_reg);
    Wr(VP_PAT_BAR_G_12_15,g_reg);

    Wr(VP_PAT_BAR_B_0_3,b_reg);
    Wr(VP_PAT_BAR_B_4_7,b_reg);
    Wr(VP_PAT_BAR_B_8_11,b_reg);
    Wr(VP_PAT_BAR_B_12_15,b_reg);
}
void vpu_testpat_def(void)
{
    Wr_reg_bits(VP_CTRL,0,19,9);
    Wr_reg_bits(VP_PAT_3D_MOD,0,0,5);
    Wr_reg_bits(VP_PAT_3D_MOD,10,8,12);
    Wr(VP_PAT_3D_XY_MID,0x3c0021c);//??
    Wr(VP_PAT_XY_MODE,0x2c);
    Wr(VP_PAT_XY_SCL,0x22003c);
    Wr(VP_PAT_XY_OF_SHFT,0);
    Wr(VP_PAT_XRMP_SCL,0xffffff);
    Wr(VP_PAT_YRMP_SCL,0xffffff);

    Wr(VP_PAT_BAR_R_0_3,0xffff0000);
    Wr(VP_PAT_BAR_R_4_7,0xffff0000);
    Wr(VP_PAT_BAR_R_8_11,0x20406080);
    Wr(VP_PAT_BAR_R_12_15,0xa0c0e0ff);

    Wr(VP_PAT_BAR_G_0_3,0xffffffff);
    Wr(VP_PAT_BAR_G_4_7,0);
    Wr(VP_PAT_BAR_G_8_11,0x20406080);
    Wr(VP_PAT_BAR_G_12_15,0xa0c0e0ff);

    Wr(VP_PAT_BAR_B_0_3,0xff00ff00);
    Wr(VP_PAT_BAR_B_4_7,0xff00ff00);
    Wr(VP_PAT_BAR_B_8_11,0x20406080);
    Wr(VP_PAT_BAR_B_12_15,0xa0c0e0ff);

    Wr(VP_GRD9_XY_SZ,0xe70082);
    Wr(VP_GRD9_XY_ST0,0x620037);
    Wr(VP_GRD9_XY_ST1,0x34d01db);
    Wr(VP_GRD9_XY_ST2,0x637037f);

    Wr(VP_GRY8_XY_SZ,0xc0006c);
    Wr(VP_GRY8_XY_ST0,0x24000d8);
    Wr(VP_GRY8_XY_ST1,0x24002f4);

    Wr(VP_CIR15_RAD,0xf0);
    Wr(VP_CIR15_SQ_RAD,0xe10);
    Wr(VP_CIR15_X01,0xbe023a);
    Wr(VP_CIR15_X23,0x3c0053c);
    Wr(VP_CIR15_X4_Y0,0x6b800be);
    Wr(VP_CIR15_Y12,0x21c0384);
    Wr(VP_TRI_CTRL,0xe370000);
}
extern vpu_srcif_mode_t srcif_mode;

vpu_srcif_mode_t vpu_get_srcif_mode(void)
{
    return srcif_mode;
}

void vpu_set_color_surge(unsigned int mode, vpu_timing_t timing_cur)
{
	unsigned int data,reg,data1;
    if (mode) {
       reg = timing_table[timing_cur].hactive/2;
       data = timing_table[timing_cur].vactive;
       Wr(VP_CM2_ADDR_PORT, ROI_X_SCOPE_REG);
	   Wr(VP_CM2_DATA_PORT,  ((reg<<16) | data));

       Wr(VP_CM2_ADDR_PORT, IFO_MODE_REG);
       data1 = Rd(VP_CM2_DATA_PORT)|0x1;
       Wr(VP_CM2_ADDR_PORT, IFO_MODE_REG);
       Wr(VP_CM2_DATA_PORT, data1);
    } else {
       reg = timing_table[timing_cur].hactive;
       data = timing_table[timing_cur].vactive;
       Wr(VP_CM2_ADDR_PORT, ROI_X_SCOPE_REG);
       Wr(VP_CM2_DATA_PORT,  ((reg<<16) | data));

       Wr(VP_CM2_ADDR_PORT, IFO_MODE_REG);
       data1 = Rd(VP_CM2_DATA_PORT)&(~(0x1));
       Wr(VP_CM2_ADDR_PORT, IFO_MODE_REG);
       Wr(VP_CM2_DATA_PORT, data1);
    }
}

#ifdef IN_FBC_MAIN_CONFIG
extern int panel_id;
void vpu_set_projectID(unsigned int pid)
{
    panel_id = pid;
}
void vpu_whitebalance_init(void)
{
    enable_wb(1);//tmp setting
}
int vpu_whitebalance_status(void)
{
    int enable,bypass;
    enable = Rd_reg_bits(VP_CTRL,4,1);    //enable
    bypass = Rd_reg_bits(VP_BYPASS_CTRL,2,1);    //bypass
    if(enable&(!bypass))
        return 1;
    else
        return 0;
}
void vpu_timing_change_process(void)
{
    int dm_res_sel,hsize,vsize;
    hsize = timing_table[timing_cur].hactive;
    vsize = timing_table[timing_cur].vactive;
    vclk_set_encl_lvds(timing_cur,LVDS_PORTS);
    vpu_initial(hsize,vsize);
    dnlp_config(hsize,vsize,1,1,1); //dnlp_en=1; hist_win_en=1;luma_hist_spl_en=1;
    //cm2
    Wr(VP_CM2_DATA_PORT, (((vsize&0x1fff)<<16)|((hsize&0x1fff))));
    if(timing_cur ==  TIMING_1366x768P60)
        dm_res_sel =  0;
    if((timing_cur >=  TIMING_1920x1080P50)&&(timing_cur <=  TIMING_1920x1080P120_3D_SG))
        dm_res_sel =  1;
    else if((timing_cur >=  TIMING_3840x2160P60)&&(timing_cur <=  TIMING_3840x2160P30))
        dm_res_sel =  2;
    else if((timing_cur >=  TIMING_4kx1kP120_3D_SG)&&(timing_cur <=  TIMING_4kxd5kP240_3D_SG))
        dm_res_sel =  4;
    else {
        dm_res_sel =  1;
        LOGI(TAG_VPP, "unsupported video format!\n");
    }
    enable_demura(2);
}

/*sel:0-->default;1-->black*/
void vpu_csc_config(unsigned int sel)
{
	if (sel == 0) {
		Wr(VP_CSC1_OFF_INP01,	0x07c00600);
		Wr(VP_CSC1_OFF_INP2,	0x00000600);
		Wr(VP_CSC1_MTRX_00_01,0x00950000);
		Wr(VP_CSC1_MTRX_02_10,0x00cc0095);
		Wr(VP_CSC1_MTRX_11_12,0x03ce0398);
		Wr(VP_CSC1_MTRX_20_21,0x00950102);
		Wr(VP_CSC1_MTRX_22_OFF_OUP0,0x00000000);
		Wr(VP_CSC1_OFF_OUP12,0x38000000);
	} else if (sel == 1) {
		Wr(VP_CSC1_OFF_INP01,	0x00000000);
		Wr(VP_CSC1_OFF_INP2,	0x00000000);
		Wr(VP_CSC1_MTRX_00_01,0x00000000);
		Wr(VP_CSC1_MTRX_02_10,0x00000000);
		Wr(VP_CSC1_MTRX_11_12,0x00000000);
		Wr(VP_CSC1_MTRX_20_21,0x00000000);
		Wr(VP_CSC1_MTRX_22_OFF_OUP0,0x00000000);
		Wr(VP_CSC1_OFF_OUP12,0x00000000);
	}
}

extern int csc_config;
void vpu_csc_config_ext(unsigned int sel)
{
	csc_config = sel;
}
extern void SRCIF_FSM_STATE_Handle(void *arg);
void vpu_srcif_debug(unsigned int mode,unsigned int mux)
{
    srcif_mode = mode;
    int ret = -2;
    LOGD(TAG_VPP, "%s: mode:%d;mux:%d\n",__func__,mode,mux);
    switch(srcif_mode) {
    case SRCIF_PURE_HARDWARE://pure hardware mode
        srcif_fsm_init();
        if((timing_cur >= TIMING_1920x1080P50)&&(timing_cur <= TIMING_1920x1080P120_3D_SG))
            srcif_tmg_on(0);
        else if((timing_cur >= TIMING_3840x2160P60)&&(timing_cur <= TIMING_4kxd5kP240_3D_SG))
            srcif_tmg_on(2);
        srcif_fsm_on();
        break;
    case SRCIF_HYBRID://hardware & software hybrid mode
        srcif_hybrid_fsm_init();
        if((timing_cur >= TIMING_1920x1080P50)&&(timing_cur <= TIMING_1920x1080P120_3D_SG))
          srcif_tmg_on(0);   
        else if((timing_cur >= TIMING_3840x2160P60)&&(timing_cur <= TIMING_4kxd5kP240_3D_SG))
          srcif_tmg_on(2);   
        ret = RegisterInterrupt(INT_VPU_FSM_STATE_CHG_IRQ, INT_TYPE_IRQ, (interrupt_handler_t)SRCIF_FSM_STATE_Handle);
        if(ret == 0) {
            SetInterruptEnable(INT_VPU_FSM_STATE_CHG_IRQ, 1);
            LOGD(TAG_VPP, "[vpu_util.C] Enable interrupts: vpu_fsm_state_chg_interrupt\n");
        }
        break;
    case SRCIF_PURE_SOFTWARE://pure software mode
        if(mux == 1)
            srcif_pure_sw_ptn();
        else if(mux == 2)
            srcif_pure_sw_hdmi();
        break;
    default:
        break;
    }
}

#if 1 //for client interface
fbc_hist_t out_hist;
fbc_hist_t* fbc_hist_info(void)
{
    unsigned int i,ratio = 8;
    vframe_hist_t hist_info;
    memcpy(&hist_info,&local_hist,sizeof(vframe_hist_t));
    for(i = 0; i < hist_info.hist_pow; i++) {
        ratio = ratio*2;
    }
    for(i = 0; i < 32; i++) {
        out_hist.hist_data[i] = hist_info.gamma[i]*ratio;
    }
    out_hist.hist_data[32] = hist_info.gamma[64]*ratio;//black
    out_hist.hist_data[33] = hist_info.gamma[65]*ratio;//white
    return &out_hist;
}
int fbc_avg_lut(void)
{
    unsigned int lum_sum,pixel_sum,lut_avg;
    lum_sum = local_hist.luma_sum;
    pixel_sum = local_hist.pixel_sum*2;
    lut_avg = lum_sum/pixel_sum;
    return lut_avg;
}
int fbc_bri_convert(int ui_val)
{
    int bri_reg;
    if(ui_val > 100)
        return 2047;
    bri_reg = 2047*ui_val/100 - 1024;
    return bri_reg;
}
int fbc_con_convert(int ui_val)
{
    int con_reg;
    con_reg = 511*ui_val/100;
    return con_reg;
}
int fbc_backlight_convert(int ui_val)
{
    if(ui_val > 100)
        return timing_table[timing_cur].vtotal;
    unsigned int val_v_reg = timing_table[timing_cur].vtotal*ui_val/100;
    return val_v_reg;
}
void fbc_bri_set(int reg_val)
{
    Wr_reg_bits(VP_BST,reg_val&0x7ff,16,11);
}
void fbc_con_set(int reg_val)
{
    Wr_reg_bits(VP_BST,reg_val&0x3ff,0,9);
}
/*reg_val:0~255*/
void fbc_backlight_set(int reg_val)
{
#if 0
    if(reg_val > FBC_BACKLIGHT_RANGE_REG)
        return;
    unsigned int val_v_reg = timing_table[timing_cur].vtotal*reg_val/FBC_BACKLIGHT_RANGE_REG << 16;
    Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0);
    Wr(VP_PWM_DATA_PORT,val_v_reg);
#endif
    if(reg_val > FBC_BACKLIGHT_RANGE_UI)
        return;

    unsigned int val_v_reg,val_h_reg,val_v_range;
    unsigned int i,data;

    if(panel_param->pwm_hz == 60) {
        if(panel_param->bl_inverter) {
            val_v_reg = (timing_table[timing_cur].vtotal*(FBC_BACKLIGHT_RANGE_UI-reg_val)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = (timing_table[timing_cur].vtotal*reg_val/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
        val_h_reg = (timing_table[timing_cur].htotal/2 -1)<< 16;//one clock two pixels
    } else if (panel_param->pwm_hz == 120) {
        if(panel_param->bl_inverter) {
            val_v_reg = ((timing_table[timing_cur].vtotal/2-1)*(FBC_BACKLIGHT_RANGE_UI-reg_val)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = ((timing_table[timing_cur].vtotal/2-1)*reg_val/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
		val_v_range = timing_table[timing_cur].vtotal/2;
        val_h_reg = (timing_table[timing_cur].htotal/2 -1)<< 16;//one clock two pixels
    } else if (panel_param->pwm_hz == 240) {
        if(panel_param->bl_inverter) {
            val_v_reg = ((timing_table[timing_cur].vtotal/4-1)*(FBC_BACKLIGHT_RANGE_UI-reg_val)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = ((timing_table[timing_cur].vtotal/4-1)*reg_val/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
		val_v_range = timing_table[timing_cur].vtotal/4;
        val_h_reg = (timing_table[timing_cur].htotal/2 -1)<< 16;//one clock two pixels
    } else {
        if(panel_param->bl_inverter) {
            val_v_reg = (timing_table[timing_cur].vtotal*(FBC_BACKLIGHT_RANGE_UI-reg_val)/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        } else {
            val_v_reg = (timing_table[timing_cur].vtotal*reg_val/FBC_BACKLIGHT_RANGE_UI << 16)|0x40000000;
        }
        val_h_reg = (timing_table[timing_cur].htotal/2 -1)<< 16;//one clock two pixels
    }


    for(i = 0; i < 3; i++) { //pwm0/1/2
        if (panel_param->pwm_hz == 60) {

            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0 );
            Wr(VP_PWM_DATA_PORT,val_v_reg);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
        } else if (panel_param->pwm_hz == 120) {

            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0 );
            Wr(VP_PWM_DATA_PORT,val_v_reg);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1 + i*8);
            Wr(VP_PWM_DATA_PORT,val_v_reg+((val_v_range<<16)|val_v_range));
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);

        } else if(panel_param->pwm_hz == 240) {
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0 );
            Wr(VP_PWM_DATA_PORT,val_v_reg);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1 + i*8);
            Wr(VP_PWM_DATA_PORT,val_v_reg+((val_v_range<<16)|val_v_range));
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2 + i*8);
            Wr(VP_PWM_DATA_PORT,val_v_reg+(((2*val_v_range)<<16)|(2*val_v_range)));
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3 + i*8);
            Wr(VP_PWM_DATA_PORT,val_v_reg+(((3*val_v_range)<<16)|(3*val_v_range)));

        } else { //default 60
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V0 );
            Wr(VP_PWM_DATA_PORT,val_v_reg);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V1 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V2 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
            Wr(VP_PWM_ADDR_PORT,VPU_PWM0_V3 + i*8);
            Wr(VP_PWM_DATA_PORT,0xffffffff);
        }

    }
    data = ((timing_table[timing_cur].vtotal-1) << 16)|(timing_table[timing_cur].htotal/2 - 1);
    Wr(VP_PWM_ADDR_PORT,VPU_PWM_HVSIZE_M1);
    Wr(VP_PWM_DATA_PORT,data);
    //for 3d reserved

}
void fbc_demura_enable(unsigned int en)
{
    if(en) {
        Wr_reg_bits(VP_CTRL, 1,13,1);//enable
        Wr_reg_bits(VP_BYPASS_CTRL,0,11,1);
    } else {
        Wr_reg_bits(VP_CTRL, 0,13,1);//disable
        Wr_reg_bits(VP_BYPASS_CTRL,1,11,1);//bypass
    }
}
void fbc_demura_set(unsigned int leak_light,unsigned int threshold)
{
    Wr_reg_bits(VP_DEMURA_CTRL,0,0,1);//data width of each Component ;  0: 10bits;  1: 8bits
    Wr_reg_bits(VP_DEMURA_CTRL,threshold,4,10);//Threshold check for demura
    Wr_reg_bits(VP_DEMURA_CTRL,leak_light,16,13);//Leak light
}
void fbc_demura_load_table(demura_lutidx_t table_index,int *data,int sizeItem)
{
    vpu_write_lut_new (table_index, sizeItem, 0, data, 0);
}
void fbc_dynamic_contrast_enable(int enable)
{
    if(enable)
        enable_dnlp  (1);
    else
        enable_dnlp  (2);
}
void fbc_backlight_enable(int enable)
{
    if(enable)
        enable_backlight  (1);
    else
        enable_backlight  (0);
}
int fbc_backlight_status(void)
{
    unsigned int data;
    data = Rd_reg_bits(PREG_PAD_GPIO3_O,12,1);
    if(data)
        return 0;
    else
        return 1;

    #if 0
    unsigned int data,port;
    port = VPU_PWM0_V0;
    Wr(VP_PWM_ADDR_PORT,port);
    data = Rd(VP_PWM_DATA_PORT);
    if(data&(1 << 30))
        return 1;
    else
        return 0;
	#endif
    
}
void fbc_switch_to_hdmi(int enable)
{
    unsigned int rdreg = 0;
    rdreg = (Rd(SRCIF_WRAP_CTRL) & 0x40) >> 0x6;//0:hdmi 1:ptn

    if(enable == 1)
    {
        con_auto_hdmi = 1;
        if(0 == rdreg) //last switch is hdmi
        {
            return;
        }
        vpu_srcif_debug(2,2);//force from hdmi
        enable_csc0(0);
    }
    else
    {
        con_auto_hdmi = 0;
        if(1 == rdreg) //last switch is ptn
        {
            return;
        }
        vpu_srcif_debug(2,1);//force from patgen
        enable_csc0(1);
    }
}
/*index:-4:+4*/
void fbc_set_gamma(int index)
{
    int i,j,gamma_index_ext;
    cur_gamma_index = index;
    gamma_index_ext = cur_gamma_index + 4;
    if(gamma_index_ext > 8)
        return;
    int *gamma_buf;
    unsigned short *gamma_buf_ex;
    gamma_buf = malloc(GAMMA_ITEM * sizeof(int));
    memset(gamma_buf, 0, GAMMA_ITEM * sizeof( int));
    enable_gamma (0);//must disable gamma before change gamma table!!!
    for(j = 0; j < GAMMA_MAX; j++) {
        gamma_buf_ex = &(vpu_config_table.gamma[gamma_index_ext].gamma_r[0]);
        for(i = 0; i < GAMMA_ITEM; i++) {
            gamma_buf[i] = gamma_buf_ex[i+GAMMA_ITEM*j];
            //  printf("gamma_buf[%d] = %x",i,gamma_buf[i]);
        }
        vpu_set_gamma_lut(j,gamma_buf,GAMMA_ITEM);
    }
    enable_gamma (1);//must disable gamma before change gamma table!!!

    free(gamma_buf);
}
int fbc_get_gamma(void)
{
    return cur_gamma_index;
}

int fbc_calcululate_bri_con(unsigned int value,unsigned int index_low,unsigned int index_up,unsigned int index_range)
{
    int index_value;
    index_value = value*(index_up - index_low)/index_range + index_low ;
    return index_value;
}


void fbc_adj_bri(unsigned int bri_ui)
{
    if (bri_ui>FBC_BRI_RANGE_UI)
        return;

    unsigned int i,index_range;
    int bri_index=0,bri_pre,bri_next;
    int bri_reg;
    index_range =(FBC_BRI_RANGE_UI+vpu_config_table.bri_con_index-2)/(vpu_config_table.bri_con_index-1);
    for(i=1; i<vpu_config_table.bri_con_index; i++) {
        if (bri_ui<=(index_range*i)) {
            bri_index = i;
            break;
        }
    }
    bri_pre = (vpu_config_table.bri_con[bri_index-1].bri_con>>16)&0x7ff;
    bri_next =  (vpu_config_table.bri_con[bri_index].bri_con>>16)&0x7ff;
    if((bri_pre>>10)&(0x1)) {
        bri_pre = (vpu_config_table.bri_con[bri_index-1].bri_con>>16)&0x3ff;
    } else {
        bri_pre = (vpu_config_table.bri_con[bri_index-1].bri_con>>16)&0x3ff|0x400;
    }	
    if((bri_next>>10)&(0x1)) {
        bri_next =(vpu_config_table.bri_con[bri_index].bri_con>>16)&0x3ff;
    } else {
        bri_next = (vpu_config_table.bri_con[bri_index].bri_con>>16)&0x3ff|0x400;
    }	
    bri_ui -=index_range *(bri_index -1);
    if (bri_index == vpu_config_table.bri_con_index -1) {
        index_range = FBC_BRI_RANGE_UI - index_range*(vpu_config_table.bri_con_index -2);
    }
    bri_reg = fbc_calcululate_bri_con(bri_ui,bri_pre,bri_next,index_range);
    bri_reg-=1024;
    Wr_reg_bits(VP_BST,bri_reg&0x7ff,16,11);
}

void fbc_adj_con(unsigned int con_ui)
{
    if (con_ui>FBC_CON_RANGE_UI)
        return;

    unsigned int i,index_range;
    int con_index=0,con_pre,con_next;
    int con_reg;
    index_range = (FBC_CON_RANGE_UI+vpu_config_table.bri_con_index-2)/(vpu_config_table.bri_con_index-1);
    for(i=1; i<vpu_config_table.bri_con_index; i++) {
        if (con_ui<=(index_range*i)) {
            con_index = i;
            break;
        }
    }
    con_pre = vpu_config_table.bri_con[con_index-1].bri_con&0x1ff;
    con_next =  vpu_config_table.bri_con[con_index].bri_con&0x1ff;
    con_ui -=index_range *(con_index -1);
    if (con_index == vpu_config_table.bri_con_index -1) {
        index_range = FBC_CON_RANGE_UI - index_range*(vpu_config_table.bri_con_index -2);
    }
    con_reg = fbc_calcululate_bri_con(con_ui,con_pre,con_next,index_range);
    Wr_reg_bits(VP_BST,con_reg&0x1ff,0,9);

}

void fbc_adj_sat(unsigned int sat_ui)
{
    if (sat_ui>FBC_SAT_RANGE_UI)
        return;

    unsigned int i,index_range;
    int sat_index=0,sat_pre,sat_next;
    int sat_reg,data;
    index_range = (FBC_SAT_RANGE_UI+vpu_config_table.sat_hue_index-2)/(vpu_config_table.sat_hue_index-1);
    for(i=1; i<vpu_config_table.sat_hue_index; i++) {
        if (sat_ui<=(index_range*i)) {
            sat_index = i;
            break;
        }
    }
    sat_pre = vpu_config_table.sat_hue[sat_index-1].sat&0xfff;
    sat_next =  vpu_config_table.sat_hue[sat_index].sat&0xfff;
    sat_ui -=index_range *(sat_index -1);
    if (sat_index == vpu_config_table.sat_hue_index -1) {
        index_range = FBC_SAT_RANGE_UI - index_range*(vpu_config_table.sat_hue_index -2);
    }
    sat_reg = fbc_calcululate_bri_con(sat_ui,sat_pre,sat_next,index_range);
    Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
    data = Rd(VP_CM2_DATA_PORT)&0xfff;
    Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
    Wr(VP_CM2_DATA_PORT,  ((sat_reg<<16) | data));
}

// hue divid into two segment
void fbc_adj_hue(unsigned int hue_ui)
{
    if (hue_ui>FBC_HUE_RANGE_UI)
        return;

    unsigned int index_range;
    int hue_pre,hue_next;
    int hue_reg,data;
    index_range = (FBC_HUE_RANGE_UI+1)/2;
    if(hue_ui <=index_range) {
        hue_pre = vpu_config_table.sat_hue[0].hue&0xfff;
	    if(vpu_config_table.sat_hue[1].hue < 0xe00){
		    hue_next =(vpu_config_table.sat_hue[1].hue&0xfff)|0x1000;				
		} else {
		    hue_next =	vpu_config_table.sat_hue[1].hue&0xfff;	
		}	
    } else {
	    if(vpu_config_table.sat_hue[1].hue >= 0xe00) {
	        hue_pre = vpu_config_table.sat_hue[1].hue&0xfff;
		    hue_next =(vpu_config_table.sat_hue[2].hue&0xfff)|0x1000;		
		} else {
	        hue_pre = vpu_config_table.sat_hue[1].hue&0xfff;
		    hue_next =	vpu_config_table.sat_hue[2].hue&0xfff;	
		}
		    index_range = FBC_HUE_RANGE_UI - index_range;			
      	    hue_ui -=index_range;
	}
	hue_reg = fbc_calcululate_bri_con(hue_ui,hue_pre,hue_next,index_range);
	if(hue_reg>=0x1000)
		hue_reg-=4096;

	Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
	data = (Rd(VP_CM2_DATA_PORT)>>16)&0xfff;
	Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
	Wr(VP_CM2_DATA_PORT,  (hue_reg | (data<<16)));
}
#endif

void set_color_gamut(int mode)
{
	int hue_val,sat_val;

    Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
    hue_val = Rd(VP_CM2_DATA_PORT)&0xfff;
    Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
	sat_val = (Rd(VP_CM2_DATA_PORT)>>16)&0xfff;

	switch(mode){
    case 0:
        sat_val+=20;
        Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
        Wr(VP_CM2_DATA_PORT,  ((sat_val<<16) | hue_val));
	    break;
    case 1:   //standard mode
        Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
        Wr(VP_CM2_DATA_PORT,  ((sat_val<<16) | hue_val));
        break;
    case 2:   //xvycc mode
        sat_val+=10;
        Wr(VP_CM2_ADDR_PORT, CM_GLOBAL_GAIN_REG);
        Wr(VP_CM2_DATA_PORT,  ((sat_val<<16) | hue_val));
        break;
     default:
        break;
	}
}

int fbc_system_pwm_set(vpu_pwm_channel_set_t pwm_set)
{
    switch(pwm_set.pwm_channel)
    {
        case 0:
            vpu_backlight_adj(pwm_set.duty&0xff, timing_cur);
        break;
        case 1:
        break;
        default:
        break;
    }
    return 0;
}

/*kuka@20140618 add end*/

#endif
//=======================================================================================================


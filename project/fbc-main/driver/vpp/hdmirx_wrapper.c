#include <register.h>
#include <common.h>
#include <c_arc_pointer_reg.h>
#include <hdmirx_parameter.h>
#include <hdmirx.h>
#include <log.h>
#include <vpp.h>
#include <cmd.h>
#include <stdlib.h>
#include <string.h>
#include <vpu_util.h>
#include <srcif.h>
#include <command.h>
#include <project.h>
#include <vbyone.h>

//#include <cmd.h>

// For FBC, define HDMIRX_PHY_AML, and HDMIRX_VID_CEA.
// We need some more configuration for FBC's HDMIRX2.0
// for example: add channel_switch config
//              add CEA video mode config

#define HDMIRX_VERSION  "150116"
#define CEC_MSG_QUEUE_SIZE  20
//#define EQ_DEBUG_MODE
#ifdef EQ_DEBUG_MODE
#define DBG_SIZE        200
static unsigned char eq_ch0_index = 0;
static unsigned char eq_ch1_index = 0;
static unsigned char eq_ch2_index = 0;
static unsigned int eq_ch0_tb[2][DBG_SIZE] = {0};
static unsigned int eq_ch1_tb[2][DBG_SIZE] = {0};
static unsigned int eq_ch2_tb[2][DBG_SIZE] = {0};
#endif
static unsigned int eq_ch0 = 0;
static unsigned int eq_ch1 = 0;
static unsigned int eq_ch2 = 0;

struct hdmi_rx_ctrl_video {
    /** DVI detection status: DVI (true) or HDMI (false) */
    int dvi;
    /** Deep color mode: 24, 30, 36 or 48 [bits per pixel] */
    unsigned deep_color_mode;
    /** Pixel clock frequency [kHz] */
    unsigned long pixel_clk;
    /** TMDS clock frequency [kHz] */
    unsigned long tmds_clk;
    /** Refresh rate [0.01Hz] */
    unsigned long refresh_rate;
    /** Interlaced */
    int interlaced;
    /** Vertical offset */
    unsigned long voffset;
    /** Vertical active */
    unsigned long vactive;
    /** Vertical total */
    unsigned long vtotal;
    /** Horizontal offset */
    unsigned long hoffset;
    /** Horizontal active */
    unsigned long hactive;
    /** Horizontal total */
    unsigned long htotal;
    /** AVI Y1-0, video format */
    unsigned video_format;
    /** AVI VIC6-0, video mode identification code */
    unsigned video_mode;
    /** AVI PR3-0, pixel repetition factor */
    unsigned pixel_repetition;
    /* for sw info */
    unsigned int sw_vic;
    unsigned int sw_dvi;
    int           sw_fp;
    int           sw_alternative;
};

struct rx {
    unsigned char pow5v_state[10];
    char tx_5v_status;
    struct hdmi_rx_ctrl_video pre_video_params;
    struct hdmi_rx_ctrl_video cur_video_params;
};

typedef struct cec_msg {
    unsigned char cmd;
    unsigned char msg_data[10];
    unsigned char msg_len;
} cec_msg;

typedef struct cec_msg_queue {
    struct cec_msg msg[CEC_MSG_QUEUE_SIZE];
    unsigned char wr_index;
    unsigned char rd_index;
} cec_msg_queue;

struct cec_msg_queue tx_queue;
static int need_auto_calibration = 0;
static unsigned int eq_position = 0;
extern int irq_unstable_flag;
extern int irq_stable_flag;
static char sig_status = 0;
static int lvds_rst_flag = 0;
static unsigned char init_cnt_max = 1;
static unsigned char unlock_max = 1;
static unsigned char lock_max = 156;//150;
static char debug_log = 0;
static char hide_logo_flag = 1;
static int pat_cnt = 1;
static int LVDS_reset_flag = 1;
static int LVDS_reset_cnt = 0;

struct rx rx;

extern void hide_logo();
extern unsigned char con_auto_hdmi;
extern unsigned char customer_ptn;

static backlight_func setBacklight = NULL;
void register_backlight_func(backlight_func func)
{
    setBacklight = func;
}


void hdmirx_get_video_info(struct hdmi_rx_ctrl_video *params)
{
    //unsigned long temp;
    const unsigned factor = 100;
    unsigned divider = 0;

    //params->video_format = (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_AVI_PB) >> 5) & 0x3;
    //params->video_mode = (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_AVI_PB) >> 24) & 0x7f;
    //params->dvi = (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_STS) >> 28) & 0x1;
    //params->interlaced = (hdmirx_rd_dwc(HDMIRX_DWC_MD_STS) >> 3) & 0x1;
    params->htotal = (hdmirx_rd_dwc(HDMIRX_DWC_MD_HT1) >> 16) & 0xffff;
    params->vtotal = hdmirx_rd_dwc(HDMIRX_DWC_MD_VTL) & 0xffff;
    params->hactive = hdmirx_rd_dwc(HDMIRX_DWC_MD_HACT_PX) & 0xffff;
    params->vactive = hdmirx_rd_dwc(HDMIRX_DWC_MD_VAL) & 0xffff;
    //params->pixel_repetition = (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_AVI_HB) >> 24) &0xf;
    params->tmds_clk = hdmirx_get_tmds_clock();
    params->pixel_clk = params->tmds_clk;
    //printf("\n***111**tmds_clk=[%d],pixel_clk=[%d]******\n", params->tmds_clk, params->pixel_clk);
#if 0
    temp = (hdmirx_rd_dwc(HDMIRX_DWC_HDMI_STS) >> 28) & 0xf; //MSK(4,28));
    if(temp == 7) {
        params->deep_color_mode = 48;
        divider = 2.00 * factor;    /* divide by 2 */
    } else if(temp == 6) {
        params->deep_color_mode = 36;
        divider = 1.50 * factor;    /* divide by 1.5 */
    } else if(temp == 5) {
        params->deep_color_mode = 30;
        divider = 1.25 * factor;    /* divide by 1.25 */
    } else {
        params->deep_color_mode = 24;
        divider = 1.00 * factor;
    }
    //params->pixel_clk = (params->pixel_clk * factor) / divider;
    //params->hoffset = (params->hoffset * factor) / divider;
    //params->hactive   = (params->hactive * factor) / divider;
    //params->htotal = (params->htotal  * factor) / divider;
    printf("\n***222**tmds_clk=[%d],pixel_clk=[%d] temp=[%d]******\n", params->tmds_clk, params->pixel_clk, temp);
#endif
}


void dump_reg(void)
{
    int i = 0;
    printf("\n\n*******Top registers********\n");
    printf("[addr ]  addr + 0x0,  addr + 0x1,  addr + 0x2,  addr + 0x3\n\n");
    for(i = 0; i <= 0x56; ) {
        printf("[0x%-3x]  0x%-8x,  0x%-8x,  0x%-8x,  0x%-8x\n",i,(unsigned int)hdmirx_rd_top(i),(unsigned int)hdmirx_rd_top(i+1),(unsigned int)hdmirx_rd_top(i+2),(unsigned int)hdmirx_rd_top(i+3));
        i = i + 4;
    }

    printf("\n\n*******Controller registers********\n");
    \
    printf("[addr ]  addr + 0x0, [addr ]  addr + 0x4, [addr ]  addr + 0x8, [addr ]  addr + 0xc\n\n");
    for(i = 0; i <= 0xffc; ) {
        if(i == 0xc || i ==0x3c || i ==0x8c || i ==0xa0 || i ==0xac || i ==0xc8 || i ==0xd8 || i ==0xdc \
           || i ==0x184 || i ==0x188 || i ==0x18c || i ==0x190 ||i ==0x194 || i ==0x198 ||i ==0x19c || i ==0x204 \
           || i ==0x220 || i ==0x230 || i ==0x234 || i ==0x238 || i ==0x26c || i ==0x270 || i ==0x274 || i ==0x278 \
           || i ==0x290 || i ==0x294 || i ==0x298 || i ==0x29c || i ==0x2d4 || i ==0x2dc || i ==0x2e8 || i ==0x2ec \
           || i ==0x2f0 || i ==0x2f4 || i ==0x2f8 || i ==0x2fc || i ==0x314 || i ==0x328 || i ==0x32c || i ==0x348 \
           || i ==0x34c || i ==0x350 || i ==0x354 || i ==0x358 || i ==0x35c || i ==0x384 || i ==0x388 || i ==0x38c \
           || i ==0x398 || i ==0x39c || i ==0x3b0 || i ==0x3b4 || i ==0x3b8 || i ==0x3bc || i ==0x3d8 || i ==0x3dc \
           || i ==0x41c || i ==0x810 || i ==0x814 || i ==0x818 || i ==0x81c || i ==0x830 || i ==0x834 || i ==0x838 \
           || i ==0x83c || i ==0x854 || i ==0x858 || i ==0x85c || i ==0x8e4 || i ==0x8e8 || i ==0x8ec || i ==0xf60 \
           || i ==0xf64 || i ==0xf70 || i ==0xf74 || i ==0xf78 || i ==0xf7c || i ==0xf88 || i ==0xf8c || i ==0xf90 \
           || i ==0xf94 || i ==0xfa0 || i ==0xfa4 || i ==0xfa8 || i ==0xfac || i ==0xfb8 || i ==0xfbc || i ==0xfc0 \
           || i ==0xfc4 || i ==0xfd0 || i ==0xfd4 || i ==0xfd8 || i ==0xfdc || i ==0xfe8 || i ==0xfec || i ==0xff0 \
           || (i>=0x60&&i<=0x7c) || (i>=0x100&&i<=0x13c) || (i>=0x1a0&&i<=0x1fc) || (i>=0x420&&i<=0x5fc) \
           || (i>=0x614&&i<=0x7fc) || (i>=0x880&&i<=0x8dc) || (i>=0x8f0&&i<=0xf74)) {
            printf("[0x%-3x]  null      , ", i);
            i = i + 4;
        } else {
            printf("[0x%-3x]  0x%-8x, ",i,hdmirx_rd_dwc(i));

            i = i + 4;
        }
        if(i%16==0)
            printf("\n");
    }
    /*
    printf("\n\n*******PHY registers********\n");
    printf("[addr ]  addr + 0x0,  addr + 0x1,  addr + 0x2,  addr + 0x3\n\n");
    for(i = 0; i <= 0x9a; ){
        printf("[0x%-3x]  0x%-8x,  0x%-8x,  0x%-8x,  0x%-8x\n",i,hdmirx_rd_phy(i),hdmirx_rd_phy(i+1),hdmirx_rd_phy(i+2),hdmirx_rd_phy(i+3));
        i = i + 4;
    }
    */
}

void dump_edid(void)
{
    int i = 0;
    printf("\n\n*******EDID data********\n");
    printf("[addr ]  addr + 0x0,  addr + 0x1,  addr + 0x2,  addr + 0x3\n\n");
    for(i = 0; i < 256; ) {
        printf("[0x%-3x]  0x%-8x,  0x%-8x,  0x%-8x,  0x%-8x\n",i,
               (unsigned int)hdmirx_rd_top(HDMIRX_TOP_EDID_OFFSET+i),(unsigned int)hdmirx_rd_top(HDMIRX_TOP_EDID_OFFSET+i+1),
               (unsigned int)hdmirx_rd_top(HDMIRX_TOP_EDID_OFFSET+i+2),(unsigned int)hdmirx_rd_top(HDMIRX_TOP_EDID_OFFSET+i+3));
        i = i + 4;
    }
}

//TODO:
void dump_hdcp(void)
{

}
void dump_eq_data(void)
{
#ifdef EQ_DEBUG_MODE
    int i=0;
    printf("**************CH0**************\n");
    printf("EQ1_CS:%d  EQ1_RS:%d  EQ2_CS:%d  EQ2_RS:%d\n",(eq_ch0&0x7000)>>12,(eq_ch0&0xe00)>>9,(eq_ch0&0x1e0)>>5,(eq_ch0&0xe)>>1);
    for(i=0; i<DBG_SIZE; i++) {
        printf("%d: EQ1_CS:%d  EQ1_RS:%d  EQ2_CS:%d  EQ2_RS:%d  errcnt:%d\n",(eq_ch0_tb[0][i]&0x7000)>>12,(eq_ch0_tb[0][i]&0xe00)>>9,(eq_ch0_tb[0][i]&0x1e0)>>5,(eq_ch0_tb[0][i]&0xe)>>1,eq_ch0_tb[1][i]);
    }
    printf("**************CH1**************\n");
    printf("EQ1_CS:%d  EQ1_RS:%d  EQ2_CS:%d  EQ2_RS:%d\n",(eq_ch1&0x7000)>>12,(eq_ch1&0xe00)>>9,(eq_ch1&0x1e0)>>5,(eq_ch1&0xe)>>1);
    for(i=0; i<DBG_SIZE; i++) {
        printf("%d: EQ1_CS:%d  EQ1_RS:%d  EQ2_CS:%d  EQ2_RS:%d  errcnt:%d\n",(eq_ch1_tb[0][i]&0x7000)>>12,(eq_ch1_tb[0][i]&0xe00)>>9,(eq_ch1_tb[0][i]&0x1e0)>>5,(eq_ch1_tb[0][i]&0xe)>>1,eq_ch1_tb[1][i]);
    }
    printf("**************CH0**************\n");
    printf("EQ1_CS:%d  EQ1_RS:%d  EQ2_CS:%d  EQ2_RS:%d\n",(eq_ch0&0x7000)>>12,(eq_ch0&0xe00)>>9,(eq_ch0&0x1e0)>>5,(eq_ch0&0xe)>>1);
    for(i=0; i<DBG_SIZE; i++) {
        printf("%d: EQ1_CS:%d  EQ1_RS:%d  EQ2_CS:%d  EQ2_RS:%d  errcnt:%d\n",(eq_ch2_tb[0][i]&0x7000)>>12,(eq_ch2_tb[0][i]&0xe00)>>9,(eq_ch2_tb[0][i]&0x1e0)>>5,(eq_ch2_tb[0][i]&0xe)>>1,eq_ch2_tb[1][i]);
    }
#endif
}

void dump_video_state()
{
    unsigned long temp;

    printf("\n video format %d\n", (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_AVI_PB) >> 5) & 0x3);//MSK(2, 5)
    printf("video_mode %d\n", (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_AVI_PB) >> 24) & 0x7f); //MSK(7,24)
    printf("dvi %d\n", (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_STS) >> 28) & 0x1);// _BIT(28));
    printf("interlaced %d\n", (hdmirx_rd_dwc(HDMIRX_DWC_MD_STS) >> 3) & 0x1); //_BIT(3));
    printf("htotal %d\n", (hdmirx_rd_dwc(HDMIRX_DWC_MD_HT1) >> 16) & 0xffff);//MSK(16,16));
    printf("vtotal %d\n", hdmirx_rd_dwc(HDMIRX_DWC_MD_VTL) & 0xffff); //MSK(16,0));
    printf("hactive %d\n", hdmirx_rd_dwc(HDMIRX_DWC_MD_HACT_PX) & 0xffff);//MSK(16,0));
    printf("vactive %d\n", hdmirx_rd_dwc(HDMIRX_DWC_MD_VAL) & 0xffff); //MSK(16,0));
    printf("pixel_repetition %d\n", (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_AVI_HB) >> 24) &0xf);//MSK(4,24));
    printf("tmds clk %d\n", hdmirx_get_tmds_clock());
    //TMDS clock & Pixel clock :TODO
    printf("***top***\n");
    printf("Hactive %d\n",hdmirx_rd_top(0x2d)>>16);
    printf("HTOTAL %d\n",hdmirx_rd_top(0x2d)&0x1fff);
    printf("Vactive %d\n",hdmirx_rd_top(0x30)>>16);
    printf("VTOTAL %d\n",hdmirx_rd_top(0x30)&0xfff);
    temp = (hdmirx_rd_dwc(HDMIRX_DWC_HDMI_STS) >> 28) & 0xf; //MSK(4,28));

    if(temp == 4)
        printf("deep color mode 48 bite\n");
    else if(temp == 5)
        printf("deep color mode 36 bite\n");
    else if(temp == 6)
        printf("deep color mode 30 bite\n");
    else
        printf("deep color mode 24 bite\n");

    printf("\nVendor Specific Info ID %x\n", (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_VSI_ST0) & 0xffffff));//MSK(24,0));
    printf("HDMI_VIDEO_Formate %x\n", ((hdmirx_rd_dwc(HDMIRX_DWC_PDEC_VSI_ST1) >> 5) & 0x7));//MSK(3,5));
    printf("3D struct %x\n", (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_VSI_ST1) >> 16) & 0xf);//MSK(4,16));
    printf("3D ext %x\n", (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_VSI_ST1) >> 20) & 0xf);//MSK(4,20));
}

void dump_audio_state()
{
    unsigned long rd_data = hdmirx_rd_dwc(HDMIRX_DWC_PDEC_AIF_PB0);

    printf("coding type %u\n", (rd_data >> 4) & 0xf);//MSK(4,4));
    printf("channel count %u\n", (rd_data) & 0x7);//MSK(3,0));
    printf("sample freq %u\n", (rd_data >> 10) & 0x7);//MSK(3,10));
    printf("sample size %u\n", (rd_data >> 8) & 3);//MSK(2,8));
    printf("channel allocation %u\n", (rd_data >> 24) & 0xff);//MSK(8,24));
    printf("cts %d\n", hdmirx_rd_dwc(HDMIRX_DWC_PDEC_ACR_CTS));
    printf("N %d\n", hdmirx_rd_dwc(HDMIRX_DWC_PDEC_ACR_N));
}

void dump_clock_data(void)
{
    printf("****************CLOCK*****************\n");
    printf("hdmirx_aud_clk = %d\n",     hdmirx_get_clock(48));
    printf("hdmirx_aud_mclk = %d\n",    hdmirx_get_clock(47));
    printf("hdmirx_aud_sck = %d\n",     hdmirx_get_clock(46));
    printf("hdmirx_audmeas_clk = %d\n", hdmirx_get_clock(45));
    printf("HDMI_RX_CLK_OUT = %d\n",    hdmirx_get_clock(44));
    printf("cts_hdmirx_phy_cfg_clk = %d\n", hdmirx_get_clock(43));
    printf("AUD_CLK_OUT = %d\n",        hdmirx_get_clock(42));
    printf("hdmirx_tmds_clk_out = %d\n",    hdmirx_get_clock(41));
    printf("cts_hdmirx_meas_ref_clk = %d\n",        hdmirx_get_clock(40));
    printf("cts_hdmirx_modet_clk = %d\n",   hdmirx_get_clock(39));
    printf("cts_hdmirx_cfg_clk = %d\n",     hdmirx_get_clock(38));
    printf("cts_hdmirx_acr_ref_clk = %d\n", hdmirx_get_clock(37));
    printf("hdmirx_tmds_clk = %d\n",    hdmirx_get_clock(36));
    printf("hdmirx_vid_clk = %d\n", hdmirx_get_clock(35));
    printf("cts_ref_clk = %d\n",        hdmirx_get_clock(34));
    printf("vx1_fifo_clk = %d\n",   hdmirx_get_clock(33));
    printf("lvds_fifo_clk = %d\n",  hdmirx_get_clock(32));
    printf("cts_vpu_clki = %d\n",   hdmirx_get_clock(31));
    printf("vid_pll_clk = %d\n",    hdmirx_get_clock(30));
    printf("hdmirx_cable_clk = %d\n",   hdmirx_get_clock(29));
    printf("cts_cec_clk_32k = NULL\n");//   clk_util_clk_msr(26, 1000));
    printf("sys_clk_vpu = %d\n",        hdmirx_get_clock(11));
    printf("sys_clk_hdmirx = %d\n",     hdmirx_get_clock(10));
    printf("sys_clk_hdmirx_cec = %d\n", hdmirx_get_clock(8));
    printf("sys_pll_clk = %d\n",    hdmirx_get_clock(6));
    printf("sys_oscin_i = %d\n",    hdmirx_get_clock(0));
    printf("****************CLOCK*****************\n");

}
#define LOCK_BIT (0xf<<8)
void monitor_sig_errcnt()
{
    unsigned long lock = hdmirx_rd_dwc(0x824);
    static int flag = 0;
    int errcnt0 = hdmirx_rd_top(0x61);
    int errcnt1 = hdmirx_rd_top(0x62);

    if((lock&LOCK_BIT) != LOCK_BIT) {
        flag = 1;
        printf("\n%x,%x,%x", errcnt0, errcnt1, (lock&LOCK_BIT)>>8);
    } else if(flag == 1) {
        printf("\n%x,%x,%x", errcnt0, errcnt1, (lock&LOCK_BIT)>>8);
        flag = 0;
    }
}

int do_hdmi_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    //unsigned int data_in,cmd_id,i,type,charIndex;
    char* cmd;
    int addr;
    int data;
    unsigned int value = 0;

    addr = strtoul(argv[2], NULL, 16);
    data = strtoul(argv[3], NULL, 16);
    cmd = argv[1];

    if(argc < 2) {
        return -1;
    }

    if(!strncmp(argv[0], "hdmi", 4)) {
        if(!strncmp(cmd, "reg", 3)) {
            dump_reg();
        } else if(!strncmp(cmd, "edid", 4)) {
            dump_edid();
        } else if(!strncmp(cmd, "hdcp", 4)) {
            dump_hdcp();
        } else if(!strncmp(cmd, "video", 5)) {
            dump_video_state();
        } else if(!strncmp(cmd, "audio", 5)) {
            dump_audio_state();
        } else if(!strncmp(cmd, "EQ", 2)) {
            dump_eq_data();
        } else if(!strncmp(cmd, "clock", 5)) {
            dump_clock_data();
        } else if(!strncmp(cmd, "version", 7)) {
            printf("HDMI version : %ls\n",HDMIRX_VERSION);
        } else if(!strncmp(cmd, "reset", 5)) {
            hdmirx_phy_init();
            printf("phy init\n");
        } else if(!strncmp(cmd, "log", 3)) {
            debug_log = addr;
            printf("unlock_cnt = %d",unlock_max);
        } else if(!strncmp(cmd, "unlock", 6)) {
            unlock_max = addr;
            printf("unlock_cnt = %d",unlock_max);
        } else if(!strncmp(cmd, "lock", 4)) {
            lock_max = addr;
            printf("unlock_cnt = %d",lock_max);
        } else if(!strncmp(cmd, "config", 5)) {
            hdmirx_config();
            printf("config\n");
        } else if(!strncmp(cmd, "auto1", 5)) {
            LVDS_reset_flag = 1;
        } else if(!strncmp(cmd, "auto0", 5)) {
            LVDS_reset_flag = 0;
        } else if(!strncmp(cmd, "auto2", 5)) {
            need_auto_calibration = 2;
            eq_position = 0;
        } else if(!strncmp(cmd, "cklock", 6)) {
            printf("start lock check!\n");
            need_auto_calibration = 5;
        } else if(!strncmp(cmd, "timerstate", 5)) {
            printf("sig_state = %d\n",sig_status);
        } else if(!strncmp(cmd, "1p5", 3)) {
            printf("\nset 80030670 to 0x4a379221, +-1.5%.");
            Wr(VX1_LVDS_PLL_CTL2, 0x4a379221);
        } else if(!strncmp(cmd, "2p3", 3)) {
            printf("\nset 80030670 to 0x4a378a21, +-2.3%.");
            Wr(VX1_LVDS_PLL_CTL2, 0x4a378a21);
        } else if(!strncmp(cmd, "3p1", 3)) {
            printf("\nset 80030670 to 0x4a770221, +-3.1%.");
            Wr(VX1_LVDS_PLL_CTL2, 0x4a770221);
        } else if(!strncmp(cmd, "000", 3)) {
            printf("\nset 80030670 to default value:ca763a21");
            Wr(VX1_LVDS_PLL_CTL2, 0xca763a21);
        } else if(!strncmp(cmd, "src0", 4)) {
            Wr(SRCIF_WRAP_CTRL1,    0xc0300000);
            printf("\nset 80031660 to default value:0xc0300000");
        } else if(!strncmp(cmd, "src1", 4)) {
            Wr(SRCIF_WRAP_CTRL1,    0xc0340000);
            printf("\nset 80031660 to value:0xc0340000");
        }
        if(strncmp(cmd, "rht", 3) == 0) {
            value = hdmirx_rd_top(addr);
            printf("hdmirx TOP reg[%x]=%x\n",addr, value);
        } else if(strncmp(cmd, "rhp", 3) == 0) {

        } if(strncmp(cmd, "rhd", 3) == 0) {
            value = hdmirx_rd_dwc(addr);
            printf("hdmirx DWC reg[%x]=%x\n",addr, value);
        }
        if(strncmp(cmd, "wht", 3) == 0) {
            hdmirx_wr_top(addr, data);
            printf("write %x to hdmirx TOP reg[%x]\n",data,addr);
        } else if(strncmp(cmd, "whp", 3) == 0) {

        } else if(strncmp(cmd, "whd", 3) == 0) {
            hdmirx_wr_dwc(addr, data);
            printf("write %x to hdmirx DWC reg[%x]\n",data,addr);
        }
    }

    return 0;
}

static int hdmirx_cec_post_msg(unsigned char *s, unsigned short len)
{
    unsigned char i=0;
    //memcpy(&tx_queue.msg[tx_queue.wr_index], s, sizeof(unsigned char), len);
    tx_queue.msg[tx_queue.wr_index].msg_len = len+1;
    tx_queue.msg[tx_queue.wr_index].cmd = s[0];
    for(i=0; i<len-1; i++) {
        tx_queue.msg[tx_queue.wr_index].msg_data[i] = s[i+1];
    }
    tx_queue.wr_index = (tx_queue.wr_index+1) % CEC_MSG_QUEUE_SIZE;
    return 0;
}


void hdmirx_register_channel(void)
{
    if(RegisterChannel(0x10, hdmirx_cec_post_msg) != 0)
        printf("register cec channel fail\n");
}
#define EQ_MAX_POSITION 0x1fff
void hdmirx_auto_calibration(void)
{
    unsigned int data32;
    static int err_count_ch0 = 0x7fff;
    static int err_count_ch1 = 0x7fff;
    static int err_count_ch2 = 0x7fff;

    static unsigned int eq_position = 0;
    unsigned int error_ch0 = hdmirx_rd_dwc(HDMIRX_DWC_SCDC_REGS1) >> 16 & 0x7fff;
    unsigned int error_ch1 = hdmirx_rd_dwc(HDMIRX_DWC_SCDC_REGS2) & 0x7fff;
    unsigned int error_ch2 = hdmirx_rd_dwc(HDMIRX_DWC_SCDC_REGS2) >> 16 & 0x7fff;

    if(eq_position > 0)
        data32 = (((eq_position-1) & 0x07)<<1) | (((eq_position-1) & 0x1ff8)<<2);
    else
        data32 = ((eq_position & 0x07)<<1) | ((eq_position & 0x1ff8)<<2);

    //----------------------------CH0-----------------------------
    if(error_ch0 < err_count_ch0) {
        err_count_ch0 = error_ch0;
        eq_ch0 = data32;
#ifdef EQ_DEBUG_MODE
        eq_ch0_index = 0;
#endif
        printf("CH0 best Set=%x--EQ = %d",data32,err_count_ch0);
    }
#ifdef EQ_DEBUG_MODE
    else if(error_ch0 == err_count_ch0) {
        eq_ch0_tb[0][eq_ch0_index] = data32;
        eq_ch0_tb[1][eq_ch0_index] = error_ch0;
        eq_ch0_index++;
        if(eq_ch0_index > DBG_SIZE)
            eq_ch0_index = 0;
    }
#endif
    //----------------------------CH1-----------------------------
    if(error_ch1 < err_count_ch1) {
        err_count_ch1 = error_ch1;
        eq_ch1 = data32;
#ifdef EQ_DEBUG_MODE
        eq_ch1_index = 0;
#endif
        printf("CH1 best Set=%x--EQ = %d",data32,err_count_ch1);
    }
#ifdef EQ_DEBUG_MODE
    else if(error_ch1 == err_count_ch1) {
        eq_ch1_tb[0][eq_ch1_index] = data32;
        eq_ch1_tb[1][eq_ch1_index] = error_ch1;
        eq_ch1_index++;
        if(eq_ch1_index > DBG_SIZE)
            eq_ch1_index = 0;
    }
#endif
    //----------------------------CH2-----------------------------
    if(error_ch2 < err_count_ch2) {
        err_count_ch2 = error_ch2;
        eq_ch2 = data32;
#ifdef EQ_DEBUG_MODE
        eq_ch2_index = 0;
#endif
        printf("CH2 best Set=%x--EQ = %d",data32,err_count_ch2);
    }
#ifdef EQ_DEBUG_MODE
    else if(error_ch2 == err_count_ch2) {
        eq_ch2_tb[0][eq_ch2_index] = data32;
        eq_ch2_tb[1][eq_ch2_index] = error_ch2;
        eq_ch2_index++;
        if(eq_ch2_index > DBG_SIZE)
            eq_ch2_index = 0;
    }
#endif
    if(eq_position < EQ_MAX_POSITION) {
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6,data32);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7,data32);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8,data32);
        eq_position++;
    } else {
        need_auto_calibration = 0;
        printf("eq_ch0 = %x,eq_ch1 = %x,eq_ch2 = %x\n",eq_ch0,eq_ch1,eq_ch2);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6,eq_ch0);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7,eq_ch1);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8,eq_ch2);
    }

}

#ifdef EQ_DEBUG_MODE
#define CH0_ALIGNMENT  (3<<24)
#define CH1_ALIGNMENT  (3<<26)
#define CH2_ALIGNMENT  (3<<28)
void hdmirx_auto_calibration_alignment(void)
{
    unsigned int data32;
    //static unsigned int eq_position = 0;
    //unsigned int error_ch0 = hdmirx_rd_dwc(HDMIRX_DWC_SCDC_REGS1) >> 16 & 0x7fff;
    //unsigned int error_ch1 = hdmirx_rd_dwc(HDMIRX_DWC_SCDC_REGS2) & 0x7fff;
    //unsigned int error_ch2 = hdmirx_rd_dwc(HDMIRX_DWC_SCDC_REGS2) >> 16 & 0x7fff;
    //unsigned int error_ch0 = hdmirx_rd_top(HDMIRX_TOP_CHAN01_ERRCNT) & 0x7fff;
    //unsigned int error_ch1 = hdmirx_rd_top(HDMIRX_TOP_CHAN01_ERRCNT) >> 14 & 0x7fff;
    //unsigned int error_ch2 = hdmirx_rd_top(HDMIRX_TOP_CHAN2_ERRCNT) >> 14 & 0x7fff;

    if(eq_position > 0)
        data32 = (((eq_position-1) & 0x07)<<1) | (((eq_position-1) & 0x1ff8)<<2);
    else
        data32 = ((eq_position & 0x07)<<1) | ((eq_position & 0x1ff8)<<2);
    unsigned int status32 = hdmirx_rd_top(HDMIRX_TOP_TMDS_ALIGN_STAT);

    //----------------------------CH0-----------------------------
    if((status32&CH0_ALIGNMENT)==CH0_ALIGNMENT) {
        eq_ch0_tb[0][eq_ch0_index] = data32;
        eq_ch0_tb[1][eq_ch0_index] = status32;
        eq_ch0_index++;
        if(eq_ch0_index > DBG_SIZE)
            eq_ch0_index = 0;
        printf("CH0 lock EQ = %x,alignment = %x",data32,status32);
    }
    if((status32&CH1_ALIGNMENT)==CH1_ALIGNMENT) {
        eq_ch1_tb[0][eq_ch1_index] = data32;
        eq_ch0_tb[1][eq_ch1_index] = status32;
        eq_ch1_index++;
        if(eq_ch1_index > DBG_SIZE)
            eq_ch1_index = 0;
        printf("CH1 lock EQ = %x,alignment = %x",data32,status32);
    }
    if((status32&CH2_ALIGNMENT)==CH2_ALIGNMENT) {
        eq_ch2_tb[0][eq_ch2_index] = data32;
        eq_ch0_tb[1][eq_ch2_index] = status32;
        eq_ch2_index++;
        if(eq_ch2_index > DBG_SIZE)
            eq_ch2_index = 0;
        printf("CH2 lock EQ = %x,alignment = %x",data32,status32);
    }
    if(eq_position < EQ_MAX_POSITION) {
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6,data32);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7,data32);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8,data32);
        eq_position++;
    } else {
        need_auto_calibration = 0;
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6,eq_ch0_tb[0][eq_ch0_index]);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7,eq_ch0_tb[0][eq_ch1_index]);
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8,eq_ch0_tb[0][eq_ch2_index]);
    }
}
#endif

#define DE_MARGIN   10
#define MIN_VTOTAL  (1125-50)
#define MIN_HTOTAL  (2200-100)
#define MIN_HACTIVE (1920-20)
#define MIN_VACTIVE (1080-20)

int istimingstable(struct hdmi_rx_ctrl_video *pre, struct hdmi_rx_ctrl_video *cur)
{
    int ret = 1;

    if ((abs((signed int)pre->hactive - (signed int)cur->hactive) > DE_MARGIN) ||
        (abs((signed int)pre->vactive - (signed int)cur->vactive) > DE_MARGIN) ||
        (abs((signed int)pre->htotal- (signed int)cur->htotal) > DE_MARGIN) ||
        (abs((signed int)pre->vtotal - (signed int)cur->vtotal) > DE_MARGIN) ||
        (cur->vtotal < MIN_VTOTAL)||
        (cur->htotal < MIN_HTOTAL)||
        (cur->vactive< MIN_VACTIVE)||
        (cur->hactive< MIN_HACTIVE)) {

            ret = 0;

        }
    return ret;
}

void hdmirx_DPLL_monitor(void)
{
    static int pll_error_count=0;
    int lock_flag = hdmirx_rd_dwc(HDMIRX_DWC_SCDC_REGS1);
    //unsigned int hdmirx_tmds_clk = hdmirx_get_clock(36);
    unsigned int hdmirx_cable_clk = hdmirx_get_clock(29);
    //unsigned int HDMI_RX_CLK_OUT = hdmirx_get_clock(44);
    if(hdmirx_cable_clk!=0) {
        //range>10M || DPLL unlock
        unsigned int hdmirx_tmds_clk_out = hdmirx_get_clock(41);
        if((abs(hdmirx_cable_clk - hdmirx_tmds_clk_out) > 10000000) ||
           (!hdmirx_rd_top(HDMIRX_TOP_DPLL_CTRL) & (1<<31)) || (((lock_flag>>9)&0x7) != 0x7)) {
            pll_error_count++;
            if(pll_error_count > 5) {
                pll_error_count = 0;
                hdmirx_reset_DPLL();
                if(debug_log)
                    printf("hdmirx_reset_DPLL\n");
            }

        }
    }
    //pre_cable_clk = hdmirx_cable_clk;

}
void hdmirx_sw_reset(void)
{
	hdmirx_wr_dwc(HDMIRX_DWC_DMI_SW_RST,0x4);
	delay_us(200);
	printf("sw reset\n");
}
void hdmirx_lvds_reset(void)
{
	Wr(VX1_LVDS_PLL_CTL, 0xe0000226);
	delay_us(50);
	Wr(VX1_LVDS_PLL_CTL, 0xc0004226);

	Wr(VX1_LVDS_PHY_CNTL0, 0x10081);
	delay_us(1);
	Wr(VX1_LVDS_PHY_CNTL0, 0x0080);

	Wr(VID_PLL_CLK_CNTL, 0x000af39c);
	delay_us(1);
	Wr(VID_PLL_CLK_CNTL, 0x000a739c);

	delay_us(10);

	if((get_ic_version() == 2) || (HDMI_PORT_SWITCH == HDMI_PORT_B)){
		hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6, 0x19a9a);
	    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7, 0x19a9a);
	    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8, 0x19a9a);
		delay_us(1);
		hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6, 0x39a9a);
	    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7, 0x39a9a);
	    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8, 0x39a9a);
	}else{
		hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6, 0x1019a9a);
	    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7, 0x1019a9a);
	    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8, 0x1019a9a);
		delay_us(1);
		hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6, 0x1039a9a);
	    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7, 0x1039a9a);
	    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8, 0x1039a9a);
	}
	printf("lvds reset\n");
}
char pow_state(void)
{
    char ret = 0;
    char sum_state = 0;

    rx.pow5v_state[0] = rx.pow5v_state[1];
    rx.pow5v_state[1] = rx.pow5v_state[2];
    rx.pow5v_state[2] = rx.pow5v_state[3];
    rx.pow5v_state[3] = rx.pow5v_state[4];
    rx.pow5v_state[4] = rx.pow5v_state[5];
    rx.pow5v_state[5] = rx.pow5v_state[6];
    rx.pow5v_state[6] = rx.pow5v_state[7];
    rx.pow5v_state[7] = rx.pow5v_state[8];
    rx.pow5v_state[8] = rx.pow5v_state[9];
    rx.pow5v_state[9] = (hdmirx_rd_top(HDMIRX_TOP_HPD_PWR5V)>>20)&0x1;
    sum_state = rx.pow5v_state[0] + rx.pow5v_state[1] + rx.pow5v_state[2]
                + rx.pow5v_state[3] + rx.pow5v_state[4] + rx.pow5v_state[5] + rx.pow5v_state[6]
                + rx.pow5v_state[7] + rx.pow5v_state[8] + rx.pow5v_state[9];
    if(sum_state <= 2) {
        ret = 0;
    } else if (sum_state >= 5) {
        ret = 1;
    }
    return ret;
}

#define SM_INT              0
#define SM_HPD_LOW          1
#define SM_HPD_HIGH         2
#define SM_PLL_UNLOCK       3
#define SM_SIGNAL_UNSTABLE  4
#define SM_SIGNAL_STABLE    5
void hdmirx_sig_monitor(void)
{
    static char unlock_cnt = 0;
    static char lock_cnt = 0;
#ifdef EQ_DEBUG_MODE
    if(need_auto_calibration==1) {
        hdmirx_auto_calibration();
        //hdmirx_auto_calibration_alignment();
        return;
    } else if(need_auto_calibration==2) {
        //hdmirx_auto_calibration();
        hdmirx_auto_calibration_alignment();
        return;
    }
#endif
    if(need_auto_calibration==5) {
        monitor_sig_errcnt();
        return;
    }
    rx.tx_5v_status = pow_state();
    hdmirx_DPLL_monitor();
	if((OUTPUT_VB1 == panel_param->output_mode) && (LVDS_reset_flag == 1)){
		if(hdmirx_get_clock(29) != 0){
			if(abs(hdmirx_get_clock(31) - hdmirx_get_clock(29)) > 10000000){
				if(LVDS_reset_cnt++ > 20){
					hdmirx_lvds_reset();
					LVDS_reset_cnt = 0;
				}
			}
		}
	}
    switch(sig_status) {
    case SM_INT:
        if (--init_cnt_max == 0) {
            memset(&tx_queue, 0, sizeof(struct cec_msg_queue));
            hdmirx_wr_top(HDMIRX_TOP_HPD_PWR5V, 0x11);
            sig_status = SM_HPD_LOW;
			delay_us(1);
			if(customer_ptn == 1){
				if(lvds_rst_flag && (OUTPUT_VB1 == panel_param->output_mode)){
					hdmirx_lvds_reset();
					if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
						srcif_fsm_off();
						enable_csc0(1);
						vpu_pattern_Switch(PATTERN_MODE_BLUE);
						srcif_pure_sw_ptn();
					} else if (vpu_get_srcif_mode() == SRCIF_PURE_HARDWARE) {
						enable_csc0(1);
					}
				}
			}else{
				if(lvds_rst_flag && (OUTPUT_VB1 == panel_param->output_mode)){
					hdmirx_lvds_reset();
				}
				if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
					srcif_fsm_off();
					enable_csc0(1);
						//vpu_pattern_Switch(PATTERN_MODE_BLUE);
					srcif_pure_sw_ptn();
				} else if (vpu_get_srcif_mode() == SRCIF_PURE_HARDWARE) {
					enable_csc0(1);
				}
			}
        }
        break;
    case SM_HPD_LOW:
		if(customer_ptn == 1){
			 if(0 == rx.tx_5v_status)
            	break;
        		hdmirx_wr_top(HDMIRX_TOP_HPD_PWR5V, 0x10);
        		sig_status = SM_HPD_HIGH;
		}else{

	        if(0 == rx.tx_5v_status){
				if(pat_cnt > 100){
					if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
						srcif_fsm_off();
						enable_csc0(1);
						vpu_pattern_Switch(PATTERN_MODE_BLUE);
						srcif_pure_sw_ptn();
					} else if (vpu_get_srcif_mode() == SRCIF_PURE_HARDWARE) {
						enable_csc0(1);
					}
					pat_cnt = 0;
				}
				if(pat_cnt != 0)
					pat_cnt ++;
	            break;
	        }
			if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
					srcif_fsm_off();
					enable_csc0(1);
					vpu_pattern_Switch(PATTERN_MODE_BLACK);
					srcif_pure_sw_ptn();
				} else if (vpu_get_srcif_mode() == SRCIF_PURE_HARDWARE) {
					enable_csc0(1);
				}
	        hdmirx_wr_top(HDMIRX_TOP_HPD_PWR5V, 0x10);
	        sig_status = SM_HPD_HIGH;
		}
        break;
    case SM_HPD_HIGH:
        if(0 == rx.tx_5v_status) {
            sig_status = SM_INT;
            init_cnt_max = 1;
            break;
        }
        sig_status = SM_PLL_UNLOCK;
        break;
    case SM_PLL_UNLOCK:
        if(0 == rx.tx_5v_status) {
            sig_status = SM_INT;
            init_cnt_max = 1;
            break;
        }
        if(hdmi_rx_phy_pll_lock()) { // && hdmi_rx_audio_pll_lock())
            if(lock_cnt++ > 10) {
                //hdmirx_init();
                printf("unlock_unstable\n");
                sig_status = SM_SIGNAL_UNSTABLE;
                lock_cnt = 0;
            }
        }
        break;
    case SM_SIGNAL_UNSTABLE:
        if(0 == rx.tx_5v_status) {
            sig_status = SM_INT;
            init_cnt_max = 1;
			vpu_pattern_Switch(PATTERN_MODE_BLUE);
            break;
        }
        if (hdmi_rx_phy_pll_lock()) {
            hdmirx_get_video_info(&rx.cur_video_params);
            if(istimingstable(&rx.pre_video_params, &rx.cur_video_params)) {
                if(lock_cnt == (lock_max-10)) {
			if(NULL != setBacklight)
			{
				setBacklight(0);
			}
			vpu_csc_config_ext(1);//for csc1 output black
			if(hide_logo_flag && (customer_ptn != 1)){
                            hide_logo();
                            hide_logo_flag = 0;
	                    }
					if(get_metal_revision() == REV_A){
                    	hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_CONFIG,0x80000000);
						printf("prestable, hdmirx cea reset.\n");
					}
                }else if (lock_cnt == lock_max-8) {
                    //sig_status = SM_SIGNAL_STABLE;
					if(customer_ptn == 1)
                    	vpu_pattern_Switch(PATTERN_MODE_BLUE);
					else
                    	vpu_pattern_Switch(PATTERN_MODE_BLACK);
					hdmirx_sw_reset();
					if(get_metal_revision() == REV_A)
                    	hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_CONFIG,0x00000000);

                    printf("stable\n");
					if(debug_log){
	                    printf("hactive: pre:%d--cur:%d\n",rx.pre_video_params.hactive,rx.cur_video_params.hactive);
	                    printf("vactive: pre:%d--cur:%d\n",rx.pre_video_params.vactive,rx.cur_video_params.vactive);
	                    printf("htotal: pre:%d--cur:%d\n",rx.pre_video_params.htotal,rx.cur_video_params.htotal);
	                    printf("vtotal: pre:%d--cur:%d\n\n",rx.pre_video_params.vtotal,rx.cur_video_params.vtotal);
					}
                    hdmirx_audio_control(1);

                }else if(lock_cnt == lock_max - 6) {
                	//sig_status = SM_SIGNAL_STABLE;
                	printf("after stable,output hdmi sig\n");
                    if(con_auto_hdmi)
                    {
                        if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
	                        srcif_pure_sw_hdmi();
	                        srcif_fsm_on();
	                    }

                        if(((hdmirx_rd_dwc(HDMIRX_DWC_PDEC_AVI_PB)>>5)&0x3) != 0) {
	                        enable_csc0(0);
	                    } else {
	                        enable_csc0(1);
	                    }
/*
					if(hide_logo_flag && (customer_ptn != 1)){
                            hide_logo();
                            hide_logo_flag = 0;
	                    }*/
                    }
                    //lock_cnt = 0;
				}
                else if(lock_cnt == lock_max-2) {
                                    //sig_status = SM_SIGNAL_STABLE;
                                    printf("after stable,vbyone reset\n");
                                    vbyone_softreset();
                                    //lock_cnt = 0;
                                }
		else if(lock_cnt == lock_max+10) {
			sig_status = SM_SIGNAL_STABLE;
			printf("after stable,csc1 force to default\n");
			vpu_csc_config_ext(2);
			if(NULL != setBacklight)
			{
				setBacklight(1);
			}
			lock_cnt = 0;
		}

				lock_cnt++;
            } else {
                if (lock_cnt && debug_log) {
                    printf("timing unstable lock_cnt = %d.\n", lock_cnt);
                    printf("hactive: pre:%d--cur:%d\n",rx.pre_video_params.hactive,rx.cur_video_params.hactive);
                    printf("vactive: pre:%d--cur:%d\n",rx.pre_video_params.vactive,rx.cur_video_params.vactive);
                    printf("htotal: pre:%d--cur:%d\n",rx.pre_video_params.htotal,rx.cur_video_params.htotal);
                    printf("vtotal: pre:%d--cur:%d\n\n",rx.pre_video_params.vtotal,rx.cur_video_params.vtotal);
                    lock_cnt = 0;
                }
            }
            memcpy(&rx.pre_video_params, &rx.cur_video_params, sizeof(struct hdmi_rx_ctrl_video));
        } else {
            if (lock_cnt) {
                printf("hdmi_rx_phy_pll_lock unstable lock_cnt = %d.\n", lock_cnt);
                lock_cnt = 0;
            }
        }
        break;
    case SM_SIGNAL_STABLE:
        if(0 == rx.tx_5v_status) {
            sig_status = SM_INT;
            init_cnt_max = 1;
			if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
				srcif_fsm_off();
				enable_csc0(1);
				vpu_pattern_Switch(PATTERN_MODE_BLUE);
				srcif_pure_sw_ptn();
			} else if (vpu_get_srcif_mode() == SRCIF_PURE_HARDWARE) {
				enable_csc0(1);
			}
			hdmirx_audio_control(0);
            break;
        }
        hdmirx_get_video_info(&rx.cur_video_params);
        if (0==hdmi_rx_phy_pll_lock()) {
            if(++unlock_cnt > unlock_max) {
                sig_status = SM_SIGNAL_UNSTABLE;
                if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
                    srcif_fsm_off();
                    enable_csc0(1);
                    vpu_pattern_Switch(PATTERN_MODE_BLUE);
                    srcif_pure_sw_ptn();
                } else if (vpu_get_srcif_mode() == SRCIF_PURE_HARDWARE) {
                        enable_csc0(1);
                }
                hdmirx_audio_control(0);

				if(get_metal_revision() == REV_A)
                	hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_CONFIG,0x80000000);

                printf("stable--->unstable, no pll lock.\n");
                unlock_cnt = 0;
            }
        } else {
            if(!istimingstable(&rx.pre_video_params, &rx.cur_video_params)) {
                if(debug_log) {
                    printf("hactive: pre:%d--cur:%d\n",rx.pre_video_params.hactive,rx.cur_video_params.hactive);
                    printf("vactive: pre:%d--cur:%d\n",rx.pre_video_params.vactive,rx.cur_video_params.vactive);
                    printf("htotal: pre:%d--cur:%d\n",rx.pre_video_params.htotal,rx.cur_video_params.htotal);
                    printf("vtotal: pre:%d--cur:%d\n",rx.pre_video_params.vtotal,rx.cur_video_params.vtotal);
                    printf("-unlock_cnt = %d\n",unlock_cnt);
                }
                if(++unlock_cnt > unlock_max) {
                    sig_status = SM_SIGNAL_UNSTABLE;
                    if (vpu_get_srcif_mode() == SRCIF_PURE_SOFTWARE) {
                        srcif_fsm_off();
                        enable_csc0(1);
                    	if(customer_ptn == 1)
                    		vpu_pattern_Switch(PATTERN_MODE_BLUE);
						else
                    		vpu_pattern_Switch(PATTERN_MODE_BLACK);
                        srcif_pure_sw_ptn();
                    } else if (vpu_get_srcif_mode() == SRCIF_PURE_HARDWARE) {
                        enable_csc0(1);
                    }
                    hdmirx_audio_control(0);

					if(get_metal_revision() == REV_A)
                    	hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_CONFIG,0x80000000);

                    printf("stable--->unstable, timing changed.\n");
                    unlock_cnt = 0;
                }
            } else {
                if (unlock_cnt) {
                    printf("stable unlock_cnt = %d\n", unlock_cnt);
                    unlock_cnt = 0;
                }
            }
			lvds_rst_flag = 1;
        }
        memcpy(&rx.pre_video_params, &rx.cur_video_params, sizeof(struct hdmi_rx_ctrl_video));
        break;
    default:
        break;


    }
}
char get_hdmi_stat(void)
{
	char ret = 0;

	if(sig_status == SM_SIGNAL_STABLE)
		ret = 1;
	else
		ret = 0;

	return ret;
}
void hdmirx_cec_monitor(void)
{
    if(hdmirx_rd_dwc(HDMIRX_DWC_CEC_CTRL) & (1<<0)) {
        return;
    }
    if(tx_queue.rd_index == tx_queue.wr_index) {
        //printf("\n cec no new msg\n");
        return;
    }
    hdmirx_wr_dwc(HDMIRX_DWC_CEC_CTRL, 0x00000002);
    hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA0, 0x04);
    hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA1, tx_queue.msg[tx_queue.rd_index].cmd);
    hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_CNT, tx_queue.msg[tx_queue.rd_index].msg_len);
    if(tx_queue.msg[tx_queue.rd_index].msg_len>2)
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA2, tx_queue.msg[tx_queue.rd_index].msg_data[0]);
    if(tx_queue.msg[tx_queue.rd_index].msg_len>3)
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA3, tx_queue.msg[tx_queue.rd_index].msg_data[1]);
    if(tx_queue.msg[tx_queue.rd_index].msg_len>4)
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA4, tx_queue.msg[tx_queue.rd_index].msg_data[2]);
    if(tx_queue.msg[tx_queue.rd_index].msg_len>5)
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA5, tx_queue.msg[tx_queue.rd_index].msg_data[3]);
    if(tx_queue.msg[tx_queue.rd_index].msg_len>6)
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA6, tx_queue.msg[tx_queue.rd_index].msg_data[4]);
    if(tx_queue.msg[tx_queue.rd_index].msg_len>7)
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA7, tx_queue.msg[tx_queue.rd_index].msg_data[5]);
    if(tx_queue.msg[tx_queue.rd_index].msg_len>8)
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA8, tx_queue.msg[tx_queue.rd_index].msg_data[6]);
    if(tx_queue.msg[tx_queue.rd_index].msg_len>9)
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_TX_DATA9, tx_queue.msg[tx_queue.rd_index].msg_data[7]);

    hdmirx_wr_dwc(HDMIRX_DWC_CEC_CTRL, 0x00000003);
    tx_queue.rd_index = (tx_queue.rd_index+1) % CEC_MSG_QUEUE_SIZE;

    return;
}

extern unsigned int CmdChannelAddData(unsigned int cmd_owner, unsigned char * data);

void hdmi_rx_get_cec_cmd(void)
{
    //int wait_cnt = 0;
    int msg_len = 0;
    int i = 0;
    unsigned char* msg;

#ifndef ENABLE_CEC_FUNCTION
    return;
#endif
    if(hdmirx_rd_dwc(HDMIRX_DWC_CEC_CTRL) != 0x00000002) {
        LOGD(TAG_HDMIRX, "msg error\n");
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_LOCK, 0);
        return;
    }
    msg_len = hdmirx_rd_dwc(HDMIRX_DWC_CEC_RX_CNT);
    msg = (unsigned char *)malloc(msg_len*sizeof(unsigned char));
    if(msg_len <= 1) {
        hdmirx_wr_dwc(HDMIRX_DWC_CEC_LOCK, 0);
        LOGD(TAG_HDMIRX, "msg error report addr\n");
    }
    //msg[0] = hdmirx_rd_dwc(HDMIRX_DWC_CEC_RX_DATA1);
    for(i=0; i<msg_len-2; i++) {
        msg[i] = hdmirx_rd_dwc(HDMIRX_DWC_CEC_RX_DATA1 + i*4);
    }

    CmdChannelAddData(0x10,msg);
    //clr CEC lock bit
    hdmirx_wr_dwc(HDMIRX_DWC_CEC_LOCK, 0);
}




#include <register.h>
#include <common.h>
#include <c_arc_pointer_reg.h>
#include <hdmirx_parameter.h>
#include <hdmi_parameter.h>
#include <hdmirx.h>
#include <log.h>
#include <clk_vpp.h>
#include <vpp.h>
#include <panel.h>
#include <project.h>

// For FBC, define HDMIRX_PHY_AML, and HDMIRX_VID_CEA.
// We need some more configuration for FBC's HDMIRX2.0
// for example: add channel_switch config
//              add CEA video mode config

int irq_unstable_flag = 0;
int irq_stable_flag = 0;
//#define HDMIRX_PHY_SNPS
#define HDMIRX_PHY_AML

//#define HDMIRX_VID_PVO
#define HDMIRX_VID_CEA

//#define DPLL_USE_OSCIN_
#define USE_MANU_CTS_N      0 // 1  //1 //dwc 0x214 bit4 use manual cts&n for debug
#define I2S_OUTPUT_SELECT   1   //0:16bit 1:32bit
#define RX_FOR_REPEATER             0
#define NEW_AUDIO_PLL_SET   //weicheng.zhang

//------------------------------------------------------------------------------
// The following parameters are not to be modified
//------------------------------------------------------------------------------
#if 1

#define TOTAL_PIXELS        (FRONT_PORCH+HSYNC_PIXELS+BACK_PORCH+ACTIVE_PIXELS) // Number of total pixels per line.
#define TOTAL_LINES         (LINES_F0+(LINES_F1*INTERLACE_MODE))                // Number of total lines per frame.

//------------------------------------------------------------------------------
// The following parameters are for CEA interface relative
//------------------------------------------------------------------------------
#define MANUAL_CEA_TIMING       0   // Manual configuration, value for HS and VS generation coming from register bank

//------------------------------------------------------------------------------
// HDCP
//------------------------------------------------------------------------------
#define HDCP_ON                0
#define HDCP_KEY_DECRYPT_EN    0//1

//#define RX_FOR_REPEATER

// [   12] hdmi_mode, not used here
// [   11] max_cascade_exceeded
// [10: 8] depth
// [    7] max_devs_exceeded
// [ 6: 0] device_count
#define BSTATUS_DN              ((0 << 11)  | \
                                 (3 << 8)   | \
                                 (0 << 7)   | \
                                 (5 << 0))


//------------------------------------------------------------------------------
// EDID
//------------------------------------------------------------------------------
#define EDID_EXTENSION_FLAG         1               // Number of 128-bytes blocks that following the basic block
#define EDID_AUTO_CEC_ENABLE        0               // 1=Automatic switch CEC ID
//#define EDID_CEC_ID_ADDR            0x00990098      // EDID address offsets for storing 2-byte of Physical Address
//#define EDID_CEC_ID_DATA            0x1234          // Physical Address: e.g. 0x1023 is 1.0.2.3
#define EDID_CLK_DIVIDE_M1          9               // EDID I2C clock = sysclk / (1+EDID_CLK_DIVIDE_M1).
#define EDID_IN_FILTER_MODE         7               // 0=No in filter; 1=Filter, use every sample;
                                                    // 2=Filter, use 1 sample out of 2 ...; 7=Filter, use 1 sample out of 7.


//------------------------------------------------------------------------------
// Audio
//------------------------------------------------------------------------------
#define TX_I2S_SPDIF        1                       // 0=SPDIF; 1=I2S. Note: Must select I2S if CHIP_HAVE_HDMI_RX is defined.
#define TX_I2S_8_CHANNEL    0                       // 0=I2S 2-channel; 1=I2S 4 x 2-channel.
#define RX_AO_SEL           1                       // Select HDMIRX audio output format: 0=SAO SPDIF; 1=SAO I2S; 2=PAO; 3=Audin decode SPDIF; 4=Audin decode I2S.
#define RX_8_CHANNEL        TX_I2S_8_CHANNEL        // 0=I2S 2-channel; 1=I2S 4 x 2-channel.

#define AUDIO_SAMPLE_RATE   10                      // 0=8kHz; 1=11.025kHz; 2=12kHz; 3=16kHz; 4=22.05kHz; 5=24kHz; 6=32kHz; 7=44.1kHz; 8=48kHz; 9=88.2kHz; 10=96kHz; 11=192kHz; 12=768kHz; Other=48kHz.
#define AUDIO_PACKET_TYPE   HDMI_AUDIO_PACKET_SMP   // 2=audio sample packet; 7=one bit audio; 8=DST audio packet; 9=HBR audio packet.
#define EXP_AUDIO_LENGTH    (RX_8_CHANNEL?2304:9216)    // exp/i2s_data.exp file length

// For Audio Clock Recovery
#define ACR_MODE            0                       // Select which ACR scheme:
                                                    // 0=Analog PLL based ACR;
                                                    // 1=Digital ACR.
#define AUDPLL_X4           0                       // 0=Clock recovery output 256xFs; 1=Clock recovery output 512xFs.

#define MANUAL_ACR_N        6144
#define MANUAL_ACR_CTS      297000//((RX_COLOR_DEPTH==HDMI_COLOR_DEPTH_24B)? 74250 : (RX_COLOR_DEPTH==HDMI_COLOR_DEPTH_30B)? 74250*5/4 : (RX_COLOR_DEPTH==HDMI_COLOR_DEPTH_36B)? 74250*3/2 : 74250*2)
#define EXPECT_ACR_N        12288
#define EXPECT_ACR_CTS      ((RX_COLOR_DEPTH==HDMI_COLOR_DEPTH_24B)? 148500 : (RX_COLOR_DEPTH==HDMI_COLOR_DEPTH_30B)? 148500*5/4 : (RX_COLOR_DEPTH==HDMI_COLOR_DEPTH_36B)? 148500*3/2 : 148500*2)

#define EXPECT_MEAS_RESULT  154184                  // = T(audio_master_clk) * meas_clk_cycles / T(hdmi_audmeas_ref_clk); where meas_clk_cycles=4096; T(hdmi_audmeas_ref_clk)=4.704 ns.

//------------------------------------------------------------------------------
// TMDS clock measure
//------------------------------------------------------------------------------
#define EXPECT_TMDS_MEAS    50687                   // = T(ref_clk) * ref_cycles / T(tmds_clk);  where ref_cycles=8192; T(ref_clk)=41.666 ns.
#define EXPECT_CABLE_MEAS   50687                   // = T(ref_clk) * ref_cycles / T(cable_clk); where ref_cycles=8192; T(ref_clk)=41.666 ns.

//------------------------------------------------------------------------------
// Video
//------------------------------------------------------------------------------
//video format vic
#define HDMI_1080P50        31
#define HDMI_1080P60        16
#define HDMI_3840_2160P50   96
#define HDMI_3840_2160P60   97

#define VIC                 HDMI_1080P60                      // Video format identification code: 640x480p@59.94/60Hz
#define INTERLACE_MODE      0                       // 0=Progressive; 1=Interlace.
#define PIXEL_REPEAT_HDMI   (1-1)                   // Pixel repeat factor seen by HDMI TX
#define SCRAMBLER_EN        0

// TODO #define MODE_3D             0                       // Define it to enable 3D mode: 1=3D frame-packing; 2=3D side-by-side; 3=3D top-and-bottom.
#define ACTIVE_SPACE        0                       // For 3D: Number of lines inserted between two active video regions.

#if ((VIC==HDMI_3840_2160P60)||(VIC==HDMI_3840_2160P50))
#define TMDS_CLK_DIV4       1                       // 0:TMDS_CLK_rate=TMDS_Character_rate; 1:TMDS_CLK_rate=TMDS_Character_rate/4, for TMDS_Character_rate>340Mcsc.
//#define ACTIVE_PIXELS       (640*(1+PIXEL_REPEAT_HDMI)) // Number of active pixels per line.
//#define ACTIVE_LINES        (480/(1+INTERLACE_MODE))    // Number of active lines per field.
#define ACTIVE_PIXELS       (3840/2*(1+PIXEL_REPEAT_HDMI))    // Number of active pixels per line.
#define ACTIVE_LINES        (2160/2/(1+INTERLACE_MODE))       // Number of active lines per field.
#define LINES_F0            2250                    // Number of lines in the even field.
#define LINES_F1            2250                    // Number of lines in the odd field.
#define FRONT_PORCH         (176/2)                     // Number of pixels from DE Low to HSYNC high.
#define HSYNC_PIXELS        (88/2)                      // Number of pixels of HSYNC pulse.
#define BACK_PORCH          (296/2)                     // Number of pixels from HSYNC low to DE high.
#define EOF_LINES           8                       // HSYNC count between last line of active video and start of VSYNC
                                                    // a.k.a. End of Field (EOF). In interlaced mode,
                                                    // HSYNC count will be eof_lines at the end of even field
                                                    // and eof_lines+1 at the end of odd field.
#define VSYNC_LINES         10                      // HSYNC count of VSYNC assertion
                                                    // In interlaced mode VSYNC will be in-phase with HSYNC in the even field and
                                                    // out-of-phase with HSYNC in the odd field.
#define SOF_LINES           72                      // HSYNC count between VSYNC de-assertion and first line of active video
#define HSYNC_POLARITY      1                       // TX HSYNC polarity: 0=low active; 1=high active.
#define VSYNC_POLARITY      1                       // TX VSYNC polarity: 0=low active; 1=high active.
#define TOTAL_FRAMES        3                       // Number of frames to run in simulation
#define VIU_DISPLAY_ON                              // Define it to enable viu display
// #define TX_COLOR_DEPTH          HDMI_COLOR_DEPTH_30B    // Pixel bit width: 4=24-bit; 5=30-bit; 6=36-bit; 7=48-bit.
#define TX_COLOR_DEPTH          HDMI_COLOR_DEPTH_24B    // Pixel bit width: 4=24-bit; 5=30-bit; 6=36-bit; 7=48-bit.
#define RX_COLOR_DEPTH          TX_COLOR_DEPTH          // Pixel bit width: 4=24-bit; 5=30-bit; 6=36-bit; 7=48-bit.
#define TX_INPUT_COLOR_FORMAT   HDMI_COLOR_FORMAT_RGB   // Pixel format: 0=RGB444; 1=YCbCr422; 2=YCbCr444; 3=YCbCr420.
#define TX_OUTPUT_COLOR_FORMAT  HDMI_COLOR_FORMAT_RGB   // Pixel format: 0=RGB444; 1=YCbCr422; 2=YCbCr444; 3=YCbCr420.
#define RX_COLOR_FORMAT         TX_OUTPUT_COLOR_FORMAT  // Pixel format: 0=RGB444; 1=YCbCr422; 2=YCbCr444; 3=YCbCr420.
#define TX_INPUT_COLOR_RANGE    HDMI_COLOR_RANGE_LIM    // Pixel range: 0=limited; 1=full.
#define TX_OUTPUT_COLOR_RANGE   HDMI_COLOR_RANGE_LIM    // Pixel range: 0=limited; 1=full.

#else
#define TMDS_CLK_DIV4       0                       // 0:TMDS_CLK_rate=TMDS_Character_rate; 1:TMDS_CLK_rate=TMDS_Character_rate/4, for TMDS_Character_rate>340Mcsc.
#define ACTIVE_PIXELS       (1920*(1+PIXEL_REPEAT_HDMI)) // Number of active pixels per line.
#define ACTIVE_LINES        (1080/(1+INTERLACE_MODE))    // Number of active lines per field.
#define LINES_F0            1125                    // Number of lines in the even field.
#define LINES_F1            1125                    // Number of lines in the odd field.
#define FRONT_PORCH         88                      // Number of pixels from DE Low to HSYNC high.
#define HSYNC_PIXELS        44                      // Number of pixels of HSYNC pulse.
#define BACK_PORCH          148                     // Number of pixels from HSYNC low to DE high.
#define EOF_LINES           4                       // HSYNC count between last line of active video and start of VSYNC
                                                    // a.k.a. End of Field (EOF). In interlaced mode,
                                                    // HSYNC count will be eof_lines at the end of even field
                                                    // and eof_lines+1 at the end of odd field.
#define VSYNC_LINES         5                       // HSYNC count of VSYNC assertion
                                                    // In interlaced mode VSYNC will be in-phase with HSYNC in the even field and
                                                    // out-of-phase with HSYNC in the odd field.
#define SOF_LINES           36                      // HSYNC count between VSYNC de-assertion and first line of active video
#define HSYNC_POLARITY      1                       // TX HSYNC polarity: 0=low active; 1=high active.
#define VSYNC_POLARITY      1                       // TX VSYNC polarity: 0=low active; 1=high active.
#define TOTAL_FRAMES        3                       // Number of frames to run in simulation
#define VIU_DISPLAY_ON                              // Define it to enable viu display
// #define TX_COLOR_DEPTH          HDMI_COLOR_DEPTH_30B    // Pixel bit width: 4=24-bit; 5=30-bit; 6=36-bit; 7=48-bit.
#define TX_COLOR_DEPTH          HDMI_COLOR_DEPTH_24B    // Pixel bit width: 4=24-bit; 5=30-bit; 6=36-bit; 7=48-bit.
#define RX_COLOR_DEPTH          TX_COLOR_DEPTH          // Pixel bit width: 4=24-bit; 5=30-bit; 6=36-bit; 7=48-bit.
#define TX_INPUT_COLOR_FORMAT   HDMI_COLOR_FORMAT_422   // Pixel format: 0=RGB444; 1=YCbCr422; 2=YCbCr444; 3=YCbCr420.
#define TX_OUTPUT_COLOR_FORMAT  HDMI_COLOR_FORMAT_422   // Pixel format: 0=RGB444; 1=YCbCr422; 2=YCbCr444; 3=YCbCr420.
#define RX_COLOR_FORMAT         TX_OUTPUT_COLOR_FORMAT  // Pixel format: 0=RGB444; 1=YCbCr422; 2=YCbCr444; 3=YCbCr420.
#define TX_INPUT_COLOR_RANGE    HDMI_COLOR_RANGE_LIM    // Pixel range: 0=limited; 1=full.
#define TX_OUTPUT_COLOR_RANGE   HDMI_COLOR_RANGE_LIM    // Pixel range: 0=limited; 1=full.
#endif

//unsigned char   aksv_received = 0;    // Used for testing repeater, ignored if the test is receiver-only
#endif
void hdmirx_wr_only_top (unsigned long addr, unsigned long data)
{
    unsigned long base_offset = INT_HDMIRX_BASE_OFFSET;
    unsigned long dev_offset = 0;       // INT TOP ADDR_PORT: 0xc800e000; INT DWC ADDR_PORT: 0xc800e010
                                        // EXT TOP ADDR_PORT: 0xc800e020; EXT DWC ADDR_PORT: 0xc800e030
    *((volatile unsigned long *) (HDMIRX_ADDR_PORT+base_offset+dev_offset)) = addr;
    *((volatile unsigned long *) (HDMIRX_DATA_PORT+base_offset+dev_offset)) = data;
} /* hdmirx_wr_only_TOP */

void hdmirx_wr_only_dwc (unsigned long addr, unsigned long data)
{
    unsigned long base_offset = INT_HDMIRX_BASE_OFFSET;
    unsigned long dev_offset = 0x10;    // INT TOP ADDR_PORT: 0xc800e000; INT DWC ADDR_PORT: 0xc800e010
                                        // EXT TOP ADDR_PORT: 0xc800e020; EXT DWC ADDR_PORT: 0xc800e030
    *((volatile unsigned long *) (HDMIRX_ADDR_PORT+base_offset+dev_offset)) = addr;
    *((volatile unsigned long *) (HDMIRX_DATA_PORT+base_offset+dev_offset)) = data;
} /* hdmirx_wr_only_DWC */

unsigned long hdmirx_rd_top (unsigned long addr)
{
    unsigned long base_offset = INT_HDMIRX_BASE_OFFSET;
    unsigned long dev_offset = 0;       // INT TOP ADDR_PORT: 0xc800e000; INT DWC ADDR_PORT: 0xc800e010
                                        // EXT TOP ADDR_PORT: 0xc800e020; EXT DWC ADDR_PORT: 0xc800e030
    unsigned long data;
    *((volatile unsigned long *) (HDMIRX_ADDR_PORT+base_offset+dev_offset)) = addr;
    data = *((volatile unsigned long *) (HDMIRX_DATA_PORT+base_offset+dev_offset));
    return (data);
} /* hdmirx_rd_TOP */

unsigned long hdmirx_rd_dwc (unsigned long addr)
{
    unsigned long base_offset = INT_HDMIRX_BASE_OFFSET;
    unsigned long dev_offset = 0x10;    // INT TOP ADDR_PORT: 0xc800e000; INT DWC ADDR_PORT: 0xc800e010
                                        // EXT TOP ADDR_PORT: 0xc800e020; EXT DWC ADDR_PORT: 0xc800e030
    unsigned long data;
    *((volatile unsigned long *) (HDMIRX_ADDR_PORT+base_offset+dev_offset)) = addr;
    data = *((volatile unsigned long *) (HDMIRX_DATA_PORT+base_offset+dev_offset));
    return (data);
} /* hdmirx_rd_DWC */

void hdmirx_rd_check_dwc (unsigned long addr, unsigned long exp_data, unsigned long mask)
{
     unsigned long rd_data;
     rd_data = hdmirx_rd_dwc(addr);
     if ((rd_data | mask) != (exp_data | mask))
     {
         printf("hdmirx check dwc reg:%x data:%x != exp_data:%x\n",addr, rd_data, exp_data);
     }
} /* hdmirx_rd_check_DWC */
void hdmirx_wr_top (unsigned long addr, unsigned long data)
{
    hdmirx_wr_only_top(addr, data);
} /* hdmirx_wr_TOP */

void hdmirx_wr_dwc (unsigned long addr, unsigned long data)
{
    hdmirx_wr_only_dwc(addr, data);
} /* hdmirx_wr_DWC */

void hdmirx_poll_dwc (unsigned long addr, unsigned long exp_data, unsigned long mask)
{
    unsigned long rd_data;
    unsigned char max_try = 50;
    unsigned long cnt   = 0;
    unsigned char done  = 0;

    rd_data = hdmirx_rd_dwc(addr);
    while (((cnt < max_try) || (max_try == 0)) && (done != 1)) {
        if ((rd_data | mask) == (exp_data | mask)) {
            done = 1;
        } else {
            cnt ++;
            rd_data = hdmirx_rd_dwc(addr);
        }
    }
    if (done == 0) {
        LOGE(TAG_HDMIRX, "[HDMIRX.C] Error: hdmirx_poll_dwc access time-out!\n");
    }
} /* hdmirx_poll_DWC */

const unsigned char rx_edid[256]  =
{
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x05, 0xAC, 0x02, 0x2C, 0x01, 0x01, 0x01, 0x01,
    0x26, 0x18, 0x01, 0x03, 0x80, 0x85, 0x4B, 0x78, 0x0A, 0x0D, 0xC9, 0xA0, 0x57, 0x47, 0x98, 0x27,
    0x12, 0x48, 0x4C, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x74, 0x00, 0x30, 0xF2, 0x70, 0x5A, 0x80, 0xB0, 0x58,
    0x8A, 0x00, 0x20, 0xC2, 0x31, 0x00, 0x00, 0x1E, 0x08, 0xE8, 0x00, 0xA0, 0xF5, 0x70, 0x5A, 0x80,
    0xB0, 0x58, 0x8A, 0x00, 0x20, 0xC2, 0x31, 0x00, 0x00, 0x1E, 0x04, 0x74, 0x00, 0x30, 0xf2, 0x70,
    0x5a, 0x80, 0xb0, 0x58, 0x8a, 0x00, 0x20, 0xc2, 0x31, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0xFc,
    0x00, 0x41, 0x4d, 0x4c, 0x20, 0x46, 0x42, 0x43, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0xc2,
    0x02, 0x03, 0x1F, 0xF0, 0x43, 0x5F, 0x61, 0x5E, 0x23, 0x09, 0x07, 0x01, 0x83, 0x01, 0x00, 0x00,
    0x6E, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x3C, 0x20, 0xA0, 0x42, 0x03, 0x02, 0x81, 0x7F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03
};

void hdmirx_edid_setting (void)
{
    int i=0;
    for (i=0; i<256; i++){
        hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+i, rx_edid[i]);
    }
	//----------------------User EDID----------------------------
	//ManufactureID
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+8, panel_param->ManufactureID[0]);
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+9, panel_param->ManufactureID[1]);
	//ProductID
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+10, panel_param->ProductID[0]);
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+11, panel_param->ProductID[1]);
	//SerialNumber
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+12, panel_param->SerialNumber[0]);
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+13, panel_param->SerialNumber[1]);
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+14, panel_param->SerialNumber[2]);
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+15, panel_param->SerialNumber[3]);
	//ManufactureDate
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+16, panel_param->ManufactureDate[0]);
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+17, panel_param->ManufactureDate[1]);
	//ChipID
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+250, panel_param->ChipID[0]);
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+251, panel_param->ChipID[1]);
	//panel info | 3d info
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+252, panel_param->PanelInfo|(panel_param->ThreeDinfo << 4));
	//SpecicalInfo
	hdmirx_wr_top(HDMIRX_TOP_EDID_OFFSET+253, panel_param->SpecicalInfo);

} /* hdmirx_edid_setting */


void hdmirx_key_setting (unsigned char   encrypt_en)
{
} /* hdmirx_key_setting */
#if 0
void hdmirx_repeater_config (unsigned long bstatus,unsigned short *ksv)
{
    unsigned int    i;
    unsigned int    device_count;
    unsigned long   ksv_hi, ksv_lo;

    device_count    = bstatus & 0x7f;

    // Write Bstatus
    LOGD(TAG_HDMIRX, "[HDMIRX.C] Repeater: write Bstatus...\n");
    hdmirx_wr_dwc(HDMIRX_DWC_HDCP_RPT_BSTATUS,   bstatus);
    // Wait until waiting_ksv = 1
    LOGD(TAG_HDMIRX, "[HDMIRX.C] Repeater: wait for 1st part authentication to complete...\n");
    hdmirx_poll_dwc(HDMIRX_DWC_HDCP_RPT_CTRL, (1<<5), ~(1<<5), 0);
    // Write KSV
    LOGD(TAG_HDMIRX, "[HDMIRX.C] Repeater: write KSV...\n");
    for (i = 0; i < device_count; i ++) {
        ksv_hi  = ksv[i*5+4]&0xff;
        ksv_lo  = ((ksv[i*5+3]&0xff)<<24) | ((ksv[i*5+2]&0xff)<<16) | ((ksv[i*5+1]&0xff)<<8) | ((ksv[i*5]&0xff)<<0);
        hdmirx_poll_dwc(HDMIRX_DWC_HDCP_RPT_CTRL, (0<<6), ~(1<<6), 0);         // Wait for ksv_hold=0
        hdmirx_wr_dwc(HDMIRX_DWC_HDCP_RPT_KSVFIFO_CTRL,  i);
        hdmirx_wr_only_dwc(HDMIRX_DWC_HDCP_RPT_KSVFIFO1, ksv_hi);
        hdmirx_wr_only_dwc(HDMIRX_DWC_HDCP_RPT_KSVFIFO0, ksv_lo);
    }
    hdmirx_poll_dwc(HDMIRX_DWC_HDCP_RPT_CTRL, (0<<6), ~(1<<6), 0);             // Wait for ksv_hold=0
    // SW indicate completion of KSV write
    hdmirx_wr_only_dwc(HDMIRX_DWC_HDCP_RPT_CTRL, hdmirx_rd_dwc(HDMIRX_DWC_HDCP_RPT_CTRL) | (1<<2));
    // Wait for HW completion of V value
    LOGD(TAG_HDMIRX, "[HDMIRX.C] Repeater: wait for 2nd part authentication to complete...\n");
    hdmirx_poll_dwc(HDMIRX_DWC_HDCP_RPT_CTRL, (1<<4), ~(1<<4), 0);             // Wait for ready=1
    LOGD(TAG_HDMIRX, "[HDMIRX.C] Repeater: ...done\n");
} /* hdmirx_repeater_config */
#endif
void aocec_poll_reg_busy (unsigned char reg_busy)
{
    if (reg_busy) {
        LOGD(TAG_HDMIRX, "[HDMIRX.C] Polling AO_CEC reg_busy=1\n");
    } else {
        LOGD(TAG_HDMIRX, "[HDMIRX.C] Polling AO_CEC reg_busy=0\n");
    }
    while (((*P_AO_CEC_RW_REG) & (1 << 23)) != (reg_busy << 23)) {
        delay_us(31);
    }
} /* aocec_poll_reg_busy */

void aocec_wr_only_reg (unsigned long addr, unsigned long data)
{
    unsigned long data32;

    aocec_poll_reg_busy(0);

    data32  = 0;
    data32 |= (1    << 16); // [16]     cec_reg_wr
    data32 |= (data << 8);  // [15:8]   cec_reg_wrdata
    data32 |= (addr << 0);  // [7:0]    cec_reg_addr
    (*P_AO_CEC_RW_REG) = data32;
} /* aocec_wr_only_reg */

unsigned long aocec_rd_reg (unsigned long addr, unsigned int check_busy_high)
{
    unsigned long data32;

    aocec_poll_reg_busy(0);

    data32  = 0;
    data32 |= (0    << 16); // [16]     cec_reg_wr
    data32 |= (0    << 8);  // [15:8]   cec_reg_wrdata
    data32 |= (addr << 0);  // [7:0]    cec_reg_addr
    (*P_AO_CEC_RW_REG) = data32;

    // When CEC clock is as fast as clk81 (~200MHz), we may miss Busy=1 pulse, which will call the test hang.
    // Checking busy=low is enough for correct operation. Checking busy=high is only for simulation test coverage.
    if (check_busy_high) {
        aocec_poll_reg_busy(1);
    }
    aocec_poll_reg_busy(0);

    data32 = ((*P_AO_CEC_RW_REG) >> 24) & 0xff;

    return (data32);
} /* aocec_rd_reg */

void aocec_rd_check_reg (unsigned long addr, unsigned long exp_data, unsigned long mask, unsigned int check_busy_high)
{
    unsigned long rd_data;
    rd_data = aocec_rd_reg(addr, check_busy_high);
    if ((rd_data | mask) != (exp_data | mask))
    {
        LOGD(TAG_HDMIRX, "[HDMIRX.C] AO-CEC addr=0x%08x rd_data=0x%08x\n", addr, rd_data);
        LOGD(TAG_HDMIRX, "[HDMIRX.C] Error: AO-CEC exp_data=0x%08x mask=0x%08x\n", exp_data, mask);
    }
} /* aocec_rd_check_reg */

void aocec_wr_reg (unsigned long addr, unsigned long data)
{
    aocec_wr_only_reg(addr, data);
    aocec_rd_check_reg(addr, data, 0, 1);
} /* aocec_wr_reg */

void aocec_wr_reg_fast (unsigned long addr, unsigned long data)
{
    aocec_wr_only_reg(addr, data);
    aocec_rd_check_reg(addr, data, 0, 0);
} /* aocec_wr_reg_fast */

void hdmi_rx_set_hpd(int status)
{

    status = status;
}
//hdmirx top irq enable partially
void hdmi_rx_irq_init(void)
{
    unsigned long data32 = 0;
    /*
    data32 |= (1    << 27); // [   27] meter_stable_chg_cable
    data32 |= (1    << 26); // [   26] vid_stable_fall[7] -- Active line count unstable
    data32 |= (1    << 25); // [   25] vid_stable_fall[6] -- Vsync line count unstable
    data32 |= (1    << 24); // [   24] vid_stable_fall[5] -- EOF line count unstable
    data32 |= (1    << 23); // [   23] vid_stable_fall[4] -- SOF line count unstable
    data32 |= (1    << 22); // [   22] vid_stable_fall[3] -- Active pixel count unstable
    data32 |= (1    << 21); // [   21] vid_stable_fall[2] -- Hsync pixel count unstable
    data32 |= (1    << 20); // [   20] vid_stable_fall[1] -- Front porch pixel count unstable
    data32 |= (1    << 19); // [   19] vid_stable_fall[0] -- Back porch pixel count unstable
    data32 |= (1    << 18); // [   18] vid_stable_rise[7] -- Active line count stable.
    data32 |= (1    << 17); // [   17] vid_stable_rise[6] -- Vsync line count stable
    data32 |= (1    << 16); // [   16] hdcp_enc_state_fall
    data32 |= (1    << 15); // [   15] hdcp_enc_state_rise
    data32 |= (1    << 14); // [   14] hdcp_auth_start_fall
    data32 |= (1    << 13); // [   13] hdcp_auth_start_rise
    data32 |= (1    << 12); // [   12] meter_stable_chg_hdmi
    data32 |= (1    << 11); // [   11] vid_colour_depth_chg
    data32 |= (1    << 10); // [   10] vid_fmt_chg
    data32 |= (1    << 9);  // [    9] vid_stable_rise[5] -- EOF line count stable
    data32 |= (1    << 8);  // [    8] vid_stable_rise[4] -- SOF line count stable
    data32 |= (1    << 7);  // [    7] vid_stable_rise[3] -- Active pixel count stable
    data32 |= (1    << 6);  // [    6] hdmirx_5v_fall
    data32 |= (1    << 5);  // [    5] vid_stable_rise[2] -- Hsync pixel count stable
    data32 |= (1    << 4);  // [    4] vid_stable_rise[1] -- Front porch pixel count stable
    data32 |= (1    << 3);  // [    3] vid_stable_rise[0] -- Back porch pixel count stable
    */
    data32 |= (1    << 2);  // [    2] hdmirx_5v_rise
    //data32 |= (1    << 1);  // [    1] edid_addr_intr
    //data32 |= (1    << 0);  // [    0] core_intr_rise: sub-interrupts will be configured later
    hdmirx_wr_top(HDMIRX_TOP_INTR_MASKN,  data32);
}

#ifdef IN_FBC_MAIN_CONFIG
void hdmi_rx_init(void)
{
    //hdmi_rx_clk_init();
    hdmi_rx_irq_init();
}
//hdmitx 5v detect & HPD set
static int HPD_Set_by_top_irq(void)
{
    /*
    if(hdmi_tx_5v_rise == true){
        HPD_HIGH;
        hdmi_tx_5v_status = 1;
        hdmi_tx_5v_rise = false;
        return;
    }else if(hdmi_tx_5v_fall == true){
        HPD_LOW;
        hdmi_tx_5v_status = 0;
        hdmi_tx_5v_fall = false;
        return;
    }
    */
    return 0;
}

void hdmirx_phy_init(void)
{
    unsigned long data32;
    int i = 15;
    int result = 1;
    int count = 10;

    data32  = 0;
    data32 |= 0 << 31;//[31]  CDR_BY_PI
    data32 |= 1 << 30;//[30]  CDR_LK_BY
    data32 |= 0 << 29;//[29]  CH_TSTCLK_BUF_PU
    data32 |= 1 << 28;//[28] CH_IQBUF_PU
    data32 |= 2 << 26;//[27: 26] CH_IQBUF_SEL
    data32 |= 0 << 25;//[25] PI_IQSEL
    data32 |= 1 << 24;//[24] PI_PHSEL
    data32 |= 0 << 16;//[23:16] NA
    data32 |= 0 << 12;//[15:12]  TX_IDR
    data32 |= 0 << 10;//[11:10]  COMMON_TX1_PU/COMMON_TX0_PU
    data32 |= 0 << 0; //[9:0]  NA
    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_0, data32);
    if(OUTPUT_LVDS == panel_param->output_mode){
        data32  = 0;
        data32 |= 0 << 24;//[31:24] NA
        data32 |= 1 << 23;//[23] RCAL_PU
        data32 |= 1 << 22;//[22] RCAL_IBSEL
        data32 |= 0 << 21;//[21] RTERM_TEST_EN
        data32 |= 0 << 19;//[20:19]  NA
        data32 |= 1 << 18;//[18] CH_RTERM_EN
        data32 |= 1 << 17;//[17] CKAMP_PU
        data32 |= 1 << 16;//[16] CKAMP_PU
        //data32 |= 0x0f << 12;//[15:12] CH_RTERM_SET
        data32 |= 0 << 8;//[11:8]ANA_TST_SEL
        data32 |= 1 << 7;//[7] IGENOP_IBSEL
        data32 |= 1 << 6;//[6] IGEN_TYPE_SEL
        data32 |= 1 << 5;//[5]  IGEN_PU
        data32 |= 1 << 4;//[4]  BG_PU
        data32 |= 2 << 0; //[3:0]  IB100U_250U_TOCH
        for(i=15; i>=0; i--)
        {
            hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_1, (data32 | (i<<12)));
            delay_us(10);
            result = hdmirx_rd_top(HDMIRX_TOP_PHY_STAT_0) & 1;
            if(result == 0)
                break;
        }
        if(result != 0)
            printf("Hdmirx : resistor auto calibration fail\n");
        //disable calibration
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_1, (data32 | (i<<12) & (~(1<<23))));
    }else{
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_1, 0x47b0f2);//0x47a0f4
    }

    data32  = 0;
    data32 |= 0 << 22;//[31:22] NA
    data32 |= 2 << 20;//[2:20]LDO_VREF
    data32 |= 1 << 19;//19] CH2_PU/LDO2_PU
    data32 |= 1 << 18;//18] CH1_PU/LDO1_PU
    data32 |= 1 << 17;//[17] LDO_OP_IBSELST_SEL
    data32 |= 1 << 16;//[16]CH0_PU/LDO0_PU
    data32 |= 1 << 15;//[15]CH_ISINK_IBSEL
    data32 |= 10<< 10;//[14:10]BIAS_PI
    data32 |= 8 << 5;//[9: 5]IBIAS_EQ
    data32 |= 24<< 0; //[4:0]  IBIAS_DCC
    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_2, data32);

    if(OUTPUT_LVDS == panel_param->output_mode){
        data32  = 0;
        data32 |= 1 << 30;//[31:30]DR_BC
        data32 |= 21<< 21;//[29:21]CDR_PG
        data32 |= 0 << 20;//[20] CDR_BYPASS
        data32 |= 32<< 14;//[19:14]CDR_BY_CMPN
        data32 |= 8 << 10;//[13:10] CDR_CMPN_C
        data32 |= 0 << 9;//[9] CDR_PI_OFE_EN
        data32 |= 4 << 6;//[8:6] CDR_PI_OFE
        data32 |= 32<< 0; //[5:0] CDR_BY_PI_IN
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_3, data32);
    }else{
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_3, 0x71482120);//0x71082120
    }

    data32  = 0;
    data32 |= 0 << 15;// [15] TMDSVALID_SEL 0: 3ch valid and 1: manual ctrl
    data32 |= 0 << 14;// [14] TMDSVALID_MANUAL
    data32 |= 0 << 13;// [13] PLL_CKREF_SEL  0: from cable 1:from CFGCLK
    data32 |= 0 << 0; // [0:12]NA
    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_4, data32);//HDMIRX_PHY_HRX_MPLL_CTL0

    data32  = 0;
    data32 |= 0 << 29;//[31:29] TMDSCLK_SEL 000: tmds_pll, 100:bist_ch0_plldiv  001: bist_ch1_plldiv, 011: bist_ch2_plldiv
    data32 |= 1 << 28;//[28] TOP_IQBUF_PU_PLL1
    data32 |= 2 << 26;//[27:26]TOP_IQBUF_SEL
    data32 |= 0 << 25;///[25] TOP_IQBUF_PU_PLL2
    data32 |= 0 << 23;///[24:23]TOP_IQBUF_SEL_PLL2
    data32 |= 0 << 18;//[22:18]NA
    data32 |= 0 << 17; //[17]  TOP_DFF_BIST_BUF_RB
    data32 |= 1 << 16; //[16]  TOP_DFF_RESAMP_RB
    data32 |= 0 << 0;// [15:0] PLL1
    hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_5, data32);

    data32  = 0;
    //bit[31:16]
    if(OUTPUT_LVDS == panel_param->output_mode){
        data32 |= 0 << 31;//[31]  LONG_BIST_SEL
        data32 |= 0 << 30;//[30] LONG_BIST_SEL
        data32 |= 1 << 29;//[29] EQ3_AMP_RESX2
        data32 |= 0 << 28;//[28] BIST_TX_ICTL
        if(HDMI_PORT_SWITCH == HDMI_PORT_A)
        data32 |= 1 << 24;//[27:24]BIST_TX_ICTL  //channel swap
        else
			data32 |= 0 << 24;//[27:24]BIST_TX_ICTL  //channel swap
        data32 |= 0 << 23;//[23] SER_EN
        data32 |= 0 << 22;//[22] SER_EN
        data32 |= 0 << 21;//[21]    SER_SELF_TEST
        data32 |= 0 << 20;//[20] TST_DAT_SEL
        data32 |= 0 << 19;//[19] DES_DIVSEL
        data32 |= 0 << 18;//[18] DES_MC23
        data32 |= 0 << 17;//[17] HFSAMP_DFF_RN
        data32 |= 1 << 16;//[16] PI_PU
        //bit[15:0]
        data32 |= 1 << 15;//[15] EQ1_RS
        data32 |= 4 << 12;//[14:12]EQ1_RS
        data32 |= 8 << 8;//[11:8]EQ1_RS
        data32 |= 0 << 5;//[7:5] EQ2_CS
        data32 |= 0 << 4;//[4] EQ_BYPASS
        data32 |= 4 << 1;//[3:1] EQ2_RS
        data32 |= 0 << 0; //[0] NA
        //hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6, data32);//HDMIRX_PHY_TMDSCH0_CTL0
        //hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7, data32);//HDMIRX_PHY_TMDSCH1_CTL0
        //hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8, data32);//HDMIRX_PHY_TMDSCH2_CTL0
        //delay_us(10);
        data32 |= 1 << 17;
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6, data32);//HDMIRX_PHY_TMDSCH0_CTL0
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7, data32);//HDMIRX_PHY_TMDSCH1_CTL0
        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8, data32);//HDMIRX_PHY_TMDSCH2_CTL0
    }else{
    	if((get_ic_version() == 2) || (HDMI_PORT_SWITCH == HDMI_PORT_B)){
			hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6, 0x39a9a);
	        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7, 0x39a9a);
	        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8, 0x39a9a);
		}else{
	        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_6, 0x1039a9a);
	        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_7, 0x1039a9a);
	        hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_8, 0x1039a9a);
		}
    }

#if 0
    data32  = 0;
    data32 |= 0 << 31;//[31]  HDMI_RX_DPLL_LOCK
    data32 |= 1 << 30;//[30]  HDMI_RX_DPLL_EN
    data32 |= 1 << 29;//[29]  HDMI_RX_DPLL_RESET
#if(VIC == HDMI_1080P50 || VIC == HDMI_1080P60 || VIC == HDMI_3840_2160P50 || VIC == HDMI_3840_2160P60)
    data32 |= 4 << 9;//[28:24]HDMI_RX_DPLL_N
#else
    data32 |= 3 << 24;//[28:24]HDMI_RX_DPLL_N
#endif
    data32 |= 0 << 23;//[23]  Not used
    data32 |= 0 << 20;//[22:20]HDMI_RX_EQ_SEL
    data32 |= 0 << 19;//[19 ] Not used
    data32 |= 0 << 16;//[18:16]HDMI_RX_AUDIO_RATE
    data32 |= 0 << 15;//[15] HDMI_RX_AFC_DONE
    data32 |= 3 << 13;//[14:13] HDMI_RX_DPLL_CLK_EN
    data32 |= 0 << 11;//[12:11]  HDMI_RX_DPLL_OD1
    data32 |= 0 << 9;//[10:9]  HDMI_RX_DPLL_OD
#if(VIC == HDMI_1080P50 || VIC == HDMI_1080P60 || VIC == HDMI_3840_2160P50 || VIC == HDMI_3840_2160P60)
    data32 |= 0x50 << 0; //[8:0]  HDMI_RX_DPLL_M
#else
    data32 |=0x0f<<0; //[8:0]  HDMI_RX_DPLL_M
#endif
    hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, data32);

    data32  = 0;
    data32 |= 0 << 29;//[31:29]  Not used
    data32 |= 0 << 28;//[28] HDMI_RX_DPLL_DPFD_LMODE
    data32 |= 1 << 26;//[27:26]  HDMI_RX_DC_VC_IN
    data32 |= 0 << 24;//[25:24]  HDMI_RX_DCO_SDMCK_SEL
    data32 |= 0 << 23;//[23] HDMI_RX_DCO_M_EN
    data32 |= 0 << 22;//[22] Not used
    data32 |= 1 << 21;//[21] HDMI_RX_DPLL_SDM_PR_EN
    data32 |= 0 << 20;//[20] HDMI_RX_DPLL_DIV_MODE
    data32 |= 1 << 17;//[19:17] Not used
    data32 |= 1 << 16;//[16]  HDMI_RX_DPLL_BGP_EN
    data32 |= 5 << 12;//[15:12]  HDMI_RX_DPLL_BGP_C
    data32 |= 0 << 0; //[11:0]  HDMI_RX_DPLL_DIV_FRAC
    hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, data32);


    data32  = 0;
    data32 |= 0 << 30;//[31:30] Not used
    data32 |= 2 << 26;//[29:26] HDMI_RX_DPLL_FILTER_PVT2
    data32 |= 9 << 22;//[25:22]  HDMI_RX_DPLL_FILTER_PVT1
    data32 |= 0x221 << 11;//[21:11]  HDMI_RX_DPLL_FILTER_ACQ2
    data32 |= 0x6c7 << 0; //[10:0]  HDMI_RX_DPLL_FILTER_ACQ1
    hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, data32);


    data32  = 0;
    data32 |= 0 << 26;//[31:26]  Not used
    data32 |= 1 << 25;//[25]  HDMI_RX_DPLL_PVT_FIX_EN
    data32 |= 0 << 24;//[24]  Not used
    data32 |= 2 << 22;//[23:22]  HDMI_RX_DPLL_DCO_IUP
    data32 |= 0 << 18;//[21:18] HDMI_RX_DPLL_SS_AMP
    data32 |= 0 << 14;//[17:14] HDMI_RX_DPLL_SS_CLK
    data32 |= 0 << 13;//[13] HDMI_RX_DPLL_SSEN
    data32 |= 1 << 12;//[12] HDMI_RX_DPLL_DCO_SDM_EN
    data32 |= 1 << 11;//[11] HDMI_RX_DPLL_IIR_BYPASS_N
    data32 |= 1 << 10;//[10]  HDMI_RX_DPLL_TDC_EN
    data32 |= 0X0A << 6;//[9:6]  HDMI_RX_DPLL_LM_W
    data32 |= 0x37 << 0; //[5:0]  HDMI_RX_DPLL_LM_S
    hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, data32);


    data32  = 0;
    data32 |= 0 << 20;//[31:20]  Not used
    data32 |= 0xc08 << 8;//[19:8]  HDMI_RX_DPLL_REVE
    data32 |= 0x82 << 0; //[7:0]  HDMI_RX_DPLL_TDC_BUF
    hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, data32);


    data32  = 0;
    data32 |= 0 << 31;//[31]  HDMI_RX_AFC_OVER
#if(VIC == HDMI_1080P50 || VIC == HDMI_1080P60)
    data32 |= 4 << 28;//[30:28] HDMI_RX_XD
#else
    data32 |= 1 << 28;//[30:28] HDMI_RX_XD
#endif
    data32 |= 0 << 24;//[27:24] HDMI_RX_AFC_REVE
    data32 |= 0 << 23;//[23] HDMI_RX_DCO_SEL
    data32 |= 0 << 22;//[22] HDMI_RX_BAND_J
    data32 |= 0x80000 << 2;//[21:2]  HDMI_RX_AFC_BYPASS_IN
    data32 |= 0 << 1;//[1]  HDMI_RX_AFC_BYPASS
    data32 |= 0 << 0; //[0]  HDMI_RX_TMDS_M40
    hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, data32);

    data32  = 0;
    data32 |= 0 << 31;//[31]  HDMI_RX_DPLL_LOCK
    data32 |= 1 << 30;//[30]  HDMI_RX_DPLL_EN
    data32 |= 0 << 29;//[29]  HDMI_RX_DPLL_RESET
#if(VIC == HDMI_1080P50 || VIC == HDMI_1080P60 || VIC == HDMI_3840_2160P50 || VIC == HDMI_3840_2160P60)
    data32 |= 4 << 9;//[28:24]HDMI_RX_DPLL_N
#else
    data32 |= 3 << 24;//[28:24]HDMI_RX_DPLL_N
#endif
    data32 |= 0 << 23;//[23]  Not used
    data32 |= 0 << 20;//[22:20]HDMI_RX_EQ_SEL
    data32 |= 0 << 19;//[19 ] Not used
    data32 |= 0 << 16;//[18:16]HDMI_RX_AUDIO_RATE
    data32 |= 0 << 15;//[15] HDMI_RX_AFC_DONE
    data32 |= 3 << 13;//[14:13] HDMI_RX_DPLL_CLK_EN
    data32 |= 0 << 11;//[12:11]  HDMI_RX_DPLL_OD1
    data32 |= 0 << 9;//[10:9]  HDMI_RX_DPLL_OD
#if(VIC == HDMI_1080P50 || VIC == HDMI_1080P60 || VIC == HDMI_3840_2160P50 || VIC == HDMI_3840_2160P60)
    data32 |= 0x50 << 0; //[8:0]  HDMI_RX_DPLL_M
#else
    data32 |=0x0f<<0; //[8:0]  HDMI_RX_DPLL_M
#endif
    hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, data32);


#endif
    //audio pll set //by weicheng.zhang
    Wr(0x1a9,Rd(0x1a9)|1);
#ifndef NEW_AUDIO_PLL_SET
    data32  = 0;
    data32 |= 0 << 31;//[31]  Not used
    data32 |= 1 << 30;//[30]  AUD_DPLL_EN
    data32 |= 0 << 29;//[29] AUD_DPLL_RESET
    data32 |= 0 << 26;//[28:26]no used
    data32 |= 0 << 20;//[25:20] AUD_DPLL_XD
    data32 |= 0 << 18;//[19:18] No used
    data32 |= 0 << 16;//[17:16] AUD_DPLL_OD
    data32 |= 0 << 14;//[15:14]  No used
#if(VIC == HDMI_1080P50 || VIC == HDMI_1080P60 || VIC == HDMI_3840_2160P50 || VIC == HDMI_3840_2160P60)
    data32 |= 4 << 9;//[13:9]  AUD_DPLL_N
    data32 |= 0x50 << 0; //[8:0]  AUD_DPLL_M
#else
    data32 |= 1 << 9;//[13:9]  AUD_DPLL_N
    data32 |= 0x28 << 0; //[8:0]  AUD_DPLL_M
#endif
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL, data32);
#else
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL, 0x40000000);
#endif

#ifndef NEW_AUDIO_PLL_SET
    data32  = 0;
    data32 |= 0 << 28;//[31:28]  AUD_DPLL_LM_W
    data32 |= 0x27 << 22;//[27:22]  AUD_DPLL_LM_S
    data32 |= 0 << 21;//[21]  AUD_DPLL_DPFD_LMODE
    data32 |= 1 << 19;//[20:19] AUD_DC_VC_IN
    data32 |= 0 << 17;//[18:17] AUD_DCO_SDMCK_SEL
    data32 |= 0 << 16;//[16] AUD_DCO_M_EN
    data32 |= 0 << 14;//[15:14] No used
    data32 |= 0 << 13;//[13] AUD_AFC_DSEL_BYPASS
    data32 |= 0 << 12;//[12]  AUD_AFC_DSEL_IN
    data32 |= 0 << 6;//[11:6]  No used
    data32 |= 0 << 4; //[5:4]  AUD_DPLL_DCO_IUP
    data32 |= 1 << 3;//[3] AUD_DPLL_PVT_FIX_EN
    data32 |= 1 << 2;//[2] AUD_DPLL_DCO_SDM_EN
    data32 |= 1 << 1;//[1] AUD_DPLL_IIR_BYPASS_N
    data32 |= 0 << 0;//[0] AUD_DPLL_TDC_EN
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_2, data32);
#else
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_2, 0x00010020);
#endif


    data32  = 0;
    data32 |= 0 << 30;//[31:30] No used
    data32 |= 2 << 26;//[29: 26] AUD_DPLL_FILTER_PVT2
    data32 |= 0x9 << 22;//[25:22]  AUD_DPLL_FILTER_PVT1
    data32 |= 0x4E7 << 11;//[21:11]  AUD_DPLL_FILTER_ACQ2
    data32 |= 0x221 << 0; //[10:0]  AUD_DPLL_FILTER_ACQ1
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_3, data32);

#ifndef NEW_AUDIO_PLL_SET
    data32  = 0;
    data32 |= 7 << 28;//[31:28]  AUD_DPLL_DDS_RC_FILTER
    data32 |= 5 << 24; //[27:24]  AUD_DPLL_DDS_CLK_SEL
    data32 |= 0 << 21;//[23: 21] No used
    data32 |= 0 << 20;//[20] AUD_DPLL_INIT_CON
    data32 |= 0 << 8;//[19:8] AUD_DPLL_REVE
    data32 |= 1 << 0;//[7:0] AUD_DPLL_TDC_BUF
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_4, data32);
#else
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_4, 0x00000020);
#endif

#ifndef NEW_AUDIO_PLL_SET
    data32  = 0;
    data32 |= 0 << 24;//[31:24]  No used
    data32 |= 0 << 12;//[23:12]  AUD_DPLL_DAC_DEM_CTRL
    data32 |= 0xf20 << 0; //[11:0]  AUD_DPLL_DAC_CTRL
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_5, data32);
#else
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_5, 0x00000e04);//0x00000e0c
#endif

#ifndef NEW_AUDIO_PLL_SET
    data32  = 0;
    data32 |=   1 << 27;    //AUD_DPLL_DDS_REVE<11>
    data32 |=   1 << 31;    //AUD_DPLL_DDS_REVE<15>
    data32 |= 0 << 16;//[31:16]  AUD_DPLL_DDS_REVE
    data32 |= 0 << 12;//[15:12]  No used
    data32 |= 0 << 0; //[11:0]  AUD_DPLL_DDS_DIVIDER
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_6, data32);
#else
    if(OUTPUT_LVDS == panel_param->output_mode)
        hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_6, 0x06000000);
    else
        hdmirx_wr_top(HDMIRX_TOP_AUDPLL_CTRL_6, 0x07000000);
#endif


    data32  = 0;
    data32 |= (1            << 17); // [17] audfifo_rd_en
    data32 |= (1            << 16); // [16] pktfifo_rd_en
    data32 |= (0            << 8);  // [8]  tmds_ch2_clk_inv
    data32 |= (0            << 7);  // [7]  tmds_ch1_clk_inv
    data32 |= (0            << 6);  // [6]  tmds_ch0_clk_inv
    data32 |= (AUDPLL_X4    << 5);  // [5]  aud_pll4x_cfg:0=aud_pll output tmds_clk*2*N/CTS; 1=aud_pll output tmds_clk*4*N/CTS.
    data32 |= (1            << 4);  // [4]  force_aud_pll4x: 1= use aud_pll4x_cfg
    data32 |= (0            << 3);  // [3]  phy_clk_inv
    data32 |= (1            << 2);  // [2]  hdmirx_cecclk_en
    hdmirx_wr_top(HDMIRX_TOP_CLK_CNTL,  data32);

#if 0//USE_MANU_CTS_N
    //Wr(0x187,0x00100000);
    hdmirx_wr_top(0x41,0x2000);
    hdmirx_wr_top(0x51,0x4100603d);
    hdmirx_wr_top(0x52,0x04215e00);
    hdmirx_wr_top(0x53,0x0a763a21);
    hdmirx_wr_top(0x54,0x02801eb7);
    hdmirx_wr_top(0x55,0x000d0a80);
    hdmirx_wr_top(0x56,0x01210046);
    //hdmi rht 0x51

    //Wr(0x800306a4,0x00000001);
    Wr(0x1a9,0x00000001);

    hdmirx_wr_dwc(0x280,0x000f1b30);
    hdmirx_wr_dwc(0x284,0x000024c0);
    hdmirx_wr_dwc(0x214,0x00000010);

    hdmirx_wr_top(0x4b,0x40000000);
    hdmirx_wr_top(0x4c,0x00010000);
    hdmirx_wr_top(0x4e,0x70000020);
    hdmirx_wr_top(0x4f,0x00000c0c);
    hdmirx_wr_top(0x50,0x80000000);
#endif
}
void hdmirx_handler(void)
{
    hdmirx_sig_monitor();
#ifdef ENABLE_CEC_FUNCTION
    hdmirx_cec_monitor();
#endif
}
void hdmirx_reset(int ctl)
{
    if(ctl == 1){
        //hdmirx_wr_dwc(0xff0, 0x7f);
    }


}
int hdmirx_get_clock(int index)
{
    return clk_util_clk_msr(index, 50);
}

int hdmirx_get_tmds_clock(void)
{
    return clk_util_clk_msr(36, 50);
}
void hdmirx_reset_DPLL(void)
{
    if(OUTPUT_LVDS == panel_param->output_mode){
        //1080p
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x64016028);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, 0x04215000);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, 0x0a44b221);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, 0x02001eb7);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a82);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, 0x01210046);
        delay_us(10);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x44016028);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a83);
    }else if(OUTPUT_VB1 == panel_param->output_mode){
        if(PANEL_YUV420 == panel_param->format){
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x68016028);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, 0x04215000);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, 0x0a54c221);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, 0x02001eb7);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a82);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, 0x0121a026);
            delay_us(10);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x48016028);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a83);
        }else{
            if(TIMING_3840x2160P50 == panel_param->vx1_timing){
                //1080p cable output 4K 594M or 123.75 -> 4950
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x64016028);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, 0x04215000);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, 0x0a54c221);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, 0x02001eb7);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a82);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, 0x0121a006);
                delay_us(10);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x44016028);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a83);
            }
            else //if(TIMING_3840x2160P60 == panel_param->vx1_timing){
            {
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x64016028);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, 0x04215000);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, 0x0a54c221);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, 0x02001eb7);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a82);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, 0x0121a006);
                delay_us(10);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x44016028);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a83);
            }
        }
    }
}
void hdmirx_set_DPLL(void)
{
    char i = 0;
    unsigned long data32 = 0;
    data32 |= 0 << 29;//[31:29] Not used
    data32 |= 1 << 28;//[28] LVDS_DPLL_BGP_EN
    data32 |= 5 << 24;//[27:24] LVDS_DPLL_BGP_C
    data32 |= 0x10a << 12;//[23:12] LVDS_DPLL_REVE
    data32 |= 0x81 << 4;//[11:4] LVDS_DPLL_TDC_BUF
    data32 |= 1 << 3;//[3] LVDS_DPLL_PVT_FIX_EN
    data32 |= 0 << 1;//[2:1] LVDS_DPLL_DCO_IUP
    data32 |= 1 << 0; //[0] LVDS_DPLL_DCO_SDM_EN
    Wr(VX1_LVDS_PLL_CTL3, data32);
    delay_us(10);
    do{
        if(OUTPUT_LVDS == panel_param->output_mode){
        //1080p
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x64016028);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, 0x04215000);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, 0x0a44b221);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, 0x02001eb7);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a82);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, 0x01210046);
        delay_us(10);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x44016028);
        hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a83);
    }else if(OUTPUT_VB1 == panel_param->output_mode){
        if(PANEL_YUV420 == panel_param->format){
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x68016028);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, 0x04215000);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, 0x0a54c221);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, 0x02001eb7);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a82);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, 0x0121a026);
            delay_us(10);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x48016028);
            hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a83);
        }else{
            if(TIMING_3840x2160P50 == panel_param->vx1_timing){
                //1080p cable output 4K 594M or 123.75 -> 4950
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x64016028);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, 0x04215000);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, 0x0a54c221);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, 0x02001eb7);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a82);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, 0x0121a006);
                delay_us(10);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x44016028);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a83);
            }
            else //if(TIMING_3840x2160P60 == panel_param->vx1_timing){
            {
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x64016028);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_2, 0x04215000);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_3, 0x0a54c221);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_4, 0x02001eb7);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a82);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_6, 0x0121a006);
                delay_us(10);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL, 0x44016028);
                hdmirx_wr_top(HDMIRX_TOP_DPLL_CTRL_5, 0x000d0a83);
            }
            }
        }
        if(i++ > 20){
            printf("\n\nDPLL ERR\n\n");
            break;
        }
    }while(hdmirx_rd_top(HDMIRX_TOP_DPLL_CTRL) & (1<<31));

}
int hdmi_rx_phy_pll_lock(void)
{
    if((hdmirx_rd_dwc (HDMIRX_DWC_HDMI_PLL_LCK_STS) & 0x01) == 0)
        return 0;
    else
        return 1;
}
int hdmi_rx_audio_pll_lock(void)
{
    if((hdmirx_rd_dwc (HDMIRX_DWC_AUD_PLL_CTRL) & (1<<31)) == 0)
        return 0;
    else
        return 1;
}
void hdmirx_audio_control(char enable)
{
    if(enable)
    {
        // manual N&CTS setting == 0
        //hdmirx_wr_dwc(HDMIRX_DWC_AUD_CLK_CTRL,    1<<4);
        // Force N&CTS to start with, will switch to received values later on, for simulation speed up.
        // [4]cts_n_ref: 0=used decoded; 1=use manual N&CTS.
        //hdmirx_wr_dwc(HDMIRX_DWC_AUD_CLK_CTRL,    0);
        hdmirx_wr_dwc(HDMIRX_DWC_AUD_SAO_CTRL,  I2S_OUTPUT_SELECT);
    }
    else
    {
        hdmirx_wr_dwc(HDMIRX_DWC_AUD_SAO_CTRL,  0x7ff);
        // [4]cts_n_ref: 0=used decoded; 1=use manual N&CTS.
        //hdmirx_wr_dwc(HDMIRX_DWC_AUDPLL_GEN_CTS, 0);//MANUAL_ACR_CTS);
        //hdmirx_wr_dwc(HDMIRX_DWC_AUDPLL_GEN_N,     0);//MANUAL_ACR_N);
        //hdmirx_wr_dwc(HDMIRX_DWC_AUD_CLK_CTRL,    1<<4);
        // [4]cts_n_ref: 0=used decoded; 1=use manual N&CTS.
        //iaudioclk_domain_reset
        //hdmirx_wr_dwc(HDMIRX_DWC_DMI_SW_RST, hdmirx_rd_dwc(HDMIRX_DWC_DMI_SW_RST)|IAUDIOCLK_DOMAIN_RESET);
        //hdmirx_wr_dwc(HDMIRX_DWC_DMI_SW_RST, hdmirx_rd_dwc(HDMIRX_DWC_DMI_SW_RST)&(~IAUDIOCLK_DOMAIN_RESET));
        //audio_fifo_reset
        hdmirx_wr_dwc(HDMIRX_DWC_AUD_FIFO_CTRL, hdmirx_rd_dwc(HDMIRX_DWC_AUD_FIFO_CTRL)|AFIF_INIT);
        hdmirx_wr_dwc(HDMIRX_DWC_AUD_FIFO_CTRL, hdmirx_rd_dwc(HDMIRX_DWC_AUD_FIFO_CTRL)&(~AFIF_INIT));
    }
}
#endif


//hdmirx init
void hdmirx_config(void)
{
    unsigned long   data32;
    unsigned long   base_offset = INT_HDMIRX_BASE_OFFSET;

    // 3. wait for TX PHY clock up

    // 4. wait for rx sense

    // 5. Release IP reset

    // 8. If defined, force manual N & CTS to speed up simulation
    hdmirx_wr_top(HDMIRX_TOP_AUDPLL_LOCK_FILTER,    32);    // Filter 100ns glitch
    hdmirx_rd_check_dwc(HDMIRX_DWC_AUD_PLL_CTRL, 0<<31, ~(1<<31));  // AUD PLL should not be locked at this time yet.

    data32  = 0;
    data32 |= (7        << 13); // [15:13]  n_cts_update_width:000=hdmirx_n_cts_update pulse width is 1 tmds_clk cycle; 001=2-cycle; 011=3-cycle; 111=4-cycle.
    data32 |= (0        << 12); // [12]     n_cts_update_on_pll4x:1=aud_pll4x_en change will result in a hdmirx_n_cts_update pulse; 0=No hdmirx_n_cts_update pulse on aud_pll4x_en change.
    data32 |= (1        << 11); // [11]     n_cts_update_man:1=manual assert an hdmirx_n_cts_update pulse; 0=no action.
    data32 |= (0        << 10); // [10]     pll_tmode_cntl
    data32 |= (0        << 9);  // [9]      force_afif_status:1=Use cntl_audfifo_status_cfg as fifo status; 0=Use detected afif_status.
    data32 |= (1        << 8);  // [8]      afif_status_auto:1=Enable audio FIFO status auto-exit EMPTY/FULL, if FIFO level is back to LipSync; 0=Once enters EMPTY/FULL, never exits.
    data32 |= (1        << 6);  // [ 7: 6]  Audio FIFO nominal level :0=s_total/4;1=s_total/8;2=s_total/16;3=s_total/32.
    data32 |= (3        << 4);  // [ 5: 4]  Audio FIFO critical level:0=s_total/4;1=s_total/8;2=s_total/16;3=s_total/32.
    data32 |= (0        << 3);  // [3]      afif_status_clr:1=Clear audio FIFO status to IDLE.
    data32 |= (ACR_MODE << 2);  // [2]      dig_acr_en
    data32 |= (ACR_MODE << 1);  // [1]      audmeas_clk_sel: 0=select aud_pll_clk; 1=select aud_acr_clk.
    data32 |= (ACR_MODE << 0);  // [0]      aud_clk_sel: 0=select aud_pll_clk; 1=select aud_acr_clk.
    hdmirx_wr_top(HDMIRX_TOP_ACR_CNTL_STAT, data32);

    hdmirx_wr_dwc(HDMIRX_DWC_AUDPLL_GEN_CTS,MANUAL_ACR_CTS);
    hdmirx_wr_dwc(HDMIRX_DWC_AUDPLL_GEN_N,  MANUAL_ACR_N);

    // Force N&CTS to start with, will switch to received values later on, for simulation speed up.
    data32  = 0;
    data32 |= (USE_MANU_CTS_N   << 4);  // [4]      cts_n_ref: 0=used decoded; 1=use manual N&CTS.
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_CLK_CTRL,  data32);

    data32  = 0;
    data32 |= (0    << 28); // [28]     pll_lock_filter_byp
    data32 |= (1    << 24); // [27:24]  pll_lock_toggle_div
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_PLL_CTRL,  data32);


    printf("11 rx config\n");
    // 11. RX configuration
    ///hdmirx_wr_dwc(HDMIRX_DWC_HDMI_CKM_EVLTM, 0x0016fff0);
    //hdmirx_wr_dwc(HDMIRX_DWC_HDMI_CKM_F,      0xf98a0190);

    data32  = 0;
    data32 |= (80   << 18); // [26:18]  afif_th_start
    data32 |= (8    << 9);  // [17:9]   afif_th_max
    data32 |= (8    << 0);  // [8:0]    afif_th_min
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_FIFO_TH,   data32);

    data32  = 0;
    data32 |= (hdmirx_rd_dwc(HDMIRX_DWC_HDMI_MODE_RECOVER) & 0xf8000000);   // [31:27]  preamble_cnt_limit
    data32 |= (0    << 24); // [25:24]  mr_vs_pol_adj_mode
    data32 |= (0    << 18); // [18]     spike_filter_en
    data32 |= (0    << 13); // [17:13]  dvi_mode_hyst
    data32 |= (0    << 8);  // [12:8]   hdmi_mode_hyst
    data32 |= (0    << 6);  // [7:6]    hdmi_mode: 0=automatic
    data32 |= (2    << 4);  // [5:4]    gb_det
    data32 |= (0    << 2);  // [3:2]    eess_oess
    data32 |= (1    << 0);  // [1:0]    sel_ctl01
    hdmirx_wr_dwc(HDMIRX_DWC_HDMI_MODE_RECOVER, data32);

    data32  = 0;
    data32 |= (1     << 31);    // [31]     pfifo_store_filter_en
    data32 |= (1     << 26);    // [26]     pfifo_store_mpegs_if
    data32 |= (1     << 25);    // [25]     pfifo_store_aud_if
    data32 |= (1     << 24);    // [24]     pfifo_store_spd_if
    data32 |= (1     << 23);    // [23]     pfifo_store_avi_if
    data32 |= (1     << 22);    // [22]     pfifo_store_vs_if
    data32 |= (1     << 21);    // [21]     pfifo_store_gmtp
    data32 |= (1     << 20);    // [20]     pfifo_store_isrc2
    data32 |= (1     << 19);    // [19]     pfifo_store_isrc1
    data32 |= (1     << 18);    // [18]     pfifo_store_acp
    data32 |= (0     << 17);    // [17]     pfifo_store_gcp
    data32 |= (0     << 16);    // [16]     pfifo_store_acr
    data32 |= (0     << 14);    // [14]     gcpforce_clravmute
    data32 |= (0     << 13);    // [13]     gcpforce_setavmute
    data32 |= (0     << 12);    // [12]     gcp_avmute_allsps
    data32 |= (0     << 8);     // [8]      pd_fifo_fill_info_clr
    data32 |= (0     << 6);     // [6]      pd_fifo_skip
    data32 |= (0     << 5);     // [5]      pd_fifo_clr
    data32 |= (1     << 4);     // [4]      pd_fifo_we
    data32 |= (1     << 0);     // [0]      pdec_bch_en
    hdmirx_wr_dwc(HDMIRX_DWC_PDEC_CTRL, data32);

    data32  = 0;
    data32 |= (1    << 6);  // [6]      auto_vmute
    data32 |= (0xf  << 2);  // [5:2]    auto_spflat_mute
    hdmirx_wr_dwc(HDMIRX_DWC_PDEC_ASP_CTRL, data32);

    data32  = 0;
    data32 |= (1    << 16); // [16]     afif_subpackets: 0=store all sp; 1=store only the ones' spX=1.
    data32 |= (0    << 0);  // [0]      afif_init
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_FIFO_CTRL, data32);

    data32  = 0;
    data32 |= (0    << 10); // [10]     ws_disable
    data32 |= (0    << 9);  // [9]      sck_disable
    data32 |= (0    << 5);  // [8:5]    i2s_disable
    data32 |= (0    << 1);  // [4:1]    spdif_disable
    data32 |= (I2S_OUTPUT_SELECT    << 0);  // [0]      i2s_32_16
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_SAO_CTRL,  data32);

    // Manual de-repeat to speed up simulation, will switch to auto value later on.
    data32  = 0;
    data32 |= (PIXEL_REPEAT_HDMI    << 1);  // [4:1]    man_vid_derepeat
    data32 |= (0                    << 0);  // [0]      auto_derepeat
    hdmirx_wr_dwc(HDMIRX_DWC_HDMI_RESMPL_CTRL,  data32);

    // At the 1st frame, HDMIRX hasn't received AVI packet, HDMIRX default video format to RGB, so manual/force something to speed up simulation:
    data32  = 0;
    #ifdef HDMIRX_PHY_AML
    data32 |= (0                        << 24); // [26:24]  vid_data_map. 0={vid2, vid1, vid0}->{vid2, vid1, vid0}
    #else   /* HDMIRX_PHY_AML */
    // For receiving YUV444 video, we manually map component data to speed up simulation, manual-mapping will be cancelled once AVI is received.
    if ((rx_color_format == HDMI_COLOR_FORMAT_444) && (base_offset == INT_HDMIRX_BASE_OFFSET)) {
        data32 |= (2                        << 24); // [26:24]  vid_data_map. 2={vid1, vid0, vid2}->{vid2, vid1, vid0}
    } else {
        data32 |= (0                        << 24); // [26:24]  vid_data_map. 0={vid2, vid1, vid0}->{vid2, vid1, vid0}
    }
    #endif  /* HDMIRX_PHY_AML */
    data32 |= (0                            << 19); // [19]     cntl_422_mode : 0=Insert a repeat of every pixel; 1=Insert an average of every 2-pixel.
    data32 |= (1                            << 5);  // [5]      cntl_vs_irq_pol: 0=Use vid_vs rising edge to generate vs_irq; 1=Use vid_vs falling edge to generate vs_irq.
    data32 |= (0                            << 4);  // [4]      is_vic39
    data32 |= (0                            << 2);  // [3:2]    vs_pol: [1] 0=Auto-detect VS polarity; 1=use manual VS polarity.
                                                    //                  [0] munual VS polarity. 0=Active high; 1=Active low.
    data32 |= (0                            << 0);  // [1:0]    hs_pol: [1] 0=Auto-detect HS polarity; 1=use manual HS polarity.
                                                    //                  [0] munual HS polarity. 0=Active high; 1=Active low.
    hdmirx_wr_top(HDMIRX_TOP_VID_CNTL,  data32);

    data32  = 0;
    data32 |= (3                        << 27); // [29:27]  decoup_thresh_dpix. Read start threshold for decouple FIFO in hdmirx_vid_dpix.
    data32 |= (3                        << 24); // [26:24]  decoup_thresh_420out. Read start threshold for output decouple FIFO in hdmirx_vid_420
    data32 |= (3                        << 21); // [23:21]  decoup_thresh_420in. Read start threshold for input decouple FIFO in hdmirx_vid_420
    data32 |= (0                        << 20); // [20]     last420l_rdwin_mode. Control when to start read from FIFO for outputting 420 even or last line.
                                                //          0=use measured the previous line's start position minus last420l_rdwin_auto.
                                                //          1=use last420l_rdwin_manual to start the read window.
    data32 |= (0                        << 8);  // [19:8]   last420l_rdwin_manual
    data32 |= (0                        << 0);  // [7:0]    last420l_rdwin_auto
    hdmirx_wr_top(HDMIRX_TOP_VID_CNTL2,  data32);

    // To speed up simulation:
    // Force VS polarity until for the first 2 frames, because it takes one whole frame for HDMIRX to detect the correct VS polarity;
    // HS polarity can be detected just after one line, so it can be set to auto-detect from the start.
    data32  = 0;
    data32 |= (2    << 3);  // [4:3]    vs_pol_adj_mode:0=invert input VS; 1=no invert; 2=auto convert to high active; 3=no invert.
    data32 |= (2    << 1);  // [2:1]    hs_pol_adj_mode:0=invert input VS; 1=no invert; 2=auto convert to high active; 3=no invert.
    hdmirx_wr_dwc(HDMIRX_DWC_HDMI_SYNC_CTRL,    data32);

    data32  = 0;
    data32 |= (0    << 31); // [31]     apply_int_mute
    data32 |= (3    << 21); // [22:21]  aport_shdw_ctrl
    data32 |= (2    << 19); // [20:19]  auto_aclk_mute
    data32 |= (1    << 10); // [16:10]  aud_mute_speed
    data32 |= (1    << 7);  // [7]      aud_avmute_en
    data32 |= (1    << 5);  // [6:5]    aud_mute_sel
    data32 |= (1    << 3);  // [4:3]    aud_mute_mode
    data32 |= (0    << 1);  // [2:1]    aud_ttone_fs_sel
    data32 |= (0    << 0);  // [0]      testtone_en
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_MUTE_CTRL, data32);

    data32  = 0;
    data32 |= (1    << 12); // [12]     vid_data_checken
    data32 |= (1    << 11); // [11]     data_island_checken
    data32 |= (1    << 10); // [10]     gb_checken
    data32 |= (1    << 9);  // [9]      preamb_checken
    data32 |= (1    << 8);  // [8]      ctrl_checken
    data32 |= (1    << 4);  // [4]      scdc_enable
    data32 |= (1    << 0);  // [1:0]    scramble_sel
    hdmirx_wr_dwc(HDMIRX_DWC_HDMI20_CONTROL,    data32);

    data32  = 0;
    data32 |= (1    << 24); // [25:24]  i2c_spike_suppr
    data32 |= (0    << 20); // [20]     i2c_timeout_en
    data32 |= (0    << 0);  // [19:0]   i2c_timeout_cnt
    hdmirx_wr_dwc(HDMIRX_DWC_SCDC_I2CCONFIG,    data32);

    data32  = 0;
    data32 |= (0    << 1);  // [1]      hpd_low
    data32 |= (1    << 0);  // [0]      power_provided
    hdmirx_wr_dwc(HDMIRX_DWC_SCDC_CONFIG,   data32);

    data32  = 0;
    data32 |= (0xabcdef << 8);  // [31:8]   manufacture_oui
    data32 |= (1        << 0);  // [7:0]    sink_version
    hdmirx_wr_dwc(HDMIRX_DWC_SCDC_WRDATA0,  data32);

    data32  = 0;
    data32 |= (10       << 20); // [29:20]  chlock_max_err
    data32 |= (24000    << 0);  // [15:0]   milisec_timer_limit
    hdmirx_wr_dwc(HDMIRX_DWC_CHLOCK_CONFIG, data32);

    data32  = 0;
    data32 |= (0    << 16); // [17:16]  pao_rate
    #ifdef HDMIRX_PHY_AML
    data32 |= (1    << 12); // [12]     pao_disable
    #else   /* HDMIRX_PHY_AML */
    data32 |= (0    << 12); // [12]     pao_disable
    #endif  /* HDMIRX_PHY_AML */
    data32 |= (0    << 4);  // [11:4]   audio_fmt_chg_thres
    data32 |= (0    << 1);  // [2:1]    audio_fmt
    data32 |= (0    << 0);  // [0]      audio_fmt_sel
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_PAO_CTRL,  data32);

    data32  = 0;
    data32 |= (0                        << 8);  // [10:8]   ch_map[7:5]
    data32 |= (1                        << 7);  // [7]      ch_map_manual
    data32 |= ((RX_8_CHANNEL? 0x13:0x00)<< 2);  // [6:2]    ch_map[4:0]
    data32 |= (1                        << 0);  // [1:0]    aud_layout_ctrl:0/1=auto layout; 2=layout 0; 3=layout 1.
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_CHEXTR_CTRL,   data32);

    data32  = 0;
    data32 |= (0    << 8);  // [8]      fc_lfe_exchg: 1=swap channel 3 and 4
    hdmirx_wr_dwc(HDMIRX_DWC_PDEC_AIF_CTRL, data32);

    data32  = 0;
    data32 |= (0    << 20); // [20]     rg_block_off:1=Enable HS/VS/CTRL filtering during active video
    data32 |= (1    << 19); // [19]     block_off:1=Enable HS/VS/CTRL passing during active video
    data32 |= (5    << 16); // [18:16]  valid_mode
    data32 |= (0    << 12); // [13:12]  ctrl_filt_sens
    data32 |= (3    << 10); // [11:10]  vs_filt_sens
    data32 |= (0    << 8);  // [9:8]    hs_filt_sens
    data32 |= (2    << 6);  // [7:6]    de_measure_mode
    data32 |= (0    << 5);  // [5]      de_regen
    data32 |= (3    << 3);  // [4:3]    de_filter_sens
    hdmirx_wr_dwc(HDMIRX_DWC_HDMI_ERROR_PROTECT,    data32);

    data32  = 0;
    data32 |= (0    << 8);  // [10:8]   hact_pix_ith
    data32 |= (0    << 5);  // [5]      hact_pix_src
    data32 |= (1    << 4);  // [4]      htot_pix_src
    hdmirx_wr_dwc(HDMIRX_DWC_MD_HCTRL1, data32);

    data32  = 0;
    data32 |= (1    << 12); // [14:12]  hs_clk_ith
    data32 |= (7    << 8);  // [10:8]   htot32_clk_ith
    data32 |= (1    << 5);  // [5]      vs_act_time
    data32 |= (3    << 3);  // [4:3]    hs_act_time
    data32 |= (0    << 0);  // [1:0]    h_start_pos
    hdmirx_wr_dwc(HDMIRX_DWC_MD_HCTRL2, data32);

    data32  = 0;
    data32 |= (1                << 4);  // [4]      v_offs_lin_mode
    data32 |= (1                << 1);  // [1]      v_edge
    data32 |= (INTERLACE_MODE   << 0);  // [0]      v_mode
    hdmirx_wr_dwc(HDMIRX_DWC_MD_VCTRL,  data32);

    data32  = 0;
    data32 |= (1    << 10); // [11:10]  vofs_lin_ith
    data32 |= (3    << 8);  // [9:8]    vact_lin_ith
    data32 |= (0    << 6);  // [7:6]    vtot_lin_ith
    data32 |= (7    << 3);  // [5:3]    vs_clk_ith
    data32 |= (2    << 0);  // [2:0]    vtot_clk_ith
    hdmirx_wr_dwc(HDMIRX_DWC_MD_VTH,    data32);
    //hdmirx_wr_dwc(HDMIRX_DWC_MD_VTH,  0xfff);

    data32  = 0;
    data32 |= (1    << 2);  // [2]      fafielddet_en
    data32 |= (0    << 0);  // [1:0]    field_pol_mode
    hdmirx_wr_dwc(HDMIRX_DWC_MD_IL_POL, data32);

    data32  = 0;
    data32 |= (0    << 2);  // [4:2]    deltacts_irqtrig
    data32 |= (0    << 0);  // [1:0]    cts_n_meas_mode
    hdmirx_wr_dwc(HDMIRX_DWC_PDEC_ACRM_CTRL,    data32);

    data32  = 0;
    data32 |= (0                << 28); // [28]     dcm_ph_diff_cnt_clr_p
    data32 |= (0                << 20); // [27:20]  dcm_ph_diff_cnt_thres
    data32 |= (1                << 18); // [18]     dcm_default_phase
    data32 |= (0                << 17); // [17]     dcm_pixel_phase_sel
    data32 |= (0                << 13); // [16:13]  dcm_pixel_phase
    data32 |= (1                << 12); // [12]     dcm_colour_depth_sel. Speed up simulation by forcing color_depth for the first 2 frames, this bit will be reset in test.c after 2 frames.
    data32 |= (RX_COLOR_DEPTH   << 8);  // [11:8]   dcm_colour_depth
    data32 |= (5                << 2);  // [5:2]    dcm_gcp_zero_fields
    data32 |= (0                << 0);  // [1:0]    dcm_dc_operation
    hdmirx_wr_dwc(HDMIRX_DWC_HDMI_DCM_CTRL, data32);

    data32  = 0;
    data32 |= (0    << 9);  // [13:9]   audiodet_threshold
    hdmirx_wr_dwc(HDMIRX_DWC_PDEC_DBG_CTRL, data32);
    printf("phy aml config\n");
    #ifdef HDMIRX_PHY_AML
    // Configure channel switch

    data32  = 0;
    data32 |= 0<<3;  //valid_always
    data32 |= (3    <<  0); // [2:0]  decoup_thresh
    hdmirx_wr_top(HDMIRX_TOP_CHAN_SWITCH_1, data32);

    data32  = 0;
	if(HDMI_PORT_SWITCH == HDMI_PORT_A){
    data32 |= (0      << 28); // [29:28]    source_2
    data32 |= (1      << 26); // [27:26]    source_1
    data32 |= (2      << 24); // [25:24]    source_0
	}else{
    	data32 |= (2    << 28); // [29:28]    source_2
    	data32 |= (1    << 26); // [27:26]    source_1
    	data32 |= (0    << 24); // [25:24]    source_0
	}
    data32 |= (0      << 20); // [22:20]    skew_2
    data32 |= (0      << 16); // [18:16]    skew_1
    data32 |= (0      << 12); // [14:12]    skew_0
    data32 |= (0      << 10); // [10]       bitswap_2
    data32 |= (0      <<  9); // [9]        bitswap_1
    data32 |= (0      <<  8); // [8]        bitswap_0
    data32 |= (0      <<  6); // [6]        polarity_2
    data32 |= (0      <<  5); // [5]        polarity_1
    data32 |= (0      <<  4); // [4]        polarity_0
    data32 |= (0      <<  0); // [0]        enable
    hdmirx_wr_top(HDMIRX_TOP_CHAN_SWITCH_0, data32);

    // Configure TMDS algin
    printf("tmds algin\n");
    data32  = 0;
    data32 |= (0    << 31); // [   31] cntl_force_valid_cfg
    data32 |= (0    << 28); // [29:28] glitch_filter_en_2: 0=disable; 1=1-cycle glitch filter.
    data32 |= (0    << 26); // [27:26] glitch_filter_en_1: 0=disable; 1=1-cycle glitch filter.
    data32 |= (0    << 24); // [25:24] glitch_filter_en_0: 0=disable; 1=1-cycle glitch filter.
    data32 |= (0    << 22); // [23:22] tolerance_2
    data32 |= (2    << 19); // [21:19] win_score_bound_2
    data32 |= (0    << 16); // [18:16] win_score_delay_2
    data32 |= (0    << 14); // [15:14] tolerance_1
    data32 |= (2    << 11); // [13:11] win_score_bound_1
    data32 |= (0    <<  8); // [10: 8] win_score_delay_1
    data32 |= (0    <<  6); // [ 7: 6] tolerance_0
    data32 |= (2    <<  3); // [ 5: 3] win_score_bound_0
    data32 |= (0    <<  0); // [ 2: 0] win_score_delay_0
    hdmirx_wr_top(HDMIRX_TOP_TMDS_ALIGN_CNTL0,  data32);

    data32  = 0;
    data32 |= (1    << 30); // [31:30] cntl_valid_mode: 0=Valid if all 3 channels are stable, invalid if any channel is unstable;
                            //                          1=Valid once all 3 channels are stable, then always valid until reset;
                            //                          2=By cntl_force_valid_cfg.
    data32 |= (0    << 29); // [   29] forced_delay_adjustment_enable_2
    data32 |= (0    << 28); // [   28] forced_bound_adjustment_enable_2
    data32 |= (0    << 27); // [   27] forced_delay_adjustment_enable_1
    data32 |= (0    << 26); // [   26] forced_bound_adjustment_enable_1
    data32 |= (0    << 25); // [   25] forced_delay_adjustment_enable_0
    data32 |= (0    << 24); // [   24] forced_bound_adjustment_enable_0
    data32 |= (0    << 20); // [23:20] forced_delay_adjustment_2
    data32 |= (0    << 16); // [19:16] forced_bound_adjustment_2
    data32 |= (0    << 12); // [15:12] forced_delay_adjustment_1
    data32 |= (0    <<  8); // [11: 8] forced_bound_adjustment_1
    data32 |= (0    <<  4); // [ 7: 4] forced_delay_adjustment_0
    data32 |= (0    <<  0); // [ 3: 0] forced_bound_adjustment_0
    hdmirx_wr_top(HDMIRX_TOP_TMDS_ALIGN_CNTL1,  data32);


    #endif  /* HDMIRX_PHY_AML */

    #ifdef HDMIRX_VID_CEA
    // For CEA Video Mode
    data32  = 0;
    if(SCRAMBLER_EN)
        data32 |= (1              << 31); // [31]   enable    ceavid_rst
    else
        data32 |= (0              << 31); // [31]   disable   ceavid_rst
    data32 |= (0              << 14); // [14]       ceavid_vidid
    if(get_metal_revision() == REV_A)
    	data32 |= (0              << 10); // [13:10]    ceavid_realign_th
    else
		data32 |= (0xf              << 10); // [13:10]    ceavid_realign_th--for revB auto frame sync function
    data32 |= (0              <<  6); // [9:6]      ceavid_ignframe
    data32 |= (0              <<  5); // [5]        ceavid_vbos_manual
    data32 |= (INTERLACE_MODE <<  4); // [4]        ceavid_ilace_manual
    data32 |= (VSYNC_POLARITY <<  3); // [3]        ceavid_vpol_manual
    data32 |= (HSYNC_POLARITY <<  2); // [2]        ceavid_hpol_manual
    data32 |= (MANUAL_CEA_TIMING     <<  1); // [1]     ceavid_manual
    data32 |= (0              <<  0); // [0]        ceavid_en_manual
    hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_CONFIG,  data32);

    if(MANUAL_CEA_TIMING) {
        LOGD(TAG_HDMIRX, "[HDMIRX.C] Use Manual Configuration for CEA based on pixel_clock\n");
        //LOGD(TAG_HDMIRX, "[HDMIRX.C] hblank is %d, hactive is %d\n", (front_porch+hsync_pixels+back_porch), hactive);
        //LOGD(TAG_HDMIRX, "[HDMIRX.C] hfront is %d, hsync_width is %d\n", front_porch, hsync_pixels);
        //LOGD(TAG_HDMIRX, "[HDMIRX.C] vblank is %d, vactive is %d\n", (sof_lines+vsync_lines+eof_lines), vactive);
        //LOGD(TAG_HDMIRX, "[HDMIRX.C] vfront is %d, vsync_width is %d\n", eof_lines, vsync_lines);

        data32  = 0;
        data32 |= (0    <<  1); // [4:1]    ceavid_3dstructure_manual
        data32 |= (0    <<  0); // [0]      ceavid_3den_manual
        hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_3DCONFIG,   data32);

        data32  = 0;
        data32 |= ((FRONT_PORCH+HSYNC_PIXELS+BACK_PORCH) << 16); // [31:16]    hblank
        data32 |= (ACTIVE_PIXELS                                 <<  0); // [15:0]     hactive
        hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_HCONFIG_LO,  data32);

        data32  = 0;
        data32 |= (FRONT_PORCH << 16); // [31:16]    hfront
        data32 |= (HSYNC_PIXELS <<  0); // [15:0]    hsync_width
        hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_HCONFIG_HI,  data32);

        data32  = 0;
        data32 |= ((EOF_LINES+VSYNC_LINES+SOF_LINES)    << 16); // [31:16]  vblank
        data32 |= (ACTIVE_LINES                             <<  0); // [15:0]   vactive
        hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_VCONFIG_LO,  data32);

        data32  = 0;
        data32 |= (EOF_LINES << 16); // [31:16] vfront
        data32 |= (VSYNC_LINES<<  0); // [15:0]     vsync_width
        hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_VCONFIG_HI,  data32);

        // Enable manual model after manual parameters are set
        hdmirx_wr_dwc(HDMIRX_DWC_CEAVID_CONFIG, hdmirx_rd_dwc(HDMIRX_DWC_CEAVID_CONFIG) | (1<<0));
    }
    #endif  /* HDMIRX_VID_CEA */

    // Configure tmds clock measurement

    data32  = 0;
    data32 |= (1    << 28); // [31:28] meas_tolerance
    data32 |= (8192 <<  0); // [23: 0] ref_cycles
    hdmirx_wr_top(HDMIRX_TOP_METER_HDMI_CNTL,   data32);
    hdmirx_wr_top(HDMIRX_TOP_METER_CABLE_CNTL,  data32);

    // 12. RX PHY configuration

    // Turn on interrupts that to do with PHY communication
    hdmirx_wr_only_dwc(HDMIRX_DWC_HDMI_ICLR,    0xffffffff);
#if IN_FBC_MAIN_CONFIG
    hdmirx_wr_only_dwc(HDMIRX_DWC_HDMI_IEN_SET, dwc_hdmi_ien_maskn);
#endif
    hdmirx_rd_check_dwc(HDMIRX_DWC_HDMI_ISTS,   0, 0);

    //data32    = 0;
    //data32 |= (TMDS_CLK_DIV4  <<  1); // [    1] tmds_clk_div4
    //data32 |= (1              <<  0); // [    0] enable
    //hdmirx_wr_top(HDMIRX_TOP_PHY_CTRL_0,  data32);

    // 13.  HDMI RX Ready! - Assert HPD
    LOGD(TAG_HDMIRX, "[HDMIRX.C] HDMI RX Ready! - Assert HPD\n");


    /*
    if (base_offset == INT_HDMIRX_BASE_OFFSET) {
        // Configure external video data generator and analyzer
        start_video_gen_ana(vic,                    // Video format identification code
                            pixel_repeat_hdmi,
                            interlace_mode,         // 0=Progressive; 1=Interlace.
                            rx_color_depth,         // color_depth: 4=24-bit; 5=30-bit; 6=36-bit; 7=48-bit.
                            rx_color_format,        // Pixel format: 0=RGB444; 1=YCbCr422; 2=YCbCr444; 3=YCbCr420.
                            front_porch,            // Number of pixels from DE Low to HSYNC high
                            back_porch,             // Number of pixels from HSYNC low to DE high
                            hsync_pixels,           // Number of pixels of HSYNC pulse
                            hsync_polarity,         // TX HSYNC polarity: 0=low active; 1=high active.
                            sof_lines,              // HSYNC count between VSYNC de-assertion and first line of active video
                            eof_lines,              // HSYNC count between last line of active video and start of VSYNC
                            vsync_lines,            // HSYNC count of VSYNC assertion
                            vsync_polarity,         // TX VSYNC polarity: 0=low active; 1=high active.
                            total_pixels,           // Number of total pixels per line
                            total_lines);           // Number of total lines per frame
        }
    */
    // 14.  RX_FINAL_CONFIG
    data32  = 0;
    //data32 |= (1  << 20); // [21:20]  lock_hyst
    data32 |= (0    << 20); // [21:20]  lock_hyst
    data32 |= (0    << 16); // [18:16]  clk_hyst
    //data32 |= (2490 << 4);    // [15:4]   eval_time
    data32 |= (0x26e << 4); // [15:4]   eval_time//
    hdmirx_wr_dwc(HDMIRX_DWC_HDMI_CKM_EVLTM,    data32);

    data32  = 0;
    data32 |= (0x226c << 16); // [31:16]maxfreq //340000*4095/158000
    data32 |= (0x26e << 0); // [15:0]minfreq    //24000*4095/158000
    hdmirx_wr_dwc(HDMIRX_DWC_HDMI_CKM_F,    data32);

    printf("RX PHY PLL lock wait\n");
    // RX PHY PLL lock wait
    #if 0
    LOGW(TAG_HDMIRX, "[HDMIRX.C] WAITING FOR TMDSVALID-------------------\n");
    if (base_offset == INT_HDMIRX_BASE_OFFSET) {
        while (! (hdmi_pll_lock)) {
            delay_us(10);
        }
    } else {
        while ((hdmirx_rd_dwc(HDMIRX_DWC_HDMI_PLL_LCK_STS) & 0x1) == 0) {
            delay_us(10);
        }
    }
    LOGD(TAG_HDMIRX, "[HDMIRX.C] HDMI_PLL Locked -------------------\n");
    hdmirx_poll_dwc(HDMIRX_DWC_HDMI_CKM_RESULT, 1<<16, ~(1<<16), 0);

    #ifdef HDMIRX_PHY_AML
    LOGW(TAG_HDMIRX, "[HDMIRX.C] WAITING FOR TMDS alignment stable-------\n");
    hdmirx_poll_top(HDMIRX_TOP_TMDS_ALIGN_STAT, 0x3f<<24, ~(0x3f<<24));
    LOGD(TAG_HDMIRX, "[HDMIRX.C] TMDS alignment stable-------------------\n");
    #endif  /* HDMIRX_PHY_AML */
    #endif
    // 15. Waiting for AUDIO PLL to lock before performing RX synchronous resets!
    //hdmirx_poll_reg(base_offset, HDMIRX_DEV_ID_DWC, HDMIRX_DWC_AUD_PLL_CTRL, 1<<31, ~(1<<31));

    // 16. RX Reset
#if 0
    data32  = 0;
    #ifdef HDMIRX_VID_CEA
    data32 |= (0    << 6);  // [6]      pixel_enable
    #endif  /* HDMIRX_VID_CEA */
    data32 |= (0    << 5);  // [5]      cec_enable
    data32 |= (0    << 4);  // [4]      aud_enable
    data32 |= (0    << 3);  // [3]      bus_enable
    data32 |= (0    << 2);  // [2]      hdmi_enable
    data32 |= (0    << 1);  // [1]      modet_enable
    data32 |= (1    << 0);  // [0]      cfg_enable
    hdmirx_wr_dwc(HDMIRX_DWC_DMI_DISABLE_IF,data32);
#endif

    delay_us(1);

    //--------------------------------------------------------------------------
    // Enable HDMIRX-DWC interrupts:
    //--------------------------------------------------------------------------
    hdmirx_wr_only_dwc(HDMIRX_DWC_PDEC_ICLR,        0xffffffff);
    hdmirx_wr_only_dwc(HDMIRX_DWC_AUD_CEC_ICLR,     0xffffffff);
    hdmirx_wr_only_dwc(HDMIRX_DWC_AUD_FIFO_ICLR,    0xffffffff);
    hdmirx_wr_only_dwc(HDMIRX_DWC_MD_ICLR,          0xffffffff);
    //hdmirx_wr_only_dwc(HDMIRX_DWC_HDMI_ICLR,      0xffffffff);

#ifdef IN_FBC_MAIN_CONFIG
    hdmirx_wr_only_dwc(HDMIRX_DWC_PDEC_IEN_SET,     dwc_pdec_ien_maskn);
    //hdmirx_wr_only_dwc(HDMIRX_DWC_AUD_CEC_IEN_SET,    dwc_aud_cec_ien_maskn);
    hdmirx_wr_only_dwc(HDMIRX_DWC_AUD_FIFO_IEN_SET, dwc_aud_fifo_ien_maskn);
    hdmirx_wr_only_dwc(HDMIRX_DWC_MD_IEN_SET,       dwc_md_ien_maskn);
    //hdmirx_wr_only_dwc(HDMIRX_DWC_HDMI_IEN_SET,   hdmi_ien_maskn);
#endif

    hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_ISTS,       0, 0);
    hdmirx_rd_check_dwc(HDMIRX_DWC_AUD_CEC_ISTS,    0, 0);
    hdmirx_rd_check_dwc(HDMIRX_DWC_AUD_FIFO_ISTS,   0, 0);
    hdmirx_rd_check_dwc(HDMIRX_DWC_MD_ISTS,         0, 0);
    //hdmirx_rd_check_dwc(HDMIRX_DWC_HDMI_ISTS,     0, 0);

    //--------------------------------------------------------------------------
    // Bring up RX
    //--------------------------------------------------------------------------
    data32  = 0;

    #ifdef HDMIRX_VID_CEA
    data32 |= (1    << 6);  // [6]      pixel_enable
    #endif  /* HDMIRX_VID_CEA */
    data32 |= (1    << 5);  // [5]      cec_enable
    data32 |= (1    << 4);  // [4]      aud_enable
    data32 |= (1    << 3);  // [3]      bus_enable
    data32 |= (1    << 2);  // [2]      hdmi_enable
    data32 |= (1    << 1);  // [1]      modet_enable
    data32 |= (1    << 0);  // [0]      cfg_enable
    hdmirx_wr_dwc(HDMIRX_DWC_DMI_DISABLE_IF,data32);

    delay_us(10);
    printf("hdmirx_phy_init\n");
    hdmirx_phy_init();

    #ifdef IN_FBC_MAIN_CONFIG
    hdmirx_cec_init();
    #endif
    // Enable channel output
    //hdmirx_wr_top(HDMIRX_TOP_CHAN_SWITCH_0, hdmirx_rd_top(HDMIRX_TOP_CHAN_SWITCH_0) | (1<<0));
#ifdef HDMIRX_VID_CEA
        // if(manual_cea) {
        // }
#endif  /* HDMIRX_VID_CEA */

    hdmirx_wr_top(HDMIRX_TOP_CHAN_SWITCH_0, hdmirx_rd_top(HDMIRX_TOP_CHAN_SWITCH_0) | (1<<0));

}
#ifdef IN_FBC_MAIN_CONFIG
int hdmirx_cec_init(void)
{
    unsigned long data32;
    //set cec clk 32768k
    //Wr_reg_bits(HHI_CLK_32K_CNTL, 1, 16, 2);
    //Wr_reg_bits(HHI_CLK_32K_CNTL, 1, 18, 1);


    // HDMI IP CEC clock = 24M/732=32786.9Hz
    data32  = 0;
    data32 |= 1         << 15;  // [   15] clk_en
    data32 |= 0         << 13;  // [14:13] clk_sel: 0=oscin_clk_divN; 1=internal_osc_clk; 2=AO_pin_clk; 3=cts_sys_clk.
    data32 |= (732-1)   << 0;   // [12: 0] clk_div
    Wr(CEC_CLK_32K_CNTL,    data32);
    //*P_CEC_CLK_32K_CNTL |= (0<<13) | (1<<15) | ((732-1)<<0);

    //set logic addr
    hdmirx_wr_dwc(HDMIRX_DWC_CEC_ADDR_L, 0x00000001);
    hdmirx_wr_dwc(HDMIRX_DWC_CEC_ADDR_H, 0x00000000);
    printf("cec enable\n");
    //enable cec eom irq
    //hdmirx_wr_dwc(HDMIRX_DWC_AUD_CEC_IEN_SET, (3<<16));
    //hdmirx_wr_top(HDMIRX_TOP_INTR_MASKN, 0x00000001);

    hdmirx_wr_dwc(HDMIRX_DWC_AUD_CEC_ICLR,      0xffffffff);
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_CEC_IEN_SET,   (3<<16));
    return 0;
}
#endif

void hdmirx_hdcp_init(void)
{
    unsigned long   data32;

    data32  = 0;
    data32 |= (1    << 16); // [17:16]  i2c_spike_suppr
    data32 |= (1    << 13); // [13]     hdmi_reserved. 0=No HDMI capabilities.
    data32 |= (1    << 12); // [12]     fast_i2c
    data32 |= (1    << 9);  // [9]      one_dot_one

    data32 |= (1    << 8);  // [8]      fast_reauth
    data32 |= (0x3a << 1);  // [7:1]    hdcp_ddc_addr
    hdmirx_wr_dwc(HDMIRX_DWC_HDCP_SETTINGS, data32);    // DEFAAULT: {13'd0, 2'd1, 1'b1, 3'd0, 1'b1, 2'd0, 1'b1, 1'b1, 7'd58, 1'b0}

    hdmirx_key_setting(HDCP_KEY_DECRYPT_EN);

    data32  = 0;
    data32 |= RX_FOR_REPEATER       << 3;   // [3]      repeater
    data32 |= 0                     << 2;   // [2]      ksvlist_ready
    data32 |= 0                     << 1;   // [1]      timeout
    data32 |= 0                     << 0;   // [0]      lost_auth
    hdmirx_wr_dwc(HDMIRX_DWC_HDCP_RPT_CTRL, data32);

    hdmirx_wr_dwc(HDMIRX_DWC_HDCP_RPT_BSTATUS, 0);  /* nothing attached downstream */

    data32  = 0;
    data32 |= (0                    << 25); // [25]     hdcp_endislock:1=once hdcp_enable is on, can not be disabled unless by reset; 0=no lock hdcp_enable.
    data32 |= (HDCP_ON              << 24); // [24]     hdcp_enable
    data32 |= (0                    << 10); // [11:10]  hdcp_sel_avmute: 0=normal mode.
    data32 |= (0                    << 8);  // [9:8]    hdcp_ctl: 0=automatic.
    data32 |= (0                    << 6);  // [7:6]    hdcp_ri_rate: 0=Ri exchange once every 128 frames.
    data32 |= (HDCP_KEY_DECRYPT_EN  << 1);  // [1]      key_decrypt_enable
    data32 |= (HDCP_ON              << 0);  // [0]      hdcp_enc_en
    hdmirx_wr_dwc(HDMIRX_DWC_HDCP_CTRL, data32);
}

void hdmirx_init(void)
{
    unsigned long   data32;
    unsigned long   base_offset = INT_HDMIRX_BASE_OFFSET;
    LOGD(TAG_HDMIRX, "[HDMIRX.C] Configure HDMI 2.0 RX -- Begin 0819\n");
    // --------------------------------------------------------
    // Program core_pin_mux to enable HDMI pins
    // --------------------------------------------------------
    (*P_PERIPHS_PIN_MUX_0) |= (1 << 23) ;  // pm_gpioA_4_hdmirx_cec_EE
    (*P_PERIPHS_PIN_MUX_2) |= ( //(1 << 17)   |   // pm_gpioB_9_hdmirx_cec_EE
                                (1 << 4)    |   // pm_gpioB_4_hdmirx_5v
                                (1 << 3)    |   // pm_gpioB_3_hdmirx_hpd
                                (1 << 2)    |   // pm_gpioB_2_hdmirx_sda
                                (1 << 1));      // pm_gpioB_1_hdmirx_scl
    //(*P_PAD_PULL_UP_REG2) |= (1 << 9);  // pull up gpioB[9] cec
    (*P_PAD_PULL_UP_REG0) |= (1 << 4);  // pull up gpioA[4] cec
    //Wr_reg_bits(HHI_GCLK_MPEG0, 1, 21, 1);  // Turn on clk_hdmirx_pclk, also = sysclk
    *P_PERIPHS_CLK_GATE_EN_EE |= (1<<6); // turn on sysclk and PCLK
    // Enable APB3 fail on error
    *((volatile unsigned long *) (HDMIRX_CTRL_PORT+INT_HDMIRX_BASE_OFFSET))         |= ((1 << 15) | (1<<12));   // APB3 to INT HDMIRX-TOP err_en, and stack_enable=1.
    *((volatile unsigned long *) (HDMIRX_CTRL_PORT+INT_HDMIRX_BASE_OFFSET+0x10))    |= ((1 << 15) | (1<<12));   // APB3 to INT HDMIRX-DWC err_en, and stack_enable=1.
    //*((volatile unsigned long *) (HDMIRX_CTRL_PORT+EXT_HDMIRX_BASE_OFFSET))       |= ((1 << 15) | (1<<12));   // APB3 to EXT HDMIRX-TOP err_en, and stack_enable=1.
    //*((volatile unsigned long *) (HDMIRX_CTRL_PORT+EXT_HDMIRX_BASE_OFFSET+0x10))  |= ((1 << 15) | (1<<12));   // APB3 to EXT HDMIRX-DWC err_en, and stack_enable=1.
    //--------------------------------------------------------------------------
    // Enable HDMIRX interrupts:
    //--------------------------------------------------------------------------
    //data32    = 0;
    //data32 |= (1  << 2);  // [    2] hdmirx_5v_rise
    //data32 |= (1  << 6);  // [    6] hdmirx_5v_fall
    //data32 |= (1  << 0);  // [    0] IP_irq

    //--------------------------------------------------------------------------
    // Step 1-13: RX_INITIAL_CONFIG
    //--------------------------------------------------------------------------
    // 1. DWC reset default to be active, until reg HDMIRX_TOP_SW_RESET[0] is set to 0.
    //hdmirx_rd_check_top(HDMIRX_TOP_SW_RESET, 0x1, 0x0);
    hdmirx_wr_top(HDMIRX_TOP_MEM_PD,    0); // Release memories out of power down.
    // 2. turn on clocks: hdmirx_modet_clk, hdmirx_cfg_clk, hdmirx_acr_ref_clk, hdmirx_phy_cfg_clk, and hdmi_audmeas_ref_clk
    data32  = 0;
    //data32 |= (1 << 25);  // [26:25] HDMIRX mode detection clock mux select: sys_pll_clk
    data32 |= (0 << 25);    // [26:25] HDMIRX mode detection clock mux select: osc_clk
    data32 |= (1 << 24);    // [24]    HDMIRX mode detection clock enable
    ////data32 |= (0xf << 16);  // [22:16] HDMIRX mode detection clock divider: 800/16 = 50MHz //typical:50MHz
    data32 |= (0 << 16);    // [22:16] HDMIRX mode detection clock divider: 24/1 = 24MHz
    data32 |= (1 << 9);     // [10: 9] HDMIRX config clock mux select: sys_pll_clk=800M //1.2GHz
    data32 |= (1 << 8);     // [    8] HDMIRX config clock enable
    //data32 |= (8 << 0);   // [ 6: 0] HDMIRX config clock divider: 1200/9=133.3MHz
    ////data32 |= (2 << 0);     // [ 6: 0] HDMIRX config clock divider: 800/3= 266.6 //typical:300MHz
    data32 |= (5 << 0);     // [ 6: 0] HDMIRX config clock divider: 800/6=133.3MHz
    Wr(HDMIRX_CFG_CLK_CNTL,     data32);
    data32  = 0;
    data32 |= (1        << 25); // [26:25] HDMIRX ACR ref clock mux select: sys_pll_clk=800 //1.2GHz
    data32 |= (ACR_MODE << 24); // [24]    HDMIRX ACR ref clock enable
    //data32 |= (2      << 16); // [22:16] HDMIRX ACR ref clock divider: 1200/3=400MHz //typical 400MHz
    data32 |= (1        << 16); // [22:16] HDMIRX ACR ref clock divider: 800/2=400MHz   407M
    Wr(HDMIRX_AUD_CLK_CNTL, data32);
    data32  = 0;
    data32 |= (0        << 21); // [22:21] hdmirx_phy_cfg_clk mux select: osc_clk
    data32 |= (1        << 20); // [   20] hdmirx_phy_cfg_clk enable
    data32 |= (0        << 12); // [18:12] hdmirx_phy_cfg_clk divider: 24/1 = 24MHz 24.48m
    //data32 |= (1      << 9);  // [10: 9] HDMIRX audmeas clock mux select: sys_pll_clk
    data32 |= (0        << 9);  // [10: 9] HDMIRX audmeas clock mux select: osc_clk
    data32 |= (1        << 8);  // [    8] HDMIRX audmeas clock enable
    //data32 |= (4      << 0);  // [ 6: 0] HDMIRX audmeas clock divider: 800/4 = 200MHz //typical:250
    data32 |= (0        << 0);  // [ 6: 0] HDMIRX audmeas clock divider: 24/1 = 24MHz   ????
    Wr(HDMIRX_MEAS_CLK_CNTL, data32);
    //hdmirx_audioclk_init();

    // 3. wait for TX PHY clock up

    // 4. wait for rx sense
    // 5. Release IP reset
    hdmirx_wr_top(HDMIRX_TOP_SW_RESET,  0x0);
    // 6. Enable functional modules
    data32  = 0;
    #ifdef HDMIRX_VID_CEA
    data32 |= (1 << 6); // [6]  pixel_enable
    #endif  /* HDMIRX_VID_CEA */
    data32 |= (1 << 5); // [5]  cec_enable
    data32 |= (1 << 4); // [4]  aud_enable
    data32 |= (1 << 3); // [3]  bus_enable
    data32 |= (1 << 2); // [2]  hdmi_enable
    data32 |= (1 << 1); // [1]  modet_enable
    data32 |= (1 << 0); // [0]  cfg_enable
    hdmirx_wr_dwc(HDMIRX_DWC_DMI_DISABLE_IF,    data32);
    delay_us(5);
    printf("hdmirx 7 reset functional module\n");
    // 7. Reset functional modules
    //hdmirx_wr_only_dwc(HDMIRX_DWC_DMI_SW_RST, 0x0000007F);
    delay_us(10);
    //hdmirx_wr_only_dwc(HDMIRX_DWC_DMI_SW_RST, 0);
    // hpd init
    data32  = 0;
    data32 |= (0                << 5);  // [    5]  invert_hpd
    data32 |= (1                << 4);  // [    4]  force_hpd: default=1
    data32 |= (1                << 0);  // [    0]  hpd_config
    hdmirx_wr_only_top(HDMIRX_TOP_HPD_PWR5V,    data32);

    #ifdef IN_FBC_MAIN_CONFIG
    hdmirx_wr_top(HDMIRX_TOP_INTR_MASKN,    top_ien_maskn);
    printf("set top irq %x\n",top_ien_maskn);
    #endif
    // 9. Set EDID data at RX
    hdmirx_edid_setting();

    data32  = 0;
    data32 |= (EDID_IN_FILTER_MODE              << 14); // [16:14]  i2c_filter_mode
    data32 |= (((EDID_IN_FILTER_MODE==0)?0:1)   << 13); // [   13]  i2c_filter_enable
    data32 |= (EDID_AUTO_CEC_ENABLE             << 11); // [   11]  auto_cec_enable
    data32 |= (0                                << 10); // [   10]  scl_stretch_trigger_config
    data32 |= (0                                << 9);  // [    9]  force_scl_stretch_trigger
    data32 |= (1                                << 8);  // [    8]  scl_stretch_enable
    data32 |= (EDID_CLK_DIVIDE_M1               << 0);  // [ 7: 0]  clk_divide_m1
    hdmirx_wr_top(HDMIRX_TOP_EDID_GEN_CNTL, data32);
    //hdmirx_wr_top(HDMIRX_TOP_EDID_ADDR_CEC, EDID_CEC_ID_ADDR);
    //hdmirx_wr_top(HDMIRX_TOP_EDID_DATA_CEC_PORT01,    ((EDID_CEC_ID_DATA&0xff)<<8) | (EDID_CEC_ID_DATA>>8));

    // 10. HDCP
    hdmirx_hdcp_init();
    hdmirx_register_channel();
    hdmirx_config();
    //cec_init
}
void hdmirx_audio_fifo_rst(void)
{
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_FIFO_CTRL, 1);
    delay_us(10);
    hdmirx_wr_dwc(HDMIRX_DWC_AUD_FIFO_CTRL, 0);
}

#ifdef IN_FBC_MAIN_CONFIG
void HDMIRX_IRQ_Handle(void *arg)
{
    unsigned long tmp_data;
    //unsigned long data32;
    unsigned long hdmirx_top_intr_stat;
    unsigned int  core_intr_rpt_num = 0;
    //unsigned long cts;
    //unsigned int  i;
    //unsigned long ref_cycles_stat0;
    //unsigned long ref_cycles_stat1;
#ifdef ENABLE_CEC_FUNCTION
    int b_cec_get_msg = 0;
#endif
	if(0){//(OUTPUT_VB1 == panel_param->output_mode){
		static int vx1_rst_flag = 1;
		int vx1_sts = 0;
		vx1_sts = Rd_reg_bits(VBO_RO_STATUS,0,6);
		if((vx1_rst_flag == 1) && (vx1_sts == 2 || vx1_sts == 4 || vx1_sts == 8)){
			vbyone_softreset();
			printf("vx1 rst\n");
			vx1_rst_flag = 0;
		}else if((vx1_rst_flag == 0) && (vx1_sts == 0x20))
			vx1_rst_flag = 1;
	}
    hdmirx_top_intr_stat = hdmirx_rd_top(HDMIRX_TOP_INTR_STAT);
    hdmirx_wr_only_top(HDMIRX_TOP_INTR_STAT_CLR, hdmirx_top_intr_stat); // clear interrupts in HDMIRX-TOP module

    // For core_intr, best check bit [31] rather [0], to make sure we've served all interrupt requests until we see ohdmi_int level goes down.
    if (hdmirx_top_intr_stat & (1 << 31)) {
        // [31] DWC_hdmi_rx.ohdmi_int
        // Check packet decoder interrupts in HDMIRX-DWC
#if 1
        tmp_data = hdmirx_rd_dwc(HDMIRX_DWC_PDEC_ISTS) & dwc_pdec_ien_maskn;
        if (tmp_data) {
            hdmirx_wr_only_dwc(HDMIRX_DWC_PDEC_ICLR, tmp_data);
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT00_pdFifoThMinPass
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT00_pdFifoThMinPass) {
                //stimulus_print("[TEST.C] Error: HDMIRX DWC.pd_fifo_th_min_pass Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT01_pdFifoThMaxPass
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT01_pdFifoThMaxPass) {
                //stimulus_print("[TEST.C] Error: HDMIRX DWC.pd_fifo_th_max_pass Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT02_pdFifoThStartPass
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT02_pdFifoThStartPass) {
                //stimulus_print("[TEST.C] HDMIRX DWC.pd_fifo_th_start_pass Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT03_pdFifoUnderfl
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT03_pdFifoUnderfl) {
                //stimulus_print("[TEST.C] Error: HDMIRX DWC.pd_fifo_underfl Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT04_pdFifoOverfl
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT04_pdFifoOverfl) {
                //stimulus_print("[TEST.C] Error: HDMIRX DWC.pd_fifo_overfl Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT08_pdFifoNewEntry
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT08_pdFifoNewEntry) {
                //stimulus_print("[TEST.C] HDMIRX DWC.pd_fifo_new_entry Interrupt Process_Irq\n");
                // Check packets stored in FIFO
                while (hdmirx_rd_dwc(HDMIRX_DWC_PDEC_STS) & (1<<8)) {
                    data32 = hdmirx_rd_dwc(HDMIRX_DWC_PDEC_FIFO_DATA);
                    switch (data32 & 0xff) {
                    case 0x82 : // AVI packet in FIFO
                        if (data32 != 0x000d0282) {
                            //stimulus_print("[TEST.C] Error: HDMI AVI InfoFrame header incorrect!\n");
                        }
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00081000 | (RX_COLOR_FORMAT<<(8+5)), 0x000000ff);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  (PIXEL_REPEAT_HDMI<<8) | VIC, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                    break;
                    case 0x84 : // AIF packet in FIFO
                        if (data32 != 0x000a0184) {
                            //stimulus_print("[TEST.C] Error: HDMI AIF InfoFrame header incorrect!\n");
                        }
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00030000 | ((RX_8_CHANNEL?7:1)<<8), 0x000000ff);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000113, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                        hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_FIFO_DATA,  0x00000000, 0);
                    break;
                    default :
                        //stimulus_print("[TEST.C] Error: Unkown HDMI InfoFrame received!\n");
                    break;
                    }
                }
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT15_vsiRcv
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT15_vsiRcv) {
                //stimulus_print("[TEST.C] HDMIRX DWC.vsi_rcv Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT16_gcpRcv
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT16_gcpRcv) {
                //stimulus_print("[TEST.C] HDMIRX DWC.gcp_rcv Interrupt Process_Irq\n");
                if (gcp_rcv == 0) {
                    gcp_rcv = 1;    // Do not check the color_depth on the 1st GCP, it has some latency
                } else {
                    hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_GCP_AVMUTE, RX_COLOR_DEPTH<<4, ~(0xf<<4));
                }
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT17_acrRcv
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT17_acrRcv) {
                //stimulus_print("[TEST.C] HDMIRX DWC.acr_rcv Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT18_aviRcv
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT18_aviRcv) {
                //stimulus_print("[TEST.C] HDMIRX DWC.avi_rcv Interrupt Process_Irq\n");
                // Check AVI InfoFrame's pixel repetition factor
                hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_AVI_HB, PIXEL_REPEAT_HDMI<<24, 0xf0ffffff);
                // Check AVI InfoFrame's VIC and video format
                hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_AVI_PB, (VIC<<24) | (RX_COLOR_FORMAT<<5), 0x80ffff9f);
                // On first AVI received, cancel manual/force mode done for speeding up simulation. Now that we can do it automatically.
                #if 0
                if (recv_avi==0) {
                    recv_avi = 1;
                    // Cancel manual oavi_video_format for YUV422 and YUV420 video
                    if ((RX_COLOR_FORMAT == HDMI_COLOR_FORMAT_422) || (RX_COLOR_FORMAT == HDMI_COLOR_FORMAT_420)) {
                        stimulus_event(31, STIMULUS_HDMI_UTIL_VID_FORMAT    |
                                            (0              << 4)           |   // 0=Release force; 1=Force vid_fmt
                                            (RX_COLOR_FORMAT << 0));            // Video format: 0=RGB444; 1=YCbCr422; 2=YCbCr444; 3=YCbCr420.
                    // Cancel manual-mapping component data for YUV444 video
                    } else if (RX_COLOR_FORMAT == HDMI_COLOR_FORMAT_444) {
                        // [26:24]  vid_data_map. 0={vid2, vid1, vid0}->{vid2, vid1, vid0}
                        hdmirx_wr_reg(INT_HDMIRX_BASE_OFFSET, HDMIRX_DEV_ID_TOP, HDMIRX_TOP_VID_CNTL,   hdmirx_rd_reg(INT_HDMIRX_BASE_OFFSET, HDMIRX_DEV_ID_TOP, HDMIRX_TOP_VID_CNTL) & (~(0x7<<24)));
                    }
                }
                #endif
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT19_aifRcv
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT19_aifRcv) {
                //stimulus_print("[TEST.C] HDMIRX DWC.aif_rcv Interrupt Process_Irq\n");
                // Check Audio InfoFrame's channel speaker allocation field
                hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_AIF_PB0, (0x13<<24) | (0x3<<8) | ((RX_8_CHANNEL?7:1) <<0),0);
                hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_AIF_PB1, (1<<8) | (0<<7) | (0<<3),0);
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT20_gmdRcv
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT20_gmdRcv) {
                //stimulus_print("[TEST.C] HDMIRX DWC.gmd_rcv Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT21_gcpAvmuteChg
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT21_gcpAvmuteChg) {
                //stimulus_print("[TEST.C] HDMIRX DWC.gcp_av_mute_chg Interrupt Process_Irq\n");
                if(hdmirx_rd_dwc(0x380) & 3 == 2){
					enable_csc0(1);
                }
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT22_acrCtsChg
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT22_acrCtsChg) {
                //stimulus_print("[TEST.C] HDMIRX DWC.acr_cts_chg Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT23_acrNChg
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT23_acrNChg) {
                //stimulus_print("[TEST.C] HDMIRX DWC.acr_n_chg Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT24_aviCksChg
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT24_aviCksChg) {
                //stimulus_print("[TEST.C] HDMIRX DWC.avi_cks_chg Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT25_aifCksChg
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT25_aifCksChg) {
                //stimulus_print("[TEST.C] HDMIRX DWC.aif_cks_chg Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT26_gmdCksChg
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT26_gmdCksChg) {
                //stimulus_print("[TEST.C] HDMIRX DWC.gmd_cks_chg Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT27_vsiCksChg
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT27_vsiCksChg) {
                //stimulus_print("[TEST.C] HDMIRX DWC.vsi_cks_chg Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT28_dviDet
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT28_dviDet) {
                if (hdmi_mode==0) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.dvidet Interrupt Process_Irq: switch to HDMI mode\n");
                    hdmi_mode = 1;
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.dvidet Interrupt Process_Irq: switch to DVI mode\n");
                    hdmi_mode = 0;
                }
            }
            #endif
            #ifdef HDMIRX_DWC_PDEC_IEN_BIT29_aud_type_chg
            if (tmp_data & HDMIRX_DWC_PDEC_IEN_BIT29_aud_type_chg) {
                //stimulus_print("[TEST.C] Error: HDMIRX DWC.aud_type_chg Interrupt Process_Irq\n");
            }
            #endif
        }
#endif
        // Check audio clock and CEC interrupts in HDMIRX-DWC
        tmp_data = hdmirx_rd_dwc(HDMIRX_DWC_AUD_CEC_ISTS) & 3<<16;
        if (tmp_data) {
            hdmirx_wr_only_dwc(HDMIRX_DWC_AUD_CEC_ICLR, tmp_data);
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT00_ctsnCnt
            if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT00_ctsnCnt) {
                //stimulus_print("[TEST.C] HDMIRX DWC.ctsn_cnt Interrupt Process_Irq\n");
                recv_acr_packet_cnt ++;
                // Check received N & CTS value
                hdmirx_rd_check_dwc(HDMIRX_DWC_PDEC_ACR_N,  EXPECT_ACR_N, 0);
                cts = hdmirx_rd_dwc(HDMIRX_DWC_PDEC_ACR_CTS);
                if ((cts < (EXPECT_ACR_CTS-1)) || (cts > (EXPECT_ACR_CTS+1))) {
                    //stimulus_display("[TEST.C] Error: HDMIRX received out-of-range CTS value, actual=%d\n", cts);
                }
                if (recv_acr_packet_cnt == 1) {
                    // Switch N & CTS to the values that are received by ACR info packets
                    // [4]      cts_n_ref: 0=used decoded; 1=use manual N&CTS.
                    hdmirx_wr_dwc(HDMIRX_DWC_AUD_CLK_CTRL,  0);
                } else if (recv_acr_packet_cnt == 4) {
                    // Check AUD PLL should have been locked by now.
                    hdmirx_rd_check_dwc(HDMIRX_DWC_AUD_PLL_CTRL, 1<<31, ~(1<<31));
                    // Enable TX I2S I/F
                    //stimulus_print("[TEST.C] Start Audio\n");
                    if (TX_I2S_SPDIF) {
                        hdmitx_wr_reg(EXT_HDMITX_BASE_OFFSET, HDMITX_DEV_ID_DWC, HDMITX_DWC_AUD_CONF0,
                                        hdmitx_rd_reg(EXT_HDMITX_BASE_OFFSET, HDMITX_DEV_ID_DWC, HDMITX_DWC_AUD_CONF0) | ((TX_I2S_8_CHANNEL? 0xf : 0x1) << 0));
                    }
                    // Enable external audio data generator
                    stimulus_event(31, STIMULUS_HDMI_UTIL_AGEN_ENABLE | (1 << 0));
                } else if (recv_acr_packet_cnt == 10) {
                    // TODO
                    ////stimulus_print("[TEST.C] Start audio clock measure...\n");
                    //Wr(AUDIN_HDMI_MEAS_CTRL,    Rd(AUDIN_HDMI_MEAS_CTRL) | (1 << 1));   // [    1] enable
                }
            }
            #endif
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT01_sckStable
            if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT01_sckStable) {
                //stimulus_print("[TEST.C] HDMIRX DWC.sck_stable Interrupt Process_Irq\n");
                // Check audio PLL lock stable
                hdmirx_rd_check_dwc(HDMIRX_DWC_AUD_PLL_CTRL, 1<<31, ~(1<<31));
            }
            #endif
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT16_done
            if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT16_done) {
                //printf("done\n");
                //stimulus_print("[TEST.C] HDMIRX DWC.cec_done Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT17_eom
                    if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT17_eom) {
#ifdef ENABLE_CEC_FUNCTION
                        b_cec_get_msg = 1;
                        //printf("ack\n");
#endif
                    }
            #endif
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT18_nack
                    if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT18_nack) {
                        //stimulus_print("[TEST.C] HDMIRX DWC.cec_nack Interrupt Process_Irq\n");
                    }
            #endif
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT19_arblst
                    if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT19_arblst) {
                        //stimulus_print("[TEST.C] HDMIRX DWC.cec_arblst Interrupt Process_Irq\n");
                    }
            #endif
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT20_errorInit
                    if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT20_errorInit) {
                        //stimulus_print("[TEST.C] HDMIRX DWC.cec_error_init Interrupt Process_Irq\n");
                    }
            #endif
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT21_errorFoll
                    if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT21_errorFoll) {
                        //stimulus_print("[TEST.C] HDMIRX DWC.cec_error_foll Interrupt Process_Irq\n");
                    }
            #endif
            #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT22_wakeupctrl
                    if (tmp_data & HDMIRX_DWC_AUD_CEC_IEN_BIT22_wakeupctrl) {
                        //stimulus_print("[TEST.C] HDMIRX DWC.cec_wakeupctrl Interrupt Process_Irq\n");
                    }
            #endif
        }
#if 1
        // Check audio FIFO interrupts in HDMIRX-DWC
        tmp_data = hdmirx_rd_dwc(HDMIRX_DWC_AUD_FIFO_ISTS) & dwc_aud_fifo_ien_maskn;
        if (tmp_data) {
            hdmirx_wr_only_dwc(HDMIRX_DWC_AUD_FIFO_ICLR, tmp_data);
            #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT00_afifThMin
            if (tmp_data & HDMIRX_DWC_AUD_FIFO_IEN_BIT00_afifThMin) {
                //stimulus_print("[TEST.C] HDMIRX DWC.afif_th_min Interrupt Process_Irq\n");
            }
        #endif
        #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT01_afifThMax
                    if (tmp_data & HDMIRX_DWC_AUD_FIFO_IEN_BIT01_afifThMax) {
                        //stimulus_print("[TEST.C] HDMIRX DWC.afif_th_max Interrupt Process_Irq\n");
                    }
        #endif
        #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT02_afifThsPass
                    if (tmp_data & HDMIRX_DWC_AUD_FIFO_IEN_BIT02_afifThsPass) {
                        //stimulus_print("[TEST.C] HDMIRX DWC.afif_ths_pass Interrupt Process_Irq\n");
                        // Start analyzing audio output
                        stimulus_event(31, STIMULUS_HDMI_UTIL_AIU_ANLYZ_EN  |
                                          (0                << 18)          |   // aiu_data_frm_old_spdif
                                          (EXP_AUDIO_LENGTH << 2)           |   // exp/i2s_data.exp file length
                                          (1                << 0));             // Enable analyzing AIU output
                    }
        #endif
        #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT03_afifUnderfl
                    if (tmp_data & HDMIRX_DWC_AUD_FIFO_IEN_BIT03_afifUnderfl) {
                        hdmirx_audio_fifo_rst();
                    }
        #endif
        #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT04_afifOverfl
                    if (tmp_data & HDMIRX_DWC_AUD_FIFO_IEN_BIT04_afifOverfl) {
                        hdmirx_audio_fifo_rst();
                    }
        #endif
                }
#endif
#if 1
        // Check video mode interrupts in HDMIRX-DWC
        tmp_data = hdmirx_rd_dwc( HDMIRX_DWC_MD_ISTS) & dwc_md_ien_maskn;
        if (tmp_data) {
            hdmirx_wr_only_dwc(HDMIRX_DWC_MD_ICLR,  tmp_data);
            #ifdef HDMIRX_DWC_MD_IEN_BIT00_hsAct
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT00_hsAct) {
                //stimulus_print("[TEST.C] HDMIRX DWC.hs_act Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT01_vsAct
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT01_vsAct) {
                if (vsAct_1st) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.vs_act Interrupt Process_Irq: Initial change\n");
                    vsAct_1st  = 0;
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.vs_act Interrupt Process_Irq: Subsequent change\n");
                }
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT02_deActivity
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT02_deActivity) {
                //stimulus_print("[TEST.C] HDMIRX DWC.de_activity Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT03_ilace
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT03_ilace) {
                //stimulus_print("[TEST.C] HDMIRX DWC.interlace Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT04_htot32Clk
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT04_htot32Clk) {
                if (htot32_1st) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.htot32_clk Interrupt Process_Irq: Initial change\n");
                    htot32_1st  = 0;
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.htot32_clk Interrupt Process_Irq: Subsequent change\n");
                }
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT05_hsClk
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT05_hsClk) {
                hs_clk_cnt ++;
                if (hs_clk_cnt <= 2) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.hs_clk Interrupt Process_Irq: Initial change\n");
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.hs_clk Interrupt Process_Irq: Subsequent change\n");
                }
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT06_hactPix
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT06_hactPix) {
                hactPix_cnt ++;
                if (hactPix_cnt <= 2) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.hact_pix Interrupt Process_Irq: Initial change\n");
                    if (hactPix_cnt == 2) {
                        hdmirx_rd_check_reg(INT_HDMIRX_BASE_OFFSET, HDMIRX_DEV_ID_DWC, HDMIRX_DWC_MD_HACT_PX,   ACTIVE_PIXELS, 0);
                    }
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.hact_pix Interrupt Process_Irq: Subsequent change\n");
                }
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT07_vtotClk
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT07_vtotClk) {
                //stimulus_print("[TEST.C] HDMIRX DWC.vtot_clk Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT08_vsClk
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT08_vsClk) {
                //stimulus_print("[TEST.C] HDMIRX DWC.vs_clk Interrupt Process_Irq\n");
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT09_vactLin
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT09_vactLin) {
                if (vactLin_1st) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.vact_lin Interrupt Process_Irq: Initial change\n");
                    vactLin_1st = 0;
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.vact_lin Interrupt Process_Irq: subsequent change\n");
                }
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT10_vtotLin
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT10_vtotLin) {
                if (vtotLin_1st) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.vtot_lin Interrupt Process_Irq: Initial change\n");
                    vtotLin_1st = 0;
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.vtot_lin Interrupt Process_Irq: subsequent change\n");
                }
            }
            #endif
            #ifdef HDMIRX_DWC_MD_IEN_BIT11_vofsLin
            if (tmp_data & HDMIRX_DWC_MD_IEN_BIT11_vofsLin) {
                vofsLin_cnt ++;
                if (vofsLin_cnt <= 3) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.vofs_lin Interrupt Process_Irq: Initial change\n");
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.vofs_lin Interrupt Process_Irq: subsequent change\n");
                }
            }
            #endif
        }
#endif
#if 1
        // Check hdmi interrupts in HDMIRX-DWC
        tmp_data = hdmirx_rd_dwc(HDMIRX_DWC_HDMI_ISTS) & dwc_hdmi_ien_maskn;
        if (tmp_data) {
            hdmirx_wr_only_dwc(HDMIRX_DWC_HDMI_ICLR, tmp_data);
            #ifdef HDMIRX_DWC_HDMI_IEN_BIT05_pllLckChg
            if (tmp_data & HDMIRX_DWC_HDMI_IEN_BIT05_pllLckChg) {
                hdmi_pll_lock = hdmirx_rd_dwc(HDMIRX_DWC_HDMI_PLL_LCK_STS) & 0x1;
                if (hdmi_pll_lock) {
                    //stimulus_print("[TEST.C] HDMIRX DWC.pll_lck=1 Interrupt Process_Irq\n");
                } else {
                    //stimulus_print("[TEST.C] Error: HDMIRX DWC.pll_lck=0 Interrupt Process_Irq\n");
                }
            }
            #endif
            #ifdef HDMIRX_DWC_HDMI_IEN_BIT25_aksvRcv
            if (tmp_data & HDMIRX_DWC_HDMI_IEN_BIT25_aksvRcv) {
                //stimulus_print("[TEST.C] HDMIRX DWC.aksvRcv Interrupt Process_Irq\n");
                aksv_received   = 1;
            }
            #endif
            #ifdef HDMIRX_DWC_HDMI_IEN_BIT19_scdcTmdsCfgChg
            if (tmp_data & HDMIRX_DWC_HDMI_IEN_BIT19_scdcTmdsCfgChg) {
                int scdc_temp;
                scdc_temp = hdmirx_rd_dwc(HDMIRX_DWC_SCDC_REGS0);
                if((scdc_temp >> 16) & 0x1 != SCRAMBLER_EN) {
                    //stimulus_print("[TEST.C] Error: HDMIRX SCDC Scrambler_en check failed\n");
                    stimulus_finish_fail(16);
                }
                if((scdc_temp >> 17) & 0x1 != TMDS_CLK_DIV4) {
                    //stimulus_print("[TEST.C] Error: HDMIRX SCDC tmds_clk_div4 check failed\n");
                    stimulus_finish_fail(17);
                }
                //stimulus_print("[TEST.C] HDMIRX DWC.scdcTmdsCfgChg Interrupt Process_Irq and check passed\n");
            }
            #endif
        }
#endif
        // During interrupt serving, further ohdmi_int sources may become active,
        // re-check bit [31] DWC_hdmi_rx.ohdmi_int, if it is still high, repeat the interrupt service.
        if (hdmirx_rd_top(HDMIRX_TOP_INTR_STAT) & (1<<31)) {
            hdmirx_wr_only_top(HDMIRX_TOP_INTR_STAT_CLR, 1<<0); // clear core_intr_rise in HDMIRX-TOP module
            //stimulus_display("[TEST.C] HDMIRX CORE_INTR Interrupt Process_Irq: repeat %d\n", ++core_intr_rpt_num);
        } else {
            hdmirx_top_intr_stat &= ~(1<<31);
        }
    } /* while (hdmirx_top_intr_stat & (1 << 31)) // [31] DWC_hdmi_rx.ohdmi_int */
#if 1
    #ifdef HDMIRX_TOP_IEN_BIT01_EDID_ADDR_INTR
    if (hdmirx_top_intr_stat & (1 << 1)) {  // [1] edid_addr_intr
            //stimulus_print("[TEST.C] HDMIRX EDID_ADDR Interrupt Process_Irq\n");
            // Check EDID_ADDR status in HDMIRX-TOP.edid_if
            //hdmirx_rd_check_reg(INT_HDMIRX_BASE_OFFSET, HDMIRX_DEV_ID_TOP, HDMIRX_TOP_EDID_GEN_STAT_A,    1<<16, ~(1<<16));
            tmp_data = (edid_addr_intr_num+1)%256;
            for (i = (3+edid_addr_intr_num*2)*128; (i < (3+(edid_addr_intr_num+1)*2)*128) && (i < (1+EDID_EXTENSION_FLAG)*128); i++) {
                hdmirx_wr_reg(INT_HDMIRX_BASE_OFFSET, HDMIRX_DEV_ID_TOP, HDMIRX_TOP_EDID_OFFSET+(i&0x1ff),  tmp_data);
                tmp_data = (tmp_data+1)%256;
            }
            edid_addr_intr_num ++;
            // Clear EDID_ADDR status in HDMIRX-TOP.edid_if, which also cancels i2c_clock_stretching
            hdmirx_wr_only_top(HDMIRX_TOP_EDID_GEN_STAT_A,  1<<16); // clear EDID_ADDR status in HDMIRX-TOP.edid_if
            //hdmirx_rd_check_top(HDMIRX_TOP_EDID_GEN_STAT_A, 0<<16, ~(1<<16));
        } /* edid_addr_intr */
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT02_5V_RISE
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT02_5V_RISE) {  // [2] hdmirx_5v_rise
        //stimulus_print("[TEST.C] HDMIRX RX_5V_RISE Interrupt Process_Irq\n");
        //hdmirx_rd_check_top(HDMIRX_TOP_HPD_PWR5V, 1<<20, ~(0xf<<20));
        //printf("HPD high\n");
        //hdmirx_wr_top(HDMIRX_TOP_HPD_PWR5V, 0x10);
    } /* if (hdmirx_top_intr_stat & (1 << 2)) // [2] hdmirx_5v_rise */
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT03_VID_BACKPORCH_STABLE
    // [3] Back porch pixel count stable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT03_VID_BACKPORCH_STABLE)   {
        irq_stable_flag |= HDMIRX_TOP_IEN_BIT03_VID_BACKPORCH_STABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT04_VID_FRONTPORCH_STABLE
    // [4] Front porch pixel count stable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT04_VID_FRONTPORCH_STABLE){
        irq_stable_flag |= HDMIRX_TOP_IEN_BIT03_VID_BACKPORCH_STABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT05_HSYNC_PIXEL_STABLE
    // [5] Hsync pixel count stable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT05_HSYNC_PIXEL_STABLE){
        irq_stable_flag |= HDMIRX_TOP_IEN_BIT05_HSYNC_PIXEL_STABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT06_5V_FALL
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT06_5V_FALL){   // [6] hdmirx_5v_fall
        //printf("HPD low\n");
        //hdmirx_wr_top(HDMIRX_TOP_HPD_PWR5V, 0x11);
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT07_VID_ACTIVE_PIXEL_STABLE
    // [7] Active pixel count stable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT07_VID_ACTIVE_PIXEL_STABLE){
        irq_stable_flag |= HDMIRX_TOP_IEN_BIT07_VID_ACTIVE_PIXEL_STABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT08_VID_SOF_LINE_STABLE
    // [8] SOF line count stable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT08_VID_SOF_LINE_STABLE){
        irq_stable_flag |= HDMIRX_TOP_IEN_BIT08_VID_SOF_LINE_STABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT09_VID_EOF_LINE_STABLE
    // [9] EOF line count stable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT09_VID_EOF_LINE_STABLE){
        irq_stable_flag |= HDMIRX_TOP_IEN_BIT09_VID_EOF_LINE_STABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT10_VID_FMT_CHANGE
    // [10] vid_fmt_chg
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT10_VID_FMT_CHANGE) {
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT10_VID_FMT_CHANGE;
        //hdmirx_rd_check_top(HDMIRX_TOP_VID_STAT, (RX_COLOR_FORMAT)<<20, ~(0x7<<20)); // check VID_FORMAT
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT11_VID_COLOR_DEPTH_CHANGE
    // [11] vid_colour_depth_chg
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT11_VID_COLOR_DEPTH_CHANGE) {
        // For deep-color mode, do not check color_depth on 1st vid_colour_depth_chg interrupt, it maybe junk data.
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT11_VID_COLOR_DEPTH_CHANGE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT12_METER_STABLE_CHG_HDMI
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT12_METER_STABLE_CHG_HDMI) { // [12] meter_stable_chg_hdmi
        //stimulus_print("[TEST.C] HDMIRX HDMI_CLK_STABLE_CHG Interrupt Process_Irq\n");
        tmp_data = hdmirx_rd_top(HDMIRX_TOP_METER_HDMI_STAT);
        if (tmp_data & (1<<31)) {
            //stimulus_print("[TEST.C] HDMIRX HDMI clock meter stable\n");
            if (((tmp_data & 0xffffff) != EXPECT_TMDS_MEAS) && ((tmp_data & 0xffffff) != EXPECT_TMDS_MEAS+1)) {
                    //stimulus_display2("[TEST.C] Error: HDMIRX HDMI clock meter result mismatch, expect=%d(+1), actual=%d\n", EXPECT_TMDS_MEAS, tmp_data & 0xffffff);
            }
        } else {
            //stimulus_print("[TEST.C] Error: HDMIRX HDMI clock meter unstable\n");
        }
    } /* if (hdmirx_top_intr_stat & (1 << 12)) // [12] meter_stable_chg_hdmi */
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT13_HDCP_AUTH_START_RISE
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT13_HDCP_AUTH_START_RISE) { // [13] hdcp_auth_start_rise
        //stimulus_print("[TEST.C] HDMIRX HDCP_AUTH_START_RISE Interrupt Process_Irq\n");
    } /* if (hdmirx_top_intr_stat & (1 << 13)) // [13] hdcp_auth_start_rise */
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT14_HDCP_AUTH_START_FALL
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT14_HDCP_AUTH_START_FALL) { // [14] hdcp_auth_start_fall
        //stimulus_print("[TEST.C] Error: HDMIRX HDCP_AUTH_START_FALL Interrupt Process_Irq\n");
    } /* if (hdmirx_top_intr_stat & (1 << 14)) // [14] hdcp_auth_start_fall */
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT15_HDCP_ENC_STATE_RISE
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT15_HDCP_ENC_STATE_RISE) { // [15] hdcp_enc_state_rise
        //stimulus_print("[TEST.C] HDMIRX HDCP_ENC_STATE_RISE Interrupt Process_Irq\n");
    } /* if (hdmirx_top_intr_stat & (1 << 15)) // [15] hdcp_enc_state_rise */
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT16_HDCP_ENC_STATE_FALL
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT16_HDCP_ENC_STATE_FALL) { // [16] hdcp_enc_state_fall
        //stimulus_print("[TEST.C] Error: HDMIRX HDCP_ENC_STATE_FALL Interrupt Process_Irq\n");
    } /* if (hdmirx_top_intr_stat & (1 << 16)) // [16] hdcp_enc_state_fall */
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT17_VID_VSYNC_LINE_STABLE
    // [17] Vsync line count stable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT17_VID_VSYNC_LINE_STABLE){
        irq_stable_flag |= HDMIRX_TOP_IEN_BIT17_VID_VSYNC_LINE_STABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT18_VID_ACTIVE_LINE_STABLE
    // [18] Active line count stable.
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT18_VID_ACTIVE_LINE_STABLE){
        irq_stable_flag |= HDMIRX_TOP_IEN_BIT18_VID_ACTIVE_LINE_STABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT19_VID_BACKPORCH_UNSTABLE
    // [19] Back porch pixel count unstable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT19_VID_BACKPORCH_UNSTABLE){
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT19_VID_BACKPORCH_UNSTABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT20_VID_FRONTPORCH_UNSTABLE
    // [20] Front porch pixel count unstable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT20_VID_FRONTPORCH_UNSTABLE){
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT20_VID_FRONTPORCH_UNSTABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT21_HSYNC_PIXEL_UNSTABLE
    // [21] Hsync pixel count unstable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT21_HSYNC_PIXEL_UNSTABLE){
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT21_HSYNC_PIXEL_UNSTABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT22_VID_ACTIVE_PIXEL_UNSTABLE
    // [22] Active pixel count unstable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT22_VID_ACTIVE_PIXEL_UNSTABLE){
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT22_VID_ACTIVE_PIXEL_UNSTABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT23_VID_SOF_LINE_UNSTABLE
    // [23] SOF line count unstable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT23_VID_SOF_LINE_UNSTABLE){
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT23_VID_SOF_LINE_UNSTABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT24_VID_EOF_LINE_UNSTABLE
    // [24] EOF line count unstable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT24_VID_EOF_LINE_UNSTABLE){
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT24_VID_EOF_LINE_UNSTABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT25_VID_VSYNC_LINE_UNSTABLE
    // [25] Vsync line count unstable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT25_VID_VSYNC_LINE_UNSTABLE){
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT25_VID_VSYNC_LINE_UNSTABLE;
    }
    #endif
    #ifdef HDMIRX_TOP_IEN_BIT26_VID_ACTIVE_LINE_UNSTABLE
    // [26] Active line count unstable
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT26_VID_ACTIVE_LINE_UNSTABLE){
        irq_unstable_flag |= HDMIRX_TOP_IEN_BIT26_VID_ACTIVE_LINE_UNSTABLE;
    }
    #endif
    #if HDMIRX_TOP_IEN_BIT27_METER_STABLE_CHG_CABLE
    if (hdmirx_top_intr_stat & HDMIRX_TOP_IEN_BIT27_METER_STABLE_CHG_CABLE) { // [27] meter_stable_chg_cable
        //stimulus_print("[TEST.C] HDMIRX CABLE_CLK_STABLE_CHG Interrupt Process_Irq\n");
        tmp_data = hdmirx_rd_reg(INT_HDMIRX_BASE_OFFSET, HDMIRX_DEV_ID_TOP, HDMIRX_TOP_METER_CABLE_STAT);
        if (tmp_data & (1<<31)) {
            //stimulus_print("[TEST.C] HDMIRX CABLE clock meter stable\n");
            if (((tmp_data & 0xffffff) != EXPECT_CABLE_MEAS) && ((tmp_data & 0xffffff) != EXPECT_CABLE_MEAS+1)) {
                //stimulus_display2("[TEST.C] Error: HDMIRX CABLE clock meter result mismatch, expect=%d(+1), actual=%d\n", EXPECT_CABLE_MEAS, tmp_data & 0xffffff);
            }
        } else {
                //stimulus_print("[TEST.C] Error: HDMIRX CABLE clock meter unstable\n");
        }
    } /* if (hdmirx_top_intr_stat & (1 << 27)) // [27] meter_stable_chg_cable */
    #endif
#endif

#ifdef ENABLE_CEC_FUNCTION
    if(b_cec_get_msg){
        hdmi_rx_get_cec_cmd();
        b_cec_get_msg = 0;
    }
#endif
}
#endif

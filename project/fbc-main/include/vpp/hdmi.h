#ifndef HDMI_H
#define HDMI_H




//------------------------------------------------------------------------------
// Operation parameters:
//------------------------------------------------------------------------------

/*

//------------------------------------------------------------------------------
// Defines to communicate from C code to verilog world
//------------------------------------------------------------------------------

// For testing HDMITX
#define STIMULUS_HDMI_UTIL_SET_VIC                  0x01000000
#define STIMULUS_HDMI_UTIL_SET_HSYNC_0              0x02000000
#define STIMULUS_HDMI_UTIL_SET_HSYNC_1              0x03000000
#define STIMULUS_HDMI_UTIL_SET_VSYNC_0              0x04000000
#define STIMULUS_HDMI_UTIL_SET_VSYNC_1              0x05000000
#define STIMULUS_HDMI_UTIL_SET_H_TOTAL              0x06000000
#define STIMULUS_HDMI_UTIL_VANLYZ_RESET             0x07000000
#define STIMULUS_HDMI_UTIL_AANLYZ_EN                0x08000000
#define STIMULUS_HDMI_UTIL_INIT_EOF                 0x1a000000  // simulation speedup for interlace video
#define STIMULUS_HDMI_UTIL_SET_ACR_N                0x1b000000
#define STIMULUS_HDMI_UTIL_SET_ACR_CTS              0x1c000000

// For testing HDMIRX
#define STIMULUS_HDMI_UTIL_SEL_RX_PORT              0x09000000
#define STIMULUS_HDMI_UTIL_SET_TOTAL_FRAMES         0x0a000000
#define STIMULUS_HDMI_UTIL_VGEN_RESET               0x0b000000
#define STIMULUS_HDMI_UTIL_AGEN_CTRL                0x0c000000
#define STIMULUS_HDMI_UTIL_AGEN_ENABLE              0x0d000000
#define STIMULUS_HDMI_UTIL_AIU_ANLYZ_EN             0x0e000000
#define STIMULUS_HDMI_UTIL_CEC1_CHK_REG_RD          0x0f000000
#define STIMULUS_HDMI_UTIL_AGEN_CTRL_2              0x10000000
#define STIMULUS_HDMI_UTIL_INVERT_HPD               0x11000000
#define STIMULUS_HDMI_UTIL_INIT_FIELD_NUM           0x12000000
#define STIMULUS_HDMI_UTIL_CALC_PLL_CONFIG          0x13000000
#define STIMULUS_HDMI_UTIL_VID_FORMAT               0x14000000
#define STIMULUS_HDMI_UTIL_ARCTX_MODE               0x15000000
#define STIMULUS_HDMI_UTIL_CHECK_HPD                0x16000000
#define STIMULUS_HDMI_UTIL_AOCEC_CHK_PARAM          0x17000000
#define STIMULUS_HDMI_UTIL_SET_V_TOTAL              0x18000000
#define STIMULUS_HDMI_UTIL_SET_PWR5V                0x19000000
#define STIMULUS_HDMI_UTIL_EARLY_START              0x1d000000

#define STIMULUS_EVENT_EXT_HDMI_TX_PLL              30
*/

extern void 			hdmirx_handler(void);
extern void				hdmirx_init(void);


#endif  /* HDMI_H */

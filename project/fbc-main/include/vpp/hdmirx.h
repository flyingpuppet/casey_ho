#ifndef HDMIRX_H
#define HDMIRX_H

// Device ID to differentiate HDMIRX register access to TOP, DWC or PHY
#define HDMIRX_DEV_ID_TOP       0
#define HDMIRX_DEV_ID_DWC       1
#define HDMIRX_DEV_ID_PHY       2

#define HDMIRX_ADDR_PORT        0x80034400  // TOP ADDR_PORT: 0xc800e000; DWC ADDR_PORT: 0xc800e010
#define HDMIRX_DATA_PORT        0x80034404  // TOP DATA_PORT: 0xc800e004; DWC DATA_PORT: 0xc800e014
#define HDMIRX_CTRL_PORT        0x80034408  // TOP CTRL_PORT: 0xc800e008; DWC CTRL_PORT: 0xc800e018

#define INT_HDMIRX_BASE_OFFSET  0x00000000  // INT TOP ADDR_PORT: 0xc800e000; INT DWC ADDR_PORT: 0xc800e010
#define EXT_HDMIRX_BASE_OFFSET  0x00000020  // EXT TOP ADDR_PORT: 0xc800e020; EXT DWC ADDR_PORT: 0xc800e030

#define ENABLE_CEC_FUNCTION


#define HDMI_COLOR_DEPTH_24B            4
#define HDMI_COLOR_DEPTH_30B            5
#define HDMI_COLOR_DEPTH_36B            6
#define HDMI_COLOR_DEPTH_48B            7

#define HDMI_COLOR_FORMAT_RGB           0
#define HDMI_COLOR_FORMAT_422           1
#define HDMI_COLOR_FORMAT_444           2
#define HDMI_COLOR_FORMAT_420           3

#define HDMI_COLOR_RANGE_LIM            0
#define HDMI_COLOR_RANGE_FUL            1

#define HDMI_AUDIO_PACKET_SMP           0x02
#define HDMI_AUDIO_PACKET_1BT           0x07
#define HDMI_AUDIO_PACKET_DST           0x08
#define HDMI_AUDIO_PACKET_HBR           0x09

// Use the following functions to access the HDMIRX modules (TOP, DWC or PHY) by default
//extern void             hdmirx_wr_only_reg  (unsigned char dev_id, unsigned long addr, unsigned long data);
//extern unsigned long    hdmirx_rd_reg       (unsigned char dev_id, unsigned long addr);
//extern void             hdmirx_rd_check_reg (unsigned char dev_id, unsigned long addr, unsigned long exp_data, unsigned long mask);
//extern void             hdmirx_wr_reg       (unsigned char dev_id, unsigned long addr, unsigned long data);
//extern void             hdmirx_poll_reg     (unsigned char dev_id, unsigned long addr, unsigned long exp_data, unsigned long mask);
extern void 			hdmirx_init(void);
extern void 			hdmirx_sig_monitor(void);
extern void 			hdmirx_cec_monitor(void);
extern void 			hdmi_rx_get_cec_cmd(void);
extern void				hdmirx_register_channel(void);
// HDMIRX repeater configuration
//extern void             hdmirx_repeater_config (unsigned long bstatus, unsigned short *ksv);

//extern void             aocec_poll_reg_busy (unsigned char reg_busy);
extern void             aocec_wr_only_reg (unsigned long addr, unsigned long data);
extern unsigned long    aocec_rd_reg (unsigned long addr, unsigned int check_busy_high);
extern void             aocec_rd_check_reg (unsigned long addr, unsigned long exp_data, unsigned long mask, unsigned int check_busy_high);
extern void             aocec_wr_reg (unsigned long addr, unsigned long data);
extern void             aocec_wr_reg_fast (unsigned long addr, unsigned long data);
extern void				hdmirx_set_DPLL(void);
extern void 			hdmirx_reset_DPLL(void);
extern void 			HDMIRX_IRQ_Handle(void *arg);
extern void 			hdmirx_config(void);
extern void 			hdmirx_phy_init(void);
// Internal functions:
void            hdmirx_wr_only_top  (unsigned long addr, unsigned long data);
void            hdmirx_wr_only_dwc  (unsigned long addr, unsigned long data);
//void            hdmirx_wr_only_phy  (unsigned long addr, unsigned long data);
unsigned long   hdmirx_rd_top       (unsigned long addr);
unsigned long   hdmirx_rd_dwc       (unsigned long addr);
//unsigned long   hdmirx_rd_phy       (unsigned long addr);
//void            hdmirx_rd_check_top (unsigned long addr, unsigned long exp_data, unsigned long mask);
void            hdmirx_rd_check_dwc (unsigned long addr, unsigned long exp_data, unsigned long mask);
//void            hdmirx_rd_check_phy (unsigned long addr, unsigned long exp_data, unsigned long mask);
void            hdmirx_wr_top       (unsigned long addr, unsigned long data);
void            hdmirx_wr_dwc       (unsigned long addr, unsigned long data);
//void            hdmirx_wr_phy       (unsigned long addr, unsigned long data);
//void            hdmirx_poll_top     (unsigned long addr, unsigned long exp_data, unsigned long mask);
//void            hdmirx_poll_dwc     (unsigned long addr, unsigned long exp_data, unsigned long mask, unsigned long max_try);
//void            hdmirx_poll_phy     (unsigned long addr, unsigned long exp_data, unsigned long mask);
void            hdmirx_key_setting  (   unsigned char           encrypt_en);

int 			hdmi_rx_phy_pll_lock(void);
int 			hdmi_rx_audio_pll_lock(void);
int 			hdmirx_get_clock(int index);
int 			hdmirx_get_tmds_clock(void);
void 			hdmirx_phy_init(void);
void 			hdmirx_audio_control(char enable);



//------------------------------------------------------------------------------
// Defines for simulation
//------------------------------------------------------------------------------

#endif /* HDMIRX_H */

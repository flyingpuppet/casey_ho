#ifndef _VBYONE_H_
#define _VBYONE_H_

#define VBO_VIN_YUV_GBR 0
#define VBO_VIN_YVU_GRB 1
#define VBO_VIN_UYV_BGR 2
#define VBO_VIN_UVY_BRG 3
#define VBO_VIN_VYU_RGB 4
#define VBO_VIN_VUY_RBG 5

#define VBO_VIN_30BPP   0
#define VBO_VIN_24BPP   1
#define VBO_VIN_18BPP   2

//VBO_SOFT_RST
   #define  VBO_SOFT_RST_BIT      0
   #define  VBO_SOFT_RST_WID      9

//VBO_CTRL
    #define VBO_ENABLE_BIT  0
    #define VBO_EBABLE_WID  1

    #define VBO_ALN_SHIFT_BIT     1
    #define VBO_ALN_SHIFT_WID     1

    #define VBO_LFSR_BYPASS_BIT   2
    #define VBO_LFSR_BYPASS_WID   1

    #define VBO_VDE_EXTEND_BIT    3
    #define VBO_VDE_EXTEND_WID    1

    #define VBO_HSYNC_SYNC_MODE_BIT   4
    #define VBO_HSYNC_SYNC_MODE_WID   2

    #define VBO_VSYNC_SYNC_MODE_BIT   6
    #define VBO_VSYNC_SYNC_MODE_WID   2

    #define VBO_FSM_CTRL_BIT      8
    #define VBO_FSM_CTRL_WID      3

    #define VBO_CTL_MODE_BIT      11
    #define VBO_CTL_MODE_WID      5

    #define VBO_CTL_MODE2_BIT     16
    #define VBO_CTL_MODE2_WID     4

    #define VBO_B8B10_CTRL_BIT    20
    #define VBO_B8B10_CTRL_WID    3

    #define VBO_VIN2ENC_TMSYNC_MODE_BIT  24
    #define VBO_VIN2ENC_TMSYNC_MODE_WID   1

    #define VBO_VIN2ENC_HVSYNC_DLY_BIT  25
    #define VBO_VIN2ENC_HVSYNC_DLY_WID  1

    #define VBO_POWER_ON_BIT  28
    #define VBO_POWER_ON_WID  1

    #define VBO_PLL_LOCK_BIT  29
    #define VBO_PLL_LOCK_WID  1

//VBO_VIN_CTRL
   #define  VBO_VIN_SYNC_CTRL_BIT 0
   #define  VBO_VIN_SYNC_CTRL_WID 2

   #define  VBO_VIN_HSYNC_POL_BIT 4
   #define  VBO_VIN_HSYNC_POL_WID 1

   #define  VBO_VIN_VSYNC_POL_BIT 5
   #define  VBO_VIN_VSYNC_POL_WID 1

   #define  VBO_VOUT_HSYNC_POL_BIT 6
   #define  VBO_VOUT_HSYNC_POL_WID 1

   #define  VBO_VOUT_VSYNC_POL_BIT 7
   #define  VBO_VOUT_VSYNC_POL_WID 1

   #define  VBO_VIN_PACK_BIT      8
   #define  VBO_VIN_PACK_WID      3

   #define  VBO_VIN_BPP_BIT      11
   #define  VBO_VIN_BPP_WID       2

   #define  VBO_ACT_VSIZE_BIT    16
   #define  VBO_ACT_VSIZE_WID    12

//VBO_LANES
   #define  VBO_LANE_NUM_BIT      0
   #define  VBO_LANE_NUM_WID      3

   #define  VBO_LANE_REGION_BIT   4
   #define  VBO_LANE_REGION_WID   2

   #define  VBO_SUBLANE_NUM_BIT   8
   #define  VBO_SUBLANE_NUM_WID   3

   #define  VBO_BYTE_MODE_BIT     11
   #define  VBO_BYTE_MODE_WID     2

//VBO_REGION01
    #define  VBO_REGION_0_BIT     0
    #define  VBO_REGION_0_WID    12
    #define  VBO_REGION_1_BIT    16
    #define  VBO_REGION_1_WID    12

//VBO_REGION23
    #define  VBO_REGION_2_BIT     0
    #define  VBO_REGION_2_WID    12
    #define  VBO_REGION_3_BIT    16
    #define  VBO_REGION_3_WID    12

//VBO_VBK_CTL
    #define  VBO_VBLANK_CTL0_BIT     0
    #define  VBO_VBLANK_CTL0_WID    16
    #define  VBO_VBLANK_CTL1_BIT    16
    #define  VBO_VBLANK_CTL1_WID    16

//VBO_HBK_PXL_CTL
    #define  VBO_HBLANK_CTL_BIT     0
    #define  VBO_HBLANK_CTL_WID    16
    #define  VBO_PXL_CTL0_BIT      16
    #define  VBO_PXL_CTL0_WID       4
    #define  VBO_PXL_CTL1_BIT      20
    #define  VBO_PXL_CTL1_WID       4

//VBO_LANE_SKEW
//VBO_LANE_SWAP
    #define VBO_LANE_SWAP_BIT       0
    #define VBO_LANE_SWAP_WID      11
    #define VBO_LANE_REV10_BIT     16
    #define VBO_LANE_REV10_WID      8


//VBO_RO_STATUS

extern int config_vbyone(int lane_num, int byte_num, int region_num, int hsize, int vsize, int enable);
extern void set_vbyone_vfmt   (int vin_color, int vin_bpp);
extern void set_vbyone_ctlbits(int p3d_en, int p3d_lr, int mode);
extern void set_vbyone_sync_pol(int hsync_pol, int vsync_pol);
extern int set_vbyone_lanes(int lane_num, int byte_num, int region_num, int hsize);

extern void set_VX1_output(int lane_num, int byte_num, int region_num, int color_fmt, int hsize, int vsize);
extern void vbyone_softreset(void);
#endif


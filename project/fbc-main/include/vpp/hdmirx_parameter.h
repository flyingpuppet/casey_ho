#ifndef HDMIRX_PARAMETER_DEFINE_H
#define HDMIRX_PARAMETER_DEFINE_H

//------------------------------------------------------------------------------
// TOP-level wrapper registers addresses
//------------------------------------------------------------------------------

#define HDMIRX_TOP_SW_RESET                     0x000
#define HDMIRX_TOP_CLK_CNTL                     0x001
#define HDMIRX_TOP_HPD_PWR5V                    0x002
#define HDMIRX_TOP_PORT_SEL                     0x003   // Not used.
#define HDMIRX_TOP_EDID_GEN_CNTL                0x004
#define HDMIRX_TOP_EDID_ADDR_CEC                0x005
#define HDMIRX_TOP_EDID_DATA_CEC_PORT01         0x006
#define HDMIRX_TOP_EDID_DATA_CEC_PORT23         0x007
#define HDMIRX_TOP_EDID_GEN_STAT_A              0x008
#define HDMIRX_TOP_INTR_MASKN                   0x009
#define HDMIRX_TOP_INTR_STAT                    0x00A
#define HDMIRX_TOP_INTR_STAT_CLR                0x00B
#define HDMIRX_TOP_VID_CNTL                     0x00C
#define HDMIRX_TOP_VID_STAT                     0x00D
#define HDMIRX_TOP_ACR_CNTL_STAT                0x00E
#define HDMIRX_TOP_ACR_AUDFIFO                  0x00F
#define HDMIRX_TOP_ARCTX_CNTL                   0x010   // Not used.
#define HDMIRX_TOP_METER_HDMI_CNTL              0x011
#define HDMIRX_TOP_METER_HDMI_STAT              0x012
#define HDMIRX_TOP_VID_CNTL2                    0x013
#define HDMIRX_TOP_MEM_PD                       0x014
#define HDMIRX_TOP_EDID_RAM_OVR0                0x015
#define HDMIRX_TOP_EDID_RAM_OVR0_DATA           0x016
#define HDMIRX_TOP_EDID_RAM_OVR1                0x017
#define HDMIRX_TOP_EDID_RAM_OVR1_DATA           0x018
#define HDMIRX_TOP_EDID_RAM_OVR2                0x019
#define HDMIRX_TOP_EDID_RAM_OVR2_DATA           0x01a
#define HDMIRX_TOP_EDID_RAM_OVR3                0x01b
#define HDMIRX_TOP_EDID_RAM_OVR3_DATA           0x01c
#define HDMIRX_TOP_EDID_RAM_OVR4                0x01d
#define HDMIRX_TOP_EDID_RAM_OVR4_DATA           0x01e
#define HDMIRX_TOP_EDID_RAM_OVR5                0x01f
#define HDMIRX_TOP_EDID_RAM_OVR5_DATA           0x020
#define HDMIRX_TOP_EDID_RAM_OVR6                0x021
#define HDMIRX_TOP_EDID_RAM_OVR6_DATA           0x022
#define HDMIRX_TOP_EDID_RAM_OVR7                0x023
#define HDMIRX_TOP_EDID_RAM_OVR7_DATA           0x024
#define HDMIRX_TOP_EDID_GEN_STAT_B              0x025
#define HDMIRX_TOP_EDID_GEN_STAT_C              0x026
#define HDMIRX_TOP_EDID_GEN_STAT_D              0x027
#define HDMIRX_TOP_CHAN_SWITCH_0                0x028
#define HDMIRX_TOP_TMDS_ALIGN_CNTL0             0x029
#define HDMIRX_TOP_TMDS_ALIGN_CNTL1             0x02a
#define HDMIRX_TOP_TMDS_ALIGN_STAT              0x02b
#define HDMIRX_TOP_VID_STABLE                   0x02c
#define HDMIRX_TOP_H_ACTIVE_TOTAL               0x02d
#define HDMIRX_TOP_H_BLANK_FRONT                0x02e
#define HDMIRX_TOP_H_SYNC_BACK                  0x02f
#define HDMIRX_TOP_V_ACTIVE_TOTAL               0x030
#define HDMIRX_TOP_V_BLANK_EOF                  0x031
#define HDMIRX_TOP_V_SYNC_SOF                   0x032
#define HDMIRX_TOP_PRBS_GEN                     0x033
#define HDMIRX_TOP_PRBS_ANA_0                   0x034
#define HDMIRX_TOP_PRBS_ANA_1                   0x035
#define HDMIRX_TOP_PRBS_ANA_STAT                0x036
#define HDMIRX_TOP_PRBS_ANA_BER_CH0             0x037
#define HDMIRX_TOP_PRBS_ANA_BER_CH1             0x038
#define HDMIRX_TOP_PRBS_ANA_BER_CH2             0x039
#define HDMIRX_TOP_METER_CABLE_CNTL             0x03a
#define HDMIRX_TOP_METER_CABLE_STAT             0x03b
#define HDMIRX_TOP_CHAN_SWITCH_1                0x03c
#define HDMIRX_TOP_PHY_CTRL_0                   0x03d
#define HDMIRX_TOP_PHY_CTRL_1                   0x03e
#define HDMIRX_TOP_PHY_CTRL_2                   0x03f
#define HDMIRX_TOP_PHY_CTRL_3                   0x040
#define HDMIRX_TOP_PHY_CTRL_4                   0x041
#define HDMIRX_TOP_PHY_CTRL_5                   0x042
#define HDMIRX_TOP_PHY_CTRL_6                   0x043
#define HDMIRX_TOP_PHY_CTRL_7                   0x044
#define HDMIRX_TOP_PHY_CTRL_8                   0x045
#define HDMIRX_TOP_PHY_CTRL_9                   0x046
#define HDMIRX_TOP_PHY_STAT_0                   0x047
#define HDMIRX_TOP_PHY_STAT_1                   0x048
#define HDMIRX_TOP_PHY_STAT_2                   0x049
#define HDMIRX_TOP_PHY_STAT_3                   0x04a
#define HDMIRX_TOP_AUDPLL_CTRL                  0x04b
#define HDMIRX_TOP_AUDPLL_CTRL_2                0x04c
#define HDMIRX_TOP_AUDPLL_CTRL_3                0x04d
#define HDMIRX_TOP_AUDPLL_CTRL_4                0x04e
#define HDMIRX_TOP_AUDPLL_CTRL_5                0x04f
#define HDMIRX_TOP_AUDPLL_CTRL_6                0x050
#define HDMIRX_TOP_DPLL_CTRL                    0x051
#define HDMIRX_TOP_DPLL_CTRL_2                  0x052
#define HDMIRX_TOP_DPLL_CTRL_3                  0x053
#define HDMIRX_TOP_DPLL_CTRL_4                  0x054
#define HDMIRX_TOP_DPLL_CTRL_5                  0x055
#define HDMIRX_TOP_DPLL_CTRL_6                  0x056

#define HDMIRX_TOP_AUDPLL_LOCK_FILTER           0x060

#define HDMIRX_TOP_CHAN01_ERRCNT                0x061
#define HDMIRX_TOP_CHAN2_ERRCNT                 0x062

#define HDMIRX_TOP_DONT_TOUCH0                  0x0fe   // Do not write to this register, it is a place holder to testbench to feed back onto APB.
#define HDMIRX_TOP_DONT_TOUCH1                  0x0ff   // Do not write to this register, it is a place holder to testbench to feed back onto APB.

#define HDMIRX_TOP_EDID_OFFSET                  0x200

//------------------------------------------------------------------------------
// DWC_HDMI_RX Controller registers addresses
//------------------------------------------------------------------------------

// HDMI registers
#define HDMIRX_DWC_HDMI_SETUP_CTRL              0x0000
#define HDMIRX_DWC_HDMI_OVR_CTRL                0x0004
#define HDMIRX_DWC_HDMI_TIMER_CTRL              0x0008
#define HDMIRX_DWC_HDMI_RES_OVR                 0x0010
#define HDMIRX_DWC_HDMI_RES_STS                 0x0014
#define HDMIRX_DWC_HDMI_PLL_CTRL                0x0018
#define HDMIRX_DWC_HDMI_PLL_FRQSET1             0x001C
#define HDMIRX_DWC_HDMI_PLL_FRQSET2             0x0020
#define HDMIRX_DWC_HDMI_PLL_PAR1                0x0024
#define HDMIRX_DWC_HDMI_PLL_PAR2                0x0028
#define HDMIRX_DWC_HDMI_PLL_PAR3                0x002C
#define HDMIRX_DWC_HDMI_PLL_LCK_STS             0x0030
#define HDMIRX_DWC_HDMI_CLK_CTRL                0x0034
#define HDMIRX_DWC_HDMI_PCB_CTRL                0x0038
#define HDMIRX_DWC_HDMI_PHS_CTRL                0x0040
#define HDMIRX_DWC_HDMI_PHS_USED                0x0044
#define HDMIRX_DWC_HDMI_MISC_CTRL               0x0048
#define HDMIRX_DWC_HDMI_EQOFF_CTRL              0x004C
#define HDMIRX_DWC_HDMI_EQGAIN_CTRL             0x0050
#define HDMIRX_DWC_HDMI_EQCAL_STS               0x0054
#define HDMIRX_DWC_HDMI_EQRESULT                0x0058
#define HDMIRX_DWC_HDMI_EQ_MEAS_CTRL            0x005C
#define HDMIRX_DWC_HDMI_MODE_RECOVER            0x0080
#define HDMIRX_DWC_HDMI_ERROR_PROTECT           0x0084
#define HDMIRX_DWC_HDMI_ERD_STS                 0x0088
#define HDMIRX_DWC_HDMI_SYNC_CTRL               0x0090
#define HDMIRX_DWC_HDMI_CKM_EVLTM               0x0094
#define HDMIRX_DWC_HDMI_CKM_F                   0x0098
#define HDMIRX_DWC_HDMI_CKM_RESULT              0x009C
#define HDMIRX_DWC_HDMI_RESMPL_CTRL             0x00A4
#define HDMIRX_DWC_HDMI_DCM_CTRL                0x00A8
#define HDMIRX_DWC_HDMI_VM_CFG_CH_0_1           0x00B0
#define HDMIRX_DWC_HDMI_VM_CFG_CH2              0x00B4
#define HDMIRX_DWC_HDMI_SPARE                   0x00B8
#define HDMIRX_DWC_HDMI_STS                     0x00BC

// HDCP registers

#define HDMIRX_DWC_HDCP_CTRL                    0x00C0
#define HDMIRX_DWC_HDCP_SETTINGS                0x00C4
#define HDMIRX_DWC_HDCP_SEED                    0x00C8
#define HDMIRX_DWC_HDCP_BKSV1                   0x00CC
#define HDMIRX_DWC_HDCP_BKSV0                   0x00D0
#define HDMIRX_DWC_HDCP_KIDX                    0x00D4
#define HDMIRX_DWC_HDCP_KEY1                    0x00D8
#define HDMIRX_DWC_HDCP_KEY0                    0x00DC
#define HDMIRX_DWC_HDCP_DBG                     0x00E0
#define HDMIRX_DWC_HDCP_AKSV1                   0x00E4
#define HDMIRX_DWC_HDCP_AKSV0                   0x00E8
#define HDMIRX_DWC_HDCP_AN1                     0x00EC
#define HDMIRX_DWC_HDCP_AN0                     0x00F0
#define HDMIRX_DWC_HDCP_EESS_WOO                0x00F4
#define HDMIRX_DWC_HDCP_I2C_TIMEOUT             0x00F8
#define HDMIRX_DWC_HDCP_STS                     0x00FC

#define HDMIRX_DWC_HDCP_RPT_CTRL                0x0600
#define HDMIRX_DWC_HDCP_RPT_BSTATUS             0x0604
#define HDMIRX_DWC_HDCP_RPT_KSVFIFO_CTRL        0x0608
#define HDMIRX_DWC_HDCP_RPT_KSVFIFO1            0x060C
#define HDMIRX_DWC_HDCP_RPT_KSVFIFO0            0x0610

// Video mode registers
#define HDMIRX_DWC_MD_HCTRL1                    0x0140
#define HDMIRX_DWC_MD_HCTRL2                    0x0144
#define HDMIRX_DWC_MD_HT0                       0x0148
#define HDMIRX_DWC_MD_HT1                       0x014C
#define HDMIRX_DWC_MD_HACT_PX                   0x0150
#define HDMIRX_DWC_MD_HACT_RSV                  0x0154
#define HDMIRX_DWC_MD_VCTRL                     0x0158
#define HDMIRX_DWC_MD_VSC                       0x015C
#define HDMIRX_DWC_MD_VTC                       0x0160
#define HDMIRX_DWC_MD_VOL                       0x0164
#define HDMIRX_DWC_MD_VAL                       0x0168
#define HDMIRX_DWC_MD_VTH                       0x016C
#define HDMIRX_DWC_MD_VTL                       0x0170
#define HDMIRX_DWC_MD_IL_CTRL                   0x0174
#define HDMIRX_DWC_MD_IL_SKEW                   0x0178
#define HDMIRX_DWC_MD_IL_POL                    0x017C
#define HDMIRX_DWC_MD_STS                       0x0180

// Audio registers
#define HDMIRX_DWC_AUD_CTRL                     0x0200
#define HDMIRX_DWC_AUD_PLL_CTRL                 0x0208
#define HDMIRX_DWC_AUD_PLL_LOCK                 0x020C
#define HDMIRX_DWC_AUD_PLL_RESET                0x0210
#define HDMIRX_DWC_AUD_CLK_CTRL                 0x0214
#define HDMIRX_DWC_AUD_CLK_MASP                 0x0218
#define HDMIRX_DWC_AUD_CLK_MAUD                 0x021C
#define HDMIRX_DWC_AUD_FILT_CTRL1               0x0220
#define HDMIRX_DWC_AUD_FILT_CTRL2               0x0224
#define HDMIRX_DWC_AUD_CTS_MAN                  0x0228
#define HDMIRX_DWC_AUD_N_MAN                    0x022C
#define HDMIRX_DWC_AUD_CLK_STS                  0x023C
#define AFIF_INIT								1 //0x240
#define HDMIRX_DWC_AUD_FIFO_CTRL                0x0240
#define HDMIRX_DWC_AUD_FIFO_TH                  0x0244
#define HDMIRX_DWC_AUD_FIFO_FILL_S              0x0248
#define HDMIRX_DWC_AUD_FIFO_CLR_MM              0x024C
#define HDMIRX_DWC_AUD_FIFO_FILLSTS             0x0250
#define HDMIRX_DWC_AUD_CHEXTR_CTRL              0x0254
#define HDMIRX_DWC_AUD_MUTE_CTRL                0x0258
#define HDMIRX_DWC_AUD_FIFO_FILLSTS1            0x025C
#define HDMIRX_DWC_AUD_SAO_CTRL                 0x0260
#define HDMIRX_DWC_AUD_PAO_CTRL                 0x0264
#define HDMIRX_DWC_AUD_SPARE                    0x0268
#define HDMIRX_DWC_AUD_FIFO_STS                 0x027C

// Audio PLL registers
#define HDMIRX_DWC_AUDPLL_GEN_CTS               0x0280
#define HDMIRX_DWC_AUDPLL_GEN_N                 0x0284
#define HDMIRX_DWC_AUDPLL_GEN_CTRL_RW1          0x0288
#define HDMIRX_DWC_AUDPLL_GEN_CTRL_RW2          0x028C
#define HDMIRX_DWC_AUDPLL_GEN_CTRL_W1           0x0298
#define HDMIRX_DWC_AUDPLL_GEN_STS_RO1           0x02A0
#define HDMIRX_DWC_AUDPLL_GEN_STS_RO2           0x02A4
#define HDMIRX_DWC_AUDPLL_SC_NDIVCTSTH          0x02A8
#define HDMIRX_DWC_AUDPLL_SC_CTS                0x02AC
#define HDMIRX_DWC_AUDPLL_SC_N                  0x02B0
#define HDMIRX_DWC_AUDPLL_SC_CTRL               0x02B4
#define HDMIRX_DWC_AUDPLL_SC_STS1               0x02B8
#define HDMIRX_DWC_AUDPLL_SC_STS2               0x02BC

// Synopsys PHY I2C Registers
#define HDMIRX_DWC_SNPS_PHYG3_CTRL              0x02C0
#define HDMIRX_DWC_I2CM_PHYG3_SLAVE             0x02C4
#define HDMIRX_DWC_I2CM_PHYG3_ADDRESS           0x02C8
#define HDMIRX_DWC_I2CM_PHYG3_DATAO             0x02CC
#define HDMIRX_DWC_I2CM_PHYG3_DATAI             0x02D0
#define HDMIRX_DWC_I2CM_PHYG3_OPERATION         0x02D4
#define HDMIRX_DWC_I2CM_PHYG3_MODE              0x02D8
#define HDMIRX_DWC_I2CM_PHYG3_SOFTRST           0x02DC
#define HDMIRX_DWC_I2CM_PHYG3_SS_CNTS           0x02E0
#define HDMIRX_DWC_I2CM_PHYG3_FS_HCNT           0x02E4

// Packet decoder and FIFO control registers
#define HDMIRX_DWC_PDEC_CTRL                    0x0300
#define HDMIRX_DWC_PDEC_FIFO_CFG                0x0304
#define HDMIRX_DWC_PDEC_FIFO_STS                0x0308
#define HDMIRX_DWC_PDEC_FIFO_DATA               0x030C
#define HDMIRX_DWC_PDEC_DBG_CTRL                0x0310
#define HDMIRX_DWC_PDEC_DBG_CTS                 0x0318
#define HDMIRX_DWC_PDEC_DBG_ACP                 0x031C
#define HDMIRX_DWC_PDEC_DBG_ERR_CORR            0x0320
#define HDMIRX_DWC_PDEC_FIFO_STS1               0x0324
#define HDMIRX_DWC_PDEC_ACRM_CTRL               0x0330
#define HDMIRX_DWC_PDEC_ACRM_MAX                0x0334
#define HDMIRX_DWC_PDEC_ACRM_MIN                0x0338
#define HDMIRX_DWC_PDEC_ERR_FILTER              0x033C
#define HDMIRX_DWC_PDEC_ASP_CTRL                0x0340
#define HDMIRX_DWC_PDEC_ASP_ERR                 0x0344
#define HDMIRX_DWC_PDEC_STS                     0x0360
#define HDMIRX_DWC_PDEC_AUD_STS                 0x0364
#define HDMIRX_DWC_PDEC_VSI_PAYLOAD0            0x0368
#define HDMIRX_DWC_PDEC_VSI_PAYLOAD1            0x036C
#define HDMIRX_DWC_PDEC_VSI_PAYLOAD2            0x0370
#define HDMIRX_DWC_PDEC_VSI_PAYLOAD3            0x0374
#define HDMIRX_DWC_PDEC_VSI_PAYLOAD4            0x0378
#define HDMIRX_DWC_PDEC_VSI_PAYLOAD5            0x037C
#define HDMIRX_DWC_PDEC_GCP_AVMUTE              0x0380
#define HDMIRX_DWC_PDEC_ACR_CTS                 0x0390
#define HDMIRX_DWC_PDEC_ACR_N                   0x0394
#define HDMIRX_DWC_PDEC_AVI_HB                  0x03A0
#define HDMIRX_DWC_PDEC_AVI_PB                  0x03A4
#define HDMIRX_DWC_PDEC_AVI_TBB                 0x03A8
#define HDMIRX_DWC_PDEC_AVI_LRB                 0x03AC
#define HDMIRX_DWC_PDEC_AIF_CTRL                0x03C0
#define HDMIRX_DWC_PDEC_AIF_HB                  0x03C4
#define HDMIRX_DWC_PDEC_AIF_PB0                 0x03C8
#define HDMIRX_DWC_PDEC_AIF_PB1                 0x03CC
#define HDMIRX_DWC_PDEC_GMD_HB                  0x03D0
#define HDMIRX_DWC_PDEC_GMD_PB                  0x03D4
#define HDMIRX_DWC_PDEC_VSI_ST0                 0x03E0
#define HDMIRX_DWC_PDEC_VSI_ST1                 0x03E4
#define HDMIRX_DWC_PDEC_VSI_PB0                 0x03E8
#define HDMIRX_DWC_PDEC_VSI_PB1                 0x03EC
#define HDMIRX_DWC_PDEC_VSI_PB2                 0x03F0
#define HDMIRX_DWC_PDEC_VSI_PB3                 0x03F4
#define HDMIRX_DWC_PDEC_VSI_PB4                 0x03F8
#define HDMIRX_DWC_PDEC_VSI_PB5                 0x03FC

// CEA Video Mode registers
#define HDMIRX_DWC_CEAVID_CONFIG                0x0400
#define HDMIRX_DWC_CEAVID_3DCONFIG              0x0404
#define HDMIRX_DWC_CEAVID_HCONFIG_LO            0x0408
#define HDMIRX_DWC_CEAVID_HCONFIG_HI            0x040C
#define HDMIRX_DWC_CEAVID_VCONFIG_LO            0x0410
#define HDMIRX_DWC_CEAVID_VCONFIG_HI            0x0414
#define HDMIRX_DWC_CEAVID_STATUS                0x0418

// HDMI 2.0 feature registers
#define HDMIRX_DWC_HDMI20_CONTROL               0x0800
#define HDMIRX_DWC_SCDC_I2CCONFIG               0x0804
#define HDMIRX_DWC_SCDC_CONFIG                  0x0808
#define HDMIRX_DWC_CHLOCK_CONFIG                0x080C
#define HDMIRX_DWC_SCDC_REGS0                   0x0820
#define HDMIRX_DWC_SCDC_REGS1                   0x0824
#define HDMIRX_DWC_SCDC_REGS2                   0x0828
#define HDMIRX_DWC_SCDC_REGS3                   0x082C
#define HDMIRX_DWC_SCDC_MANSPEC0                0x0840
#define HDMIRX_DWC_SCDC_MANSPEC1                0x0844
#define HDMIRX_DWC_SCDC_MANSPEC2                0x0848
#define HDMIRX_DWC_SCDC_MANSPEC3                0x084C
#define HDMIRX_DWC_SCDC_MANSPEC4                0x0850
#define HDMIRX_DWC_SCDC_WRDATA0                 0x0860
#define HDMIRX_DWC_SCDC_WRDATA1                 0x0864
#define HDMIRX_DWC_SCDC_WRDATA2                 0x0868
#define HDMIRX_DWC_SCDC_WRDATA3                 0x086C
#define HDMIRX_DWC_SCDC_WRDATA4                 0x0870
#define HDMIRX_DWC_SCDC_WRDATA5                 0x0874
#define HDMIRX_DWC_SCDC_WRDATA6                 0x0878
#define HDMIRX_DWC_SCDC_WRDATA7                 0x087C
#define HDMIRX_DWC_HDMI20_STATUS                0x08E0

// Packet decoder interrupt registers
#define HDMIRX_DWC_PDEC_IEN_CLR                 0x0F78
#define HDMIRX_DWC_PDEC_IEN_SET                 0x0F7C
#define HDMIRX_DWC_PDEC_ISTS                    0x0F80
#define HDMIRX_DWC_PDEC_IEN                     0x0F84
#define HDMIRX_DWC_PDEC_ICLR                    0x0F88
#define HDMIRX_DWC_PDEC_ISET                    0x0F8C

// Audio and CEC interrupt registers
#define HDMIRX_DWC_AUD_CEC_IEN_CLR              0x0F90
#define HDMIRX_DWC_AUD_CEC_IEN_SET              0x0F94
#define HDMIRX_DWC_AUD_CEC_ISTS                 0x0F98
#define HDMIRX_DWC_AUD_CEC_IEN                  0x0F9C
#define HDMIRX_DWC_AUD_CEC_ICLR                 0x0FA0
#define HDMIRX_DWC_AUD_CEC_ISET                 0x0FA4

// Audio FIFO interrupt registers
#define HDMIRX_DWC_AUD_FIFO_IEN_CLR             0x0FA8
#define HDMIRX_DWC_AUD_FIFO_IEN_SET             0x0FAC
#define HDMIRX_DWC_AUD_FIFO_ISTS                0x0FB0
#define HDMIRX_DWC_AUD_FIFO_IEN                 0x0FB4
#define HDMIRX_DWC_AUD_FIFO_ICLR                0x0FB8
#define HDMIRX_DWC_AUD_FIFO_ISET                0x0FBC

// Video mode interrupt registers
#define HDMIRX_DWC_MD_IEN_CLR                   0x0FC0
#define HDMIRX_DWC_MD_IEN_SET                   0x0FC4
#define HDMIRX_DWC_MD_ISTS                      0x0FC8
#define HDMIRX_DWC_MD_IEN                       0x0FCC
#define HDMIRX_DWC_MD_ICLR                      0x0FD0
#define HDMIRX_DWC_MD_ISET                      0x0FD4

// HDMI interrupt registers

#define HDMIRX_DWC_HDMI_IEN_CLR                 0x0FD8
#define HDMIRX_DWC_HDMI_IEN_SET                 0x0FDC
#define HDMIRX_DWC_HDMI_ISTS                    0x0FE0
#define HDMIRX_DWC_HDMI_IEN                     0x0FE4
#define HDMIRX_DWC_HDMI_ICLR                    0x0FE8
#define HDMIRX_DWC_HDMI_ISET                    0x0FEC

#define HDMIRX_DWC_HDMI2_IEN_CLR                0x0F60
#define HDMIRX_DWC_HDMI2_IEN_SET                0x0F64
#define HDMIRX_DWC_HDMI2_ISTS                   0x0F68
#define HDMIRX_DWC_HDMI2_IEN                    0x0F6C
#define HDMIRX_DWC_HDMI2_ICLR                   0x0F70
#define HDMIRX_DWC_HDMI2_ISET                   0x0F74

// DMI registers
#define IAUDIOCLK_DOMAIN_RESET					(1<<4) //0xff0
#define HDMIRX_DWC_DMI_SW_RST                   0x0FF0
#define HDMIRX_DWC_DMI_DISABLE_IF               0x0FF4
#define HDMIRX_DWC_DMI_MODULE_ID_EXT            0x0FF8
#define HDMIRX_DWC_DMI_MODULE_ID                0x0FFC

// CEC Controller registers addresses
#define  HDMIRX_DWC_CEC_CTRL                    0x1F00
#define  HDMIRX_DWC_CEC_MASK                    0x1F08
#define  HDMIRX_DWC_CEC_ADDR_L                  0x1F14
#define  HDMIRX_DWC_CEC_ADDR_H                  0x1F18
#define  HDMIRX_DWC_CEC_TX_CNT                  0x1F1C
#define  HDMIRX_DWC_CEC_RX_CNT                  0x1F20
#define  HDMIRX_DWC_CEC_TX_DATA0                0x1F40
#define  HDMIRX_DWC_CEC_TX_DATA1                0x1F44
#define  HDMIRX_DWC_CEC_TX_DATA2                0x1F48
#define  HDMIRX_DWC_CEC_TX_DATA3                0x1F4C
#define  HDMIRX_DWC_CEC_TX_DATA4                0x1F50
#define  HDMIRX_DWC_CEC_TX_DATA5                0x1F54
#define  HDMIRX_DWC_CEC_TX_DATA6                0x1F58
#define  HDMIRX_DWC_CEC_TX_DATA7                0x1F5C
#define  HDMIRX_DWC_CEC_TX_DATA8                0x1F60
#define  HDMIRX_DWC_CEC_TX_DATA9                0x1F64
#define  HDMIRX_DWC_CEC_TX_DATA10               0x1F68
#define  HDMIRX_DWC_CEC_TX_DATA11               0x1F6C
#define  HDMIRX_DWC_CEC_TX_DATA12               0x1F70
#define  HDMIRX_DWC_CEC_TX_DATA13               0x1F74
#define  HDMIRX_DWC_CEC_TX_DATA14               0x1F78
#define  HDMIRX_DWC_CEC_TX_DATA15               0x1F7C
#define  HDMIRX_DWC_CEC_RX_DATA0                0x1F80
#define  HDMIRX_DWC_CEC_RX_DATA1                0x1F84
#define  HDMIRX_DWC_CEC_RX_DATA2                0x1F88
#define  HDMIRX_DWC_CEC_RX_DATA3                0x1F8C
#define  HDMIRX_DWC_CEC_RX_DATA4                0x1F90
#define  HDMIRX_DWC_CEC_RX_DATA5                0x1F94
#define  HDMIRX_DWC_CEC_RX_DATA6                0x1F98
#define  HDMIRX_DWC_CEC_RX_DATA7                0x1F9C
#define  HDMIRX_DWC_CEC_RX_DATA8                0x1FA0
#define  HDMIRX_DWC_CEC_RX_DATA9                0x1FA4
#define  HDMIRX_DWC_CEC_RX_DATA10               0x1FA8
#define  HDMIRX_DWC_CEC_RX_DATA11               0x1FAC
#define  HDMIRX_DWC_CEC_RX_DATA12               0x1FB0
#define  HDMIRX_DWC_CEC_RX_DATA13               0x1FB4
#define  HDMIRX_DWC_CEC_RX_DATA14               0x1FB8
#define  HDMIRX_DWC_CEC_RX_DATA15               0x1FBC
#define  HDMIRX_DWC_CEC_LOCK                    0x1FC0
#define  HDMIRX_DWC_CEC_WKUPCTRL                0x1FC4


//HDMI PHY REG
#define HDMIRX_PHY_HRX_COMMON_CTL0							0x03D
#define HDMIRX_PHY_HRX_COMMON_CTL1							0x03E
#define HDMIRX_PHY_HRX_COMMON_CTL2							0x03F
#define HDMIRX_PHY_HRX_COMMON_CTL3							0x040
#define HDMIRX_PHY_HRX_MPLL_CTL0							0x041//bit [15:0]
#define HDMIRX_PHY_HRX_MPLL_CTL1							0x041//bit [31:16]
#define HDMIRX_PHY_HRX_MPLL_CTL2							0x042//bit [15:0]
#define HDMIRX_PHY_HRX_MPLL_CTL3							0x042//bit [31:16]
#define HDMIRX_PHY_TMDSCH0_CTL0								0x043//bit [15:0]
//#define HDMIRX_PHY_HDMIRX_TMDSCH0_CTL1					0x043//bit [31:16]
#define HDMIRX_PHY_TMDSCH1_CTL0								0x044//bit [15:0]
//#define HDMIRX_PHY_HDMIRX_TMDSCH1_CTL1					0x044//bit [31:16]
#define HDMIRX_PHY_TMDSCH2_CTL0								0x045//bit [15:0]
//#define HDMIRX_PHY_HDMIRX_TMDSCH2_CTL1					0x045//bit [31:16]
#define HDMIRX_PHY_TMDSCLK_CTL0								0x046//bit [15:0]
//#define HDMIRX_PHY_HDMIRX_TMDSCLK_CTL1					0x046//bit [31:16]
//HDMI PHY STATUS
//COMMON_STATUS bit[15:0]	bit0: resitor calibration indication bit
//MPLL_STATUS0 bit[31:16]
#define HDMIRX_PHY_STATUS0									0x047
//MPLL_STATUS1 bit[15:0]
//TMDSCH0_STAUTS bit[31:16]
#define HDMIRX_PHY_STATUS1									0x048
//TMDSCH1_STAUTS bit[15:0]
//TMDSCH2_STAUTS bit[31:16]
#define HDMIRX_PHY_STATUS2									0x049
//TMDSCLK_STAUTS bit[15:0]
#define HDMIRX_PHY_STATUS3									0x04a

#define HDMIRX_PHY_AUD_PLL_CTL								0x04b
#define HDMIRX_PHY_AUD_PLL_CTL2								0x04c
#define	HDMIRX_PHY_AUD_PLL_CTL3  							0x04d
#define	HDMIRX_PHY_AUD_PLL_CTL4								0x04e
#define	HDMIRX_PHY_AUD_PLL_CTL5								0x04f
//bit[31:16] AUD_DPLL_DDS_REVE
//bit(11+16) = 1:TMDS_DIV_CLK   =0:TMDS_REQUEST_CLOCK
//bit(15+16) = 1:input clk		=0:crystal clock
#define	HDMIRX_PHY_AUD_PLL_CTL6								0x050

//bit[28:24]	N
//bit[8:0]		M
#define HDMIRX_PHY_DPLL_CTL									0x051
#define HDMIRX_PHY_DPLL_CTL2								0x052
#define HDMIRX_PHY_DPLL_CTL3								0x053
#define HDMIRX_PHY_DPLL_CTL4								0x054
#define HDMIRX_PHY_DPLL_CTL5								0x055
#define HDMIRX_PHY_DPLL_CTL6								0x056


//// H13RCTRL registers default values
//#define DEFAULT_RX_HDMI_SETUP_CTRL      {6'd0, 1'b1, 1'b1, 6'd0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 6'd24, 1'b0, 1'b0, 4'd0, 1'b0}
//#define DEFAULT_RX_HDMI_OVR_CTRL        {1'b0, 3'd0, 2'd0, 1'b0, 3'd0, 1'b0, 1'b0, 3'd0, 1'b0, 2'd0, 3'd0, 3'd0, 7'd0, 1'b0}
//#define DEFAULT_RX_HDMI_TIMER_CTRL      {21'd0, 1'b0, 10'd632}
//#define DEFAULT_RX_HDMI_RES_OVR         {4'd0, 4'd5, 1'b0, 7'd0, 1'b0, 6'd0, 1'b0, 1'b0, 1'b0, 6'd0}
//#define DEFAULT_RX_HDMI_RES_STS         {1'b0, 7'd0, 1'b0, 6'd0, 1'b0, 8'd0, 8'd0}
//#define DEFAULT_RX_HDMI_PLL_CTRL        {8'd0, 8'd0, 4'd0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b1, 2'd2, 1'b1, 1'b0, 2'd0, 1'b0}
//#define DEFAULT_RX_HDMI_PLL_FRQSET1     {8'd114, 8'd82, 8'd49, 8'd33}
//#define DEFAULT_RX_HDMI_PLL_FRQSET2     {1'b0, 3'd4, 4'd0, 8'd212, 8'd179, 8'd147}
//#define DEFAULT_RX_HDMI_PLL_PAR1        {4'd12, 4'd6, 4'd15, 4'd5, 4'd15, 4'd8, 4'd9, 4'd4}
//#define DEFAULT_RX_HDMI_PLL_PAR2        {4'd7, 4'd8, 4'd8, 4'd7, 4'd9, 4'd6, 4'd10, 4'd6}
//#define DEFAULT_RX_HDMI_PLL_PAR3        {1'b0, 3'd7, 1'b1, 3'd6, 1'b1, 3'd4, 1'b1, 3'd3, 1'b1, 3'd2, 1'b1, 3'd1, 1'b1, 3'd1, 1'b1, 3'd0}
//#define DEFAULT_RX_HDMI_PLL_LCK_STS     {18'd0, 4'd0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0}
//#define DEFAULT_RX_HDMI_CLK_CTRL        {11'd0, 5'd0, 2'd0, 5'd0, 3'd2, 3'd2, 2'd0, 1'b0}
//#define DEFAULT_RX_HDMI_PCB_CTRL        {6'd0, 1'b0, 1'b0, 4'd0, 2'd0, 1'b0, 1'b0, 3'd0, 1'b0, 1'b0, 3'd0, 3'd0, 1'b0, 1'b0, 3'd0}
//#define DEFAULT_RX_HDMI_PHS_CTRL        {3'd0, 3'd0, 3'd0, 1'b0, 6'd42, 2'd0, 2'd1, 1'b0, 1'b0, 1'b1, 1'b1, 3'd0, 1'b1, 2'd0, 2'd2}
//#define DEFAULT_RX_HDMI_PHS_USED        {5'd0, 1'b0, 1'b0, 1'b0, 2'd0, 6'd0, 2'd0, 6'd0, 2'd0, 6'd0}
//#define DEFAULT_RX_HDMI_MISC_CTRL       {2'd0, 3'd0, 2'd0, 1'b0, 7'd0, 1'b0, 4'd0, 1'b0, 1'b0, 1'b0, 1'b1, 7'd0, 1'b0}
//#define DEFAULT_RX_HDMI_EQOFF_CTRL      {13'd0, 3'd0, 2'd0, 1'b0, 4'd0, 4'd0, 4'd0, 1'b0}
//#define DEFAULT_RX_HDMI_EQGAIN_CTRL     {8'd0, 1'b0, 3'd4, 3'd4, 3'd4, 1'b0, 1'b0, 1'b0, 2'd1, 2'd2, 1'b0, 1'b0, 1'b0, 3'd4, 1'b0}
//#define DEFAULT_RX_HDMI_EQCAL_STS       {2'd0, 4'd0, 4'd0, 4'd0, 1'b0, 1'b0, 1'b0, 3'd0, 3'd0, 3'd0, 3'd0, 1'b0, 1'b0, 1'b0}
//#define DEFAULT_RX_HDMI_EQRESULT        {9'd0, 12'd0, 11'd0}
//#define DEFAULT_RX_HDMI_EQ_MEAS_CTRL    {12'd0, 1'b0, 1'b0, 1'b0, 1'b0, 16'd0}
//#define DEFAULT_RX_HDMI_MODE_RECOVER    {6'd0, 2'd0, 5'd0, 1'b0, 5'd8, 5'd8, 2'd0, 2'd0, 2'd0, 2'd0}
//#define DEFAULT_RX_HDMI_ERROR_PROTECT   {11'd0, 1'b0, 1'b0, 3'd0, 2'd0, 2'd0, 2'd0, 2'd0, 2'd0, 1'b0, 2'd0, 3'd0}
//#define DEFAULT_RX_HDMI_ERD_STS         {29'd0, 3'd0}
//#define DEFAULT_RX_HDMI_SYNC_CTRL       {27'd0, 2'd0, 2'd0, 1'b0}
//#define DEFAULT_RX_HDMI_CKM_EVLTM       {10'd0, 2'd1, 1'b0, 3'd0, 12'd4095, 3'd0, 1'b0}
//#define DEFAULT_RX_HDMI_CKM_F           {16'd63882, 16'd9009}
//#define DEFAULT_RX_HDMI_CKM_RESULT      {14'd0, 1'b0, 1'b0, 16'd0}
//#define DEFAULT_RX_HDMI_RESMPL_CTRL     {27'd0, 4'd0, 1'b1}
//#define DEFAULT_RX_HDMI_DCM_CTRL        {3'd0, 1'b0, 8'd0, 2'd0, 1'b0, 4'd0, 1'b0, 4'd4, 2'd0, 4'd5, 2'd0}
//#define DEFAULT_RX_HDMI_VM_CFG_CH_0_1   {16'd0, 16'd0}
//#define DEFAULT_RX_HDMI_VM_CFG_CH2      {15'd0,  1'b0, 16'd0}
//#define DEFAULT_RX_HDMI_SPARE           32'd0
//#define DEFAULT_RX_HDMI_STS             {4'd0, 4'd0, 8'd0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 7'd0}
//#define DEFAULT_RX_HDCP_CTRL            {17'd0, 1'b0, 1'b0, 1'b0, 2'd0, 2'd0, 2'd0, 3'd0, 1'b0, 1'b0, 1'b0}
//#define DEFAULT_RX_HDCP_SETTINGS        {13'd0, 2'd1, 1'b1, 3'd0, 1'b1, 2'd0, 1'b1, 1'b1, 7'd58, 1'b0}
//#define DEFAULT_RX_HDCP_SEED            {16'd0, 16'd0}
//#define DEFAULT_RX_HDCP_BKSV1           {24'd0, 8'd0}
//#define DEFAULT_RX_HDCP_BKSV0           32'd0
//#define DEFAULT_RX_HDCP_KIDX            {26'd0, 6'd0}
//#define DEFAULT_RX_HDCP_KEY1            {8'd0, 24'd0}
//#define DEFAULT_RX_HDCP_KEY0            32'd0
//#define DEFAULT_RX_HDCP_DBG             {8'd0, 1'b0, 1'b0, 6'd0, 16'd0}
//#define DEFAULT_RX_HDCP_AKSV1           {24'd0, 8'd0}
//#define DEFAULT_RX_HDCP_AKSV0           32'd0
//#define DEFAULT_RX_HDCP_AN1             32'd0
//#define DEFAULT_RX_HDCP_AN0             32'd0
//#define DEFAULT_RX_HDCP_EESS_WOO        {6'd0, 10'd534, 6'd0, 10'd511}
//#define DEFAULT_RX_HDCP_I2C_TIMEOUT     32'd0
//#define DEFAULT_RX_HDCP_STS             {31'd0, 1'b1}
//#define DEFAULT_RX_MD_HCTRL1            {21'd0, 3'd1, 2'd0, 1'b0, 1'b1, 4'd0}
//#define DEFAULT_RX_MD_HCTRL2            {17'd0, 3'd2, 1'b0, 3'd1, 2'd0, 1'b0, 2'd0, 1'b0, 2'd2}
//#define DEFAULT_RX_MD_HT0               {16'd0, 7'd0, 9'd0}
//#define DEFAULT_RX_MD_HT1               {4'd0, 12'd0, 4'd0, 12'd0}
//#define DEFAULT_RX_MD_HACT_PX           {20'd0, 12'd0}
//#define DEFAULT_RX_MD_HACT_RSV          {20'd0, 12'd0}
//#define DEFAULT_RX_MD_VCTRL             {27'd0, 1'b0, 2'd0, 1'b1, 1'b0}
//#define DEFAULT_RX_MD_VSC               {16'd0, 16'd0}
//#define DEFAULT_RX_MD_VTC               {10'd0, 22'd0}
//#define DEFAULT_RX_MD_VOL               {21'd0, 11'd0}
//#define DEFAULT_RX_MD_VAL               {21'd0, 11'd0}
//#define DEFAULT_RX_MD_VTH               {20'd0, 2'd2, 2'd0, 2'd0, 3'd2, 3'd2}

#endif /* HDMIRX_PARAMETER_DEFINE_H */

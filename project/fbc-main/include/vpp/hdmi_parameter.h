#ifndef HDMI_PARAMETER_H
#define HDMI_PARAMETER_H
#include <vpp.h>
//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------
#ifdef IN_FBC_MAIN_CONFIG
//------------------------------------------------------------------------------
// Interrupt Mask
//------------------------------------------------------------------------------

//#define HDMIRX_DWC_PDEC_IEN_BIT29_aud_type_chg      (1<<29) // 0xf7c bit[29]
///#define HDMIRX_DWC_PDEC_IEN_BIT28_dviDet            (1<<28) // 0xf7c bit[28]
//#define HDMIRX_DWC_PDEC_IEN_BIT27_vsiCksChg         (1<<27) // 0xf7c bit[27]
//#define HDMIRX_DWC_PDEC_IEN_BIT26_gmdCksChg         (1<<26) // 0xf7c bit[26]
//#define HDMIRX_DWC_PDEC_IEN_BIT25_aifCksChg         (1<<25) // 0xf7c bit[25]
//#define HDMIRX_DWC_PDEC_IEN_BIT24_aviCksChg         (1<<24) // 0xf7c bit[24]
//#define HDMIRX_DWC_PDEC_IEN_BIT23_acrNChg           (1<<23) // 0xf7c bit[23]
//#define HDMIRX_DWC_PDEC_IEN_BIT22_acrCtsChg         (1<<22) // 0xf7c bit[22]
#define HDMIRX_DWC_PDEC_IEN_BIT21_gcpAvmuteChg      (1<<21) // 0xf7c bit[21]
///#define HDMIRX_DWC_PDEC_IEN_BIT20_gmdRcv            (1<<20) // 0xf7c bit[20]
///#define HDMIRX_DWC_PDEC_IEN_BIT19_aifRcv            (1<<19) // 0xf7c bit[19]
///#define HDMIRX_DWC_PDEC_IEN_BIT18_aviRcv            (1<<18) // 0xf7c bit[18]
//#define HDMIRX_DWC_PDEC_IEN_BIT17_acrRcv            (1<<17) // 0xf7c bit[17]
///#define HDMIRX_DWC_PDEC_IEN_BIT16_gcpRcv            (1<<16) // 0xf7c bit[16]
///#define HDMIRX_DWC_PDEC_IEN_BIT15_vsiRcv            (1<<15) // 0xf7c bit[15]
///#define HDMIRX_DWC_PDEC_IEN_BIT08_pdFifoNewEntry    (1<<8)  // 0xf7c bit[08]
///#define HDMIRX_DWC_PDEC_IEN_BIT04_pdFifoOverfl      (1<<4)  // 0xf7c bit[04]
///#define HDMIRX_DWC_PDEC_IEN_BIT03_pdFifoUnderfl     (1<<3)  // 0xf7c bit[03]
//#define HDMIRX_DWC_PDEC_IEN_BIT02_pdFifoThStartPass (1<<2)  // 0xf7c bit[02]
///#define HDMIRX_DWC_PDEC_IEN_BIT01_pdFifoThMaxPass   (1<<1)  // 0xf7c bit[01]
///#define HDMIRX_DWC_PDEC_IEN_BIT00_pdFifoThMinPass   (1<<0)  // 0xf7c bit[00]

//#define HDMIRX_DWC_AUD_CEC_IEN_BIT22_wakeupctrl     (1<<22) // 0xf94 bit[22]
//#define HDMIRX_DWC_AUD_CEC_IEN_BIT21_errorFoll      (1<<21) // 0xf94 bit[21]
//#define HDMIRX_DWC_AUD_CEC_IEN_BIT20_errorInit      (1<<20) // 0xf94 bit[20]
//#define HDMIRX_DWC_AUD_CEC_IEN_BIT19_arblst         (1<<19) // 0xf94 bit[19]
//#define HDMIRX_DWC_AUD_CEC_IEN_BIT18_nack           (1<<18) // 0xf94 bit[18]
#define HDMIRX_DWC_AUD_CEC_IEN_BIT17_eom            (1<<17) // 0xf94 bit[17]
#define HDMIRX_DWC_AUD_CEC_IEN_BIT16_done           (1<<16) // 0xf94 bit[16]
///#define HDMIRX_DWC_AUD_CEC_IEN_BIT01_sckStable      (1<<1)  // 0xf94 bit[01]
///#define HDMIRX_DWC_AUD_CEC_IEN_BIT00_ctsnCnt        (1<<0)  // 0xf94 bit[00]

#define HDMIRX_DWC_AUD_FIFO_IEN_BIT04_afifOverfl    (1<<4) // 0xfac bit[04]
#define HDMIRX_DWC_AUD_FIFO_IEN_BIT03_afifUnderfl   (1<<3) // 0xfac bit[03]
//#define HDMIRX_DWC_AUD_FIFO_IEN_BIT02_afifThsPass   (1<<2) // 0xfac bit[02]
//#define HDMIRX_DWC_AUD_FIFO_IEN_BIT01_afifThMax     (1<<1) // 0xfac bit[01]
//#define HDMIRX_DWC_AUD_FIFO_IEN_BIT00_afifThMin     (1<<0) // 0xfac bit[00]

//#define HDMIRX_DWC_MD_IEN_BIT11_vofsLin             (1<<11) // 0xfc4 bit[11]
//#define HDMIRX_DWC_MD_IEN_BIT10_vtotLin             (1<<10) // 0xfc4 bit[10]
//#define HDMIRX_DWC_MD_IEN_BIT09_vactLin             (1<<9)  // 0xfc4 bit[09]
//#define HDMIRX_DWC_MD_IEN_BIT08_vsClk               (1<<8)  // 0xfc4 bit[08]
//#define HDMIRX_DWC_MD_IEN_BIT07_vtotClk             (1<<7)  // 0xfc4 bit[07]
//#define HDMIRX_DWC_MD_IEN_BIT06_hactPix             (1<<6)  // 0xfc4 bit[06]
//#define HDMIRX_DWC_MD_IEN_BIT05_hsClk               (1<<5)  // 0xfc4 bit[05]
//#define HDMIRX_DWC_MD_IEN_BIT04_htot32Clk           (1<<4)  // 0xfc4 bit[04]
///#define HDMIRX_DWC_MD_IEN_BIT03_ilace               (1<<3)  // 0xfc4 bit[03]
//#define HDMIRX_DWC_MD_IEN_BIT02_deActivity          (1<<2)  // 0xfc4 bit[02]
//#define HDMIRX_DWC_MD_IEN_BIT01_vsAct               (1<<1)  // 0xfc4 bit[01]
//#define HDMIRX_DWC_MD_IEN_BIT00_hsAct               (1<<0)  // 0xfc4 bit[00]

//#define HDMIRX_DWC_HDMI_IEN_BIT30_i2cmpArblost      (1<<30) // 0xfdc bit[30]
//#define HDMIRX_DWC_HDMI_IEN_BIT29_i2cmpnack         (1<<29) // 0xfdc bit[29]
//#define HDMIRX_DWC_HDMI_IEN_BIT28_i2cmpdone         (1<<28) // 0xfdc bit[28]
///#define HDMIRX_DWC_HDMI_IEN_BIT25_aksvRcv           (1<<25) // 0xfdc bit[25]
//#define HDMIRX_DWC_HDMI_IEN_BIT24_pllClockGated     (1<<24) // 0xfdc bit[24]
//#define HDMIRX_DWC_HDMI_IEN_BIT19_scdcTmdsCfgChg    (1<<19) // 0xfdc bit[19]
//#define HDMIRX_DWC_HDMI_IEN_BIT18_scdcscStatusChg   (1<<18) // 0xfdc bit[18]
//#define HDMIRX_DWC_HDMI_IEN_BIT17_scdcCfgChg        (1<<17) // 0xfdc bit[17]
//#define HDMIRX_DWC_HDMI_IEN_BIT16_dcmCurrentModeChg (1<<16) // 0xfdc bit[16]
//#define HDMIRX_DWC_HDMI_IEN_BIT15_dcmPhDiffCntOverfl    (1<<15) // 0xfdc bit[15]
//#define HDMIRX_DWC_HDMI_IEN_BIT14_dcmGcpZeroFieldsPass  (1<<14) // 0xfdc bit[14]
//#define HDMIRX_DWC_HDMI_IEN_BIT13_ctl3Change            (1<<13) // 0xfdc bit[13]
//#define HDMIRX_DWC_HDMI_IEN_BIT12_ctl2Change        (1<<12) // 0xfdc bit[12]
//#define HDMIRX_DWC_HDMI_IEN_BIT11_ctl1Change        (1<<11) // 0xfdc bit[11]
//#define HDMIRX_DWC_HDMI_IEN_BIT10_ctl0Change        (1<<10) // 0xfdc bit[10]
//#define HDMIRX_DWC_HDMI_IEN_BIT09_vsPolAdj          (1<<9)  // 0xfdc bit[09]
//#define HDMIRX_DWC_HDMI_IEN_BIT08_hsPolAdj          (1<<8)  // 0xfdc bit[08]
//#define HDMIRX_DWC_HDMI_IEN_BIT07_resOverload       (1<<7)  // 0xfdc bit[07]
//#define HDMIRX_DWC_HDMI_IEN_BIT06_clkChange         (1<<6)  // 0xfdc bit[06]
///#define HDMIRX_DWC_HDMI_IEN_BIT05_pllLckChg         (1<<5)  // 0xfdc bit[05]
//#define HDMIRX_DWC_HDMI_IEN_BIT04_eqgainDone        (1<<4)  // 0xfdc bit[04]
//#define HDMIRX_DWC_HDMI_IEN_BIT03_offscalDone       (1<<3)  // 0xfdc bit[03]
//#define HDMIRX_DWC_HDMI_IEN_BIT02_rescalDone        (1<<2)  // 0xfdc bit[02]
//#define HDMIRX_DWC_HDMI_IEN_BIT01_actChange         (1<<1)  // 0xfdc bit[01]
//#define HDMIRX_DWC_HDMI_IEN_BIT00_stateReached      (1<<0)  // 0xfdc bit[00]


//#define HDMIRX_TOP_IEN_BIT01_EDID_ADDR_INTR				(1<<1)
#define HDMIRX_TOP_IEN_BIT02_5V_RISE					(1<<2)
#define HDMIRX_TOP_IEN_BIT03_VID_BACKPORCH_STABLE		(1<<3)
#define HDMIRX_TOP_IEN_BIT04_VID_FRONTPORCH_STABLE		(1<<4)
#define HDMIRX_TOP_IEN_BIT05_HSYNC_PIXEL_STABLE			(1<<5)
#define HDMIRX_TOP_IEN_BIT06_5V_FALL					(1<<6)
#define HDMIRX_TOP_IEN_BIT07_VID_ACTIVE_PIXEL_STABLE	(1<<7)
#define HDMIRX_TOP_IEN_BIT08_VID_SOF_LINE_STABLE		(1<<8)
#define HDMIRX_TOP_IEN_BIT09_VID_EOF_LINE_STABLE		(1<<9)
#define HDMIRX_TOP_IEN_BIT10_VID_FMT_CHANGE				(1<<10)
#define HDMIRX_TOP_IEN_BIT11_VID_COLOR_DEPTH_CHANGE		(1<<11)
//#define HDMIRX_TOP_IEN_BIT12_METER_STABLE_CHG_HDMI		(1<<12)
//#define HDMIRX_TOP_IEN_BIT13_HDCP_AUTH_START_RISE		(1<<13)
//#define HDMIRX_TOP_IEN_BIT14_HDCP_AUTH_START_FALL		(1<<14)
//#define HDMIRX_TOP_IEN_BIT15_HDCP_ENC_STATE_RISE		(1<<15)
//#define HDMIRX_TOP_IEN_BIT16_HDCP_ENC_STATE_FALL		(1<<16)
#define HDMIRX_TOP_IEN_BIT17_VID_VSYNC_LINE_STABLE		(1<<17)
#define HDMIRX_TOP_IEN_BIT18_VID_ACTIVE_LINE_STABLE		(1<<18)
#define HDMIRX_TOP_IEN_BIT19_VID_BACKPORCH_UNSTABLE		(1<<19)
#define HDMIRX_TOP_IEN_BIT20_VID_FRONTPORCH_UNSTABLE	(1<<20)
#define HDMIRX_TOP_IEN_BIT21_HSYNC_PIXEL_UNSTABLE		(1<<21)
#define	HDMIRX_TOP_IEN_BIT22_VID_ACTIVE_PIXEL_UNSTABLE	(1<<22)
#define HDMIRX_TOP_IEN_BIT23_VID_SOF_LINE_UNSTABLE		(1<<23)
#define HDMIRX_TOP_IEN_BIT24_VID_EOF_LINE_UNSTABLE		(1<<24)
#define HDMIRX_TOP_IEN_BIT25_VID_VSYNC_LINE_UNSTABLE	(1<<25)
#define HDMIRX_TOP_IEN_BIT26_VID_ACTIVE_LINE_UNSTABLE	(1<<26)
//#define HDMIRX_TOP_IEN_BIT27_METER_STABLE_CHG_CABLE		(1<<27)

unsigned long dwc_pdec_ien_maskn    = ( 0
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT29_aud_type_chg
                                    | HDMIRX_DWC_PDEC_IEN_BIT29_aud_type_chg
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT28_dviDet
                                    | HDMIRX_DWC_PDEC_IEN_BIT28_dviDet
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT27_vsiCksChg
                                    | HDMIRX_DWC_PDEC_IEN_BIT27_vsiCksChg
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT26_gmdCksChg
                                    | HDMIRX_DWC_PDEC_IEN_BIT26_gmdCksChg
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT25_aifCksChg
                                    | HDMIRX_DWC_PDEC_IEN_BIT25_aifCksChg
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT24_aviCksChg
                                    | HDMIRX_DWC_PDEC_IEN_BIT24_aviCksChg
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT23_acrNChg
                                    | HDMIRX_DWC_PDEC_IEN_BIT23_acrNChg
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT22_acrCtsChg
                                    | HDMIRX_DWC_PDEC_IEN_BIT22_acrCtsChg
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT21_gcpAvmuteChg
                                    | HDMIRX_DWC_PDEC_IEN_BIT21_gcpAvmuteChg
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT20_gmdRcv
                                    | HDMIRX_DWC_PDEC_IEN_BIT20_gmdRcv
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT19_aifRcv
                                    | HDMIRX_DWC_PDEC_IEN_BIT19_aifRcv
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT18_aviRcv
                                    | HDMIRX_DWC_PDEC_IEN_BIT18_aviRcv
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT17_acrRcv
                                    | HDMIRX_DWC_PDEC_IEN_BIT17_acrRcv
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT16_gcpRcv
                                    | HDMIRX_DWC_PDEC_IEN_BIT16_gcpRcv
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT15_vsiRcv
                                    | HDMIRX_DWC_PDEC_IEN_BIT15_vsiRcv
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT08_pdFifoNewEntry
                                    | HDMIRX_DWC_PDEC_IEN_BIT08_pdFifoNewEntry
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT04_pdFifoOverfl
                                    | HDMIRX_DWC_PDEC_IEN_BIT04_pdFifoOverfl
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT03_pdFifoUnderfl
                                    | HDMIRX_DWC_PDEC_IEN_BIT03_pdFifoUnderfl
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT02_pdFifoThStartPass
                                    | HDMIRX_DWC_PDEC_IEN_BIT02_pdFifoThStartPass
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT01_pdFifoThMaxPass
                                    | HDMIRX_DWC_PDEC_IEN_BIT01_pdFifoThMaxPass
                                #endif
                                #ifdef HDMIRX_DWC_PDEC_IEN_BIT00_pdFifoThMinPass
                                    | HDMIRX_DWC_PDEC_IEN_BIT00_pdFifoThMinPass
                                #endif
                                    );

unsigned long dwc_aud_cec_ien_maskn = ( 0
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT22_wakeupctrl
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT22_wakeupctrl
                                #endif
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT21_errorFoll
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT21_errorFoll
                                #endif
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT20_errorInit
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT20_errorInit
                                #endif
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT19_arblst
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT19_arblst
                                #endif
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT18_nack
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT18_nack
                                #endif
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT17_eom
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT17_eom
                                #endif
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT16_done
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT16_done
                                #endif
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT01_sckStable
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT01_sckStable
                                #endif
                                #ifdef HDMIRX_DWC_AUD_CEC_IEN_BIT00_ctsnCnt
                                    | HDMIRX_DWC_AUD_CEC_IEN_BIT00_ctsnCnt
                                #endif
                                    );

unsigned long dwc_aud_fifo_ien_maskn= ( 0
                                #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT04_afifOverfl
                                    | HDMIRX_DWC_AUD_FIFO_IEN_BIT04_afifOverfl
                                #endif
                                #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT03_afifUnderfl
                                    | HDMIRX_DWC_AUD_FIFO_IEN_BIT03_afifUnderfl
                                #endif
                                #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT02_afifThsPass
                                    | HDMIRX_DWC_AUD_FIFO_IEN_BIT02_afifThsPass
                                #endif
                                #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT01_afifThMax
                                    | HDMIRX_DWC_AUD_FIFO_IEN_BIT01_afifThMax
                                #endif
                                #ifdef HDMIRX_DWC_AUD_FIFO_IEN_BIT00_afifThMin
                                    | HDMIRX_DWC_AUD_FIFO_IEN_BIT00_afifThMin
                                #endif
                                    );

unsigned long dwc_md_ien_maskn      = ( 0
                                #ifdef HDMIRX_DWC_MD_IEN_BIT11_vofsLin
                                    | HDMIRX_DWC_MD_IEN_BIT11_vofsLin
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT10_vtotLin
                                    | HDMIRX_DWC_MD_IEN_BIT10_vtotLin
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT09_vactLin
                                    | HDMIRX_DWC_MD_IEN_BIT09_vactLin
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT08_vsClk
                                    | HDMIRX_DWC_MD_IEN_BIT08_vsClk
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT07_vtotClk
                                    | HDMIRX_DWC_MD_IEN_BIT07_vtotClk
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT06_hactPix
                                    | HDMIRX_DWC_MD_IEN_BIT06_hactPix
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT05_hsClk
                                    | HDMIRX_DWC_MD_IEN_BIT05_hsClk
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT04_htot32Clk
                                    | HDMIRX_DWC_MD_IEN_BIT04_htot32Clk
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT03_ilace
                                    | HDMIRX_DWC_MD_IEN_BIT03_ilace
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT02_deActivity
                                    | HDMIRX_DWC_MD_IEN_BIT02_deActivity
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT01_vsAct
                                    | HDMIRX_DWC_MD_IEN_BIT01_vsAct
                                #endif
                                #ifdef HDMIRX_DWC_MD_IEN_BIT00_hsAct
                                    | HDMIRX_DWC_MD_IEN_BIT00_hsAct
                                #endif
                                    );

unsigned long dwc_hdmi_ien_maskn    = ( 0
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT30_i2cmpArblost
                                    | HDMIRX_DWC_HDMI_IEN_BIT30_i2cmpArblost
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT29_i2cmpnack
                                    | HDMIRX_DWC_HDMI_IEN_BIT29_i2cmpnack
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT28_i2cmpdone
                                    | HDMIRX_DWC_HDMI_IEN_BIT28_i2cmpdone
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT25_aksvRcv
                                    | HDMIRX_DWC_HDMI_IEN_BIT25_aksvRcv
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT24_pllClockGated
                                    | HDMIRX_DWC_HDMI_IEN_BIT24_pllClockGated
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT19_scdcTmdsCfgChg
                                    | HDMIRX_DWC_HDMI_IEN_BIT19_scdcTmdsCfgChg
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT18_scdcscStatusChg
                                    | HDMIRX_DWC_HDMI_IEN_BIT18_scdcscStatusChg
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT17_scdcCfgChg
                                    | HDMIRX_DWC_HDMI_IEN_BIT17_scdcCfgChg
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT16_dcmCurrentModeChg
                                    | HDMIRX_DWC_HDMI_IEN_BIT16_dcmCurrentModeChg
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT15_dcmPhDiffCntOverfl
                                    | HDMIRX_DWC_HDMI_IEN_BIT15_dcmPhDiffCntOverfl
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT14_dcmGcpZeroFieldsPass
                                    | HDMIRX_DWC_HDMI_IEN_BIT14_dcmGcpZeroFieldsPass
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT13_ctl3Change
                                    | HDMIRX_DWC_HDMI_IEN_BIT13_ctl3Change
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT12_ctl2Change
                                    | HDMIRX_DWC_HDMI_IEN_BIT12_ctl2Change
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT11_ctl1Change
                                    | HDMIRX_DWC_HDMI_IEN_BIT11_ctl1Change
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT10_ctl0Change
                                    | HDMIRX_DWC_HDMI_IEN_BIT10_ctl0Change
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT09_vsPolAdj
                                    | HDMIRX_DWC_HDMI_IEN_BIT09_vsPolAdj
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT08_hsPolAdj
                                    | HDMIRX_DWC_HDMI_IEN_BIT08_hsPolAdj
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT07_resOverload
                                    | HDMIRX_DWC_HDMI_IEN_BIT07_resOverload
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT06_clkChange
                                    | HDMIRX_DWC_HDMI_IEN_BIT06_clkChange
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT05_pllLckChg
                                    | HDMIRX_DWC_HDMI_IEN_BIT05_pllLckChg
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT04_eqgainDone
                                    | HDMIRX_DWC_HDMI_IEN_BIT04_eqgainDone
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT03_offscalDone
                                    | HDMIRX_DWC_HDMI_IEN_BIT03_offscalDone
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT02_rescalDone
                                    | HDMIRX_DWC_HDMI_IEN_BIT02_rescalDone
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT01_actChange
                                    | HDMIRX_DWC_HDMI_IEN_BIT01_actChange
                                #endif
                                #ifdef HDMIRX_DWC_HDMI_IEN_BIT00_stateReached
                                    | HDMIRX_DWC_HDMI_IEN_BIT00_stateReached
                                #endif
                                    );


unsigned long top_ien_maskn    = ( 1
								#ifdef HDMIRX_TOP_IEN_BIT27_METER_STABLE_CHG_CABLE
                                    | HDMIRX_TOP_IEN_BIT27_METER_STABLE_CHG_CABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT26_VID_ACTIVE_LINE_UNSTABLE
                                    | HDMIRX_TOP_IEN_BIT26_VID_ACTIVE_LINE_UNSTABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT25_VID_VSYNC_LINE_UNSTABLE
                                    | HDMIRX_TOP_IEN_BIT25_VID_VSYNC_LINE_UNSTABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT24_VID_EOF_LINE_UNSTABLE
                                    | HDMIRX_TOP_IEN_BIT24_VID_EOF_LINE_UNSTABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT23_VID_SOF_LINE_UNSTABLE
                                    | HDMIRX_TOP_IEN_BIT23_VID_SOF_LINE_UNSTABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT22_VID_ACTIVE_PIXEL_UNSTABLE
                                    | HDMIRX_TOP_IEN_BIT22_VID_ACTIVE_PIXEL_UNSTABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT21_HSYNC_PIXEL_UNSTABLE
                                    | HDMIRX_TOP_IEN_BIT21_HSYNC_PIXEL_UNSTABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT20_VID_FRONTPORCH_UNSTABLE
                                    | HDMIRX_TOP_IEN_BIT20_VID_FRONTPORCH_UNSTABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT19_VID_BACKPORCH_UNSTABLE
                                    | HDMIRX_TOP_IEN_BIT19_VID_BACKPORCH_UNSTABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT18_VID_ACTIVE_LINE_STABLE
                                    | HDMIRX_TOP_IEN_BIT18_VID_ACTIVE_LINE_STABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT17_VID_VSYNC_LINE_STABLE
                                    | HDMIRX_TOP_IEN_BIT17_VID_VSYNC_LINE_STABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT16_HDCP_ENC_STATE_FALL
                                    | HDMIRX_TOP_IEN_BIT16_HDCP_ENC_STATE_FALL
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT15_HDCP_ENC_STATE_RISE
                                    | HDMIRX_TOP_IEN_BIT15_HDCP_ENC_STATE_RISE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT14_HDCP_AUTH_START_FALL
                                    | HDMIRX_TOP_IEN_BIT14_HDCP_AUTH_START_FALL
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT13_HDCP_AUTH_START_RISE
                                    | HDMIRX_TOP_IEN_BIT13_HDCP_AUTH_START_RISE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT12_METER_STABLE_CHG_HDMI
                                    | HDMIRX_TOP_IEN_BIT12_METER_STABLE_CHG_HDMI
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT11_VID_COLOR_DEPTH_CHANGE
                                    | HDMIRX_TOP_IEN_BIT11_VID_COLOR_DEPTH_CHANGE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT10_VID_FMT_CHANGE
                                    | HDMIRX_TOP_IEN_BIT10_VID_FMT_CHANGE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT09_VID_EOF_LINE_STABLE
                                    | HDMIRX_TOP_IEN_BIT09_VID_EOF_LINE_STABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT08_VID_SOF_LINE_STABLE
                                    | HDMIRX_TOP_IEN_BIT08_VID_SOF_LINE_STABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT07_VID_ACTIVE_PIXEL_STABLE
                                    | HDMIRX_TOP_IEN_BIT07_VID_ACTIVE_PIXEL_STABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT06_5V_FALL
                                    | HDMIRX_TOP_IEN_BIT06_5V_FALL
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT05_HSYNC_PIXEL_STABLE
                                    | HDMIRX_TOP_IEN_BIT05_HSYNC_PIXEL_STABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT04_VID_FRONTPORCH_STABLE
                                    | HDMIRX_TOP_IEN_BIT04_VID_FRONTPORCH_STABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT03_VID_BACKPORCH_STABLE
                                    | HDMIRX_TOP_IEN_BIT03_VID_BACKPORCH_STABLE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT02_5V_RISE
                                    | HDMIRX_TOP_IEN_BIT02_5V_RISE
                                #endif
                                #ifdef HDMIRX_TOP_IEN_BIT01_EDID_ADDR_INTR
                                    | HDMIRX_TOP_IEN_BIT01_EDID_ADDR_INTR
                                #endif
                                    );

static const unsigned short SampleKSVList[]=
{
    0x35,0x79,0x6A,0x17,0x2E,//Bksv0
    0x47,0x8E,0x71,0xE2,0x0F,//Bksv1
    0x74,0xE8,0x53,0x97,0xA6,//Bksv2
    0x51,0x1E,0xF2,0x1A,0xCD,//BKSV3
    0xE7,0x26,0x97,0xf4,0x01,//BKSV4
};


#endif
#endif  /* HDMI_PARAMETER_H */

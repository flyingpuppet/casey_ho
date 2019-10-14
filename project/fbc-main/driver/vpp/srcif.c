#include <register.h>
#include <common.h>
#include <c_arc_pointer_reg.h>
#include <srcif.h>
#include <log.h>

static hybrid_st =0;
// Delay routine
void delay_us(int  us )
{
	sleep(us);
}

void srcif_fsm_init()
{

	int data32 = 0;
	Wr(SRCIF_WRAP_CTRL ,    0x00000024);
	Wr(SRCIF_WRAP_CTRL1,    0x00340000);
	Wr(SRCIF_WRAP_CTRL1,    0xc0340000);
	Wr(SRCIF_WRAP_CNT0 ,    0x00000010);
	Wr(SRCIF_WRAP_CNT1 ,    0x00000020);
	Wr(SRCIF_WRAP_CNT2 ,    0x00000030);
	Wr(SRCIF_WRAP_CNT3 ,    0x00000040);
	Wr(SRCIF_WRAP_CNT5 ,    0x00000050);
	Wr(SRCIF_WRAP_CNT6 ,    0x00000060);
	//Wr(SRCIF_WRAP_CTRL ,    0x03200020);
	Wr(SRCIF_WRAP_CTRL ,    0x00000024);

}
#ifdef IN_FBC_MAIN_CONFIG
void srcif_fsm_fc_stbl()
{
	Wr(SRCIF_WRAP_CTRL ,    (Rd(SRCIF_WRAP_CTRL) | 0xc00000));
}

void srcif_fsm_stbl_from_hdmi()
{
    Wr(SRCIF_WRAP_CTRL ,    (Rd(SRCIF_WRAP_CTRL) && 0xff3fffff));
}

void srcif_fsm_fc_unstbl()
{
	Wr(SRCIF_WRAP_CTRL ,    ((Rd(SRCIF_WRAP_CTRL) & 0xff3fffff)| 0x80800000));
}
#endif
void srcif_tmg_on(int mode)
{
  //mode == 0, 1080p,
  //mode == 1, 640x480p
  //mode == 2, 4k2k
  if (mode == 0) {
    Wr(VP_TMGEN_HTOTAL,0x464044b);
    Wr(VP_TMGEN_HAVON_H,0x43f0080);
    Wr(VP_TMGEN_VAVON_V,0x4570020);
    Wr(VP_TMGEN_HSO_H  ,0x0050000);
    Wr(VP_TMGEN_VSO_H  ,0x0050000);
  }
  else if (mode == 1) {
    Wr(VP_TMGEN_HTOTAL,0x20c01af);
    Wr(VP_TMGEN_HAVON_H,0x15f0020);
    Wr(VP_TMGEN_VAVON_V,0x1ef0010);
    Wr(VP_TMGEN_HSO_H  ,0x0050000);
    Wr(VP_TMGEN_VSO_H  ,0x0050000);
    Wr(VP_IMG_SIZE,0x1df027f);
  }
  else if (mode == 2) {
    Wr(VP_TMGEN_HTOTAL,0x8c90897);
    Wr(VP_TMGEN_HAVON_H,0x79f0020);
    Wr(VP_TMGEN_VAVON_V,0x87f0010);
    Wr(VP_TMGEN_HSO_H  ,0x0050000);
    Wr(VP_TMGEN_VSO_H  ,0x0050000);
    Wr(VP_IMG_SIZE,0x86f0eff);
  }
  else {
    Wr(VP_TMGEN_HTOTAL,0x464044b);
    Wr(VP_TMGEN_HAVON_H,0x43f0080);
    Wr(VP_TMGEN_VAVON_V,0x4570020);
    Wr(VP_TMGEN_HSO_H  ,0x0050000);
    Wr(VP_TMGEN_VSO_H  ,0x0050000);
  }

}

void srcif_fsm_on()
{
	int data32 = 0;
    data32 = Rd(SRCIF_WRAP_CTRL);
	Wr(SRCIF_WRAP_CTRL ,    (data32 | 0x80200000));
}

void srcif_fsm_off()
{
	int data32 = 0;
    data32 = Rd(SRCIF_WRAP_CTRL);
	Wr(SRCIF_WRAP_CTRL ,    (data32 & 0x7fdfffff));
}

void srcif_pure_sw_ptn()
{
	int data32 = 0;
	Wr(SRCIF_WRAP_CTRL ,    0x00000020);
	//step 1, rst fifo, vmux, gate vpu, force fifo_en, vmux_en, vmux_sel
	Wr(SRCIF_WRAP_CTRL ,    0x0802aaa0);
	delay_us(1);
	//step 2, clock mux to ptn
	Wr(SRCIF_WRAP_CTRL ,    0x0812aaa0);
	delay_us(1);
	//step 3, Need a wait pll lock here
	//step 4, release rst of vmux, en vpu_clk_en
	Wr(SRCIF_WRAP_CTRL ,    0x0c12aba0);
	delay_us(1);
	//step 5, enable ptn_en, vmux_en
	Wr(SRCIF_WRAP_CTRL ,    0x0c12bbe0);
	Wr(VP_CTRL ,    Rd(VP_CTRL) | 0x2);
	delay_us(1);
}


#ifdef IN_FBC_MAIN_CONFIG
void srcif_fsm_fc_ptn()
{
	Wr(SRCIF_WRAP_CTRL ,    (Rd(SRCIF_WRAP_CTRL) | 0x10000000));
}

void srcif_fsm_mute_stbl()
{
	Wr(SRCIF_WRAP_CTRL1,    (Rd(SRCIF_WRAP_CTRL1) | 0x400000));
}

void srcif_fsm_no_mute_stbl()
{
	Wr(SRCIF_WRAP_CTRL1,    (Rd(SRCIF_WRAP_CTRL1) & 0xffbfffff));
}

void srcif_fsm_clk_freerun()
{
	Wr(SRCIF_WRAP_CTRL,    (Rd(SRCIF_WRAP_CTRL) | 0x40000));
}

void srcif_pure_sw_hdmi()
{
	int data32 = 0;
	Wr(SRCIF_WRAP_CTRL ,    0x00000020);
	//step 1, rst fifo, vmux, gate vpu, force fifo_en, vmux_en, vmux_sel
	Wr(SRCIF_WRAP_CTRL ,    0x0802aea0);
	delay_us(1);
	//step 2, clock mux to ptn
	Wr(SRCIF_WRAP_CTRL ,    0x081aaea0);
	delay_us(1);
	//step 3, Need a wait pll lock here
	//step 4, release rst of vmux, en vpu_clk_en
	Wr(SRCIF_WRAP_CTRL ,    0x0c1bafa0);
	delay_us(1);
	//step 5, enable fifo_en, vmux_en
	Wr(SRCIF_WRAP_CTRL ,    0x0c1bffa0);
	delay_us(1);
}

void srcif_hybrid_fsm_init()
{
	int data32 = 0;
	Wr(SRCIF_WRAP_CTRL ,    0x80000024);
	Wr(SRCIF_WRAP_CTRL1,    0x03100003);
	Wr(SRCIF_WRAP_CTRL1,    0xc3100003);
	Wr(SRCIF_WRAP_CNT0 ,    0x00000010);
	Wr(SRCIF_WRAP_CNT1 ,    0x00000020);
	Wr(SRCIF_WRAP_CNT2 ,    0x00000030);
	Wr(SRCIF_WRAP_CNT3 ,    0x00000020);
	Wr(SRCIF_WRAP_CNT5 ,    0x00000010);
	Wr(SRCIF_WRAP_CNT6 ,    0x00000020);
	Wr(SRCIF_WRAP_CTRL ,    0x80200024);
}

void srcif_hybrid_fsm_ctrl()
{
	int data32 = 0;
	//check status register
	data32 = Rd(SRCIF_WRAP_STATUS);
	LOGD(TAG_VPP, "status = %x\n",data32);
	LOGD(TAG_VPP, "state = %x\n",data32 & 0x7);

	if ((data32 & 0x7) == 0x0) {
		LOGD(TAG_VPP, "state: st_idle\n");
	}
	else if ((data32 & 0x7) == 0x1) {
		delay_us(100);
		LOGD(TAG_VPP, "state: st_rst_all, goto st_clk_mux\n");
		Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) & 0xffffffdf);
		Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) | 0x20);
		Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) & 0xffffffdf);
	}
	else if ((data32 & 0x7) == 0x2) {
		LOGD(TAG_VPP, "state: st_mux_clk\n");
		data32 = Rd(SRCIF_WRAP_STATUS);
		while ((data32 & 0x400) != 0x400) {
			delay_us(1);
			data32 = Rd(SRCIF_WRAP_STATUS);
		}

		if ((data32 & 0x0800) == 0x0800) {
			LOGD(TAG_VPP, "state: st_mux_clk, stbl , goto st_hdmi\n");
			Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) & 0xffffff7f);
			Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) | 0x80);
			Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) & 0xffffff7f);
		}
		else {
			LOGD(TAG_VPP, "state: st_clk_mux, un stbl , goto st_ptn\n");
			Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) & 0xffffffbf);
			Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) | 0x40);
			Wr(SRCIF_WRAP_CTRL1,Rd(SRCIF_WRAP_CTRL1) & 0xffffffbf);
		}

	}
	else if ((data32 & 0x7) == 0x3) {
		LOGD(TAG_VPP, "state: st_hdmi\n");
	}
	else if ((data32 & 0x7) == 0x4) {
		LOGD(TAG_VPP, "state: st_ptn\n");
	}
}

void srcif_hybrid_fsm_goto_rst_all()
{
	int data32 = 0;
	LOGD(TAG_VPP, "hybrid fsm reset all\n");
	Wr(SRCIF_WRAP_CTRL1 ,    (Rd(SRCIF_WRAP_CTRL1) | 0x10));
	Wr(SRCIF_WRAP_CTRL1 ,    (Rd(SRCIF_WRAP_CTRL1) & 0xffffffef));
}



void set_srcif_hdmi2vpu (
    int adj_mode                    ,
    int hsize                       ,
    int line_blank_num              ,

    int reg_rx_drop_tim_ratio       , // u6
    int reg_lbuf_depth              , // u12
    int reg_loop0_fifo_lowlmt       , // u15
    int reg_loop0_fifo_target       , // u15
    int reg_loop0_fifo_higlmt       , // u15
    int reg_loop0_error_core0       , // u12
    int reg_loop0_error_core1       , // u12
    int reg_loop0_error_core_mode   , // u1
    int reg_loop0_error_lmt         , // u14
    int reg_loop0_error_gain_lmt    , // u8
    int reg_loop0_error_gain_raw    , // u8
    int reg_loop0_error_gain_fin    , // u8
    int reg_loop0_adj_pad_gain      , // u8
    int reg_loop0_adj_pad_rs        , // u3
    int reg_loop0_adj_pad_pxgrouprs , // u3
    int reg_verr_stbdet_win0          // u14
    )
{
	int data32 = 0;

    int reg_meas_cyc_mode    ; // 1 : keep cycle; 0 : keep time
    int reg_rx_loop0_drop_en ;
    int reg_tx_loop0_fill_en ;
    int reg_rx_drop_num      ; // HSYN_NUM+PREDE_NUM;
    int reg_rx_drop_line_len ; // HSYN_NUM+PREDE_NUM; // u15
    int reg_vblank_hsize_lmt ;

	LOGD(TAG_VPP, "=== set_srcif_hdmi_datapath ====\n");

    if ( adj_mode==0 ) {
        reg_meas_cyc_mode    = 1;
        reg_rx_loop0_drop_en = 1;
        reg_tx_loop0_fill_en = 1;
        reg_rx_drop_num      = line_blank_num;
        reg_rx_drop_line_len = line_blank_num;
    }
    else if (adj_mode==1) {
        reg_meas_cyc_mode    = 1;
        reg_rx_loop0_drop_en = 0;
        reg_tx_loop0_fill_en = 0;
        reg_rx_drop_num      = line_blank_num;
        reg_rx_drop_line_len = line_blank_num;
    }
    else {
        reg_meas_cyc_mode    = 0;
        reg_rx_loop0_drop_en = 0;
        reg_tx_loop0_fill_en = 0;
        reg_rx_drop_num      = line_blank_num;
        reg_rx_drop_line_len = line_blank_num;
    }

    reg_vblank_hsize_lmt     = hsize;

    // set control reg
    Wr_reg_bits(VPU_SRCIF_CTRL,reg_meas_cyc_mode,0,1);
    data32 = ((reg_rx_loop0_drop_en & 0x1)<<1) |
              (reg_tx_loop0_fill_en & 0x1);
    Wr_reg_bits(VPU_SRCIF_CTRL,data32,3,2);
    Wr_reg_bits(VPU_SRCIF_CTRL,reg_rx_drop_tim_ratio,8,6);

    data32 = ((reg_rx_drop_num      & 0xffff)<<16) |
              (reg_rx_drop_line_len & 0xffff);
    Wr(VPU_SRCIF_RX_DROP_NUM, data32);

    data32 = ((reg_vblank_hsize_lmt & 0xffff)<<16) |
              (reg_lbuf_depth       & 0xfff );
    Wr(VPU_SRCIF_LBUF_DEPTH, data32);



    data32 = ((reg_loop0_fifo_lowlmt & 0x7fff)<<16) |
              (reg_loop0_fifo_higlmt & 0x7fff);
    Wr(VPU_SRCIF_LOOP_FIFO_LMT, data32);

    data32 = ((reg_loop0_fifo_target & 0x7fff)<<16) |
              (reg_loop0_error_lmt   & 0x3fff);
    Wr(VPU_SRCIF_LOOP_FIFO_TARGET, data32);

    data32 = ((reg_loop0_error_core_mode & 0x1)<<28) |
             ((reg_loop0_error_core0 & 0xfff)<<16) |
              (reg_loop0_error_core1 & 0xfff);
    Wr(VPU_SRCIF_LOOP_ERR_CORE, data32);

    data32 = ((reg_loop0_error_gain_lmt & 0xff)<<16) |
             ((reg_loop0_error_gain_raw & 0xff)<<8 ) |
              (reg_loop0_error_gain_fin & 0xff);
    Wr(VPU_SRCIF_LOOP_ERR_GAIN, data32);

    data32 = ((reg_loop0_adj_pad_rs        & 0x7 )<<16) |
             ((reg_loop0_adj_pad_gain      & 0xff)<<8 ) |
             ((reg_loop0_adj_pad_pxgrouprs & 0x7 )<<4 ) |
              (0x2                         & 0x3 );
    Wr(VPU_SRCIF_LOOP_ADJ_PAD_CFG, data32);

    data32 = (reg_verr_stbdet_win0 & 0x3fff);
    Wr(VPU_SRCIF_VERR_STBDET_WIN, data32);

}

void set_srcif_hdmi2vpu_default (
    int adj_mode                    , // 0 : adaptive adj
                                      // 1 : pre-cut hblank pixel
                                      // 2 : keep time each line
    int hsize                       ,
    int line_blank_num              ,
    int reg_loop0_adj_pad_pxgrouprs , // u3
    int reg_verr_stbdet_win0          // u14
    )
{
    set_srcif_hdmi2vpu (
         adj_mode                    ,
         hsize                       ,
         line_blank_num              ,

         16  , // int reg_rx_drop_tim_ratio       , // u6
         1024, // int reg_lbuf_depth              , // u12
         500 , // int reg_loop0_fifo_lowlmt       , // u15
         4000, // int reg_loop0_fifo_target       , // u15
         7800, // int reg_loop0_fifo_higlmt       , // u15
         700 , // int reg_loop0_error_core0       , // u12
         700 , // int reg_loop0_error_core1       , // u12
         0   , // int reg_loop0_error_core_mode   , // u1
         1000, // int reg_loop0_error_lmt         , // u14
         32  , // int reg_loop0_error_gain_lmt    , // u8
         255 , // int reg_loop0_error_gain_raw    , // u8
         32  , // int reg_loop0_error_gain_fin    , // u8
         64  , // int reg_loop0_adj_pad_gain      , // u8
         4   , // int reg_loop0_adj_pad_rs        , // u3
         reg_loop0_adj_pad_pxgrouprs , // u3
         reg_verr_stbdet_win0          // u14
    );

}
#endif

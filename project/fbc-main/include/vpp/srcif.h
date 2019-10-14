#ifndef _SRCIF_FSM_H_
#define _SRCIF_FSM_H_

extern void srcif_fsm_init();
extern void srcif_pure_sw_ptn();
extern void delay_us(int  us );
extern void sleep(int us);
extern void srcif_pure_sw_hdmi();
extern void srcif_hybrid_fsm_init();
extern void srcif_hybrid_fsm_ctrl();
extern void srcif_hybrid_fsm_goto_rst_all();
extern void srcif_fsm_on();
extern void srcif_fsm_off();
extern void srcif_fsm_fc_stbl();
extern void srcif_fsm_fc_unstbl();
extern void srcif_tmg_on(int mode);
extern void srcif_fsm_stbl_from_hdmi();
extern void srcif_fsm_fc_ptn();
extern void srcif_fsm_mute_stbl();
extern void srcif_fsm_no_mute_stbl();
extern void srcif_fsm_clk_freerun();
#endif

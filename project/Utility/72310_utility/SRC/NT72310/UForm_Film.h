//---------------------------------------------------------------------------

#ifndef UForm_FilmH
#define UForm_FilmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include "RegCheckBox.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RegLabeledEdit.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_Film : public TMEMCForm
{
__published:	// IDE-managed Components
    TButton *btn_Refresh;
    TGroupBox *gb1;
    TRegCheckBox *rcb_film_a_en;
    TRegCheckBox *rcb_film_b_en;
    TRegCheckBox *rcb_film_c_en;
    TRegCheckBox *rcb_film_d_en;
    TRegCheckBox *rcb_film_e_en;
    TGroupBox *GroupBox1;
    TRegLabeledEdit *film_quit_th;
    TRegLabeledEdit *film_prd_th;
    TGroupBox *GroupBox2;
    TRegLabeledEdit *film_r_h0;
    TRegLabeledEdit *film_r_v0;
    TRegLabeledEdit *film_r_h1;
    TRegLabeledEdit *film_r_v1;
    TRegLabeledEdit *film_r_h0_c;
    TRegLabeledEdit *film_r_v0_c;
    TRegLabeledEdit *film_r_h1_c;
    TRegLabeledEdit *film_r_v1_c;
    TGroupBox *GroupBox3;
    TRegLabeledEdit *film_diff_th_c;
    TRegLabeledEdit *film_diff_c_lsb;
    TRegLabeledEdit *film_dyn_w1_c;
    TRegLabeledEdit *film_dyn_w2_c;
    TGroupBox *GroupBox4;
    TRegLabeledEdit *dyn_th_sel_22;
    TRegLabeledEdit *dyn_th_sel_32;
    TRegLabeledEdit *dyn_th_sel_3223;
    TRegLabeledEdit *dyn_th_sel_2224;
    TRegLabeledEdit *dyn_th_sel_32322;
    TRegLabeledEdit *dyn_th_sel_1123;
    TRegLabeledEdit *dyn_th_sel_55;
    TRegLabeledEdit *dyn_th_sel_6487;
    TGroupBox *GroupBox5;
    TRegLabeledEdit *film_cad_num_22;
    TRegLabeledEdit *film_cad_num_32;
    TRegLabeledEdit *film_cad_num_3223;
    TRegLabeledEdit *film_cad_num_2224;
    TRegLabeledEdit *film_cad_num_1123;
    TRegLabeledEdit *film_cad_num_55;
    TRegLabeledEdit *film_cad_num_64;
    TRegLabeledEdit *film_cad_num_87;
    TRegLabeledEdit *film_cad_num_32322;
    TGroupBox *GroupBox6;
    TRegLabeledEdit *film_quit_diff_th_a;
    TRegLabeledEdit *film_quit_diff_th_b;
    TRegLabeledEdit *film_quit_diff_th_c;
    TRegLabeledEdit *film_quit_diff_th_d;
    TRegLabeledEdit *film_quit_diff_th_e;
    TGroupBox *GroupBox7;
    TRegLabeledEdit *rb_glb_mot_a;
    TRegLabeledEdit *rb_glb_mot_b;
    TRegLabeledEdit *rb_glb_mot_c;
    TRegLabeledEdit *rb_glb_mot_d;
    TRegLabeledEdit *rb_glb_mot_e;
    TRegLabeledEdit *rb_glb_mot_r;
    TRegLabeledEdit *rb_glb_mot_all;
    TRegLabeledEdit *rb_glb_mot_all_film;
    TGroupBox *GroupBox8;
    TRegLabeledEdit *rb_y_hstgm_max;
    TRegLabeledEdit *rb_y_hstgm_max2;
    TRegLabeledEdit *rb_y_hstgm_min;
    TRegLabeledEdit *rb_y_hstgm_max_idx;
    TRegLabeledEdit *rb_y_hstgm_max2_idx;
    TRegLabeledEdit *rb_y_hstgm_min_idx;
    TGroupBox *GroupBox9;
    TRegLabeledEdit *rb_apl;
    TRegLabeledEdit *RegLabeledEdit1;
    TRegLabeledEdit *RegLabeledEdit2;
    TRegLabeledEdit *RegLabeledEdit3;
    TRegLabeledEdit *RegLabeledEdit4;
    TRegLabeledEdit *RegLabeledEdit5;
    TRegLabeledEdit *RegLabeledEdit6;
    TRegLabeledEdit *RegLabeledEdit7;
    TRegLabeledEdit *RegLabeledEdit8;
    TRegLabeledEdit *RegLabeledEdit9;
    TRegLabeledEdit *RegLabeledEdit10;
    TRegLabeledEdit *RegLabeledEdit11;
    TRegLabeledEdit *RegLabeledEdit12;
    TRegLabeledEdit *RegLabeledEdit13;
    TRegLabeledEdit *RegLabeledEdit14;
    TRegLabeledEdit *RegLabeledEdit15;
    TRegLabeledEdit *RegLabeledEdit16;
    TRegLabeledEdit *RegLabeledEdit17;
    TRegLabeledEdit *RegLabeledEdit18;
    TRegLabeledEdit *RegLabeledEdit19;
    TRegLabeledEdit *RegLabeledEdit20;
    TRegLabeledEdit *RegLabeledEdit21;
    TRegLabeledEdit *RegLabeledEdit22;
    TRegLabeledEdit *RegLabeledEdit23;
    TRegLabeledEdit *RegLabeledEdit24;
    TRegLabeledEdit *RegLabeledEdit25;
    TRegLabeledEdit *RegLabeledEdit26;
    TRegLabeledEdit *RegLabeledEdit27;
    TRegLabeledEdit *RegLabeledEdit28;
    TRegLabeledEdit *RegLabeledEdit29;
    TRegLabeledEdit *RegLabeledEdit30;
    TRegLabeledEdit *RegLabeledEdit31;
    TRegLabeledEdit *RegLabeledEdit32;
    TRegLabeledEdit *film_det_en;
    TRegLabeledEdit *RegLabeledEdit33;
    TRegLabeledEdit *RegLabeledEdit34;
    TGroupBox *GroupBox10;
    TRegLabeledEdit *RegLabeledEdit35;
    TRegLabeledEdit *RegLabeledEdit36;
    TRegLabeledEdit *RegLabeledEdit39;
    TRegLabeledEdit *RegLabeledEdit40;
    TGroupBox *GroupBox11;
    TRegLabeledEdit *RegLabeledEdit37;
    TRegLabeledEdit *RegLabeledEdit38;
    TRegCheckBox *RegCheckBox1;
    TGroupBox *GroupBox12;
    TRegCheckBox *RegCheckBox2;
    TRegCheckBox *RegCheckBox3;
    TRegCheckBox *RegCheckBox4;
    TRegCheckBox *RegCheckBox5;
    void __fastcall btn_RefreshClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_Film(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Film *Form_Film;
//---------------------------------------------------------------------------
#endif

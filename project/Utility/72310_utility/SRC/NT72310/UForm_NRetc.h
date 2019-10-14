//---------------------------------------------------------------------------

#ifndef UForm_NRetcH
#define UForm_NRetcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
#include "RegCheckBox.h"
#include "RegRadioButton.h"
#include "RegLabeledEdit.h"
#include "RegEdit.h"
//---------------------------------------------------------------------------
class TForm_NRetc : public TMEMCForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TRegEdit *Edit1;
    TRegCheckBox *CheckBox1;
    TRegCheckBox *CheckBox2;
    TRegCheckBox *CheckBox3;
    TRegRadioButton *RadioButton1;
    TRegRadioButton *RadioButton2;
    TRegEdit *Edit2;
    TRegCheckBox *CheckBox9;
    TRegCheckBox *CheckBox10;
    TGroupBox *GroupBox2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label27;
    TRegEdit *Edit3;
    TRegCheckBox *CheckBox4;
    TRegCheckBox *CheckBox5;
    TRegCheckBox *CheckBox6;
    TRegCheckBox *CheckBox7;
    TRegEdit *Edit5;
    TRegCheckBox *CheckBox8;
    TRegEdit *Edit4;
    TGroupBox *GroupBox3;
    TLabel *Label6;
    TLabel *Label7;
    TRegEdit *Edit6;
    TRegEdit *Edit7;
    TGroupBox *GroupBox4;
    TGroupBox *GroupBox5;
    TLabel *Label8;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label22;
    TLabel *Label23;
    TLabel *Label21;
    TRegRadioButton *RadioButton4;
    TRegRadioButton *RadioButton5;
    TGroupBox *GroupBox6;
    TRegLabeledEdit *nr1_sad_limit;
    TRegLabeledEdit *sad_thd1;
    TRegLabeledEdit *sad_thd2;
    TRegLabeledEdit *nr0_sad_limit;
    TGroupBox *ME_STE;
    TLabel *Label26;
    TRegRadioButton *RadioButton6;
    TRegRadioButton *RadioButton7;
    TRegLabeledEdit *transi_thd;
    TRegLabeledEdit *ste_thd1;
    TRegLabeledEdit *ste_thd2;
    TRegLabeledEdit *watershed;
    TRegLabeledEdit *weitght;
    TRegLabeledEdit *slope2;
    TRegLabeledEdit *slope1;
    TGroupBox *action;
    TRegLabeledEdit *nr_action;
    TRegLabeledEdit *action_thd1;
    TRegLabeledEdit *action_thd2;
    TRegLabeledEdit *pos_out;
    TRegLabeledEdit *neg_out;
    TGroupBox *Smv;
    TRegCheckBox *center;
    TRegCheckBox *smv_en;
    TRegLabeledEdit *smv_clr_step;
    TRegLabeledEdit *v0;
    TRegLabeledEdit *v1;
    TRegLabeledEdit *v2;
    TRegLabeledEdit *v3;
    TRegLabeledEdit *h0;
    TRegLabeledEdit *h1;
    TRegLabeledEdit *h2;
    TRegLabeledEdit *h3;
    TRegLabeledEdit *smv_thd;
    TRegLabeledEdit *zmv_thd;
    TRegCheckBox *inner_nr0_smv0;
    TRegCheckBox *inner_nr1_smv1;
    TRegCheckBox *outer_nr1_smv1;
    TGroupBox *Pan_clr;
    TRegLabeledEdit *mv_diff;
    TRegLabeledEdit *mv_len;
    TRegLabeledEdit *mv_cnt_thd;
    TRegCheckBox *pan_clr_en;
    TRegLabeledEdit *nr0_pan_clr_step;
    TRegLabeledEdit *nr1_pan_clr_step;
    TGroupBox *Outpost;
    TRegRadioButton *LPF_181;
    TRegRadioButton *LPF_121;
    TRegLabeledEdit *low_bound;
    TRegLabeledEdit *slope;
    TRegLabeledEdit *lv_thd;
    TGroupBox *PTL;
    TRegCheckBox *org;
    TRegCheckBox *OR_all;
    TRegCheckBox *short_line;
    TRegCheckBox *small_corner;
    TRegCheckBox *diagonal_line;
    TButton *btn_Refresh;
    TRegEdit *RegEdit1;
    TRegEdit *RegEdit2;
    TLabel *Label9;
    TRegCheckBox *RegCheckBox1;
    TRegEdit *RegEdit3;
    TRegEdit *RegEdit4;
    TRegEdit *RegEdit5;
    TRegEdit *RegEdit6;
    TRegEdit *RegEdit7;
    TRegEdit *RegEdit8;
    TRegEdit *RegEdit9;
    TRegEdit *RegEdit10;
    TRegEdit *RegEdit11;
    TRegEdit *RegEdit12;
    TRegEdit *RegEdit13;
    TRegEdit *RegEdit14;
    void __fastcall Edit1Change(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall CheckBox2Click(TObject *Sender);
    void __fastcall CheckBox3Click(TObject *Sender);
    void __fastcall CheckBox9Click(TObject *Sender);
    void __fastcall RadioButton1Click(TObject *Sender);
    void __fastcall CheckBox10Click(TObject *Sender);
    void __fastcall RadioButton2Click(TObject *Sender);
    void __fastcall Edit2Change(TObject *Sender);
    void __fastcall Edit3Change(TObject *Sender);
    void __fastcall Edit4Change(TObject *Sender);
    void __fastcall CheckBox4Click(TObject *Sender);
    void __fastcall CheckBox5Click(TObject *Sender);
    void __fastcall CheckBox7Click(TObject *Sender);
    void __fastcall CheckBox8Click(TObject *Sender);
    void __fastcall Edit5Change(TObject *Sender);
    void __fastcall Edit6Change(TObject *Sender);
    void __fastcall Edit7Change(TObject *Sender);
    void __fastcall RadioButton4Click(TObject *Sender);
    void __fastcall RadioButton5Click(TObject *Sender);
    void __fastcall Label9Click(TObject *Sender);
    void __fastcall Label10Click(TObject *Sender);
    void __fastcall Label11Click(TObject *Sender);
    void __fastcall Label12Click(TObject *Sender);
    void __fastcall Label13Click(TObject *Sender);
    void __fastcall Label18Click(TObject *Sender);
    void __fastcall Label19Click(TObject *Sender);
    void __fastcall Label20Click(TObject *Sender);
    void __fastcall Label21Click(TObject *Sender);
    void __fastcall Label14Click(TObject *Sender);
    void __fastcall Label15Click(TObject *Sender);
    void __fastcall Label16Click(TObject *Sender);
    void __fastcall Label17Click(TObject *Sender);
    void __fastcall Label24Click(TObject *Sender);
    void __fastcall Label25Click(TObject *Sender);
    void __fastcall sad_thd1Change(TObject *Sender);
    void __fastcall sad_thd2Change(TObject *Sender);
    void __fastcall nr0_sad_limitChange(TObject *Sender);
    void __fastcall nr1_sad_limitChange(TObject *Sender);
    void __fastcall RadioButton6Click(TObject *Sender);
    void __fastcall RadioButton7Click(TObject *Sender);
    void __fastcall Label26Click(TObject *Sender);
    void __fastcall transi_thdChange(TObject *Sender);
    void __fastcall ME_STEClick(TObject *Sender);
    void __fastcall ste_thd2Change(TObject *Sender);
    void __fastcall slope1Change(TObject *Sender);
    void __fastcall slope2Change(TObject *Sender);
    void __fastcall watershedChange(TObject *Sender);
    void __fastcall nr_actionChange(TObject *Sender);
    void __fastcall action_thd1Change(TObject *Sender);
    void __fastcall action_thd2Change(TObject *Sender);
    void __fastcall pos_outChange(TObject *Sender);
    void __fastcall neg_outChange(TObject *Sender);
    void __fastcall smv_enClick(TObject *Sender);
    void __fastcall centerClick(TObject *Sender);
    void __fastcall smv_clr_stepChange(TObject *Sender);
    void __fastcall smv_thdChange(TObject *Sender);
    void __fastcall zmv_thdChange(TObject *Sender);
    void __fastcall v0Change(TObject *Sender);
    void __fastcall v1Change(TObject *Sender);
    void __fastcall v2Change(TObject *Sender);
    void __fastcall v3Change(TObject *Sender);
    void __fastcall h0Change(TObject *Sender);
    void __fastcall h1Change(TObject *Sender);
    void __fastcall h2Change(TObject *Sender);
    void __fastcall h3Change(TObject *Sender);
    void __fastcall inner_nr0_smv0Click(TObject *Sender);
    void __fastcall inner_nr1_smv1Click(TObject *Sender);
    void __fastcall outer_nr1_smv1Click(TObject *Sender);
    void __fastcall pan_clr_enClick(TObject *Sender);
    void __fastcall mv_diffChange(TObject *Sender);
    void __fastcall mv_lenChange(TObject *Sender);
    void __fastcall mv_cnt_thdChange(TObject *Sender);
    void __fastcall nr0_pan_clr_stepChange(TObject *Sender);
    void __fastcall nr1_pan_clr_stepChange(TObject *Sender);
    void __fastcall LPF_181Click(TObject *Sender);
    void __fastcall LPF_121Click(TObject *Sender);
    void __fastcall center_onlyClick(TObject *Sender);
    void __fastcall low_boundChange(TObject *Sender);
    void __fastcall slopeChange(TObject *Sender);
    void __fastcall lv_thdChange(TObject *Sender);
    void __fastcall orgClick(TObject *Sender);
    void __fastcall OR_allClick(TObject *Sender);
    void __fastcall short_lineClick(TObject *Sender);
    void __fastcall small_cornerClick(TObject *Sender);
    void __fastcall diagonal_lineClick(TObject *Sender);
    void __fastcall btn_RefreshClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_NRetc(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_NRetc *Form_NRetc;
//---------------------------------------------------------------------------
#endif

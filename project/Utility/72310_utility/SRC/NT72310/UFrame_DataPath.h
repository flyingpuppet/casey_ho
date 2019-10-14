//---------------------------------------------------------------------------

#ifndef UFrame_DataPathH
#define UFrame_DataPathH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCFrame.h"
#include "RegCheckBox.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrame_DataPath : public TMEMCFrame
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TGroupBox *GB_MEY;
    TCheckBox *CB_MeY_DC_Bypass;
    TCheckBox *CB_MeY_LastLine_Bypass;
    TGroupBox *GroupBox6;
    TRadioButton *RB_MeY_DC_mode0;
    TRadioButton *RB_MeY_DC_mode1;
    TRadioButton *RB_MeY_DC_mode2;
    TRadioButton *RB_MeY_DC_mode3;
    TRadioButton *RB_MeY_DC_mode4;
    TCheckBox *CB_MeY_Debug;
    TGroupBox *GroupBox8;
    TRadioButton *RB_MeY_Error_0;
    TRadioButton *RB_MeY_Error_1;
    TRadioButton *RB_MeY_Error_2;
    TRadioButton *RB_MeY_Error_3;
    TGroupBox *GB_TP;
    TRadioButton *RB_MeY_Test_0;
    TRadioButton *RB_MeY_Test_1;
    TRadioButton *RB_MeY_Test_2;
    TRadioButton *RB_MeY_Test_3;
    TGroupBox *GB_MCY;
    TCheckBox *CB_McY_DC_Bypass;
    TCheckBox *CB_McY_LastLine_Bypass;
    TGroupBox *GroupBox4;
    TRadioButton *RB_McY_DC_mode0;
    TRadioButton *RB_McY_DC_mode1;
    TRadioButton *RB_McY_DC_mode2;
    TRadioButton *RB_McY_DC_mode3;
    TRadioButton *RB_McY_DC_mode4;
    TGroupBox *GroupBox9;
    TRadioButton *RB_McY_Error_0;
    TRadioButton *RB_McY_Error_1;
    TRadioButton *RB_McY_Error_2;
    TRadioButton *RB_McY_Error_3;
    TGroupBox *GroupBox10;
    TRadioButton *RB_McY_Test_0;
    TRadioButton *RB_McY_Test_1;
    TRadioButton *RB_McY_Test_2;
    TRadioButton *RB_McY_Test_3;
    TCheckBox *CB_McY_Debug;
    TGroupBox *GB_MCC;
    TCheckBox *CB_McC_DC_Bypass;
    TCheckBox *CB_McC_LastLine_Bypass;
    TGroupBox *GroupBox7;
    TRadioButton *RB_McC_DC_mode0;
    TRadioButton *RB_McC_DC_mode1;
    TRadioButton *RB_McC_DC_mode2;
    TRadioButton *RB_McC_DC_mode3;
    TRadioButton *RB_McC_DC_mode4;
    TGroupBox *GroupBox11;
    TRadioButton *RB_McC_Error_0;
    TRadioButton *RB_McC_Error_1;
    TRadioButton *RB_McC_Error_2;
    TRadioButton *RB_McC_Error_3;
    TGroupBox *GroupBox12;
    TRadioButton *RB_McC_Test_0;
    TRadioButton *RB_McC_Test_1;
    TRadioButton *RB_McC_Test_2;
    TRadioButton *RB_McC_Test_3;
    TCheckBox *CB_McC_Debug;
    TGroupBox *GB_DCMode;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TRadioButton *RadioButton5;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TRadioButton *RadioButton11;
    TGroupBox *GroupBox3;
    TRadioButton *rb_PC;
    TRadioButton *rb_VD;
    TGroupBox *GroupBox5;
    TRadioButton *rb_888;
    TRadioButton *rb_101010;
    TRadioButton *rb_1088;
    TButton *Button11;
    TCheckBox *CB_Half;
    TButton *Button1;
    void __fastcall Button11Click(TObject *Sender);
    void __fastcall CB_HalfClick(TObject *Sender);
    void __fastcall RadioButton1Click(TObject *Sender);
    void __fastcall rb_PCClick(TObject *Sender);
    void __fastcall CB_MeY_DC_BypassClick(TObject *Sender);
    void __fastcall CB_MeY_DebugClick(TObject *Sender);
    void __fastcall RB_MeY_DC_mode0Click(TObject *Sender);
    void __fastcall RB_MeY_Error_0Click(TObject *Sender);
    void __fastcall RB_MeY_Test_0Click(TObject *Sender);
    void __fastcall RB_McY_Error_0Click(TObject *Sender);
    void __fastcall RB_McY_Test_0Click(TObject *Sender);
    void __fastcall RB_McC_Error_0Click(TObject *Sender);
    void __fastcall RB_McC_Test_0Click(TObject *Sender);
    void __fastcall RadioButton11Click(TObject *Sender);
    void __fastcall rb_888Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);

private:	// User declarations
    void __fastcall NT72310_Bypass(bool checkflag, int tag);
    void __fastcall NT72310_SetDCMode(int mode, int tag);
public:		// User declarations
    __fastcall TFrame_DataPath(TComponent* Owner);
    void __fastcall Refresh();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_DataPath *Frame_DataPath;
//---------------------------------------------------------------------------
#endif

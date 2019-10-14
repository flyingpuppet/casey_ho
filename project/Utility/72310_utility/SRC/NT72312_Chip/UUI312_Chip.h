//---------------------------------------------------------------------------

#ifndef UUI312_ChipH
#define UUI312_ChipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "RegCheckBox.h"
#include "RegLabeledEdit.h"
//---------------------------------------------------------------------------
class TForm_UI312_Chip : public TMEMCForm
{
__published:	// IDE-managed Components
    TRadioGroup *rg_Input_Format;
    TRadioGroup *rg_Output_Format;
    TRadioGroup *rg_Input_Mode;
    TRadioGroup *rg_SwapLR;
    TGroupBox *gb_depth;
    TTrackBar *tb_Depth;
    TTrackBar *tb_Disparity;
    TLabel *Label1;
    TLabel *Label2;
    TRegCheckBox *rcb_Mute;
    TGroupBox *GroupBox1;
    TLabel *Label3;
    TLabel *Label4;
    TTrackBar *tb_FRC;
    TTrackBar *tb_Dejudder;
    TButton *Button1;
        TGroupBox *GroupBox2;
        TRegLabeledEdit *rle_PWM_Freq;
        TRegLabeledEdit *rle_PWM_Duty;
        TRegLabeledEdit *rle_Test_Pattern;
    TButton *Button2;
    void __fastcall rg_Input_ModeClick(TObject *Sender);
    void __fastcall rg_Output_FormatClick(TObject *Sender);
    void __fastcall rg_Input_FormatClick(TObject *Sender);
    void __fastcall rg_SwapLRClick(TObject *Sender);
    void __fastcall tb_DepthChange(TObject *Sender);
    void __fastcall tb_DisparityChange(TObject *Sender);
    void __fastcall tb_FRCChange(TObject *Sender);
    void __fastcall tb_DejudderChange(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_UI312_Chip(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_UI312_Chip *Form_UI312_Chip;
//---------------------------------------------------------------------------
#endif

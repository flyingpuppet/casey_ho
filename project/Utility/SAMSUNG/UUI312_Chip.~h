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
#include "RegEdit.h"
#include "RegScrollBar.h"
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
    TButton *Button1;
        TGroupBox *GroupBox2;
        TRegLabeledEdit *rle_PWM_Freq;
        TRegLabeledEdit *rle_PWM_Duty;
        TRegLabeledEdit *rle_Test_Pattern;
    TGroupBox *GroupBox3;
    TRegLabeledEdit *rle_BT_Delay;
    TRegLabeledEdit *rle_BT_Duty;
    TGroupBox *GroupBox4;
    TRegLabeledEdit *rle_3DPWM_Delay;
    TRegLabeledEdit *rle_3DPWM_Duty;
    TRadioGroup *rg_OutFre;
    TRegCheckBox *rcb_panel;
    TRegCheckBox *rcb_bbPanel;
    TGroupBox *GroupBox1;
    TLabel *Label3;
    TLabel *Label4;
    TTrackBar *tb_FRC;
    TTrackBar *tb_Dejudder;
    TRadioGroup *rg_frc;
    TRadioGroup *rg_Mailbox;
    TRegLabeledEdit *rle_Mute;
    TRegLabeledEdit *RegLabeledEdit10;
        TGroupBox *gb_WB;
        TRegLabeledEdit *RegLabeledEdit1;
        TRegLabeledEdit *RegLabeledEdit2;
        TRegLabeledEdit *RegLabeledEdit3;
        TRegLabeledEdit *RegLabeledEdit4;
        TRegLabeledEdit *RegLabeledEdit5;
        TRegLabeledEdit *RegLabeledEdit6;
        TRegLabeledEdit *RegLabeledEdit7;
        TRegLabeledEdit *RegLabeledEdit8;
        TRegLabeledEdit *RegLabeledEdit9;
        TRegCheckBox *RegCheckBox1;
        TRegScrollBar *RegScrollBar_RGain;
        TRegScrollBar *RegScrollBar_GGain;
        TRegScrollBar *RegScrollBar_BGain;
        TRegScrollBar *RegScrollBar_ROff;
        TRegScrollBar *RegScrollBar_GOff;
        TRegScrollBar *RegScrollBar_BOff;
        TRegScrollBar *RegScrollBar_RLmt;
        TRegScrollBar *RegScrollBar_GLmt;
        TRegScrollBar *RegScrollBar_BLmt;
    TRegScrollBar *RegScrollBar1;
    TRegCheckBox *RegCheckBox2;
    void __fastcall rg_Input_ModeClick(TObject *Sender);
    void __fastcall rg_Output_FormatClick(TObject *Sender);
    void __fastcall rg_Input_FormatClick(TObject *Sender);
    void __fastcall rg_SwapLRClick(TObject *Sender);
    void __fastcall tb_DepthChange(TObject *Sender);
    void __fastcall tb_DisparityChange(TObject *Sender);
    void __fastcall tb_FRCChange(TObject *Sender);
    void __fastcall tb_DejudderChange(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall rg_OutFreClick(TObject *Sender);
    void __fastcall rg_frcClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall rg_MailboxClick(TObject *Sender);

    void __fastcall RegEditExit(TObject *Sender);
    void __fastcall RegEditKeyPress(TObject * Sender, char & Key);
    void __fastcall RegScrollBarScroll(TObject * Sender, TScrollCode ScrollCode, int & ScrollPos);
    
private:	// User declarations
    int MailBoxType;
    enum En_frcLevel{en_standard, en_smooth, en_clear, en_custom};
    int frc_level, dejudder_level;
    virtual AnsiString __fastcall getEditName(int i);
    virtual AnsiString __fastcall getScrollName(int i) ;
    virtual int __fastcall getconCount();
    int frc_custom;
    static AnsiString rgb_conres[];
    void __fastcall FRCLevel(En_frcLevel en_mode);
public:		// User declarations
    __fastcall TForm_UI312_Chip(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_UI312_Chip *Form_UI312_Chip;
//---------------------------------------------------------------------------
#endif

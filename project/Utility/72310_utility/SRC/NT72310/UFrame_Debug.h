//---------------------------------------------------------------------------

#ifndef UFrame_DebugH
#define UFrame_DebugH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCFrame.h"
#include <Buttons.hpp>
#include "RegEdit.h"
#include "RegRadioButton.h"
#include "RegScrollBar.h"
//---------------------------------------------------------------------------
class TFrame_Debug : public TMEMCFrame
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox13;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TCheckBox *CB_DebugPort;
    TCheckBox *CB_DebugByte;
    TScrollBar *SB_sig;
    TEdit *Ed_sig;
    TScrollBar *SB_sig1;
    TEdit *Ed_sig1;
    TScrollBar *SB_low;
    TEdit *Ed_low;
    TScrollBar *SB_high;
    TEdit *Ed_high;
    TButton *Button12;
    TGroupBox *GroupBox14;
    TSpeedButton *SpeedButton1;
    TSpeedButton *btn_Refresh;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TCheckBox *CB_meiyr_lb;
    TCheckBox *CB_meiyr_pic;
    TCheckBox *CB_IPy;
    TCheckBox *CB_IPcb;
    TCheckBox *CB_IPcr;
    TCheckBox *CB_IPyrd;
    TCheckBox *CB_mepyr_pic;
    TCheckBox *CB_mepyr_lb;
    TCheckBox *CB_mei2yr_pic;
    TCheckBox *CB_mei2yr_lb;
    TCheckBox *CB_mciyr_pic;
    TCheckBox *CB_mciyr_lb;
    TCheckBox *CB_mcicr_pic;
    TCheckBox *CB_mcicr_lb;
    TCheckBox *CB_mcpyr_pic;
    TCheckBox *CB_mcpyr_lb;
    TCheckBox *CB_mcpcr_pic;
    TCheckBox *CB_mcpcr_lb;
    TCheckBox *CB_MV_ph_wr;
    TCheckBox *CB_MV_pi_wr;
    TCheckBox *CB_MV_pi_rd;
    TCheckBox *CB_MV_ph_rd;
    TCheckBox *CB_MV_ppi_rd;
    void __fastcall Button12Click(TObject *Sender);
    void __fastcall btn_RefreshClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SB_sigScroll(TObject *Sender, TScrollCode ScrollCode,
          int &ScrollPos);
    void __fastcall CB_DebugPortClick(TObject *Sender);
    void __fastcall ReadDebugData();
    void __fastcall WriteDebugData();
    void __fastcall Ed_sigKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TFrame_Debug(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_Debug *Frame_Debug;
//---------------------------------------------------------------------------
#endif

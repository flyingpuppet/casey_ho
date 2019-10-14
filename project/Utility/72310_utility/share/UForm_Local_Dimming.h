//---------------------------------------------------------------------------

#ifndef UForm_Local_DimmingH
#define UForm_Local_DimmingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include "RegCheckBox.h"
#include "RegEdit.h"
#include "RegScrollBar.h"
#include "RegLabeledEdit.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_Local_Dimming : public TMEMCForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TRegCheckBox *RegCheckBox1;
    TRegCheckBox *RegCheckBox2;
    TGroupBox *GroupBox2;
    TRegCheckBox *RegCheckBox3;
    TRegScrollBar *RegScrollBar1;
    TRegEdit *RegEdit1;
    TLabel *Label1;
    TGroupBox *GroupBox3;
    TRegCheckBox *RegCheckBox4;
    TRegScrollBar *RegScrollBar2;
    TRegEdit *RegEdit2;
    TLabel *Label2;
    TRegScrollBar *RegScrollBar3;
    TRegEdit *RegEdit3;
    TLabel *Label3;
    TGroupBox *GroupBox4;
    TRegCheckBox *RegCheckBox5;
    TRegScrollBar *RegScrollBar4;
    TRegEdit *RegEdit4;
    TLabel *Label4;
    TRegScrollBar *RegScrollBar5;
    TRegEdit *RegEdit5;
    TLabel *Label5;
    TRegScrollBar *RegScrollBar6;
    TRegEdit *RegEdit6;
    TLabel *Label6;
    TGroupBox *GroupBox5;
    TLabel *Label7;
    TRegCheckBox *RegCheckBox6;
    TRegScrollBar *RegScrollBar7;
    TRegEdit *RegEdit7;
    TLabel *Label8;
    TRegScrollBar *RegScrollBar8;
    TRegEdit *RegEdit8;
    TGroupBox *GroupBox6;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TRegCheckBox *RegCheckBox7;
    TRegScrollBar *RegScrollBar9;
    TRegEdit *RegEdit9;
    TRegScrollBar *RegScrollBar10;
    TRegEdit *RegEdit10;
    TRegScrollBar *RegScrollBar11;
    TRegEdit *RegEdit11;
    TLabel *Label12;
    TRegScrollBar *RegScrollBar12;
    TRegEdit *RegEdit12;
    TGroupBox *GroupBox7;
    TLabel *Label13;
    TLabel *Label14;
    TRegScrollBar *RegScrollBar13;
    TRegEdit *RegEdit13;
    TRegScrollBar *RegScrollBar14;
    TRegEdit *RegEdit14;
    TLabel *Label15;
    TRegScrollBar *RegScrollBar15;
    TRegEdit *RegEdit15;
    TGroupBox *GroupBox8;
    TRegCheckBox *RegCheckBox8;
    TRegCheckBox *RegCheckBox9;
    TRegCheckBox *RegCheckBox10;
    TRegCheckBox *RegCheckBox11;
    TRegCheckBox *RegCheckBox12;
    TGroupBox *GB_DUTY_BLU;
    TRegLabeledEdit *RegLabeledEdit1;
    TRegLabeledEdit *RegLabeledEdit2;
    TRegLabeledEdit *RegLabeledEdit3;
    TRegLabeledEdit *RegLabeledEdit4;
    TRegLabeledEdit *RegLabeledEdit5;
    TRegLabeledEdit *RegLabeledEdit6;
    TRegLabeledEdit *RegLabeledEdit7;
    TRegLabeledEdit *RegLabeledEdit8;
    TButton *Button1;
    TButton *Button2;
    TScrollBar *sb_AOS_TH;
    TScrollBar *sb_AOS_PX;
    TEdit *ed_AOS_TH;
    TEdit *ed_AOS_PX;
    TRegEdit *re_AOS_TH_H;
    TRegEdit *re_AOS_TH_L;
    TRegEdit *re_AOS_PX_H;
    TRegEdit *re_AOS_PX_L;
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall RegScrollBar1Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall RegEdit1KeyPress(TObject *Sender, char &Key);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall sb_AOS_THScroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall sb_AOS_PXScroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall ed_AOS_THKeyPress(TObject *Sender, char &Key);
    void __fastcall ed_AOS_PXKeyPress(TObject *Sender, char &Key);
    void __fastcall RegEdit1Exit(TObject *Sender);
    void __fastcall ed_AOS_THExit(TObject *Sender);
    void __fastcall ed_AOS_PXExit(TObject *Sender);
private:	// User declarations
    static AnsiString conres[];
public:		// User declarations
    __fastcall TForm_Local_Dimming(TComponent* Owner);
    virtual AnsiString __fastcall getEditName(int i);
    virtual AnsiString __fastcall getScrollName(int i);
    virtual int __fastcall getconCount();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Local_Dimming *Form_Local_Dimming;
//---------------------------------------------------------------------------
#endif

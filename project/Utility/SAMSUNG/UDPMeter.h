//---------------------------------------------------------------------------

#ifndef UDPMeterH
#define UDPMeterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include "RegCheckBox.h"
#include "RegEdit.h"
#include "RegLabeledEdit.h"
#include "RegScrollBar.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_DPMeter : public TMEMCForm
{
__published:	// IDE-managed Components
    TGroupBox *gb_ColorMeter;
    TLabel *Label5;
    TLabel *Label6;
    TRegCheckBox *rcb_Cur0;
    TRegScrollBar *RegScrollBar1;
    TRegEdit *RegEdit1;
    TRegEdit *RegEdit2;
    TRegScrollBar *RegScrollBar2;
    TRegLabeledEdit *rle_R0;
    TRegLabeledEdit *rle_G0;
    TRegLabeledEdit *rle_B0;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label4;
    TGroupBox *GroupBox2;
    TLabel *Label7;
    TLabel *Label8;
    TRegCheckBox *rcb_Cur1;
    TRegScrollBar *RegScrollBar6;
    TRegEdit *RegEdit6;
    TRegEdit *RegEdit7;
    TRegScrollBar *RegScrollBar7;
    TRegLabeledEdit *rle_R1;
    TRegLabeledEdit *rle_G1;
    TRegLabeledEdit *rle_B1;
    TButton *Button1;
    TRegScrollBar *RegScrollBar3;
    TRegEdit *RegEdit3;
    TRegEdit *RegEdit4;
    TRegScrollBar *RegScrollBar4;
    TCheckBox *cb_IPPattern;
    TRegScrollBar *RegScrollBar5;
    TRegEdit *RegEdit5;
    void __fastcall RegEdit3Exit(TObject *Sender);
    void __fastcall RegEdit1Exit(TObject *Sender);
    void __fastcall RegEdit1KeyPress(TObject *Sender, char &Key);
    void __fastcall RegScrollBar1Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall cb_IPPatternClick(TObject *Sender);
    void __fastcall RegScrollBar3Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall RegEdit3KeyPress(TObject *Sender, char &Key);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    void __fastcall refreshData(TRegLabeledEdit * re);
    void __fastcall refreshRGB(int index);
    virtual AnsiString __fastcall getEditName(int i);
    virtual AnsiString __fastcall getScrollName(int i);
    virtual int __fastcall getconCount();
    static AnsiString conres[];
public:		// User declarations
    __fastcall TForm_DPMeter(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_DPMeter *Form_DPMeter;
//---------------------------------------------------------------------------
#endif

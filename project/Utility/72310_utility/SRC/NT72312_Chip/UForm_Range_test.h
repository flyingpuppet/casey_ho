//---------------------------------------------------------------------------

#ifndef UForm_Range_testH
#define UForm_Range_testH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RegCheckBox.h"
#include "RegScrollBar.h"
#include "UMEMCForm.h"
#include "RegEdit.h"
#include "RegRadioButton.h"
//---------------------------------------------------------------------------
class TForm_Range_test : public TMEMCForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TRegCheckBox *RegCheckBox1;
    TRegCheckBox *RegCheckBox2;
    TRegCheckBox *RegCheckBox3;
    TRegCheckBox *RegCheckBox4;
    TRegCheckBox *RegCheckBox5;
    TRegCheckBox *RegCheckBox6;
    TRegScrollBar *RegScrollBar1;
    TRegScrollBar *RegScrollBar2;
    TRegScrollBar *RegScrollBar3;
    TLabel *Label1;
    TLabel *Label2;
    TGroupBox *GroupBox2;
    TRegCheckBox *RegCheckBox7;
    TRegCheckBox *RegCheckBox8;
    TRegCheckBox *RegCheckBox9;
    TRegCheckBox *RegCheckBox10;
    TRegCheckBox *RegCheckBox11;
    TRegCheckBox *RegCheckBox12;
    TRegEdit *RegEdit1;
    TRegEdit *RegEdit2;
    TRegEdit *RegEdit3;
    TRegScrollBar *RegScrollBar4;
    TRegEdit *RegEdit4;
    TLabel *Label3;
    TRegScrollBar *RegScrollBar5;
    TRegEdit *RegEdit5;
    TLabel *Label4;
    TRegScrollBar *RegScrollBar6;
    TRegEdit *RegEdit6;
    TLabel *Label5;
    TRegCheckBox *RegCheckBox13;
    TRegCheckBox *RegCheckBox14;
    TRegCheckBox *RegCheckBox15;
    TButton *Button1;
    TEdit *Edit1;
    TEdit *Edit2;
    TRegCheckBox *RegCheckBox16;
    TRegScrollBar *RegScrollBar7;
    TLabel *Label6;
    TRegEdit *RegEdit7;
    TRegScrollBar *RegScrollBar8;
    TLabel *Label7;
    TRegEdit *RegEdit8;
    TRegRadioButton *RegRadioButton1;
    TRegRadioButton *RegRadioButton2;
    TRegRadioButton *RegRadioButton3;
    TRegCheckBox *RegCheckBox17;
    void __fastcall RegScrollBar1Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall RegEdit1Exit(TObject *Sender);
    void __fastcall RegEdit1KeyPress(TObject *Sender, char &Key);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
    static AnsiString conres[];
public:		// User declarations
    __fastcall TForm_Range_test(TComponent* Owner);
    virtual AnsiString __fastcall getEditName(int i);
    virtual AnsiString __fastcall getScrollName(int i);
    virtual int __fastcall getconCount();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Range_test *Form_Range_test;
//---------------------------------------------------------------------------
#endif

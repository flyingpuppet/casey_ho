//---------------------------------------------------------------------------

#ifndef UForm_Demo_ChipH
#define UForm_Demo_ChipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include "RegCheckBox.h"
#include "RegLabeledEdit.h"
#include <ExtCtrls.hpp>
#include "RegScrollBar.h"
#include "RegEdit.h"
//---------------------------------------------------------------------------
class TForm_Demo_Chip : public TMEMCForm
{
__published:	// IDE-managed Components
    TGroupBox *GB_Demo0;
    TRegCheckBox *RegCheckBox1;
    TRegScrollBar *RegScrollBar1;
    TRegScrollBar *RegScrollBar2;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TRegScrollBar *RegScrollBar3;
    TRegScrollBar *RegScrollBar4;
    TLabel *Label4;
    TLabel *Label5;
    TRegEdit *RegEdit1;
    TRegEdit *RegEdit2;
    TRegEdit *RegEdit3;
    TRegEdit *RegEdit4;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TGroupBox *GroupBox1;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TRegScrollBar *RegScrollBar5;
    TRegScrollBar *RegScrollBar6;
    TRegScrollBar *RegScrollBar7;
    TRegScrollBar *RegScrollBar8;
    TRegEdit *RegEdit5;
    TRegEdit *RegEdit6;
    TRegEdit *RegEdit7;
    TRegEdit *RegEdit8;
    TLabel *Label10;
    TGroupBox *GroupBox2;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TRegScrollBar *RegScrollBar9;
    TRegScrollBar *RegScrollBar10;
    TRegScrollBar *RegScrollBar11;
    TRegScrollBar *RegScrollBar12;
    TRegEdit *RegEdit9;
    TRegEdit *RegEdit10;
    TRegEdit *RegEdit11;
    TRegEdit *RegEdit12;
    TGroupBox *GroupBox3;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TRegScrollBar *RegScrollBar13;
    TRegScrollBar *RegScrollBar14;
    TRegScrollBar *RegScrollBar15;
    TRegScrollBar *RegScrollBar16;
    TRegEdit *RegEdit13;
    TRegEdit *RegEdit14;
    TRegEdit *RegEdit15;
    TRegEdit *RegEdit16;
    TGroupBox *GroupBox4;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TRegScrollBar *RegScrollBar17;
    TRegScrollBar *RegScrollBar18;
    TRegScrollBar *RegScrollBar19;
    TRegScrollBar *RegScrollBar20;
    TRegEdit *RegEdit17;
    TRegEdit *RegEdit18;
    TRegEdit *RegEdit19;
    TRegEdit *RegEdit20;
    TGroupBox *GroupBox5;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label25;
    TLabel *Label26;
    TRegScrollBar *RegScrollBar21;
    TRegScrollBar *RegScrollBar22;
    TRegScrollBar *RegScrollBar23;
    TRegScrollBar *RegScrollBar24;
    TRegEdit *RegEdit21;
    TRegEdit *RegEdit22;
    TRegEdit *RegEdit23;
    TRegEdit *RegEdit24;
    TGroupBox *GroupBox6;
    TLabel *Label27;
    TLabel *Label28;
    TLabel *Label29;
    TLabel *Label30;
    TRegScrollBar *RegScrollBar25;
    TRegScrollBar *RegScrollBar26;
    TRegScrollBar *RegScrollBar27;
    TRegScrollBar *RegScrollBar28;
    TRegEdit *RegEdit25;
    TRegEdit *RegEdit26;
    TRegEdit *RegEdit27;
    TRegEdit *RegEdit28;
    TGroupBox *GroupBox7;
    TLabel *Label31;
    TLabel *Label32;
    TLabel *Label33;
    TLabel *Label34;
    TRegScrollBar *RegScrollBar29;
    TRegScrollBar *RegScrollBar30;
    TRegScrollBar *RegScrollBar31;
    TRegScrollBar *RegScrollBar32;
    TRegEdit *RegEdit29;
    TRegEdit *RegEdit30;
    TRegEdit *RegEdit31;
    TRegEdit *RegEdit32;
    TRegCheckBox *RegCheckBox2;
    TRegCheckBox *RegCheckBox3;
    TRegCheckBox *RegCheckBox4;
    TRegCheckBox *RegCheckBox5;
    TRegCheckBox *RegCheckBox6;
    TRegCheckBox *RegCheckBox7;
    TRegCheckBox *RegCheckBox8;
    TButton *Button1;
    TRadioButton *RadioButton17;
    TRadioButton *RadioButton18;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TRadioButton *RadioButton5;
    TRadioButton *RadioButton6;
    TRadioButton *RadioButton7;
    TRadioButton *RadioButton8;
    TRadioButton *RadioButton9;
    TRadioButton *RadioButton10;
    TRadioButton *RadioButton11;
    TRadioButton *RadioButton12;
    TRadioButton *RadioButton13;
    TRadioButton *RadioButton14;
    TRadioButton *RadioButton15;
    TRadioButton *RadioButton16;
    TRadioButton *RadioButton19;
    TRadioButton *RadioButton20;
    TRadioButton *RadioButton21;
    TRadioButton *RadioButton22;
    TRadioButton *RadioButton23;
    TRadioButton *RadioButton24;
    TRadioButton *RadioButton25;
    TRadioButton *RadioButton26;
    TRadioButton *RadioButton27;
    TRadioButton *RadioButton28;
    TRadioButton *RadioButton29;
    TRadioButton *RadioButton30;
    TRadioButton *RadioButton31;
    TRadioButton *RadioButton32;
    TRadioButton *RadioButton33;
    TRadioButton *RadioButton34;
    TRadioButton *RadioButton35;
    TRadioButton *RadioButton36;
    TRadioButton *RadioButton37;
    TRadioButton *RadioButton38;
    TRadioButton *RadioButton39;
    TRadioButton *RadioButton40;
    TButton *btn_win0;
    TButton *btn_win1;
    TButton *btn_win2;
    TButton *btn_win3;
    TButton *btn_win4;
    TButton *btn_win5;
    TButton *btn_win6;
    TButton *btn_win7;
    void __fastcall RegScrollBar1Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall RegEdit1Exit(TObject *Sender);
    void __fastcall RegEdit1KeyPress(TObject *Sender, char &Key);
    void __fastcall RadioButton33Click(TObject *Sender);
    void __fastcall btn_win0Click(TObject *Sender);
    void __fastcall RadioButton3Click(TObject *Sender);
    void __fastcall RadioButton7Click(TObject *Sender);
    void __fastcall RadioButton11Click(TObject *Sender);
    void __fastcall RadioButton15Click(TObject *Sender);
    void __fastcall RadioButton21Click(TObject *Sender);
    void __fastcall RadioButton25Click(TObject *Sender);
    void __fastcall RadioButton29Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
    static AnsiString conres[];
    static unsigned int DemoWin[4][4];
public:		// User declarations
    __fastcall TForm_Demo_Chip(TComponent* Owner);
    virtual AnsiString __fastcall getEditName(int i);
    virtual AnsiString __fastcall getScrollName(int i);
    virtual int __fastcall getconCount();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Demo_Chip *Form_Demo_Chip;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef UForm_ValidationH
#define UForm_ValidationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
#include "RegLabeledEdit.h"
#include "RegEdit.h"
#include "RegScrollBar.h"
//---------------------------------------------------------------------------
class TForm_Validation : public TMEMCForm
{
__published:	// IDE-managed Components
    TPanel *pl_dock;
    TPanel *pl_left;
    TPanel *pl_right;
    TPanel *Panel1;
    TGroupBox *GroupBox8;
    TRegLabeledEdit *RegLabeledEdit10;
    TRegLabeledEdit *RegLabeledEdit11;
    TRegLabeledEdit *RegLabeledEdit12;
    TGroupBox *GroupBox9;
    TRegLabeledEdit *RegLabeledEdit13;
    TRegLabeledEdit *RegLabeledEdit14;
    TRegLabeledEdit *RegLabeledEdit15;
    TGroupBox *GroupBox10;
    TLabel *Label17;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TRegScrollBar *RegScrollBar17;
    TRegEdit *RegEdit17;
    TRegScrollBar *RegScrollBar18;
    TRegEdit *RegEdit18;
    TRegScrollBar *RegScrollBar19;
    TRegEdit *RegEdit19;
    TRegScrollBar *RegScrollBar20;
    TRegEdit *RegEdit20;
    TGroupBox *GroupBox11;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label23;
    TLabel *Label24;
    TRegScrollBar *RegScrollBar21;
    TRegEdit *RegEdit21;
    TRegScrollBar *RegScrollBar22;
    TRegEdit *RegEdit22;
    TRegScrollBar *RegScrollBar23;
    TRegEdit *RegEdit23;
    TRegScrollBar *RegScrollBar24;
    TRegEdit *RegEdit24;
    TButton *Button2;
    TGroupBox *GroupBox12;
    TRegLabeledEdit *RegLabeledEdit16;
    TRegLabeledEdit *RegLabeledEdit17;
    TRegLabeledEdit *RegLabeledEdit18;
    TGroupBox *GroupBox13;
    TLabel *Label25;
    TLabel *Label26;
    TLabel *Label27;
    TLabel *Label28;
    TRegScrollBar *RegScrollBar25;
    TRegEdit *RegEdit25;
    TRegScrollBar *RegScrollBar26;
    TRegEdit *RegEdit26;
    TRegScrollBar *RegScrollBar27;
    TRegEdit *RegEdit27;
    TRegScrollBar *RegScrollBar28;
    TRegEdit *RegEdit28;
    TGroupBox *GroupBox14;
    TLabel *Label29;
    TLabel *Label30;
    TRegScrollBar *RegScrollBar29;
    TRegEdit *RegEdit29;
    TRegScrollBar *RegScrollBar30;
    TRegEdit *RegEdit30;
    TRegScrollBar *RegScrollBar31;
    TRegEdit *RegEdit31;
    TRegScrollBar *RegScrollBar32;
    TRegEdit *RegEdit32;
    TLabel *Label31;
    TLabel *Label32;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TRegScrollBar *RegScrollBar1;
    TRegEdit *RegEdit1;
    TRegScrollBar *RegScrollBar2;
    TRegEdit *RegEdit2;
    TRegScrollBar *RegScrollBar3;
    TRegEdit *RegEdit3;
    TRegScrollBar *RegScrollBar4;
    TRegEdit *RegEdit4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TRegScrollBar *RegScrollBar5;
    TRegEdit *RegEdit5;
    TRegScrollBar *RegScrollBar6;
    TRegEdit *RegEdit6;
    TRegScrollBar *RegScrollBar7;
    TRegEdit *RegEdit7;
    TRegScrollBar *RegScrollBar8;
    TRegEdit *RegEdit8;
    TRegScrollBar *RegScrollBar9;
    TRegEdit *RegEdit9;
    TRegScrollBar *RegScrollBar10;
    TRegEdit *RegEdit10;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TRegScrollBar *RegScrollBar11;
    TRegEdit *RegEdit11;
    TRegScrollBar *RegScrollBar12;
    TRegEdit *RegEdit12;
    TLabel *Label13;
    TLabel *Label14;
    TRegScrollBar *RegScrollBar13;
    TRegEdit *RegEdit13;
    TRegScrollBar *RegScrollBar14;
    TRegEdit *RegEdit14;
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall RegScrollBar17Change(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_Validation(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Validation *Form_Validation;
//---------------------------------------------------------------------------
#endif

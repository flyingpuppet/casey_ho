//---------------------------------------------------------------------------

#ifndef UForm_IPH
#define UForm_IPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include "RegLabeledEdit.h"
#include <ExtCtrls.hpp>
#include "RegCheckBox.h"
//---------------------------------------------------------------------------
class TForm_IP : public TMEMCForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TRegLabeledEdit *RegLabeledEdit1;
    TRegLabeledEdit *RegLabeledEdit2;
    TRegLabeledEdit *RegLabeledEdit3;
    TRegLabeledEdit *RegLabeledEdit4;
    TRegLabeledEdit *RegLabeledEdit5;
    TRegLabeledEdit *RegLabeledEdit6;
    TRegLabeledEdit *RegLabeledEdit7;
    TRegLabeledEdit *RegLabeledEdit8;
    TRegCheckBox *RegCheckBox1;
    TRegLabeledEdit *RegLabeledEdit9;
    TRegLabeledEdit *RegLabeledEdit10;
    TRegLabeledEdit *RegLabeledEdit11;
    TRegLabeledEdit *RegLabeledEdit12;
    TRegLabeledEdit *RegLabeledEdit13;
    TRegLabeledEdit *RegLabeledEdit14;
    TRegLabeledEdit *RegLabeledEdit15;
    TRegLabeledEdit *RegLabeledEdit16;
    TRegLabeledEdit *RegLabeledEdit17;
    TRegLabeledEdit *RegLabeledEdit18;
    TRegLabeledEdit *RegLabeledEdit19;
    TRegLabeledEdit *RegLabeledEdit20;
    TRegLabeledEdit *RegLabeledEdit21;
    TRegLabeledEdit *RegLabeledEdit22;
    TRegLabeledEdit *RegLabeledEdit23;
    TRegLabeledEdit *RegLabeledEdit24;
    TRegLabeledEdit *RegLabeledEdit25;
    TRegLabeledEdit *RegLabeledEdit26;
    TRegLabeledEdit *RegLabeledEdit27;
    TRegLabeledEdit *RegLabeledEdit28;
    TRegLabeledEdit *RegLabeledEdit29;
    TRegLabeledEdit *RegLabeledEdit30;
    TRegLabeledEdit *RegLabeledEdit31;
    TRegLabeledEdit *RegLabeledEdit32;
    TRegLabeledEdit *RegLabeledEdit33;
    TRegLabeledEdit *RegLabeledEdit34;
    TRegLabeledEdit *RegLabeledEdit35;
    TRegLabeledEdit *RegLabeledEdit36;
    TRegLabeledEdit *RegLabeledEdit37;
    TRegLabeledEdit *RegLabeledEdit38;
    TRegLabeledEdit *RegLabeledEdit39;
    TRegLabeledEdit *RegLabeledEdit40;
    TGroupBox *GroupBox2;
    TRegCheckBox *RegCheckBox2;
    TRegLabeledEdit *RegLabeledEdit41;
    TRegCheckBox *RegCheckBox3;
    TRegLabeledEdit *RegLabeledEdit42;
    TRegLabeledEdit *RegLabeledEdit43;
    TRegLabeledEdit *RegLabeledEdit44;
    TRegLabeledEdit *RegLabeledEdit45;
    TRegLabeledEdit *RegLabeledEdit46;
    TRegLabeledEdit *RegLabeledEdit47;
    TRegLabeledEdit *RegLabeledEdit48;
    TRegLabeledEdit *RegLabeledEdit49;
    TRegLabeledEdit *RegLabeledEdit50;
    TRegLabeledEdit *RegLabeledEdit51;
    TRegLabeledEdit *RegLabeledEdit52;
    TRegLabeledEdit *RegLabeledEdit53;
    TButton *btnRefresh;
    TGroupBox *GroupBox3;
    TRegLabeledEdit *RegLabeledEdit54;
    TRegLabeledEdit *RegLabeledEdit55;
    void __fastcall btnRefreshClick(TObject *Sender);
    void __fastcall RegLabeledEdit44KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_IP(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_IP *Form_IP;
//---------------------------------------------------------------------------
#endif

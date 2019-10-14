//---------------------------------------------------------------------------

#ifndef UForm_PHSH
#define UForm_PHSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_PHS : public TMEMCForm
{
__published:	// IDE-managed Components
    TButton *btn_autotiming;
    TLabeledEdit *le_PHS;
    void __fastcall btn_autotimingClick(TObject *Sender);
    void __fastcall le_PHSKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_PHS(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_PHS *Form_PHS;
//---------------------------------------------------------------------------
#endif

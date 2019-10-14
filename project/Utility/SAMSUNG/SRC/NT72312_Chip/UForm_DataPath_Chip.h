//---------------------------------------------------------------------------

#ifndef UForm_DataPath_ChipH
#define UForm_DataPath_ChipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RegCheckBox.h"
#include "RegLabeledEdit.h"
#include "UForm_DataPath.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_DataPath_Chip : public TForm_DataPath
{
__published:	// IDE-managed Components
    TButton *Button3;
    TCheckBox *cb_Hscaler;
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall cb_HscalerClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_DataPath_Chip(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_DataPath_Chip *Form_DataPath_Chip;
//---------------------------------------------------------------------------
#endif

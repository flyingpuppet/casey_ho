//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_ME_1_Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RegCheckBox"
#pragma link "RegEdit"
#pragma link "RegLabeledEdit"
#pragma link "UForm_ME_1"
#pragma resource "*.dfm"
TForm_ME_1_Chip *Form_ME_1_Chip;
//---------------------------------------------------------------------------
__fastcall TForm_ME_1_Chip::TForm_ME_1_Chip(TComponent* Owner)
    : TForm_ME_1(Owner)
{
}
//---------------------------------------------------------------------------

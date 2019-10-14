//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_gauss_Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UForm_Gauss"
#pragma resource "*.dfm"
TForm_gauss_Chip *Form_gauss_Chip;
//---------------------------------------------------------------------------
__fastcall TForm_gauss_Chip::TForm_gauss_Chip(TComponent* Owner)
    : TForm_gauss(Owner)
{
}
//---------------------------------------------------------------------------

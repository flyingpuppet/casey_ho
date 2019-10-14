//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_DDR_312Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UFrame_DDR"
#pragma resource "*.dfm"
TFrame_DDR_312Chip *Frame_DDR_312Chip;
//---------------------------------------------------------------------------
__fastcall TFrame_DDR_312Chip::TFrame_DDR_312Chip(TComponent* Owner)
    : TFrame_DDR(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_BWMeasure_312Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UFrame_BWMeasure_312FPGA"
#pragma resource "*.dfm"
TFrame_BWMeasure_312Chip *Frame_BWMeasure_312Chip;
//---------------------------------------------------------------------------
__fastcall TFrame_BWMeasure_312Chip::TFrame_BWMeasure_312Chip(TComponent* Owner)
    : TFrame_BWMeasure_312FPGA(Owner)
{
}
//---------------------------------------------------------------------------
int __fastcall TFrame_BWMeasure_312Chip::GetMCCLK()
{
    return 150;
}
//---------------------------------------------------------------------------


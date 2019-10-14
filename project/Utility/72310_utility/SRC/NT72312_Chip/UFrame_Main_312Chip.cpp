//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_Main_312Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RegCheckBox"
#pragma link "UFrame_Main_312FPGA"
#pragma resource "*.dfm"
TFrame_Main_312Chip *Frame_Main_312Chip;
//---------------------------------------------------------------------------
__fastcall TFrame_Main_312Chip::TFrame_Main_312Chip(TComponent* Owner)
    : TFrame_Main_312FPGA(Owner)
{
}
__fastcall TFrame_Main_312Chip::TFrame_Main_312Chip(TComponent* Owner, DeviceCreate * oDev_Cre)
    : TFrame_Main_312FPGA(Owner,oDev_Cre)
{
}
//---------------------------------------------------------------------------



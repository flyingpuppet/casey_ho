//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_DDR_312FPGA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UFrame_DDR"
#pragma resource "*.dfm"
TFrame_DDR_312FPGA *Frame_DDR_312FPGA;
//---------------------------------------------------------------------------
__fastcall TFrame_DDR_312FPGA::TFrame_DDR_312FPGA(TComponent* Owner)
    : TFrame_DDR(Owner)
{
}
//---------------------------------------------------------------------------

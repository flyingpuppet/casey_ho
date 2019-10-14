//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_PHS.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"
TForm_PHS *Form_PHS;
//---------------------------------------------------------------------------
__fastcall TForm_PHS::TForm_PHS(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_PHS::btn_autotimingClick(TObject *Sender)
{
    /*0xE009_001C bit[27:16] = 0xE009_00E0 bit[27:16]
    0xE009_0030 bit[27:16] = 0xE009_00DC bit[27:16]
    0xE009_0030 bit[ 9: 0] = 0xE009_00DC bit[ 9: 0]
    0xE009_0034 bit[27:16] = 0x0A (V-sync width)
    0xE009_0034 bit[ 9: 0] = 0xE009_00E0 bit[11: 0] - 0xE009_00DC bit[27:16] - 0xE009_00DC bit[ 9: 0]
    0xE009_0038 bit[27:16] = 0xE009_00E4 bit[ 9: 0]
    0xE009_0038 bit[10: 0] = 0x10 (H-sync width)
    0xE009_003C bit[27:16] = 0xE009_00D8 bit[27:16] - 0xE009_00E0 bit[27:16] - 0xE009_00E4 bit[ 9: 0]
    0xE009_003C bit[10: 0] = 0xE009_00E0 bit[27:16]  */

    unsigned int value, val_E0_H, val_E0_L, val_DC_H, val_DC_L, val_E4, val_D8;

    GetDevice()->ReadDWord(0xE00900E0, value);
    val_E0_H = (value >> 16) & 0x0FFF;
    val_E0_L = value & 0x00000FFF;

    GetDevice()->ReadDWord(0xE00900DC, value);
    val_DC_H = (value >> 16) & 0x0FFF;
    val_DC_L = value & 0x000003FF;

    GetDevice()->ReadDWord(0xE00900D8, value);
    val_D8 = (value >> 16) & 0x0FFF;

    GetDevice()->ReadDWord(0xE00900E4, value);
    val_E4 = value & 0x000003FF;

    WriteFormatPara(0xE009001C, 16, 12, val_E0_H);
    WriteFormatPara(0xE0090030, 16, 12, val_DC_H);
    WriteFormatPara(0xE0090030, 0, 10, val_DC_L);
    WriteFormatPara(0xE0090034, 16, 12, 0x0A);
    WriteFormatPara(0xE0090034, 0, 10, val_E0_L-val_DC_H-val_DC_L );
    WriteFormatPara(0xE0090038, 16, 12, val_E4);
    WriteFormatPara(0xE0090038, 0, 11, 0x10);
    WriteFormatPara(0xE009003C, 16, 12, val_D8-val_E0_H-val_E4);
    WriteFormatPara(0xE009003C, 0, 11, val_E0_H);

}
//---------------------------------------------------------------------------
void __fastcall TForm_PHS::le_PHSKeyPress(TObject *Sender, char &Key)
{
    double Fval;
    unsigned int val;
    if(Key == 13)
    {
        /*0xE009_0024 bit[20: 0] = F, F = ( input_active_pixel / output_active_pixel ) x 2^20
        Create a blank that we can fill with scaling ratio
        If we want scaling ratio = 1.5x
        F = ( 1 / 1.5 ) x 2^20
        = 0.666667 x 2^20
        = 0xAAAAA
        Then auto set 0xE009_0024 bit[20: 0] = 0xAAAAA */

        Fval = le_PHS->Text.ToDouble();

        Fval = (1/Fval) * Power(2,20);
        
        val = RoundTo(Fval, 0) ;

        WriteFormatPara(0xE0090024, 0, 21, val);

    }
}
//---------------------------------------------------------------------------

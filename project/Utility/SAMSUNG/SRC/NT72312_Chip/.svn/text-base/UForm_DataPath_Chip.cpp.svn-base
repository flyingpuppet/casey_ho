//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_DataPath_Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma link "UForm_DataPath"
#pragma resource "*.dfm"
TForm_DataPath_Chip *Form_DataPath_Chip;
//---------------------------------------------------------------------------
__fastcall TForm_DataPath_Chip::TForm_DataPath_Chip(TComponent* Owner)
    : TForm_DataPath(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_DataPath_Chip::Button3Click(TObject *Sender)
{
    if(cb_Hscaler->Checked)
    {
        WriteFormatPara(0xC00C0038, 24, 2, 2);
	    GetDevice()->WriteDWord(0xE0090000, 0xac5debf6);

	    WriteFormatPara(0xE009001C, 16, 12, 0x0280);
	    GetDevice()->WriteDWord(0xE0090030, 0x04380029);
	    GetDevice()->WriteDWord(0xE0090034, 0x000A062E);
	    GetDevice()->WriteDWord(0xE0090038, 0x00190010);
	    GetDevice()->WriteDWord(0xE009003C, 0x007D03C0);
	    
	    WriteFormatPara(0xE0090020, 0, 1, 1);
	    GetDevice()->WriteDWord(0xE0090024, 0x000aaaab);
	    WriteFormatPara(0xE0090004, 0, 2, 1);


    }
    else
    {
        WriteFormatPara(0xE0090004, 0, 2, 2);
    }               

}
//---------------------------------------------------------------------------



void __fastcall TForm_DataPath_Chip::cb_HscalerClick(TObject *Sender)
{
    //Button3.Click();
}
//---------------------------------------------------------------------------






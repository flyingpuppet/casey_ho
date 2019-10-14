//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_IP.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegLabeledEdit"
#pragma link "RegCheckBox"
#pragma resource "*.dfm"
TForm_IP *Form_IP;
//---------------------------------------------------------------------------
__fastcall TForm_IP::TForm_IP(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm_IP::btnRefreshClick(TObject *Sender)
{
    TRegCheckBox * rcb;
    TRegLabeledEdit * rle;
    AnsiString str;
    int val;
    Byte bval;

    for(int i=0; i<this->ComponentCount; i++)
    {
        if(this->Components[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)this->Components[i];
            rle->Refresh();
            if(rle->Tag != 0)
            {
                if(rle->TextType == ttHex)
                {
                    str = "0x"+rle->Text;
                }
                else
                {
                    str = rle->Text;
                }
                val = str.ToInt();
                GetDevice()->ReadByte(rle->RegStartAddress.ToInt()+rle->Tag, bval);
                bval >>= 2*(rle->Tag-1);
                val = (val<<2) | bval;
                if(rle->TextType == ttInt)
                {
                    rle->Text = IntToStr(val);
                }
                else
                {
                    rle->Text = IntToHex(val, 4);
                }

            }
        }
        if(this->Components[i]->ClassNameIs("TRegCheckBox"))
        {
            rcb = (TRegCheckBox *)this->Components[i];
            rcb->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_IP::RegLabeledEdit44KeyPress(TObject *Sender,
      char &Key)
{
    TRegLabeledEdit * rle;
    Byte bval, bval1;
    AnsiString sval;
    unsigned int value;
    if(Key != 13) return;
    if(rle->Tag == 0)   return;
    
    rle = (TRegLabeledEdit *)Sender;

    GetDevice()->ReadByte(rle->RegStartAddress.ToInt() + rle->Tag, bval);
    switch(rle->Tag)
    {
        case 3:
            bval &= 0xCF;
        break;
        case 2:
            bval &= 0xF3;
        break;
        case 1:
            bval &= 0xFC;
        break;
    }

    if(rle->TextType == ttInt)
    {
        sval = rle->Text;
    }
    else
    {
        sval = "0x"+rle->Text;
    }

    value = rle->Text.ToInt();
    bval |= (value & 0x00000003)<<(2*(rle->Tag-1));
    bval1 = (value>>8) & 0x000000FF;

    GetDevice()->WriteByte(rle->RegStartAddress.ToInt() + rle->Tag, bval);
    GetDevice()->WriteByte(rle->RegStartAddress.ToInt(), bval1);
}
//---------------------------------------------------------------------------


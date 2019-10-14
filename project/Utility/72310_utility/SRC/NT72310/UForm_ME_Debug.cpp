//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_ME_Debug.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TForm_ME_Debug *Form_ME_Debug;
//---------------------------------------------------------------------------
__fastcall TForm_ME_Debug::TForm_ME_Debug(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_ME_Debug::btnRefreshClick(TObject *Sender)
{
    TRegCheckBox * rcb;
    TRegLabeledEdit * rle;
    Byte hivalue, tmp;
    AnsiString str,strValue;
    int val;
    Byte bval;
    int value;

    for(int i=0; i<this->ComponentCount; i++)
    {
        if(this->Components[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)this->Components[i];
            rle->Refresh();
            if(rle->Tag != 0)
            {
                if(rle->Tag == 1)
                {
                    if(rle->Name == "rle_mv_ini_x")
                    {
                        GetDevice()->ReadByte(rle->RegStartAddress.ToInt()+4, hivalue);
                        try
                        {
                            if(rle->TextType == ttHex)
                            {
                                strValue = "0x"+rle->Text;
                                value = strValue.ToInt();
                            }
                            else
                            {
                                value = rle->Text.ToInt();
                            }
                        }
                        catch(...)
                        {
                            value = 0;
                        }
                        tmp = hivalue  & 0x07;
                        value = (tmp<<8) | value;
                        if(rle->TextType == ttHex)
                        {
                            rle->Text = IntToHex(value,3);
                        }
                        else
                        {
                            rle->Text = IntToStr(value);
                        }
                    }
                    else
                    {
                        GetDevice()->ReadByte(rle->RegStartAddress.ToInt()+3, hivalue);
                        try
                        {
                            if(rle->TextType == ttHex)
                            {
                                strValue = "0x"+rle->Text;
                                value = strValue.ToInt();
                            }
                            else
                            {
                                value = rle->Text.ToInt();
                            }
                        }
                        catch(...)
                        {
                            value = 0;
                        }
                        tmp = (hivalue >> 3)  & 0x03;
                        value = (tmp<<8) | value;
                        if(rle->TextType == ttHex)
                        {
                            rle->Text = IntToHex(value,3);
                        }
                        else
                        {
                            rle->Text = IntToStr(value);
                        }
                    }

                }
                else
                {
                    GetDevice()->ReadByte(rle->RegStartAddress.ToInt()+rle->Tag, hivalue);
                    try
                    {
                        if(rle->TextType == ttHex)
                        {
                            strValue = "0x"+rle->Text;
                            value = strValue.ToInt();
                        }
                        else
                        {
                            value = rle->Text.ToInt();
                        }
                    }
                    catch(...)
                    {
                        value = 0;
                    }
                    tmp = hivalue  & 0x07;
                    value = (tmp<<8) | value;
                    if(rle->TextType == ttHex)
                    {
                        rle->Text = IntToHex(value,3);
                    }
                    else
                    {
                        rle->Text = IntToStr(value);
                    }
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

void __fastcall TForm_ME_Debug::RegLabeledEdit7KeyPress(TObject *Sender,
      char &Key)
{
    //
    TRegLabeledEdit * rle;
    Byte bval, bval1, bval2, tmp;
    AnsiString sval;
    unsigned int value;

    if(Key != 13)   return;

    rle = (TRegLabeledEdit *)Sender;

    GetDevice()->ReadByte(rle->RegStartAddress.ToInt()+1, tmp);
    tmp &= 0xE0;
    if(rle->TextType == ttInt)
    {
        sval = rle->Text;
    }
    else
    {
        sval = "0x"+rle->Text;
    }

    value = rle->Text.ToInt();
    bval = value & 0x000000FF;
    bval1 = (value>>8) & 0x000000FF;
    bval2 = (value>>16) & 0x0000001F;
    tmp |= bval2;

    GetDevice()->WriteByte(rle->RegStartAddress.ToInt() - rle->Tag, bval);
    GetDevice()->WriteByte(rle->RegStartAddress.ToInt(), bval1);
    GetDevice()->WriteByte(rle->RegStartAddress.ToInt()+1, tmp);
}
//---------------------------------------------------------------------------

void __fastcall TForm_ME_Debug::rle_mv_ini_xKeyPress(TObject *Sender,
      char &Key)
{
    TRegLabeledEdit * re;
    int value;
    AnsiString str;
    Byte hiByte,lowByte, tmp;


    //ShowMessage(Key);
    if(Key == 13)
    {
        re = (TRegLabeledEdit *)Sender;
        if(re->TextType == ttHex)
        {
            str = "0x"+re->Text;
        }
        else
        {
            str = re->Text;
        }
        value = str.ToInt();
        
        hiByte = (value>>8) & 0x07;
        lowByte = value & 0xFF;
        GetDevice()->ReadByte(re->RegStartAddress.ToInt()+4, tmp);
        tmp &= 0xF8;
        hiByte = hiByte|tmp;
        GetDevice()->WriteByte(re->RegStartAddress.ToInt()+4, hiByte);
        GetDevice()->WriteByte(re->RegStartAddress.ToInt(),lowByte);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_ME_Debug::rle_mv_ini_yKeyPress(TObject *Sender,
      char &Key)
{
    TRegLabeledEdit * re;
    int value;
    AnsiString str;
    Byte hiByte,lowByte, tmp;


    //ShowMessage(Key);
    if(Key == 13)
    {
        re = (TRegLabeledEdit *)Sender;
        if(re->TextType == ttHex)
        {
            str = "0x"+re->Text;
        }
        else
        {
            str = re->Text;
        }
        value = str.ToInt();
        
        hiByte = (value>>8) & 0x03;
        lowByte = value & 0xFF;
        GetDevice()->ReadByte(re->RegStartAddress.ToInt()+3, tmp);
        tmp &= 0xE7;
        hiByte = (hiByte<<3)|tmp;
        GetDevice()->WriteByte(re->RegStartAddress.ToInt()+3, hiByte);
        GetDevice()->WriteByte(re->RegStartAddress.ToInt(),lowByte);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_ME_Debug::ph_ini_rleKeyPress(TObject *Sender,
      char &Key)
{
//
    TRegLabeledEdit * re;
    int value;
    AnsiString str;
    Byte hiByte,lowByte, tmp;


    //ShowMessage(Key);
    if(Key == 13)
    {
        re = (TRegLabeledEdit *)Sender;
        if(re->TextType == ttHex)
        {
            str = "0x"+re->Text;
        }
        else
        {
            str = re->Text;
        }
        value = str.ToInt();
        
        hiByte = (value>>8) & 0x07;
        lowByte = value & 0xFF;
        GetDevice()->ReadByte(re->RegStartAddress.ToInt()+re->Tag, tmp);
        tmp &= 0xF8;
        hiByte = hiByte|tmp;
        GetDevice()->WriteByte(re->RegStartAddress.ToInt()+re->Tag, hiByte);
        GetDevice()->WriteByte(re->RegStartAddress.ToInt(),lowByte);
    }
}
//---------------------------------------------------------------------------


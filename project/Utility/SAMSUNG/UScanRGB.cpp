//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UScanRGB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"
TForm_ScanRGB *Form_ScanRGB;
//---------------------------------------------------------------------------
__fastcall TForm_ScanRGB::TForm_ScanRGB(TComponent* Owner)
    : TMEMCForm(Owner)
{
    resultList = new TStringList();

}
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetDefaultRGB()
{
    SetRGain(512);
    SetGGain(512);
    SetBGain(512);
    SetROffset(512);
    SetGOffset(512);
    SetBOffset(512);
} 
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetRGain(int val)
{
    if(!MailBox_Available())    return;

    WriteFormatPara(0x9f02006C,0,10,val);
    MailBox_SendAddress(0x9f02006C);
} 
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetGGain(int val)
{
    if(!MailBox_Available())    return;

    WriteFormatPara(0x9f02006C,10,10,val);
    MailBox_SendAddress(0x9f02006C);
} 
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetBGain(int val)
{
    if(!MailBox_Available())    return;

    WriteFormatPara(0x9f02006C,20,10,val);
    MailBox_SendAddress(0x9f02006C);
}
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetROffset(int val)
{
    if(!MailBox_Available())    return;

    WriteFormatPara(0x9f020070,0,10,val);
    MailBox_SendAddress(0x9f020070);
}
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetGOffset(int val)
{
    if(!MailBox_Available())    return;

    WriteFormatPara(0x9f020070,10,10,val);
    MailBox_SendAddress(0x9f020070);
}
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetBOffset(int val)
{
    if(!MailBox_Available())    return;

    WriteFormatPara(0x9f020070,20,10,val);
    MailBox_SendAddress(0x9f020070);
}
//---------------------------------------------------------------------------
int __fastcall TForm_ScanRGB::readROut(int index)
{
    unsigned int val, val1;
    Byte msb;
    Byte lsb;

    GetDevice()->ReadDWord(0xE00E0F80, val);
    if(index == 0)
    {
        lsb = (val>>8) & 0x03;
        GetDevice()->ReadByte(0xE00E0F76,msb);
        val = (msb << 2) | lsb;
    }
    else if(index == 1)
    {
        lsb = (val>>24) & 0x03;
        GetDevice()->ReadByte(0xE00E0F7E,msb);
        val = (msb << 2) | lsb;
    }
    return val;
}
//---------------------------------------------------------------------------
int __fastcall TForm_ScanRGB::readGOut(int index)
{
    unsigned int val;
    Byte msb;
    Byte lsb;

    GetDevice()->ReadDWord(0xE00E0F80, val);
    if(index == 0)
    {
        lsb = (val>>4) & 0x03;
        GetDevice()->ReadByte(0xE00E0F75,msb);
        val = (msb << 2) | lsb;
    }
    else if(index == 1)
    {
        lsb = (val>>20) & 0x03;
        GetDevice()->ReadByte(0xE00E0F7D,msb);
        val = (msb << 2) | lsb;
    }
    return val;
}
//---------------------------------------------------------------------------
int __fastcall TForm_ScanRGB::readBOut(int index)
{
    unsigned int val;
    Byte msb;
    Byte lsb;

    GetDevice()->ReadDWord(0xE00E0F80, val);
    if(index == 0)
    {
        lsb = val & 0x03;
        GetDevice()->ReadByte(0xE00E0F74,msb);
        val = (msb << 2) | lsb;
    }
    else if(index == 1)
    {
        lsb = (val>>16) & 0x03;
        GetDevice()->ReadByte(0xE00E0F7C,msb);
        val = (msb << 2) | lsb;
    }
    return val;
}
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetCursorPosition(int index, int x, int y)
{
    if(index == 0)
    {
        WriteFormatPara(0xE00E0F70, 0, 11, x);
        WriteFormatPara(0xE00E0F70, 16, 11, y);
    }
    else if(index == 1)
    {
        WriteFormatPara(0xE00E0F78, 0, 11, x);
        WriteFormatPara(0xE00E0F78, 16, 11, y);
    }
} 
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::SetCursorColor(int index, Cursor_Color cl)
{
    if(index == 0)
    {
        WriteFormatPara(0xE00E0F74, 24, 3, cl);
    }
    else if(index == 1)
    {
        WriteFormatPara(0xE00E0F7C, 24, 3, cl);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::EnableRead(int index, bool enable)
{
    if(index == 0)
    {
        if(enable)
        {
            WriteFormatPara(0xE00E0F74, 31, 1, 1);
        }
        else
        {
            WriteFormatPara(0xE00E0F74, 31, 1, 0);
        }
    }
    else if(index == 1)
    {
        if(enable)
        {
            WriteFormatPara(0xE00E0F7C, 31, 1, 1);
        }
        else
        {
            WriteFormatPara(0xE00E0F7C, 31, 1, 0);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_ScanRGB::FormDestroy(TObject *Sender)
{
    delete resultList;

}
//---------------------------------------------------------------------------

void __fastcall TForm_ScanRGB::Button1Click(TObject *Sender)
{
    int step;
    int * result;
    
    PB->Position = 0;
    step = le_Step->Text.ToInt();
    //result = (int *)malloc((1024/step+1)*sizeof(int));
    PB->Max = (1024/step)*2;
    resultList->Clear();

    if(!MailBox_Available())    return;
    WriteFormatPara(0x9F020040, 2, 1, 1);//white balance on
    GetDevice()->WriteDWord(0xC00A00A0, 02020040);

    switch(cb_scanOption->ItemIndex)
    {
        case 0:
            scanRGBOut(step, CI_RGain , 0, resultList);
            scanRGBOut(step, CI_ROffset , 0, resultList);
        break;
        case 1:
            scanRGBOut(step, CI_GGain , 0, resultList);
            scanRGBOut(step, CI_GOffset , 0, resultList);
        break;
        case 2:
            scanRGBOut(step, CI_BGain , 0, resultList);
            scanRGBOut(step, CI_BOffset , 0, resultList);
        break;
        case 3:
            PB->Max = (1024/step)*6;
            scanRGBOut(step, CI_RGain , 0, resultList);
            scanRGBOut(step, CI_ROffset , 0, resultList);
            scanRGBOut(step, CI_GGain , 0, resultList);
            scanRGBOut(step, CI_GOffset , 0, resultList);
            scanRGBOut(step, CI_BGain , 0, resultList);
            scanRGBOut(step, CI_BOffset , 0, resultList);
        break;
    }

   // free(result);

}
//---------------------------------------------------------------------------
void __fastcall TForm_ScanRGB::scanRGBOut(int step,  int ColorIndex, int index, TStringList * sl )
{
    AnsiString strGain, strValue;
    int readOut;

    EnableRead(index, true);
    SetCursorColor(index,Cur_White);
    SetCursorPosition(index, 960, 540);
    SetDefaultRGB();


    switch (ColorIndex)
    {
      case 0:
        strGain = "RGain, ";
        strValue = "ROut, ";
        for(int i=0;i<1024;i+=step)
        {

            SetRGain(i);
            Sleep(10);
            readOut= readROut(index);
            strGain += IntToStr(i)+", ";
            strValue += IntToStr(readOut)+", ";
            PB->Position++;
        }
      break;
      case 1:
        strGain = "GGain, ";
        strValue = "GOut, ";
        for(int i=0;i<1024;i+=step)
        {
            SetGGain(i);
            Sleep(10);
            readOut= readGOut(index);
            strGain += IntToStr(i)+", ";
            strValue += IntToStr(readOut)+", ";
            PB->Position++;
        }
      break;
      case 2:
        strGain = "BGain, ";
        strValue = "BOut, ";
        for(int i=0;i<1024;i+=step)
        {
            SetBGain(i);
            Sleep(10);
            readOut= readBOut(index);
            strGain += IntToStr(i)+", ";
            strValue += IntToStr(readOut)+", ";
            PB->Position++;
        }
      break;
      case 3:
        strGain = "ROffset, ";
        strValue = "ROut, ";
        for(int i=0;i<1024;i+=step)
        {
            SetROffset(i);
            Sleep(10);
            readOut= readROut(index);
            strGain += IntToStr(i)+", ";
            strValue += IntToStr(readOut)+", ";
            PB->Position++;
        }
      break;
      case 4:
        strGain = "GOffset, ";
        strValue = "GOut, ";
        for(int i=0;i<1024;i+=step)
        {
            SetGOffset(i);
            Sleep(10);
            readOut= readGOut(index);
            strGain += IntToStr(i)+", ";
            strValue += IntToStr(readOut)+", ";
            PB->Position++;
        }
      break;
      case 5:
        strGain = "BOffset, ";
        strValue = "BOut, ";
        for(int i=0;i<1024;i+=step)
        {
            SetBOffset(i);
            Sleep(10);
            readOut= readBOut(index);
            strGain += IntToStr(i)+", ";
            strValue += IntToStr(readOut)+", ";
            PB->Position++;
        }
      break;
    }



    if(sl != NULL)
    {
        sl->Add(strGain);
        sl->Add(strValue);
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_ScanRGB::SaveClick(TObject *Sender)
{
    if(SaveDialog1->Execute())
    {
        resultList->SaveToFile(SaveDialog1->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_ScanRGB::Button2Click(TObject *Sender)
{
    SetDefaultRGB();    
}
//---------------------------------------------------------------------------


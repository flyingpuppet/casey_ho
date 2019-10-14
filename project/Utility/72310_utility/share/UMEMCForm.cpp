//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMEMCForm.h"
#include "RegLabeledEdit.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WinSkinStore"
#pragma link "WinSkinData"
#pragma resource "*.dfm"
TMEMCForm *MEMCForm;

I2CDevice * TMEMCForm::Device = NULL;
AnsiString TMEMCForm::mFilePath = "";
//---------------------------------------------------------------------------
__fastcall TMEMCForm::TMEMCForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMEMCForm::SetDevice(I2CDevice * dev)
{
    Device = dev;
}
//---------------------------------------------------------------------------
void __fastcall TMEMCForm::SetFilePath(AnsiString path)
{
    mFilePath = path;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMEMCForm::GetFilePath()
{
    return mFilePath;
}
//---------------------------------------------------------------------------
I2CDevice * __fastcall TMEMCForm::GetDevice()
{
    return Device;
}
//---------------------------------------------------------------------------

void __fastcall TMEMCForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    //Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TMEMCForm::LoadRegEditInfo(AnsiString * str)
{
    AnsiString s_addr, s_name, s_offset, s_start, s_bits;
    int i;
    TRegLabeledEdit * ed;

    i=0;
    s_addr=str[0];
    i++;
    while(str[i]!="EOF")
    {
        s_name = str[i];
        i++;
        s_offset = str[i];
        i++;
        s_start = str[i];
        i++;
        s_bits = str[i];
        i++;

        if(FindComponent(s_name)!= NULL)
        {
            ed = (TRegLabeledEdit *)FindComponent(s_name);
            ed->RegStartAddress = s_addr+s_offset;
            ed->RegStart = s_start.ToInt();
            ed->RegBits = s_bits.ToInt();
            ed->EditLabel->Caption = s_name;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMEMCForm::LoadPara(unsigned int * pi)
{
    for(int i=0; i<(int)pi[0]; i++)
    {
        switch(pi[i*3+1])
        {
            case 'D':
                GetDevice()->AllWriteDWord(pi[i*3+2], pi[i*3+3]);
            break;
            case 'B':
                GetDevice()->AllWriteByte(pi[i*3+2], (Byte)pi[i*3+3]);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMEMCForm::LoadFormatPara(unsigned int * pi)
{
    for(int i=0; i<(int)pi[0]; i++)
    {
        WriteFormatPara(pi[i*4+1],pi[i*4+2],pi[i*4+3],pi[i*4+4]);    
    }
}
//---------------------------------------------------------------------------
void __fastcall TMEMCForm::WriteFormatPara(unsigned int FAddress, unsigned int FstartBits, unsigned int FBits, unsigned int Value )
{
    unsigned int address, address2;
    unsigned int value,value2, tmp1, tmp2;
    int mode1,Bits1,Bits2;
    
    if(FBits>32)   return;
    value = Value;
    if(value >= pow(2,FBits))
    {
        value = pow(2,FBits)-1;
    }
    address = FAddress;

    mode1 = address % 4;
    if(mode1*8+FstartBits+FBits > 32)
    {
        Bits2 = mode1*8+FstartBits+FBits - 32;
        Bits1 = FBits-Bits2;
        address -= mode1;
        address2 = address + 4;
        GetDevice()->AllReadDWord(address, tmp1);
        GetDevice()->AllReadDWord(address2, tmp2);
        tmp1 &= (0xFFFFFFFF>>Bits1);
        tmp2 &= (0xFFFFFFFF<<Bits2);
        value2 = value>>Bits1;
        value = value<<(32-Bits1);
        tmp1 |= value;
        tmp2 |= value2;
        GetDevice()->AllWriteDWord(address, tmp1);
        GetDevice()->AllWriteDWord(address2, tmp2);
    }
    else
    {
        address -= mode1;
        Bits1 = FBits;
        GetDevice()->AllReadDWord(address, tmp1);
        tmp1 &= ~((0xFFFFFFFF<<(mode1*8+FstartBits))&(0xFFFFFFFF>>(32-mode1*8-FstartBits-FBits)));
        value = (value<<(mode1*8+FstartBits));
        tmp1 |= value;
        GetDevice()->AllWriteDWord(address, tmp1);
    }
}
//---------------------------------------------------------------------------
TRegEdit * __fastcall  TMEMCForm::Find(TRegScrollBar * rsb)
{
    TRegEdit * rle;
    int count;
    count = getconCount();//res[0].ToInt();
    for(int i=0;i<count;i++)
    {
        if(rsb->Name == getScrollName(i))
        {
            rle = (TRegEdit *)FindComponent(getEditName(i));
            return rle;
        }
    }
    return NULL;

}
//---------------------------------------------------------------------------
TRegScrollBar * __fastcall  TMEMCForm::Find(TRegEdit * rlb)
{
    TRegScrollBar * rsb;
    int count;
    count = getconCount();//res[0].ToInt();
    for(int i=0;i<count;i++)
    {
        if(rlb->Name == getEditName(i))
        {
            rsb = (TRegScrollBar *)FindComponent(getScrollName(i));
            return rsb;
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMEMCForm::getEditName(int i)
{
    return "";
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMEMCForm::getScrollName(int i)
{
    return "";
}
//---------------------------------------------------------------------------
int __fastcall TMEMCForm::getconCount()
{
    return 0;
}
//---------------------------------------------------------------------------
bool __fastcall TMEMCForm::MailBox_Available()
{
    unsigned int mailread;
    int i;
    for(i=0;i<10;i++)
    {
        GetDevice()->ReadDWord(0xC00A00A0, mailread);
        if(mailread == 0)
        {
            return true;
        }
    }
    if(i>=10)
    {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TMEMCForm::MailBox_SendAddress(unsigned int address)
{
    GetDevice()->WriteDWord(0xC00A00A0, address);
}
//---------------------------------------------------------------------------

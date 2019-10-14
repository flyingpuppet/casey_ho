//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMEMCFrame.h"
#include "UMEMCForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMEMCFrame *MEMCFrame;

I2CDevice * TMEMCFrame::Dev = NULL;
TStringGrid * TMEMCFrame::SG_Left = NULL;
TStringGrid * TMEMCFrame::SG_Right = NULL;
TStringList * TMEMCFrame::RefBuf = NULL;
int TMEMCFrame::Block = 0;
bool TMEMCFrame::m_bIs8BitFormat = false;
//---------------------------------------------------------------------------
__fastcall TMEMCFrame::TMEMCFrame(TComponent* Owner)
    : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMEMCFrame::SetDevice(I2CDevice * oDev)
{
    Dev = oDev;
}
//---------------------------------------------------------------------------
I2CDevice * __fastcall TMEMCFrame::GetDevice()
{
    return Dev;
}
//---------------------------------------------------------------------------
void __fastcall TMEMCFrame::LoadMeasurePar(AnsiString * strs)
{
    AnsiString s_count, s_add, s_value, s_sta;
    int v_count;

    s_count = strs[0];
    v_count = s_count.ToInt();
    for(int i=0;i<v_count;i++)
    {
        s_sta = strs[3*i+1];
        s_add = strs[3*i+2];
        s_value = strs[3*i+3];
        if(s_sta == "B")
        {
            GetDevice()->WriteByte((unsigned int)s_add.ToInt(),
                (Byte)s_value.ToInt());
        }
        else
        if(s_sta == "D")
        {
            GetDevice()->WriteDWord((unsigned int)s_add.ToInt(),
                (unsigned int)s_value.ToInt());
        }
    }
}
//---------------------------------------------------------------------------
unsigned int __fastcall TMEMCFrame::MakeAddress(unsigned int b, int p, int r)
{
    return (unsigned int)((b<<16) | (p<<8) | r);
}
//---------------------------------------------------------------------------
unsigned int __fastcall TMEMCFrame::MakeAddress(AnsiString sb, AnsiString sp, AnsiString sr)
{
    unsigned int b;
    int p, r;
    try
    {
        b = (unsigned int)sb.ToInt();
        p = (int)sp.ToInt();
        r = (int)sr.ToInt();
        return MakeAddress(b, p, r);
    }
    catch(...)
    {
        return 0;
    }


}
//---------------------------------------------------------------------------
void __fastcall TMEMCFrame::FillStringGrid(TStringGrid * sg, TStringList* sl,
    AnsiString block)
{
    AnsiString buf;
    int blockCount;

    blockCount = block.ToInt();
    FillStringGrid(sg, sl, blockCount);
}
//---------------------------------------------------------------------------
void __fastcall TMEMCFrame::FillStringGrid(TStringGrid * sg, TStringList* sl,
    int block)
{
    AnsiString buf;

    SetBlock(block);
    
    if(sl == NULL)
    {
        return;
    }
    if(block*16 > sl->Count-1)
    {
        return;
    }
    for(int i=0; i<16; i++)
    {
        buf = sl->Strings[block*16+i];
        if( (buf.SubString(1, 2) == ":1")&&(buf.SubString(7, 3) == "000") )
        {
            buf.Delete(1, 9);
            for(int j=0; j<16; j++)
            {
                sg->Cells[j][i] = buf.SubString(2*j+1, 2);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMEMCFrame::SetLeftGrid(TStringGrid * sg)
{
    SG_Left = sg;
}
//---------------------------------------------------------------------------
void __fastcall TMEMCFrame::SetRightGrid(TStringGrid * sg)
{
    SG_Right = sg;
}
//---------------------------------------------------------------------------
TStringGrid * __fastcall TMEMCFrame::GetLeftGrid()
{
    return SG_Left;
}
//---------------------------------------------------------------------------
TStringGrid * __fastcall TMEMCFrame::GetRightGrid()
{
    return SG_Right;
}
//---------------------------------------------------------------------------
void __fastcall TMEMCFrame::SetBlock(int b)
{
    Block = b;    
}
//---------------------------------------------------------------------------
int __fastcall TMEMCFrame::GetBlock()
{
    return Block;    
}
//---------------------------------------------------------------------------
void __fastcall TMEMCFrame::LoadPara(unsigned int * pi)
{
    /*for(int i=0; i<(int)pi[0]; i++)
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
    }*/
    MEMCForm->LoadPara(pi);
}
void __fastcall TMEMCFrame::LoadFormatPara(unsigned int * pi)
{
    /*for(int i=0; i<(int)pi[0]; i++)
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
    }*/
    MEMCForm->LoadFormatPara(pi);
}
//---------------------------------------------------------------------------

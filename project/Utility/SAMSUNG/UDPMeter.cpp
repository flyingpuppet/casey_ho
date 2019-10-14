//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UDPMeter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegEdit"
#pragma link "RegLabeledEdit"
#pragma link "RegScrollBar"
#pragma resource "*.dfm"

AnsiString TForm_DPMeter::conres[]=
{
    "7",
    "RegScrollBar1", "RegEdit1" ,
    "RegScrollBar2", "RegEdit2" ,
    "RegScrollBar3", "RegEdit3" ,
    "RegScrollBar4", "RegEdit4" ,
    "RegScrollBar5", "RegEdit5" ,
    "RegScrollBar6", "RegEdit6" ,
    "RegScrollBar7", "RegEdit7" ,
};
TForm_DPMeter *Form_DPMeter;
//---------------------------------------------------------------------------
__fastcall TForm_DPMeter::TForm_DPMeter(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_DPMeter::RegEdit3Exit(TObject *Sender)
{
    Byte msb, lsb;
    unsigned int val;
    TRegEdit * re;
    
    re = (TRegEdit *)Sender;
    
    /*GetDevice()->ReadByte(0xE0000143, val);
    msb = (val>>(re->Tag*2)) && 0x03;
    re->Refresh();
    re->Text = IntToStr((msb << 8) | (re->Text.ToInt()));*/
    val = re->Text.ToInt();
    msb = (val >> 8) & 0x03;
    lsb = val & 0xFF;

    WriteFormatPara((unsigned int)re->RegStartAddress.ToInt(), re->RegStart, re->RegBits, lsb);
    WriteFormatPara(0xE0000143, re->Tag*2, 2, msb);

    Find(re)->Position = re->Text.ToInt(); 
}
//---------------------------------------------------------------------------
void __fastcall TForm_DPMeter::RegEdit1Exit(TObject *Sender)
{
    Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();
    refreshRGB(((TRegEdit * )Sender)->Tag);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DPMeter::RegEdit1KeyPress(TObject *Sender, char &Key)
{
    if(Key == 13)
    {
        Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();
        refreshRGB(((TRegEdit * )Sender)->Tag); 
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm_DPMeter::RegScrollBar1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    if(ScrollCode == scEndScroll)
    {
        Find((TRegScrollBar * )Sender)->Text = IntToStr(ScrollPos);
        refreshRGB(((TRegScrollBar * )Sender)->Tag);
    }


}
//---------------------------------------------------------------------------
void __fastcall TForm_DPMeter::refreshData(TRegLabeledEdit * re)
{
    unsigned int val;
    Byte msb;
    Byte lsb;
    GetDevice()->ReadDWord(0xE00E0F80, val);
    lsb = (val>>(re->Tag*4)) & 0x03;
    GetDevice()->ReadByte((unsigned int)re->RegStartAddress.ToInt(),msb);
    re->Text = IntToStr((msb << 2) | lsb);    
}
//---------------------------------------------------------------------------
void __fastcall TForm_DPMeter::refreshRGB(int index)
{
    if(index == 0)
    {
        refreshData(rle_R0);//->Refresh();
        refreshData(rle_G0);//->Refresh();
        refreshData(rle_B0);//->Refresh();
    }
    else if(index == 1)
    {
        refreshData(rle_R1);//->Refresh();
        refreshData(rle_G1);//->Refresh();
        refreshData(rle_B1);//->Refresh();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_DPMeter::cb_IPPatternClick(TObject *Sender)
{
    if(cb_IPPattern->Checked)
    {
        GetDevice()->WriteByte(0xE000013C,0x11);
    }
    else
    {
        GetDevice()->WriteByte(0xE000013C,0x00);   
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_DPMeter::RegScrollBar3Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    Byte msb, lsb;
    TRegScrollBar * rsb;
    if(ScrollCode == scEndScroll)
    {
        rsb = (TRegScrollBar *)Sender;
        
        msb = (ScrollPos>>8) & 0x03;
        lsb = ScrollPos & 0xFF;
        
        WriteFormatPara((unsigned int)rsb->RegStartAddress.ToInt(), rsb->RegStart, rsb->RegBits, lsb);
        WriteFormatPara(0xE0000143, rsb->Tag*2, 2, msb);
        
        Find((TRegScrollBar * )Sender)->Text = IntToStr(ScrollPos);
    }    
}
//---------------------------------------------------------------------------

void __fastcall TForm_DPMeter::RegEdit3KeyPress(TObject *Sender, char &Key)
{
    Byte msb, lsb;
    unsigned int val;
    TRegEdit * re;


    if(Key == 13)
    {
        re = (TRegEdit *)Sender;

        /*GetDevice()->ReadByte(0xE0000143, val);
        msb = (val>>(re->Tag*2)) && 0x03;
        re->Refresh();
        re->Text = IntToStr((msb << 8) | (re->Text.ToInt()));*/

        val = re->Text.ToInt();
        msb = (val >> 8) & 0x03;
        lsb = val & 0xFF;

        WriteFormatPara((unsigned int)re->RegStartAddress.ToInt(), re->RegStart, re->RegBits, lsb);
        WriteFormatPara(0xE0000143, re->Tag*2, 2, msb);

        Find(re)->Position = re->Text.ToInt();
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_DPMeter::Button1Click(TObject *Sender)
{
    unsigned int val;
    Byte bval;

    GetDevice()->ReadByte(0xE000013C, bval);
    GetDevice()->ReadDWord(0xE0000140, val);

    if((bval&0x10) == 0x10)
    {
        cb_IPPattern->Checked = true;
    }
    else
    {
        cb_IPPattern->Checked = false;
    }

    RegScrollBar3->Position = (((val>>24)&0x03)<<8) | (val & 0xFF);
    RegScrollBar4->Position = (((val>>26)&0x03)<<8) | ((val >> 8) & 0xFF);
    RegScrollBar5->Position = (((val>>28)&0x03)<<8) | ((val >> 16) & 0xFF);

    RegEdit3->Text = IntToStr(RegScrollBar3->Position);
    RegEdit4->Text = IntToStr(RegScrollBar4->Position);
    RegEdit5->Text = IntToStr(RegScrollBar5->Position);

    rcb_Cur0->Refresh();
    rcb_Cur1->Refresh();
    
    RegScrollBar1->Refresh();
    RegEdit1->Refresh();
    RegScrollBar2->Refresh();
    RegEdit2->Refresh();

    RegScrollBar6->Refresh();
    RegEdit6->Refresh();
    RegScrollBar7->Refresh();
    RegEdit7->Refresh();

    refreshData(rle_R0);//->Refresh();
    refreshData(rle_G0);//->Refresh();
    refreshData(rle_B0);//->Refresh();

    refreshData(rle_R1);//->Refresh();
    refreshData(rle_G1);//->Refresh();
    refreshData(rle_B1);//->Refresh();
}
//---------------------------------------------------------------------------
int __fastcall TForm_DPMeter::getconCount()
{
    int i;
    i = conres[0].ToInt();
    return i;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_DPMeter::getEditName(int i)
{
    return conres[2*i+2];
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_DPMeter::getScrollName(int i)
{
    return conres[2*i+1];
}
//---------------------------------------------------------------------------



void __fastcall TForm_DPMeter::FormShow(TObject *Sender)
{
    WriteFormatPara(0xE00E0F74,24,3,0x7);
    WriteFormatPara(0xE00E0F7C,24,3,0x6);        
}
//---------------------------------------------------------------------------


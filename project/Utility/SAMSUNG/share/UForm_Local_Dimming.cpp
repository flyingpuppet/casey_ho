//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_Local_Dimming.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegEdit"
#pragma link "RegScrollBar"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TForm_Local_Dimming *Form_Local_Dimming;
AnsiString TForm_Local_Dimming::conres[]=
{
    "15",
    "RegScrollBar1", "RegEdit1" ,
    "RegScrollBar2", "RegEdit2" ,
    "RegScrollBar3", "RegEdit3" ,
    "RegScrollBar4", "RegEdit4" ,
    "RegScrollBar5", "RegEdit5" ,
    "RegScrollBar6", "RegEdit6" ,
    "RegScrollBar7", "RegEdit7" ,
    "RegScrollBar8", "RegEdit8" ,
    "RegScrollBar9", "RegEdit9" ,
    "RegScrollBar10", "RegEdit10" ,
    "RegScrollBar11", "RegEdit11" ,
    "RegScrollBar12", "RegEdit12" ,
    "RegScrollBar13", "RegEdit13" ,
    "RegScrollBar14", "RegEdit14" ,
    "RegScrollBar15", "RegEdit15" ,
};
//---------------------------------------------------------------------------
__fastcall TForm_Local_Dimming::TForm_Local_Dimming(TComponent* Owner)
    : TMEMCForm(Owner)
{
    
}
//---------------------------------------------------------------------------
void __fastcall TForm_Local_Dimming::Button2Click(TObject *Sender)
{
    TRegLabeledEdit * rle;
    for(int i =0;i<GB_DUTY_BLU->ControlCount;i++)
    {
        if(GB_DUTY_BLU->Controls[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *) GB_DUTY_BLU->Controls[i];
            rle->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::RegScrollBar1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    if(ScrollCode == scEndScroll)
    {
        Find((TRegScrollBar * )Sender)->Text = IntToStr(ScrollPos);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::RegEdit1KeyPress(TObject *Sender,
      char &Key)
{
    if(Key == 13)
    {
        Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::Button1Click(TObject *Sender)
{
    AnsiString conName;

    TRegLabeledEdit * rle;
    TRegCheckBox * rcb;
    TRegScrollBar * rsb;
    TRegEdit * re;


    for(int i=0;i<this->ComponentCount;i++)
    {
        conName = this->Components[i]->ClassName();
        if(conName=="TRegEdit")
        {
            re = (TRegEdit *)this->Components[i];
            re->Refresh();
        }
        if(conName=="TRegCheckBox")
        {
            rcb = (TRegCheckBox *)this->Components[i];
            rcb->Refresh();
        }
        if(conName=="TRegLabeledEdit")
        {
            rle = (TRegLabeledEdit *)this->Components[i];
            rle->Refresh();
        }
        if(conName=="TRegScrollBar")
        {
            rsb = (TRegScrollBar *)this->Components[i];
            rsb->Refresh();
        }
    }

    sb_AOS_TH->Position = re_AOS_TH_H->Text.ToInt() * 256 + re_AOS_TH_L->Text.ToInt();
    ed_AOS_TH->Text =  IntToStr(sb_AOS_TH->Position);

    sb_AOS_PX->Position = re_AOS_PX_H->Text.ToInt() * 256 + re_AOS_PX_L->Text.ToInt();
    ed_AOS_PX->Text =  IntToStr(sb_AOS_PX->Position);

}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::sb_AOS_THScroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    if(ScrollCode == scEndScroll)
    {
        ed_AOS_TH->Text = IntToStr(ScrollPos);

        WriteFormatPara(0xE00802E9, 0, 8, ScrollPos / 256);
        WriteFormatPara(0xE00802EA, 0, 8, ScrollPos % 256);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::sb_AOS_PXScroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    if(ScrollCode == scEndScroll)
    {
        ed_AOS_PX->Text = IntToStr(ScrollPos);

        WriteFormatPara(0xE00802D0, 0, 8, ScrollPos / 256);
        WriteFormatPara(0xE00802D1, 0, 8, ScrollPos % 256);
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_Local_Dimming::ed_AOS_THKeyPress(TObject *Sender,
      char &Key)
{
    if(Key == 13)
    {
        sb_AOS_TH->Position = ed_AOS_TH->Text.ToInt();

        WriteFormatPara(0xE00802E9, 0, 8, sb_AOS_TH->Position/256);
        WriteFormatPara(0xE00802EA, 0, 8, sb_AOS_TH->Position%256);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::ed_AOS_PXKeyPress(TObject *Sender,
      char &Key)
{
    if(Key == 13)
    {
        sb_AOS_PX->Position = ed_AOS_PX->Text.ToInt();

        WriteFormatPara(0xE00802D0, 0, 8, sb_AOS_PX->Position/256);
        WriteFormatPara(0xE00802D1, 0, 8, sb_AOS_PX->Position%256);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::RegEdit1Exit(TObject *Sender)
{
    Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::ed_AOS_THExit(TObject *Sender)
{
    sb_AOS_TH->Position = ed_AOS_TH->Text.ToInt();

    WriteFormatPara(0xE00802E9, 0, 8, sb_AOS_TH->Position/256);
    WriteFormatPara(0xE00802EA, 0, 8, sb_AOS_TH->Position%256);
}
//---------------------------------------------------------------------------

void __fastcall TForm_Local_Dimming::ed_AOS_PXExit(TObject *Sender)
{
    sb_AOS_PX->Position = ed_AOS_PX->Text.ToInt();

    WriteFormatPara(0xE00802D0, 0, 8, sb_AOS_PX->Position/256);
    WriteFormatPara(0xE00802D1, 0, 8, sb_AOS_PX->Position%256);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_Local_Dimming::getEditName(int i)
{
    return conres[2*i+2];
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_Local_Dimming::getScrollName(int i)
{
    return conres[2*i+1];
}
//---------------------------------------------------------------------------
int __fastcall TForm_Local_Dimming::getconCount()
{
    int i;
    i = conres[0].ToInt();
    return i;
}
//---------------------------------------------------------------------------



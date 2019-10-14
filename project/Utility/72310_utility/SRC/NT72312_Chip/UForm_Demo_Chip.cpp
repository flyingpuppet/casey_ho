//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_Demo_Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma link "RegScrollBar"
#pragma link "RegEdit"
#pragma resource "*.dfm"
TForm_Demo_Chip *Form_Demo_Chip;

AnsiString TForm_Demo_Chip::conres[]=
{
    "32",
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
    "RegScrollBar16", "RegEdit16" ,
    "RegScrollBar17", "RegEdit17" ,
    "RegScrollBar18", "RegEdit18" ,
    "RegScrollBar19", "RegEdit19" ,
    "RegScrollBar20", "RegEdit20" ,
    "RegScrollBar21", "RegEdit21" ,
    "RegScrollBar22", "RegEdit22" ,
    "RegScrollBar23", "RegEdit23" ,
    "RegScrollBar24", "RegEdit24" ,
    "RegScrollBar25", "RegEdit25" ,
    "RegScrollBar26", "RegEdit26" ,
    "RegScrollBar27", "RegEdit27" ,
    "RegScrollBar28", "RegEdit28" ,
    "RegScrollBar29", "RegEdit29" ,
    "RegScrollBar30", "RegEdit30" ,
    "RegScrollBar31", "RegEdit31" ,
    "RegScrollBar32", "RegEdit32" ,
};

unsigned int TForm_Demo_Chip::DemoWin[4][4]=
{
    {0,0,960,1080,},    //L
    {960,0,1920,1080},  //R
    {0,0,1920,540,},    //T
    {0,540,1920,1080,}, //B
};
//---------------------------------------------------------------------------
__fastcall TForm_Demo_Chip::TForm_Demo_Chip(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
int __fastcall TForm_Demo_Chip::getconCount()
{
    int i;
    i = conres[0].ToInt();
    return i;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_Demo_Chip::getEditName(int i)
{
    return conres[2*i+2];
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_Demo_Chip::getScrollName(int i)
{
    return conres[2*i+1];
}
//---------------------------------------------------------------------------
void __fastcall TForm_Demo_Chip::RegScrollBar1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    if(ScrollCode == scEndScroll)
    {
        Find((TRegScrollBar * )Sender)->Text = IntToStr(ScrollPos);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Demo_Chip::RegEdit1Exit(TObject *Sender)
{
    Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();    
}
//---------------------------------------------------------------------------
void __fastcall TForm_Demo_Chip::RegEdit1KeyPress(TObject *Sender,
      char &Key)
{
    if(Key == 13)
    {
        Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();
    }    
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::RadioButton33Click(TObject *Sender)
{
    //
    TRadioButton * rb;
    rb = (TRadioButton *)Sender;
    switch(rb->Tag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            WriteFormatPara(0xE000025D, 0 , 11, DemoWin[rb->Tag][0]);
            WriteFormatPara(0xE000025E, 5 , 11, DemoWin[rb->Tag][1]);
            WriteFormatPara(0xE0000260, 0 , 11, DemoWin[rb->Tag][2]);
            WriteFormatPara(0xE0000261, 5 , 11, DemoWin[rb->Tag][3]);
            btn_win0->Click();
        break;
        case 4:
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::btn_win0Click(TObject *Sender)
{
    AnsiString conName;

    TRegLabeledEdit * rle;
    TRegCheckBox * rcb;
    TRegScrollBar * rsb;
    TRegEdit * re;

    TGroupBox * gb;
    TButton * btn;

    btn = (TButton *)Sender;
    gb = (TGroupBox *)btn->Parent;

    //gb = (TComponent *)Sender->

    for(int i=0;i<gb->ControlCount;i++)
    {
        conName = gb->Controls[i]->ClassName();
        //ShowMessage(conName);
        if(conName=="TRegEdit")
        {
            re = (TRegEdit *)gb->Controls[i];
            re->Refresh();
        }
        if(conName=="TRegCheckBox")
        {
            rcb = (TRegCheckBox *)gb->Controls[i];
            rcb->Refresh();
        }
        if(conName=="TRegLabeledEdit")
        {
            rle = (TRegLabeledEdit *)gb->Controls[i];
            rle->Refresh();
        }
        if(conName=="TRegScrollBar")
        {
            rsb = (TRegScrollBar *)gb->Controls[i];
            rsb->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::RadioButton3Click(TObject *Sender)
{
    TRadioButton * rb;
    rb = (TRadioButton *)Sender;
    switch(rb->Tag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            WriteFormatPara(0xE0000264, 0 , 11, DemoWin[rb->Tag][0]);
            WriteFormatPara(0xE0000265, 5 , 11, DemoWin[rb->Tag][1]);
            WriteFormatPara(0xE0000268, 0 , 11, DemoWin[rb->Tag][2]);
            WriteFormatPara(0xE0000269, 5 , 11, DemoWin[rb->Tag][3]);
            btn_win1->Click();
        break;
        case 4:
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::RadioButton7Click(TObject *Sender)
{
    TRadioButton * rb;
    rb = (TRadioButton *)Sender;
    switch(rb->Tag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            WriteFormatPara(0xE000026C, 0 , 11, DemoWin[rb->Tag][0]);
            WriteFormatPara(0xE000026D, 5 , 11, DemoWin[rb->Tag][1]);
            WriteFormatPara(0xE0000270, 0 , 11, DemoWin[rb->Tag][2]);
            WriteFormatPara(0xE0000271, 5 , 11, DemoWin[rb->Tag][3]);
            btn_win2->Click();
        break;
        case 4:
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::RadioButton11Click(TObject *Sender)
{
    TRadioButton * rb;
    rb = (TRadioButton *)Sender;
    switch(rb->Tag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            WriteFormatPara(0xE0000274, 0 , 11, DemoWin[rb->Tag][0]);
            WriteFormatPara(0xE0000275, 5 , 11, DemoWin[rb->Tag][1]);
            WriteFormatPara(0xE0000278, 0 , 11, DemoWin[rb->Tag][2]);
            WriteFormatPara(0xE0000279, 5 , 11, DemoWin[rb->Tag][3]);
            btn_win3->Click();
        break;
        case 4:
        break;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::RadioButton15Click(TObject *Sender)
{
    TRadioButton * rb;
    rb = (TRadioButton *)Sender;
    switch(rb->Tag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            WriteFormatPara(0xE000027C, 0 , 11, DemoWin[rb->Tag][0]);
            WriteFormatPara(0xE000027D, 5 , 11, DemoWin[rb->Tag][1]);
            WriteFormatPara(0xE0000280, 0 , 11, DemoWin[rb->Tag][2]);
            WriteFormatPara(0xE0000281, 5 , 11, DemoWin[rb->Tag][3]);
            btn_win4->Click();
        break;
        case 4:
        break;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::RadioButton21Click(TObject *Sender)
{
    TRadioButton * rb;
    rb = (TRadioButton *)Sender;
    switch(rb->Tag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            WriteFormatPara(0xE0000284, 0 , 11, DemoWin[rb->Tag][0]);
            WriteFormatPara(0xE0000285, 5 , 11, DemoWin[rb->Tag][1]);
            WriteFormatPara(0xE0000288, 0 , 11, DemoWin[rb->Tag][2]);
            WriteFormatPara(0xE0000289, 5 , 11, DemoWin[rb->Tag][3]);
            btn_win5->Click();
        break;
        case 4:
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::RadioButton25Click(TObject *Sender)
{
    TRadioButton * rb;
    rb = (TRadioButton *)Sender;
    switch(rb->Tag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            WriteFormatPara(0xE000028C, 0 , 11, DemoWin[rb->Tag][0]);
            WriteFormatPara(0xE000028D, 5 , 11, DemoWin[rb->Tag][1]);
            WriteFormatPara(0xE0000290, 0 , 11, DemoWin[rb->Tag][2]);
            WriteFormatPara(0xE0000291, 5 , 11, DemoWin[rb->Tag][3]);
            btn_win6->Click();
        break;
        case 4:
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::RadioButton29Click(TObject *Sender)
{
    TRadioButton * rb;
    rb = (TRadioButton *)Sender;
    switch(rb->Tag)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            WriteFormatPara(0xE0000294, 0 , 11, DemoWin[rb->Tag][0]);
            WriteFormatPara(0xE0000295, 5 , 11, DemoWin[rb->Tag][1]);
            WriteFormatPara(0xE0000298, 0 , 11, DemoWin[rb->Tag][2]);
            WriteFormatPara(0xE0000299, 5 , 11, DemoWin[rb->Tag][3]);
            btn_win7->Click();
        break;
        case 4:
        break;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_Demo_Chip::FormShow(TObject *Sender)
{
//
    /*AnsiString conName;

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
    }     */
}
//---------------------------------------------------------------------------

void __fastcall TForm_Demo_Chip::Button1Click(TObject *Sender)
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
}
//---------------------------------------------------------------------------


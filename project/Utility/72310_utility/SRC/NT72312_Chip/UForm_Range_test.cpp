//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_Range_test.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RegCheckBox"
#pragma link "RegScrollBar"
#pragma link "UMEMCForm"
#pragma link "RegEdit"
#pragma link "RegRadioButton"
#pragma resource "*.dfm"
TForm_Range_test *Form_Range_test;

AnsiString TForm_Range_test::conres[]=
{
    "8",
    "RegScrollBar1", "RegEdit1" ,
    "RegScrollBar2", "RegEdit2" ,
    "RegScrollBar3", "RegEdit3" ,
    "RegScrollBar4", "RegEdit4" ,
    "RegScrollBar5", "RegEdit5" ,
    "RegScrollBar6", "RegEdit6" ,
    "RegScrollBar7", "RegEdit7" ,
    "RegScrollBar8", "RegEdit8" ,
};
//---------------------------------------------------------------------------
__fastcall TForm_Range_test::TForm_Range_test(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_Range_test::getEditName(int i)
{
    return conres[2*i+2];
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_Range_test::getScrollName(int i)
{
    return conres[2*i+1];
}
//---------------------------------------------------------------------------
int __fastcall TForm_Range_test::getconCount()
{
    int i;
    i = conres[0].ToInt();
    return i;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Range_test::RegScrollBar1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    TRegScrollBar * rsb;
    TEdit * ed;
    double dd;
    AnsiString str;

    if(ScrollCode == scEndScroll)
    {
        rsb = (TRegScrollBar * )Sender;
        Find(rsb)->Text = IntToStr(ScrollPos);
        if(rsb->Tag != 0)
        {
            dd = ScrollPos / 4.0;
            str.printf("%.2f", dd);
            ed = (TEdit *)FindComponent("Edit"+IntToStr(rsb->Tag));
            ed->Text = str;
        }
    }    
}
//---------------------------------------------------------------------------
void __fastcall TForm_Range_test::RegEdit1Exit(TObject *Sender)
{
    TRegEdit * re;
    TEdit * ed;
    double dd;
    AnsiString str;

    re = (TRegEdit * )Sender;
    Find(re)->Position = re->Text.ToInt();
    if(re->Tag != 0)
    {
        dd = re->Text.ToInt() / 4.0;
        str.printf("%.2f", dd);
        ed = (TEdit *)FindComponent("Edit"+IntToStr(re->Tag));
        ed->Text = str;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Range_test::RegEdit1KeyPress(TObject *Sender,
      char &Key)
{
    TRegEdit * re;
    TEdit * ed;
    double dd;
    AnsiString str;
    
    if(Key == 13)
    {
        re = (TRegEdit * )Sender;
        Find(re)->Position = re->Text.ToInt();
        if(re->Tag != 0)
        {
            dd = re->Text.ToInt() / 4.0;
            str.printf("%.2f", dd);
            ed = (TEdit *)FindComponent("Edit"+IntToStr(re->Tag));
            ed->Text = str;
        }
    }    
}
//---------------------------------------------------------------------------
void __fastcall TForm_Range_test::Button1Click(TObject *Sender)
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


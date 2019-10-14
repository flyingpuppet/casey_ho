//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_BandWidth.h"
#include "UFrame_BWMeasure_312Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegEdit"
#pragma link "RegScrollBar"
#pragma link "RegCheckBox"
#pragma resource "*.dfm"
TForm_BandWidth *Form_BandWidth;

AnsiString TForm_BandWidth::conres[]=
{
    "46",
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
    "RegScrollBar33", "RegEdit33" ,
    "RegScrollBar34", "RegEdit34" ,
    "RegScrollBar35", "RegEdit35" ,
    "RegScrollBar36", "RegEdit36" ,
    "RegScrollBar37", "RegEdit37" ,
    "RegScrollBar38", "RegEdit38" ,
    "RegScrollBar39", "RegEdit39" ,
    "RegScrollBar40", "RegEdit40" ,
    "RegScrollBar41", "RegEdit41" ,
    "RegScrollBar42", "RegEdit42" ,
    "RegScrollBar43", "RegEdit43" ,
    "RegScrollBar44", "RegEdit44" ,
    "RegScrollBar45", "RegEdit45" ,
    "RegScrollBar46", "RegEdit46" ,
};
//---------------------------------------------------------------------------
__fastcall TForm_BandWidth::TForm_BandWidth(TComponent* Owner)
    : TMEMCForm(Owner)
{
    Frame_BWMeasure_312Chip = new TFrame_BWMeasure_312Chip(this);
    Frame_BWMeasure_312Chip->Parent = this->Panel1;
    Frame_BWMeasure_312Chip->Align = alClient;
    Frame_BWMeasure_312Chip->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_BandWidth::RegScrollBar1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    //
    if(ScrollCode == scEndScroll)
    {
        Find((TRegScrollBar * )Sender)->Text = IntToStr(ScrollPos);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_BandWidth::RegEdit1KeyPress(TObject *Sender,
      char &Key)
{
    //
    if(Key == 13)
    {
        Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_BandWidth::RegEdit1Exit(TObject *Sender)
{
    //
    Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();   
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_BandWidth::getEditName(int i)
{
    return conres[2*i+2];
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm_BandWidth::getScrollName(int i)
{
    return conres[2*i+1];
}
//---------------------------------------------------------------------------
int __fastcall TForm_BandWidth::getconCount()
{
    int i;
    i = conres[0].ToInt();
    return i;
}
//---------------------------------------------------------------------------
void __fastcall TForm_BandWidth::refreshClick(TObject *Sender)
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

void __fastcall TForm_BandWidth::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    delete Frame_BWMeasure_312Chip;
}
//---------------------------------------------------------------------------


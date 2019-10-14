//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_ME_2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TForm_ME_2 *Form_ME_2;
//---------------------------------------------------------------------------
__fastcall TForm_ME_2::TForm_ME_2(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm_ME_2::btnRefreshClick(TObject *Sender)
{
//
    TRegCheckBox * rcb;
    TRegLabeledEdit * rle;

    for(int i=0; i<this->ComponentCount; i++)
    {
        if(this->Components[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)this->Components[i];
            rle->Refresh();
        }
        if(this->Components[i]->ClassNameIs("TRegCheckBox"))
        {
            rcb = (TRegCheckBox *)this->Components[i];
            rcb->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_ME_2::ComboBox1Change(TObject *Sender)
{
    TComboBox * cb;
    Byte val;

    cb = (TComboBox *)Sender;
    switch(cb->ItemIndex)
    {
        case 0:
            val = 0;
        break;
        case 1:
            val = 0x55;
        break;
        case 2:
            val = 0xAA;
        break;
        case 3:
            val = 0xFF;
        break;
    }

    //val = (cb->ItemIndex<<6) | (cb->ItemIndex<<4) | (cb->ItemIndex<<2) | cb->ItemIndex;
    GetDevice()->WriteByte(0xE0000900,val);
}
//---------------------------------------------------------------------------


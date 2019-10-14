//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_ME_3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TForm_ME_3 *Form_ME_3;
//---------------------------------------------------------------------------
__fastcall TForm_ME_3::TForm_ME_3(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_ME_3::Button1Click(TObject *Sender)
{
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


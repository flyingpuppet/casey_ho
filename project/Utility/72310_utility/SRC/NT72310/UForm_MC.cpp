//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_MC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TForm_MC *Form_MC;
//---------------------------------------------------------------------------
__fastcall TForm_MC::TForm_MC(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm_MC::Button1Click(TObject *Sender)
{
    TRegLabeledEdit * ed;
    TRegCheckBox * cb;
    AnsiString conName;
    for(int i=0;i<ComponentCount;i++)
    {
        conName = Components[i]->ClassName();
        if(conName == "TRegLabeledEdit")
        {
            ed = (TRegLabeledEdit *)Components[i];
            ed->Refresh();
        }
        if(conName == "TRegCheckBox")
        {
            cb = (TRegCheckBox *)Components[i];
            cb->Refresh();
        }
    }
}
//---------------------------------------------------------------------------


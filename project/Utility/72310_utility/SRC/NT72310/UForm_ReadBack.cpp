//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_ReadBack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TForm_ReadBack *Form_ReadBack;
//---------------------------------------------------------------------------
__fastcall TForm_ReadBack::TForm_ReadBack(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_ReadBack::Button1Click(TObject *Sender)
{
    TRegLabeledEdit * ed;

    AnsiString conName;
    for(int i=0;i<ComponentCount;i++)
    {
        conName = Components[i]->ClassName();
        if(conName == "TRegLabeledEdit")
        {
            ed = (TRegLabeledEdit *)Components[i];
            ed->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

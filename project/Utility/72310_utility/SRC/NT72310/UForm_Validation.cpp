//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_Validation.h"
#include "UFrame_DataPath.h"
#include "UFrame_BWMeasure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegLabeledEdit"
#pragma link "RegEdit"
#pragma link "RegScrollBar"
#pragma resource "*.dfm"
TForm_Validation *Form_Validation;
//---------------------------------------------------------------------------
__fastcall TForm_Validation::TForm_Validation(TComponent* Owner)
    : TMEMCForm(Owner)
{
    Frame_BWMeasure = new TFrame_BWMeasure(this);
    Frame_DataPath = new TFrame_DataPath(this);
    Frame_BWMeasure->Parent = this->pl_right;
    Frame_DataPath->Parent = this->pl_left;
    Frame_DataPath->Align = alClient;
    Frame_BWMeasure->Align = alClient;
    Frame_BWMeasure->Show();
    Frame_DataPath->Show();

}
//---------------------------------------------------------------------------
void __fastcall TForm_Validation::Button2Click(TObject *Sender)
{
    TRegLabeledEdit * ed;
    TRegScrollBar * sb;
    TRegEdit * eed;
    TButton * btn;
    TGroupBox * gb;

    btn = (TButton *)Sender;
    //ShowMessage(btn->Parent->Name);
    for(int i=0;i<btn->Parent->ControlCount;i++)
    {
        if(btn->Parent->Controls[i]->ClassNameIs("TGroupBox"))
        {

            gb = (TGroupBox *)btn->Parent->Controls[i];
            //ShowMessage(gb->Name);
            for(int j=0;j<gb->ControlCount;j++)
            {
                 //ShowMessage(gb->Controls[i]->ClassName());

                if(gb->Controls[j]->ClassNameIs("TRegLabeledEdit"))
                {
                    ed = (TRegLabeledEdit *)gb->Controls[j];
                   //ShowMessage(ed->Name);
                    //ShowMessage(ed->RegStartAddress);
                    ed->Refresh();
                }
                if(gb->Controls[j]->ClassNameIs("TRegScrollBar"))
                {
                    sb = (TRegScrollBar *)gb->Controls[j];
                    //ShowMessage(sb->Name);
                    //ShowMessage(sb->RegStartAddress);
                    sb->Refresh();
                }
                if(gb->Controls[j]->ClassNameIs("TRegEdit"))
                {
                    eed = (TRegEdit *)gb->Controls[j];
                    //ShowMessage(sb->Name);
                    //ShowMessage(sb->RegStartAddress);
                    eed->Refresh();
                }
            }
        }

    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Validation::RegScrollBar17Change(TObject *Sender)
{
    TRegEdit * ed;
    TRegScrollBar * sb;
    AnsiString str;

    sb = (TRegScrollBar *) Sender;
    str = sb->Name;
    str.Delete(1,12);
    str = "RegEdit"+str;
    ed = (TRegEdit *)FindComponent(str);
    ed->Text = IntToHex(sb->Position,4);

}
//---------------------------------------------------------------------------
void __fastcall TForm_Validation::FormDestroy(TObject *Sender)
{
    delete Frame_DataPath;
    delete Frame_BWMeasure;
    Frame_DataPath = NULL;
    Frame_BWMeasure = NULL;    
}
//---------------------------------------------------------------------------

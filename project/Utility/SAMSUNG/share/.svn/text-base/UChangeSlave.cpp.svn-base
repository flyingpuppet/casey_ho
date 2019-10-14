//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UChangeSlave.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"
TForm_ChangeSlave *Form_ChangeSlave;
//---------------------------------------------------------------------------
__fastcall TForm_ChangeSlave::TForm_ChangeSlave(TComponent* Owner)
    : TMEMCForm(Owner)
{
    le_slave->Text = "0x"+IntToHex(GetDevice()->GetSlave(),2);
}
//---------------------------------------------------------------------------
void __fastcall TForm_ChangeSlave::BitBtn1Click(TObject *Sender)
{
    ModalResult = le_slave->Text.ToInt();    
}
//---------------------------------------------------------------------------
void __fastcall TForm_ChangeSlave::BitBtn2Click(TObject *Sender)
{
    ModalResult = -1;    
}
//---------------------------------------------------------------------------

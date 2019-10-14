//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_Bitmap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"
TForm_Bitmap *Form_Bitmap;
//---------------------------------------------------------------------------
__fastcall TForm_Bitmap::TForm_Bitmap(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bitmap::FormPaint(TObject *Sender)
{
    this->Canvas->Draw(0,0, pBitmap);    
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bitmap::FormResize(TObject *Sender)
{
    this->Canvas->Draw(0,0, pBitmap);    
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bitmap::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caFree;    
}
//---------------------------------------------------------------------------

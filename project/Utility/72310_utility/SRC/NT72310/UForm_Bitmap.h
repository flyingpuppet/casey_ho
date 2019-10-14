//---------------------------------------------------------------------------

#ifndef UForm_BitmapH
#define UForm_BitmapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
//---------------------------------------------------------------------------
class TForm_Bitmap : public TMEMCForm
{
__published:	// IDE-managed Components
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    Graphics::TBitmap * pBitmap;
    __fastcall TForm_Bitmap(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Bitmap *Form_Bitmap;
//---------------------------------------------------------------------------
#endif

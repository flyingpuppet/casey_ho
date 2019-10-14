//---------------------------------------------------------------------------

#ifndef UForm_PdepthH
#define UForm_PdepthH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm_Pdepth : public TMEMCForm
{
__published:	// IDE-managed Components
    TLabeledEdit *LE_width;
    TLabeledEdit *LE_height;
    TLabeledEdit *LE_top;
    TLabeledEdit *LE_left;
    TButton *Button4;
    TProgressBar *PB;
    TSaveDialog *SaveBitmap;
    void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
    int buf_top;
    int buf_left;
    int buf_width;
    int buf_height;

    Byte ** data_buf;

    void __fastcall ReadImageBuf();
    Byte * __fastcall ReadLine(unsigned int LineStart);
    void __fastcall MakeYUVBitmap(Graphics::TBitmap * pBitmap);
public:		// User declarations
    __fastcall TForm_Pdepth(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Pdepth *Form_Pdepth;
//---------------------------------------------------------------------------
#endif

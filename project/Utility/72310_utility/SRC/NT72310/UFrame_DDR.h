//---------------------------------------------------------------------------

#ifndef UFrame_DDRH
#define UFrame_DDRH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCFrame.h"
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFrame_DDR : public TMEMCFrame
{
__published:	// IDE-managed Components
    TStringGrid *Stg_DDR;
    TButton *BtnDDRLoad;
    TButton *BtnDDRRead;
    TLabeledEdit *LE_StartAdd;
    TLabeledEdit *LE_MemoLength;
    TButton *BtnDDRSave;
    TButton *BtnDDRWrite;
    TMemo *Memo1;
    TProgressBar *PB;
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    void __fastcall Stg_DDRKeyPress(TObject *Sender, char &Key);
    void __fastcall BtnDDRReadClick(TObject *Sender);
    void __fastcall BtnDDRWriteClick(TObject *Sender);
    void __fastcall BtnDDRLoadClick(TObject *Sender);
    void __fastcall BtnDDRSaveClick(TObject *Sender);
private:	// User declarations
    TStringList * sl_DDR;
    void __fastcall FillStgFromStr();
public:		// User declarations
    __fastcall TFrame_DDR::TFrame_DDR(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_DDR *Frame_DDR;
//---------------------------------------------------------------------------
#endif

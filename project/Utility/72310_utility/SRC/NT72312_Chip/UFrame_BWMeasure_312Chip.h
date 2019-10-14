//---------------------------------------------------------------------------

#ifndef UFrame_BWMeasure_312ChipH
#define UFrame_BWMeasure_312ChipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UFrame_BWMeasure_312FPGA.h"
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFrame_BWMeasure_312Chip : public TFrame_BWMeasure_312FPGA
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TFrame_BWMeasure_312Chip(TComponent* Owner);
    virtual int __fastcall GetMCCLK();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_BWMeasure_312Chip *Frame_BWMeasure_312Chip;
//---------------------------------------------------------------------------
#endif

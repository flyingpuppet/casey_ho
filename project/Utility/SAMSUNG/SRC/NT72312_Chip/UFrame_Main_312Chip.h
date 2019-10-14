//---------------------------------------------------------------------------

#ifndef UFrame_Main_312ChipH
#define UFrame_Main_312ChipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RegCheckBox.h"
#include "UFrame_Main_312FPGA.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFrame_Main_312Chip : public TFrame_Main_312FPGA
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TFrame_Main_312Chip(TComponent* Owner);
    __fastcall TFrame_Main_312Chip(TComponent* Owner, DeviceCreate * oDev_Cre);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_Main_312Chip *Frame_Main_312Chip;
//---------------------------------------------------------------------------
#endif

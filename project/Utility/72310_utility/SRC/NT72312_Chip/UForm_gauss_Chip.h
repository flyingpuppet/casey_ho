//---------------------------------------------------------------------------

#ifndef UForm_gauss_ChipH
#define UForm_gauss_ChipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UForm_Gauss.h"
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TForm_gauss_Chip : public TForm_gauss
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TForm_gauss_Chip(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_gauss_Chip *Form_gauss_Chip;
//---------------------------------------------------------------------------
#endif

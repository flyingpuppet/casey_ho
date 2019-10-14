//---------------------------------------------------------------------------

#ifndef UChangeSlaveH
#define UChangeSlaveH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm_ChangeSlave : public TMEMCForm
{
__published:	// IDE-managed Components
    TLabeledEdit *le_slave;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_ChangeSlave(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_ChangeSlave *Form_ChangeSlave;
//---------------------------------------------------------------------------
#endif

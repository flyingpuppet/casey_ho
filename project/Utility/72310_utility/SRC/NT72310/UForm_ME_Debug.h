//---------------------------------------------------------------------------

#ifndef UForm_ME_DebugH
#define UForm_ME_DebugH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include "RegCheckBox.h"
#include "RegLabeledEdit.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_ME_Debug : public TMEMCForm
{
__published:	// IDE-managed Components
    TGroupBox *ME_Debug_PG;
    TGroupBox *ME_force_mv;
    TRegCheckBox *RegCheckBox20;
    TRegLabeledEdit *rle_mv_ini_x;
    TRegLabeledEdit *rle_mv_ini_y;
    TRegLabeledEdit *RegLabeledEdit3;
    TRegLabeledEdit *RegLabeledEdit4;
    TRegLabeledEdit *RegLabeledEdit6;
    TRegCheckBox *RegCheckBox1;
    TRegCheckBox *RegCheckBox2;
    TRegLabeledEdit *RegLabeledEdit9;
    TRegLabeledEdit *RegLabeledEdit10;
    TButton *btnRefresh;
    TRegLabeledEdit *RegLabeledEdit5;
    TRegLabeledEdit *RegLabeledEdit11;
    TRegLabeledEdit *RegLabeledEdit12;
    TRegLabeledEdit *RegLabeledEdit13;
    TRegLabeledEdit *RegLabeledEdit14;
    TRegLabeledEdit *ph_ini_rle;
    TRegLabeledEdit *RegLabeledEdit16;
    TRegLabeledEdit *pf_ini_val;
    void __fastcall btnRefreshClick(TObject *Sender);
    void __fastcall RegLabeledEdit7KeyPress(TObject *Sender, char &Key);
    void __fastcall rle_mv_ini_xKeyPress(TObject *Sender, char &Key);
    void __fastcall rle_mv_ini_yKeyPress(TObject *Sender, char &Key);
    void __fastcall ph_ini_rleKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_ME_Debug(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_ME_Debug *Form_ME_Debug;
//---------------------------------------------------------------------------
#endif

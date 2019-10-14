//---------------------------------------------------------------------------

#ifndef ULoadScriptH
#define ULoadScriptH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm_LoadScript : public TMEMCForm
{
__published:	// IDE-managed Components
    TMemo *MemoScript;
    TButton *Button1;
    TButton *Button2;
    TOpenDialog *OpenScript;
    TSaveDialog *SaveScript;
    TButton *Button3;
    TButton *Button4;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
public:		// User declarations
    __fastcall TForm_LoadScript(TComponent* Owner);
    bool __fastcall IsComment(AnsiString str);
    bool __fastcall ExecuteScript(AnsiString str);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_LoadScript *Form_LoadScript;
//---------------------------------------------------------------------------
#endif

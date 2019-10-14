//---------------------------------------------------------------------------

#ifndef UScanRGBH
#define UScanRGBH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm_ScanRGB;
typedef enum _Cursor_Color{Cur_Black, Cur_Blue, Cur_Green, Cur_Cyan, Cur_Red, Cur_Magenta, Cur_Yellow, Cur_White}Cursor_Color;
typedef enum _Color_Index{CI_RGain, CI_GGain, CI_BGain, CI_ROffset, CI_GOffset, CI_BOffset}Color_Index;

class TForm_ScanRGB : public TMEMCForm
{
__published:	// IDE-managed Components
    TLabeledEdit *le_Step;
    TButton *Button1;
    TComboBox *cb_scanOption;
    TLabel *Label1;
    TProgressBar *PB;
    TButton *Save;
    TSaveDialog *SaveDialog1;
    TButton *Button2;
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall SaveClick(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
    void __fastcall SetDefaultRGB();
    void __fastcall SetCursorPosition(int index, int x, int y);
    void __fastcall SetCursorColor(int index, Cursor_Color cl);
    void __fastcall EnableRead(int index, bool enable);
    void __fastcall scanRGBOut(int step, int ColorIndex, int index = 0, TStringList * sl= NULL);
    void __fastcall SetRGain(int val);
    void __fastcall SetGGain(int val);
    void __fastcall SetBGain(int val);
    void __fastcall SetROffset(int val);
    void __fastcall SetGOffset(int val);
    void __fastcall SetBOffset(int val);
    int __fastcall readROut(int index);
    int __fastcall readGOut(int index);
    int __fastcall readBOut(int index);

    TStringList * resultList;


public:		// User declarations
    __fastcall TForm_ScanRGB(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_ScanRGB *Form_ScanRGB;
//---------------------------------------------------------------------------
#endif

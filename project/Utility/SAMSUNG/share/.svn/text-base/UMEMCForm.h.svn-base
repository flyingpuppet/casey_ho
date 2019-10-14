//---------------------------------------------------------------------------

#ifndef UMEMCFormH
#define UMEMCFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "WinSkinStore.hpp"
#include "WinSkinData.hpp"
#include "RegEdit.h"
#include "RegScrollBar.h"
#include "RegLabeledEdit.h"
#include "I2CDevice.h"
//---------------------------------------------------------------------------
#define BIT_0 0x01
#define BIT_1 0x02
#define BIT_2 0x04
#define BIT_3 0x08
#define BIT_4 0x10
#define BIT_5 0x20
#define BIT_6 0x40
#define BIT_7 0x80

#define N_BIT_0 0xFE
#define N_BIT_1 0xFD
#define N_BIT_2 0xFB
#define N_BIT_3 0xF7
#define N_BIT_4 0xEF
#define N_BIT_5 0xDF
#define N_BIT_6 0xBF
#define N_BIT_7 0x7F



class TMEMCForm : public TForm
{
__published:	// IDE-managed Components
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    static AnsiString mFilePath;
    static I2CDevice * Device;

public:		// User declarations
    __fastcall TMEMCForm(TComponent* Owner);
    friend class TMEMCFrame;
    static void __fastcall SetDevice(I2CDevice * dev);
    static I2CDevice * __fastcall GetDevice();
    virtual void __fastcall LoadRegEditInfo(AnsiString * str);
    virtual void __fastcall LoadPara(unsigned int * pi);
    virtual void __fastcall LoadFormatPara(unsigned int * pi);
    virtual void __fastcall WriteFormatPara(unsigned int FAddress, unsigned int FstartBits, unsigned int FBits, unsigned int value );
    void __fastcall SetFilePath(AnsiString path);
    AnsiString __fastcall GetFilePath();
    TRegEdit * __fastcall  Find(TRegScrollBar * rsb);
    TRegScrollBar * __fastcall  Find( TRegEdit * rlb);
    virtual AnsiString __fastcall getEditName(int i);
    virtual AnsiString __fastcall getScrollName(int i);
    virtual int __fastcall getconCount();
    virtual bool __fastcall MailBox_Available();
    virtual void __fastcall MailBox_SendAddress(unsigned int address);
};
//---------------------------------------------------------------------------
extern PACKAGE TMEMCForm *MEMCForm;
//---------------------------------------------------------------------------
#endif

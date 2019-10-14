//---------------------------------------------------------------------------

#ifndef RegLabeledEditH
#define RegLabeledEditH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include "..\Driver\I2CDevice.h"
#include "RegEdit.h"
#include "reg_public.h"
//---------------------------------------------------------------------------
class PACKAGE TRegLabeledEdit : public TLabeledEdit
{
private:
    static I2CDevice * FDev;
    AnsiString FAddress;
    int FBits;
    int FstartBits;
    TTextType Ftype;
    TMailBoxType FMailBox;
    AnsiString FMailBoxAddress;
protected:
public:
    static void __fastcall SetDevice(I2CDevice * dev);
    __fastcall TRegLabeledEdit(TComponent* Owner);
    DYNAMIC void __fastcall KeyPress(char &Key);
    void __fastcall Refresh();
__published:
    __property AnsiString RegStartAddress = {read = FAddress, write = FAddress, nodefault};
    __property int RegBits  = {read=FBits, write=FBits, nodefault };
    __property int RegStart = {read=FstartBits, write=FstartBits, nodefault};
    __property TTextType TextType = {read=Ftype, write=Ftype, default = ttHex};
    __property TMailBoxType MailBox = {read=FMailBox, write=FMailBox, default = mbt_NONE};
    __property AnsiString MailBox_Address = {read = FMailBoxAddress, write = FMailBoxAddress, nodefault};//default = 0xC00A00A0};
    __property OnKeyPress;
};
//---------------------------------------------------------------------------
#endif

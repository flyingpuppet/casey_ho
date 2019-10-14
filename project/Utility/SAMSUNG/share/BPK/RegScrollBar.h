//---------------------------------------------------------------------------

#ifndef RegScrollBarH
#define RegScrollBarH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "..\Driver\I2CDevice.h"
#include "reg_public.h"
//---------------------------------------------------------------------------
class PACKAGE TRegScrollBar : public TScrollBar
{
private:
    static I2CDevice * FDev;
    AnsiString FAddress;
    int FBits;
    int FstartBits;
    bool FUserDefineMargin;
    TMailBoxType FMailBox;
    AnsiString FMailBoxAddress;
protected:
public:
    static void __fastcall SetDevice(I2CDevice * dev);
    __fastcall TRegScrollBar(TComponent* Owner);
    void __fastcall Refresh();
    DYNAMIC void __fastcall Scroll(TScrollCode ScrollCode, int &ScrollPos);
__published:
    __property AnsiString RegStartAddress = {read = FAddress, write = FAddress, nodefault};
    __property int RegBits  = {read=FBits, write=FBits, nodefault };
    __property int RegStart = {read=FstartBits, write=FstartBits, nodefault};
    __property TMailBoxType MailBox = {read=FMailBox, write=FMailBox, default = mbt_NONE};
    __property AnsiString MailBox_Address = {read = FMailBoxAddress, write = FMailBoxAddress, nodefault};//default = 0xC00A00A0};
    __property bool UserDefineMargin = {read = FUserDefineMargin, write = FUserDefineMargin, default = false};
    __property OnScroll;
};
//---------------------------------------------------------------------------
#endif

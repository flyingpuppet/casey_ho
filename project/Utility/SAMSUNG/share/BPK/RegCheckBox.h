//---------------------------------------------------------------------------

#ifndef RegCheckBoxH
#define RegCheckBoxH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "..\Driver\I2CDevice.h"
#include "reg_public.h"
//---------------------------------------------------------------------------


class PACKAGE TRegCheckBox : public TCheckBox
{
private:
    AnsiString FAddress;
    static I2CDevice * FDev;
    int FBit;
    TStrings * Fsl_Addr;
    TStrings * Fsl_Bits;
    TMailBoxType FMailBox;
    AnsiString FMailBoxAddress;

private:
    void __fastcall SetAddrs(TStrings * sl);
    void __fastcall SetBits(TStrings * sl);

protected:
public:
    static void __fastcall SetDevice(I2CDevice * dev);
    __fastcall TRegCheckBox(TComponent* Owner);
    DYNAMIC void __fastcall Click(void);
    void __fastcall Refresh(void);

__published:
    __property AnsiString RegAddress ={read = FAddress, write = FAddress, nodefault};
    __property int RegBit={read=FBit, write=FBit, default = 0};
    __property TStrings * RegAddresses = {read=Fsl_Addr,write=SetAddrs,nodefault };
    __property TStrings * RegBits = {read=Fsl_Bits,write=SetBits,nodefault };
    __property TMailBoxType MailBox = {read = FMailBox, write = FMailBox, default = mbt_NONE};
    __property AnsiString MailBox_Address = {read=FMailBoxAddress, write=FMailBoxAddress, nodefault};
    __property OnClick;
};
//---------------------------------------------------------------------------
#endif

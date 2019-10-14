//---------------------------------------------------------------------------

#ifndef RegRadioButtonH
#define RegRadioButtonH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "..\Driver\I2CDevice.h"
#include "reg_public.h"
//---------------------------------------------------------------------------
class PACKAGE TRegRadioButton : public TRadioButton
{

private:
    static I2CDevice * FDev;

    AnsiString FAddress;
    AnsiString FVal;
    AnsiString FMask;
    
    TStrings * Fsl_Addr;
    TStrings * Fsl_Vals;
    TStrings * Fsl_Masks;

    TMailBoxType FMailBox;
    AnsiString FMailBoxAddress;

private:
    void __fastcall SetAddrs(TStrings * sl);
    void __fastcall SetVals(TStrings * sl);
    void __fastcall SetMasks(TStrings * sl);


protected:
public:
    static void __fastcall SetDevice(I2CDevice * dev);
    __fastcall TRegRadioButton(TComponent* Owner);
    DYNAMIC void __fastcall Click(void);
    void __fastcall Refresh(void);
    
__published:
    __property AnsiString RegAddress ={read = FAddress, write = FAddress, nodefault};
    __property AnsiString RegValue={read=FVal, write=FVal, nodefault};
    __property AnsiString RegMask= {read=FMask, write=FMask, nodefault};

    __property TStrings * RegAddresses = {read=Fsl_Addr,write=SetAddrs,nodefault };
    __property TStrings * RegValues = {read=Fsl_Vals,write=SetVals,nodefault };
    __property TStrings * RegMasks = {read=Fsl_Masks,write=SetMasks,nodefault };

    __property TMailBoxType MailBox = {read=FMailBox, write=FMailBox, default = mbt_NONE};
    __property AnsiString MailBox_Address = {read = FMailBoxAddress, write = FMailBoxAddress, nodefault};//default = 0xC00A00A0};

    __property OnClick;

};
//---------------------------------------------------------------------------
#endif

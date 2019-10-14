//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "RegRadioButton.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
I2CDevice * TRegRadioButton::FDev = NULL;
void __fastcall TRegRadioButton::SetDevice(I2CDevice * dev)
{
    FDev = dev;
}
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TRegRadioButton *)
{
    new TRegRadioButton(NULL);
}
//---------------------------------------------------------------------------
__fastcall TRegRadioButton::TRegRadioButton(TComponent* Owner)
    : TRadioButton(Owner)
{
    Fsl_Addr = new TStringList();
    Fsl_Vals = new TStringList();
    Fsl_Masks = new TStringList();
}
//---------------------------------------------------------------------------
void __fastcall TRegRadioButton::SetAddrs(TStrings * sl)
{
    Fsl_Addr->Assign(sl);
}
//---------------------------------------------------------------------------
void __fastcall TRegRadioButton::SetVals(TStrings * sl)
{
    Fsl_Vals->Assign(sl);
}
//---------------------------------------------------------------------------
void __fastcall TRegRadioButton::SetMasks(TStrings * sl)
{
    Fsl_Masks->Assign(sl);
}
//---------------------------------------------------------------------------
void __fastcall TRegRadioButton::Click(void)
{
    unsigned int address;
    unsigned int value;
    unsigned int tmp;
    unsigned int mask;
    unsigned int mailread;
    
    if(FDev==NULL)  return;
    if((Fsl_Addr->Count != 0)&&(Fsl_Masks->Count != 0)&&(Fsl_Vals->Count !=0))
    {
        if((Fsl_Addr->Count != Fsl_Masks->Count)||
            (Fsl_Addr->Count != Fsl_Vals->Count)||
            (Fsl_Masks->Count != Fsl_Vals->Count))
        {
            //return;
        }
        else
        {
            for(int i=0;i<Fsl_Addr->Count;i++)
            {
                try
                {
                    if(FMailBox != mbt_NONE)
                    {
                        int i;
                        for(i=0;i<10;i++)
                        {
                            FDev->AllReadDWord((unsigned int)FMailBoxAddress.ToInt(),mailread);
                            if(mailread == 0)
                            {
                                break;
                            }
                        }
                        if(i>=10)
                        {
                            return;
                        }
                    }
                    address = Fsl_Addr->Strings[i].ToInt();
                    value = Fsl_Vals->Strings[i].ToInt();
                    if( Fsl_Vals->Strings[i] == "")
                    {
                        mask = 0xFFFFFFFF;
                    }
                    else
                    {
                        mask = Fsl_Vals->Strings[i].ToInt();
                    }
                    FDev->AllReadDWord(address,tmp);
                    tmp &= (~mask);
                    value &= mask;
                    value |= tmp;
                    FDev->AllWriteDWord(address,value);
                    if(FMailBox == mbt_MBADDR)
                    {
                        FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(),address);
                    }
                    else if(FMailBox == mbt_MBBITS)
                    {
                        FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(),address);    
                    }
                }
                catch(...)
                {
                    return;
                }

            }
        }
    }

    if((FAddress != "")&&(FVal != ""))
    {
        try
        {
            address = FAddress.ToInt();
            value = FVal.ToInt();
            if(FMask == "")
            {
                mask = 0xFFFFFFFF;
            }
            else
            {
                mask = FMask.ToInt();
            }
            FDev->AllReadDWord(address,tmp);
            tmp &= (~mask);
            value &= mask;
            value |= tmp;
            FDev->AllWriteDWord(address,value);
            if(FMailBox == mbt_MBADDR)
            {
                FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(),address);
            }
            else if(FMailBox == mbt_MBBITS)
            {
                FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(),address);    
            }
        }
        catch(...)
        {
            return;
        }
    }
    if(OnClick != NULL)
    {
        OnClick(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall TRegRadioButton::Refresh(void)
{
    unsigned int address;
    Byte mask, value;

    int bit, mode;
    if (FDev == NULL) return;
    if((Fsl_Addr->Count != 0)&&(Fsl_Masks->Count != 0)&&(Fsl_Vals->Count !=0))
    {
        if((Fsl_Addr->Count != Fsl_Masks->Count)||
        (Fsl_Addr->Count != Fsl_Vals->Count)||
        (Fsl_Masks->Count != Fsl_Vals->Count))
        {
            //return;
        }
        else
        {
            try
            {
                address = Fsl_Addr->Strings[0].ToInt();
                bit = Fsl_Vals->Strings[0].ToInt();
                mask = Fsl_Masks->Strings[0].ToInt();

                FDev->AllReadByte(address,value);
                this->Checked = ((value & mask) == bit)? true:false;
            }
            catch(...)
            {
                return;
            }

        }
    }

    if ((FAddress != ""))
    {
        try
        {
            address = FAddress.ToInt();
        }
        catch(...)
        {
            return;
        }
        bit = FVal.ToInt();
        mask = FMask.ToInt();       

        FDev->AllReadByte(address,value);
        this->Checked = ((value & mask) == bit)? true:false;
        return ;
    }
}
//---------------------------------------------------------------------------
namespace Regradiobutton
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TRegRadioButton)};
         RegisterComponents("Standard", classes, 0);
    }
}
//---------------------------------------------------------------------------
 
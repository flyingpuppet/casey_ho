//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "RegCheckBox.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
I2CDevice * TRegCheckBox::FDev = NULL;

static inline void ValidCtrCheck(TRegCheckBox *)
{
    new TRegCheckBox(NULL);
}
//---------------------------------------------------------------------------
__fastcall TRegCheckBox::TRegCheckBox(TComponent* Owner)
    : TCheckBox(Owner)
{
    Fsl_Addr = new TStringList;
    Fsl_Bits = new TStringList;
}
void __fastcall TRegCheckBox::SetDevice(I2CDevice * dev)
{
    FDev = dev;
}
//---------------------------------------------------------------------------
void __fastcall TRegCheckBox::SetAddrs(TStrings * sl)
{
    Fsl_Addr->Assign(sl);
}
//---------------------------------------------------------------------------
void __fastcall TRegCheckBox::SetBits(TStrings * sl)
{
    Fsl_Bits->Assign(sl);
}
//---------------------------------------------------------------------------
void __fastcall TRegCheckBox::Click(void)
{
    unsigned int address;
    unsigned int mailread;
    Byte value;
    int bit;

    int mode;

    if(FDev==NULL) return;
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

    if((Fsl_Addr->Count != 0) && (Fsl_Bits->Count != 0))
    {
        if(Fsl_Addr->Count != Fsl_Bits->Count)
        {
        }
        for(int i=0; i<Fsl_Addr->Count; i++)
        {
            try
            {
                address = Fsl_Addr->Strings[i].ToInt();
                bit = Fsl_Bits->Strings[i].ToInt();
                if(bit>=8)  return;

                FDev->AllReadByte(address,value);
                value &= (~(0x01<<bit));
                if(this->Checked)
                {
                    value |= 0x01<<bit;
                }
                FDev->AllWriteByte(address,value);
                if(FMailBox == mbt_MBADDR)
                {
                    FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(), (address/4)*4);
                }
                else if(FMailBox == mbt_MBBITS)
                {
                    FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(), ((bit+(address % 4)*8)<<24)|((bit+(address % 4)*8)<<16)|(((address/4)*4)&0x0000FFFF));    
                }
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
        
        if (FBit>=8) return;
        else
        {
            FDev->AllReadByte(address,value);
            value &= (~(0x01<<FBit));
            if(this->Checked)
            {
                value |= 0x01<<FBit;
            }
            FDev->AllWriteByte(address,value);
            if(FMailBox == mbt_MBADDR)
            {
                FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(), (address/4)*4);
            }
            else if(FMailBox == mbt_MBBITS)
            {
                FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(), ((FBit+(address % 4)*8)<<24)|((FBit+(address % 4)*8)<<16)|(((address/4)*4)&0x0000FFFF));    
            }
        }
        return;
    }
    if(OnClick != NULL)
    {
        OnClick(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall TRegCheckBox::Refresh()
{
    unsigned int address;
    Byte mask, value;

    int bit, mode;
    if (FDev == NULL) return;

    if((Fsl_Addr->Count != 0) && (Fsl_Bits->Count != 0))
    {
        if(Fsl_Addr->Count != Fsl_Bits->Count)  return;
        try
        {
            address = Fsl_Addr->Strings[0].ToInt();
            bit = Fsl_Bits->Strings[0].ToInt();
            if(bit>=8)  return;
            else
            {
                mask = 0x01<<bit;
            }

            FDev->AllReadByte(address,value);
            this->Checked = ((value & mask) == mask)? true:false;
        }
        catch(...)
        {
            return;
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
        
        if (FBit>=8) return;
        else
        {
            mask = 0x01<<FBit;
        }
        FDev->AllReadByte(address,value);
        this->Checked = ((value & mask) == mask)? true:false;
        return ;
    }
}
//---------------------------------------------------------------------------
namespace Regcheckbox
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TRegCheckBox)};
         RegisterComponents("Standard", classes, 0);
    }
}
//---------------------------------------------------------------------------

 
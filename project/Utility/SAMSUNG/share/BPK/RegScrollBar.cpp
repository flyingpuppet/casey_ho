//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "RegScrollBar.h"
#include <math.h>
#include <math.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

I2CDevice * TRegScrollBar::FDev = NULL;
void __fastcall TRegScrollBar::SetDevice(I2CDevice * dev)
{
    FDev = dev;
}
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TRegScrollBar *)
{
    new TRegScrollBar(NULL);
}
//---------------------------------------------------------------------------
__fastcall TRegScrollBar::TRegScrollBar(TComponent* Owner)
    : TScrollBar(Owner)
{
    //this->Max = Power(2,this->RegBits)-1;
}
//---------------------------------------------------------------------------
void __fastcall TRegScrollBar::Scroll(TScrollCode ScrollCode, int &ScrollPos)
{
    unsigned int address, address2;
    unsigned int value,value2, tmp1, tmp2, mailread;

    int mode1,Bits1,Bits2;
    if(FDev == NULL) return;

    if(!FUserDefineMargin)   Max = pow(2,FBits)-1;

    if(ScrollCode == scEndScroll)
    {
        if(FAddress != "")
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
                if(FBits>32)   return;
                address = FAddress.ToInt();
                value = ScrollPos;
                if(value >= pow(2,FBits))
                {
                    value = pow(2,FBits)-1;
                }

                mode1 = address % 4;
                if(mode1*8+FstartBits+FBits > 32)
                {
                    Bits2 = mode1*8+FstartBits+FBits - 32;
                    Bits1 = FBits-Bits2;
                    address -= mode1;
                    address2 = address + 4;
                    FDev->AllReadDWord(address, tmp1);
                    FDev->AllReadDWord(address2, tmp2);
                    tmp1 &= (0xFFFFFFFF>>Bits1);
                    tmp2 &= (0xFFFFFFFF<<Bits2);
                    value2 = value>>Bits1;
                    value = value<<(32-Bits1);
                    tmp1 |= value;
                    tmp2 |= value2;
                    FDev->AllWriteDWord(address, tmp1);
                    FDev->AllWriteDWord(address2, tmp2);
                    if(FMailBox == mbt_MBADDR)
                    {
                        FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(), address);
                    }
                    else if(FMailBox == mbt_MBBITS)
                    {
                        FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(), (FstartBits<<24)|((FstartBits+FBits-1)<<16)|(address&0x000FFFF));
                    }
                }
                else
                {
                    address -= mode1;
                    Bits1 = FBits;
                    FDev->AllReadDWord(address, tmp1);
                    tmp1 &= ~((0xFFFFFFFF<<(mode1*8+FstartBits))&(0xFFFFFFFF>>(32-mode1*8-FstartBits-FBits)));
                    value = (value<<(mode1*8+FstartBits));
                    tmp1 |= value;
                    FDev->AllWriteDWord(address, tmp1);
                    if(FMailBox == mbt_MBADDR)
                    {
                        FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(), address);
                    }
                    else if(FMailBox == mbt_MBBITS)
                    {
                        FDev->AllWriteDWord((unsigned int)FMailBoxAddress.ToInt(), (FstartBits<<24)|((FstartBits+FBits-1)<<16)|(address&0x000FFFF));
                    }
                }
            }
            catch(...)
            {
                return;
            }
        }
    }
    if(OnScroll != NULL)
    {
        OnScroll(this, ScrollCode, ScrollPos);
    }

}
//---------------------------------------------------------------------------
void __fastcall TRegScrollBar::Refresh()
{
    unsigned int address, address2;
    unsigned int value,value2, tmp1, tmp2;

    int mode1,Bits1,Bits2;

    if(FDev==NULL)  return;

    if(!FUserDefineMargin)   Max = pow(2,FBits)-1;

    if(FAddress != "")
    {
        try
        {
            if(FBits>32)   return;

            address = FAddress.ToInt();

            mode1 = address % 4;
            if(mode1*8+FstartBits+FBits > 32)
            {
                Bits2 = mode1*8+FstartBits+FBits - 32;
                Bits1 = FBits-Bits2;
                address -= mode1;
                address2 = address + 4;
                FDev->AllReadDWord(address, tmp1);
                FDev->AllReadDWord(address2, tmp2);
                value = ((tmp2 & (0xFFFFFFFF>>(32-Bits2)))<<Bits1)|(tmp1 >>(32-Bits1));
            }
            else
            {
                address -= mode1;
                Bits1 = FBits;
                FDev->AllReadDWord(address, tmp1);
                value = (tmp1&(0xFFFFFFFF>>(32-mode1*8-FstartBits-FBits)))>>(mode1*8+FstartBits);
            }
            Position = value;
        }
        catch(...)
        {
            return;
        }
    }
}
//---------------------------------------------------------------------------
namespace Regscrollbar
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TRegScrollBar)};
         RegisterComponents("Standard", classes, 0);
    }
}
//---------------------------------------------------------------------------
 
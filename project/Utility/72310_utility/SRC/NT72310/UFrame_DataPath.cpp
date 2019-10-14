//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_DataPath.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCFrame"
#pragma link "RegCheckBox"
#pragma resource "*.dfm"
TFrame_DataPath *Frame_DataPath;


#define MEY_DCBypass  10
#define MCY_DCBypass  11
#define MCC_DCBypass  12

#define MEY_LastLineBypass  20
#define MCY_LastLineBypass  21
#define MCC_LastLineBypass  22

#define MEY_DCMode0     30
#define MEY_DCMode1     31
#define MEY_DCMode2     32
#define MEY_DCMode3     33
#define MEY_DCMode4     34

#define MCY_DCMode0     40
#define MCY_DCMode1     41
#define MCY_DCMode2     42
#define MCY_DCMode3     43
#define MCY_DCMode4     44

#define MCC_DCMode0     50
#define MCC_DCMode1     51
#define MCC_DCMode2     52
#define MCC_DCMode3     53
#define MCC_DCMode4     54

#define ADDR_BYPass        0xE00001F4
#define ADDR_MMUByPass     0xE0000B58
#define IP08               0xE0000108
#define IP09               0xE0000109
#define IP0A               0xE000010A
#define MMU4D              0xE0000B4D
#define MMU4E              0xE0000B4E
#define MMU4F              0xE0000B4F
#define FRC_TOP3A          0xE000003A
#define IPCSC              0xE0000158
#define MCCSC              0xE0000201
#define IP94               0xE0000194
#define MMU_HACTIVE        0xE0000B52
#define MMU_CACTIVE        0xE0000B54

#define IPFC               0xE00001FC
#define MMU64              0xE0000B64
#define MMU65              0xE0000B65
#define MMU66              0xE0000B66

#define IPF9               0xE00001F9
#define MMU68              0xE0000B68
#define MMU6A              0xE0000B6A

#define IPFA               0xE00001FA
#define IPFB               0xE00001FB
#define MMU69              0xE0000B69
#define MMU6B              0xE0000B6B

#define LVDSCLKSW          0xC00D002C
#define LVDSASSERT         0xC00C0008

#define IPDEBUG            0xE0000040


//---------------------------------------------------------------------------
__fastcall TFrame_DataPath::TFrame_DataPath(TComponent* Owner)
    : TMEMCFrame(Owner)
{
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::Button11Click(TObject *Sender)
{
    unsigned int value;

    GetDevice()->WriteDWord(LVDSCLKSW, 0);
    GetDevice()->WriteDWord(LVDSASSERT, 0x00020000);
    GetDevice()->ReadDWord(LVDSASSERT,value);
    GetDevice()->ReadDWord(LVDSASSERT,value);
    GetDevice()->ReadDWord(LVDSASSERT,value);
    GetDevice()->ReadDWord(LVDSASSERT,value);
    GetDevice()->WriteDWord(LVDSASSERT, 0);
    GetDevice()->WriteDWord(LVDSCLKSW, 0x00000C00);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::CB_HalfClick(TObject *Sender)
{
    TCheckBox * cb;
    int active;
    unsigned int dValue;

    cb = (TCheckBox *)Sender;

    if (cb->Checked)
    {
        GetDevice()->ReadDWord(IP94, dValue);
        active = dValue & 0x0000FFFF;
        active /= 2;
        dValue &= 0xFFFF0000;
        dValue |= active;
        GetDevice()->WriteDWord(IP94, dValue);

        GetDevice()->ReadDWord(MMU_HACTIVE-2, dValue);
        active = (dValue & 0xFFFF0000)>>16;
        active /= 2;
        dValue &= 0x0000FFFF;
        dValue |= active<<16;
        GetDevice()->WriteDWord(MMU_HACTIVE-2, dValue);

        GetDevice()->ReadDWord(MMU_CACTIVE, dValue);
        active = dValue & 0x0000FFFF;
        active /= 2;
        dValue &= 0xFFFF0000;
        dValue |= active;
        GetDevice()->WriteDWord(MMU_CACTIVE, dValue);
    }
    else
    {
        GetDevice()->ReadDWord(IP94, dValue);
        active = dValue & 0x0000FFFF;
        active *= 2;
        dValue &= 0xFFFF0000;
        dValue |= active;
        GetDevice()->WriteDWord(IP94, dValue);

        GetDevice()->ReadDWord(MMU_HACTIVE-2, dValue);
        active = (dValue & 0xFFFF0000)>>16;
        active *= 2;
        dValue &= 0x0000FFFF;
        dValue |= active<<16;
        GetDevice()->WriteDWord(MMU_HACTIVE-2, dValue);

        GetDevice()->ReadDWord(MMU_CACTIVE, dValue);
        active = dValue & 0x0000FFFF;
        active *= 2;
        dValue &= 0xFFFF0000;
        dValue |= active;
        GetDevice()->WriteDWord(MMU_CACTIVE, dValue);
    }    
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RadioButton1Click(TObject *Sender)
{
    TRadioButton * RB;
    TRadioButton * RBMode;
    int mode;
    Byte value_ip, value_mmu;

    RB = (TRadioButton *)Sender;
    mode = RB->Tag;

    NT72310_Bypass(false, MEY_DCBypass);
    CB_MeY_DC_Bypass->Checked = false;

    NT72310_Bypass(false, MCY_DCBypass);
    CB_McY_DC_Bypass->Checked = false;

    NT72310_Bypass(false, MCC_DCBypass);
    CB_McC_DC_Bypass->Checked = false;

    GetDevice()->ReadByte(ADDR_BYPass+3, value_ip);
    GetDevice()->ReadByte(ADDR_MMUByPass, value_mmu);
    value_ip &= 0xF8;
    value_ip |= mode;
    value_mmu &= 0x8F;
    value_mmu |= (mode<<4);
    GetDevice()->WriteByte(ADDR_BYPass+3, value_ip);
    GetDevice()->WriteByte(ADDR_MMUByPass, value_mmu);

    RBMode = (TRadioButton * )FindComponent("RB_MeY_DC_mode"+IntToStr(mode));
    RBMode->Checked = true;

    GetDevice()->ReadByte(ADDR_BYPass+1, value_ip);
    GetDevice()->ReadByte(ADDR_MMUByPass+1, value_mmu);
    value_ip &= 0xF8;
    value_ip |= mode;
    value_mmu &= 0x8F;
    value_mmu |= (mode<<4);
    GetDevice()->WriteByte(ADDR_BYPass+1, value_ip);
    GetDevice()->WriteByte(ADDR_MMUByPass+1, value_mmu);

    RBMode = (TRadioButton *)FindComponent("RB_McY_DC_mode"+IntToStr(mode));
    RBMode->Checked = true;

    GetDevice()->ReadByte(ADDR_BYPass+2, value_ip);
    GetDevice()->ReadByte(ADDR_MMUByPass+2, value_mmu);
    value_ip &= 0xF8;
    value_ip |= mode;
    value_mmu &= 0x8F;
    value_mmu |= (mode<<4);
    GetDevice()->WriteByte(ADDR_BYPass+2, value_ip);
    GetDevice()->WriteByte(ADDR_MMUByPass+2, value_mmu);

    RBMode = (TRadioButton *)FindComponent("RB_McC_DC_mode"+IntToStr(mode));
    RBMode->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::NT72310_Bypass(bool checkflag, int tag)
{
    Byte Value_bypass;
    Byte Value_MeyByp, Value_McyByp, Value_MccByp;

    GetDevice()->ReadByte(ADDR_BYPass, Value_bypass);
    GetDevice()->ReadByte(ADDR_MMUByPass, Value_MeyByp);
    GetDevice()->ReadByte(ADDR_MMUByPass+1, Value_McyByp);
    GetDevice()->ReadByte(ADDR_MMUByPass+2, Value_MccByp);

    switch(tag)
    {
        case MEY_LastLineBypass :
            Value_bypass &= 0xBF;
            Value_MeyByp &= 0xFD;
            if(checkflag)
            {
                Value_bypass |= 0x40;
                Value_MeyByp |= 0x02;
            }
            GetDevice()->WriteByte(ADDR_MMUByPass, Value_MeyByp);
        break;
        case MCY_LastLineBypass:
            Value_bypass &= 0xEF;
            Value_McyByp &= 0xFD;
            if(checkflag)
            {
                Value_bypass |= 0x10;
                Value_McyByp |= 0x02;
            }
            GetDevice()->WriteByte(ADDR_MMUByPass+1, Value_McyByp);
        break;
        case MCC_LastLineBypass:
            Value_bypass &= 0xDF;
            Value_MccByp &= 0xFD;
            if(checkflag)
            {
                Value_bypass |= 0x20;
                Value_MccByp |= 0x02;
            }
            GetDevice()->WriteByte(ADDR_MMUByPass+2, Value_MccByp);
        break;

        case MEY_DCBypass:
            Value_bypass &= 0xFB;
            Value_MeyByp &= 0xFE;
            if(checkflag)
            {
                Value_bypass |= 0x04;
                Value_MeyByp |= 0x01;

            }
            GetDevice()->WriteByte(ADDR_MMUByPass, Value_MeyByp);
        break;
        case MCY_DCBypass:
            Value_bypass &= 0xFE;
            Value_McyByp &= 0xFE;
            if(checkflag)
            {
                Value_bypass |= 0x01;
                Value_McyByp |= 0x01;
            }
            GetDevice()->WriteByte(ADDR_MMUByPass+1, Value_McyByp);
        break;
        case MCC_DCBypass:
            Value_bypass &= 0xFD;
            Value_MccByp &= 0xFE;
            if(checkflag)
            {
                Value_bypass |= 0x02;
                Value_MccByp |= 0x01;
            }
            GetDevice()->WriteByte(ADDR_MMUByPass+2, Value_MccByp);
        break;
    }
    GetDevice()->WriteByte(ADDR_BYPass , Value_bypass);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::rb_PCClick(TObject *Sender)
{
    TRadioButton * RB;
    Byte value_top3a, value_ipcsc, value_mccsc, value_ip5B, value_mmu17, value_me380;
    RB = (TRadioButton *)Sender;

    GetDevice()->ReadByte(FRC_TOP3A, value_top3a);
    //ReadByte(IPCSC, value_ipcsc);
    //ReadByte(MCCSC, value_mccsc);
    switch (RB->Tag)
    {
        case 0:     //PC
            value_top3a &= 0xFE;
            value_ipcsc = 0;
            value_mccsc = 0;
            value_ip5B = 0x08;
            value_mmu17 = 0x27;
            value_me380 = 0x5f;
        break;
        case 1:      //VD
            value_top3a &= 0xFE;
            value_top3a |= 0x01;
            value_ipcsc = 0x61;
            value_mccsc = 0x71;
            value_ip5B = 0x00;
            value_mmu17 = 0x00;
            value_me380 = 0x40;
        break;
    }
    GetDevice()->WriteByte(FRC_TOP3A, value_top3a);
    GetDevice()->WriteByte(IPCSC, value_ipcsc);
    GetDevice()->WriteByte(MCCSC, value_mccsc);
    GetDevice()->WriteByte(0xE000015B, value_ip5B);
    GetDevice()->WriteByte(0xE0000B17, value_mmu17);
    GetDevice()->WriteByte(0xE0000A80, value_me380);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::CB_MeY_DC_BypassClick(TObject *Sender)
{
    TCheckBox * CB;
    CB = (TCheckBox *)Sender;

    NT72310_Bypass(CB->Checked, CB->Tag);    
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::CB_MeY_DebugClick(TObject *Sender)
{
    TCheckBox * cb;
    Byte value_0, value_1, value_2, value_3;

    cb = (TCheckBox *)Sender;

    switch(cb->Tag)
    {
        case 0:
            GetDevice()->ReadByte(IPFC, value_0);
            GetDevice()->ReadByte(MMU64, value_1);
            GetDevice()->ReadByte(MMU65, value_2);
            GetDevice()->ReadByte(MMU66, value_3);
            value_0 &= 0xFE;
            value_1 &= 0xFE;
            value_2 &= 0xFE;
            value_3 &= 0xFE;
            if(cb->Checked)
            {
                value_0 |= 0x01;
                value_1 |= 0x01;
                value_2 |= 0x01;
                value_3 |= 0x01;
            }
            GetDevice()->WriteByte(IPFC, value_0);
            GetDevice()->WriteByte(MMU64, value_1);
            GetDevice()->WriteByte(MMU65, value_2);
            GetDevice()->WriteByte(MMU66, value_3);
        break;
        case 1:
            GetDevice()->ReadByte(IPF9, value_0);
            GetDevice()->ReadByte(MMU68, value_1);
            GetDevice()->ReadByte(MMU6A, value_2);
            value_0 &= 0xFE;
            value_1 &= 0xFE;
            value_2 &= 0xFE;
            if(cb->Checked)
            {
                value_0 |= 0x01;
                value_1 |= 0x01;
                value_2 |= 0x01;
            }
            GetDevice()->WriteByte(IPF9, value_0);
            GetDevice()->WriteByte(MMU68, value_1);
            GetDevice()->WriteByte(MMU6A, value_2);
        break;
        case 2:
            GetDevice()->ReadByte(IPFA, value_0);
            GetDevice()->ReadByte(IPFB, value_1);
            GetDevice()->ReadByte(MMU69, value_2);
            GetDevice()->ReadByte(MMU6B, value_3);
            value_0 &= 0xFE;
            value_1 &= 0xFE;
            value_2 &= 0xFE;
            value_3 &= 0xFE;
            if(cb->Checked)
            {
                value_0 |= 0x01;
                value_1 |= 0x01;
                value_2 |= 0x01;
                value_3 |= 0x01;
            }
            GetDevice()->WriteByte(IPFA, value_0);
            GetDevice()->WriteByte(IPFB, value_1);
            GetDevice()->WriteByte(MMU69, value_2);
            GetDevice()->WriteByte(MMU6B, value_3);
        break;
    }    
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RB_MeY_DC_mode0Click(TObject *Sender)
{
    TRadioButton * RB;
    int mod, div;

    RB = (TRadioButton *)Sender;
    mod = RB->Tag % 5;

    div = RB->Tag / 10;
    switch(div)
    {
        case 3:
            if(CB_MeY_DC_Bypass->Checked) return;
        case 4:
            if(CB_McY_DC_Bypass->Checked) return;
        case 5:
            if(CB_McC_DC_Bypass->Checked) return;
    }

    NT72310_SetDCMode(mod, RB->Tag);
}

void __fastcall TFrame_DataPath::NT72310_SetDCMode(int mode, int tag)
{
    int div;
    Byte value_ip, value_mmu;
    Byte value_ip08, value_ip09, value_ip0a;
    Byte value_mmu4d, value_mmu4e, value_mmu4f;
    
    div = tag / 10;

    switch(mode)
    {
        case 0:
            if(div == 4)
            {
                value_ip08 = 0x14;
                value_mmu4d = 0x28;
                GetDevice()->WriteByte(IP08, value_ip08);
                GetDevice()->WriteByte(MMU4D, value_mmu4d);
            }
            else
            if(div == 5)
            {
                value_ip09 = 0x14;
                value_mmu4e = 0x28;
                GetDevice()->WriteByte(IP09, value_ip09);
                GetDevice()->WriteByte(MMU4E, value_mmu4e);
            }
            else
            if(div == 3)
            {
                value_ip0a = 0x0A;
                value_mmu4f = 0x14;
                GetDevice()->WriteByte(IP0A, value_ip0a);
                GetDevice()->WriteByte(MMU4F, value_mmu4f);
            }
        break;
        case 1:
            if(div == 4)
            {
                value_ip08 = 0x15;
                value_mmu4d = 0x2A;
                GetDevice()->WriteByte(IP08, value_ip08);
                GetDevice()->WriteByte(MMU4D, value_mmu4d);
            }
            else
            if(div == 5)
            {
                value_ip09 = 0x15;
                value_mmu4e = 0x2A;
                GetDevice()->WriteByte(IP09, value_ip09);
                GetDevice()->WriteByte(MMU4E, value_mmu4e);
            }
            else
            if(div == 3)
            {
                value_ip0a = 0x0B;
                value_mmu4f = 0x15;
                GetDevice()->WriteByte(IP0A, value_ip0a);
                GetDevice()->WriteByte(MMU4F, value_mmu4f);
            }
        break;
        case 2:
            if(div == 4)
            {
                value_ip08 = 0x16;
                value_mmu4d = 0x2C;
                GetDevice()->WriteByte(IP08, value_ip08);
                GetDevice()->WriteByte(MMU4D, value_mmu4d);
            }
            else
            if(div == 5)
            {
                value_ip09 = 0x16;
                value_mmu4e = 0x2C;
                GetDevice()->WriteByte(IP09, value_ip09);
                GetDevice()->WriteByte(MMU4E, value_mmu4e);
            }
            else
            if(div == 3)
            {
                value_ip0a = 0x0B;
                value_mmu4f = 0x15;
                GetDevice()->WriteByte(IP0A, value_ip0a);
                GetDevice()->WriteByte(MMU4F, value_mmu4f);
            }
        break;
        case 3:
            if(div == 4)
            {
                value_ip08 = 0x17;
                value_mmu4d = 0x2F;
                GetDevice()->WriteByte(IP08, value_ip08);
                GetDevice()->WriteByte(MMU4D, value_mmu4d);
            }
            else
            if(div == 5)
            {
                value_ip09 = 0x17;
                value_mmu4e = 0x2F;
                GetDevice()->WriteByte(IP09, value_ip09);
                GetDevice()->WriteByte(MMU4E, value_mmu4e);
            }
            else
            if(div == 3)
            {
                value_ip0a = 0x0C;
                value_mmu4f = 0x18;
                GetDevice()->WriteByte(IP0A, value_ip0a);
                GetDevice()->WriteByte(MMU4F, value_mmu4f);
            }
        break;
        case 4:
            if(div == 4)
            {
                value_ip08 = 0x1B;
                value_mmu4d = 0x36;
                GetDevice()->WriteByte(IP08, value_ip08);
                GetDevice()->WriteByte(MMU4D, value_mmu4d);
            }
            else
            if(div == 5)
            {
                value_ip09 = 0x1B;
                value_mmu4e = 0x36;
                GetDevice()->WriteByte(IP09, value_ip09);
                GetDevice()->WriteByte(MMU4E, value_mmu4e);
            }
            else
            if(div == 3)
            {
                value_ip0a = 0x0C;
                value_mmu4f = 0x18;
                GetDevice()->WriteByte(IP0A, value_ip0a);
                GetDevice()->WriteByte(MMU4F, value_mmu4f);
            }
        break;
    }

    switch(div)
    {
    case 3:
        GetDevice()->ReadByte(ADDR_BYPass+3, value_ip);
        GetDevice()->ReadByte(ADDR_MMUByPass, value_mmu);
        value_ip &= 0xF8;
        value_ip |= mode;
        value_mmu &= 0x8F;
        value_mmu |= (mode<<4);
        GetDevice()->WriteByte(ADDR_BYPass+3, value_ip);
        GetDevice()->WriteByte(ADDR_MMUByPass, value_mmu);
    break;
    case 4:
        GetDevice()->ReadByte(ADDR_BYPass+1, value_ip);
        GetDevice()->ReadByte(ADDR_MMUByPass+1, value_mmu);
        value_ip &= 0xF8;
        value_ip |= mode;
        value_mmu &= 0x8F;
        value_mmu |= (mode<<4);
        GetDevice()->WriteByte(ADDR_BYPass+1, value_ip);
        GetDevice()->WriteByte(ADDR_MMUByPass+1, value_mmu);
    break;
    case 5:
        GetDevice()->ReadByte(ADDR_BYPass+2, value_ip);
        GetDevice()->ReadByte(ADDR_MMUByPass+2, value_mmu);
        value_ip &= 0xF8;
        value_ip |= mode;
        value_mmu &= 0x8F;
        value_mmu |= (mode<<4);
        GetDevice()->WriteByte(ADDR_BYPass+2, value_ip);
        GetDevice()->WriteByte(ADDR_MMUByPass+2, value_mmu);
    break;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RB_MeY_Error_0Click(TObject *Sender)
{
    TCheckBox * cb;
    Byte value_0, value_1, value_2, value_3;
    cb = (TCheckBox *)Sender;


    GetDevice()->ReadByte(IPFC, value_0);
    GetDevice()->ReadByte(MMU64, value_1);
    GetDevice()->ReadByte(MMU65, value_2);
    GetDevice()->ReadByte(MMU66, value_3);
    value_0 &= 0xF9;
    value_1 &= 0xF9;
    value_2 &= 0xF9;
    value_3 &= 0xF9;
    if(cb->Checked)
    {
        value_0 |= (cb->Tag<<1);
        value_1 |= (cb->Tag<<1);
        value_2 |= (cb->Tag<<1);
        value_3 |= (cb->Tag<<1);
    }
    GetDevice()->WriteByte(IPFC, value_0);
    GetDevice()->WriteByte(MMU64, value_1);
    GetDevice()->WriteByte(MMU65, value_2);
    GetDevice()->WriteByte(MMU66, value_3);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RB_MeY_Test_0Click(TObject *Sender)
{
    TCheckBox * cb;
    Byte value_0, value_1, value_2, value_3;
    cb = (TCheckBox *)Sender;


    GetDevice()->ReadByte(IPFC, value_0);
    GetDevice()->ReadByte(MMU64, value_1);
    GetDevice()->ReadByte(MMU65, value_2);
    GetDevice()->ReadByte(MMU66, value_3);
    value_0 &= 0xCF;
    value_1 &= 0xCF;
    value_2 &= 0xCF;
    value_3 &= 0xCF;
    if(cb->Checked)
    {
        value_0 |= (cb->Tag<<4);
        value_1 |= (cb->Tag<<4);
        value_2 |= (cb->Tag<<4);
        value_3 |= (cb->Tag<<4);
    }
    GetDevice()->WriteByte(IPFC, value_0);
    GetDevice()->WriteByte(MMU64, value_1);
    GetDevice()->WriteByte(MMU65, value_2);
    GetDevice()->WriteByte(MMU66, value_3);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RB_McY_Error_0Click(TObject *Sender)
{
    TCheckBox * cb;
    Byte value_0, value_1, value_2;

    cb = (TCheckBox *)Sender;

    GetDevice()->ReadByte(IPF9, value_0);
    GetDevice()->ReadByte(MMU68, value_1);
    GetDevice()->ReadByte(MMU6A, value_2);
    value_0 &= 0xF9;
    value_1 &= 0xF9;
    value_2 &= 0xF9;
    if(cb->Checked)
    {
        value_0 |= (cb->Tag<<1);
        value_1 |= (cb->Tag<<1);
        value_2 |= (cb->Tag<<1);
    }
    GetDevice()->WriteByte(IPF9, value_0);
    GetDevice()->WriteByte(MMU68, value_1);
    GetDevice()->WriteByte(MMU6A, value_2);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RB_McY_Test_0Click(TObject *Sender)
{
    TCheckBox * cb;
    Byte value_0, value_1, value_2;

    cb = (TCheckBox *)Sender;

    GetDevice()->ReadByte(IPF9, value_0);
    GetDevice()->ReadByte(MMU68, value_1);
    GetDevice()->ReadByte(MMU6A, value_2);
    value_0 &= 0xCF;
    value_1 &= 0xCF;
    value_2 &= 0xCF;
    if(cb->Checked)
    {
        value_0 |= (cb->Tag<<4);
        value_1 |= (cb->Tag<<4);
        value_2 |= (cb->Tag<<4);
    }
    GetDevice()->WriteByte(IPF9, value_0);
    GetDevice()->WriteByte(MMU68, value_1);
    GetDevice()->WriteByte(MMU6A, value_2);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RB_McC_Error_0Click(TObject *Sender)
{
    TCheckBox * cb;
    Byte value_0, value_1, value_2, value_3;
    cb = (TCheckBox *)Sender;
    
    GetDevice()->ReadByte(IPFA, value_0);
    GetDevice()->ReadByte(IPFB, value_1);
    GetDevice()->ReadByte(MMU69, value_2);
    GetDevice()->ReadByte(MMU6B, value_3);
    value_0 &= 0xF9;
    value_1 &= 0xF9;
    value_2 &= 0xF9;
    value_3 &= 0xF9;
    if(cb->Checked)
    {
        value_0 |= (cb->Tag<<1);
        value_1 |= (cb->Tag<<1);
        value_2 |= (cb->Tag<<1);
        value_3 |= (cb->Tag<<1);
    }
    GetDevice()->WriteByte(IPFA, value_0);
    GetDevice()->WriteByte(IPFB, value_1);
    GetDevice()->WriteByte(MMU69, value_2);
    GetDevice()->WriteByte(MMU6B, value_3);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RB_McC_Test_0Click(TObject *Sender)
{
    TCheckBox * cb;
    Byte value_0, value_1, value_2, value_3;
    cb = (TCheckBox *)Sender;


    GetDevice()->ReadByte(IPFA, value_0);
    GetDevice()->ReadByte(IPFB, value_1);
    GetDevice()->ReadByte(MMU69, value_2);
    GetDevice()->ReadByte(MMU6B, value_3);
    value_0 &= 0xCF;
    value_1 &= 0xCF;
    value_2 &= 0xCF;
    value_3 &= 0xCF;
    if(cb->Checked)
    {
        value_0 |= (cb->Tag<<4);
        value_1 |= (cb->Tag<<4);
        value_2 |= (cb->Tag<<4);
        value_3 |= (cb->Tag<<4);
    }
    GetDevice()->WriteByte(IPFA, value_0);
    GetDevice()->WriteByte(IPFB, value_1);
    GetDevice()->WriteByte(MMU69, value_2);
    GetDevice()->WriteByte(MMU6B, value_3);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::RadioButton11Click(TObject *Sender)
{
    TRadioButton * sb;
    Byte Value_DCbypass;
    unsigned int value_mmu;

    sb = (TRadioButton *)Sender;
    GetDevice()->ReadByte(ADDR_BYPass, Value_DCbypass);
    GetDevice()->ReadDWord(ADDR_MMUByPass, value_mmu);
    value_mmu &= 0xFFFEFEFE;
    Value_DCbypass &=0xF8;
    if(sb->Checked)
    {
        Value_DCbypass |= 0x07;
        value_mmu |= 0x00010101;
    }
    GetDevice()->WriteByte(ADDR_BYPass, Value_DCbypass);
    GetDevice()->WriteDWord(ADDR_MMUByPass, value_mmu);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::rb_888Click(TObject *Sender)
{
    Byte value, y_burst, c_burst, qy_burst, y_len, c_len, qy_len;
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;

    GetDevice()->ReadByte(0xE000003A, value);
    value &= 0xF3;
    switch(rb->Tag)
    {
        case 0:
            value |= 0x0C;
            y_burst = 0x1E;
            c_burst = 0x1E;
            qy_burst = 0x0F;
            y_len = 0x3C;
            c_len = 0x3C;
            qy_len = 0x1E;
        break;
        case 1:
            value |= 0x00;
            y_burst = 0x2B;
            c_burst = 0x2B;
            qy_burst = 0x0F;
            y_len = 0x4B;
            c_len = 0x4B;
            qy_len = 0x1E;
        break;
        case 2:
            value |= 0x04;
            y_burst = 0x26;
            c_burst = 0x26;
            qy_burst = 0x0F;
            y_len = 0x4B;
            c_len = 0x3C;
            qy_len = 0x1E;
        break;
    }
    GetDevice()->WriteByte(0xE000003A, value);
    if(CB_McY_DC_Bypass->Checked)
    {
        GetDevice()->WriteByte(0xE0000108, y_burst);
        GetDevice()->WriteByte(0xE0000B4D, y_len);
    }
    if(CB_McC_DC_Bypass->Checked)
    {
        GetDevice()->WriteByte(0xE0000109, c_burst);
        GetDevice()->WriteByte(0xE0000B4E, c_len);
    }
    if(CB_MeY_DC_Bypass->Checked)
    {
        GetDevice()->WriteByte(0xE000010A, qy_burst);
        GetDevice()->WriteByte(0xE0000B4F, qy_len);
    }

}
//---------------------------------------------------------------------------
void __fastcall TFrame_DataPath::Refresh()
{
    Byte bval;
    unsigned int val;

    GetDevice()->ReadByte(FRC_TOP3A, bval);
    if((bval & 0x01) == 0x01)
    {
        rb_VD->Checked = true;
    }
    else
    {
        rb_PC->Checked = true;
    }

    if((bval & 0x0C) == 0x00)
    {
        rb_101010->Checked = true;
    }
    else if((bval & 0x0C) == 0x0C)
    {
        rb_888->Checked = true;
    }
    else if((bval & 0x0C) == 0x08)
    {
        rb_1088->Checked = true;
    }

    GetDevice()->ReadDWord(ADDR_BYPass, val);
    if((val & 0x01) == 0x01)
    {
        CB_McY_DC_Bypass->Checked = true;
    }
    else
    {
        CB_McY_DC_Bypass->Checked = false;
    }

    if((val & 0x02) == 0x02)
    {
        CB_McC_DC_Bypass->Checked = true;
    }
    else
    {
        CB_McC_DC_Bypass->Checked = false;
    }

    if((val & 0x04) == 0x04)
    {
        CB_MeY_DC_Bypass->Checked = true;
    }
    else
    {
        CB_MeY_DC_Bypass->Checked = false;
    }

    if((val & 0x10) == 0x10)
    {
        CB_McY_LastLine_Bypass->Checked = true;
    }
    else
    {
        CB_McY_LastLine_Bypass->Checked = false;
    }

    if((val & 0x20) == 0x20)
    {
        CB_McC_LastLine_Bypass->Checked = true;
    }
    else
    {
        CB_McC_LastLine_Bypass->Checked = false;
    }

    if((val & 0x40) == 0x40)
    {
        CB_MeY_LastLine_Bypass->Checked = true;
    }
    else
    {
        CB_MeY_LastLine_Bypass->Checked = false;
    }

    //GetDevice()->ReadByte(ADDR_BYPass+1,bval);
    switch((val>>8) & 0x07)
    {
        case 0:
            RB_McY_DC_mode0->Checked = true;
            break;
        case 1:
            RB_McY_DC_mode1->Checked = true;
            break;
        case 2:
            RB_McY_DC_mode2->Checked = true;
            break;
        case 3:
            RB_McY_DC_mode3->Checked = true;
            break;
        case 4:
            RB_McY_DC_mode4->Checked = true;
            break;
    }

    //GetDevice()->ReadByte(ADDR_BYPass+2,bval);
    switch((val>>16) & 0x07)
    {
        case 0:
            RB_McC_DC_mode0->Checked = true;
            break;
        case 1:
            RB_McC_DC_mode1->Checked = true;
            break;
        case 2:
            RB_McC_DC_mode2->Checked = true;
            break;
        case 3:
            RB_McC_DC_mode3->Checked = true;
            break;
        case 4:
            RB_McC_DC_mode4->Checked = true;
            break;
    }
    
    //GetDevice()->ReadByte(ADDR_BYPass+3,bval);
    switch((val>>24) & 0x07)
    {
        case 0:
            RB_MeY_DC_mode0->Checked = true;
            break;
        case 1:
            RB_MeY_DC_mode1->Checked = true;
            break;
        case 2:
            RB_MeY_DC_mode2->Checked = true;
            break;
        case 3:
            RB_MeY_DC_mode3->Checked = true;
            break;
        case 4:
            RB_MeY_DC_mode4->Checked = true;
            break;
    }
}

void __fastcall TFrame_DataPath::Button1Click(TObject *Sender)
{
    Refresh();    
}
//---------------------------------------------------------------------------


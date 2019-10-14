//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_Debug.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCFrame"
#pragma link "RegEdit"
#pragma link "RegRadioButton"
#pragma link "RegScrollBar"
#pragma resource "*.dfm"


#define IPDEBUG            0xE0000040

TFrame_Debug *Frame_Debug;
//---------------------------------------------------------------------------
__fastcall TFrame_Debug::TFrame_Debug(TComponent* Owner)
    : TMEMCFrame(Owner)
{
}
//---------------------------------------------------------------------------
unsigned int debug_pin[] =
{
    9,
    0xC00C0034, 0x00003210,
    0xC00C0030, 0x00000000,
    0xC00C0308, 0x0000021f,
    0xC00C0304, 0x00000fff,
    0xC00C0318, 0x30303030,
    0xC00C031c, 0x30303030,
    0xC00C0320, 0x30303030,
    0xC00C0324, 0x30303030,
    0xC00C0030, 0x00797979,
};
void __fastcall TFrame_Debug::Button12Click(TObject *Sender)
{
    unsigned int count, address, value;

    count = debug_pin[0];
    for(int i=0; i < (int)count; i++)
    {
        address = debug_pin[2*i+1];
        value = debug_pin[2*i+2];
        GetDevice()->WriteDWord(address, value);
    }

    ReadDebugData();

}
//---------------------------------------------------------------------------
AnsiString BW_Flag[] =
{
    "7",
    "0xE0000B60",
    "CB_meiyr_lb",      "0x01",
    "CB_meiyr_pic",     "0x01",
    "CB_mepyr_lb",      "0x02",
    "CB_mepyr_pic",     "0x02",
    "CB_mei2yr_lb",     "0x04",
    "CB_mei2yr_pic",    "0x04",
    "CB_mciyr_lb",      "0x08",
    "CB_mciyr_pic",     "0x08",
    "CB_mcicr_lb",      "0x10",
    "CB_mcicr_pic",     "0x10",
    "CB_mcpyr_lb",      "0x20",
    "CB_mcpyr_pic",     "0x20",
    "CB_mcpcr_lb",      "0x40",
    "CB_mcpcr_pic",     "0x40",
};

AnsiString BW_IP_Flag[] =
{
    "4",
    "0xE000015A",
    "CB_IPy",   "0x01",
    "CB_IPcb",  "0x02",
    "CB_IPcr",  "0x04",
    "CB_IPyrd", "0x08",
};
AnsiString BW_MV_Flag[] =
{
    "5",
    "0xE0000A95",
    "CB_MV_ph_wr",   "0x01",
    "CB_MV_pi_wr",  "0x02",
    "CB_MV_ph_rd",  "0x04",
    "CB_MV_pi_rd", "0x08",
    "CB_MV_ppi_rd", "0x10"
};
void __fastcall TFrame_Debug::btn_RefreshClick(TObject *Sender)
{
    TCheckBox * cb;
    String s_compo, s_mask, s_count, s_add;
    unsigned int value;
    int v_count, v_mask;
    Byte v_mmu60, v_mmu61, v_ip5a;

    s_count = BW_Flag[0];
    v_count = s_count.ToInt();
    s_add = BW_Flag[1];
    GetDevice()->ReadDWord((unsigned int)s_add.ToInt(),value);
    v_mmu60 = value & 0x000000FF;
    v_mmu61 = (value>>8) & 0x000000FF;
    for(int i=0; i<v_count; i++)
    {
        s_compo = BW_Flag[i*2+2];
        s_mask = BW_Flag[i*2+3];
        cb = (TCheckBox *)FindComponent(s_compo);
        if(i % 2)
        {
            v_mask = s_mask.ToInt();
            cb->Checked = ((v_mmu61 & v_mask)==v_mask)? true:false;
        }
        else
        {
            v_mask = s_mask.ToInt();
            cb->Checked = ((v_mmu60 & v_mask)==v_mask)?true:false;
        }
    }

    s_count = BW_IP_Flag[0];
    v_count = s_count.ToInt();
    s_add = BW_IP_Flag[1];
    GetDevice()->ReadByte((unsigned int)s_add.ToInt(),v_ip5a);
    for(int i=0; i< v_count; i++)
    {
        s_compo = BW_IP_Flag[i*2+2];
        s_mask = BW_IP_Flag[i*2+3];
        cb = (TCheckBox *)FindComponent(s_compo);
        v_mask = s_mask.ToInt();
        cb->Checked = ((v_ip5a & v_mask)==v_mask)?true:false;
    }

    s_count = BW_MV_Flag[0];
    v_count = s_count.ToInt();
    s_add = BW_MV_Flag[1];
    GetDevice()->ReadByte((unsigned int)s_add.ToInt(),v_ip5a);
    for(int i=0; i< v_count; i++)
    {
        s_compo = BW_MV_Flag[i*2+2];
        s_mask = BW_MV_Flag[i*2+3];
        cb = (TCheckBox *)FindComponent(s_compo);
        v_mask = s_mask.ToInt();
        cb->Checked = ((v_ip5a & v_mask)==v_mask)?true:false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Debug::SpeedButton1Click(TObject *Sender)
{
    unsigned int v_mmu;
    Byte v_ip;
    Byte v_mv;

    GetDevice()->ReadDWord(0xE0000B60, v_mmu);
    GetDevice()->ReadByte(0xE000015A, v_ip);
    GetDevice()->ReadByte(0xE0000A95, v_mv);

    v_mmu &= 0xFFFF8080;
    v_mmu |= 0x00007F7F;
    v_ip &= 0xF0;
    v_ip |= 0x0F;
    v_mv &= 0xE0;
    v_mv |= 0x1F;

    GetDevice()->WriteDWord(0xE0000B60, v_mmu);
    GetDevice()->WriteByte(0xE000015A, v_ip);
    GetDevice()->WriteByte(0xE0000A95, v_mv);

    btn_Refresh->Click();    
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Debug::SB_sigScroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    AnsiString strName;
    TScrollBar * sb;
    TEdit * ed;


    if (ScrollCode == scEndScroll)
    {
        sb = (TScrollBar *)Sender;
        strName = sb->Name;
        strName.Delete(1,3);
        strName.Insert("Ed_",1);
        ed = (TEdit *)FindComponent(strName);
        ed->Text = IntToStr(sb->Position);
        WriteDebugData();
    }        
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Debug::CB_DebugPortClick(TObject *Sender)
{
    WriteDebugData();    
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Debug::WriteDebugData()
{
    Byte v_40, v_41, v_42, v_43;
    unsigned int value;

    v_40 = SB_sig->Position;
    v_41 = SB_sig1->Position;
    v_42 = SB_low->Position;
    v_43 = SB_high->Position;

    v_42 |= CB_DebugPort->Checked ? 0x80:0x00;
    v_43 |= CB_DebugByte->Checked ? 0x80:0x00;

    value = (v_43<<24)|(v_42<<16)|(v_41<<8)|(v_40);

    GetDevice()->WriteDWord(IPDEBUG, value);
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Debug::ReadDebugData()
{
    Byte v_40, v_41, v_42, v_43;
    unsigned int value;
    
    GetDevice()->ReadDWord(IPDEBUG, value);

    v_40 = value && 0x000000FF;
    v_41 = (value>>8) && 0x000000FF;
    v_42 = (value>>16) && 0x000000FF;
    v_43 = (value>>24) && 0x000000FF;

    SB_sig->Position = v_40;
    SB_sig1->Position = v_41;
    SB_low->Position = v_42 & 0x7F;
    SB_high->Position = v_43 & 0x7F;
    Ed_sig->Text = IntToStr(v_40);
    Ed_sig1->Text = IntToStr(v_41);
    Ed_low->Text = IntToStr(v_42);
    Ed_high->Text = IntToStr(v_43);
    CB_DebugPort->Checked = ((v_42 & 0x80)==0x80)? true:false;
    CB_DebugByte->Checked = ((v_43 & 0x80)==0x80)? true:false;

}
//---------------------------------------------------------------------------
void __fastcall TFrame_Debug::Ed_sigKeyPress(TObject *Sender, char &Key)
{
    TEdit * ed;
    TScrollBar * sb;
    String strName;
    int value;

    ed = (TEdit *)Sender;

    if(Key == VK_RETURN)
    {
        value = StrToInt(ed->Text);
        strName = ed->Name;
        strName.Delete(1,3);
        strName.Insert("SB_",1);
        sb = (TScrollBar *)FindComponent(strName);
        value = value > 255 ? 255:value;
        sb->Position = value;
        ed->Text = IntToStr(value);
        WriteDebugData();
    }    

    if(!(Key>='0' && Key<='9'))
    {
        Key = 0;
    }    
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UUI312_Chip.h"
#include "RegCheckBox.h"
#include "RegLabeledEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma link "RegEdit"
#pragma link "RegScrollBar"
#pragma resource "*.dfm"
TForm_UI312_Chip *Form_UI312_Chip;

unsigned int FRC_Smooth[] =
{
    12,
    0xE000092C, 4, 4, 0x0F,
    0xE0000804, 0, 8, 0x12,
    0xE0000F9C, 0, 8, 0xD0,
    0xE0000F9D, 0, 8, 0xD0,
    0xE0000F00, 0, 8, 0x28,
    0xE0000F9F, 0, 3, 0x00,
    0xE0000F97, 0, 8, 0x2C,
    0xE0000C8F, 0, 8, 0x01,
    0xE0000546, 0, 8, 0x0E,
    0xE0000547, 0, 8, 0x04,
    0xE00005CE, 0, 8, 0x0E,
    0xE00005CF, 0, 8, 0x04,

    0xE0000F96, 0, 8, 0xFF,
};
unsigned int FRC_Standard[] =
{
    12,
    0xE000092C, 4, 4, 0x00,
    0xE0000804, 0, 8, 0x12,
    0xE0000F9C, 0, 8, 0xE4,
    0xE0000F9D, 0, 8, 0xC0,
    0xE0000F00, 0, 8, 0x4C,
    0xE0000F9F, 0, 3, 0x02,
    0xE0000F97, 0, 8, 0x3C,
    0xE0000C8F, 0, 8, 0x02,
    0xE0000546, 0, 8, 0x0E,
    0xE0000547, 0, 8, 0x01,
    0xE00005CE, 0, 8, 0x0E,
    0xE00005CF, 0, 8, 0x01,

    0xE0000F96, 0, 8, 0xFF,
};
unsigned int FRC_Clear[] =
{
    12,
    0xE000092C, 4, 4, 0x00,
    0xE0000804, 0, 8, 0x08,
    0xE0000F9C, 0, 8, 0xE4,
    0xE0000F9D, 0, 8, 0xC0,
    0xE0000F00, 0, 8, 0x28,
    0xE0000F9F, 0, 3, 0x00,
    0xE0000F97, 0, 8, 0x3C,
    0xE0000C8F, 0, 8, 0x04,
    0xE0000546, 0, 8, 0x08,
    0xE0000547, 0, 8, 0x01,
    0xE00005CE, 0, 8, 0x08,
    0xE00005CF, 0, 8, 0x01,

    0xE0000F96, 0, 8, 0xFF,
};


AnsiString TForm_UI312_Chip::rgb_conres[]=
{
    "9",
    "RegScrollBar_RGain", "RegLabeledEdit1" ,
    "RegScrollBar_GGain", "RegLabeledEdit2" ,
    "RegScrollBar_BGain", "RegLabeledEdit3" ,

    "RegScrollBar_ROff", "RegLabeledEdit4" ,
    "RegScrollBar_GOff", "RegLabeledEdit5" ,
    "RegScrollBar_BOff", "RegLabeledEdit6" ,

    "RegScrollBar_RLmt", "RegLabeledEdit7" ,
    "RegScrollBar_GLmt", "RegLabeledEdit8" ,
    "RegScrollBar_BLmt", "RegLabeledEdit9" ,

};
//---------------------------------------------------------------------------
__fastcall TForm_UI312_Chip::TForm_UI312_Chip(TComponent* Owner)
    : TMEMCForm(Owner)
{
}

AnsiString __fastcall TForm_UI312_Chip::getEditName(int i)
{
    return rgb_conres[2*i+2];
}

int __fastcall TForm_UI312_Chip::getconCount()
{
    int i;
    i = rgb_conres[0].ToInt();
    return i;
}
AnsiString __fastcall TForm_UI312_Chip::getScrollName(int i)
{
    return rgb_conres[2*i+1];
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm_UI312_Chip::rg_Input_ModeClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;

    if(!MailBox_Available()) return;
    switch(rg->ItemIndex)
    {
        case 0: //VD
            WriteFormatPara(0x9f020040, 0, 1, 0x0);
            break;
        case 1: //PC
            WriteFormatPara(0x9f020040, 0, 1, 0x1);
            break;
    }
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f020040);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x00000040);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_UI312_Chip::rg_Output_FormatClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;
    if(!MailBox_Available()) return;
    switch(rg->ItemIndex)
    {
        case 0: //2D
            WriteFormatPara(0x9f020050, 4, 4, 0x1);
            //WriteFormatPara(0x9f020047, 0, 8, 0x0);
            break;
        case 1: //3D_PR
            WriteFormatPara(0x9f020050, 4, 4, 0x2);
            //WriteFormatPara(0x9f020047, 0, 8, 0x0);
            break;
        case 2: //3D_SG
            WriteFormatPara(0x9f020050, 4, 4, 0x4);
            //WriteFormatPara(0x9f020047, 0, 8, 0x0);
            break;
        case 3: //3D_SG_SS
            WriteFormatPara(0x9f020050, 4, 4, 0x8);
            //WriteFormatPara(0x9f020047, 0, 8, 0x01);
            break;
    }
    tb_Depth->Position = 7;
    tb_Disparity->Position = 5;
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f020050);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x04070050);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_UI312_Chip::rg_Input_FormatClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;
    if(!MailBox_Available()) return;
    switch(rg->ItemIndex)
    {
        case 0: //2D
            WriteFormatPara(0x9f020050, 0, 4, 0x1);
            break;
        case 1: //3D_L/R
            WriteFormatPara(0x9f020050, 0, 4, 0x8);
            break;
        case 2: //3D_TB
            WriteFormatPara(0x9f020050, 0, 4, 0x4);
            break;
        case 3: //3D_SBS
            WriteFormatPara(0x9f020050, 0, 4, 0x2);
            break;
    }
    tb_Depth->Position = 7;
    tb_Disparity->Position = 5;
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f020050);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x00030050);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::rg_SwapLRClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;
    if(!MailBox_Available()) return;
    switch(rg->ItemIndex)
    {
        case 0: //L2R
            WriteFormatPara(0x9f020047, 0, 8, 0x00);
            break;
        case 1: //R2L
            WriteFormatPara(0x9f020047, 0, 8, 0x01);
            break;
    }
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f020044);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x181F0044);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::tb_DepthChange(TObject *Sender)
{
    TTrackBar * bar;
    bar = (TTrackBar * )Sender;
    if(!MailBox_Available()) return;
    WriteFormatPara(0x9f020052, 0, 8, bar->Position);
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f020050);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x10170050);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::tb_DisparityChange(TObject *Sender)
{
    TTrackBar * bar;
    bar = (TTrackBar * )Sender;
    if(!MailBox_Available()) return;
    WriteFormatPara(0x9f020051, 0, 8, bar->Position);
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f020050);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x080F0050);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::tb_FRCChange(TObject *Sender)
{
    TTrackBar * bar;
    bar = (TTrackBar * )Sender;
    if(!MailBox_Available())    return;
    //WriteFormatPara(0x9f020045, 0, 8, bar->Position);
    frc_level = bar->Position;
    //WriteFormatPara(0xE0000F93, 0, 4, frc_level);
    GetDevice()->WriteByte(0x9f02004C,frc_level);
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f02004C);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x00087004C);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::tb_DejudderChange(TObject *Sender)
{
    TTrackBar * bar;
    bar = (TTrackBar * )Sender;
    if(!MailBox_Available())    return;
    dejudder_level = bar->Position;
    GetDevice()->WriteByte(0x9f020046,dejudder_level);
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f020044);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x10170044);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::Button1Click(TObject *Sender)
{
    unsigned int val_44, val_50, val_40, val_4C;
    TRegLabeledEdit * rle;
        TRegCheckBox * rcb;
    TRegScrollBar *rsl;
    rle_Mute->Refresh();
    rle_Test_Pattern->Refresh();
    //rcb_FRC->Refresh();
    rcb_panel->Refresh();
    rcb_bbPanel->Refresh();

    rle_PWM_Duty->Refresh();
    rle_PWM_Freq->Refresh();
    rle_3DPWM_Duty->Refresh();
    rle_3DPWM_Delay->Refresh();
    rle_BT_Delay->Refresh();
    rle_BT_Duty->Refresh();

    for(int i=0;i<gb_WB->ControlCount;i++)
    {
        if(gb_WB->Controls[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)gb_WB->Controls[i];
            rle->Refresh();
        }
        else if(gb_WB->Controls[i]->ClassNameIs("TRegScrollBar"))
        {
            rsl = (TRegScrollBar *)gb_WB->Controls[i];
            rsl->Refresh();
        }
        else if(Components[i]->ClassNameIs("TRegCheckBox"))
        {
            rcb = (TRegCheckBox *)Components[i];
            rcb->Refresh();
        }
    }
    

    GetDevice()->ReadDWord(0x9f020040, val_40);
    GetDevice()->ReadDWord(0x9f020044, val_44);
    GetDevice()->ReadDWord(0x9f02004C, val_4C);
    GetDevice()->ReadDWord(0x9f020050, val_50);

    rg_Input_Mode->ItemIndex = (val_40 & 0x00000001);
    switch(val_50 & 0x0F)
    {
        case 1:
            rg_Input_Format->ItemIndex =   0;
            break;
        case 2:
            rg_Input_Format->ItemIndex =   3;
            break;
        case 4:
            rg_Input_Format->ItemIndex =   2;
            break;
        case 8:
            rg_Input_Format->ItemIndex =   1;
            break;
    }

    switch((val_50 & 0xF0)>>4)
    {
        case 1:
            rg_Output_Format->ItemIndex =   0;
            break;
        case 2:
            rg_Output_Format->ItemIndex =   1;
            break;
        case 4:
            rg_Output_Format->ItemIndex =   2;
            break;
        case 8:
            rg_Output_Format->ItemIndex =   3;
            break;
    }
    
    rg_OutFre->ItemIndex = (val_4C & 0x00F00000)>>20;
    rg_frc->ItemIndex = ((val_44 & 0x0000FF00)>>8);
    rg_SwapLR->ItemIndex = ((val_44 & 0xFF000000) >> 24);
    tb_Depth->Position = ((val_50 & 0x00FF0000) >> 16);
    tb_Disparity->Position = ((val_50 & 0x0000FF00) >> 8);
    tb_FRC->Position = ((val_4C & 0x000000FF));
    tb_Dejudder->Position = ((val_44 & 0x00FF0000) >> 16);
    //rle_PR->Refresh();
    //rle_I->Refresh();
    //rle_L->Refresh();
    //rle_T->Refresh();
    //rle_PWM_Freq->Refresh();
    //rle_PWM_Duty->Refresh();            
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::Button2Click(TObject *Sender)
{
    for(int i=0; i<1000; i++)
    {
        rg_Input_Mode->ItemIndex = 0;

        Sleep(1000);
        rg_Input_Mode->ItemIndex = 1;
        Sleep(1000);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_UI312_Chip::FRCLevel(En_frcLevel en_mode)
{
    if(!MailBox_Available())    return;
    GetDevice()->WriteByte(0x9f020045,en_mode);
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f020044);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x080F0044);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::rg_OutFreClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;
    if(!MailBox_Available())
    {
        ShowMessage("mail box not clear");
        return;
    }

    //0x9F02004C[20-23]
    WriteFormatPara(0x9f02004C, 20, 4, rg->ItemIndex);
    if(MailBoxType == mbt_MBADDR)
    {
        MailBox_SendAddress(0x9f02004C);
    }
    else if(MailBoxType == mbt_MBBITS)
    {
        MailBox_SendAddress(0x1417004C);
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_UI312_Chip::rg_frcClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;

    FRCLevel((En_frcLevel)rg->ItemIndex);
}
//---------------------------------------------------------------------------



void __fastcall TForm_UI312_Chip::FormShow(TObject *Sender)
{
    TRegLabeledEdit * rle;
    TRegCheckBox * rcb;
    TRegScrollBar *rsl;
    MailBoxType = rg_Mailbox->ItemIndex;
    for(int i=0;i<this->ComponentCount;i++)
    {
        if(Components[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)Components[i];
            if(rle->Tag != 1)
            {
                rle->MailBox = MailBoxType;
            }
        }
        else if(Components[i]->ClassNameIs("TRegCheckBox"))
        {
            rcb = (TRegCheckBox *)Components[i];
            if(rcb->Tag != 1)
            {
                rcb->MailBox = MailBoxType;
            }
        }
        else if(Components[i]->ClassNameIs("TRegScrollBar"))
        {
            rsl = (TRegScrollBar *)Components[i];
            if(rsl->Tag != 1)
            {
                rsl->MailBox = MailBoxType;
            }
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::rg_MailboxClick(TObject *Sender)
{
    TRegLabeledEdit * rle;
    TRegCheckBox * rcb;
    TRegScrollBar *rsl;
    MailBoxType = rg_Mailbox->ItemIndex;
    for(int i=0;i<this->ComponentCount;i++)
    {
        if(Components[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)Components[i];
            if(rle->Tag != 1)
            {
                rle->MailBox = MailBoxType;
            }
        }
        else if(Components[i]->ClassNameIs("TRegCheckBox"))
        {
            rcb = (TRegCheckBox *)Components[i];
            if(rcb->Tag != 1)
            {
                rcb->MailBox = MailBoxType;
            }
        }
        else if(Components[i]->ClassNameIs("TRegScrollBar"))
        {
            rsl = (TRegScrollBar *)Components[i];
            if(rsl->Tag != 1)
            {
                rsl->MailBox = MailBoxType;
            }
        }
    }
}

void __fastcall TForm_UI312_Chip::RegEditExit(TObject *Sender)
{
        //TODO: Add your source code here
    Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();

}

void __fastcall TForm_UI312_Chip::RegEditKeyPress(TObject * Sender, char &Key)
{
        //TODO: Add your source code here
     if(Key == 13)
    {
        Find((TRegEdit * )Sender)->Position = ((TRegEdit * )Sender)->Text.ToInt();
    }
}


void __fastcall TForm_UI312_Chip::RegScrollBarScroll(TObject * Sender, TScrollCode ScrollCode, int & ScrollPos)
{
        //TODO: Add your source code here
    if(ScrollCode == scEndScroll)
    {
        Find((TRegScrollBar * )Sender)->Text = IntToStr(ScrollPos);
    }
}
//---------------------------------------------------------------------------



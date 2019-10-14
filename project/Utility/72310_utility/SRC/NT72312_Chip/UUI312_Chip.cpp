//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UUI312_Chip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TForm_UI312_Chip *Form_UI312_Chip;
//---------------------------------------------------------------------------
__fastcall TForm_UI312_Chip::TForm_UI312_Chip(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_UI312_Chip::rg_Input_ModeClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;
    switch(rg->ItemIndex)
    {
        case 0: //VD
            WriteFormatPara(0x9f020040, 0, 8, 0x0);
            break;
        case 1: //PC
            WriteFormatPara(0x9f020040, 0, 8, 0x1);
            break;
    }
        
}
//---------------------------------------------------------------------------
void __fastcall TForm_UI312_Chip::rg_Output_FormatClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;
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
}
//---------------------------------------------------------------------------
void __fastcall TForm_UI312_Chip::rg_Input_FormatClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;
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
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::rg_SwapLRClick(TObject *Sender)
{
    TRadioGroup * rg;
    rg = (TRadioGroup *)Sender;
    switch(rg->ItemIndex)
    {
        case 0: //L2R
            WriteFormatPara(0x9f020047, 0, 8, 0x00);
            break;
        case 1: //R2L
            WriteFormatPara(0x9f020047, 0, 8, 0x01);
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::tb_DepthChange(TObject *Sender)
{
    TTrackBar * bar;
    bar = (TTrackBar * )Sender;
    WriteFormatPara(0x9f020052, 0, 8, bar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::tb_DisparityChange(TObject *Sender)
{
    TTrackBar * bar;
    bar = (TTrackBar * )Sender;
    WriteFormatPara(0x9f020051, 0, 8, bar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::tb_FRCChange(TObject *Sender)
{
    TTrackBar * bar;
    bar = (TTrackBar * )Sender;
    WriteFormatPara(0x9f020045, 0, 8, bar->Position);    
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::tb_DejudderChange(TObject *Sender)
{
    TTrackBar * bar;
    bar = (TTrackBar * )Sender;
    WriteFormatPara(0x9f020046, 0, 8, bar->Position);    
}
//---------------------------------------------------------------------------

void __fastcall TForm_UI312_Chip::Button1Click(TObject *Sender)
{
    //
    unsigned int val_44, val_50, val_40;
    rcb_Mute->Refresh();
    rle_Test_Pattern->Refresh();
    GetDevice()->ReadDWord(0x9f020040, val_40);
    GetDevice()->ReadDWord(0x9f020044, val_44);
    GetDevice()->ReadDWord(0x9f020050, val_50);

    rg_Input_Mode->ItemIndex = (val_40 & 0x000000FF);
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
    rg_SwapLR->ItemIndex = ((val_44 & 0xFF000000) >> 24);
    tb_Depth->Position = ((val_50 & 0x00FF0000) >> 16);
    tb_Disparity->Position = ((val_50 & 0x0000FF00) >> 8);
    tb_FRC->Position = ((val_44 & 0x0000FF00) >> 8);
    tb_Dejudder->Position = ((val_44 & 0x00FF0000) >> 16);
    rle_PWM_Freq->Refresh();
    rle_PWM_Duty->Refresh();            
}
//---------------------------------------------------------------------------


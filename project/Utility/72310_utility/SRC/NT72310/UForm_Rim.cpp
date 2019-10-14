//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_Rim.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegCheckBox"
#pragma link "RegEdit"
#pragma link "RegScrollBar"
#pragma resource "*.dfm"
TForm_Rim *Form_Rim;
//---------------------------------------------------------------------------
__fastcall TForm_Rim::TForm_Rim(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm_Rim::force_rim_enClick(TObject *Sender)
{
        //reg_02A3[7]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::CheckBox1Click(TObject *Sender)
{
        //reg_0238[3]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit47Change(TObject *Sender)
{
        //reg_01A4[7:0], reg_01A3[7:4]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit48Change(TObject *Sender)
{
        //reg_01A6[3:0], reg_01A5[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit49Change(TObject *Sender)
{
        //reg_01A7[7:0], reg_01A6[7:4]
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit50Change(TObject *Sender)
{
        // reg_01AB[1:0], reg_01A8[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit51Change(TObject *Sender)
{
        // reg_01AB[3:2], reg_01A9[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit52Change(TObject *Sender)
{
        // reg_01AB[5:4], reg_01AA[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit53Change(TObject *Sender)
{
        //reg_01AF[1:0], reg_01AC[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit54Change(TObject *Sender)
{
        //reg_01AF[3:2], reg_01AD[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit55Change(TObject *Sender)
{
        //reg_01AF[5:4], reg_01AE[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit56Change(TObject *Sender)
{
        //reg_01A2[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::Edit11Change(TObject *Sender)
{
        // if(reg_01B0[3] == 0)
        // {
        //      (UP, POSI1) = (0xFFF);
        //      (UP, CNT1 ) = (0);
        //  }
        // else
        // {
        //      (UP, POSI1) = (reg_01B2[3:0], reg_01B1[7:0]);
        //      (UP, CNT1 ) = (reg_01BB[3:0], reg_01BA[7:0]);
        //  }

        //######  all are {reg_01B0 ~ reg_01E3 }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::apl_StringGridClick(TObject *Sender)
{
        //reg_0D30 , reg_0D34, reg_0D38, reg_0D3C
        //reg_0D31 , reg_0D35, reg_0D39, reg_0D3D
        //reg_0D32 , reg_0D36, reg_0D3A, reg_0D3E
        //reg_0D33 , reg_0D37, reg_0D3B, reg_0D3F
}
//---------------------------------------------------------------------------
void __fastcall TForm_Rim::rim_StringGridClick(TObject *Sender)
{
        //reg_0D08~reg0D27         
}
//---------------------------------------------------------------------------




void __fastcall TForm_Rim::Rim_Up_TrackBarChange(TObject *Sender)
{
    // reg_02A2[7:0], reg_02A1[7:5]
    lb_trackUp->Caption = IntToStr(Rim_Up_TrackBar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TForm_Rim::Rim_Le_TrackBarChange(TObject *Sender)
{
    //reg_02A1[2:0], reg_02A0[7:0]
    lb_trackLeft->Caption = IntToStr(Rim_Le_TrackBar->Position);    
}
//---------------------------------------------------------------------------

void __fastcall TForm_Rim::Rim_Ri_TrackBarChange(TObject *Sender)
{
    // reg_02A5[2:0], reg_02A4[7:0]
    lb_trackRight->Caption = IntToStr(Rim_Ri_TrackBar->Position); 
}
//---------------------------------------------------------------------------

void __fastcall TForm_Rim::Rim_Dn_TrackBarChange(TObject *Sender)
{
    // reg_02A6[7:0], reg_02A5[7:5]
    lb_trackDown->Caption = IntToStr(Rim_Dn_TrackBar->Position);  
}
//---------------------------------------------------------------------------


void __fastcall TForm_Rim::Button5Click(TObject *Sender)
{
    AnsiString conName;
    TButton * btn;

    for(int i=0;i<this->ComponentCount;i++)
    {
        conName = this->Components[i]->ClassName();
        if(conName == "TButton")
        {
            btn = (TButton *)this->Components[i];
            if(btn != Sender)
            {
                btn->Click();
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_Rim::Button1Click(TObject *Sender)
{
    AnsiString conName, strValue;
    TRegEdit * ed;
    Byte hivalue, tmp;
    int value;

    for(int i=0;i<setting_GroupBox->ControlCount;i++)
    {
        conName = setting_GroupBox->Controls[i]->ClassName();
        if(conName.SubString(1,4)=="TReg")
        {
            ed = (TRegEdit *)setting_GroupBox->Controls[i];
            ed->Refresh();

            if(ed->Tag>0)
            {
                GetDevice()->ReadByte(ed->RegStartAddress.ToInt()+ed->Tag, hivalue);
                try
                {
                    if(ed->TextType == ttHex)
                    {
                        strValue = "0x"+ed->Text;
                        value = strValue.ToInt();
                    }
                    else
                    {
                        value = ed->Text.ToInt();
                    }
                }
                catch(...)
                {
                    value = 0;
                }
                tmp = (hivalue >>((3-ed->Tag)*2)) & 0x03;
                value = (tmp<<8) | value;
                if(ed->TextType == ttHex)
                {
                    ed->Text = IntToHex(value,3);
                }
                else
                {
                    ed->Text = IntToStr(value);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_Rim::Button7Click(TObject *Sender)
{
    AnsiString conName;
    TRegScrollBar * rsb;
    TRegCheckBox * rcb;

    for(int i=0;i<GroupBox1->ControlCount;i++)
    {
        conName = GroupBox1->Controls[i]->ClassName();
        //ShowMessage(conName +" "+GroupBox1->Controls[i]->Name);
        if(conName.SubString(1,4)=="TReg")
        {
            if(conName == "TRegScrollBar")
            {
                rsb = (TRegScrollBar *)GroupBox1->Controls[i];
                rsb->Refresh();
            }
            if(conName == "TRegCheckBox")
            {
                rcb = (TRegCheckBox *)GroupBox1->Controls[i];
                rcb->Refresh();
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_Rim::Button3Click(TObject *Sender)
{
    AnsiString conName, strValue;
    TRegCheckBox * rcb;
    TRegEdit * ed;
    Byte hivalue, tmp;
    int value;

    for(int i=0;i<posi_cnt_detail_GroupBox->ControlCount;i++)
    {
        conName = posi_cnt_detail_GroupBox->Controls[i]->ClassName();
        if(conName.SubString(1,4)=="TReg")
        {
            if(conName == "TRegCheckBox")
            {
                rcb = (TRegCheckBox *)posi_cnt_detail_GroupBox->Controls[i];
                rcb->Refresh();
            }
            if(conName == "TRegEdit")
            {
                ed = (TRegEdit *)posi_cnt_detail_GroupBox->Controls[i];
                //ed->Refresh();

                if(ed->Tag>0)
                {
                    GetDevice()->ReadByte(ed->RegStartAddress.ToInt()+ed->Tag, hivalue);
                    try
                    {
                        if(ed->TextType == ttHex)
                        {
                            strValue = "0x"+ed->Text;
                            value = strValue.ToInt();
                        }
                        else
                        {
                            value = ed->Text.ToInt();
                        }
                    }
                    catch(...)
                    {
                        value = 0;
                    }
                    tmp = (hivalue >>((3-ed->Tag)*2)) & 0x03;
                    value = (tmp<<8) | value;
                    if(ed->TextType == ttHex)
                    {
                        ed->Text = IntToHex(value,3);
                    }
                    else
                    {
                        ed->Text = IntToStr(value);
                    }
                }
            }    
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Rim::Button4Click(TObject *Sender)
{

    AnsiString conName, strValue;
    TRegEdit * ed;
    Byte hivalue, tmp;
    int value;

    for(int i=0;i<dyn_dc_GroupBox->ControlCount;i++)
    {
        conName = dyn_dc_GroupBox->Controls[i]->ClassName();
        if(conName.SubString(1,4)=="TReg")
        {
            ed = (TRegEdit *)dyn_dc_GroupBox->Controls[i];
            ed->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Rim::Button2Click(TObject *Sender)
{
    AnsiString conName, strValue;
    TRegEdit * ed;
    Byte hivalue, tmp;
    int value;

    for(int i=0;i<GroupBox21->ControlCount;i++)
    {
        conName = GroupBox21->Controls[i]->ClassName();
        if(conName.SubString(1,4)=="TReg")
        {
            ed = (TRegEdit *)GroupBox21->Controls[i];
            ed->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Rim::Button6Click(TObject *Sender)
{
    AnsiString conName, strValue;
    TRegEdit * ed;
    Byte hivalue, tmp;
    int value;

    for(int i=0;i<OOR_motion->ControlCount;i++)
    {
        conName = OOR_motion->Controls[i]->ClassName();
        if(conName.SubString(1,4)=="TReg")
        {
            ed = (TRegEdit *)OOR_motion->Controls[i];
            ed->Refresh();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_Rim::Edit51KeyPress(TObject *Sender, char &Key)
{
    TRegEdit * re;
    int value;
    AnsiString str;
    Byte hiByte,lowByte, tmp;


    //ShowMessage(Key);
    if(Key == 13)
    {
        re = (TRegEdit *)Sender;
        if(re->TextType == ttHex)
        {
            str = "0x"+re->Text;
            value = str.ToInt();
        }
        else
        {
            value = re->Text.ToInt();
        }
        hiByte = (value>>8) & 0x03;
        lowByte = value & 0xFF;
        GetDevice()->ReadByte(re->RegStartAddress.ToInt()+re->Tag, tmp);
        tmp &= (0xFF<<(2*(3-re->Tag+1))|(0xFF>>(2*(re->Tag+1))));
        hiByte = (hiByte<<(2*(3-re->Tag)))|tmp;
        GetDevice()->WriteByte(re->RegStartAddress.ToInt()+re->Tag, hiByte);
        GetDevice()->WriteByte(re->RegStartAddress.ToInt(),lowByte);
    }
}
//---------------------------------------------------------------------------





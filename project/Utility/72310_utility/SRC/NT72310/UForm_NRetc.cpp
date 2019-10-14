//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_NRetc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma resource "*.dfm"
TForm_NRetc *Form_NRetc;
//---------------------------------------------------------------------------
__fastcall TForm_NRetc::TForm_NRetc(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Edit1Change(TObject *Sender)
{
        // reg_0c03[7:5]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox1Click(TObject *Sender)
{
        //reg_0c01[0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox2Click(TObject *Sender)
{
        //reg_0c01[2]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox3Click(TObject *Sender)
{
        //reg_0c01[1]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox9Click(TObject *Sender)
{
        //reg_0c01[3]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::RadioButton1Click(TObject *Sender)
{
        // reg_0c01[4] == 0            ?????????????????????????
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox10Click(TObject *Sender)
{
        // reg_0c03[4]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::RadioButton2Click(TObject *Sender)
{
        // reg_0c01[4] == 0             ?????????????????????
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Edit2Change(TObject *Sender)
{
        // reg_0c02[7:4]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Edit3Change(TObject *Sender)
{
        // reg_ocA6[3:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Edit4Change(TObject *Sender)
{
        // reg_0cA7[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox4Click(TObject *Sender)
{
        //reg_0c8e[2]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox5Click(TObject *Sender)
{
        // reg_0c8e[3]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox7Click(TObject *Sender)
{
        // reg_0c8e[1]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::CheckBox8Click(TObject *Sender)
{
        //reg_0c8e[0] == 0        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Edit5Change(TObject *Sender)
{
        //reg_0c8F ?????????????????????????????????????????????
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Edit6Change(TObject *Sender)
{
        //reg_0CA9[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Edit7Change(TObject *Sender)
{
        //reg_0CA8[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::RadioButton4Click(TObject *Sender)
{
        //reg_0c8e[7] == 1
        //
        Label9->Caption = "nr";
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::RadioButton5Click(TObject *Sender)
{
        //reg_0c8e[7] == 0
        Label9->Caption = "sad";        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label9Click(TObject *Sender)
{
        // if (reg_0c8e[7] == 0) cout<<"sad";
        // else  cout<<"nr";        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label10Click(TObject *Sender)
{
        // reg_0cAD[15:8], reg_0cAC[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label11Click(TObject *Sender)
{
        // reg_0cAF[15:8], reg_0cAE[7:0]       
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label12Click(TObject *Sender)
{
        // reg_0cB1[15:8], reg_0cB0[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label13Click(TObject *Sender)
{
                // reg_0cB3[15:8], reg_0cB2[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label18Click(TObject *Sender)
{
        // reg_0cB9[15:8], reg_0cB8[7:0        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label19Click(TObject *Sender)
{
        // reg_0cBB[15:8], reg_0cBA[7:0
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label20Click(TObject *Sender)
{
        // reg_0cBD[15:8], reg_0cBC[7:0
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label21Click(TObject *Sender)
{
        // reg_0CBF[15:8], reg_0CBE[7:0
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label14Click(TObject *Sender)
{
        // set reg_0C0D[0] == 0, then (reg_0CB5[15:8], reg_0CB4[7:0])
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label15Click(TObject *Sender)
{
        // set reg_0C0D[0] == 1, then reg_0CB5[15:8], reg_0CB4[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label16Click(TObject *Sender)
{

        // set reg_0C0D[1] == 0, then reg_0CB7[15:8], reg_0CB6[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label17Click(TObject *Sender)
{
        // set reg_0C0D[1] == 0, then reg_0CB7[15:8], reg_0CB6[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label24Click(TObject *Sender)
{
        //reg_0C9F[15:8], reg_0C9E[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label25Click(TObject *Sender)
{
        //reg_0C6E[23:16], reg_0C6D[15:8], reg_0C6C[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::sad_thd1Change(TObject *Sender)
{
        // reg_0C58[7:4]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::sad_thd2Change(TObject *Sender)
{
        //reg_0C58[3:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::nr0_sad_limitChange(TObject *Sender)
{
        // reg_0C56[7:4]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::nr1_sad_limitChange(TObject *Sender)
{
        //reg_0C2F[3:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::RadioButton6Click(TObject *Sender)
{
        // set reg_0C01[6] == 1        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::RadioButton7Click(TObject *Sender)
{
        // set reg_0C01[5] == 1        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::Label26Click(TObject *Sender)
{
        // h = reg_0C01[6];
        // v = reg_0c01[5];
        // cout<<"ste dir: (h,v) = ("<<h<<","<<v<<")";       ???????????????
        TLabel * lb;
        AnsiString str;
        Byte value;
        GetDevice()->ReadByte(0xE0000C01,value);
        str = "ste dir: (h,v) = ("+IntToStr(((value & 0x40==0x40)?1:0))+", "
            +IntToStr(((value & 0x20==0x20)?1:0))+")";
        lb->Caption = str;

}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::transi_thdChange(TObject *Sender)
{
        // reg_0C5E[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::ME_STEClick(TObject *Sender)
{
        //reg_0C5B
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::ste_thd2Change(TObject *Sender)
{
        // reg_0C5C
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::slope1Change(TObject *Sender)
{
        // reg_0C5D[2:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::slope2Change(TObject *Sender)
{
        //reg_0C5D[6:4]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::watershedChange(TObject *Sender)
{
        //reg_0C5A[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::nr_actionChange(TObject *Sender)
{
        //reg_0C17[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::action_thd1Change(TObject *Sender)
{
        //reg_0C13[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::action_thd2Change(TObject *Sender)
{
        //reg_0C14[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::pos_outChange(TObject *Sender)
{
        //reg_0C16[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::neg_outChange(TObject *Sender)
{
        //reg_0C15[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::smv_enClick(TObject *Sender)
{
        //reg_0C10[3]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::centerClick(TObject *Sender)
{
        //reg_0C32[7]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::smv_clr_stepChange(TObject *Sender)
{
        //reg_0C3F[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::smv_thdChange(TObject *Sender)
{
        // reg_0C31[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::zmv_thdChange(TObject *Sender)
{
        //reg_0C30[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::v0Change(TObject *Sender)
{
        //reg_0C33[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::v1Change(TObject *Sender)
{
        //reg_0C34[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::v2Change(TObject *Sender)
{
        //reg_0C35[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::v3Change(TObject *Sender)
{
        //reg_0C36[7:0]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::h0Change(TObject *Sender)
{
        //reg_0C37[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::h1Change(TObject *Sender)
{
        //reg_0C38[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::h2Change(TObject *Sender)
{
        //reg_0C39[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::h3Change(TObject *Sender)
{
        //reg_0C3A[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::inner_nr0_smv0Click(TObject *Sender)
{
        // reg_0C11[0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::inner_nr1_smv1Click(TObject *Sender)
{
        //reg_0C11[1]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::outer_nr1_smv1Click(TObject *Sender)
{
        //reg_0C11[2]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::pan_clr_enClick(TObject *Sender)
{
        // reg_0C10[7]
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::mv_diffChange(TObject *Sender)
{
        //reg_0C51[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::mv_lenChange(TObject *Sender)
{
        //reg_0C50[7:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::mv_cnt_thdChange(TObject *Sender)
{
        //reg_0c52[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::nr0_pan_clr_stepChange(TObject *Sender)
{
        //reg_0C53[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::nr1_pan_clr_stepChange(TObject *Sender)
{
        //reg_0CAA[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::LPF_181Click(TObject *Sender)
{
        //reg_0542[6] == 1        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::LPF_121Click(TObject *Sender)
{
        //reg_0542[6] == 0        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::center_onlyClick(TObject *Sender)
{
        //reg_0542[5]     ??????????????????????????
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::low_boundChange(TObject *Sender)
{
        //reg_0546[5:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::slopeChange(TObject *Sender)
{
        //reg_0547[2:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::lv_thdChange(TObject *Sender)
{
        //reg_054A[2:0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::orgClick(TObject *Sender)
{
        //reg_0234[5]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::OR_allClick(TObject *Sender)
{
        //reg_0234[6]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::short_lineClick(TObject *Sender)
{
        //reg_0237[0]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::small_cornerClick(TObject *Sender)
{
        //reg_0237[1]        
}
//---------------------------------------------------------------------------
void __fastcall TForm_NRetc::diagonal_lineClick(TObject *Sender)
{
        //reg_0237[2]        
}
//---------------------------------------------------------------------------




void __fastcall TForm_NRetc::btn_RefreshClick(TObject *Sender)
{
    AnsiString conName;
    TRegEdit * re;
    TRegLabeledEdit * rle;
    TRegCheckBox * rcb;
    TRegRadioButton * rrb;
    Byte value;

    for(int i=0;i<this->ComponentCount;i++)
    {
        conName = this->Components[i]->ClassName();
        if(conName=="TRegEdit")
        {
            re = (TRegEdit *)this->Components[i];
            if((re->Tag == 100)||(re->Tag == 101))
            {
                GetDevice()->ReadByte(0xE0000C0D, value);
                value &= 0xFE;
                value |= (re->Tag == 100) ? 0x00:0x01;
                GetDevice()->WriteByte(0xE0000C0D,value);
            }
            else if((re->Tag == 110)||(re->Tag == 111))
            {
                GetDevice()->ReadByte(0xE0000C0D, value);
                value &= 0xFD;
                value |= (re->Tag == 110) ? 0x00:0x02;
                GetDevice()->WriteByte(0xE0000C0D,value);
            }
            re->Refresh();
        }
        if(conName=="TRegCheckBox")
        {
            rcb = (TRegCheckBox *)this->Components[i];
            rcb->Refresh();
        }
        if(conName=="TRegLabeledEdit")
        {
            rle = (TRegLabeledEdit *)this->Components[i];
            rle->Refresh();
        }
        if(conName=="TRegRadioButton")
        {
            rrb = (TRegRadioButton *)this->Components[i];
            rrb->Refresh();
        }
    }
}
//---------------------------------------------------------------------------




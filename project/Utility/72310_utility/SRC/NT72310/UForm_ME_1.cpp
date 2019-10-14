//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UForm_ME_1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "RegLabeledEdit"
#pragma link "RegEdit"
#pragma link "RegCheckBox"
#pragma resource "*.dfm"
TForm_ME_1 *Form_ME_1;

AnsiString sCon[4][10][3]=
{
    {
        {"cb_ip_Enmv0", "ed_ip_mv_x0", "ed_ip_mv_y0"},
        {"cb_ip_Enmv1", "ed_ip_mv_x1", "ed_ip_mv_y1"},
        {"cb_ip_Enmv2", "ed_ip_mv_x2", "ed_ip_mv_y2"},
        {"cb_ip_Enmv3", "ed_ip_mv_x3", "ed_ip_mv_y3"},
        {"cb_ip_Enmv4", "ed_ip_mv_x4", "ed_ip_mv_y4"},
        {"cb_ip_Enmv5", "ed_ip_mv_x5", "ed_ip_mv_y5"},
        {"cb_ip_Enmv6", "ed_ip_mv_x6", "ed_ip_mv_y6"},
        {"cb_ip_Enmv7", "ed_ip_mv_x7", "ed_ip_mv_y7"},
        {"cb_ip_Enmv8", "ed_ip_mv_x8", "ed_ip_mv_y8"},
        {"cb_ip_Enmv9", "ed_ip_mv_x9", "ed_ip_mv_y9"},
    }, 
    {
        {"cb_pi_Enmv0", "ed_pi_mv_x0", "ed_pi_mv_y0"},
        {"cb_pi_Enmv1", "ed_pi_mv_x1", "ed_pi_mv_y1"},
        {"cb_pi_Enmv2", "ed_pi_mv_x2", "ed_pi_mv_y2"},
        {"cb_pi_Enmv3", "ed_pi_mv_x3", "ed_pi_mv_y3"},
        {"cb_pi_Enmv4", "ed_pi_mv_x4", "ed_pi_mv_y4"},
        {"cb_pi_Enmv5", "ed_pi_mv_x5", "ed_pi_mv_y5"},
        {"cb_pi_Enmv6", "ed_pi_mv_x6", "ed_pi_mv_y6"},
        {"cb_pi_Enmv7", "ed_pi_mv_x7", "ed_pi_mv_y7"},
        {"cb_pi_Enmv8", "ed_pi_mv_x8", "ed_pi_mv_y8"},
        {"cb_pi_Enmv9", "ed_pi_mv_x9", "ed_pi_mv_y9"},
    },
    {
        {"cb_ph_Enmv0", "ed_ph_mv_x0", "ed_ph_mv_y0"},
        {"cb_ph_Enmv1", "ed_ph_mv_x1", "ed_ph_mv_y1"},
        {"cb_ph_Enmv2", "ed_ph_mv_x2", "ed_ph_mv_y2"},
        {"cb_ph_Enmv3", "ed_ph_mv_x3", "ed_ph_mv_y3"},
        {"cb_ph_Enmv4", "ed_ph_mv_x4", "ed_ph_mv_y4"},
        {"cb_ph_Enmv5", "ed_ph_mv_x5", "ed_ph_mv_y5"},
        {"cb_ph_Enmv6", "ed_ph_mv_x6", "ed_ph_mv_y6"},
        {"cb_ph_Enmv7", "ed_ph_mv_x7", "ed_ph_mv_y7"},
        {"cb_ph_Enmv8", "ed_ph_mv_x8", "ed_ph_mv_y8"},
        {"cb_ph_Enmv9", "ed_ph_mv_x9", "ed_ph_mv_y9"},
    },                                                
    {                                                 
        {"cb_pf_Enmv0", "ed_pf_mv_x0", "ed_pf_mv_y0"},
        {"cb_pf_Enmv1", "ed_pf_mv_x1", "ed_pf_mv_y1"},
        {"cb_pf_Enmv2", "ed_pf_mv_x2", "ed_pf_mv_y2"},
        {"cb_pf_Enmv3", "ed_pf_mv_x3", "ed_pf_mv_y3"},
        {"cb_pf_Enmv4", "ed_pf_mv_x4", "ed_pf_mv_y4"},
        {"cb_pf_Enmv5", "ed_pf_mv_x5", "ed_pf_mv_y5"},
        {"cb_pf_Enmv6", "ed_pf_mv_x6", "ed_pf_mv_y6"},
        {"cb_pf_Enmv7", "ed_pf_mv_x7", "ed_pf_mv_y7"},
        {"cb_pf_Enmv8", "ed_pf_mv_x8", "ed_pf_mv_y8"},
        {"cb_pf_Enmv9", "ed_pf_mv_x9", "ed_pf_mv_y9"},
    },
};
mv_mat Mat[25] =
{
    {6,6,},
    {5,6,},
    {0,6,},
    {1,6,},
    {2,6,},
             
    {6,5,},
    {5,5,},
    {0,5,},
    {1,5,},
    {2,5,},
             
    {6,0,},
    {5,0,},
    {0,0,},
    {1,0,},
    {2,0,},
             
    {6,1,},
    {5,1,},
    {0,1,},
    {1,1,},
    {2,1,},
             
    {6,2,},
    {5,2,},
    {0,2,},
    {1,2,},
    {2,2,},
};
//---------------------------------------------------------------------------
__fastcall TForm_ME_1::TForm_ME_1(TComponent* Owner)
    : TMEMCForm(Owner)
{

    for(int i=0;i<4;i++)
    {
        checkList[i] = new TStringList;
        for(int j=0;j<10;j++)
        {
            Con[i][j].Enable_CB = (TCheckBox *)FindComponent(sCon[i][j][0]);
            Con[i][j].PosX = (TRegEdit *)FindComponent(sCon[i][j][1]);
            Con[i][j].PosY = (TRegEdit *)FindComponent(sCon[i][j][2]);
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_ME_1::cb_ip_ma1Click(TObject *Sender)
{
    TCheckBox * cb;
    int pidx;
    int idx;

    cb = (TCheckBox *)Sender;
    pidx = mv_Page->ActivePageIndex;
//
    if(cb->Checked == true)
    {
        if(checkList[pidx]->Count>=10)
        {
            cb->Checked = false;
            return;
        }
        else
        {
            checkList[pidx]->AddObject(IntToHex(cb->Tag,2),cb);
            checkList[pidx]->Sort();
        }
    }
    else
    {
        if(checkList[pidx]->Count>0)
        {
            if(checkList[pidx]->Find(IntToHex(cb->Tag,2),idx))
            {
                checkList[pidx]->Delete(idx);
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_ME_1::btnScanmvClick(TObject *Sender)
{
    TCheckBox * cb;
    char key;
    for(int i=0;i<10;i++)
    {
        Con[mv_Page->ActivePageIndex][i].Enable_CB->Checked = false;
    }
    
    for(int i=0;i<checkList[mv_Page->ActivePageIndex]->Count;i++)
    {
        cb = (TCheckBox *)checkList[mv_Page->ActivePageIndex]->Objects[i];
        //ShowMessage(checkList->Strings[i]+cb->Name);
        Con[mv_Page->ActivePageIndex][i].Enable_CB->Checked = true;
        Con[mv_Page->ActivePageIndex][i].PosX->Text = IntToHex(Mat[cb->Tag].valX,2);
        key = VK_RETURN;
        Con[mv_Page->ActivePageIndex][i].PosX->KeyPress(key);
        Con[mv_Page->ActivePageIndex][i].PosY->Text = IntToHex(Mat[cb->Tag].valY,2);
        Con[mv_Page->ActivePageIndex][i].PosY->KeyPress(key);
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm_ME_1::btnRefreshClick(TObject *Sender)
{
    TRegCheckBox * rcb;
    TRegLabeledEdit * rle;
    TRegEdit * re;
    TGroupBox * gb;


    for(int i=0; i<GB_GMV->ControlCount; i++)
    {
        if(GB_GMV->Controls[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)GB_GMV->Controls[i];
            rle->Refresh();
        }
        if(GB_GMV->Controls[i]->ClassNameIs("TRegCheckBox"))
        {
            rcb = (TRegCheckBox *)GB_GMV->Controls[i];
            rcb->Refresh();
        }
        if(GB_GMV->Controls[i]->ClassNameIs("TRegEdit"))
        {
            re = (TRegEdit *)GB_GMV->Controls[i];
            re->Refresh();
        }
    }

    for(int i=0;i<mv_Page->ActivePage->ControlCount;i++)
    {
        if(mv_Page->ActivePage->Controls[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)mv_Page->ActivePage->Controls[i];
            rle->Refresh();
        }
        if(mv_Page->ActivePage->Controls[i]->ClassNameIs("TRegCheckBox"))
        {
            rcb = (TRegCheckBox *)mv_Page->ActivePage->Controls[i];
            rcb->Refresh();
        }
        if(mv_Page->ActivePage->Controls[i]->ClassNameIs("TRegEdit"))
        {
            re = (TRegEdit *)mv_Page->ActivePage->Controls[i];
            re->Refresh();
        }
        if(mv_Page->ActivePage->Controls[i]->ClassNameIs("TGroupBox"))
        {
            gb = (TGroupBox *)mv_Page->ActivePage->Controls[i];
            //ShowMessage(gb->Name);
            for(int j=0;j<gb->ControlCount;j++)
            {
                //ShowMessage(gb->Controls[j]->ClassName());
                if(gb->Controls[j]->ClassNameIs("TRegLabeledEdit"))
                {
                    rle = (TRegLabeledEdit *)gb->Controls[j];
                    rle->Refresh();
                }
                if(gb->Controls[j]->ClassNameIs("TRegCheckBox"))
                {
                    rcb = (TRegCheckBox *)gb->Controls[j];
                    rcb->Refresh();
                }
                if(gb->Controls[j]->ClassNameIs("TRegEdit"))
                {
                    re = (TRegEdit *)gb->Controls[j];
                    re->Refresh();
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm_ME_1::FormDestroy(TObject *Sender)
{
    for(int i=0;i<4;i++)
    {
        if(checkList[i]->Count > 0)
        {
            for (int j=0;j<checkList[i]->Count;j++)
            {
                checkList[i]->Objects[i]->Free();
            }
        }
        delete checkList[i];
    }    
}
//---------------------------------------------------------------------------


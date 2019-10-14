//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "UFrame_BWMeasure.h"
#include "I2CDevice.h"
#include "UForm_BWData.h"
#include <io.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCFrame"
#pragma link "CSPIN"
#pragma resource "*.dfm"

#define LINES           1125
#define READNUM         3
TFrame_BWMeasure *Frame_BWMeasure;
//---------------------------------------------------------------------------
__fastcall TFrame_BWMeasure::TFrame_BWMeasure(TComponent* Owner)
    : TMEMCFrame(Owner)
{
    IP_Mode = 0;
    ME_Mode = 0;
    MC_Mode = 0;
    Free_Mode = 0;
    LineCounts = 1;
    startLine = 0;
    endLine = 1125;
    bTotal = false;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<16;j++)
        {
            Agents[i][j] = false;
        }
    }

    unsigned int frame;
    Byte N,M;
    double ovsync;
    double ivsync;
    unsigned int ovtotal;
    unsigned int ivtotal;

    GetDevice()->ReadDWord(0xE00000C0,frame);
    frame = frame>>8;
    GetDevice()->ReadByte(0xE0000069,N);
    GetDevice()->ReadByte(0xE00000D5,M);
    if(M==0)    M=1;

    ivsync = (double)(150*1E6)/ (double)frame;
    ovsync = (double)(ivsync*N) /(double)M;

    GetDevice()->ReadDWord(0xE0000134, ivtotal);
    ivtotal = (ivtotal>>16) & 0x07FF;
    GetDevice()->ReadDWord(0xE000008C, ovtotal);
    ovtotal &= 0x00000FFF;

    inLineFreq = ivsync * (double)ivtotal;
    outLineFreq = ovsync * (double)ovtotal;
}
//---------------------------------------------------------------------------

AnsiString IP_BW[] =
{
    "10",
    "B",    "0xE000030A",   "0xC0",
    //"B",    "0xE000030B",   "0x40",
    "B",    "0xE0000B1D",   "0x80",
    "B",    "0xE0000B1E",   "0x00",
    "B",    "0xE0000B1F",   "0x00",
    "D",    "0xE0000B20",   "0x00000100",
    "D",    "0xE0000B24",   "0x04000002",
    "D",    "0xE0000B28",   "0x00000000",
    "D",    "0xE0000B2C",   "0x00000000",
    "D",    "0xE0000B30",   "0x00000000",
    "B",    "0xE0000B34",   "0x00"
};

AnsiString MC_BW[] =
{
    "10",
    "B",    "0xE000030A",   "0xC0",
    //"B",    "0xE000030B",   "0x40",
    "B",    "0xE0000B1D",   "0x08",
    "B",    "0xE0000B1E",   "0x00",
    "B",    "0xE0000B1F",   "0x00",
    "D",    "0xE0000B20",   "0x20000010",
    "D",    "0xE0000B24",   "0x00400000",
    "D",    "0xE0000B28",   "0x00000000",
    "D",    "0xE0000B2C",   "0x00000000",
    "D",    "0xE0000B30",   "0x00000000",
    "B",    "0xE0000B34",   "0x00"
};

AnsiString ME_BW[] =
{
    "10",
    "B",    "0xE000030A",   "0xC0",
    //"B",    "0xE000030B",   "0x40",
    "B",    "0xE0000B1D",   "0x01",
    "B",    "0xE0000B1E",   "0x00",
    "B",    "0xE0000B1F",   "0x00",
    "D",    "0xE0000B20",   "0x04000002",
    "D",    "0xE0000B24",   "0x20000000",
    "D",    "0xE0000B28",   "0x00400000",
    "D",    "0xE0000B2C",   "0x00008000",
    "D",    "0xE0000B30",   "0x00000100",
    "B",    "0xE0000B34",   "0x02"
};

int AgentIDMap[16]=
{
    0,1,2,13,14,15,16,17,3,4,5,6,7,8,9,10,   
};

void __fastcall TFrame_BWMeasure::IPMeasure()
{
    AnsiString val;
    bufCount = 4;

    iBuf = (double **)malloc(bufCount*sizeof(double *));

    for(int i=0;i<bufCount;i++)
    {
        iBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));//new int[(endLine-startLine)/LineCounts];
    }
    ////////////////////////////////////////////////////////
    /*fBuf = (double **)malloc(bufCount*sizeof(double));

    for(int i=0;i<bufCount;i++)
    {
        fBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));
    }  */
    ///////////////////////////////////////////////////////////



    PB_BW->Max = ((endLine-startLine)*READNUM*bufCount) /LineCounts ;
    PB_BW->Min = 0;
    PB_BW->Position = 0;
    bufReadCount = 0;
    
    LoadMeasurePar(IP_BW);
    ReadMeasure(4, 0);
    
    memo_out->Clear();

    AnsiString str_v;
    for(int i=0;i<bufCount;i++)
    {
        val = "";
        for(int j=0;j<(endLine-startLine)/LineCounts;j++)
        {
            str_v.printf("%.2f",iBuf[i][j]);
            val += str_v+", ";//IntToStr(iBuf[i][j])+", ";
        }
        memo_out->Lines->Add(val);
    }

    if(SaveDialog1->Execute())
    {
        memo_out->Lines->SaveToFile(SaveDialog1->FileName);
    }

    Form_BWData = new TForm_BWData(this->Parent);
    Form_BWData->SetSeries(bufCount,(endLine-startLine)/LineCounts,iBuf);
    Form_BWData->SetLines(LineCounts);
    Form_BWData->Show();
}
void __fastcall TFrame_BWMeasure::MCMeasure()
{
    AnsiString val;
    bufCount = 4;
    
    iBuf = (double **)malloc(bufCount*sizeof(double *));

    for(int i=0;i<bufCount;i++)
    {
        iBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));//new int[(endLine-startLine)/LineCounts];
    }

    ////////////////////////////////////////////////////////
    /*fBuf = (double **)malloc(bufCount*sizeof(double));

    for(int i=0;i<bufCount;i++)
    {
        fBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));
    }*/
    ///////////////////////////////////////////////////////////

    PB_BW->Max = ((endLine-startLine)*READNUM*bufCount) /LineCounts ;
    PB_BW->Min = 0;
    PB_BW->Position = 0;
    bufReadCount = 0;

    LoadMeasurePar(MC_BW);
    ReadMeasure(4, 1);

    memo_out->Clear();
    AnsiString str_v;
    for(int i=0;i<bufCount;i++)
    {
        val = "";
        for(int j=0;j<(endLine-startLine)/LineCounts;j++)
        {
            str_v.printf("%.2f",iBuf[i][j]);
            val += str_v+", ";//IntToStr(iBuf[i][j])+", ";
        }
        memo_out->Lines->Add(val);
    }

    memo_out->Clear();
    if(SaveDialog1->Execute())
    {
        memo_out->Lines->SaveToFile(SaveDialog1->FileName);
    }

    Form_BWData = new TForm_BWData(this->Parent);
    Form_BWData->SetSeries(bufCount,(endLine-startLine)/LineCounts,iBuf);
    Form_BWData->SetLines(LineCounts);
    Form_BWData->Show();

}
void __fastcall TFrame_BWMeasure::MEMeasure()
{
    AnsiString val;
    bufCount = 8;

    iBuf = (double **)malloc(bufCount*sizeof(double *));

    for(int i=0;i<bufCount;i++)
    {
        iBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));//new int[(endLine-startLine)/LineCounts];
    }

    ////////////////////////////////////////////////////////
    /*fBuf = (double **)malloc(bufCount*sizeof(double));

    for(int i=0;i<bufCount;i++)
    {
        fBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));
    }  */
    ///////////////////////////////////////////////////////////

    PB_BW->Max = ((endLine-startLine)*READNUM*bufCount) /LineCounts ;
    PB_BW->Min = 0;
    PB_BW->Position = 0;
    bufReadCount = 0;
    
    LoadMeasurePar(ME_BW);
    ReadMeasure(8, 2);
    
    memo_out->Clear();
    AnsiString str_v;
    for(int i=0;i<bufCount;i++)
    {
        val = "";
        for(int j=0;j<(endLine-startLine)/LineCounts;j++)
        {
            str_v.printf("%.2f", iBuf[i][j] );
            val += str_v+", ";//IntToStr(iBuf[i][j])+", ";
        }
        memo_out->Lines->Add(val);
    }

    if(SaveDialog1->Execute())
    {
        memo_out->Lines->SaveToFile(SaveDialog1->FileName);
    }

    Form_BWData = new TForm_BWData(this->Parent);
    Form_BWData->SetSeries(bufCount,(endLine-startLine)/LineCounts,iBuf);
    Form_BWData->SetLines(LineCounts);
    Form_BWData->Show();
}

void __fastcall TFrame_BWMeasure::ReadMeasure(int count, int index, int readNum )
{
    unsigned int v_18, v_1c;
    unsigned int ** p_vResult;
    int **p_iResult;
    int * p_value;
    int num;
    AnsiString val;
    TStringList * memoList;
    double freq;

    double LineFreq;

    memoList = new TStringList;
    
    memoList->Clear();
    memo_out->Lines->Clear();
    Byte b_v18;

    //calculate the result read count
    //start read address at 0xE0000B34, but result start address at 0xE0000B35
    num = count * 3 + 1;
    if((num % 4)!=0)
    {
        num = (num / 4 + 1) * 4;
    }
    num /= 4;

    p_vResult = (unsigned int **)malloc(readNum*sizeof(unsigned int *));
    for(int i=0;i<readNum;i++)
    {
        p_vResult[i] = (unsigned int *)malloc(num*sizeof(unsigned int));
    }

    p_iResult = ( int **)malloc(readNum*sizeof( int *));
    for(int i=0;i<readNum;i++)
    {
        p_iResult[i] = ( int *)malloc(count*sizeof( int));
    }

    p_value = ( int *)malloc(count*sizeof( int));
    
    GetDevice()->ReadDWord(0xE0000B18,v_18);
    GetDevice()->ReadDWord(0xE0000B1C,v_1c);

    switch(index)
    {
        case 0:    //IP
            b_v18 = IP_Mode;
        break;
        case 1:    //MC
            b_v18 = MC_Mode;
        break;
        case 2:    //ME
            b_v18 = ME_Mode;
        break;
        default:
            b_v18 = Free_Mode;
        break;
    }
    if(b_v18 == 0)
    {
        LineFreq = inLineFreq;
    }
    else
    {
        LineFreq = outLineFreq;
    }
    
    for(int i=0;i<(endLine-startLine)/LineCounts;i++)
    {
        GetDevice()->WriteDWord(0xE0000B18,v_18 & 0xFFFFFFFB);
        v_18 &= 0x000000F8;
        v_18 |= (((startLine+LineCounts*(i+1))& 0xFF)<<24) | (((startLine+LineCounts*i) & 0xFFFF)<<8)| b_v18;// | 0x04  ;
        v_1c &= 0xFFFFFFF8;
        v_1c |= ((startLine+LineCounts*(i+1)) >> 8) & 0x00000007;
        GetDevice()->WriteDWord(0xE0000B18,v_18);
        GetDevice()->WriteDWord(0xE0000B1C,v_1c);
        GetDevice()->WriteDWord(0xE0000B18,v_18 | 0x00000004);


        //memoList->Add(IntToHex((int)v_18,8)+"  "+IntToHex((int)v_1c, 8)+" "+IntToStr(i) );
        Sleep(20);
        for(int m=0; m<readNum; m++)
        {
            if(bTotal)
            {
                Sleep(20);
            }
            for(int j=0; j<num; j++ )
            {
                GetDevice()->ReadDWord(0xE0000B34+j*4,p_vResult[m][j]);
                //memoList->Add(IntToHex((int)(0xE0000B34+j*4), 8)+": "+IntToHex((int)(p_vResult[m][j]),8));
            }
            for(int j=0;j<count;j++)
            {
                switch(j)
                {
                    case 0:
                        p_iResult[m][0] = p_vResult[m][0] >> 8;
                        break;
                    case 1:
                        p_iResult[m][1] = p_vResult[m][1]& 0x00FFFFFF;
                        break;
                    case 2:
                        p_iResult[m][2] = (p_vResult[m][1]>>24) | ((p_vResult[m][2]&0x0000FFFF)<<8);
                        break;
                    case 3:
                        p_iResult[m][3] = (p_vResult[m][2]>>16) | ((p_vResult[m][3]&0x000000FF)<<16);
                        break;
                    case 4:
                        p_iResult[m][4] = p_vResult[m][3]>>8;
                        break;
                    case 5:
                        p_iResult[m][5] = p_vResult[m][4]& 0x00FFFFFF;
                        break;
                    case 6:
                        p_iResult[m][6] = (p_vResult[m][4]>>24) | ((p_vResult[m][5]&0x0000FFFF)<<8);
                        break;
                    case 7:
                        p_iResult[m][7] = (p_vResult[m][5]>>16) | ((p_vResult[m][6]&0x000000FF)<<16);
                        break;
                }
                PB_BW->Position++;
            }

        }
        /*if(LineCounts>1)
        {
            str += IntToStr(i)+"~"+IntToStr(i+LineCounts-1)+", ";
        }
        else
        {
            str += IntToStr(i)+", ";
        }*/
        //translate buf to file
        for(int m=0; m<count; m++)
        {
            p_value[m] = 0;
            val = "";
            for(int j=0;j<readNum;j++)
            {
                int ve;
                p_value[m] += p_iResult[j][m];
                if(cb_Band->Checked)
                {
                    ve = ((p_iResult[j][m]*16/ LineCounts)*LineFreq )/1E6;
                }
                else
                {
                    ve = p_iResult[j][m];
                }
                val += IntToStr(ve)+" ";
            }
            if(!bTotal)
            {
                p_value[m] /= readNum;

                if(cb_Band->Checked)
                {

                    freq = (((double)(p_value[m]*16)/ (double)LineCounts)*LineFreq )/1E6;
                    iBuf[bufReadCount+m][i] = Ceil(freq);
                }
                else
                {
                    iBuf[bufReadCount+m][i]=p_value[m];
                }
            }
            else
            {
                datalist->Add(val);
            }

        }
    }
    bufReadCount += count;


    for(int i=0;i<readNum;i++)
    {
        free(p_vResult[i]);
    }
    free(p_vResult);

    for(int i=0;i<readNum;i++)
    {
        free(p_iResult[i]);
    }
    free(p_iResult);

    free(p_value);

}
void __fastcall TFrame_BWMeasure::Button1Click(TObject *Sender)
{
    IPMeasure();    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::Button2Click(TObject *Sender)
{
    MEMeasure();    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::Button3Click(TObject *Sender)
{
    MCMeasure();    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::RB_IP_0Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;
    IP_Mode = rb->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::RB_ME_0Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;
    ME_Mode = rb->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::RB_MC_0Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;
    MC_Mode = rb->Tag;    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::RB_all_0Click(TObject *Sender)
{
    TRadioButton * rb;

    rb = (TRadioButton *)Sender;
    IP_Mode = rb->Tag;
    ME_Mode = rb->Tag;
    MC_Mode = rb->Tag;
    Free_Mode = rb->Tag;
    switch(rb->Tag)
    {
        case 0:
            RB_IP_0->Checked = true;
            RB_MC_0->Checked = true;
            RB_ME_0->Checked = true;
        break;
        case 1:
            RB_IP_1->Checked = true;
            RB_MC_1->Checked = true;
            RB_ME_1->Checked = true;
        break;
        case 2:
            RB_IP_2->Checked = true;
            RB_MC_2->Checked = true;
            RB_ME_2->Checked = true;
        break;
        case 3:
            RB_IP_3->Checked = true;
            RB_MC_3->Checked = true;
            RB_ME_3->Checked = true;
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::CB_LinesChange(TObject *Sender)
{
    try
    {
        LineCounts = CB_Lines->Text.ToInt();
    }
    catch(...)
    {
    }


}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::Ed_StartChange(TObject *Sender)
{
    try
    {
        startLine = Ed_Start->Text.ToInt();
    }
    catch(...)
    {
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::Ed_EndChange(TObject *Sender)
{
    try
    {
        endLine = Ed_End->Text.ToInt();
    }
    catch(...)
    {
    }
}
//---------------------------------------------------------------------------


void __fastcall TFrame_BWMeasure::btn_AllBWClick(TObject *Sender)
{
    AnsiString val;

    bufCount = 16;

    iBuf = (double **)malloc(bufCount*sizeof(double *));

    for(int i=0;i<bufCount;i++)
    {
        iBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));//new int[(endLine-startLine)/LineCounts];
    }


    ////////////////////////////////////////////////////////
    /*fBuf = (double **)malloc(bufCount*sizeof(double));

    for(int i=0;i<bufCount;i++)
    {
        fBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));
    }*/
    ///////////////////////////////////////////////////////////


    PB_BW->Max = ((endLine-startLine)*READNUM /LineCounts )* bufCount ;
    PB_BW->Min = 0;
    PB_BW->Position = 0;
    
    bufReadCount = 0;

    LoadMeasurePar(ME_BW);
    ReadMeasure(8, 2);

    LoadMeasurePar(MC_BW);
    ReadMeasure(4, 1);

    LoadMeasurePar(IP_BW);
    ReadMeasure(4, 0);



    memo_out->Clear();
    AnsiString str_v;
    for(int i=0;i<bufCount;i++)
    {
        val = "";
        for(int j=0;j<(endLine-startLine)/LineCounts;j++)
        {
            str_v.printf("%.2f", iBuf[i][j]);
            val += str_v+", ";//IntToStr(iBuf[i][j])+", ";
        }
        memo_out->Lines->Add(val);
    }

    if(SaveDialog1->Execute())
    {
        memo_out->Lines->SaveToFile(SaveDialog1->FileName);
    }
    
    Form_BWData = new TForm_BWData(this->Parent);
    Form_BWData->SetSeries(bufCount,(endLine-startLine)/LineCounts,iBuf);
    Form_BWData->SetLines(LineCounts);
    Form_BWData->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::Button4Click(TObject *Sender)
{
    //

    unsigned int AgentReg[7],AgentValue[8];
    unsigned int val_1c, val_34;
    unsigned int valid_1c, valid_34;

    AnsiString val;
    TCheckBox * cb;
    int j;


    j=0;
    for(int i=0;i<CheckPanel->ControlCount;i++)
    {
        if(CheckPanel->Controls[i]->ClassNameIs("TCheckBox"))
        {
            cb = (TCheckBox *)CheckPanel->Controls[i];
            AgentValue[cb->Tag] = 0;

            if(cb->Checked)
            {
                for(int m=0; m<16; m++)
                {
                    if(Agents[cb->Tag][m])
                    {
                        AgentValue[cb->Tag] |= 0x00000001<<AgentIDMap[m];
                    }
                }
                AgentValue[cb->Tag] &= 0x00FFFFFF;
                j++;
            }
            else
            {
                AgentValue[cb->Tag] = 0;
            }
        }
    }

    bufCount = j;

    PB_BW->Max = ((endLine-startLine)*READNUM*bufCount) /LineCounts ;
    PB_BW->Min = 0;
    PB_BW->Position = 0;
    bufReadCount = 0;


    iBuf = (double **)malloc(bufCount*sizeof(double *));

    for(int i=0;i<bufCount;i++)
    {
        iBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));//new int[(endLine-startLine)/LineCounts];
    }

    ////////////////////////////////////////////////////////
    /*fBuf = (double **)malloc(bufCount*sizeof(double));

    for(int i=0;i<bufCount;i++)
    {
        fBuf[i] = (double *)malloc((endLine-startLine)/LineCounts*sizeof(double));
    }   */
    ///////////////////////////////////////////////////////////

    GetDevice()->ReadDWord(0xE0000B1C, val_1c);
    GetDevice()->ReadDWord(0xE0000B34, val_34);


    val_1c = 0;
    val_34 = 0;

    valid_1c = val_1c & 0x000000FF;
    valid_34 = val_34 & 0xFFFFFF00;

    /*for(int i=0;i<8;i++)
    {
        AgentValue[i] = 0x00000001<<(AgentIDMap[i]);
        AgentValue[i] &= 0x00FFFFFF;
    } */
    AgentReg[0] = (AgentValue[0]<<8) | valid_1c;
    AgentReg[1] = AgentValue[1] | (AgentValue[2]<<24);
    AgentReg[2] = (AgentValue[2]>>8)|(AgentValue[3]<<16);
    AgentReg[3] = (AgentValue[3]>>16)|(AgentValue[4]<<8);
    AgentReg[4] = AgentValue[5] | (AgentValue[6]<<24);
    AgentReg[5] = (AgentValue[6]>>8)|(AgentValue[7]<<16);
    AgentReg[6] =  (AgentValue[7]>>16)|valid_34;

    /*String str = "";
    for(int i=0;i<7;i++)
    {
        str += IntToHex((int)AgentReg[i],8)+"  ";
    }
    ShowMessage(str);
    return;*/          

    for(int i=0; i<7; i++)
    {
        GetDevice()->WriteDWord(0xE0000B1C+4*i,AgentReg[i]);
    }

    ReadMeasure(bufCount, 4);
    
    memo_out->Clear();
    AnsiString str_v;
    for(int i=0;i<bufCount;i++)
    {
        val = "";
        for(int j=0;j<(endLine-startLine)/LineCounts;j++)
        {
            str_v.printf("%.2f", iBuf[i][j]);
            val += str_v + ", ";//IntToStr(iBuf[i][j])+", ";
        }
        memo_out->Lines->Add(val);
    }

    if(SaveDialog1->Execute())
    {
        memo_out->Lines->SaveToFile(SaveDialog1->FileName);
    }

    Form_BWData = new TForm_BWData(this->Parent);
    Form_BWData->SetSeries(bufCount,(endLine-startLine)/LineCounts,iBuf);
    Form_BWData->SetLines(LineCounts);
    Form_BWData->Show();

}
//---------------------------------------------------------------------------


void __fastcall TFrame_BWMeasure::CheckBox1Click(TObject *Sender)
{
    TCheckBox * cb;
    TEdit * comb;
    AnsiString Name;

    cb = (TCheckBox *)Sender;
    Name = "Edit"+IntToStr(cb->Tag+1);
    comb = (TEdit *)FindComponent(Name);
    if(cb->Checked)
    {
        comb->Enabled = true;
    }
    else
    {
        comb->Enabled = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFrame_BWMeasure::btnTotalClick(TObject *Sender)
{
    int tmpLinesCount, tmpEndLine, tmpStartLine;

    tmpLinesCount = LineCounts;
    tmpEndLine = endLine;
    tmpStartLine = startLine;

    LineCounts = 1125;
    startLine = 0;
    endLine = 1125;
    bTotal = true;
    datalist = new TStringList();

    /*for (int i =0;i<16;i++)
    {
        datalist->Add("");
    }*/

    LoadMeasurePar(ME_BW);
    ReadMeasure(8,2,6);

    LoadMeasurePar(MC_BW);
    ReadMeasure(4,1,6);
    
    LoadMeasurePar(IP_BW);
    ReadMeasure(4,0,6);

    LineCounts = tmpLinesCount;
    startLine = tmpStartLine;
    endLine = tmpEndLine;
    bTotal = false;

    for(int i=0;i<datalist->Count;i++)
    {
        datalist->Strings[i] = clb_Agents->Items->Strings[i]+ "\t"+datalist->Strings[i] ;
    }

    memo_out->Lines = datalist;
    memo_out->Refresh();
    if(SaveDialog1->Execute())
    {
        datalist->SaveToFile(SaveDialog1->FileName);
    }

}
//---------------------------------------------------------------------------


void __fastcall TFrame_BWMeasure::Edit1Enter(TObject *Sender)
{
    TEdit * ed;
    int EditIndex;

    ed = (TEdit *)Sender;

    EditIndex = ed->Tag;
    clb_Agents->Visible = false;
    clb_Agents->Left = ed->Left+20;
    clb_Agents->Width = ed->Width-20;
    clb_Agents->Top = ed->Top+ed->Height+2;
    for(int i=0;i<clb_Agents->Count;i++)
    {
        clb_Agents->Checked[i]  =   Agents[EditIndex][i];
    }
    clb_Agents->Tag = EditIndex;
    clb_Agents->BringToFront();
    clb_Agents->Visible = true;

}
//---------------------------------------------------------------------------



void __fastcall TFrame_BWMeasure::clb_AgentsClick(TObject *Sender)
{
    int EditIndex;
    TEdit * ed;
    AnsiString str;

    EditIndex = clb_Agents->Tag;

    Agents[EditIndex][clb_Agents->ItemIndex] = clb_Agents->Checked[clb_Agents->ItemIndex];
    //ShowMessage("Edit"+IntToStr(EditIndex+1));
    ed = (TEdit *)FindComponent("Edit"+IntToStr(EditIndex+1));
    //ShowMessage(ed->Name);
    str = "";
    for(int i=0; i<clb_Agents->Items->Count;i++)
    {
        if(clb_Agents->Checked[i])
        {
            str += clb_Agents->Items->Strings[i]+"; ";
        }
    }
    ed->Text = str;

}
//---------------------------------------------------------------------------


void __fastcall TFrame_BWMeasure::Edit1Exit(TObject *Sender)
{
    if(!clb_Agents->Focused())
    {
        clb_Agents->Visible = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_BWMeasure::clb_AgentsExit(TObject *Sender)
{
    TEdit * ed;
    bool noDisa = false;
    for(int i=0;i<8;i++)
    {
        ed = (TEdit *)FindComponent("Edit"+IntToStr(i+1));
        noDisa = noDisa || ed->Focused();
    }
    if(!noDisa)
    {
        clb_Agents->Visible = false;
    }
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_Main_312FPGA.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMainFrame"
#pragma link "RegCheckBox"
#pragma resource "*.dfm"
TFrame_Main_312FPGA *Frame_Main_312FPGA;
//---------------------------------------------------------------------------
__fastcall TFrame_Main_312FPGA::TFrame_Main_312FPGA(TComponent* Owner)
    : TFrame_Main(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TFrame_Main_312FPGA::TFrame_Main_312FPGA(TComponent* Owner, DeviceCreate * oDev_Cre)
    : TFrame_Main(Owner,oDev_Cre)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Main_312FPGA::CB_BoardChange(TObject *Sender)
{
    int block;


    GetDevice()->SetBoard(CB_Board->ItemIndex);

    if(CB_Board->ItemIndex != Board_ALL)
    {
        block = GetDevice()->GetBoard()*m_iPageNum+(GetDevice()->GetPage()&0x3F);
        FillStringGrid(SG_Main, m_slRegBuf, block);
        if(GetRightGrid()!=NULL)
        {
            FillStringGrid(GetRightGrid(), RefBuf, block);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Main_312FPGA::bBtn_ReadPageClick(TObject *Sender)
{
    unsigned int Value;
    unsigned int tmpVal;
    unsigned char tmp;
    //int * p;
    Byte * buf;

    PB->Visible = true;
    PB->Max = m_bIs8BitFormat? 256:64;
    PB->Position = 0;
    //* p =0;
    //PB->Position = *p;
    //buf = (Byte *)malloc(256);

    GetDevice()->SetRegister(0);
    /*GetDevice()->BurstReadByte(256, buf);
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            SG_Main->Cells[j][i] = IntToHex(buf[i*16+j], 2);
        }
    }
    free(buf); */


    for(int i=0; i<16; i++)
    {
        if(m_bIs8BitFormat)
        {
            for(int j=0; j<16; j+=4)
            {
                GetDevice()->SetRegister(i*16+j);
                if(GetDevice()->GetBoard() == Board_ALL)
                {
                    Value = 0;
                    for(int k=0; k<Board_ALL; k++)
                    {
                        GetDevice()->SetBoard(k);
                        GetDevice()->ReadDWord(tmpVal);
                        Value |= tmpVal;
                    }
                    GetDevice()->SetBoard(Board_ALL);
                }
                else
                {
                    GetDevice()->ReadDWord(Value);
                }
                tmp = Value>>24;
                SG_Main->Cells[j+3][i] = IntToHex(tmp, 2);

                tmp = (unsigned char)((Value>>16)&0x00ff);
                SG_Main->Cells[j+2][i] = IntToHex(tmp, 2);

                tmp = (unsigned char)((Value>>8)&0x00ff);
                SG_Main->Cells[j+1][i] = IntToHex(tmp, 2);

                tmp = (unsigned char)(Value&0x00ff);
                SG_Main->Cells[j][i] = IntToHex(tmp, 2);
                PB->Position += 4;
            }
        }
        else
        {
            for(int j=0; j<4; j++)
            {
                GetDevice()->SetRegister(i*16+j*4);
                if(GetDevice()->GetBoard() == Board_ALL)
                {
                    Value = 0;
                    for(int k=0; k<Board_ALL; k++)
                    {
                        GetDevice()->SetBoard(k);
                        GetDevice()->ReadDWord(tmpVal);
                        Value |= tmpVal;
                    }
                    GetDevice()->SetBoard(Board_ALL);
                }
                else
                {
                    GetDevice()->ReadDWord(Value);
                }

                SG_Main->Cells[j][i] = IntToHex(tmp, 8);

                PB->Position ++;
            }
        }
    }
    SG_Main->SetFocus();    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main_312FPGA::bBtn_WritePageClick(TObject *Sender)
{
    unsigned int Value;
    AnsiString strValue;
    unsigned char tmp;

    PB->Visible = true;
    PB->Max = m_bIs8BitFormat? 256:64;
    PB->Position = 0;

    for(int i=0; i<16; i++)
    {
        if(m_bIs8BitFormat)
        {
            for(int j=0; j<16; j+=4)
            {
                GetDevice()->SetRegister(i*16+j);
                strValue = "0x"+SG_Main->Cells[j+3][i] + SG_Main->Cells[j+2][i]
                            + SG_Main->Cells[j+1][i] + SG_Main->Cells[j][i];;
                Value = strValue.ToInt();

                if(GetDevice()->GetBoard() == Board_ALL)
                {
                    for(int k=0; k<Board_ALL; k++)
                    {
                        GetDevice()->SetBoard(k);
                        GetDevice()->WriteDWord(Value);
                    }
                    GetDevice()->SetBoard(Board_ALL);
                }
                else
                {
                    GetDevice()->WriteDWord(Value);
                }
                PB->Position += 4;
            }
        }
        else
        {
            for(int j=0; j<4; j++)
            {
                GetDevice()->SetRegister(i*16+j*4);
                strValue = "0x"+ SG_Main->Cells[j][i];
                Value = strValue.ToInt();
                
                if(GetDevice()->GetBoard() == Board_ALL)
                {
                    for(int k=0; k<Board_ALL; k++)
                    {
                        GetDevice()->SetBoard(k);
                        GetDevice()->WriteDWord(Value);
                    }
                    GetDevice()->SetBoard(Board_ALL);
                }
                else
                {
                    GetDevice()->WriteDWord(Value);
                }
                
                PB->Position ++;
            }
        }
    }
    SG_Main->SetFocus();  
}
//---------------------------------------------------------------------------
void __fastcall TFrame_Main_312FPGA::bBtn_WriteAllClick(TObject *Sender)
{
    bool bPages;
    int iBoard;

    bPages = true;

    iBoard = GetDevice()->GetBoard();

    if (!m_bHexLoaded) return;

    //PB->Visible = true;
    //PB->Position = 0;
    //PB->Max = m_iBoardNum*m_iPageNum;
    
    for(int i=0;i<m_iBoardNum;i++)
    {
        for(int j=0;j<m_iPageNum;j++)
        {
            if(bPages)
            {
                if(!GetDevice()->GetPageExist(i,j))
                {
                    continue;
                }
            }

            GetDevice()->SetPage(j);
            GetDevice()->SetBoard(i);
            FillStringGrid(SG_Main, m_slRegBuf, i*m_iPageNum+j);
            if(GetRightGrid()!=NULL)
            {
                FillStringGrid(GetRightGrid(), RefBuf, i*m_iPageNum+j);
            }
            bBtn_WritePage->Click();
            /*if(MessageBox(Handle,("board "+IntToStr(i)+" Page "+IntToStr(j)).c_str(),"",MB_YESNO)==IDNO)
            {
                return;
            } */
            //PB->Position++;
        }
    }
    GetDevice()->SetBoard(iBoard);
    ShowMessage("Write Hex Finished!");
    PB->Visible = false;    
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main_312FPGA::bBtn_SaveAllClick(TObject *Sender)
{
    AnsiString buf;
    bool bPages;
    unsigned int buf_data;
    int iBoard;

    PB->Visible = true;
    PB->Position = 0;
    PB->Max = m_iBoardNum*m_iPageNum*256;

    iBoard = GetDevice()->GetBoard();

    bPages =  true;
    
    if(SD_Hex->Execute())
    {
        m_slRegBuf->Clear();
        for(int b=0; b<m_iBoardNum; b++)
        {
            for(int p=0; p<m_iPageNum; p++)
            {
                GetDevice()->SetPage(p);
                GetDevice()->SetBoard(b);
                GetDevice()->SetRegister(0);
                if(bPages)
                {
                    if(!GetDevice()->GetPageExist(b,p))
                    {
                        for(int i=0;i<16;i++)
                        {
                            buf = ":1"+IntToHex(b,1)+ IntToHex(p,2) + IntToHex(i,1)+"000";
                            buf += IntToHex(0,16);
                            buf += IntToHex(0,16);
                            m_slRegBuf->Add(buf);
                            PB->Position += 16;
                        }
                        continue;
                    }
                }
                for(int i=0;i<16;i++)
                {
                    buf = ":1"+IntToHex(b,1)+ IntToHex(p,2) + IntToHex(i,1)+"000";
                    for(int j=0;j<16;j+=4)
                    {
                        GetDevice()->SetRegister(i*16+j);
                        GetDevice()->ReadDWord(buf_data);
                        buf += IntToHex(((int)buf_data & 0xFF),2);
                        buf += IntToHex((((int)buf_data>>8) & 0xFF),2);
                        buf += IntToHex((((int)buf_data>>16) & 0xFF),2);
                        buf += IntToHex((((int)buf_data>>24) & 0xFF),2);
                        PB->Position += 4;
                    }
                    m_slRegBuf->Add(buf);
                } 
            }
        }

        m_slRegBuf->SaveToFile(SD_Hex->FileName);
    }
    PB->Visible = false;
    GetDevice()->SetBoard(iBoard);
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main_312FPGA::bBtn_LoadAllClick(TObject *Sender)
{
    int block;
    if(OD_Hex->Execute())
    {
        m_slRegBuf->Clear();
        m_slRegBuf->LoadFromFile(OD_Hex->FileName);
        m_bHexLoaded = true;
        block = GetDevice()->GetBoard()*m_iPageNum + (GetDevice()->GetPage()&0x3F);
        FillStringGrid(SG_Main, m_slRegBuf, block);
        if(GetRightGrid()!=NULL)
        {
            FillStringGrid(GetRightGrid(), RefBuf, block);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main_312FPGA::CB_PageExit(TObject *Sender)
{
    AnsiString Data;
    int block;
    Data = "0x"+CB_Page->Text;
    block = Data.ToInt();
    GetDevice()->SetPage(Data);
    GetDevice()->SetBoard(GetDevice()->GetBoard());
    if(GetDevice()->GetBoard() != Board_ALL)
    {
        block += GetDevice()->GetBoard()*m_iPageNum;
        FillStringGrid(SG_Main, m_slRegBuf, block);
        if(GetRightGrid()!=NULL)
        {
            FillStringGrid(GetRightGrid(), RefBuf, block);
        }    
    }

}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main_312FPGA::CB_PageKeyPress(TObject *Sender,
      char &Key)
{
    AnsiString a;
    int block;

    a = CB_Page->Text;



    if((Key>='0' && Key<='9')||(Key>='A' && Key<='F'))
    {
        if(a.Length()>=2)
        {
            CB_Page->Text="";
        }
    }
    else if(Key>='a' && Key<='f')
    {
        if(a.Length()>=2)
        {
            CB_Page->Text="";
        }
        Key-=0x20;
    }
    else if((Key == 13)||(Key == 8))
    {
        if(Key==13)
        {
            GetDevice()->SetPage("0x"+CB_Page->Text);
            GetDevice()->SetBoard(GetDevice()->GetBoard());
            if(GetDevice()->GetBoard() != Board_ALL)
            {
                block = GetDevice()->GetBoard()*m_iPageNum + ("0x"+CB_Page->Text).ToInt();
                FillStringGrid(SG_Main, m_slRegBuf, block);
                if(GetRightGrid()!=NULL)
                {
                    FillStringGrid(GetRightGrid(), RefBuf, block);
                }
            }
        }
    }
    else
    {
        Key = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main_312FPGA::CB_PageSelect(TObject *Sender)
{
    GetDevice()->SetPage(CB_Page->ItemIndex);
    GetDevice()->SetBoard(GetDevice()->GetBoard());
    if(GetDevice()->GetBoard() != Board_ALL)
    {
        FillStringGrid(SG_Main, m_slRegBuf, GetDevice()->GetBoard()*m_iPageNum+CB_Page->ItemIndex);
        if(GetRightGrid()!=NULL)
        {
            FillStringGrid(GetRightGrid(), RefBuf, GetDevice()->GetBoard()*m_iPageNum+CB_Page->ItemIndex);
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFrame_Main_312FPGA::GridWriteByte(Byte b)
{
    bool reval;
    reval = true;
    if(GetDevice()->GetBoard() == Board_ALL)
    {
        for(int i=0; i<Board_ALL; i++)
        {
            GetDevice()->SetBoard(i);
            if(!GetDevice()->WriteByte(b))
            {
                reval = false;
                break;
            }        
        }
        GetDevice()->SetBoard(Board_ALL);
        return reval;
    }
    else
    {
        return GetDevice()->WriteByte(b);
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFrame_Main_312FPGA::GridWriteDWord(unsigned int i)
{
    bool reval;
    reval = true;
    if(GetDevice()->GetBoard() == Board_ALL)
    {
        for(int i=0; i<Board_ALL; i++)
        {
            GetDevice()->SetBoard(i);
            if(!GetDevice()->WriteDWord(i))
            {
                reval = false;
                break;
            }        
        }
        GetDevice()->SetBoard(Board_ALL);
        return reval;
    }
    else
    {
        return GetDevice()->WriteDWord(i);
    }
}
//---------------------------------------------------------------------------



void __fastcall TFrame_Main_312FPGA::TV_PageChange(TObject *Sender,
      TTreeNode *Node)
{
    int board, page, block;

    if(Node->Parent == NULL)
    {
        Edit_BaseAddr->Text = IntToHex(ArrBaseAdd[Node->Index],4);
        GetDevice()->SetBase(ArrBaseAdd[Node->Index]);
    }
    else
    {
        Edit_BaseAddr->Text = IntToHex(ArrBaseAdd[Node->Parent->Index],4);
        GetDevice()->SetBase(ArrBaseAdd[Node->Parent->Index]);
        CB_Page->ItemIndex = Node->Index;
        GetDevice()->SetPage(Node->Index);
        GetDevice()->SetBoard(GetDevice()->GetBoard());
        if(GetDevice()->GetBoard() != Board_ALL)
        {
            block = GetDevice()->GetBoard()*m_iPageNum + Node->Index;
            FillStringGrid(SG_Main, m_slRegBuf, block);
            if(GetRightGrid()!=NULL)
            {
                FillStringGrid(GetRightGrid(), RefBuf, block);
            }
        }
    }    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main_312FPGA::cb_biscClick(TObject *Sender)
{
    if(cb_bisc->Checked)
    {
        GetDevice()->ChangePageList(1);
    }
    else
    {
        GetDevice()->ChangePageList(0);
    }
}
//---------------------------------------------------------------------------



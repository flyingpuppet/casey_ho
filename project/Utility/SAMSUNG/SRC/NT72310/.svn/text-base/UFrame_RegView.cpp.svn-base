//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_RegView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCFrame"
#pragma link "RegLabeledEdit"
#pragma resource "*.dfm"
TFrame_RegView *Frame_RegView;
//---------------------------------------------------------------------------
__fastcall TFrame_RegView::TFrame_RegView(TComponent* Owner)
    : TMEMCFrame(Owner)
{
    SetRightGrid(SG_Main);
    RefBuf = new TStringList();
    if(GetRightGrid()!=NULL)
    {
        if(GetRightGrid()->ColCount == 4)
        {
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<16;j++)
                {
                    SG_Main->Cells[i][j] = "00000000";
                }
            }
        }
        else
        {
            for(int i=0;i<16;i++)
            {
                for(int j=0;j<16;j++)
                {
                    SG_Main->Cells[i][j] = "00";
                }
            }
        }
    }
}
__fastcall TFrame_RegView::~TFrame_RegView()
{
    SetRightGrid(NULL);
    delete RefBuf;
    RefBuf = NULL;
}
//---------------------------------------------------------------------------




void __fastcall TFrame_RegView::SG_MainDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    TStringGrid * sg;

    sg = (TStringGrid *)Sender;    
/*
    switch(m_iRegTableAttribute[ACol][ARow])
    {
        case 0:
            StringGrid_SystemReg->Canvas->Brush->Color = clSkyBlue;
            StringGrid_SystemReg->Canvas->Font->Color = clBlack;
            break;
        case 1:
            StringGrid_SystemReg->Canvas->Brush->Color = clFuchsia;
            StringGrid_SystemReg->Canvas->Font->Color = clBlack;
            break;
        case 2:
            StringGrid_SystemReg->Canvas->Brush->Color = clAqua;
            StringGrid_SystemReg->Canvas->Font->Color = clWhite;
            break;
        case 3:
            StringGrid_SystemReg->Canvas->Brush->Color = clGreen;
            StringGrid_SystemReg->Canvas->Font->Color = clWhite;
            break;
    }
*/
    if(GetLeftGrid()!=NULL)
    {
        if(GetLeftGrid()->Cells[ACol][ARow] != SG_Main->Cells[ACol][ARow])
        {
            sg->Canvas->Brush->Color = clRed;
            //sg->Canvas->DrawFocusRect(Rect);
        }
    }
    sg->Canvas->FillRect(Rect);
    sg->Canvas->TextOutA(Rect.left + 5 , Rect.top + 5 , sg->Cells[ACol][ARow]);



    // Draw focus frame
    if(State.Contains(gdSelected))
    {
        TPoint points[5];
        points[0].x = Rect.Left + 1;
        points[0].y = Rect.Top + 1;
        points[1].x = Rect.Right - 2;
        points[1].y = Rect.Top + 1;
        points[2].x = Rect.Right - 2;
        points[2].y = Rect.Bottom - 2;
        points[3].x = Rect.Left + 1;
        points[3].y = Rect.Bottom - 2;
        points[4].x = Rect.Left + 1;
        points[4].y = Rect.Top + 1;

        sg->Canvas->Pen->Color = clYellow;
        sg->Canvas->Pen->Width = 3;
        sg->Canvas->Polyline(points, 4);
        sg->Canvas->DrawFocusRect(Rect);


        DrawFocusRowCol(ARow, ACol, clRed, clWhite);
    }
    if(GetLeftGrid()!= NULL)
    {
        GetLeftGrid()->Selection = SG_Main->Selection;

    }
}
//---------------------------------------------------------------------------
void __fastcall TFrame_RegView::DrawFocusRowCol(int ARow, int ACol,
    TColor MyShapeColor, TColor MyNumColor)
{
    TColor ShapeColor, NumColor;

    // initialize default color.
    ShapeColor = static_cast<TColor>(0x00F2DED5);
    NumColor = clBlue;

    TShape* ShapeArray[32] = {Shape_V0 , Shape_V1 , Shape_V2 , Shape_V3 ,
                              Shape_V4 , Shape_V5 , Shape_V6 , Shape_V7 ,
                              Shape_V8 , Shape_V9 , Shape_VA , Shape_VB ,
                              Shape_VC , Shape_VD , Shape_VE , Shape_VF ,
                              Shape_H0 , Shape_H1 , Shape_H2 , Shape_H3 ,
                              Shape_H4 , Shape_H5 , Shape_H6 , Shape_H7 ,
                              Shape_H8 , Shape_H9 , Shape_HA , Shape_HB ,
                              Shape_HC , Shape_HD , Shape_HE , Shape_HF};
    TLabel* LabelArray[32] = {Label_V0 , Label_V1 , Label_V2 , Label_V3 ,
                              Label_V4 , Label_V5 , Label_V6 , Label_V7 ,
                              Label_V8 , Label_V9 , Label_VA , Label_VB ,
                              Label_VC , Label_VD , Label_VE , Label_VF ,
                              Label_H0 , Label_H1 , Label_H2 , Label_H3 ,
                              Label_H4 , Label_H5 , Label_H6 , Label_H7 ,
                              Label_H8 , Label_H9 , Label_HA , Label_HB ,
                              Label_HC , Label_HD , Label_HE , Label_HF};

    for(int i = 0 ; i < 32 ; i++)
    {
        ShapeArray[i]->Brush->Color = ShapeColor;
    }

    for(int i = 0 ; i < 32 ; i++)
    {
        LabelArray[i]->Color = ShapeColor;
        LabelArray[i]->Font->Color = NumColor;
    }


    ShapeColor = MyShapeColor;
    NumColor = MyNumColor;

    for(int i = 0 ; i < 16 ; i++)
    {
        if(i == ARow)
        {
            ShapeArray[i]->Brush->Color = ShapeColor;
            LabelArray[i]->Color = ShapeColor;
            LabelArray[i]->Font->Color = NumColor;
        }
    }

    for(int i = 0 ; i < 16 ; i++)
    {
        if(m_bIs8BitFormat)
        {
            if(i == ACol)
            {
                ShapeArray[i + 16]->Brush->Color = ShapeColor;
                LabelArray[i + 16]->Color = ShapeColor;
                LabelArray[i + 16]->Font->Color = NumColor;
            }
        }
        else
        {
            if(i == ACol)
            {
                ShapeArray[i * 4 + 16]->Brush->Color = ShapeColor;
                LabelArray[i * 4 + 16]->Color = ShapeColor;
                LabelArray[i * 4 + 16]->Font->Color = NumColor;
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_RegView::rle_FrameChange(TObject *Sender)
{
    //
    CalVsync();

        
}
//---------------------------------------------------------------------------


void __fastcall TFrame_RegView::BitBtn_ReconnectClick(TObject *Sender)
{
    TRegLabeledEdit * rle;
    AnsiString str;

    for(int i=0;i<GB_Status->ControlCount;i++)
    {
        if(GB_Status->Controls[i]->ClassNameIs("TRegLabeledEdit"))
        {
            rle = (TRegLabeledEdit *)GB_Status->Controls[i];
            rle->Refresh();
        }
    }
   //CalVsync();
}
//---------------------------------------------------------------------------
void __fastcall TFrame_RegView::CalVsync()
{
    int frame, N, M, clk;
    double vsync,ov;
    AnsiString str;

    if(le_Clk->Text == "")   return;
    if(rle_Frame->Text == "")   return;
    if(rle_N->Text == "")   return;
    if(rle_M->Text == "")   return;

    try
    {
        clk = le_Clk->Text.ToInt()* 1E6;
        frame = rle_Frame->Text.ToInt();
        N = rle_N->Text.ToInt();
        M = rle_M->Text.ToInt()==0? 1: rle_M->Text.ToInt();
        vsync = ((double)clk  / (double)frame );
        str.sprintf("%2.2f\n",vsync);
        rle_VSync->Text=str;
        vsync = vsync / (double)M;
        ov = vsync * (double)N;


        str.sprintf("%2.2f\n",ov);
        rle_ovsync->Text=str;
    }
    catch(...)
    {
    }
}
void __fastcall TFrame_RegView::BitButton_RMoveClick(TObject *Sender)
{
    AnsiString str;

    if(GetLeftGrid()==NULL) return;

    if(GetLeftGrid()->ColCount == 4)
    {
        for(int i=0;i<16;i++)
        {
            str = "";
            for(int j=0;j<4;j++)
            {
                SG_Main->Cells[j][i] = GetLeftGrid()->Cells[j][i];
                str += SG_Main->Cells[j][i];
            }
            updateBuf(0, i, GetBlock(), str, 32);
        }
    }
    else
    {
        for(int i=0;i<16;i++)
        {
            str = "";
            for(int j=0;j<16;j++)
            {
                SG_Main->Cells[j][i] = GetLeftGrid()->Cells[j][i];
                str += SG_Main->Cells[j][i];
            }
            updateBuf(0, i, GetBlock(), str, 32);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_RegView::BitButton_LMoveClick(TObject *Sender)
{
    if(GetLeftGrid()==NULL) return;

    if(GetLeftGrid()->ColCount == 4)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<16;j++)
            {
                GetLeftGrid()->Cells[i][j] = SG_Main->Cells[i][j];
            }
        }
    }
    else
    {
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                GetLeftGrid()->Cells[i][j] = SG_Main->Cells[i][j];
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_RegView::SG_MainKeyPress(TObject *Sender, char &Key)
{
    int Col,Row,Index,INT_SubAddr,Slave_24C32,Register;
	AnsiString a;
	//BYTE data;
	bool CanSelect;
    unsigned char CurPage;


    //CurPage = Edit_ReadPage->Text.ToInt();
	Col = SG_Main->Col;
	Row = SG_Main->Row;

	a = SG_Main->Cells[Col][Row];


    if(m_bIs8BitFormat)
    {
	    if((Key>='0' && Key<='9')||(Key>='A' && Key<='F'))
	    {
		    if(a.Length()==2)
                    a="";
		    a=a+Key;
	    }
	    else if(Key>='a' && Key<='f')
	    {
		    if(a.Length()==2)
                    a="";
		    Key-=0x20;
		    a=a+Key;
	    }
    }
    else
    {
        if((Key>='0' && Key<='9')||(Key>='A' && Key<='F'))
	    {
		    if(a.Length()==8) a="";
		    a=a+Key;
	    }
	    else if(Key>='a' && Key<='f')
	    {
		    if(a.Length()==8) a="";
		    Key-=0x20;
		    a=a+Key;
	    }
    }

	//Set new value to sgRegTable
	SG_Main->Cells[Col][Row]=a;

    if(m_bIs8BitFormat)
    {
        if(SG_Main->Cells[Col][Row].Length()==2)
        {
            AnsiString DataString;
            //DataString = "0x";
            DataString = SG_Main->Cells[Col][Row];
            //data = DataString.ToInt();

            //Update the Reg's Info
            //StringGrid_SelectCellUpdate(Col, Row, CanSelect);
            //GetDevice()->WriteByte(data);
            updateBuf(Col, Row, GetBlock(), DataString, 2);
        }
    }
    else
    {
        if(SG_Main->Cells[Col][Row].Length()==8)
        {
            // Need to implement - Mars 20080212
            //unsigned int CurValue;
            AnsiString DataString;
            //DataString = "0x";
            DataString = SG_Main->Cells[Col][Row];
            //CurValue = DataString.ToInt();

            //Update the Reg's Info
            //StringGrid_SelectCellUpdate(Col, Row, CanSelect);
            //GetDevice()->WriteDWord(CurValue);
            updateBuf(Col,Row,GetBlock(),DataString, 8);
        }
    }    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_RegView::updateBuf(int Col, int Row, int Block, AnsiString str, int Length)
{
    AnsiString buf;
    
    buf = RefBuf->Strings[(Row)+Block*16];
        //ShowMessage(buf);
    buf.Delete((Col)*Length+10,Length);
        //ShowMessage(buf);
    buf.Insert(str,(Col)*Length+10);
        //ShowMessage(buf);
    RefBuf->Strings[(Row)+Block*16] = buf;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_RegView::BitButton_SaveClick(TObject *Sender)
{
    if(RefBuf->Count <=0 ) return;
    if(SD_Hex->Execute())
    {
        RefBuf->SaveToFile(SD_Hex->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_RegView::BitButton_LoadClick(TObject *Sender)
{
    if(OD_Hex->Execute())
    {
        RefBuf->LoadFromFile(OD_Hex->FileName);
    }
    FillStringGrid(SG_Main, RefBuf, GetBlock());    
}
//---------------------------------------------------------------------------



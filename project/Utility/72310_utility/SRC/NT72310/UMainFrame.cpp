//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMainFrame.h"
#include <math.h>
#include "UMEMCIni.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCFrame"
#pragma resource "*.dfm"
TFrame_Main *Frame_Main;

__fastcall TFrame_Main::~TFrame_Main()
{
    delete m_slRegBuf;
}
//---------------------------------------------------------------------------
__fastcall TFrame_Main::TFrame_Main(TComponent* Owner)
    : TMEMCFrame(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TFrame_Main::TFrame_Main(TComponent* Owner,DeviceCreate * oDev_Cre)
    : TMEMCFrame(Owner)
{
    Dev_Cre = oDev_Cre;
    TV_Page->FullExpand();
    if(GetDevice()->GetName() == "NT72310")
    {
        for(int i=0;i<16;i++)
        {
            CB_Page->Items->Add(IntToHex(i,1));
        }
        CB_Page->ItemIndex = 0;
        CB_Board->Visible = false;
        Lb_Board->Visible = false;
        m_iBoardNum = 1;
        m_iPageNum = 16;
    }
    else if(GetDevice()->GetName() == "NT72312")
    {
        for(int i=0;i<32;i++)
        {
            CB_Page->Items->Add(IntToHex(i,2));
        }
        CB_Page->ItemIndex = 0;
        CB_Board->Visible = true;
        Lb_Board->Visible = true;
        m_iBoardNum = 3;
        m_iPageNum = 32;
    }
    else if(GetDevice()->GetName() == "NT72312C")
    {
        for(int i=0;i<32;i++)
        {
            CB_Page->Items->Add(IntToHex(i,2));
        }
        CB_Page->ItemIndex = 0;
        CB_Board->Visible = false;
        Lb_Board->Visible = false;
        m_iBoardNum = 1;
        m_iPageNum = 32;
    }

    m_iCurCol = 0;
    m_iCurRow = 0;

    m_bIs8BitFormat = false;
    m_iStopBit = 7;
    m_iStartBit = 0;
    SB_Value->Min = 0;
    SB_Value->Max = pow(2,m_iStopBit-m_iStartBit+1)-1;

    Edit_BaseAddr->Text = "E000";

    GetDevice()->SetAddress(0xE000,0,0);
    m_slRegBuf = new TStringList();
    m_bHexLoaded = false;

    FormatChange(true);

    SetLeftGrid(SG_Main);

}
//---------------------------------------------------------------------------
void __fastcall TFrame_Main::SetCreator(DeviceCreate * oDev_Cre)
{
    Dev_Cre = oDev_Cre;
}
//---------------------------------------------------------------------------
DeviceCreate * __fastcall TFrame_Main::GetCreator()
{
    return Dev_Cre;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::BitBtn_ReconnectClick(TObject *Sender)
{    
    if(Dev_Cre->CreateUSBConnection())
    {
        if(GetDevice()->Start())
        {
            Shape_ConnectStatus->Brush->Color = clLime;
        }
        else
        {
            Shape_ConnectStatus->Brush->Color = clRed;
        }
    }
    else
    {
        Shape_ConnectStatus->Brush->Color = clRed;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::SG_MainDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
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
    if(GetRightGrid()!=NULL)
    {
        GetRightGrid()->Selection = SG_Main->Selection;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::DrawFocusRowCol(int ARow, int ACol, TColor MyShapeColor, TColor MyNumColor)
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
void __fastcall TFrame_Main::FormatChange(bool bIs8BitFormat)
{
    if(m_bIs8BitFormat && bIs8BitFormat)
        return;

    if(!m_bIs8BitFormat && !bIs8BitFormat)
        return;

    m_bIs8BitFormat = bIs8BitFormat;
    AnsiString DataString;
    int iValue;

    if(bIs8BitFormat)
    {
        m_iStartBit = 0;
        m_iStopBit = 7;
        SB_Value->Min = 0;
        SB_Value->Max = pow(2,m_iStopBit-m_iStartBit+1)-1;
        SB_Value->Enabled = true;
        SB_Value->Position = 0;
        // StringGrid_SystemReg transform
        for(int Row = 0 ; Row < 16 ; Row++)
        {
            for(int Col = 0 ; Col < 4 ; Col++)
            {
                AnsiString ValueString = SG_Main->Cells[Col][Row];
                AnsiString SubString;
                if(ValueString == "")
                {
                    ValueString = IntToHex(0,8);
                }
                SubString = "0x" + ValueString.SubString(1 , 2);
                m_cRegTableValueTmp[Col * 4 + 3][Row] = SubString.ToInt();
                SubString = "0x" + ValueString.SubString(3 , 2);
                m_cRegTableValueTmp[Col * 4 + 2][Row] = SubString.ToInt();
                SubString = "0x" + ValueString.SubString(5 , 2);
                m_cRegTableValueTmp[Col * 4 + 1][Row] = SubString.ToInt();
                SubString = "0x" + ValueString.SubString(7 , 2);
                m_cRegTableValueTmp[Col * 4 + 0][Row] = SubString.ToInt();
            }
        }
        SG_Main->ColCount = 16;
        SG_Main->DefaultColWidth = (SG_Main->Width / 16) - 1;
        if(GetRightGrid()!= NULL)
        {
            GetRightGrid()->ColCount = 16;
            GetRightGrid()->DefaultColWidth = (GetRightGrid()->Width /16)-1;
        }

        for(int Col = 0 ; Col < 16 ; Col++)
        {
            for(int Row = 0 ; Row < 16 ; Row++)
            {
                DataString.sprintf("%02X" , m_cRegTableValueTmp[Col][Row]);
                SG_Main->Cells[Col][Row] = DataString;
            }
        }

    }
    else
    {
        m_iStartBit = 0;
        m_iStopBit = 31;
        //SB_Value->Min = 0;
        //SB_Value->Max = pow(2,m_iStopBit-m_iStartBit+1)-1;
        SB_Value->Position = 0;
        SB_Value->Enabled = false;
        for(int Row = 0 ; Row < 16 ; Row++)
        {
            for(int Col = 0 ; Col < 4 ; Col++)
            {
                m_iRegTableValueTmp[Col][Row] = 0;
            }
        }

        for(int Row = 0 ; Row < 16 ; Row++)
        {
            for(int Col = 0 ; Col < 16 ; Col++)
            {
                int ShiftBit = Col % 4;
                DataString = "0x" + SG_Main->Cells[Col][Row];
                if (DataString == "0x")
                {
                    DataString = "0x00";
                }
                m_iRegTableValueTmp[(Col - (Col % 4)) / 4][Row] |= ((DataString.ToInt())<<(ShiftBit*8));
            }
        }
        SG_Main->ColCount = 4;
        SG_Main->DefaultColWidth = (SG_Main->Width / 4) - 2;
        if(GetRightGrid()!= NULL)
        {
            GetRightGrid()->ColCount = 4;
            GetRightGrid()->DefaultColWidth = (GetRightGrid()->Width /4)-2;
        }

        for(int Row = 0 ; Row < 16 ; Row++)
        {
            for(int Col = 0 ; Col < 4 ; Col++)
            {
                DataString.sprintf("%08X" , m_iRegTableValueTmp[Col][Row]);
                SG_Main->Cells[Col][Row] = DataString;
            }
        }

        for(int Row = 0 ; Row < 16 ; Row++)
        {
            for(int Col = 0 ; Col < 4 ; Col++)
            {
                m_iRegTableValueTmp[Col][Row] = 0;
            }
        }

    }

    // Re-position Label
    if(bIs8BitFormat)
    {
        Label_H0->Left = 37;
        Shape_H0->Left = 28;
    }
    else
    {
        Label_H0->Left = 70;
        Shape_H0->Left = 61;
    }

    Label_H1->Visible = bIs8BitFormat;
    Shape_H1->Visible = bIs8BitFormat;
    Label_H2->Visible = bIs8BitFormat;
    Shape_H2->Visible = bIs8BitFormat;
    Label_H3->Visible = bIs8BitFormat;
    Shape_H3->Visible = bIs8BitFormat;

    if(bIs8BitFormat)
    {
        Label_H4->Left = 142;
        Shape_H4->Left = 133;
    }
    else
    {
        Label_H4->Left = 174;
        Shape_H4->Left = 165;
    }

    Label_H5->Visible = bIs8BitFormat;
    Shape_H5->Visible = bIs8BitFormat;
    Label_H6->Visible = bIs8BitFormat;
    Shape_H6->Visible = bIs8BitFormat;
    Label_H7->Visible = bIs8BitFormat;
    Shape_H7->Visible = bIs8BitFormat;

    if(bIs8BitFormat)
    {
        Label_H8->Left = 246;
        Shape_H8->Left = 237;
    }
    else
    {
        Label_H8->Left = 277;
        Shape_H8->Left = 269;
    }

    Label_H9->Visible = bIs8BitFormat;
    Shape_H9->Visible = bIs8BitFormat;
    Label_HA->Visible = bIs8BitFormat;
    Shape_HA->Visible = bIs8BitFormat;
    Label_HB->Visible = bIs8BitFormat;
    Shape_HB->Visible = bIs8BitFormat;

    if(bIs8BitFormat)
    {
        Label_HC->Left = 348;
        Shape_HC->Left = 341;
    }
    else
    {
        Label_HC->Left = 381;
        Shape_HC->Left = 373;
    }

    Label_HD->Visible = bIs8BitFormat;
    Shape_HD->Visible = bIs8BitFormat;
    Label_HE->Visible = bIs8BitFormat;
    Shape_HE->Visible = bIs8BitFormat;
    Label_HF->Visible = bIs8BitFormat;
    Shape_HF->Visible = bIs8BitFormat;
    
    RePositionRegisterModify(bIs8BitFormat);
    //SB_Value->Visible = bIs8BitFormat;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::RePositionRegisterModify(bool bIs8BitFormat)
{
    AnsiString DataString;
    int iValue;

    TShape* TmpShape_7_0[8] = {Shape_Bit7 , Shape_Bit6 , Shape_Bit5 , Shape_Bit4 ,
                               Shape_Bit3 , Shape_Bit2 , Shape_Bit1 , Shape_Bit0};

    TShape* TmpShape_15_8[8] = {Shape_Bit15 , Shape_Bit14 , Shape_Bit13 , Shape_Bit12 ,
                                Shape_Bit11 , Shape_Bit10 , Shape_Bit9 , Shape_Bit8};

    TShape* TmpShape_23_16[8] = {Shape_Bit23 , Shape_Bit22 , Shape_Bit21 , Shape_Bit20 ,
                                 Shape_Bit19 , Shape_Bit18 , Shape_Bit17 , Shape_Bit16};

    TShape* TmpShape_31_24[8] = {Shape_Bit31 , Shape_Bit30 , Shape_Bit29 , Shape_Bit28 ,
                                 Shape_Bit27 , Shape_Bit26 , Shape_Bit25 , Shape_Bit24};
    // Re-position Register modify
    Label_RegisterBits_31_24->Visible = !bIs8BitFormat;
    Label_RegisterBits_23_16->Visible = !bIs8BitFormat;
    Label_RegisterBits_15_8->Visible = !bIs8BitFormat;
    if(bIs8BitFormat)
    {
        //Label_RegisterBits_7_0->Left = 7;
        Panel_Bits_7_0->Left = 7;
    }
    else
    {
        //Label_RegisterBits_7_0->Left = 356;
        Panel_Bits_7_0->Left = 354;
    }

    Panel_Bits_31_24->Visible = !bIs8BitFormat;
    Panel_Bits_23_16->Visible = !bIs8BitFormat;
    Panel_Bits_15_8->Visible = !bIs8BitFormat;

    StringGrid_RegBits_31_24->Visible = !bIs8BitFormat;
    StringGrid_RegBits_23_16->Visible = !bIs8BitFormat;
    StringGrid_RegBits_15_8->Visible = !bIs8BitFormat;
    if(bIs8BitFormat)
    {
        StringGrid_RegBits_7_0->Left = 7;
    }
    else
    {
        StringGrid_RegBits_7_0->Left = 354;
    }

    for(int i = 0 ; i < 8 ; i++)
    {
        if(bIs8BitFormat)
        {
            TmpShape_7_0[i]->Left = 8 + 14 * i;
        }
        else
        {
            TmpShape_7_0[i]->Left = 355 + 14 * i;
        }
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        TmpShape_15_8[i]->Visible = !bIs8BitFormat;
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        TmpShape_23_16[i]->Visible = !bIs8BitFormat;
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        TmpShape_31_24[i]->Visible = !bIs8BitFormat;
    }

    DataString = "0x" + SG_Main->Cells[SG_Main->Col][SG_Main->Row];
    iValue = DataString.ToInt();
    AssignRegValueTosgRegBits(iValue);
    UpdateBitsPresent();

    if(bIs8BitFormat)
    {
        Edit_ModifyStopBit->Text = "7";
        Edit_ModifyStartBit->Text = "0";
    }
    else
    {
        Edit_ModifyStopBit->Text = "31";
        Edit_ModifyStartBit->Text = "0";
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::N8bits1Click(TObject *Sender)
{
    FormatChange(true);
    N8bits1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::N32bits1Click(TObject *Sender)
{
    FormatChange(false);
    N32bits1->Checked = true;
}
//---------------------------------------------------------------------------



void __fastcall TFrame_Main::SG_MainDblClick(TObject *Sender)
{
    /*if(!m_bIs8BitFormat)
    {
        RECT CurRect;
        CurRect = SG_Main->CellRect(m_iCurCol , m_iCurRow);
        Edit_RegModify->Parent = SG_Main;
        Edit_RegModify->Text = SG_Main->Cells[m_iCurCol][m_iCurRow];
        Edit_RegModify->Left = CurRect.left ;
        Edit_RegModify->Top = CurRect.top ;
        Edit_RegModify->Width = CurRect.right - CurRect.left ;
        Edit_RegModify->Height = CurRect.bottom - CurRect.top;
        Edit_RegModify->Visible = true;
        Edit_RegModify->SetFocus();
        Edit_RegModify->AutoSelect = true;
    }*/
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::SG_MainSelectCell(
      TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
    m_iPrevRow = ARow;
    m_iPrevCol = ACol;

    StringGrid_SelectCellUpdate(ACol , ARow , CanSelect);
    //ShowRegInfo(GetSelectedRegAddressStr(ARow, ACol, m_bIs8BitFormat), m_bIs8BitFormat);
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::StringGrid_SelectCellUpdate(int ACol , int ARow , bool &CanSelect)
{
    AnsiString RegValue;
    AnsiString DataString;

	RegValue = SG_Main->Cells[ACol][ARow];
    if(GetRightGrid() != NULL)
    {
        GetRightGrid()->Col = ACol;
        GetRightGrid()->Row = ARow;
        GetRightGrid()->Refresh();
    }

    if(RegValue.data() == NULL)
        return;

    if(m_bIs8BitFormat)
    {
        unsigned char value;
	    if(RegValue.Length()!=2)
        {
            value = 0;
        }
	    else
        {
            DataString = "0x" + RegValue;
            value = DataString.ToInt();
        }

	    AssignRegValueTosgRegBits(value);
	    UpdateBitsPresent();
        SetScrollValue(value);

        m_iCurCol = ACol;
        m_iCurRow = ARow;

        //if(GetRightGrid()!=NULL)
        //{
            //GetRightGrid()->Selection = SG_Main->Selection;
            //GetRightGrid()->Cells[0][0] = "0xFF";
        //}

        GetDevice()->SetRegister(m_iCurRow*16+m_iCurCol);
    }
    else
    {
        // Need to implement - Mars 20080212
        unsigned int value;
        if(RegValue.Length() != 8)
        {
            value = 0;
        }
        else
        {
            DataString = "0x" + RegValue;
            value = DataString.ToInt();
        }

	    AssignRegValueTosgRegBits(value);
	    UpdateBitsPresent();
        SetScrollValue(value);
        
        m_iCurCol = ACol;
        m_iCurRow = ARow;
        GetDevice()->SetRegister(m_iCurRow*16+m_iCurCol*4);
    }

}

void __fastcall TFrame_Main::SG_MainKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    if(Key == VK_PRIOR)
    {
        //m_bIsIncBtn = true;
        //RegBitsIncDec();
        Key = 0;
        return;
    }
    else if(Key == VK_NEXT)
    {
        //m_bIsIncBtn = false;
        //RegBitsIncDec();
        Key = 0;
        return;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::SG_MainKeyPress(TObject *Sender,
      char &Key)
{
    int Col,Row,Index,INT_SubAddr,Slave_24C32,Register;
	AnsiString a;
	BYTE data;
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
            DataString = "0x";
            DataString += SG_Main->Cells[Col][Row];
            data = DataString.ToInt();

            //Update the Reg's Info
            StringGrid_SelectCellUpdate(Col, Row, CanSelect);
            GridWriteByte(data);
        }
    }
    else
    {
        if(SG_Main->Cells[Col][Row].Length()==8)
        {
            // Need to implement - Mars 20080212
            unsigned int CurValue;
            AnsiString DataString;
            DataString = "0x";
            DataString += SG_Main->Cells[Col][Row];
            CurValue = DataString.ToInt();

            //Update the Reg's Info
            StringGrid_SelectCellUpdate(Col, Row, CanSelect);
            GridWriteDWord(CurValue);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::Edit_RegModifyExit(TObject *Sender)
{
    /*TEdit * ed;
    unsigned int CurValue;
    unsigned char SubAddr;
    unsigned char CurPage;
    bool CanSelect;
    AnsiString DataString;


    ed = (TEdit *)Sender;
    ed->Visible = false;
    DataString = "0x";
    DataString += ed->Text;
    CurValue = DataString.ToInt();
    SubAddr = m_iCurCol * 4 + m_iCurRow * 16;
    CurPage = ed->Text.ToInt();

    //Update the Reg's Info
    SG_Main->Cells[m_iCurCol][m_iCurRow] = ed->Text;
    AssignRegValueTosgRegBits(ed->Text.ToInt());
    UpdateBitsPresent();  */
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::Edit_RegModifyKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    /*if(Key == VK_RETURN)
    {
        TEdit * ed;
        unsigned int CurValue;
        unsigned char SubAddr;
        unsigned char CurPage;
        bool CanSelect;
        AnsiString DataString;

        ed = (TEdit *)Sender;
        ed->Visible = false;
        DataString = "0x";
        DataString += ed->Text;
        CurValue = DataString.ToInt();
        SubAddr = m_iCurCol * 4 + m_iCurRow * 16;
        CurPage = ed->Text.ToInt();

        //Update the Reg's Info
        SG_Main->Cells[m_iCurCol][m_iCurRow] = ed->Text;
        AssignRegValueTosgRegBits(ed->Text.ToInt());
        UpdateBitsPresent();
    }  */  
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::CB_PageKeyPress(TObject *Sender, char &Key)
{
    AnsiString a;

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
            FillStringGrid(SG_Main, m_slRegBuf, "0x"+CB_Page->Text);
            if(GetRightGrid()!=NULL)
            {
                FillStringGrid(GetRightGrid(), RefBuf, "0x"+CB_Page->Text);
            }
        }
    }
    else
    {
        Key = 0;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::Edit_BaseAddrKeyPress(TObject *Sender,
      char &Key)
{
    TEdit * ed;
    AnsiString a;

    ed = (TEdit *)Sender;
    a = ed->Text;

    if((Key>='0' && Key<='9')||(Key>='A' && Key<='F'))
    {
        if(a.Length()>=4)
        {
            ed->Text="";
        }
    }
    else if(Key>='a' && Key<='f')
    {
        if(a.Length()>=4)
        {
            ed->Text="";
        }
        Key-=0x20;
    }
    else if((Key == 13)||(Key == 8))
    {
        if(Key == 13)
        {
            GetDevice()->SetBase("0x"+ed->Text);
        }
    }
    else
    {
        Key = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::Shape_Bit31MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    TShape* Shape = (TShape*)Sender;
    if(Shape->Tag >= 0 && Shape->Tag <=7)
    {
        if(StringGrid_RegBits_7_0->Cells[7 - (Shape->Tag % 8)][0].ToInt())
        {
            Shape->Brush->Color = clSilver;
            StringGrid_RegBits_7_0->Cells[7 - (Shape->Tag % 8)][0] = 0;
            RegBitHexTransfer();
        }
        else
        {
            Shape->Brush->Color = clYellow;
            StringGrid_RegBits_7_0->Cells[7 - (Shape->Tag % 8)][0] = 1;
            RegBitHexTransfer();
        }
    }
    else if(Shape->Tag >= 8 && Shape->Tag <= 15)
    {
        if(StringGrid_RegBits_15_8->Cells[7 - (Shape->Tag % 8)][0].ToInt())
        {
            Shape->Brush->Color = clSilver;
            StringGrid_RegBits_15_8->Cells[7 - (Shape->Tag % 8)][0] = 0;
            RegBitHexTransfer();
        }
        else
        {
            Shape->Brush->Color = clYellow;
            StringGrid_RegBits_15_8->Cells[7 - (Shape->Tag % 8)][0] = 1;
            RegBitHexTransfer();
        }
    }
    else if(Shape->Tag >= 16 && Shape->Tag <= 23)
    {
        if(StringGrid_RegBits_23_16->Cells[7 - (Shape->Tag % 8)][0].ToInt())
        {
            Shape->Brush->Color = clSilver;
            StringGrid_RegBits_23_16->Cells[7 - (Shape->Tag % 8)][0] = 0;
            RegBitHexTransfer();
        }
        else
        {
            Shape->Brush->Color = clYellow;
            StringGrid_RegBits_23_16->Cells[7 - (Shape->Tag % 8)][0] = 1;
            RegBitHexTransfer();
        }
    }
    else if(Shape->Tag >= 24 && Shape->Tag <= 31)
    {
        if(StringGrid_RegBits_31_24->Cells[7 - (Shape->Tag % 8)][0].ToInt())
        {
            Shape->Brush->Color = clSilver;
            StringGrid_RegBits_31_24->Cells[7 - (Shape->Tag % 8)][0] = 0;
            RegBitHexTransfer();
        }
        else
        {
            Shape->Brush->Color = clYellow;
            StringGrid_RegBits_31_24->Cells[7 - (Shape->Tag % 8)][0] = 1;
            RegBitHexTransfer();
        }
    }    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::UpdateBitsPresent()
{
    TShape* TmpShape_7_0[8] = {Shape_Bit7 , Shape_Bit6 , Shape_Bit5 , Shape_Bit4 ,
                               Shape_Bit3 , Shape_Bit2 , Shape_Bit1 , Shape_Bit0};

    TShape* TmpShape_15_8[8] = {Shape_Bit15 , Shape_Bit14 , Shape_Bit13 , Shape_Bit12 ,
                                Shape_Bit11 , Shape_Bit10 , Shape_Bit9 , Shape_Bit8};

    TShape* TmpShape_23_16[8] = {Shape_Bit23 , Shape_Bit22 , Shape_Bit21 , Shape_Bit20 ,
                                 Shape_Bit19 , Shape_Bit18 , Shape_Bit17 , Shape_Bit16};

    TShape* TmpShape_31_24[8] = {Shape_Bit31 , Shape_Bit30 , Shape_Bit29 , Shape_Bit28 ,
                                 Shape_Bit27 , Shape_Bit26 , Shape_Bit25 , Shape_Bit24};
    for(int i = 0 ; i < 8 ; i++)
    {
        if(StringGrid_RegBits_7_0->Cells[i][0].ToInt())
        {
            TmpShape_7_0[i]->Brush->Color = clYellow;
        }
        else
        {
            TmpShape_7_0[i]->Brush->Color = clSilver;
        }
    }

    for(int i = 0 ; i < 8 ; i++)
    {
        if(StringGrid_RegBits_15_8->Cells[i][0].ToInt())
        {
            TmpShape_15_8[i]->Brush->Color = clYellow;
        }
        else
        {
            TmpShape_15_8[i]->Brush->Color = clSilver;
        }
    }

    for(int i = 0 ; i < 8 ; i++)
    {
        if(StringGrid_RegBits_23_16->Cells[i][0].ToInt())
        {
            TmpShape_23_16[i]->Brush->Color = clYellow;
        }
        else
        {
            TmpShape_23_16[i]->Brush->Color = clSilver;
        }
    }

    for(int i = 0 ; i < 8 ; i++)
    {
        if(StringGrid_RegBits_31_24->Cells[i][0].ToInt())
        {
            TmpShape_31_24[i]->Brush->Color = clYellow;
        }
        else
        {
            TmpShape_31_24[i]->Brush->Color = clSilver;
        }
    }
}

void __fastcall TFrame_Main:: RegBitHexTransfer()
{
    int i,Col,Row;
	BYTE reg;
    unsigned char CurPage;
    AnsiString DataString;

    if(m_bIs8BitFormat)
    {
        DataString = "0x" + SG_Main->Cells[SG_Main->Col][SG_Main->Row];
        m_uiPreValue = DataString.ToInt();

        reg = 0;
        for(i=0;i<8;i++)
        {
            reg <<= 1;
            if(StringGrid_RegBits_7_0->Cells[i][0] == "")
                reg |= 0;
            else
                reg |= (StringGrid_RegBits_7_0->Cells[i][0].ToInt());
        }


        Col = SG_Main->Col;
        Row = SG_Main->Row;

        SG_Main->Cells[Col][Row] = IntToHex(reg,2);
        
        SetScrollValue((unsigned int)reg);
        //GetDevice()->WriteByte(reg);
        GridWriteByte(reg);
    }
    else
    {

        int TmpValue;
        DataString = "0x" + SG_Main->Cells[SG_Main->Col][SG_Main->Row];
        m_uiPreValue = DataString.ToInt();

        TmpValue = 0;
        for(i=0;i<8;i++)
        {
            TmpValue <<= 1;
            if(StringGrid_RegBits_31_24->Cells[i][0] == "")
                TmpValue |= 0;
            else
                TmpValue |= (StringGrid_RegBits_31_24->Cells[i][0].ToInt());
        }
        for(i=0;i<8;i++)
        {
            TmpValue <<= 1;
            if(StringGrid_RegBits_23_16->Cells[i][0] == "")
                TmpValue |= 0;
            else
                TmpValue |= (StringGrid_RegBits_23_16->Cells[i][0].ToInt());
        }
        for(i=0;i<8;i++)
        {
            TmpValue <<= 1;
            if(StringGrid_RegBits_15_8->Cells[i][0] == "")
                TmpValue |= 0;
            else
                TmpValue |= (StringGrid_RegBits_15_8->Cells[i][0].ToInt());
        }
        for(i=0;i<8;i++)
        {
            TmpValue <<= 1;
            if(StringGrid_RegBits_7_0->Cells[i][0] == "")
                TmpValue |= 0;
            else
                TmpValue |= (StringGrid_RegBits_7_0->Cells[i][0].ToInt());
        }

        Col = SG_Main->Col;
        Row = SG_Main->Row;

        SG_Main->Cells[Col][Row] = IntToHex(TmpValue,8);

        SetScrollValue(TmpValue);
        //GetDevice()->WriteDWord(TmpValue);
        GridWriteDWord(TmpValue);
    }
}

void __fastcall TFrame_Main::AssignRegValueTosgRegBits(unsigned int value)
{
    StringGrid_RegBits_7_0->Cells[0][0] = (value >> 7) & 0x01;
    StringGrid_RegBits_7_0->Cells[1][0] = (value >> 6) & 0x01;
    StringGrid_RegBits_7_0->Cells[2][0] = (value >> 5) & 0x01;
    StringGrid_RegBits_7_0->Cells[3][0] = (value >> 4) & 0x01;
    StringGrid_RegBits_7_0->Cells[4][0] = (value >> 3) & 0x01;
    StringGrid_RegBits_7_0->Cells[5][0] = (value >> 2) & 0x01;
    StringGrid_RegBits_7_0->Cells[6][0] = (value >> 1) & 0x01;
    StringGrid_RegBits_7_0->Cells[7][0] = (value >> 0) & 0x01;

    StringGrid_RegBits_15_8->Cells[0][0] = (value >> 15) & 0x01;
    StringGrid_RegBits_15_8->Cells[1][0] = (value >> 14) & 0x01;
    StringGrid_RegBits_15_8->Cells[2][0] = (value >> 13) & 0x01;
    StringGrid_RegBits_15_8->Cells[3][0] = (value >> 12) & 0x01;
    StringGrid_RegBits_15_8->Cells[4][0] = (value >> 11) & 0x01;
    StringGrid_RegBits_15_8->Cells[5][0] = (value >> 10) & 0x01;
    StringGrid_RegBits_15_8->Cells[6][0] = (value >> 9) & 0x01;
    StringGrid_RegBits_15_8->Cells[7][0] = (value >> 8) & 0x01;

    StringGrid_RegBits_23_16->Cells[0][0] = (value >> 23) & 0x01;
    StringGrid_RegBits_23_16->Cells[1][0] = (value >> 22) & 0x01;
    StringGrid_RegBits_23_16->Cells[2][0] = (value >> 21) & 0x01;
    StringGrid_RegBits_23_16->Cells[3][0] = (value >> 20) & 0x01;
    StringGrid_RegBits_23_16->Cells[4][0] = (value >> 19) & 0x01;
    StringGrid_RegBits_23_16->Cells[5][0] = (value >> 18) & 0x01;
    StringGrid_RegBits_23_16->Cells[6][0] = (value >> 17) & 0x01;
    StringGrid_RegBits_23_16->Cells[7][0] = (value >> 16) & 0x01;

    StringGrid_RegBits_31_24->Cells[0][0] = (value >> 31) & 0x01;
    StringGrid_RegBits_31_24->Cells[1][0] = (value >> 30) & 0x01;
    StringGrid_RegBits_31_24->Cells[2][0] = (value >> 29) & 0x01;
    StringGrid_RegBits_31_24->Cells[3][0] = (value >> 28) & 0x01;
    StringGrid_RegBits_31_24->Cells[4][0] = (value >> 27) & 0x01;
    StringGrid_RegBits_31_24->Cells[5][0] = (value >> 26) & 0x01;
    StringGrid_RegBits_31_24->Cells[6][0] = (value >> 25) & 0x01;
    StringGrid_RegBits_31_24->Cells[7][0] = (value >> 24) & 0x01;
}

void __fastcall TFrame_Main::RegBitsIncDec(bool bIsIncBtn)
{
    /*unsigned char CurPage, reg;
    int AddValue , value;
    AnsiString DataString;
    int Interval , UpperBound , StopBit;

    
    //StopBit = Edit_ModifyStopBit->Text.ToInt() - 8 * m_iRegisterBitShift;
    //Interval = pow(2 , Edit_ModifyStartBit->Text.ToInt() - 8 * m_iRegisterBitShift);
    //UpperBound = pow(2 , Edit_ModifyStopBit->Text.ToInt() - 8 * m_iRegisterBitShift + 1);
    StopBit = Edit_ModifyStopBit->Text.ToInt();
    Interval = pow(2 , Edit_ModifyStartBit->Text.ToInt());
    //UpperBound = pow(2 , Edit_ModifyStopBit->Text.ToInt() - 8 * m_iRegisterBitShift + 1);
    UpperBound = pow(2 , Edit_ModifyStopBit->Text.ToInt() + 1);
    if(bIsIncBtn)
    {
        if(m_bIs8BitFormat)
        {
            CurPage = CB_Page->Text.ToInt();
            DataString = "0x" + SG_Main->Cells[SG_Main->Col][SG_Main->Row];
	        value = DataString.ToInt();
            //PreValue = value;

            AddValue = ((value>>(StopBit + 1))<<(StopBit + 1));
            value -= AddValue;
            value += Interval;
            if(value >= UpperBound)
            {
                value -= UpperBound;
            }
            value += AddValue;

            SG_Main->Cells[SG_Main->Col][SG_Main->Row] = IntToHex(value, 2);
            AssignRegValueTosgRegBits(value);
	        UpdateBitsPresent();

            reg = (SG_Main->Row * 16) + SG_Main->Col;
            //SystemRW.SystemBYTEWrite(CurPage , reg , value);
        }
        else
        {
            int TmpValue;
            CurPage = CB_Page->Text.ToInt();
            DataString = "0x" + SG_Main->Cells[SG_Main->Col][SG_Main->Row];
	        value = DataString.ToInt();

            TmpValue = value;

            AddValue = ((value>>(StopBit + 1))<<(StopBit + 1));
            value -= AddValue;
            value += Interval;
            if(value >= UpperBound)
            {
                value -= UpperBound;
            }
            value += AddValue;

            SG_Main->Cells[SG_Main->Col][SG_Main->Row] = IntToHex(value, 8);
            AssignRegValueTosgRegBits(value);
	        UpdateBitsPresent();

            reg = (SG_Main->Row * 16) + SG_Main->Col*4;
            //SystemRW.SystemDWORDWrite(CurPage , reg , TmpValue);
        }
    }
    else
    {
        if(m_bIs8BitFormat)
        {
            CurPage = CB_Page->Text.ToInt();
            DataString = "0x" + SG_Main->Cells[SG_Main->Col][SG_Main->Row];
	        value = DataString.ToInt();
            //PreValue = value;


            AddValue = ((value>>(StopBit + 1 ))<<(StopBit + 1));
            value -= AddValue;
            value -= Interval;
            if(value < 0)
            {
                value += UpperBound;
            }
            value += AddValue;

            SG_Main->Cells[SG_Main->Col][SG_Main->Row] = IntToHex(value, 2);
            AssignRegValueTosgRegBits(value);
	        UpdateBitsPresent();

            reg = (SG_Main->Row * 16) + SG_Main->Col;
            //SystemRW.SystemBYTEWrite(CurPage , reg , value);

        }
        else
        {
            int TmpValue;
            CurPage = CB_Page->Text.ToInt();
            DataString = "0x" + SG_Main->Cells[SG_Main->Col][SG_Main->Row];
	        value = DataString.ToInt();

            TmpValue = value;

            AddValue = ((value>>(StopBit + 1 ))<<(StopBit + 1));
            value -= AddValue;
            value -= Interval;
            if(value < 0)
            {
                value += UpperBound;
            }
            value += AddValue;

            SG_Main->Cells[SG_Main->Col][SG_Main->Row] = IntToHex(value, 8);
            AssignRegValueTosgRegBits(value);
	        UpdateBitsPresent();

            reg = (SG_Main->Row * 16) + SG_Main->Col * 4;
            //SystemRW.SystemDWORDWrite(CurPage , reg , TmpValue);
        }
    }
    SG_Main->SetFocus();         */
}

void __fastcall TFrame_Main::BitBtn_IncreaseRegValueClick(TObject *Sender)
{
    RegBitsIncDec(true);
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::BitBtn_DecreaseRegValueClick(TObject *Sender)
{
    RegBitsIncDec(false);

}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::Ed_ValueKeyPress(TObject *Sender, char &Key)
{
    Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::SB_ValueScroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
    TScrollBar * sb;
    unsigned int value, TmpValue;
    AnsiString DataString;
    int AddValue;

    sb = (TScrollBar *)Sender;

    Ed_Value->Text = IntToStr(sb->Position);          

    if (ScrollCode == scEndScroll)
    {
        DataString = "0x" + SG_Main->Cells[SG_Main->Col][SG_Main->Row];
        value = DataString.ToInt();

        AddValue = ((value>>(m_iStopBit + 1 ))<<(m_iStopBit + 1));
        AddValue += sb->Position<<m_iStartBit;
        AddValue += value & ((m_bIs8BitFormat?0xFF:0xFFFFFFFF) >> ((m_bIs8BitFormat?8:32) - m_iStartBit));         
        
        AssignRegValueTosgRegBits(AddValue);
        UpdateBitsPresent();
        RegBitHexTransfer();
    }    
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::Edit_ModifyStopBitChange(TObject *Sender)
{
    try
    {
        unsigned int value;
        m_iStopBit = Edit_ModifyStopBit->Text.ToInt();
        m_iStartBit = Edit_ModifyStartBit->Text.ToInt();
        if(m_iStopBit<m_iStartBit)
        {
            SB_Value->Enabled = false;
            Ed_Value->Enabled = false;
        }
        else if(pow(2,m_iStopBit-m_iStartBit+1)>65536)
        {
            SB_Value->Enabled = false;
            Ed_Value->Enabled = false;
        }
        else
        {
            AnsiString Data;
            SB_Value->Enabled = true;
            Ed_Value->Enabled = true;
            SB_Value->Min = 0;
            SB_Value->Max = pow(2,m_iStopBit-m_iStartBit+1)-1;

            Data = "0x"+SG_Main->Cells[SG_Main->Col][SG_Main->Row];
            value = (unsigned int )Data.ToInt();
            SetScrollValue(value);
        }

    }
    catch(...)
    {
    }


}
//---------------------------------------------------------------------------
void __fastcall TFrame_Main::SetScrollValue(unsigned int value)
{
    unsigned int tmp;
    int bitShift;

    if(SB_Value->Enabled == false)  return;
    
    bitShift = (m_bIs8BitFormat?8:32) -  (m_iStopBit+1);
    tmp = (value << bitShift)>>bitShift;
    tmp = (tmp >> m_iStartBit);

    SB_Value->Position = (int)tmp;
    Ed_Value->Text = IntToStr((int)tmp);

}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::Edit_BaseAddrExit(TObject *Sender)
{
    AnsiString Data;
    Data = "0x"+Edit_BaseAddr->Text;
    GetDevice()->SetBase(Data);    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::CB_PageSelect(TObject *Sender)
{
    GetDevice()->SetPage(CB_Page->ItemIndex);
    FillStringGrid(SG_Main, m_slRegBuf, CB_Page->ItemIndex);
    if(GetRightGrid()!=NULL)
    {
        FillStringGrid(GetRightGrid(), RefBuf, CB_Page->ItemIndex);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::CB_PageExit(TObject *Sender)
{
    AnsiString Data;
    Data = "0x"+CB_Page->Text;
    GetDevice()->SetPage(Data);
    FillStringGrid(SG_Main, m_slRegBuf, Data);
    if(GetRightGrid()!=NULL)
    {
        FillStringGrid(GetRightGrid(), RefBuf, Data);
    }
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::bBtn_ReadPageClick(TObject *Sender)
{
    unsigned int Value;
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
                GetDevice()->ReadDWord(Value);
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
                GetDevice()->ReadDWord(Value);

                SG_Main->Cells[j][i] = IntToHex(tmp, 8);

                PB->Position ++;
            }
        }
    }
    SG_Main->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::TV_PageDblClick(TObject *Sender)
{
    TTreeView * tree;
    tree = (TTreeView *)Sender;
    if(tree->Selected->Parent == NULL)
    {
        if(tree->Selected->SelectedIndex == 2)
        {
            tree->Selected->ImageIndex = 3;
            tree->Selected->SelectedIndex = 3;
        }
        else
        {
            tree->Selected->ImageIndex = 2;
            tree->Selected->SelectedIndex = 2;
        }
        return;
    }
    bBtn_ReadPage->Click();
    SG_Main->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::TV_PageChange(TObject *Sender,
      TTreeNode *Node)
{
    int board, page;

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
        FillStringGrid(SG_Main, m_slRegBuf, Node->Index);
        if(GetRightGrid()!=NULL)
        {
            FillStringGrid(GetRightGrid(), RefBuf, Node->Index);
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::bBtn_LoadAllClick(TObject *Sender)
{
    int block;
    if(OD_Hex->Execute())
    {
        m_slRegBuf->Clear();
        m_slRegBuf->LoadFromFile(OD_Hex->FileName);
        m_bHexLoaded = true;
        block = GetDevice()->GetPage();
        FillStringGrid(SG_Main, m_slRegBuf, block);
        if(GetRightGrid()!=NULL)
        {
            FillStringGrid(GetRightGrid(), RefBuf, block);
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::bBtn_WritePageClick(TObject *Sender)
{
    AnsiString str;
    Byte * buf;

    buf = (Byte *) malloc(256);
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            str = "0x"+SG_Main->Cells[j][i];
            buf[i*16+j] = str.ToInt();
        }
    }
    GetDevice()->SetRegister(0);
    GetDevice()->BurstWriteByte(256, buf);
    SG_Main->SetFocus();
    free(buf);
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::bBtn_WriteAllClick(TObject *Sender)
{
    bool bPages; 

    bPages = (GetDevice()->GetName()=="NT72312")? true:false;

    if (!m_bHexLoaded) return;

    PB->Visible = true;
    PB->Position = 0;
    PB->Max = m_iBoardNum*m_iPageNum;
    
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
            FillStringGrid(SG_Main, m_slRegBuf, j);
            if(GetRightGrid()!=NULL)
            {
                FillStringGrid(GetRightGrid(), RefBuf, j);
            }
            bBtn_WritePage->Click();
            PB->Position++;
        }
    }
    PB->Visible = false;
    ShowMessage("Write Hex Finished!");
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::bBtn_SaveAllClick(TObject *Sender)
{
    AnsiString buf;
    bool bPages;
    Byte * buf_data;

    PB->Visible = true;
    PB->Position = 0;
    PB->Max = m_iBoardNum*m_iPageNum;

    buf_data = (Byte *)malloc(256);

    bPages = (GetDevice()->GetName() == "NT72312")? true:false;
    
    if(SD_Hex->Execute())
    {
        m_slRegBuf->Clear();
        for(int b=0; b<m_iBoardNum; b++)
        {
            for(int p=0; p<m_iPageNum; p++)
            {
                GetDevice()->SetPage(p);
                GetDevice()->SetRegister(0);
                GetDevice()->BurstReadByte(256,buf_data);
                PB->Position++;
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
                        }
                        continue;
                    }
                }
                for(int i=0;i<16;i++)
                {
                    buf = ":1"+IntToHex(b,1)+ IntToHex(p,2) + IntToHex(i,1)+"000";
                    for(int j=0;j<16;j++)
                    {
                        buf += IntToHex(buf_data[i*16+j],2);
                    }
                    m_slRegBuf->Add(buf);
                } 
            }
        }

        m_slRegBuf->SaveToFile(SD_Hex->FileName);
    }
    PB->Visible = false;
    free(buf_data);
}
//---------------------------------------------------------------------------
bool __fastcall TFrame_Main::GridWriteByte(Byte b)
{
    return GetDevice()->WriteByte(b);
}
//---------------------------------------------------------------------------
bool __fastcall TFrame_Main::GridWriteDWord(unsigned int i)
{
    return GetDevice()->WriteDWord(i);
}
//---------------------------------------------------------------------------


void __fastcall TFrame_Main::Sa1Click(TObject *Sender)
{
    AnsiString buf;
    
    TStringList * SL_Page = new TStringList;
    
    SaveDialog->DefaultExt = "*.pg";
    SaveDialog->Filter = "Page Files|*.pg|All|*.*";
    SaveDialog->FileName = "Page_"+Edit_BaseAddr->Text + CB_Page->Text;
    if(SaveDialog->Execute())
    {
        for(int i=0;i<16;i++)
        {
            buf = "";
            for(int j=0;j<16;j++)
            {
                buf += SG_Main->Cells[j][i];
            }
            SL_Page->Add(buf);
        }
        SL_Page->SaveToFile(SaveDialog->FileName);
    }
    delete SL_Page;
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::loadPage1Click(TObject *Sender)
{
    AnsiString buf;
    TStringList * SL_Page = new TStringList;
    OpenDialog->Filter = "Page Files|*.pg|All|*.*";
    if(OpenDialog->Execute())
    {
        SL_Page->LoadFromFile(OpenDialog->FileName);
        for(int i=0;i<16;i++)
        {
            buf = SL_Page->Strings[i];
            for(int j=0;j<16;j++)
            {
                SG_Main->Cells[j][i] = buf.SubString(j*2+1,2);
            }
        }
    }
    delete SL_Page;    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::Read1Click(TObject *Sender)
{
    Byte bval;

    GetDevice()->ReadByte(bval);
    SG_Main->Cells[SG_Main->Col][SG_Main->Row] = IntToHex(bval,2);
}
//---------------------------------------------------------------------------

void __fastcall TFrame_Main::Write1Click(TObject *Sender)
{
    Byte bval;
    bval = ("0x"+SG_Main->Cells[SG_Main->Col][SG_Main->Row]).ToInt();
    GetDevice()->WriteByte(bval);
}
//---------------------------------------------------------------------------


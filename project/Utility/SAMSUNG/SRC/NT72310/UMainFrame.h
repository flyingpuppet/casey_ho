//---------------------------------------------------------------------------

#ifndef UMainFrameH
#define UMainFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCFrame.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include "UDeviceCreate.h"
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFrame_Main : public TMEMCFrame
{
__published:	// IDE-managed Components
    TPanel *Panel2;
    TSplitter *Splitter1;
    TPanel *MainViewPanel;
    TGroupBox *GroupBox_SysRegModify;
    TLabel *Label_RegisterBitsText;
    TShape *Shape_Bit7;
    TShape *Shape_Bit6;
    TShape *Shape_Bit5;
    TShape *Shape_Bit4;
    TShape *Shape_Bit3;
    TShape *Shape_Bit2;
    TShape *Shape_Bit1;
    TShape *Shape_Bit0;
    TShape *Shape_Bit23;
    TShape *Shape_Bit22;
    TShape *Shape_Bit21;
    TShape *Shape_Bit20;
    TShape *Shape_Bit19;
    TShape *Shape_Bit18;
    TShape *Shape_Bit17;
    TShape *Shape_Bit16;
    TShape *Shape_Bit15;
    TShape *Shape_Bit14;
    TShape *Shape_Bit13;
    TShape *Shape_Bit12;
    TShape *Shape_Bit11;
    TShape *Shape_Bit10;
    TShape *Shape_Bit9;
    TShape *Shape_Bit8;
    TShape *Shape_Bit31;
    TShape *Shape_Bit30;
    TShape *Shape_Bit29;
    TShape *Shape_Bit28;
    TShape *Shape_Bit27;
    TShape *Shape_Bit26;
    TShape *Shape_Bit25;
    TShape *Shape_Bit24;
    TLabel *Label_NotUsed;
    TLabel *Label_WO;
    TLabel *Label_RO;
    TLabel *Label_RW;
    TPanel *Panel_Bits_31_24;
    TLabel *Label_RegisterBits_31_24;
    TStringGrid *StringGrid_RegBits_31_24;
    TStringGrid *StringGrid_RegBits_23_16;
    TStringGrid *StringGrid_RegBits_15_8;
    TStringGrid *StringGrid_RegBits_7_0;
    TPanel *Panel_NotUsedColor;
    TPanel *Panel_WOColor;
    TPanel *Panel_ROColor;
    TPanel *Panel_RWColor;
    TPanel *Panel_Bits_23_16;
    TLabel *Label_RegisterBits_23_16;
    TPanel *Panel_Bits_15_8;
    TLabel *Label_RegisterBits_15_8;
    TPanel *Panel_Bits_7_0;
    TLabel *Label_RegisterBits_7_0;
    TGroupBox *GroupBox_IncreaseDecreaseRegVal;
    TLabel *Label_ModifyStopBit;
    TLabel *Label_Dash;
    TLabel *Label_ModifyStartBit;
    TBitBtn *BitBtn_DecreaseRegValue;
    TEdit *Edit_ModifyStopBit;
    TEdit *Edit_ModifyStartBit;
    TPanel *Panel1;
    TShape *Shape_VF;
    TShape *Shape_VE;
    TShape *Shape_VD;
    TShape *Shape_VC;
    TShape *Shape_VB;
    TShape *Shape_VA;
    TShape *Shape_V9;
    TShape *Shape_V8;
    TShape *Shape_V7;
    TShape *Shape_V6;
    TShape *Shape_V5;
    TShape *Shape_V4;
    TShape *Shape_V3;
    TShape *Shape_V2;
    TShape *Shape_V1;
    TShape *Shape_V0;
    TShape *Shape_HF;
    TShape *Shape_HE;
    TShape *Shape_HD;
    TShape *Shape_HC;
    TShape *Shape_HB;
    TShape *Shape_HA;
    TShape *Shape_H9;
    TShape *Shape_H8;
    TShape *Shape_H7;
    TShape *Shape_H6;
    TShape *Shape_H5;
    TShape *Shape_H4;
    TShape *Shape_H3;
    TShape *Shape_H2;
    TShape *Shape_H1;
    TShape *Shape_H0;
    TLabel *Label_H0;
    TLabel *Label_H1;
    TLabel *Label_H2;
    TLabel *Label_H3;
    TLabel *Label_H4;
    TLabel *Label_H5;
    TLabel *Label_H6;
    TLabel *Label_H7;
    TLabel *Label_H8;
    TLabel *Label_H9;
    TLabel *Label_HA;
    TLabel *Label_HB;
    TLabel *Label_HC;
    TLabel *Label_HD;
    TLabel *Label_HE;
    TLabel *Label_HF;
    TLabel *Label_V0;
    TLabel *Label_V1;
    TLabel *Label_V2;
    TLabel *Label_V3;
    TLabel *Label_V4;
    TLabel *Label_V5;
    TLabel *Label_V6;
    TLabel *Label_V7;
    TLabel *Label_V8;
    TLabel *Label_V9;
    TLabel *Label_VA;
    TLabel *Label_VB;
    TLabel *Label_VC;
    TLabel *Label_VD;
    TLabel *Label_VE;
    TLabel *Label_VF;
    TStringGrid *SG_Main;
    TTreeView *TV_Page;
    TImageList *Ima_TreeIcon;
    TPanel *Panel3;
    TLabel *Label_BaseAddr;
    TEdit *Edit_BaseAddr;
    TLabel *Lb_Board;
    TButton *Button_SystemRegRead;
    TGroupBox *GroupBox_SystemConnectStatus;
    TShape *Shape_ConnectStatus;
    TLabel *Label_ConnectStatus;
    TBitBtn *BitBtn_Reconnect;
    TSplitter *Splitter2;
    TBitBtn *bBtn_ReadPage;
    TBitBtn *bBtn_WritePage;
    TBitBtn *BitBtn_Undo;
    TBitBtn *BitBtn_Redo;
    TLabel *Label1;
    TComboBox *CB_Board;
    TComboBox *CB_Page;
    TPopupMenu *PM_SG;
    TMenuItem *Format1;
    TMenuItem *N8bits1;
    TMenuItem *N32bits1;
    TEdit *Edit_RegModify;
    TProgressBar *PB;
    TScrollBar *SB_Value;
    TBitBtn *BitBtn1;
    TEdit *Ed_Value;
    TBitBtn *bBtn_LoadAll;
    TBitBtn *bBtn_SaveAll;
    TBitBtn *bBtn_WriteAll;
    TOpenDialog *OD_Hex;
    TSaveDialog *SD_Hex;
    TPopupMenu *pm_Page;
    TMenuItem *Sa1;
    TMenuItem *loadPage1;
    TSaveDialog *SaveDialog;
    TOpenDialog *OpenDialog;
    TMenuItem *Read1;
    TMenuItem *Write1;
    void __fastcall BitBtn_ReconnectClick(TObject *Sender);
    void __fastcall SG_MainDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall N8bits1Click(TObject *Sender);
    void __fastcall N32bits1Click(TObject *Sender);
    void __fastcall SG_MainDblClick(TObject *Sender);
    void __fastcall SG_MainSelectCell(TObject *Sender,
          int ACol, int ARow, bool &CanSelect);
    void __fastcall SG_MainKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SG_MainKeyPress(TObject *Sender,
          char &Key);
    void __fastcall Edit_RegModifyExit(TObject *Sender);
    void __fastcall Edit_RegModifyKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall CB_PageKeyPress(TObject *Sender, char &Key);
    void __fastcall Edit_BaseAddrKeyPress(TObject *Sender, char &Key);
    void __fastcall Shape_Bit31MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall BitBtn_IncreaseRegValueClick(TObject *Sender);
    void __fastcall BitBtn_DecreaseRegValueClick(TObject *Sender);
    void __fastcall Ed_ValueKeyPress(TObject *Sender, char &Key);
    void __fastcall SB_ValueScroll(TObject *Sender, TScrollCode ScrollCode,
          int &ScrollPos);
    void __fastcall Edit_ModifyStopBitChange(TObject *Sender);
    void __fastcall Edit_BaseAddrExit(TObject *Sender);
    void __fastcall CB_PageSelect(TObject *Sender);
    void __fastcall CB_PageExit(TObject *Sender);
    void __fastcall bBtn_ReadPageClick(TObject *Sender);
    void __fastcall TV_PageDblClick(TObject *Sender);
    void __fastcall TV_PageChange(TObject *Sender, TTreeNode *Node);
    void __fastcall bBtn_LoadAllClick(TObject *Sender);
    void __fastcall bBtn_WritePageClick(TObject *Sender);
    void __fastcall bBtn_WriteAllClick(TObject *Sender);
    void __fastcall bBtn_SaveAllClick(TObject *Sender);
    void __fastcall Sa1Click(TObject *Sender);
    void __fastcall loadPage1Click(TObject *Sender);
    void __fastcall Read1Click(TObject *Sender);
    void __fastcall Write1Click(TObject *Sender);
private:	// User declarations
    DeviceCreate * Dev_Cre;
    unsigned int m_uRegAddr;
    unsigned int m_uiPreValue;
    int m_iCurCol;
    int m_iCurRow;
    int m_iPrevCol;
    int m_iPrevRow;
    int m_iStopBit;
    int m_iStartBit;
    unsigned char m_cRegTableValueTmp[16][16];
    unsigned int m_iRegTableValueTmp[4][16];
    //bool m_bIs8BitFormat;
    int m_iBoard;
    int m_iPage;
    int m_iPageIndex;
    unsigned int m_uiBaseAddress;

    
    void __fastcall DrawFocusRowCol(int ARow, int ACol, TColor MyShapeColor, TColor MyNumColor);
    void __fastcall FormatChange(bool bIs8BitFormat);
    void __fastcall RePositionRegisterModify(bool bIs8BitFormat);
    void __fastcall StringGrid_SelectCellUpdate(int ACol , int ARow , bool &CanSelect);
    void __fastcall UpdateBitsPresent();
    void __fastcall RegBitHexTransfer();
    void __fastcall AssignRegValueTosgRegBits(unsigned int value);
    void __fastcall RegBitsIncDec(bool bIsIncBtn);
    void __fastcall SetScrollValue(unsigned int value);

public:		// User declarations
    static int ArrBaseAdd[6];
    bool m_bHexLoaded;
    int m_iPageNum;
    int m_iBoardNum;
    TStringList * m_slRegBuf;
    __fastcall TFrame_Main(TComponent* Owner);
    __fastcall TFrame_Main(TComponent* Owner,DeviceCreate * oDev_Cre);
    virtual __fastcall ~TFrame_Main();

    void __fastcall SetCreator(DeviceCreate * oDev_Cre);
    DeviceCreate * __fastcall GetCreator();
    virtual bool __fastcall GridWriteByte(Byte b);
    virtual bool __fastcall GridWriteDWord(unsigned int i);
};
//---------------------------------------------------------------------------
int TFrame_Main::ArrBaseAdd[6] = {0xE000,0xE008,0xC015,0xC00C,0xC00D,0x9F02};

extern PACKAGE TFrame_Main *Frame_Main;
//---------------------------------------------------------------------------
#endif

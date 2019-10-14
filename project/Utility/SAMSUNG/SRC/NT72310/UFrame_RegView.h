//---------------------------------------------------------------------------

#ifndef UFrame_RegViewH
#define UFrame_RegViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCFrame.h"
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "RegLabeledEdit.h"
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFrame_RegView : public TMEMCFrame
{
__published:	// IDE-managed Components
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
    TEdit *Edit_RegModify;
    TPanel *Panel2;
    TBitBtn *BitBtn_CompareUndo;
    TBitBtn *BitButton_Save;
    TBitBtn *BitButton_Load;
    TBitBtn *BitButton_LMove;
    TBitBtn *BitButton_RMove;
    TGroupBox *GB_Status;
    TRegLabeledEdit *RegLabeledEdit1;
    TRegLabeledEdit *RegLabeledEdit2;
    TRegLabeledEdit *RegLabeledEdit3;
    TRegLabeledEdit *RegLabeledEdit4;
    TRegLabeledEdit *rle_Frame;
    TRegLabeledEdit *rle_N;
    TRegLabeledEdit *rle_M;
    TLabeledEdit *rle_VSync;
    TLabeledEdit *le_Clk;
    TBitBtn *BitBtn1;
    TLabeledEdit *rle_ovsync;
    TSaveDialog *SD_Hex;
    TOpenDialog *OD_Hex;
    void __fastcall SG_MainDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall rle_FrameChange(TObject *Sender);
    void __fastcall BitBtn_ReconnectClick(TObject *Sender);
    void __fastcall BitButton_RMoveClick(TObject *Sender);
    void __fastcall BitButton_LMoveClick(TObject *Sender);
    void __fastcall SG_MainKeyPress(TObject *Sender, char &Key);
    void __fastcall BitButton_SaveClick(TObject *Sender);
    void __fastcall BitButton_LoadClick(TObject *Sender);
private:	// User declarations
    //TStringList * RegBuf;
    void __fastcall DrawFocusRowCol(int ARow, int ACol,
        TColor MyShapeColor, TColor MyNumColor);
    void __fastcall CalVsync();
    void __fastcall updateBuf(int Col, int Row, int Block, AnsiString str, int Length);
public:		// User declarations
    __fastcall TFrame_RegView(TComponent* Owner);
    virtual __fastcall ~TFrame_RegView();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_RegView *Frame_RegView;
//---------------------------------------------------------------------------
#endif

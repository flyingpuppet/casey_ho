//---------------------------------------------------------------------------

#ifndef UFrame_Main_312FPGAH
#define UFrame_Main_312FPGAH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMainFrame.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include "RegCheckBox.h"
enum boards{Board_A, Board_B, Board_C, Board_ALL};
//---------------------------------------------------------------------------
class TFrame_Main_312FPGA : public TFrame_Main
{
__published:	// IDE-managed Components
    TRegCheckBox *cb_bisc;
    void __fastcall CB_BoardChange(TObject *Sender);
    void __fastcall bBtn_ReadPageClick(TObject *Sender);
    void __fastcall bBtn_WritePageClick(TObject *Sender);
    void __fastcall bBtn_WriteAllClick(TObject *Sender);
    void __fastcall bBtn_SaveAllClick(TObject *Sender);
    void __fastcall bBtn_LoadAllClick(TObject *Sender);
    void __fastcall CB_PageExit(TObject *Sender);
    void __fastcall CB_PageKeyPress(TObject *Sender, char &Key);
    void __fastcall CB_PageSelect(TObject *Sender);
    void __fastcall TV_PageChange(TObject *Sender, TTreeNode *Node);
    void __fastcall cb_biscClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFrame_Main_312FPGA(TComponent* Owner);
    __fastcall TFrame_Main_312FPGA(TComponent* Owner, DeviceCreate * oDev_Cre);
    virtual bool __fastcall GridWriteByte(Byte b);
    virtual bool __fastcall GridWriteDWord(unsigned int i);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_Main_312FPGA *Frame_Main_312FPGA;
//---------------------------------------------------------------------------
#endif

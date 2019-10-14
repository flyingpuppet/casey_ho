//---------------------------------------------------------------------------

#ifndef UMainFormH
#define UMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "WinSkinData.hpp"
#include <Grids.hpp>
#include "UMainFrame.h"
#include "UMEMCFrame.h"
#include "UDeviceCreate.h"
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include "UMEMCIni.h"
#include "CPort.hpp"
//---------------------------------------------------------------------------
class TMainForm : public TMEMCForm
{
__published:	// IDE-managed Components
    TStatusBar *MainStatusBar;
    TMainMenu *MainMenu;
    TMenuItem *File1;
    TMenuItem *Setting1;
    TMenuItem *IICSpeed1;
    TMenuItem *IICSlaveAddress1;
    TSkinData *SkinData;
    TControlBar *ControlBar1;
    TPanel *MainPanel;
    TPanel *ClientPanel;
    TSplitter *Splitter1;
    TCoolBar *MenuPanel;
    TMenuItem *N101;
    TMenuItem *N201;
    TMenuItem *N301;
    TMenuItem *N401;
    TMenuItem *N501;
    TMenuItem *NT72312_Chip;
    TMainMenu *MainMenu_72312_Chip;
    TMenuItem *MenuItem1;
    TMenuItem *MI_Frame_RegView_312Chip;
    TMenuItem *MenuItem5;
    TMenuItem *MI_Form_DataPath_Chip;
    TMenuItem *MI_Form_Demo_Chip;
    TMenuItem *MI_Form_UI312_Chip;
    TMenuItem *Connection1;
    TMenuItem *mi_IIC;
    TMenuItem *mi_DSU;
    TComPort *Com;
    TMenuItem *DSUSetup1;
    TMenuItem *MI_Form_spreadSpectrum;
    TMenuItem *BIN1;
    TMenuItem *CreateBIN1;
    TMenuItem *MI_Form_DPMeter;
    TMenuItem *Tool1;
    TMenuItem *ScanRGB1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ViewClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall NT72310Click(TObject *Sender);
    void __fastcall N101Click(TObject *Sender);
    void __fastcall N5A5A5A5A1Click(TObject *Sender);
    void __fastcall LVDSRx1Click(TObject *Sender);
    void __fastcall IICSlaveAddress1Click(TObject *Sender);
    void __fastcall LocalDimming1Click(TObject *Sender);
    void __fastcall Script1Click(TObject *Sender);
    void __fastcall eee1Click(TObject *Sender);
    void __fastcall mi_IICClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall DSUSetup1Click(TObject *Sender);
    void __fastcall CreateBIN1Click(TObject *Sender);
    void __fastcall ScanRGB1Click(TObject *Sender);
private:	// User declarations
    Byte Dev_SlaveAddress;
    Con_Type lCon;
    //AnsiString ICName;
    int IIC_Speed;
    //TStringList *BarButtonList;
    TStringList *FrameList;
    TStringList *DevList;
    TMEMCFrame * curFrame;
    TMEMCForm * curForm;
    I2CDevice * Dev;
    DeviceCreate * Dev_Cre;
    int devIndex;
    int IICIndex;
    TStringGrid ** SG_Left;
    TStringGrid ** SG_Right;
    TMEMCIniFile * iFile;
    Con_Type con;

    //TMEMCFrame *CurrentFrame;
private:
    void __fastcall FindMenuView(TMenuItem* mi);
    void __fastcall ShowMainFrame();
    void __fastcall SetDeviceRef();
    unsigned int __fastcall GenMask(unsigned char * in);
    int __fastcall IndexOfSlave(Byte slave);
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

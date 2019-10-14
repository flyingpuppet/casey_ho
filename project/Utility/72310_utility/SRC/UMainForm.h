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
    TMenuItem *NT72310;
    TMenuItem *NT72312_FPGA;
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
    TMenuItem *test1;
    TMenuItem *N5A5A5A5A1;
    TMenuItem *A5A5A5A51;
    TMainMenu *MainMenu_72312_FPGA;
    TMenuItem *MenuItem12;
    TMenuItem *MenuItem19;
    TMenuItem *MI_Form_DataPath;
    TMainMenu *MainMenu_72310;
    TMenuItem *MI_Page;
    TMenuItem *MI_Frame_RegView;
    TMenuItem *MI_Frame_DDR;
    TMenuItem *MI_Frame_BWMeasure;
    TMenuItem *MI_Frame_Image;
    TMenuItem *MI_Frame_DataPath;
    TMenuItem *MI_Frame_Debug;
    TMenuItem *MenuItem35;
    TMenuItem *MI_Form_NRetc;
    TMenuItem *MI_Form_Rim;
    TMenuItem *MI_Form_Film;
    TMenuItem *MI_Form_VP;
    TMenuItem *MI_Form_MC;
    TMenuItem *MI_Form_ME_1;
    TMenuItem *MI_Form_ME_2;
    TMenuItem *MI_Form_ME_3;
    TMenuItem *MI_Form_IP;
    TMenuItem *MI_Form_ME_Debug;
    TMenuItem *MI_Form_ReadBack;
    TMenuItem *MI_Form_Validation;
    TMenuItem *MI_Frame_RegView_312FPGA;
    TMenuItem *MI_Frame_DDR_312FPGA;
    TMenuItem *LVDSRx1;
    TMenuItem *MI_Frame_BWMeasure_312FPGA;
    TMenuItem *MI_Form_gauss;
    TMenuItem *NT72312_Chip;
    TMainMenu *MainMenu_72312_Chip;
    TMenuItem *MenuItem1;
    TMenuItem *MI_Frame_RegView_312Chip;
    TMenuItem *MI_Frame_DDR_312Chip;
    TMenuItem *MI_Frame_BWMeasure_312Chip;
    TMenuItem *MenuItem5;
    TMenuItem *MI_Form_DataPath_Chip;
    TMenuItem *MI_Form_gauss_Chip;
    TMenuItem *MI_Form_PHS;
    TMenuItem *Function1;
    TMenuItem *LocalDimming1;
    TMenuItem *Script1;
    TMenuItem *MI_Form_Range_test;
    TMenuItem *MI_Frame_Image_312Chip;
    TMenuItem *MI_Form_BandWidth;
    TMenuItem *eee1;
    TMenuItem *MI_Form_ME_1_Chip;
    TMenuItem *N11111;
    TMenuItem *MI_Form_Demo_Chip;
        TMenuItem *MI_Form_UI312_Chip;
    TMenuItem *Connection1;
    TMenuItem *mi_IIC;
    TMenuItem *mi_DSU;
    TComPort *Com;
    TMenuItem *DSUSetup1;
    TMenuItem *MI_Form_spreadSpectrum;
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
    void __fastcall N11111Click(TObject *Sender);
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

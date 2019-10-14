//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMainForm.h"
#include "UFrame_DDR.h"
#include "UFrame_RegView.h"
#include "UDeviceCreate.h"
#include "I2CDevice.h"
#include "UFrame_BWMeasure.h"
#include "UFrame_Image.h"
#include "I2C.h"
#include "UFrame_DataPath.h"
#include "UFrame_Debug.h"
#include "RegCheckBox.h"
#include "RegRadioButton.h"
#include "RegEdit.h"
#include "UForm_NRetc.h"
#include "UForm_Rim.h"
#include "UForm_Film.h"
#include "UForm_MC.h"
#include "UForm_VP.h"
#include "UForm_ME_1.h"
#include "UForm_ME_2.h"
#include "UForm_ME_3.h"
#include "UForm_IP.h"
#include "UForm_ME_Debug.h"
#include "UForm_ReadBack.h"
#include "UForm_Validation.h"
#include "UForm_DataPath.h"
#include "UFrame_Main_312FPGA.h"
#include "UFrame_RegView_312FPGA.h"
#include "UFrame_DDR_312FPGA.h"
#include "UI2CMap.h"
#include "UFrame_BWMeasure_312FPGA.h"
#include "UForm_Gauss.h"
#include "UChangeSlave.h"
#include "UFrame_Main_312Chip.h"
#include "UFrame_RegView_312Chip.h"
#include "UFrame_DDR_312Chip.h"
#include "UForm_DataPath_Chip.h"
#include "UForm_gauss_Chip.h"
#include "UFrame_BWMeasure_312Chip.h"
#include "UForm_Local_Dimming.h"
#include "ULoadScript.h"
#include "UForm_PHS.h"
#include "UBandWidthAXI.h"
#include "UForm_Range_test.h"
#include "UFrame_Image_312Chip.h"
#include "UForm_BandWidth.h"

#include "DCtrlManagerInterface.h"
#include "I2CDeviceInterface.h"
#include "UForm_ME_1_Chip.h"
#include "UForm_Demo_Chip.h"
#include "UUI312_Chip.h"
#include "NT72682Updater.h"
#include "spreadSpectrum.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCForm"
#pragma link "WinSkinData"
#pragma link "UMainFrame"
#pragma link "UMEMCFrame"
#pragma link "CPort"
#pragma resource "*.dfm"

TMainForm *MainForm;


#define VIEW_INDEX  1

#define NT72310_Slave   0x34
#define NT72312_Slave   0x30

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TMEMCForm(Owner)
{
}
//---------------------------------------------------------------------------

AnsiString Slaves[] =
{
    "NT72310", "0x34",
    "NT72312", "0x30",
    "NT72312C", "0x34",
};
Byte SlaveIndex[] =
{
    0, 0x34,
    1, 0x30,
    2, 0x34,
    0xFF,
};

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //BarButtonList = new TStringList;
    //DevList = new TStringList;
    //AnsiString FileName;
    //AnsiString ICName;
    TMainMenu * mm;
    int contype;
    //Byte slave_addr;

    /*FileName = "Config.ini";

    if(!FileExist(FileName))
    {
        CreateFile
    }*/
    SetFilePath(GetCurrentDir());

    iFile = new TMEMCIniFile(GetFilePath()+"\\Config.ini");

    iFile->ReadSlaveAddress(Dev_SlaveAddress);


    Dev_Cre = new DeviceCreate;



    iFile->ReadICIndex(devIndex);
    iFile->ReadIICIndex(IICIndex);
    iFile->ReadConType(contype);

    con = (Con_Type)contype;
    lCon = con;
    if(con == conDSU)
    {
        //Com->ShowSetupDialog();
        /*if(Com->Connected == false)
        {
            Com->Open();
        } */
        mi_DSU->Checked = true;
    }
    else
    {
        mi_IIC->Checked = true;
    }


    Menu = MainMenu;
    if(devIndex == 0)
    {
        mm = MainMenu_72310;
        NT72310->Checked = true;
    }
    else if(devIndex == 1)
    {
        mm = MainMenu_72312_FPGA;
        NT72312_FPGA->Checked = true;
    }
    else if(devIndex == 2)
    {
        mm = MainMenu_72312_Chip;
        NT72312_Chip->Checked = true;
    }
    Menu->Merge(mm);;

    for(int i=0; i < mm->Items->Count; i++)
    {
        FindMenuView(mm->Items->Items[i]);
    }
    Dev = Dev_Cre->CreateDevice(Slaves[devIndex*2],Dev_SlaveAddress, con);
    if(con == conDSU)
    {
        Dev->GetProtocol()->SetConnect(Com);
    }

    Dev->SetIICIndex(IICIndex);
    SetDeviceRef();

    ShowMainFrame();

    RegisterClass(__classid(TFrame_RegView));
    RegisterClass(__classid(TFrame_DDR));
    RegisterClass(__classid(TFrame_BWMeasure));
    RegisterClass(__classid(TFrame_Image));
    RegisterClass(__classid(TFrame_DataPath));
    RegisterClass(__classid(TFrame_Debug));
    RegisterClass(__classid(TForm_NRetc));
    RegisterClass(__classid(TForm_Rim));
    RegisterClass(__classid(TForm_Film));
    RegisterClass(__classid(TForm_VP));
    RegisterClass(__classid(TForm_MC));
    RegisterClass(__classid(TForm_ME_1));
    RegisterClass(__classid(TForm_ME_2));
    RegisterClass(__classid(TForm_ME_3));
    RegisterClass(__classid(TForm_IP));
    RegisterClass(__classid(TForm_ME_Debug));
    RegisterClass(__classid(TForm_ReadBack));
    RegisterClass(__classid(TForm_Validation));
    RegisterClass(__classid(TForm_DataPath));
    RegisterClass(__classid(TFrame_RegView_312FPGA));
    RegisterClass(__classid(TFrame_DDR_312FPGA));
    RegisterClass(__classid(TFrame_BWMeasure_312FPGA));
    RegisterClass(__classid(TForm_gauss));
    RegisterClass(__classid(TFrame_RegView_312Chip));
    RegisterClass(__classid(TFrame_DDR_312Chip));
    RegisterClass(__classid(TForm_DataPath_Chip));
    RegisterClass(__classid(TForm_gauss_Chip));
    RegisterClass(__classid(TFrame_BWMeasure_312Chip));
    RegisterClass(__classid(TForm_PHS));
    RegisterClass(__classid(TForm_Range_test));
    RegisterClass(__classid(TFrame_Image_312Chip));
    RegisterClass(__classid(TForm_BandWidth));
    RegisterClass(__classid(TForm_ME_1_Chip));
    RegisterClass(__classid(TForm_Demo_Chip));
    RegisterClass(__classid(TForm_UI312_Chip));
    RegisterClass(__classid(TForm_spreadSpectrum));
}
//---------------------------------------------------------------------------
//button click function
void __fastcall TMainForm::ViewClick(TObject *Sender)
{
    int itemIndex;
    TComponent * mi;
    TClass cla;
    AnsiString Name;

    mi = (TComponent *)Sender;
    Name = mi->Name;

    Name.Delete(1,3);

    Name.Insert("T",1);

    cla = FindClass(Name);
    if(Name.SubString(1,6)=="TFrame")
    {
        if(curFrame != NULL)
        {
            if(curFrame->Name == Name)
            {
                return;
            }
            //curFrame->Free();
            delete curFrame;
            curFrame = NULL;
        }
        Application->CreateForm(cla,&curFrame);
        //curFrame->SetDevice(Dev);
        curFrame->Parent = ClientPanel;
        curFrame->Align = alClient;
        SkinData->UpdateSkinControl(this,curFrame);
        curFrame->Show();
    }
    else if(Name.SubString(1,5)=="TForm")
    {
        if(curForm != NULL)
        {
            if(curForm->Name == Name)
            {
                curForm->Show();
                return;
            }
            delete curForm;
            curForm = NULL;
        }

        Application->CreateForm(cla, &curForm);
        //curForm->SetDevice(Dev);
        SkinData->UpdateSkinControl(this,curForm);
        curForm->Show();
    }
}
//---------------------------------------------------------------------------
//Find the MenuItem that can show frame and make the related button
void __fastcall TMainForm::FindMenuView(TMenuItem* mi)
{
    TSpeedButton * button;
    String strName;

    //ShowMessage(mi->Name+" "+IntToStr(mi->Count));
    if(mi->Count == 0)   return;

    for(int i=0; i < mi->Count; i++)
    {
        FindMenuView(mi->Items[i]);
        if(mi->Items[i]->GroupIndex == VIEW_INDEX)
        {
           mi->Items[i]->OnClick = ViewClick;
           button = new TSpeedButton(this);
           button->Caption = mi->Items[i]->Caption;
           button->Parent = MenuPanel;
           button->Width = 50;
           button->Height = MenuPanel->Height-2;
           button->Left = (MenuPanel->ControlCount-1)*50+2;
           strName = mi->Items[i]->Name;
           strName.Delete(1,3);
           strName.Insert("BN_",1);
           button->Name = strName;
           //BarButtonList->AddObject(strName, button);
           button->OnClick = ViewClick;
        }
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    delete Frame_Main;

    /*for(int i=BarButtonList->Count-1;i>=0;i--)
    {
        delete BarButtonList->Objects[i];
    }
    delete BarButtonList;     */

    delete Dev;
    delete Dev_Cre;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::NT72310Click(TObject *Sender)
{
    TMenuItem * mi;
    TMainMenu * mm;
    //AnsiString ICName;
    //Byte slave_addr;

    mi = (TMenuItem *)Sender;

    mi->Checked = true;
    devIndex = mi->Tag;
    mm = MainMenu_72310;

    if(Dev->GetName() != Slaves[devIndex*2])
    {
        Dev_SlaveAddress = Slaves[devIndex*2+1].ToInt();
        delete Dev;
        Dev = NULL;
        Dev = Dev_Cre->CreateDevice(Slaves[devIndex*2],Dev_SlaveAddress, con);
        if(con == conDSU)
        {
            Dev->GetProtocol()->SetConnect(Com);
        }
        IICIndex = IndexOfSlave(Dev_SlaveAddress);
        Dev->SetIICIndex(IICIndex);
        iFile->WriteIICIndex(IICIndex);
        if(devIndex == 0)
        {
            Menu->Unmerge(mm);
            Menu = MainMenu;
            Menu->Merge(MainMenu_72310);
            mm = MainMenu_72310;
        }
        else if(devIndex == 1)
        {
            Menu->Unmerge(mm);
            Menu->Merge(MainMenu_72312_FPGA);;
            mm = MainMenu_72312_FPGA;
        }
        else if(devIndex == 2)
        {
            Menu->Unmerge(mm);
            Menu->Merge(MainMenu_72312_Chip);;
            mm = MainMenu_72312_Chip;
        }
        for(int i=MenuPanel->ControlCount-1; i>=0; i--)
        {
            delete MenuPanel->Controls[i];
        }
        /*for(int i=BarButtonList->Count-1; i>=0; i--)
        {
            delete BarButtonList->Objects[i];
        } */
        for(int i=0; i < mm->Items->Count; i++)
        {
            FindMenuView(mm->Items->Items[i]);
        }

        SetDeviceRef();
        ShowMainFrame();
        iFile->WriteICIndex(devIndex);
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowMainFrame()
{
    if(Frame_Main != NULL)
    {
        delete Frame_Main;
        Frame_Main = NULL;
    }

    /*for(int i=0;i<ClientPanel->ControlCount;i++)
    {
        if(ClientPanel->Controls[i] != NULL)
        {
            delete ClientPanel->Controls[i];
        }
    } */
    if(curFrame != NULL)
    {
        delete curFrame;
        curFrame = NULL;
    }
    
    if(devIndex == 0)
    {
        if(Frame_Main_312FPGA != NULL)
        {
            delete Frame_Main_312FPGA;
            Frame_Main_312FPGA == NULL;
        }
        if(Frame_Main_312Chip != NULL)
        {
            delete Frame_Main_312Chip;
            Frame_Main_312Chip == NULL;
        }
        Frame_Main = new TFrame_Main(this, Dev_Cre);
        Frame_Main->Parent = MainPanel;
        Frame_Main->Align = alClient;
        Frame_Main->Show();
    }
    else if(devIndex == 1)
    {
        if(Frame_Main != NULL)
        {
            delete Frame_Main;
            Frame_Main == NULL;
        }
        if(Frame_Main_312Chip != NULL)
        {
            delete Frame_Main_312Chip;
            Frame_Main_312Chip == NULL;
        }
        Frame_Main_312FPGA = new TFrame_Main_312FPGA(this, Dev_Cre);
        Frame_Main_312FPGA->Parent = MainPanel;
        Frame_Main_312FPGA->Align = alClient;
        Frame_Main_312FPGA->Show();
    }
    else if(devIndex == 2)
    {
        if(Frame_Main != NULL)
        {
            delete Frame_Main;
            Frame_Main == NULL;
        }
        if(Frame_Main_312FPGA != NULL)
        {
            delete Frame_Main_312FPGA;
            Frame_Main_312FPGA == NULL;
        }
        Frame_Main_312Chip = new TFrame_Main_312Chip(this, Dev_Cre);
        Frame_Main_312Chip->Parent = MainPanel;
        Frame_Main_312Chip->Align = alClient;
        Frame_Main_312Chip->Show();
    }
    SkinData->UpdateSkinControl(this);
}

void __fastcall TMainForm::SetDeviceRef()
{
    TRegCheckBox::SetDevice(Dev);
    TRegRadioButton::SetDevice(Dev);
    TRegEdit::SetDevice(Dev);
    TRegScrollBar::SetDevice(Dev);
    TRegLabeledEdit::SetDevice(Dev);
    TMEMCForm::SetDevice(Dev);
    TMEMCFrame::SetDevice(Dev);
    BandWidthAXI::SetDevice(Dev);
}


void __fastcall TMainForm::N101Click(TObject *Sender)
{
    TMenuItem * mi;

    mi = (TMenuItem *)Sender;

    mi->Checked = true;
    Dev->GetProtocol()->SetSpeed(mi->Tag);
}
//---------------------------------------------------------------------------




void __fastcall TMainForm::N5A5A5A5A1Click(TObject *Sender)
{
    AnsiString strValue, strErr;
    unsigned int Address, Value, readValue, regMask;
    unsigned char regAttr[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    unsigned char * regs;
    TMenuItem * mi;
    TStringList * sl;

    int pages, boards;


    mi = (TMenuItem *)Sender;
    sl = new TStringList();
    /*if(RB_A5->Checked)
    {
        strValue = RB_A5->Caption;
    }
    if(RB_5A->Checked)
    {
        strValue = RB_5A->Caption;
    }
    */
    if(mi->Tag == 0)
    {
        strValue = "5A5A5A5A";
    }
    else
    {
        strValue = "A5A5A5A5";
    }
    strValue = "0x"+strValue;
    Value = strValue.ToInt();

    /*ProgressBar_Complete->Position = 0;
    ProgressBar_Complete->Max = PAGE_REG_NUM * PAGE_NUM*BOARD_NUM;
    ProgressBar_Complete->Visible = true; */

    pages = GetDevice()->GetPageNumber();
    boards = GetDevice()->GetBoardNumber();
    
    for(int l=0; l<boards; l++)
    {
        for(int k=0; k<pages; k++)
        {
            if(GetDevice()->GetPageExist(l,k))
            {
                for (int i=0;i<16;i++)
                {
                    for(int j=0;j<16;j+=4)
                    {
                        Application->ProcessMessages();
                        Address = (GetDevice()->GetBase()<<16)+(((l<<6)+k)<<8)+(i*16+j);
                        GetDevice()->WriteDWord(Address, Value);
                    }
                }
            }
        }
    }

    for(int l=0; l<boards; l++)
    {
        for(int k=0; k<pages;k++)
        {
            if(GetDevice()->GetPageExist(l,k))
            {
                for (int i=0;i<16;i++)
                {
                    for(int j=0;j<16;j+=4)
                    {
                        Application->ProcessMessages();
                        Address = (GetDevice()->GetBase()<<16)+(((l<<6)+k)<<8)+(i*16+j);
                        GetDevice()->ReadDWord(Address, readValue);
                        regs = GetDevice()->GetRegMap(k);

                        if(regs != NULL)
                        {
                            regAttr[0] = regs[16*i+j];
                            regAttr[1] = regs[16*i+j+1];
                            regAttr[2] = regs[16*i+j+2];
                            regAttr[3] = regs[16*i+j+3];
                        }

                        regMask = GenMask(regAttr);

                        if((readValue & regMask) != (Value & regMask))
                        {
                            strErr = "Board: "+AnsiString(char('A'+l))+" Page: 0x"+IntToHex(k,2)+
                                     " Reg: 0x"+ IntToHex(i*16+j,2)+" is wrong "+
                                     "Write Value = 0x"+IntToHex((int)Value,8)+" Read Value = "+IntToHex((int)readValue, 8);
                            //MessageBox(NULL , strErr.c_str() , "Error" , MB_OK);
                            sl->Add(strErr);
                            //return;
                        }
                    }
                }
            }
        }
    }
    sl->Add("END");
    sl->SaveToFile(".\\RegLog.txt");
    MessageBox(NULL , "Verify Complete!" , "Info" , MB_OK);
    delete sl;
}
//---------------------------------------------------------------------------
unsigned int __fastcall TMainForm::GenMask(unsigned char * in)
{
    unsigned int result = 0;
    
    for(int i=0;i<4;i++)
    {
        result = (in[i]<<(i*8))+result;
    }

    return result;
}


void __fastcall TMainForm::LVDSRx1Click(TObject *Sender)
{
    I2CMap = new TI2CMap(this);
    I2CMap->ShowModal();    
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IICSlaveAddress1Click(TObject *Sender)
{
    int result;
    Form_ChangeSlave = new TForm_ChangeSlave(this);
    result = Form_ChangeSlave->ShowModal();
    if(result > 0)
    {
        Dev_SlaveAddress = (Byte)result;
        if(Dev != NULL)
        {
            Dev->SetSlave(Dev_SlaveAddress);
        }
        else
        {
            Dev = Dev_Cre->CreateDevice(Slaves[devIndex], Dev_SlaveAddress, con);    
        }
        iFile->WriteSlaveAddress(Dev_SlaveAddress);
        iFile->WriteIICIndex(IndexOfSlave(Dev_SlaveAddress));
        Dev->SetIICIndex(IndexOfSlave(Dev_SlaveAddress));
    }
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::IndexOfSlave(Byte slave)
{
    int i = 0;
    while( SlaveIndex[i] != 0xFF )
    {
        if(SlaveIndex[i*2+1] == slave)
        {
            return i;
        }
        i++;
    }
    return -1;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LocalDimming1Click(TObject *Sender)
{
    Form_Local_Dimming = new TForm_Local_Dimming(this);
    Form_Local_Dimming->Show();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Script1Click(TObject *Sender)
{
    Form_LoadScript = new TForm_LoadScript(this);
    Form_LoadScript->Show();    
}
//---------------------------------------------------------------------------

typedef IDCtrlManagerInterface * __stdcall (*GetDynCtrlManagerFunc)(void);
void __fastcall TMainForm::eee1Click(TObject *Sender)
{
    HMODULE  hLibrary = LoadLibrary("DCtrlManager.dll");
    IDCtrlManagerInterface *pDCtrlManager;
    if(hLibrary)
    {
      GetDynCtrlManagerFunc pGetDynManagerServer = (GetDynCtrlManagerFunc)GetProcAddress(hLibrary,"GetDynamCtrlManager");
      if(pGetDynManagerServer)
      {
        pDCtrlManager = pGetDynManagerServer();
        Byte val;
        Dev->ReadByte(0xE0001330,val);
        //ShowMessage(val);
        pDCtrlManager->ShowDCtrlManager(Application->Handle, static_cast<I2CDeviceInterface *>(Dev));
        delete  pDCtrlManager;
      }
      //FreeLibrary(hLibrary);
    }    
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::mi_IICClick(TObject *Sender)
{
    TMenuItem * mi;

    mi = (TMenuItem *)Sender;

    mi->Checked = true;
    if(lCon != (Con_Type) mi->Tag)
    {
        con = (Con_Type) mi->Tag;
        iFile->WriteConType((int)con);
        lCon = con;
        /*if(con == conDSU)
        {
            Com->ShowSetupDialog();
            if(Com->Connected == false)
            {
                Com->Open();
            }
        } */
        Dev = Dev_Cre->CreateDevice(Slaves[devIndex*2],Dev_SlaveAddress, con);
        if(con == conDSU)
        {
            Dev->GetProtocol()->SetConnect(Com);
        }
        SetDeviceRef();
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Button1Click(TObject *Sender)
{
    Byte buf[5];
    buf[0] = 0x55;
    buf[1] = 0x55;
    buf[2] = 0x55;
    buf[3] = 0x55;

    Com->Write(buf,4);


    buf[0] = 0x80;
    buf[1] = 0xE0;
    buf[2] = 0x00;
    buf[3] = 0x00;
    buf[4] = 0x00;
    Com->Write(buf, 5);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DSUSetup1Click(TObject *Sender)
{
    Com->ShowSetupDialog();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N11111Click(TObject *Sender)
{
    Form_NT72682Updater = new TForm_NT72682Updater(this);
    Form_NT72682Updater->ShowModal();    
}
//---------------------------------------------------------------------------


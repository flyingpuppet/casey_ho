//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


//---------------------------------------------------------------------------
USEFORM("SRC\NT72310\UFrame_RegView.cpp", Frame_RegView); /* TFrame: File Type */
USEFORM("SRC\NT72310\UMainFrame.cpp", Frame_Main); /* TFrame: File Type */
USEFORM("SRC\NT72312_FPGA\UFrame_Main_312FPGA.cpp", Frame_Main_312FPGA); /* TFrame: File Type */
USEFORM("SRC\NT72312_FPGA\UFrame_RegView_312FPGA.cpp", Frame_RegView_312FPGA); /* TFrame: File Type */
USEFORM("SRC\NT72312_Chip\UFrame_Main_312Chip.cpp", Frame_Main_312Chip); /* TFrame: File Type */
USEFORM("SRC\NT72312_Chip\UFrame_RegView_312Chip.cpp", Frame_RegView_312Chip); /* TFrame: File Type */
USEFORM("SRC\NT72312_Chip\UForm_Demo_Chip.cpp", Form_Demo_Chip);
USEFORM("SRC\NT72312_FPGA\UForm_DataPath.cpp", Form_DataPath);
USEFORM("SRC\NT72312_Chip\UForm_DataPath_Chip.cpp", Form_DataPath_Chip);
USEFORM("share\NT72682Updater.cpp", Form_NT72682Updater);
USEFORM("share\spreadSpectrum.cpp", Form_spreadSpectrum);
USEFORM("share\UI2CMap.cpp", I2CMap);
USEFORM("share\UMEMCForm.cpp", MEMCForm);
USEFORM("share\UMEMCFrame.cpp", MEMCFrame); /* TFrame: File Type */
USEFORM("UMainForm.cpp", MainForm);
USEFORM("UUI312_Chip.cpp", Form_UI312_Chip);
USEFORM("UDPMeter.cpp", Form_DPMeter);
USEFORM("UScanRGB.cpp", Form_ScanRGB);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------










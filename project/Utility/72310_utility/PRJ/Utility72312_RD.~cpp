//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


//---------------------------------------------------------------------------
USEFORM("..\SRC\NT72310\UFrame_RegView.cpp", Frame_RegView); /* TFrame: File Type */
USEFORM("..\SRC\NT72310\UFrame_DDR.cpp", Frame_DDR); /* TFrame: File Type */
USEFORM("..\SRC\NT72310\UMainFrame.cpp", Frame_Main); /* TFrame: File Type */
USEFORM("..\SRC\NT72310\UFrame_BWMeasure.cpp", Frame_BWMeasure); /* TFrame: File Type */
USEFORM("..\SRC\NT72310\UFrame_Image.cpp", Frame_Image); /* TFrame: File Type */
USEFORM("..\SRC\NT72310\UFrame_DataPath.cpp", Frame_DataPath); /* TFrame: File Type */
USEFORM("..\SRC\NT72310\UForm_Bitmap.cpp", Form_Bitmap);
USEFORM("..\SRC\NT72310\UFrame_Debug.cpp", Frame_Debug); /* TFrame: File Type */
USEFORM("..\SRC\NT72310\UForm_NRetc.cpp", Form_NRetc);
USEFORM("..\SRC\NT72310\UForm_Rim.cpp", Form_Rim);
USEFORM("..\SRC\NT72310\UForm_Film.cpp", Form_Film);
USEFORM("..\SRC\NT72310\UForm_VP.cpp", Form_VP);
USEFORM("..\SRC\NT72310\UForm_MC.cpp", Form_MC);
USEFORM("..\SRC\NT72310\UForm_ME_1.cpp", Form_ME_1);
USEFORM("..\SRC\NT72310\UForm_ME_2.cpp", Form_ME_2);
USEFORM("..\SRC\NT72310\UForm_ME_3.cpp", Form_ME_3);
USEFORM("..\SRC\NT72310\UForm_IP.cpp", Form_IP);
USEFORM("..\SRC\NT72310\UForm_ME_Debug.cpp", Form_ME_Debug);
USEFORM("..\SRC\NT72310\UForm_BWData.cpp", Form_BWData);
USEFORM("..\SRC\NT72310\UForm_ReadBack.cpp", Form_ReadBack);
USEFORM("..\SRC\NT72310\UForm_Validation.cpp", Form_Validation);
USEFORM("..\SRC\NT72312_FPGA\UForm_DataPath.cpp", Form_DataPath);
USEFORM("..\SRC\NT72312_FPGA\UFrame_Main_312FPGA.cpp", Frame_Main_312FPGA); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_FPGA\UFrame_RegView_312FPGA.cpp", Frame_RegView_312FPGA); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_FPGA\UFrame_DDR_312FPGA.cpp", Frame_DDR_312FPGA); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_FPGA\UForm_Pdepth.cpp", Form_Pdepth);
USEFORM("..\SRC\NT72312_FPGA\UFrame_BWMeasure_312FPGA.cpp", Frame_BWMeasure_312FPGA); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_FPGA\UForm_Gauss.cpp", Form_gauss);
USEFORM("..\SRC\NT72312_Chip\UFrame_Main_312Chip.cpp", Frame_Main_312Chip); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_Chip\UFrame_RegView_312Chip.cpp", Frame_RegView_312Chip); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_Chip\UFrame_DDR_312Chip.cpp", Frame_DDR_312Chip); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_Chip\UForm_DataPath_Chip.cpp", Form_DataPath_Chip);
USEFORM("..\SRC\NT72312_Chip\UForm_gauss_Chip.cpp", Form_gauss_Chip);
USEFORM("..\SRC\NT72312_Chip\UFrame_BWMeasure_312Chip.cpp", Frame_BWMeasure_312Chip); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_Chip\UForm_PHS.cpp", Form_PHS);
USEFORM("..\SRC\UForm_AXI_IDList.cpp", Form_AXI_IDList);
USEFORM("..\SRC\NT72312_Chip\UForm_Range_test.cpp", Form_Range_test);
USEFORM("..\SRC\NT72312_Chip\UFrame_Image_312Chip.cpp", Frame_Image_312Chip); /* TFrame: File Type */
USEFORM("..\SRC\NT72312_Chip\UForm_BandWidth.cpp", Form_BandWidth);
USEFORM("..\SRC\NT72312_Chip\UForm_ME_1_Chip.cpp", Form_ME_1_Chip);
USEFORM("..\SRC\NT72312_Chip\UForm_Demo_Chip.cpp", Form_Demo_Chip);
USEFORM("..\SRC\NT72312_Chip\UUI312_Chip.cpp", Form_UI312_Chip);
USEFORM("..\..\SHARE\NT72682Updater.cpp", Form_NT72682Updater);
USEFORM("..\..\SHARE\UI2CMap.cpp", I2CMap);
USEFORM("..\..\SHARE\UMEMCForm.cpp", MEMCForm);
USEFORM("..\..\SHARE\UMEMCFrame.cpp", MEMCFrame); /* TFrame: File Type */
USEFORM("..\..\SHARE\spreadSpectrum.cpp", Form_spreadSpectrum);
USEFORM("..\SRC\UMainForm.cpp", MainForm);
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


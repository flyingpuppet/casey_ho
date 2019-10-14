//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spreadSpectrum.h"
//#include "GlobalDef.h"
//#include "Global.h"
//#include "SystemRW.h"
#include <math.h>

#include <mmsystem.h>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_spreadSpectrum *Form_spreadSpectrum;
//extern CSystemRW SystemRW;
AnsiString g_itemString[257]={"empty"};
AnsiString g_itemStringMHz[257]={"empty"};
#define DDR_SSC_HZ_MAX		500000

//---------------------------------------------------------------------------
__fastcall TForm_spreadSpectrum::TForm_spreadSpectrum(TComponent* Owner)
    : TMEMCForm(Owner)
{
	//SystemRW.SystemChangeBaseAdr(SYSTEM_Base);
	f_clock_MHz = 610;//Label_spreadClk->Text.ToDouble();
	f_SSC_Hz = 20000;//LabeledEdit_spreadSSC->Text.ToDouble();

	//f_clock_MHz_LVDS= LabeledEdit_spreadClk_lvds->Text.ToDouble();
	//f_SSC_Hz_LVDS= LabeledEdit_spreadSSC_lvds->Text.ToDouble();
	//b_disSSC = false;

	f_312clock_MHz_LVDS = LabeledEdit_312_clock_lvds->Text.ToDouble();
	f_312SSC_Hz_LVDS = LabeledEdit_312_ssc_lvds->Text.ToDouble();
	f_312clock_MHz = LabeledEdit_312_clock->Text.ToDouble();
	f_312SSC_Hz = LabeledEdit_312_ssc->Text.ToDouble();
	b_312disSSC = false;
    
    combobox_selected=0;
}
//---------------------------------------------------------------------------

void Delay(unsigned int mSec , bool bProcess)
{
        unsigned int StartTime,CheckTime;
        StartTime=timeGetTime();
        do
        {
                CheckTime=timeGetTime();
                if(bProcess)
                        Application->ProcessMessages();
        }
        while ((CheckTime - StartTime) <= mSec) ;
}
//---------------------------------------------------------------------------

void __fastcall TForm_spreadSpectrum::Button_spread_resetClick(TObject *Sender)
{
	TButton *btn = (TButton *)Sender;

	
    if(btn->Name == Button_312_reset_lvds->Name)
	{
		//SetBaseAddress(0xc00d);
        WriteFormatPara(0xC00D4DF6, 1, 1, 0);
        WriteFormatPara(0xC00D4DF6, 1, 1, 1);
        WriteFormatPara(0xC00D4DF6, 1, 1, 0);
		//WriteOneBitValue(0x4d, 0xf6, 1, false);
		//WriteOneBitValue(0x4d, 0xf6, 1, true);
		//WriteOneBitValue(0x4d, 0xf6, 1, false);
	}
	else if(btn->Name == Button_312_reset->Name)
	{
		//SetBaseAddress(0xc00d);
        WriteFormatPara(0xC00D4D86, 1, 1, 0);
        WriteFormatPara(0xC00D4D86, 1, 1, 1);
        WriteFormatPara(0xC00D4D86, 1, 1, 0);
		//WriteOneBitValue(0x4d, 0x86, 1, false);
		//WriteOneBitValue(0x4d, 0x86, 1, true);
		//WriteOneBitValue(0x4d, 0x86, 1, false);
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm_spreadSpectrum::ComboBox_spread_mulfac_lvdsChange(
      TObject *Sender)
{
	TComboBox *cmbBox = (TComboBox *)Sender;


	if(cmbBox->Name == ComboBox_312_mulfac_lvds->Name)
	{
		//SetBaseAddress(0xC00D);

        WriteFormatPara(0xC00D4DF8, 0, 8, (unsigned char)f_312ssc_period_value_LVDS);
        WriteFormatPara(0xC00D4DF7, 0, 8, ComboBox_312_mulfac_lvds->ItemIndex);

		//SystemRW.SystemBYTEWrite(0x4df8, (unsigned char)f_312ssc_period_value_LVDS);
		//SystemRW.SystemBYTEWrite(0x4df7, ComboBox_312_mulfac_lvds->ItemIndex);
	}
	else if(cmbBox->Name == ComboBox_312_mulfac->Name)
	{
		//SetBaseAddress(0xC00D);

        WriteFormatPara(0xC00D4D88, 0, 8, (unsigned char)f_312ssc_period_value);
        WriteFormatPara(0xC00D4D87, 0, 8, ComboBox_312_mulfac->ItemIndex);

		//SystemRW.SystemBYTEWrite(0x4d88, (unsigned char)f_312ssc_period_value);
		//SystemRW.SystemBYTEWrite(0x4d87, ComboBox_312_mulfac->ItemIndex);
	}
	
}
//---------------------------------------------------------------------------


void __fastcall TForm_spreadSpectrum::CheckBox_spread_enableClick(TObject *Sender)
{
	TCheckBox *chkbox = (TCheckBox *)Sender;
	bool checked = false;
	
	checked = chkbox->Checked;
	
    if(chkbox->Name == CheckBox_312_enable_lvds->Name)
	{
        
		//SetBaseAddress(0xc00d);
		
		//WriteOneBitValue(0x4d, 0xf5, 0, checked);
		//WriteOneBitValue(0x4d, 0xf6, 0, checked);
		//WriteOneBitValue(0x4d, 0xf6, 1, true);		//reset
		//WriteOneBitValue(0x4d, 0xf6, 1, false);
		//if(checked)
		 //	SpecificWrite(0x4d, 0xf6, 2, 3, 2);

        WriteFormatPara(0xC00D4DF5, 0, 1, checked?1:0);
        WriteFormatPara(0xC00D4DF6, 0, 1, checked?1:0);
        WriteFormatPara(0xC00D4DF6, 1, 1, 1);
        WriteFormatPara(0xC00D4DF6, 1, 1, 0);
        if(checked)
        {
            WriteFormatPara(0xC00D4DF6, 2, 2, 2);
        }
        
	}
	else if(chkbox->Name == CheckBox_312_enable->Name)
	{
	   //	SetBaseAddress(0xc00d);
		
	   //	WriteOneBitValue(0x4d, 0x85, 0, checked);
	   //	WriteOneBitValue(0x4d, 0x80, 7, checked);
	   //	WriteOneBitValue(0x4d, 0x86, 1, true);		//reset
	   //	WriteOneBitValue(0x4d, 0x86, 1, false);
		//if(checked)
		//	SpecificWrite(0x4d, 0x80, 2, 3, 2);
        WriteFormatPara(0xC00D4D85, 0, 1, checked?1:0);
        WriteFormatPara(0xC00D4D80, 7, 1, checked?1:0);
        WriteFormatPara(0xC00D4D86, 1, 1, 1);
        WriteFormatPara(0xC00D4D86, 1, 1, 0);
        if(checked)
        {
            WriteFormatPara(0xC00D4D80, 2, 2, 2);
        }
	}
	
}
//---------------------------------------------------------------------------

void __fastcall TForm_spreadSpectrum::LabeledEdit_312_clock_lvdsKeyPress(
      TObject *Sender, char &Key)
{
    if(Key == VK_RETURN)
	{
		AnsiString outStr;
		TLabeledEdit *lblEdit = (TLabeledEdit *)Sender;

		if( (lblEdit->Name == LabeledEdit_312_clock_lvds->Name) 
				|| (lblEdit->Name == LabeledEdit_312_ssc_lvds->Name) )
		{
			f_312clock_MHz_LVDS = LabeledEdit_312_clock_lvds->Text.ToDouble();
			f_312SSC_Hz_LVDS = LabeledEdit_312_ssc_lvds->Text.ToDouble();

			ComboBox_312_mulfac_lvds->Items->Clear();
			for(int i=0; i<256; i++)
			{
				u8_312ssc_mulfac_LVDS= i;
				Button_312_calculateClick( (TObject *)Button_312_calculate_lvds);
				outStr = IntToStr(i) + "- SSP(%): " + LabeledEdit_312_SSP_lvds->Text + ", "
						 + LabeledEdit_312_SSPMHz_lvds->Text + " MHz";
				ComboBox_312_mulfac_lvds->Items->Add(outStr);
			}
		}
		else if( (lblEdit->Name == LabeledEdit_312_clock->Name) 
				|| (lblEdit->Name == LabeledEdit_312_ssc->Name) )
		{
			f_312clock_MHz = LabeledEdit_312_clock->Text.ToDouble();
			f_312SSC_Hz = LabeledEdit_312_ssc->Text.ToDouble();

			ComboBox_312_mulfac->Items->Clear();
			for(int i=0; i<256; i++)
			{
				u8_312ssc_mulfac = i;
				Button_312_calculateClick( (TObject *)Button_312_calculate);
				outStr = IntToStr(i) + "- SSP(%): " + LabeledEdit_312_SSP->Text + ", "
						 + LabeledEdit_312_SSPMHz->Text + " MHz";
				ComboBox_312_mulfac->Items->Add(outStr);
			}
		}
		
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm_spreadSpectrum::Button_312_calculateClick(
      TObject *Sender)
{
    TButton *btn = (TButton *)Sender;

	if(btn->Name == Button_312_calculate_lvds->Name)
	{
		f_312ssc_period_value_LVDS = 0.25 * 12 * 1000000 / f_312SSC_Hz_LVDS;
		//SystemRW.SystemBYTEWrite(0x1187, (unsigned char)f_ssc_period_value_LVDS);

		f_312SSP_LVDS = f_312ssc_period_value_LVDS * u8_312ssc_mulfac_LVDS / (1<<18);
		LabeledEdit_312_SSP_lvds->Text = FloatToStrF(f_312SSP_LVDS*100,
														(TFloatFormat)AnsiString::sffFixed, 4, 3);
		LabeledEdit_312_SSPMHz_lvds->Text = FloatToStrF(f_312SSP_LVDS * f_312clock_MHz_LVDS,
														(TFloatFormat)AnsiString::sffFixed, 4, 3);
	}
	else if(btn->Name == Button_312_calculate->Name)
	{
		f_312ssc_period_value = 0.25 * 12 * 1000000 / f_312SSC_Hz;
		//SystemRW.SystemBYTEWrite(0x1187, (unsigned char)f_ssc_period_value_LVDS);

		f_312SSP = f_312ssc_period_value * u8_312ssc_mulfac / (1<<18);
		LabeledEdit_312_SSP->Text = FloatToStrF(f_312SSP*100,
														(TFloatFormat)AnsiString::sffFixed, 4, 3);
		LabeledEdit_312_SSPMHz->Text = FloatToStrF(f_312SSP * f_312clock_MHz,
														(TFloatFormat)AnsiString::sffFixed, 4, 3);
	}
}
//---------------------------------------------------------------------------

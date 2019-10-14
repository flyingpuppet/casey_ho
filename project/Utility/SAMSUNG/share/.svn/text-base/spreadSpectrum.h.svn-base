//---------------------------------------------------------------------------

#ifndef spreadSpectrumH
#define spreadSpectrumH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_spreadSpectrum : public TMEMCForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl_SSC;
    TTabSheet *TabSheet_SSC_312;
    TGroupBox *GroupBox_312SSC_lvds;
    TLabeledEdit *LabeledEdit_312_clock_lvds;
    TComboBox *ComboBox_312_mulfac_lvds;
    TButton *Button_312_calculate_lvds;
    TLabeledEdit *LabeledEdit_312_ssc_lvds;
    TLabeledEdit *LabeledEdit_312_SSP_lvds;
    TLabeledEdit *LabeledEdit_312_SSPMHz_lvds;
    TCheckBox *CheckBox_312_enable_lvds;
    TButton *Button_312_reset_lvds;
    TGroupBox *GroupBox_312_ssc;
    TLabeledEdit *LabeledEdit_312_clock;
    TComboBox *ComboBox_312_mulfac;
    TButton *Button_312_calculate;
    TLabeledEdit *LabeledEdit_312_ssc;
    TLabeledEdit *LabeledEdit_312_SSP;
    TLabeledEdit *LabeledEdit_312_SSPMHz;
    TCheckBox *CheckBox_312_enable;
    TButton *Button_312_reset;
        void __fastcall ComboBox_spread_mulfac_lvdsChange(TObject *Sender);
        void __fastcall Button_spread_resetClick(TObject *Sender);
    void __fastcall CheckBox_spread_enableClick(TObject *Sender);
    void __fastcall LabeledEdit_312_clock_lvdsKeyPress(TObject *Sender,
          char &Key);
    void __fastcall Button_312_calculateClick(TObject *Sender);

private:	// User declarations
	void __fastcall TrackBarMouseDownOrUp(tagMSG &Msg, bool &Handled);
	float f_ssc_period_value;
	float f_clock_MHz;
	float f_SSC_Hz;
	float f_SSP;
	float f_SSP_Hz;
	unsigned char u8_ssc_mulfac;
        int combobox_selected;
        int trackbar_origin;

	float f_ssc_period_value_LVDS;
	float f_clock_MHz_LVDS;
	float f_SSC_Hz_LVDS;
	float f_SSP_LVDS;
	unsigned char u8_ssc_mulfac_LVDS;
	bool b_disSSC;

	float f_312ssc_period_value_LVDS;
	float f_312clock_MHz_LVDS;
	float f_312SSC_Hz_LVDS;
	float f_312SSP_LVDS;
	unsigned char u8_312ssc_mulfac_LVDS;
	bool b_312disSSC;

	float f_312ssc_period_value;
	float f_312clock_MHz;
	float f_312SSC_Hz;
	float f_312SSP;
	float f_312SSP_Hz;
	unsigned char u8_312ssc_mulfac;
	
public:		// User declarations
    __fastcall TForm_spreadSpectrum(TComponent* Owner);
	typedef void __fastcall (__closure *PreCloseCallBack)(AnsiString FormCaption);
    typedef void __fastcall (__closure *ActiveForm)(AnsiString FormCaption);
    PreCloseCallBack PreClose;
    ActiveForm CurForm;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_spreadSpectrum *Form_spreadSpectrum;
//---------------------------------------------------------------------------
#endif

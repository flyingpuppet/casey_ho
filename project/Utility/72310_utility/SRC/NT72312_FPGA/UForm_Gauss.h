//---------------------------------------------------------------------------

#ifndef UForm_GaussH
#define UForm_GaussH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "UMEMCForm.h"

#define     Y_W 8
#define     X_W 16
//---------------------------------------------------------------------------
class TForm_gauss : public TMEMCForm
{
__published:	// IDE-managed Components
    TChart *Chart1;
    TLineSeries *Series1;
    TEdit *Edit1;
    TButton *Button1;
    TEdit *Edit2;
    TLineSeries *Series2;
    TButton *Button2;
    TChart *Chart2;
    TLineSeries *LineSeries1;
    TLineSeries *LineSeries2;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TButton *Button3;
    TButton *Button4;
    TMemo *Memo1;
    TMemo *Memo2;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
    int * coff_y;
    int * coff_x;

    double * coff_x1;
    signed char offset;

public:		// User declarations
    __fastcall TForm_gauss(TComponent* Owner);
    unsigned char m_cNT72310Slave;
    int * __fastcall GetCoff(int W, double sigma, double * data=NULL);
    int __fastcall Round(double x);
    double __fastcall Gauss(double x, double sigma);
    
    /*bool __fastcall WriteByte(unsigned int Address, Byte WriteByte);
    bool __fastcall ReadByte(unsigned int Address, Byte &ReadByte);
    bool __fastcall WriteDWord(unsigned int Address, unsigned int WriteDWord);
    bool __fastcall ReadDWord(unsigned int Address, unsigned int &ReadDWord);

    bool __fastcall NT72310_AHBSetData(unsigned int WriteData);
    bool __fastcall NT72310_AHBGetData(unsigned int &ReadData);
    bool __fastcall NT72310_AHBSelAddr(unsigned int Address);  */
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_gauss *Form_gauss;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------


#ifndef UMEMCFrameH
#define UMEMCFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "I2CDevice.h"
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
#define BIT_0 0x01
#define BIT_1 0x02
#define BIT_2 0x04
#define BIT_3 0x08
#define BIT_4 0x10
#define BIT_5 0x20
#define BIT_6 0x40
#define BIT_7 0x80

#define N_BIT_0 0xFE
#define N_BIT_1 0xFD
#define N_BIT_2 0xFB
#define N_BIT_3 0xF7
#define N_BIT_4 0xEF
#define N_BIT_5 0xDF
#define N_BIT_6 0xBF
#define N_BIT_7 0x7F


class TMEMCFrame : public TFrame
{
__published:	// IDE-managed Components
private:	// User declarations
    static I2CDevice * Dev;
    //TStringGrid * SG_Left;
    //TStringGrid * SG_Right;
    static TStringGrid * SG_Left;
    static TStringGrid * SG_Right;
    static int Block;
public:		// User declarations
    static bool m_bIs8BitFormat;
    static TStringList * RefBuf;
    __fastcall TMEMCFrame(TComponent* Owner);
    void __fastcall SetBlock(int b);
    int __fastcall GetBlock();

    static void __fastcall SetDevice(I2CDevice * oDev);
    static I2CDevice * __fastcall GetDevice();

    virtual void __fastcall LoadMeasurePar(AnsiString * strs);
    
    virtual unsigned int __fastcall MakeAddress(unsigned int b, int p, int r);
    virtual unsigned int __fastcall MakeAddress(AnsiString b, AnsiString p,
        AnsiString r);
    
    virtual void __fastcall FillStringGrid(TStringGrid * sg, TStringList * sl,
        AnsiString block);
    virtual void __fastcall FillStringGrid(TStringGrid * sg, TStringList* sl,
        int block);

    virtual void __fastcall SetLeftGrid(TStringGrid * sg);
    virtual void __fastcall SetRightGrid(TStringGrid * sg);
    virtual TStringGrid * __fastcall GetLeftGrid();
    virtual  TStringGrid * __fastcall GetRightGrid();
    virtual void __fastcall LoadPara(unsigned int * pi);
    virtual void __fastcall LoadFormatPara(unsigned int * pi);
};
//---------------------------------------------------------------------------
extern PACKAGE TMEMCFrame *MEMCFrame;
//---------------------------------------------------------------------------
#endif

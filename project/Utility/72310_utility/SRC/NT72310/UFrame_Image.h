//---------------------------------------------------------------------------

#ifndef UFrame_ImageH
#define UFrame_ImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCFrame.h"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include "RegCheckBox.h"
#include "RegScrollBar.h"
//---------------------------------------------------------------------------
class TFrame_Image : public TMEMCFrame
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    TButton *Button6;
    TLabeledEdit *LE_bWidth;
    TLabeledEdit *LE_bHeight;
    TLabeledEdit *LE_bTop;
    TLabeledEdit *LE_bLeft;
    TSaveDialog *SaveBitmap;
    TRegCheckBox *CheckBox1;
    TRegCheckBox *CheckBox2;
    TRegCheckBox *CheckBox3;
    TRegScrollBar *ScrollBar1;
    TRegScrollBar *ScrollBar2;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TRegScrollBar *ScrollBar3;
    TLabel *Label6;
    TRegScrollBar *ScrollBar4;
    TRegCheckBox *CheckBox4;
    TLabel *Label7;
    TRegScrollBar *ScrollBar5;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TProgressBar *PB;
    TLabeledEdit *LE_width;
    TLabeledEdit *LE_height;
    TLabeledEdit *LE_top;
    TLabeledEdit *LE_left;
    TButton *Button4;
    TGroupBox *GroupBox1;
    TRadioButton *RB_8bit;
    TRadioButton *RB_10bit;
    TGroupBox *GroupBox2;
    TRadioButton *RB_RGB;
    TRadioButton *RB_YCbCr444;
    TRadioButton *RB_YCbCr422;
    TButton *Button5;
    TButton *Button9;
    TCheckBox *CB_Burst;
    TButton *Button1;
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall CheckBox2Click(TObject *Sender);
    void __fastcall CheckBox3Click(TObject *Sender);
    void __fastcall CheckBox4Click(TObject *Sender);
    void __fastcall ScrollBar1Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button9Click(TObject *Sender);
    void __fastcall ScrollBar5Change(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
    bool Is8bit, IsRGB, IsYCbCr422;
    int buf_top, buf_left, buf_width, buf_height;
    WORD ** y_buf;
    WORD ** Cb_buf;
    WORD ** Cr_buf;
    int RowCount;
    void __fastcall MakeBlockImage(int width,int height,Graphics::TBitmap * pBitmap,Byte ** y_buf);
    Byte * __fastcall ReadBlockLine(unsigned int LineStart,int width);

    void __fastcall ReadImageBuf();

    Word * __fastcall ReadLine(unsigned int LineStart);
    void __fastcall Make8BitRGBBitmap(Graphics::TBitmap * pBitmap);
    void __fastcall Make8BitYUVBitmap(Graphics::TBitmap * pBitmap);
    void __fastcall Make8BitYUV422Bitmap(Graphics::TBitmap * pBitmap);
    void __fastcall Make10BitRGBBitmap(Graphics::TBitmap * pBitmap);
    void __fastcall Make10BitYUVBitmap(Graphics::TBitmap * pBitmap);
    void __fastcall Make10BitYUV422Bitmap(Graphics::TBitmap * pBitmap);

    void __fastcall ReadMEYImageBuf();
    void __fastcall MakeMEYBitmap(Graphics::TBitmap * pBitmap);

    Word * __fastcall TransferTo10Bit(Word * LineBuffer);
    Word * __fastcall TransferTo8Bit(Word * LineBuffer, int ByteCount);

    void __fastcall WriteBitmapToDDR(Graphics::TBitmap * pBitmap);
    void __fastcall WriteLine(unsigned int start_add, Word * LineBuffer,Graphics::TBitmap * pBitmap);
public:		// User declarations
    __fastcall TFrame_Image(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_Image *Frame_Image;
//---------------------------------------------------------------------------
#endif

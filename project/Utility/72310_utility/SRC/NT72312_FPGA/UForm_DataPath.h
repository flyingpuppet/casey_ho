//---------------------------------------------------------------------------

#ifndef UForm_DataPathH
#define UForm_DataPathH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ExtCtrls.hpp>
#include "RegLabeledEdit.h"
#include "RegCheckBox.h"
//---------------------------------------------------------------------------
enum InputType{PC, VD};
enum InputFormat{In_2D, In_3D_LR, In_3D_TB, In_3D_SBS};
enum OutputFormat{Out_2D, Out_3D_Passive, Out_3D_Active};
enum InputResolution{Reso_1366, Reso_1920, Reso_1280};
enum InputVSync{In_50Hz, In_60Hz, In_24Hz, In_25Hz, In_48Hz, In_100Hz, In_120Hz, In_30Hz};
enum OutputVSync{Out_50Hz, Out_100Hz, Out_200Hz, Out_60Hz, Out_120Hz, Out_240Hz, Out_75Hz};
enum FilmMode{Film_video, Film_22, Film_32, Film_3223, Film_2224, Film_32322, Film_1123, Film_55, Film_64, Film_87, Film_Local_22, Film_Local_32};
enum InputBits{Bits_888, Bits_101010, Bits_1088};
enum ME_Y_DCMode{ME_Y_0, ME_Y_1, ME_Y_2, ME_Y_3};
enum MC_Y_DCMode{MC_Y_0, MC_Y_1, MC_Y_2, MC_Y_3, MC_Y_4};
enum MC_C_DCMode{MC_C_0, MC_C_1, MC_C_2, MC_C_3, MC_C_4};

struct __S_Data_Lut
{
    unsigned __int64 d0:48;
    unsigned __int64 d1:48;
};
struct __S_Data_Reg
{
    unsigned int reg0;
    unsigned int reg1;
    unsigned int reg2;
    unsigned int reg3;
};
union __Data_UN
{
    __S_Data_Lut data;
    __S_Data_Reg reg;
};

struct __S_Addr_lut
{
    unsigned int d0:16;
    unsigned int d1:16;
};
union __Addr_UN
{
    __S_Addr_lut addr;
    unsigned int reg0;
};

struct __S_ME_Inc_B
{
    Byte d0:4;
    Byte d1:4;
};
struct __S_ME_Inc
{
    __S_ME_Inc_B byte0;
    __S_ME_Inc_B byte1;
    __S_ME_Inc_B byte2;
    __S_ME_Inc_B byte3;
};
union __ME_UN
{
    __S_ME_Inc me_inc;
    unsigned int reg0;
};

struct __S_MC_Inc_B
{
    Byte d0:2;
    Byte d1:2;
    Byte d2:2;
    Byte d3:2;
};
struct __S_MC_Inc
{
    __S_MC_Inc_B byte0;
    __S_MC_Inc_B byte1;
    __S_MC_Inc_B byte2;
    __S_MC_Inc_B byte3;
};
union __MC_UN
{
    __S_MC_Inc mc_inc;
    unsigned int reg0;
};

struct __S_Film_End_b
{
    Byte d0:1;
    Byte d1:1;
    Byte d2:1;
    Byte d3:1;
    Byte d4:1;
    Byte d5:1;
    Byte d6:1;
    Byte d7:1;
};
struct __S_Film_End
{
    __S_Film_End_b byte0;
    __S_Film_End_b byte1;
    __S_Film_End_b byte2;
    __S_Film_End_b byte3;
};
union __Film_UN
{
    __S_Film_End film_end;
    unsigned int reg0;
};

struct __S_Film_Mode
{
    int film;
    char Name[10];
};

struct __S_Phase_Poiter
{
    int lut_offset;
    int ip_offset;
    int film_offset;
    int top44_control;
};

struct __S_In_Out_Pointer
{
    InputVSync in;
    OutputVSync out;
    __S_Phase_Poiter pointer[10]; 
};


class TForm_DataPath : public TMEMCForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TGroupBox *GB_MEY;
    TCheckBox *CB_MeY_DC_Bypass;
    TCheckBox *CB_MeY_LastLine_Bypass;
    TGroupBox *GroupBox6;
    TRadioButton *RB_MeY_DC_mode0;
    TRadioButton *RB_MeY_DC_mode1;
    TRadioButton *RB_MeY_DC_mode2;
    TRadioButton *RB_MeY_DC_mode3;
    TRadioButton *RB_MeY_DC_mode4;
    TCheckBox *CB_MeY_Debug;
    TGroupBox *GroupBox8;
    TRadioButton *RB_MeY_Error_0;
    TRadioButton *RB_MeY_Error_1;
    TRadioButton *RB_MeY_Error_2;
    TRadioButton *RB_MeY_Error_3;
    TGroupBox *GB_TP;
    TRadioButton *RB_MeY_Test_0;
    TRadioButton *RB_MeY_Test_1;
    TRadioButton *RB_MeY_Test_2;
    TRadioButton *RB_MeY_Test_3;
    TGroupBox *GB_MCY;
    TCheckBox *CB_McY_DC_Bypass;
    TCheckBox *CB_McY_LastLine_Bypass;
    TGroupBox *GroupBox4;
    TRadioButton *RB_McY_DC_mode0;
    TRadioButton *RB_McY_DC_mode1;
    TRadioButton *RB_McY_DC_mode2;
    TRadioButton *RB_McY_DC_mode3;
    TGroupBox *GroupBox9;
    TRadioButton *RB_McY_Error_0;
    TRadioButton *RB_McY_Error_1;
    TRadioButton *RB_McY_Error_2;
    TRadioButton *RB_McY_Error_3;
    TGroupBox *GroupBox10;
    TRadioButton *RB_McY_Test_0;
    TRadioButton *RB_McY_Test_1;
    TRadioButton *RB_McY_Test_2;
    TRadioButton *RB_McY_Test_3;
    TCheckBox *CB_McY_Debug;
    TGroupBox *GB_MCC;
    TCheckBox *CB_McC_DC_Bypass;
    TCheckBox *CB_McC_LastLine_Bypass;
    TGroupBox *GroupBox7;
    TRadioButton *RB_McC_DC_mode0;
    TRadioButton *RB_McC_DC_mode1;
    TRadioButton *RB_McC_DC_mode2;
    TRadioButton *RB_McC_DC_mode3;
    TRadioButton *RB_McC_DC_mode4;
    TGroupBox *GroupBox11;
    TRadioButton *RB_McC_Error_0;
    TRadioButton *RB_McC_Error_1;
    TRadioButton *RB_McC_Error_2;
    TRadioButton *RB_McC_Error_3;
    TGroupBox *GroupBox12;
    TRadioButton *RB_McC_Test_0;
    TRadioButton *RB_McC_Test_1;
    TRadioButton *RB_McC_Test_2;
    TRadioButton *RB_McC_Test_3;
    TCheckBox *CB_McC_Debug;
    TGroupBox *GroupBox3;
    TRadioButton *rb_PC;
    TRadioButton *rb_VD;
    TButton *Button11;
    TCheckBox *CB_Half;
    TButton *Button1;
    TGroupBox *GB_InputFormat;
    TRadioButton *rb_In_2D;
    TRadioButton *rb_In_3DTB;
    TRadioButton *rb_In_3DLR;
    TRadioButton *rb_In_3DSBS;
    TGroupBox *GroupBox1;
    TRadioButton *rb_Out_2D;
    TRadioButton *rb_Out_3DPassive;
    TRadioButton *rb_Out_3DActive;
    TGroupBox *GroupBox2;
    TRadioButton *rb_In_50;
    TRadioButton *rb_In_60;
    TGroupBox *GroupBox13;
    TRadioButton *rb_Out_50;
    TRadioButton *rb_Out_100;
    TRadioButton *rb_Out_200;
    TRadioButton *rb_Out_60;
    TRadioButton *rb_Out_120;
    TRadioButton *rb_Out_240;
    TRadioButton *rb_Out_75;
    TRadioButton *rb_In_24;
    TRadioButton *rb_In_25;
    TRadioButton *rb_In_48;
    TGroupBox *GroupBox14;
    TRadioButton *RadioButton20;
    TRadioButton *RadioButton21;
    TGroupBox *GroupBox5;
    TRadioButton *rb_888;
    TRadioButton *rb_101010;
    TRadioButton *rb_1088;
    TGroupBox *GB_ReadBack;
    TRegLabeledEdit *RegLabeledEdit1;
    TRegLabeledEdit *RegLabeledEdit2;
    TRegLabeledEdit *RegLabeledEdit3;
    TRegLabeledEdit *RegLabeledEdit4;
    TRegLabeledEdit *rle_Frame;
    TRegLabeledEdit *rle_N;
    TRegLabeledEdit *rle_M;
    TLabeledEdit *rle_VSync;
    TLabeledEdit *le_Clk;
    TLabeledEdit *rle_ovsync;
    TLabeledEdit *le_FilmMode;
    TGroupBox *GroupBox16;
    TRadioButton *rb_22;
    TRadioButton *rb_32;
    TRadioButton *rb_3223;
    TRadioButton *rb_32322;
    TRadioButton *rb_55;
    TRadioButton *rb_64;
    TRadioButton *rb_87;
    TRadioButton *rb_1123;
    TRadioButton *rb_video;
    TButton *btnLoadTbl;
    TButton *btnSetPtr;
    TRegLabeledEdit *RegLabeledEdit5;
    TRegLabeledEdit *RegLabeledEdit6;
    TRegLabeledEdit *RegLabeledEdit7;
    TRadioButton *rb_2224;
    TRadioButton *RadioButton32;
    TCheckBox *CB_AutoDet;
    TCheckBox *CB_HW;
    TCheckBox *CB_Polling;
    TButton *btn_CreateTable;
    TButton *Button2;
    TCheckBox *CB_MeY_Diagonal;
    TCheckBox *CB_McY_Diagonal;
    TCheckBox *CB_McC_Diagonal;
    TRadioButton *rb_In_100;
    TRadioButton *rb_In_120;
    TRadioButton *RB_McY_DC_mode4;
    TRadioButton *rb_22_local;
    TRadioButton *rb_32_local;
    TRadioButton *rb_In_30;
    TGroupBox *GB_Scalar;
    TRegCheckBox *RegCheckBox1;
    TCheckBox *cb_newtable;
    TRegLabeledEdit *rle_ip2A5;
    TRegLabeledEdit *rle_ip03;
    TCheckBox *cb_logoOn;
    TCheckBox *CB_Samsung;
    TGroupBox *GroupBox15;
    TRegCheckBox *RegCheckBox2;
    TRegCheckBox *RegCheckBox3;
    TRegCheckBox *RegCheckBox4;
    TRegCheckBox *RegCheckBox5;
    TRegCheckBox *RegCheckBox6;
    TRegCheckBox *RegCheckBox7;
    TRegCheckBox *RegCheckBox8;
    TRegCheckBox *RegCheckBox9;
    TRegCheckBox *RegCheckBox10;
    TButton *btnTest;
    void __fastcall rb_PCClick(TObject *Sender);
    void __fastcall RadioButton20Click(TObject *Sender);
    void __fastcall rb_In_2DClick(TObject *Sender);
    void __fastcall rb_Out_3DActiveClick(TObject *Sender);
    void __fastcall RB_MeY_DC_mode0Click(TObject *Sender);
    void __fastcall RB_McY_DC_mode4Click(TObject *Sender);
    void __fastcall RB_McC_DC_mode0Click(TObject *Sender);
    void __fastcall rb_1088Click(TObject *Sender);
    void __fastcall rb_In_50Click(TObject *Sender);
    void __fastcall rb_Out_240Click(TObject *Sender);
    void __fastcall rb_videoClick(TObject *Sender);
    void __fastcall CB_MeY_DC_BypassClick(TObject *Sender);
    void __fastcall btnLoadTblClick(TObject *Sender);
    void __fastcall CB_McY_DC_BypassClick(TObject *Sender);
    void __fastcall CB_McC_DC_BypassClick(TObject *Sender);
    void __fastcall CB_MeY_LastLine_BypassClick(TObject *Sender);
    void __fastcall CB_McY_LastLine_BypassClick(TObject *Sender);
    void __fastcall CB_McC_LastLine_BypassClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall btnSetPtrClick(TObject *Sender);
    void __fastcall btn_CreateTableClick(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall CB_MeY_DiagonalClick(TObject *Sender);
    void __fastcall CB_McY_DiagonalClick(TObject *Sender);
    void __fastcall CB_McC_DiagonalClick(TObject *Sender);
    void __fastcall rle_ip2A5KeyPress(TObject *Sender, char &Key);
    void __fastcall rle_ip03KeyPress(TObject *Sender, char &Key);
    void __fastcall cb_logoOnClick(TObject *Sender);
    void __fastcall CB_SamsungClick(TObject *Sender);
    void __fastcall btnTestClick(TObject *Sender);
private:	// User declarations
    InputType   eInputType;
    InputFormat eInputFormat;
    OutputFormat    eOutputFormat;
    InputResolution eInputResolution;
    InputVSync  eInputVSync;
    OutputVSync eOutputVSync;
    FilmMode    eFilmMode;
    InputBits   eInputBits;
    ME_Y_DCMode eME_Y_DCMode;
    MC_Y_DCMode eMC_Y_DCMode;
    MC_C_DCMode eMC_C_DCMode;

    bool b_ChangedSam;

    int NToM_Input_Index;

    bool ME_Y_DCBypass;
    bool MC_Y_DCBypass;
    bool MC_C_DCBypass;

    bool ME_Y_Lastline;
    bool MC_Y_Lastline;
    bool MC_C_LastLine;

    __Data_UN * data_lut;
    __Addr_UN * addr_lut;
    __ME_UN * me_inc;
    __MC_UN * mc_inc;
    __Film_UN * film_end;

    __S_Phase_Poiter * ph_pointer;

    void __fastcall TrimList(TStringList * sl);

    void __fastcall LoadAddrLut(TStringList * sl);
    void __fastcall LoadDataLut(TStringList * sl);
    void __fastcall LoadMeLut(TStringList * sl);
    void __fastcall LoadMcLut(TStringList * sl);
    void __fastcall LoadFilmLut(TStringList * sl);

    void __fastcall LoadPointer(TStringList * sl);

    void __fastcall LoadN2M(TStringList * sl);

    void __fastcall WriteAddrLut(__Addr_UN * addr, unsigned int start, int count);
    void __fastcall WriteDataLut(__Data_UN * data, unsigned int start, int count);
    void __fastcall WriteMeInc(__ME_UN * me, unsigned int start, int count);
    void __fastcall WriteMcInc(__MC_UN * mc, unsigned int start, int count);
    void __fastcall WriteFilmEnd(__Film_UN * film, unsigned int start, int count);

    void __fastcall SaveAddrLut(__Addr_UN * addr, TStringList * sl, int count);
    void __fastcall SaveDataLut(__Data_UN * data, TStringList * sl, int count);
    void __fastcall SaveMeInc(__ME_UN * me, TStringList * sl, int count);
    void __fastcall SaveMcInc(__MC_UN * mc, TStringList * sl, int count);
    void __fastcall SaveFilmEnd(__Film_UN * film, TStringList * sl, int count);

    void __fastcall WritePointer(__S_Phase_Poiter ptr);

    /*__Addr_UN * __fastcall ReadAddrLut( int count);
    __Data_UN * __fastcall ReadDataLut( int count);
    __ME_UN * __fastcall ReadMeInc( int count);
    __MC_UN * __fastcall ReadMCInc( int count);
    __Film_UN * __fastcall ReadFilmEnd( int count);*/


    void __fastcall SetInputType(InputType in);
    void __fastcall SetInputFormat(InputFormat in);
    void __fastcall SetOutputFormat(OutputFormat out);
    void __fastcall SetInputResolution(InputResolution in);
    void __fastcall SetInputVSync(InputVSync in);
    void __fastcall SetOutputVSync(OutputVSync out);
    void __fastcall SetFilmMode(FilmMode film);
    void __fastcall SetInputBits(InputBits bits);
    void __fastcall SetME_Y_DCMode(ME_Y_DCMode mey);
    void __fastcall SetMC_Y_DCMode(MC_Y_DCMode mcy);
    void __fastcall SetMC_C_DCMode(MC_C_DCMode mcc);
    void __fastcall SetME_Y_Bypass(bool b);
    void __fastcall SetMC_Y_Bypass(bool b);
    void __fastcall SetMC_C_Bypass(bool b);
    void __fastcall SetME_Y_Lastline(bool b);
    void __fastcall SetMC_Y_Lastline(bool b);
    void __fastcall SetMC_C_Lastline(bool b);
    void __fastcall SetME_Y_Diagonal(bool b);
    void __fastcall SetMC_Y_Diagonal(bool b);
    void __fastcall SetMC_C_Diagonal(bool b);

    void __fastcall Set2D3DResoPara(InputFormat in, OutputFormat out, InputResolution re);

    void __fastcall CalVSync();

    void __fastcall VScaler15(bool b);

    /*InputType __fastcall GetInputType();
    InputFormat __fastcall GetInputFormat();
    OutputFormat __fastcall GetOutputFormat();
    InputResolution __fastcall GetInputResolution();
    InputVSync __fastcall GetInputVSync();
    OutputVSync __fastcall GetOutputVSync();
    FilmMode __fastcall GetFilmMode();
    InputBits __fastcall GetInputBits();
    ME_Y_DCMode __fastcall GetME_Y_DCMode();
    MC_Y_DCMode __fastcall GetMC_Y_DCMode();
    MC_C_DCMode __fastcall GetMC_C_DCMode();   */

public:		// User declarations
    __fastcall TForm_DataPath(TComponent* Owner);
};
//---------------------------------------------------------------------------

extern PACKAGE TForm_DataPath *Form_DataPath;
//---------------------------------------------------------------------------
#endif

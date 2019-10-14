//---------------------------------------------------------------------------

#ifndef UFrame_BWMeasure_312FPGAH
#define UFrame_BWMeasure_312FPGAH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UFrame_BWMeasure.h"
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include "UMEMCFrame.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------

class TFrame_BWMeasure_312FPGA : public TMEMCFrame
{
__published:	// IDE-managed Components
    TButton *Button1;
    TMemo *memo_out;
    TButton *Button2;
    TButton *Button3;
    TSaveDialog *SaveDialog1;
    TProgressBar *PB_BW;
    TGroupBox *GB_Mode;
    TGroupBox *GB_IP;
    TRadioButton *RB_IP_0;
    TRadioButton *RB_IP_1;
    TRadioButton *RB_IP_2;
    TRadioButton *RB_IP_3;
    TGroupBox *GP_ME;
    TRadioButton *RB_ME_0;
    TRadioButton *RB_ME_1;
    TRadioButton *RB_ME_2;
    TRadioButton *RB_ME_3;
    TGroupBox *GB_MC;
    TRadioButton *RB_MC_0;
    TRadioButton *RB_MC_1;
    TRadioButton *RB_MC_2;
    TRadioButton *RB_MC_3;
    TRadioButton *RB_all_0;
    TRadioButton *RB_all_1;
    TRadioButton *RB_all_2;
    TRadioButton *RB_all_3;
    TLabel *Lines;
    TComboBox *CB_Lines;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *Ed_Start;
    TEdit *Ed_End;
    TButton *btn_AllBW;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TOpenDialog *OpenDialog1;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TButton *Button4;
    TPanel *CheckPanel;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TCheckBox *CheckBox7;
    TCheckBox *CheckBox8;
    TButton *btnTotal;
    TCheckListBox *clb_Agents;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit5;
    TEdit *Edit6;
    TEdit *Edit7;
    TEdit *Edit8;
    TCheckBox *cb_Band;
    TGroupBox *GroupBox1;
    TBitBtn *BitBtn1;
    TButton *Button5;
    TListBox *MemoAXI;
    TBitBtn *BitBtn2;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall RB_IP_0Click(TObject *Sender);
    void __fastcall RB_ME_0Click(TObject *Sender);
    void __fastcall RB_MC_0Click(TObject *Sender);
    void __fastcall RB_all_0Click(TObject *Sender);
    void __fastcall CB_LinesChange(TObject *Sender);
    void __fastcall Ed_StartChange(TObject *Sender);
    void __fastcall Ed_EndChange(TObject *Sender);
    void __fastcall btn_AllBWClick(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall btnTotalClick(TObject *Sender);
    void __fastcall Edit1Enter(TObject *Sender);
    void __fastcall clb_AgentsClick(TObject *Sender);
    void __fastcall Edit1Exit(TObject *Sender);
    void __fastcall clb_AgentsExit(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);

private:
    int LineCounts;
    int startLine;
    int endLine;
    int IP_Mode;
    int ME_Mode;
    int MC_Mode;
    int Free_Mode;
    double **iBuf;
    //double ** fBuf;
    int bufReadCount;
    int bufCount;
    bool Agents[8][22];
    bool bTotal;
    TStringList * datalist;
    TStringList * AgentList;
    double inLineFreq;
    double outLineFreq;
private:	// User declarations
    void __fastcall IPMeasure();
    void __fastcall MCMeasure();
    void __fastcall MEMeasure();

public:		// User declarations
    __fastcall TFrame_BWMeasure_312FPGA(TComponent* Owner);
    virtual void __fastcall ReadMeasure(int count, int index, int readNum =3);
    virtual int __fastcall GetMCCLK();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame_BWMeasure_312FPGA *Frame_BWMeasure_312FPGA;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef UForm_RimH
#define UForm_RimH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include "RegCheckBox.h"
#include "RegEdit.h"
#include "RegScrollBar.h"
//---------------------------------------------------------------------------
class TForm_Rim : public TMEMCForm
{
__published:	// IDE-managed Components
    TGroupBox *setting_GroupBox;
    TLabel *Label36;
    TLabel *Label37;
    TLabel *Label38;
    TLabel *Label39;
    TLabel *Label40;
    TLabel *Label41;
    TLabel *Label42;
    TLabel *Label43;
    TLabel *Label44;
    TLabel *Label45;
    TRegEdit *Edit49;
    TRegEdit *Edit48;
    TRegEdit *Edit47;
    TRegEdit *Edit50;
    TRegEdit *Edit51;
    TRegEdit *Edit52;
    TRegEdit *Edit53;
    TRegEdit *Edit54;
    TRegEdit *Edit55;
    TButton *Button1;
    TRegEdit *Edit56;
    TGroupBox *posi_cnt_detail_GroupBox;
    TLabel *Label35;
    TLabel *Label34;
    TLabel *Label33;
    TLabel *Label32;
    TLabel *Label31;
    TLabel *Label30;
    TLabel *Label29;
    TLabel *Label28;
    TLabel *Label27;
    TLabel *Label26;
    TLabel *Label25;
    TLabel *Label24;
    TRegEdit *Edit11;
    TRegEdit *Edit46;
    TRegEdit *Edit45;
    TRegEdit *Edit44;
    TRegEdit *Edit43;
    TRegEdit *Edit42;
    TRegEdit *Edit41;
    TRegEdit *Edit40;
    TRegEdit *Edit39;
    TRegEdit *Edit38;
    TRegEdit *Edit37;
    TRegEdit *Edit36;
    TRegEdit *Edit35;
    TRegEdit *Edit34;
    TRegEdit *Edit33;
    TRegEdit *Edit32;
    TRegEdit *Edit31;
    TRegEdit *Edit30;
    TRegEdit *Edit29;
    TRegEdit *Edit28;
    TRegEdit *Edit27;
    TRegEdit *Edit26;
    TRegEdit *Edit25;
    TRegEdit *Edit24;
    TRegEdit *Edit23;
    TRegEdit *Edit22;
    TRegEdit *Edit21;
    TRegEdit *Edit20;
    TRegEdit *Edit19;
    TRegEdit *Edit18;
    TRegEdit *Edit17;
    TRegEdit *Edit16;
    TRegEdit *Edit15;
    TRegEdit *Edit14;
    TRegEdit *Edit13;
    TRegEdit *Edit12;
    TRegCheckBox *Show_rim_detail;
    TGroupBox *OOR_motion;
    TLabel *Label173;
    TLabel *Label174;
    TLabel *Label175;
    TLabel *Label179;
    TLabel *Label180;
    TLabel *Label171;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TRegCheckBox *Show_OOR_info;
    TGroupBox *dyn_dc_GroupBox;
    TLabel *Label113;
    TLabel *Label158;
    TLabel *Label159;
    TLabel *Label160;
    TLabel *Label161;
    TLabel *Label258;
    TLabel *Label277;
    TLabel *Label278;
    TRegCheckBox *Show_rb_APL;
    TGroupBox *GroupBox21;
    TRegCheckBox *Show_rim_transition;
    TRegEdit *RegEdit1;
    TRegEdit *RegEdit2;
    TRegEdit *RegEdit3;
    TRegEdit *RegEdit4;
    TButton *Button2;
    TButton *Button3;
    TButton *Button4;
    TButton *Button5;
    TButton *Button6;
    TGroupBox *GroupBox1;
    TRegCheckBox *force_rim_en;
    TRegCheckBox *Show_Rim_info;
    TRegCheckBox *CheckBox1;
    TLabel *Rim_Le_Cap;
    TLabel *lb_trackLeft;
    TRegScrollBar *Rim_Le_TrackBar;
    TRegScrollBar *Rim_Ri_TrackBar;
    TRegScrollBar *Rim_Up_TrackBar;
    TRegScrollBar *Rim_Dn_TrackBar;
    TLabel *Rim_Dn_Cap;
    TLabel *lb_trackDown;
    TLabel *Rim_Ri_Cap;
    TLabel *lb_trackRight;
    TLabel *lb_trackUp;
    TLabel *Rim_Up_Cap;
    TRegEdit *RegEdit5;
    TRegEdit *RegEdit6;
    TRegEdit *RegEdit7;
    TRegEdit *RegEdit8;
    TRegEdit *RegEdit9;
    TRegEdit *RegEdit10;
    TRegEdit *RegEdit11;
    TRegEdit *RegEdit12;
    TRegEdit *RegEdit13;
    TRegEdit *RegEdit14;
    TRegEdit *RegEdit15;
    TRegEdit *RegEdit16;
    TRegEdit *RegEdit17;
    TRegEdit *RegEdit18;
    TRegEdit *RegEdit19;
    TRegEdit *RegEdit20;
    TRegEdit *RegEdit21;
    TRegEdit *RegEdit22;
    TRegEdit *RegEdit23;
    TRegEdit *RegEdit24;
    TRegEdit *RegEdit25;
    TRegEdit *RegEdit26;
    TRegEdit *RegEdit27;
    TRegEdit *RegEdit28;
    TRegEdit *RegEdit29;
    TRegEdit *RegEdit30;
    TRegEdit *RegEdit31;
    TRegEdit *RegEdit32;
    TRegEdit *RegEdit33;
    TRegEdit *RegEdit34;
    TRegEdit *RegEdit35;
    TRegEdit *RegEdit36;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TButton *Button7;
    TRegCheckBox *RegCheckBox1;
    TRegCheckBox *RegCheckBox2;
    TRegCheckBox *RegCheckBox3;
    TRegCheckBox *RegCheckBox4;
    TRegCheckBox *RegCheckBox5;
    TRegCheckBox *RegCheckBox6;
    TRegCheckBox *RegCheckBox7;
    TRegCheckBox *RegCheckBox8;
    TRegCheckBox *RegCheckBox9;
    TRegCheckBox *RegCheckBox10;
    TRegCheckBox *RegCheckBox11;
    TRegCheckBox *RegCheckBox12;
    TRegCheckBox *RegCheckBox13;
    TRegCheckBox *RegCheckBox14;
    TRegCheckBox *RegCheckBox15;
    TRegCheckBox *RegCheckBox16;
    TRegCheckBox *RegCheckBox17;
    TRegCheckBox *RegCheckBox18;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    void __fastcall force_rim_enClick(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall Edit47Change(TObject *Sender);
    void __fastcall Edit48Change(TObject *Sender);
    void __fastcall Edit49Change(TObject *Sender);
    void __fastcall Edit50Change(TObject *Sender);
    void __fastcall Edit51Change(TObject *Sender);
    void __fastcall Edit52Change(TObject *Sender);
    void __fastcall Edit53Change(TObject *Sender);
    void __fastcall Edit54Change(TObject *Sender);
    void __fastcall Edit55Change(TObject *Sender);
    void __fastcall Edit56Change(TObject *Sender);
    void __fastcall Edit11Change(TObject *Sender);
    void __fastcall apl_StringGridClick(TObject *Sender);
    void __fastcall rim_StringGridClick(TObject *Sender);
    void __fastcall Rim_Up_TrackBarChange(TObject *Sender);
    void __fastcall Rim_Le_TrackBarChange(TObject *Sender);
    void __fastcall Rim_Ri_TrackBarChange(TObject *Sender);
    void __fastcall Rim_Dn_TrackBarChange(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall Edit51KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TForm_Rim(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Rim *Form_Rim;
//---------------------------------------------------------------------------
#endif

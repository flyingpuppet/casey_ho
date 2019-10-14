//---------------------------------------------------------------------------

#ifndef UForm_BandWidthH
#define UForm_BandWidthH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "UMEMCForm.h"
#include "RegEdit.h"
#include "RegScrollBar.h"
#include "RegCheckBox.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_BandWidth : public TMEMCForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label25;
    TRegScrollBar *RegScrollBar1;
    TRegEdit *RegEdit1;
    TRegScrollBar *RegScrollBar2;
    TRegEdit *RegEdit2;
    TRegScrollBar *RegScrollBar3;
    TRegEdit *RegEdit3;
    TRegScrollBar *RegScrollBar4;
    TRegEdit *RegEdit4;
    TRegScrollBar *RegScrollBar5;
    TRegEdit *RegEdit5;
    TRegScrollBar *RegScrollBar6;
    TRegEdit *RegEdit6;
    TRegScrollBar *RegScrollBar7;
    TRegEdit *RegEdit7;
    TRegScrollBar *RegScrollBar8;
    TRegEdit *RegEdit8;
    TRegScrollBar *RegScrollBar9;
    TRegEdit *RegEdit9;
    TRegScrollBar *RegScrollBar10;
    TRegEdit *RegEdit10;
    TRegScrollBar *RegScrollBar11;
    TRegEdit *RegEdit11;
    TRegScrollBar *RegScrollBar12;
    TRegEdit *RegEdit12;
    TRegScrollBar *RegScrollBar13;
    TRegEdit *RegEdit13;
    TRegScrollBar *RegScrollBar14;
    TRegEdit *RegEdit14;
    TRegScrollBar *RegScrollBar15;
    TRegEdit *RegEdit15;
    TRegScrollBar *RegScrollBar16;
    TRegEdit *RegEdit16;
    TRegScrollBar *RegScrollBar17;
    TRegEdit *RegEdit17;
    TRegScrollBar *RegScrollBar18;
    TRegEdit *RegEdit18;
    TRegScrollBar *RegScrollBar19;
    TRegEdit *RegEdit19;
    TRegScrollBar *RegScrollBar20;
    TRegEdit *RegEdit20;
    TRegScrollBar *RegScrollBar21;
    TRegEdit *RegEdit21;
    TRegScrollBar *RegScrollBar22;
    TRegEdit *RegEdit22;
    TRegScrollBar *RegScrollBar23;
    TRegEdit *RegEdit23;
    TRegScrollBar *RegScrollBar24;
    TRegEdit *RegEdit24;
    TRegScrollBar *RegScrollBar25;
    TRegEdit *RegEdit25;
    TRegScrollBar *RegScrollBar26;
    TRegEdit *RegEdit26;
    TRegScrollBar *RegScrollBar27;
    TRegEdit *RegEdit27;
    TRegScrollBar *RegScrollBar28;
    TRegEdit *RegEdit28;
    TRegScrollBar *RegScrollBar29;
    TRegEdit *RegEdit29;
    TRegScrollBar *RegScrollBar30;
    TRegEdit *RegEdit30;
    TRegScrollBar *RegScrollBar31;
    TRegEdit *RegEdit31;
    TRegScrollBar *RegScrollBar32;
    TRegEdit *RegEdit32;
    TRegScrollBar *RegScrollBar33;
    TRegEdit *RegEdit33;
    TRegScrollBar *RegScrollBar34;
    TRegEdit *RegEdit34;
    TRegScrollBar *RegScrollBar35;
    TRegEdit *RegEdit35;
    TRegScrollBar *RegScrollBar36;
    TRegEdit *RegEdit36;
    TRegScrollBar *RegScrollBar37;
    TRegEdit *RegEdit37;
    TRegScrollBar *RegScrollBar38;
    TRegEdit *RegEdit38;
    TRegScrollBar *RegScrollBar39;
    TRegEdit *RegEdit39;
    TRegScrollBar *RegScrollBar40;
    TRegEdit *RegEdit40;
    TRegScrollBar *RegScrollBar41;
    TRegEdit *RegEdit41;
    TRegScrollBar *RegScrollBar42;
    TRegEdit *RegEdit42;
    TRegScrollBar *RegScrollBar43;
    TRegEdit *RegEdit43;
    TRegScrollBar *RegScrollBar44;
    TRegEdit *RegEdit44;
    TLabel *Label26;
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
    TRegCheckBox *RegCheckBox19;
    TRegCheckBox *RegCheckBox20;
    TRegCheckBox *RegCheckBox21;
    TRegCheckBox *RegCheckBox22;
    TRegCheckBox *RegCheckBox23;
    TRegCheckBox *RegCheckBox24;
    TRegCheckBox *RegCheckBox25;
    TRegCheckBox *RegCheckBox26;
    TRegCheckBox *RegCheckBox27;
    TRegCheckBox *RegCheckBox28;
    TRegCheckBox *RegCheckBox29;
    TRegCheckBox *RegCheckBox30;
    TRegCheckBox *RegCheckBox31;
    TRegCheckBox *RegCheckBox32;
    TRegCheckBox *RegCheckBox33;
    TRegCheckBox *RegCheckBox34;
    TRegCheckBox *RegCheckBox35;
    TRegCheckBox *RegCheckBox36;
    TRegCheckBox *RegCheckBox37;
    TRegCheckBox *RegCheckBox38;
    TRegCheckBox *RegCheckBox39;
    TRegCheckBox *RegCheckBox40;
    TRegCheckBox *RegCheckBox41;
    TRegCheckBox *RegCheckBox42;
    TRegCheckBox *RegCheckBox43;
    TRegCheckBox *RegCheckBox44;
    TPanel *Panel1;
    TRegCheckBox *RegCheckBox45;
    TRegCheckBox *RegCheckBox46;
    TRegCheckBox *RegCheckBox47;
    TRegCheckBox *RegCheckBox48;
    TRegCheckBox *RegCheckBox49;
    TRegCheckBox *RegCheckBox50;
    TRegCheckBox *RegCheckBox51;
    TRegCheckBox *RegCheckBox52;
    TRegCheckBox *RegCheckBox53;
    TRegCheckBox *RegCheckBox54;
    TRegCheckBox *RegCheckBox55;
    TRegCheckBox *RegCheckBox56;
    TRegCheckBox *RegCheckBox57;
    TRegCheckBox *RegCheckBox58;
    TRegCheckBox *RegCheckBox1;
    TRegCheckBox *RegCheckBox2;
    TButton *refresh;
    TRegCheckBox *RegCheckBox3;
    TRegScrollBar *RegScrollBar45;
    TRegEdit *RegEdit45;
    TRegScrollBar *RegScrollBar46;
    TRegEdit *RegEdit46;
    TLabel *Label27;
    TLabel *Label28;
    void __fastcall RegScrollBar1Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall RegEdit1KeyPress(TObject *Sender, char &Key);
    void __fastcall RegEdit1Exit(TObject *Sender);
    void __fastcall refreshClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    static AnsiString conres[];
public:		// User declarations
    __fastcall TForm_BandWidth(TComponent* Owner);
    virtual AnsiString __fastcall getEditName(int i);
    virtual AnsiString __fastcall getScrollName(int i);
    virtual int __fastcall getconCount();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_BandWidth *Form_BandWidth;
//---------------------------------------------------------------------------
#endif

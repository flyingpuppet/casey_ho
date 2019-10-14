//---------------------------------------------------------------------------

#ifndef UI2CMapH
#define UI2CMapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "I2C.h"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TI2CMap : public TForm
{
__published:	// IDE-managed Components
    TLabeledEdit *ed_Slave;
    TLabeledEdit *ed_Reg;
    TLabeledEdit *ed_Value;
    TButton *Button1;
    TButton *Button2;
    TStringGrid *sg_Regs;
    TButton *Button3;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall sg_RegsSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall sg_RegsKeyPress(TObject *Sender, char &Key);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall ed_SlaveKeyPress(TObject *Sender, char &Key);
private:	// User declarations
    CI2C * pI2C;
    Byte slaveAddr;
    Byte Reg;
public:		// User declarations
    __fastcall TI2CMap(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TI2CMap *I2CMap;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UI2CMap.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TI2CMap *I2CMap;
//---------------------------------------------------------------------------
__fastcall TI2CMap::TI2CMap(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TI2CMap::FormCreate(TObject *Sender)
{
    Byte val;
    TForm * frm;
    frm = new TForm(Application);

    pI2C = new CI2C;
    slaveAddr = 0x7C;

    if(pI2C->GetUSBStatus())
    {
        pI2C->ChangeConnectSetting(false);
        frm->Free();
    }
    else
    {
        if(pI2C->USBConnect(frm->Handle))
        {
            pI2C->ChangeConnectSetting(false);
            frm->Free();
        }
        else
        {
            pI2C->USBClose();
            frm->Free();
        }
    }

    for(int i=0; i<16; i++)
    {
        sg_Regs->Cells[i+1][0] = IntToHex(i,2);
    }
    for(int i=0; i<16; i++)
    {
        sg_Regs->Cells[0][i+1] = IntToHex(i,2);
    }
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            //Reg = i*16+j;
            //pI2C->I2CRead(slaveAddr, &Reg, &val);
            sg_Regs->Cells[j+1][i+1] = IntToHex(0,2);
        }
    }
    Reg = 0;
    //sg_Regs->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TI2CMap::Button1Click(TObject *Sender)
{
    Byte addr, reg, val;
    addr = ed_Slave->Text.ToInt();
    int count;
    reg = ed_Reg->Text.ToInt();
    val = 0;
    count = 0;
    while(!pI2C->I2CRead(addr, &reg, &val))
    {
        count++;
        if(count > 10)  return;
    }
    ed_Value->Text = "0x"+IntToHex(val,2);
}
//---------------------------------------------------------------------------
void __fastcall TI2CMap::Button2Click(TObject *Sender)
{
    Byte addr, reg, val;
    int count;

    count = 0;
    addr = ed_Slave->Text.ToInt();
    reg = ed_Reg->Text.ToInt();
    val = ed_Value->Text.ToInt();
    while(!pI2C->I2CWrite(addr, &reg, &val))
    {
        count++;
        if(count > 10) return;
    }
}
//---------------------------------------------------------------------------
void __fastcall TI2CMap::sg_RegsSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
    if((ARow!=0) && (ACol !=0))
    {
        Reg = (ARow-1)*16+(ACol-1);
    }
}
//---------------------------------------------------------------------------
void __fastcall TI2CMap::sg_RegsKeyPress(TObject *Sender, char &Key)
{
    int Col,Row,count;
	AnsiString a;
	BYTE data;

    Col = sg_Regs->Col;
	Row = sg_Regs->Row;

	a = sg_Regs->Cells[Col][Row];
    if((Key>='0' && Key<='9')||(Key>='A' && Key<='F'))
    {
        if(a.Length()==2)
                a="";
        a=a+Key;
    }
    else if(Key>='a' && Key<='f')
    {
        if(a.Length()==2)
                a="";
        Key-=0x20;
        a=a+Key;
    }
    sg_Regs->Cells[Col][Row]=a;


    if(sg_Regs->Cells[Col][Row].Length()==2)
    {
        AnsiString DataString;
        DataString = "0x";
        DataString += sg_Regs->Cells[Col][Row];
        data = DataString.ToInt();

        while(!pI2C->I2CWrite(slaveAddr, &Reg, &data))
        {
            count++;
            if(count > 10) return;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TI2CMap::Button3Click(TObject *Sender)
{
    Byte val;
    Byte oldreg;
    oldreg = Reg;
    int count;
    count = 0;
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            val = 0;
            Reg = i*16+j;
            while(!pI2C->I2CRead(slaveAddr, &Reg, &val))
            {
                count++;
                if(count > 10)  return;
            }
            sg_Regs->Cells[j+1][i+1] = IntToHex(val,2);
        }
    }
    Reg = oldreg;
}
//---------------------------------------------------------------------------
void __fastcall TI2CMap::ed_SlaveKeyPress(TObject *Sender, char &Key)
{
    if(Key == 13)
    {
        slaveAddr = ed_Slave->Text.ToInt();
    }
}
//---------------------------------------------------------------------------

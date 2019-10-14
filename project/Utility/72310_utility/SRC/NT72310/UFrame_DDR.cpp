//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFrame_DDR.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UMEMCFrame"
#pragma resource "*.dfm"
TFrame_DDR *Frame_DDR;
//---------------------------------------------------------------------------
__fastcall TFrame_DDR::TFrame_DDR(TComponent* Owner)
    : TMEMCFrame(Owner)
{
    sl_DDR = new TStringList();
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DDR::Stg_DDRKeyPress(TObject *Sender, char &Key)
{
    AnsiString cellStr, baseStr,regStr;
	AnsiString strVal;
    unsigned char bVal;
    unsigned char SubAddress;
    int Col , Row;	
	unsigned int Register;
	unsigned int Address;
	
	unsigned int BaseAddr;
	unsigned char page, regAddr;
	unsigned int Value;

    TStringGrid * stg;
    stg = (TStringGrid *)Sender;
	
	Col = stg->Col;
	Row = stg->Row;

    cellStr = stg->Cells[Col][Row];


    if((Key>='0' && Key<='9')||(Key>='A' && Key<='F'))
    {
        if(cellStr.Length() == 2)
		cellStr="";
        cellStr = cellStr + Key;
    }
    else if(Key>='a' && Key<='f')
    {
        if(cellStr.Length() == 2) 
		cellStr = "";
        Key-=0x20;
        cellStr = cellStr + Key;
    }

	stg->Cells[Col][Row] = cellStr;

    if(stg->Cells[Col][Row].Length()==2)
    {
        baseStr = "0x" + stg->Cells[0][Row];
        regStr = "0x" + stg->Cells[Col][0];
        Address = baseStr.ToInt() + regStr.ToInt();
        Value = StrToInt(strVal);
        Memo1->Lines->Insert(0, "Address: " + IntToHex((int)Address, 2) );
        Memo1->Lines->Insert(0, "value: " + strVal );
        if(!GetDevice()->WriteByte(BaseAddr, Value))
        {
            return;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame_DDR::BtnDDRReadClick(TObject *Sender)
{
    unsigned int Address, Value,BaseAdd;
    unsigned char tmp;
    int length, unit;
    int page, reg;
    int modby4, modby16;
    AnsiString str_base,buf;
    String str;

    str = LE_MemoLength->Text;
    length = str.Length();
    
    switch( str[length])
    {
        case 'K':
        case 'k':
            unit = 1024;
            str = str.SubString(1,(length-1));
            break;
        case 'M':
        case 'm':
            unit = 1048576;
            str = str.SubString(1,(length-1));
            break;
        case 'G':
        case 'g':
            unit = 1073741824;
            str = str.SubString(1,(length-1));
            break;
        default :
            unit = 1;
            break;

    }

 //   page=0;
 //   reg=0;

    str_base = "0x"+LE_StartAdd->Text;

    try
    {
        BaseAdd = str_base.ToInt();
        length = str.ToInt()*unit;
    }
    catch(...)
    {
        return;
    }

    PB->Position = 0;
    PB->Max = length;
    PB->Visible = true;
    sl_DDR->Clear();
    //Memo1->Clear();

    modby16 = BaseAdd % 16;
    modby4 = BaseAdd % 4;


    str = LE_StartAdd->Text;//IntToHex((int)(BaseAdd),8);
    sl_DDR->Add(str);
    Memo1->Lines->Add(str);
    
    str = IntToStr(length);
    sl_DDR->Add(str);
    //Memo1->Lines->Add(str);

    str = "";

    if(modby16 != 0)
    {
        for(int i=0;i<modby16;i++)
        {
            str += "  ";
        }
    }


    for(page=0;(page*256-1)<length;page++)
    {
        for(reg=0;((page*256+reg)<length && reg<256);reg+=4)
        {
            Address = BaseAdd + (page<<8) + reg - modby4;

            GetDevice()->ReadDWord(Address, Value);
            if((page==0)&&(reg==0))
            {
                switch(modby4)
                {
                    case 3:
                        tmp = Value>>24;
                        str += IntToHex(tmp, 2);
                        break;
                    case 2:
                        tmp = (unsigned char)((Value>>16)&0x00ff);
                        str += IntToHex(tmp, 2);

                        tmp = Value>>24;
                        str += IntToHex(tmp, 2);
                        break;
                    case 1:
                        tmp = (unsigned char)((Value>>8)&0x00ff);
                        str += IntToHex(tmp, 2);

                        tmp = (unsigned char)((Value>>16)&0x00ff);
                        str += IntToHex(tmp, 2);

                        tmp = Value>>24;
                        str += IntToHex(tmp, 2);
                        break;
                    case 0:
                        tmp = (unsigned char)(Value&0x00ff);
                        str += IntToHex(tmp, 2);

                        tmp = (unsigned char)((Value>>8)&0x00ff);
                        str += IntToHex(tmp, 2);

                        tmp = (unsigned char)((Value>>16)&0x00ff);
                        str += IntToHex(tmp, 2);

                        tmp = Value>>24;
                        str += IntToHex(tmp, 2);
                        break;
                }
            }
            else
            {
                tmp = (unsigned char)(Value&0x00ff);
                str += IntToHex(tmp, 2);

                tmp = (unsigned char)((Value>>8)&0x00ff);
                str += IntToHex(tmp, 2);

                tmp = (unsigned char)((Value>>16)&0x00ff);
                str += IntToHex(tmp, 2);

                tmp = Value>>24;
                str += IntToHex(tmp, 2);
            }

            if(((Address % 16) == 12))
            {
                str = IntToHex((int)(Address-12),8)+":"+str;
                sl_DDR->Add(str);
                //Memo1->Lines->Add(str);
                str = "";
            }

            PB->Position += 4;
        }
    }
    reg = ((BaseAdd+length) % 16);
    if((str !=""))//&&())
    {
        str = IntToHex((int)(Address-((reg/4)*4)),8)+":"+str.SubString(1,reg*2);
        sl_DDR->Add(str);
        //Memo1->Lines->Add(str);
    }
    else if(reg >= 12)
    {
        str = sl_DDR->Strings[sl_DDR->Count-1];
        sl_DDR->Strings[sl_DDR->Count-1] = str.SubString(1,9+reg*2);
        //Memo1->Lines[sl_DDR->Count-1] = str.SubString(1,9+reg*2);
    }
    FillStgFromStr();    
}
//---------------------------------------------------------------------------
void __fastcall TFrame_DDR::FillStgFromStr()
{
    AnsiString buf;

    buf = "0x"+sl_DDR->Strings[0];


    for(int i=0;i<Stg_DDR->RowCount;i++)
    {
        Stg_DDR->Rows[i]->Clear();
    }
    Stg_DDR->Cells[0][0] = "";
    for(int i=1;i<17;i++)
    {
        Stg_DDR->Cells[i][0] = IntToHex(i-1,2);
    }
    Stg_DDR->ColWidths[0] = 60;
    Stg_DDR->RowCount = sl_DDR->Count-1;
    for(int i=1;i<Stg_DDR->RowCount;i++)
    {
        buf = sl_DDR->Strings[i+1];
        Stg_DDR->Rows[i]->Add(buf.SubString(1,8));
        for(int j=0;j<16;j++)
        {
            Stg_DDR->Rows[i]->Add(buf.SubString(j*2+10,2));
        }
    }    
}

void __fastcall TFrame_DDR::BtnDDRWriteClick(TObject *Sender)
{
    unsigned int Value, Address, StartAdd, EndAdd;
    int length, startbytes, endbytes;
    AnsiString str_StartAdd, str_V, buf;

    if(sl_DDR->Count<0) return;

    str_StartAdd = "0x"+sl_DDR->Strings[0];
    Address = str_StartAdd.ToInt();
    length = sl_DDR->Strings[1].ToInt();

    

    StartAdd = (unsigned int)(Address - (Address % 4));
    startbytes = 4 - Address % 4;

    EndAdd = (unsigned int)(Address + length - ((Address+length) % 4));
    endbytes = (Address+length) % 4;


    Address = (unsigned int)(Address-(Address%16));

    PB->Position = 0;
    PB->Max = length;
    PB->Visible = true;

    //Memo1->Clear();
    //Memo1->Lines->Add(IntToHex((int)StartAdd,8)+"   "+IntToStr(startbytes));
    //Memo1->Lines->Add(IntToHex((int)EndAdd,8)+"   "+IntToStr(endbytes));

    
    for(int i=0;i<sl_DDR->Count-2;i++)
    {
        for(int j=0;j<16;j+=4)
        {
            buf = sl_DDR->Strings[i+2];
            Value = 0;
            if((i==0) &&(j < (int)StartAdd%16))
            {
                Address += 4;
                continue;
            }
            else if((i==0)&&(j==(int)StartAdd%16))
            {
                GetDevice()->ReadDWord(Address, Value);
                //Value = 0xFFFFFFFF;
                Value = (Value <<(startbytes)*8)>>((startbytes)*8);

            }
            else if((i==sl_DDR->Count-3) && (j==(int)EndAdd%16))
            {
                GetDevice()->ReadDWord(Address, Value);
                //Value = 0xFFFFFFFF;
                Value = (Value >>(endbytes)*8)<<((endbytes)*8);
            }
            
            str_V = buf.SubString(j*2+10,2);
            if(Trim(str_V)=="")
            {
                str_V = "00";
            }
            
            str_V = buf.SubString(j*2+12,2)+str_V;
            if(Trim(str_V)=="00")
            {
                str_V = "0000";
            }

            str_V = buf.SubString(j*2+14,2)+str_V;
            if(Trim(str_V)=="0000")
            {
                str_V = "000000";
            }

            str_V = buf.SubString(j*2+16,2)+str_V;
            if(Trim(str_V)=="000000")
            {
                str_V = "00000000";
            }
            
            str_V = TrimLeft(str_V);
            
            str_V = "0x"+str_V;

            Value += str_V.ToInt();

            
            GetDevice()->WriteDWord(Address, Value);

            //Memo1->Lines->Add(IntToHex((int)Address,8)+"   "+IntToHex((int)Value,8));
            PB->Position += 4;

            Address += 4;
        }
        
    }    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_DDR::BtnDDRLoadClick(TObject *Sender)
{
    OpenDialog->Filter = "DDR Files|*.DDR|All|*.*";
    sl_DDR->Clear();
    //Memo1->Clear();
    if(OpenDialog->Execute())
    {
        sl_DDR->LoadFromFile(OpenDialog->FileName);
        //Memo1->Lines->LoadFromFile(OpenDialog->FileName);
        if(sl_DDR->Count<0) return;

        LE_StartAdd->Text = sl_DDR->Strings[0];
        LE_MemoLength->Text = sl_DDR->Strings[1];

        FillStgFromStr();
    }    
}
//---------------------------------------------------------------------------

void __fastcall TFrame_DDR::BtnDDRSaveClick(TObject *Sender)
{
    SaveDialog->DefaultExt = "*.DDR";
    SaveDialog->Filter = "DDR Files|*.DDR|All|*.*";
    SaveDialog->FileName = "DDR_"+LE_StartAdd->Text+"_"+LE_MemoLength->Text;
    if(SaveDialog->Execute())
    {
        sl_DDR->SaveToFile(SaveDialog->FileName);
        //Memo1->Lines->SaveToFile(SaveDialog->FileName+"_MEMO");
    }    
}
//---------------------------------------------------------------------------


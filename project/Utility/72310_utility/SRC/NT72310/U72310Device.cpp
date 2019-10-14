//---------------------------------------------------------------------------


#pragma hdrstop

#include "U72310Device.h"
#include "I2CDevice.h"
#include ".\72310_reg_map\frc_reg.map"
#include ".\72310_reg_map\ip_reg.map"
#include ".\72310_reg_map\ip2_reg.map"
#include ".\72310_reg_map\me1_reg.map"
#include ".\72310_reg_map\me2_reg.map"
#include ".\72310_reg_map\me3_reg.map"
#include ".\72310_reg_map\mmu_reg.map"
#include ".\72310_reg_map\logo_reg.map"
#include ".\72310_reg_map\bist_reg.map"
#include ".\72310_reg_map\soft_reg.map"
#include ".\72310_reg_map\film_reg.map"
#include ".\72310_reg_map\dec_reg.map"
#include ".\72310_reg_map\mc_reg.map"
#include ".\72310_reg_map\halo_reg.map"
#include ".\72310_reg_map\P06_reg.map"

//---------------------------------------------------------------------------

#pragma package(smart_init)

unsigned char * regmap_310[] =
{
    frc_reg,
    ip_reg,
    mc_reg,
    dec_reg,
    film_reg,
    halo_reg,
    P06_reg,
    P06_reg,
    me1_reg,
    me2_reg,
    me3_reg,
    mmu_reg,
    logo_reg,
    ip2_reg,
    bist_reg,
    soft_reg,
};

Dev_72310::Dev_72310(AnsiString str):I2CDevice(str)
{
    this->SetRegMap(regmap_310);
}
//---------------------------------------------------------------------------
//in BCB unsigned int is 32bit, 
//DWord is also 32bit, but DWord == unsigned long, type is not match
bool Dev_72310::ReadDWord(unsigned int Address, unsigned int &ReadDWord)
{
	return GetProtocol()->ReadDWord(Address, ReadDWord);
}
//---------------------------------------------------------------------------
bool Dev_72310::WriteDWord(unsigned int Address, unsigned int WriteDWord)
{
	return GetProtocol()->WriteDWord(Address, WriteDWord);
}
//---------------------------------------------------------------------------
/*bool Dev_72310::ReadWord(unsigned int Address, Word * ReadWord)
{
	if(!IICSelAddr(Address))
	{
		return false;
	}
	if(!AHBGetData(ReadWord) )
	{
		return false;
	}
    return true;
}
//---------------------------------------------------------------------------
bool Dev_72310::WriteWord(unsigned int Address, Word WriteWord)
{
	if(IICSelAddr(Address))
	{
		return false;
	}
	if(AHBSetData(WriteWord))
	{
		return false;
	}
    return true;
}*/
//---------------------------------------------------------------------------
bool Dev_72310::ReadByte(unsigned int Address, Byte &ReadByte)
{
	return GetProtocol()->ReadByte(Address, ReadByte);	
}
//---------------------------------------------------------------------------
bool Dev_72310::WriteByte(unsigned int Address, Byte WriteByte)
{
	return GetProtocol()->WriteByte(Address, WriteByte);	
}
//---------------------------------------------------------------------------
bool Dev_72310::ReadDWord(unsigned int &ReadDWord)
{
    unsigned int    Address;

    Address = (unsigned int)((Base<<16) | (Page<<8) | Register);

    return this->ReadDWord(Address,ReadDWord);
}
//---------------------------------------------------------------------------
bool Dev_72310::WriteDWord(unsigned int WriteDWord)
{
    unsigned int    Address;

    Address = (unsigned int)((Base<<16) | (Page<<8) | Register);

    return this->WriteDWord(Address, WriteDWord);
}
//---------------------------------------------------------------------------
bool Dev_72310::ReadByte(Byte &ReadByte)
{
	unsigned int Address;

    Address = (unsigned int)((Base<<16) | (Page<<8) | Register);

    return this->ReadByte(Address, ReadByte);
}
//---------------------------------------------------------------------------
bool Dev_72310::WriteByte(Byte WriteByte)
{
    unsigned int Address;

    Address = (unsigned int)((Base<<16) | (Page<<8) | Register);

    return this->WriteByte(Address, WriteByte);
}
//---------------------------------------------------------------------------
bool Dev_72310::Start()
{
    unsigned char SubAddress;
	unsigned char Data;

	SubAddress = 0xFE;

	Data = (GetIICIndex() == 0) ? 0x31:0x68;
	if(GetProtocol()->IIC_WriteByte(SubAddress , Data) == false)
	{
		return false;
	}

    SubAddress = 0xFF;
	Data = 0x72;
	if(GetProtocol()->IIC_WriteByte(SubAddress , Data) == false)
	{
		return false;
	}
    return true;
}
//---------------------------------------------------------------------------
void Dev_72310::SetBase(unsigned int b)
{
    Base = b;
}
//---------------------------------------------------------------------------
void Dev_72310::SetBase(AnsiString sb)
{
    Base = (unsigned int)sb.ToInt();
}
//---------------------------------------------------------------------------
unsigned int Dev_72310::GetBase()
{
    return Base;
}
//---------------------------------------------------------------------------
void Dev_72310::SetPage(int p)
{
    Page = p;
}
//---------------------------------------------------------------------------
void Dev_72310::SetPage(AnsiString sp)
{
    Page = (int)sp.ToInt();
}
//---------------------------------------------------------------------------
int Dev_72310::GetPage()
{
    return Page;
}
//---------------------------------------------------------------------------
int Dev_72310::GetPageNumber()
{
    return 16;
}
int Dev_72310::GetBoardNumber()
{
    return  1;
}
void Dev_72310::SetRegister(int reg)
{
    Register = reg;
}
//---------------------------------------------------------------------------
void Dev_72310::SetRegister(AnsiString sr)
{
    Register = (int)sr.ToInt();
}

//---------------------------------------------------------------------------
int Dev_72310::GetRegister()
{
    return Register;
}
//---------------------------------------------------------------------------
void Dev_72310::SetAddress(unsigned int b, int p, int r)
{
    SetBase(b);
    SetPage(p);
    SetRegister(r);
}
//---------------------------------------------------------------------------
void Dev_72310::SetAddress(AnsiString sb, AnsiString sp, AnsiString sr)
{
    SetBase(sb);
    SetPage(sp);
    SetRegister(sr);
}
//---------------------------------------------------------------------------
void Dev_72310::SetBurstMode(bool b)
{
    BurstMode = b;
}
//---------------------------------------------------------------------------
bool Dev_72310::GetButstMode()
{
    return BurstMode;
}
//---------------------------------------------------------------------------
bool Dev_72310::BurstReadByte(unsigned int startAddr, int byteCount,
    Byte * LineBuffer, int  *Count)
{
	return GetProtocol()->BurstReadByte(startAddr, byteCount, LineBuffer, Count);
}
//---------------------------------------------------------------------------
/*bool BurstReadDWord(unsigned int startAddr, int intCountt,
            unsigned int * LineBuffer)
{
} */
//---------------------------------------------------------------------------
bool Dev_72310::BurstWriteByte(unsigned int startAddr, int byteCount,
    Byte * LineBuffer, int *Count)
{
	return GetProtocol()->BurstWriteByte(startAddr, byteCount, LineBuffer, Count);
}
//---------------------------------------------------------------------------
bool Dev_72310::BurstReadByte(int byteCount, Byte * LineBuffer, int *Count)
{
    unsigned int  Address;

    Address = (unsigned int)((Base<<16) | (Page<<8) | Register);

    return this->BurstReadByte(Address, byteCount, LineBuffer, Count);
}
//---------------------------------------------------------------------------
bool Dev_72310::BurstWriteByte(int byteCount, Byte * LineBuffer, int  *Count)
{
    unsigned int    Address;
    
    Address = (unsigned int)((Base<<16) | (Page<<8) | Register);

    return this->BurstWriteByte(Address, byteCount, LineBuffer, Count);
}
//---------------------------------------------------------------------------
void Dev_72310::SetBoard(int b)
{
}
//---------------------------------------------------------------------------
void Dev_72310::SetBoard(AnsiString sb)
{
}
//---------------------------------------------------------------------------
int Dev_72310::GetBoard()
{
    return 0;
}
//---------------------------------------------------------------------------
bool Dev_72310::AllWriteByte(unsigned int Address, Byte WriteByte)
{
    return this->WriteByte(Address, WriteByte);
}
//---------------------------------------------------------------------------
bool Dev_72310::AllReadByte(unsigned int Address, Byte &ReadByte)
{
    return this->ReadByte(Address, ReadByte);
}
//---------------------------------------------------------------------------
bool Dev_72310::AllWriteDWord(unsigned int Address, unsigned int WriteDWord)
{
    return this->WriteDWord(Address, WriteDWord);
}
//---------------------------------------------------------------------------
bool Dev_72310::AllReadDWord(unsigned int Address, unsigned int &ReadDWord)
{
    return this->ReadDWord(Address, ReadDWord);
}
//---------------------------------------------------------------------------
bool Dev_72310::GetPageExist(int b, int p)
{
    return true;
}
//---------------------------------------------------------------------------
void Dev_72310::ChangePageList(int i)
{
}
//---------------------------------------------------------------------------
void Dev_72310::ChangePageList(int * PL)
{
}
//---------------------------------------------------------------------------
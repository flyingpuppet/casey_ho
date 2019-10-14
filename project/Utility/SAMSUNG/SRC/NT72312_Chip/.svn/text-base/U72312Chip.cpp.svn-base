//---------------------------------------------------------------------------


#pragma hdrstop

#include "U72312Chip.h"
//#include ".\72312_reg_map\U72312map.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


/*unsigned char * Dev_72312_Chip::regmap_312[] =
{
    map312::frc_reg,
    map312::ip_reg,
    map312::mc_reg,
    map312::dec0_reg,
    map312::film_reg,
    map312::dehalo_reg,
    map312::logo2_reg,
    map312::me4_reg,
    map312::me1_reg,
    map312::me2_reg,
    map312::me3_reg,
    map312::mmu_reg,
    map312::logo1_reg,
    map312::ip2_reg,
    map312::bist_reg,
    map312::soft_reg,
    map312::frc2_reg,
    map312::dgen1_reg,
    map312::dgen2_reg,
    map312::post3d_reg,
    map312::dec1_reg,
    map312::dec2_reg,
    map312::dec3_reg,
    map312::dec4_reg,
    map312::dec5_reg,
    map312::dec6_reg,
    map312::dec7_reg,
    map312::dec8_reg,
    map312::rim_reg,
    map312::rim_reg,
    map312::P6_reg,
    map312::P6_reg,
};      */

//---------------------------------------------------------------------------
Dev_72312_Chip::Dev_72312_Chip(AnsiString str):Dev_72310(str)
{
    //this->SetRegMap(regmap_312);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void Dev_72312_Chip::SetBoard(int b)
{
}
//---------------------------------------------------------------------------
void Dev_72312_Chip::SetBoard(AnsiString sb)
{
}
//---------------------------------------------------------------------------
int Dev_72312_Chip::GetBoard()
{
    return 0;
}
//---------------------------------------------------------------------------
int Dev_72312_Chip::GetPageNumber()
{
    return 32;
}
//---------------------------------------------------------------------------
int Dev_72312_Chip::GetBoardNumber()
{
    return 1;
}
//---------------------------------------------------------------------------
bool Dev_72312_Chip::Start()
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
bool Dev_72312_Chip::AllWriteByte(unsigned int Address, Byte WriteByte)
{
    return this->WriteByte(Address, WriteByte);
}
//---------------------------------------------------------------------------
bool Dev_72312_Chip::AllReadByte(unsigned int Address, Byte &ReadByte)
{
    return this->ReadByte(Address, ReadByte);
}
//---------------------------------------------------------------------------
bool Dev_72312_Chip::AllWriteDWord(unsigned int Address, unsigned int WriteDWord)
{
    return this->WriteDWord(Address, WriteDWord);
}
//---------------------------------------------------------------------------
bool Dev_72312_Chip::AllReadDWord(unsigned int Address, unsigned int &ReadDWord)
{
    return this->ReadDWord(Address, ReadDWord);
}
//---------------------------------------------------------------------------
bool Dev_72312_Chip::GetPageExist(int b, int p)
{
    return true;
}
//---------------------------------------------------------------------------
void Dev_72312_Chip::ChangePageList(int i)
{
}
//---------------------------------------------------------------------------
void Dev_72312_Chip::ChangePageList(int * PL)
{
}
//---------------------------------------------------------------------------
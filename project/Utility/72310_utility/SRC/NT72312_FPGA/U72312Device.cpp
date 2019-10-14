//---------------------------------------------------------------------------


#pragma hdrstop

#include "U72312Device.h"   
#include ".\72312_reg_map\U72312map.h"
/*#include ".\72312_reg_map\frc_reg.map"
#include ".\72312_reg_map\frc2_reg.map"
#include ".\72312_reg_map\ip_reg.map"
#include ".\72312_reg_map\ip2_reg.map"
#include ".\72312_reg_map\me1_reg.map"
#include ".\72312_reg_map\me2_reg.map"
#include ".\72312_reg_map\me3_reg.map"
#include ".\72312_reg_map\me4_reg.map"
#include ".\72312_reg_map\mmu_reg.map"
#include ".\72312_reg_map\logo1_reg.map"
#include ".\72312_reg_map\logo2_reg.map"
#include ".\72312_reg_map\bist_reg.map"
#include ".\72312_reg_map\soft_reg.map"
#include ".\72312_reg_map\film_reg.map"
#include ".\72312_reg_map\dec0_reg.map"
#include ".\72312_reg_map\dec1_reg.map"
#include ".\72312_reg_map\dec2_reg.map"
#include ".\72312_reg_map\dec3_reg.map"
#include ".\72312_reg_map\dec4_reg.map"
#include ".\72312_reg_map\dec5_reg.map"
#include ".\72312_reg_map\dec6_reg.map"
#include ".\72312_reg_map\dec7_reg.map"
#include ".\72312_reg_map\dec8_reg.map"
#include ".\72312_reg_map\mc_reg.map"
#include ".\72312_reg_map\dehalo_reg.map"
#include ".\72312_reg_map\P6_reg.map"
#include ".\72312_reg_map\dgen1_reg.map"
#include ".\72312_reg_map\dgen2_reg.map"
#include ".\72312_reg_map\rim_reg.map"
#include ".\72312_reg_map\post3d_reg.map" */

//---------------------------------------------------------------------------

int __PageList[] =
{
   //0 1 2 3 4 5 6 7 8 9 a b c d e f 0 1 2 3 4 5 6 7 8 9 a b c d e f
    1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,
}; 

int __PageList_All[] =
{
   //0 1 2 3 4 5 6 7 8 9 a b c d e f 0 1 2 3 4 5 6 7 8 9 a b c d e f
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

unsigned char * Dev_72312_FPGA::regmap_312[] =
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
};


#pragma package(smart_init)
//---------------------------------------------------------------------------
Dev_72312_FPGA::Dev_72312_FPGA(AnsiString str):Dev_72310(str)
{
    Board = Board_ALL;
    PageList = __PageList;
    this->SetRegMap(regmap_312);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void Dev_72312_FPGA::SetBoard(int b)
{
    int p;
    Board = (boards)b;
    p = GetPage() & 0x3F;
    p = (b<<6)|p;
    SetPage(p);
}
//---------------------------------------------------------------------------
void Dev_72312_FPGA::SetBoard(AnsiString sb)
{
    int b;
    b = sb.ToInt();
    SetBoard(b);
}
//---------------------------------------------------------------------------
int Dev_72312_FPGA::GetBoard()
{
    return Board;
}
//---------------------------------------------------------------------------
int Dev_72312_FPGA::GetPageNumber()
{
    return 32;
}
//---------------------------------------------------------------------------
int Dev_72312_FPGA::GetBoardNumber()
{
    return 3;
}
//---------------------------------------------------------------------------
bool Dev_72312_FPGA::Start()
{
    return true;
}
//---------------------------------------------------------------------------
bool Dev_72312_FPGA::AllWriteByte(unsigned int Address, Byte WriteByte)
{
    unsigned int Addr;
    int p;

    p = (Address & 0x00003F00)>>8;
    for(int i=0;i<Board_ALL;i++)
    {
        if(!GetPageExist(i,p))
        {
            continue;
        }
        Addr = Address & 0xFFFF3FFF;
        Addr |= (i<<14);
        if(!this->WriteByte(Addr, WriteByte))
        {
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool Dev_72312_FPGA::AllReadByte(unsigned int Address, Byte &ReadByte)
{
    Byte val;
    unsigned int Addr;
    int p;

    p = (Address & 0x00003F00)>>8;
    
    ReadByte = 0;

    for(int i=0;i<Board_ALL;i++)
    {
        if(!GetPageExist(i,p))
        {
            continue;
        }
        Addr = Address & 0xFFFF3FFF;
        Addr |= (i<<14);

        if(!this->ReadByte(Addr, val))
        {
            return false;  
        }
        ReadByte |= val;
    }
    return true;
}
//---------------------------------------------------------------------------
bool Dev_72312_FPGA::AllWriteDWord(unsigned int Address, unsigned int WriteDWord)
{
    unsigned int Addr;
    int p;

    p = (Address & 0x00003F00)>>8;
    for(int i=0;i<Board_ALL;i++)
    {
        if(!GetPageExist(i,p))
        {
            continue;
        }
        Addr = Address & 0xFFFF3FFF;
        Addr |= (i<<14);
        if(!this->WriteDWord(Addr, WriteDWord))
        {
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool Dev_72312_FPGA::AllReadDWord(unsigned int Address, unsigned int &ReadDWord)
{
    unsigned int val, Addr;
    int p;

    p = (Address & 0x00003F00)>>8;
    ReadDWord = 0;

    for(int i=0;i<Board_ALL;i++)
    {
        if(!GetPageExist(i,p))
        {
            continue;
        }
        Addr = Address & 0xFFFF3FFF;
        Addr |= (i<<14);
        if(!this->ReadDWord(Addr, val))
        {
            return false;
        }
        ReadDWord |= val;
    }
    return true;
}
//---------------------------------------------------------------------------
bool Dev_72312_FPGA::GetPageExist(int b, int p)
{
    if(PageList[32*b+p] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//---------------------------------------------------------------------------
void Dev_72312_FPGA::ChangePageList(int i)
{
    if(i==0)
    {
        PageList =  __PageList;
    }
    else
    {
        PageList = __PageList_All;
    }
}
//---------------------------------------------------------------------------
void Dev_72312_FPGA::ChangePageList(int * PL)
{
    PageList = PL;
}
//---------------------------------------------------------------------------

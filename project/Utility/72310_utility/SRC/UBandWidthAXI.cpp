//---------------------------------------------------------------------------


#pragma hdrstop

#include "UBandWidthAXI.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
unsigned int BandWidthAXI::BaseAddress = 0xC00C0000;
I2CDevice * BandWidthAXI::Device = NULL;
int BandWidthAXI::Agents[23]={-1};
//---------------------------------------------------------------------------
void __fastcall BandWidthAXI::SetDevice(I2CDevice * dev)
{
    Device = dev;
}
//---------------------------------------------------------------------------
__fastcall BandWidthAXI::BandWidthAXI()
{

}
//---------------------------------------------------------------------------
__fastcall BandWidthAXI::BandWidthAXI(I2CDevice * dev)
{
    Device = dev;
}
//---------------------------------------------------------------------------
__fastcall BandWidthAXI::~BandWidthAXI()
{
}
//---------------------------------------------------------------------------
void __fastcall BandWidthAXI::getAgentMap()
{
    unsigned int maps[5];
    unsigned int val;
    Device->ReadDWord(BaseAddress+0x50, val);
    val &= 0x7FFFFFFF;
    val |= 0x80000000;
    Device->WriteDWord(BaseAddress+0x50, val);
    for(int i=0;i<5;i++)
    {
        Device->ReadDWord(BaseAddress+0x58+i*4, maps[i]);
        for(int j=0;j<5;j++)
        {
            Agents[i*5+j] = (maps[i]>>(j*6))&0x1F;
        }
    }
}
//---------------------------------------------------------------------------
int __fastcall BandWidthAXI::getAgentID(int index)
{
    return Agents[index];
}
//---------------------------------------------------------------------------
int __fastcall BandWidthAXI::getAgentIndex(int agent)
{
    int i;
    for(i=0;i<23;i++)
    {
        if(Agents[i] == agent)
        {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall BandWidthAXI::getCounterID(int agent)
{
    return getAgentIndex(agent);
}
//---------------------------------------------------------------------------
void __fastcall BandWidthAXI::setStartAndEnd(int start, int end)
{
    unsigned int val;
    Device->ReadDWord(BaseAddress+0x50, val);

    val &= 0xC800F800;
    val |= (end<<16)|start;

    Device->WriteDWord(BaseAddress+0x50, val);
}
//---------------------------------------------------------------------------
void __fastcall BandWidthAXI::SwitchCounter(int index)
{
    unsigned int val;
    Device->ReadDWord(BaseAddress+0x54, val);

    val &= 0xFFFFC0FF;
    val |= (index << 8) ;

    Device->WriteDWord(BaseAddress+0x54, val);
}
//---------------------------------------------------------------------------
unsigned int __fastcall BandWidthAXI::ReadCounter()
{
    unsigned int val;
    Device->ReadDWord(BaseAddress+0x6C, val);
    return val;
}
//---------------------------------------------------------------------------
unsigned int __fastcall BandWidthAXI::ReadCounter(int index)
{
    SwitchCounter(index);
    return ReadCounter();    
}
//---------------------------------------------------------------------------
void __fastcall BandWidthAXI::PauseCounter(bool bPause)
{
    unsigned int val;
    Device->ReadDWord(BaseAddress+0x54, val);

    val &= 0xFFFFFFFE;
    if(bPause)
    {
        val |= 0x00000001;
    }
    Device->WriteDWord(BaseAddress+0x54, val);
}
//---------------------------------------------------------------------------

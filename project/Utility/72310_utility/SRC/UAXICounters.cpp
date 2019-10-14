//---------------------------------------------------------------------------


#pragma hdrstop

#include "UAXICounters.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall AXICounters::AXICounters(int ctn, int * IDs) : count(ctn)
{
    CounterIDs = (int *)malloc(ctn*sizeof(int));
    CounterValue = (unsigned int *)malloc(ctn*sizeof(unsigned int));
    for(int i=0;i<ctn;i++)
    {
        CounterIDs[i] = IDs[i];
    }
    bCanCalculate = true;
}
//---------------------------------------------------------------------------
__fastcall AXICounters::AXICounters(int ctn) : count(ctn)
{
    CounterIDs = (int *)malloc(ctn*sizeof(int));
    CounterValue = (unsigned int *)malloc(ctn*sizeof(unsigned int));
    bCanCalculate = false;
}
//---------------------------------------------------------------------------
__fastcall AXICounters::~AXICounters()
{
}
//---------------------------------------------------------------------------
void __fastcall AXICounters::SetCounterID(int index, int ID)
{
    CounterIDs[index] = ID;
}
//---------------------------------------------------------------------------
void __fastcall AXICounters::CanCalculate(bool bCan)
{
    bCanCalculate = bCan;
}
//---------------------------------------------------------------------------
void __fastcall AXICounters::ReadCounters()
{
    //BandWidthAXI::PauseCounter(false);
    //Sleep(20);
    //BandWidthAXI::PauseCounter(true);

    for(int i=0; i<count; i++)
    {
        CounterValue[i] = BandWidthAXI::ReadCounter(CounterIDs[i]);
    }
}
//---------------------------------------------------------------------------
int __fastcall AXICounters::getCounterValue()
{
    int reval;
    reval = 0;
    ReadCounters();
    for(int i=0; i<count; i++)
    {
        reval += CounterValue[i];
    }
    return reval;
}
//---------------------------------------------------------------------------

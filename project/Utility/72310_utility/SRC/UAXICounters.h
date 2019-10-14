//---------------------------------------------------------------------------

#ifndef UAXICountersH
#define UAXICountersH
//---------------------------------------------------------------------------

#include "UBandWidthAXI.h"

class AXICounters : public TObject
{
    public:
        __fastcall AXICounters(int ctn, int * IDs);
        __fastcall AXICounters(int ctn);
        __fastcall ~AXICounters();
    private:
        bool bCanCalculate;
        const int count;
        int * CounterIDs;
        unsigned int * CounterValue;
    public:
        void __fastcall SetCounterID(int index, int ID);
        void __fastcall CanCalculate(bool bCan);
        void __fastcall ReadCounters();
        int __fastcall getCounterValue();
};
#endif
 
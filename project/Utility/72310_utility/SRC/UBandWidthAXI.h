//---------------------------------------------------------------------------

#ifndef UBandWidthAXIH
#define UBandWidthAXIH
//---------------------------------------------------------------------------

#include "I2CDevice.h"

class BandWidthAXI
{
    public:
        __fastcall BandWidthAXI();
        __fastcall BandWidthAXI(I2CDevice * dev);

        virtual __fastcall ~BandWidthAXI();
    private:
        static unsigned int BaseAddress;
        static I2CDevice * Device;
        static int Agents[23];
    public:
        static void __fastcall SetDevice(I2CDevice * dev);
        static void __fastcall getAgentMap();
        static int __fastcall getAgentID(int index);
        static int __fastcall getAgentIndex(int agent);
        static int __fastcall getCounterID(int agent);
        static void __fastcall setStartAndEnd(int start, int end);
        static void __fastcall SwitchCounter(int index);
        static unsigned int __fastcall ReadCounter();
        static unsigned int __fastcall ReadCounter(int index);
        static void __fastcall PauseCounter(bool bPause);
};
#endif
 
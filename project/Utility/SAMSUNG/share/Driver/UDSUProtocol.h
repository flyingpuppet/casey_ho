//---------------------------------------------------------------------------

#ifndef UDSUProtocolH
#define UDSUProtocolH
#include "UProtocol.h"
#include "CPort.hpp"
#include <vcl.h>
//---------------------------------------------------------------------------

class DSUProtocol : public CProtocol
{
    private:
        TComPort * com;   
        Byte comBuffer[9];
        Byte Buffer[512];
		bool bDataReceived;
        int dataCount;
        
        void __fastcall InitReadWrite();
        void __fastcall RxChar(TObject *Sender, int Count);
    public:
		__fastcall DSUProtocol();
		virtual bool __fastcall CreateConnect();
		virtual void __fastcall SetSlave(Byte b);
		virtual bool __fastcall SetConnect();
		virtual bool __fastcall SetConnect(TComPort * cp);
		virtual void __fastcall SetSpeed(int speed);
		
        virtual bool __fastcall ReadDWord(unsigned int Address, unsigned int &ReadDWord);
        virtual bool __fastcall WriteDWord(unsigned int Address, unsigned int WriteDWord);
        virtual bool __fastcall ReadByte(unsigned int Address, unsigned char &ReadByte);
        virtual bool __fastcall WriteByte(unsigned int Address, unsigned char WriteByte);
		
		virtual bool __fastcall IIC_ReadByte(Byte RegAddr, Byte * bval);
        virtual bool __fastcall IIC_WriteByte(Byte RegAddr, Byte bval);
		virtual bool __fastcall BurstReadByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count = NULL);
        virtual bool __fastcall BurstWriteByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count = NULL);
};
#endif

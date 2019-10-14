//---------------------------------------------------------------------------

#ifndef UProtocolH
#define UProtocolH
#include <vcl.h>
#include "CPort.hpp"
//#include "I2C.h"
//---------------------------------------------------------------------------
class CProtocol
{		

	public:		
		//__fastcall CProtocol();
		virtual bool __fastcall CreateConnect()=0;
		virtual void __fastcall SetSlave(Byte b)=0;
		virtual bool __fastcall SetConnect()=0;
		virtual bool __fastcall SetConnect(TComPort * cp)=0;
		virtual void __fastcall SetSpeed(int speed)=0;
        virtual bool __fastcall ReadDWord(unsigned int Address, unsigned int &ReadDWord)=0;
        virtual bool __fastcall WriteDWord(unsigned int Address, unsigned int WriteDWord)=0;
        virtual bool __fastcall ReadByte(unsigned int Address, unsigned char &ReadByte)=0;
        virtual bool __fastcall WriteByte(unsigned int Address, unsigned char WriteByte)=0;
		
		virtual bool __fastcall IIC_ReadByte(Byte RegAddr, Byte * bval)=0;
        virtual bool __fastcall IIC_WriteByte(Byte RegAddr, Byte bval)=0;
		virtual bool __fastcall BurstReadByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count = NULL)=0;
        virtual bool __fastcall BurstWriteByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count = NULL)=0;
};
#endif
 
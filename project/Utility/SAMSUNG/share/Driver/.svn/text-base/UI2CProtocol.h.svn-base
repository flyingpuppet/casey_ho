//---------------------------------------------------------------------------

#ifndef UI2CProtocolH
#define UI2CProtocolH
#include "UProtocol.h"
#include "I2C.h"
//---------------------------------------------------------------------------
class I2CProtocol : public CProtocol
{
	private:
		CI2C * IIC;
		Byte DeviceSlave;
		
        bool __fastcall IsIICExist();
		
		bool __fastcall IICSelAddr(unsigned int Address);
		bool __fastcall AHBGetData(unsigned int &ReadData);
		bool __fastcall AHBSetData(unsigned int WriteData);

        bool __fastcall DMALength(unsigned int length);
        bool __fastcall DMATriger(bool isRead);
        bool __fastcall DMAReset();
		
    public:
		__fastcall I2CProtocol();
		virtual bool __fastcall CreateConnect();
		virtual bool __fastcall SetConnect();
		virtual bool __fastcall SetConnect(TComPort * cp);
		virtual void __fastcall SetSlave(Byte b);
		virtual void __fastcall SetSpeed(int speed);
		virtual bool __fastcall IIC_ReadByte(Byte RegAddr, Byte * bval);
        virtual bool __fastcall IIC_WriteByte(Byte RegAddr, Byte bval);

        virtual bool __fastcall ReadDWord(unsigned int Address, unsigned int &ReadDWord);
        virtual bool __fastcall WriteDWord(unsigned int Address, unsigned int WriteDWord);
        virtual bool __fastcall ReadByte(unsigned int Address, unsigned char &ReadByte);
        virtual bool __fastcall WriteByte(unsigned int Address, unsigned char WriteByte);
		virtual bool __fastcall BurstReadByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count = NULL);
        virtual bool __fastcall BurstWriteByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count = NULL);
};
#endif

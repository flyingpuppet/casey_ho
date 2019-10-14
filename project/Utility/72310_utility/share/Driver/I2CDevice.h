//---------------------------------------------------------------------------

#ifndef I2CDeviceH
#define I2CDeviceH


#include <vcl.h>
//#include "I2C.h"
#include "I2CDeviceInterface.h"
#include "UProtocol.h"


//#define _IIC_Debug
/*struct __RegisterAddress
{
    unsigned int base;
    int board;
    int page;
    int reg;
} _RegAdd;  */

class I2CDevice : public I2CDeviceInterface
{
    private:
		CProtocol * oPro;
        Byte DeviceSlave;
        AnsiString Name;
        static unsigned char ** reg_map;
		int IIC_Index;

		
    public:
        
        void SetSlave(Byte bval);
        Byte GetSlave();
		void SetIICIndex(int index);
        int GetIICIndex();
        
    public:
        I2CDevice(AnsiString str);

		void SetProtocol(CProtocol * op);
		CProtocol * GetProtocol();

        void SetName(AnsiString str);
        AnsiString GetName();

        void SetRegMap(unsigned char ** ppChar);
        unsigned char * GetRegMap(int n);

        virtual void SetBase(unsigned int b)=0;
        virtual void SetBase(AnsiString sb)=0;
        virtual unsigned int GetBase()=0;

        virtual void SetBoard(int b)=0;
        virtual void SetBoard(AnsiString sb)=0;
        virtual int GetBoard()=0;

        virtual void SetPage(int p)=0;
        virtual void SetPage(AnsiString sp)=0;
        virtual int GetPage()=0;

        virtual int GetPageNumber()=0;
        virtual int GetBoardNumber()=0;


        virtual void SetRegister(int reg)=0;
        virtual void SetRegister(AnsiString sr)=0;
        virtual int GetRegister()=0;
        virtual void SetAddress(unsigned int b, int p, int r)=0;
        virtual void SetAddress(AnsiString sb, AnsiString sp, AnsiString sr)=0;

        virtual bool Start()=0;

        virtual bool GetPageExist(int b, int p)=0;
        virtual void ChangePageList(int i)=0;
        virtual void ChangePageList(int * PL)=0;

        virtual bool ReadDWord(unsigned int Address, unsigned int &ReadDWord){return true;};
		virtual bool WriteDWord(unsigned int Address, unsigned int WriteDWord){return true;};

		virtual bool ReadByte(unsigned int Address, Byte &ReadByte){return true;};
		virtual bool WriteByte(unsigned int Address, Byte WriteByte){return true;};

        virtual bool ReadDWord(unsigned int &ReadDWord)=0;
        virtual bool WriteDWord(unsigned int WriteDWord)=0;

		virtual bool ReadByte(Byte &ReadByte)=0;
		virtual bool WriteByte(Byte WriteByte)=0;

        virtual bool BurstReadByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count=NULL)=0;
        virtual bool BurstWriteByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count=NULL)=0;
        virtual bool BurstReadByte(int byteCount, Byte * LineBuffer,
            int *Count=NULL)=0;
        virtual bool BurstWriteByte(int byteCount, Byte * LineBuffer,
            int *Count=NULL)=0;
            
        virtual bool AllWriteByte(unsigned int Address, Byte WriteByte)=0;
        virtual bool AllReadByte(unsigned int Address, Byte &ReadByte)=0;
        virtual bool AllWriteDWord(unsigned int Address, unsigned int WriteDWord)=0;
        virtual bool AllReadDWord(unsigned int Address, unsigned int &ReadDWord)=0;

};


//---------------------------------------------------------------------------
#endif














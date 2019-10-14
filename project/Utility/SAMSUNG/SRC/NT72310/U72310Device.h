//---------------------------------------------------------------------------

#ifndef U72310DeviceH
#define U72310DeviceH
//---------------------------------------------------------------------------

#include <vcl.h>
#include "I2CDevice.h"

class Dev_72310 : public I2CDevice
{
    private:
        unsigned int Base;
        int Page;
        int Register;
        bool BurstMode;
        
    public:
        Dev_72310(AnsiString str);

        void SetBurstMode(bool b);
        bool GetButstMode();

        virtual void SetBase(unsigned int b);
        virtual void SetBase(AnsiString sb);
        virtual unsigned int GetBase();

        virtual void SetBoard(int b);
        virtual void SetBoard(AnsiString sb);
        virtual int GetBoard();

        virtual void SetPage(int p);
        virtual void SetPage(AnsiString sp);
        virtual int GetPage();

        virtual int GetPageNumber();
        virtual int GetBoardNumber();

        virtual void SetRegister(int reg);
        virtual void SetRegister(AnsiString sr);
        virtual int GetRegister();

        virtual void SetAddress(unsigned int b, int p, int r);
        virtual void SetAddress(AnsiString sb, AnsiString sp, AnsiString sr);

        virtual bool Start();

        virtual bool GetPageExist(int b, int p);
        virtual void ChangePageList(int i);
        virtual void ChangePageList(int * PL);

		virtual bool ReadDWord(unsigned int Address, unsigned int &ReadDWord);
		virtual bool WriteDWord(unsigned int Address, unsigned int WriteDWord);
		
		virtual bool ReadByte(unsigned int Address, Byte &ReadByte);
		virtual bool WriteByte(unsigned int Address, Byte WriteByte);

        virtual bool ReadDWord(unsigned int &ReadDWord);
        virtual bool WriteDWord(unsigned int WriteDWord);

		virtual bool ReadByte(Byte &ReadByte);
		virtual bool WriteByte(Byte WriteByte);

        virtual bool AllWriteByte(unsigned int Address, Byte WriteByte);
        virtual bool AllReadByte(unsigned int Address, Byte &ReadByte);
        virtual bool AllWriteDWord(unsigned int Address, unsigned int WriteDWord);
        virtual bool AllReadDWord(unsigned int Address, unsigned int &ReadDWord);


        virtual bool BurstReadByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count = NULL);
        virtual bool BurstWriteByte(unsigned int startAddr, int byteCount,
            Byte * LineBuffer, int *Count = NULL);
        virtual bool BurstReadByte(int byteCount, Byte * LineBuffer,
            int *Count = NULL);
        virtual bool BurstWriteByte(int byteCount, Byte * LineBuffer,
            int *Count = NULL);
};

#endif

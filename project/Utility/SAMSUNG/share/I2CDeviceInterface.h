//---------------------------------------------------------------------------

#ifndef I2CDeviceInterfaceH
#define I2CDeviceInterfaceH


class I2CDeviceInterface
{
    public:

        virtual bool ReadDWord(unsigned int Address, unsigned int &ReadDWord)=0;
        virtual bool WriteDWord(unsigned int Address, unsigned int WriteDWord)=0;
        virtual bool ReadByte(unsigned int Address, unsigned char &ReadByte)=0;
        virtual bool WriteByte(unsigned int Address, unsigned char WriteByte)=0;

};


//---------------------------------------------------------------------------
#endif














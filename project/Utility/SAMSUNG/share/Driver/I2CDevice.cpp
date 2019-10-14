//---------------------------------------------------------------------------


#pragma hdrstop

#include <vcl.h>
#include "I2CDevice.h"
#include "I2C.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

unsigned char ** I2CDevice::reg_map = NULL;

I2CDevice::I2CDevice(AnsiString str)
{
    Name = str;
#ifdef _IIC_Debug
    ShowMessage("Create Object "+Name);
#endif
}

void I2CDevice::SetRegMap(unsigned char ** ppChar)
{
    reg_map = ppChar;
}
unsigned char * I2CDevice::GetRegMap(int n)
{
    return reg_map[n];
}

void I2CDevice::SetSlave(Byte bval)
{
     DeviceSlave = bval;
     if(oPro != NULL)
     {
        oPro->SetSlave(bval);
     }
}
Byte I2CDevice::GetSlave()
{
    return DeviceSlave;
}



void I2CDevice::SetName(AnsiString str)
{
    Name = str;
}

AnsiString I2CDevice::GetName()
{
    return Name;
}

void I2CDevice::SetProtocol(CProtocol * op)
{
	oPro = op;
}
CProtocol * I2CDevice::GetProtocol()
{
	return oPro;
}
void I2CDevice::SetIICIndex(int index)
{
    IIC_Index = index;
}
//---------------------------------------------------------------------------
int I2CDevice::GetIICIndex()
{
    return IIC_Index;
}
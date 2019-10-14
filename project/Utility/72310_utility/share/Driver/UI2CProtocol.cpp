//---------------------------------------------------------------------------


#pragma hdrstop

#include "UI2CProtocol.h"
#include <vcl.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)


CI2C  * oIIC = new CI2C();
//---------------------------------------------------------------------------
__fastcall I2CProtocol::I2CProtocol()
{
	this->SetConnect();
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::CreateConnect()
{
	TForm * frm;


    frm = new TForm(Application);

    if(oIIC->GetUSBStatus())
    {
        oIIC->ChangeConnectSetting(false);
        frm->Free();
        return true;
    }
    else
    {
        if(oIIC->USBConnect(frm->Handle))
        {
            oIIC->ChangeConnectSetting(false);
            frm->Free();
            return true;
        }
        else
        {
            //oIIC.ChangeConnectSetting(true);
            //errNo = GetLastError();
            //errStr = SysErrorMessage(errNo);
            //ShowMessage(errStr);
            oIIC->USBClose();
            frm->Free();
            return false;
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::ReadDWord(unsigned int Address, unsigned int &ReadDWord)
{
	if(!IICSelAddr(Address))
	{
		return false;
	}
	if(!AHBGetData(ReadDWord) )
	{
		return false;
	}
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::WriteDWord(unsigned int Address, unsigned int WriteDWord)
{
	if(!IICSelAddr(Address))
	{
		return false;
	}
	if(!AHBSetData(WriteDWord))
	{
		return false;
	}
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::ReadByte(unsigned int Address, unsigned char &ReadByte)
{
	int modby4;
	unsigned int ReadData;
	
	modby4 = Address % 4;
	Address -= modby4;
	if(!IICSelAddr(Address))
	{
		return false;
	}
	if(!AHBGetData(ReadData) )
	{
		return false;
	}
	ReadByte = (ReadData >> (modby4*8)) & 0xFF;
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::WriteByte(unsigned int Address, unsigned char WriteByte)
{
	int modby4;
	unsigned int ReadData;
	
	modby4 = Address %4;
	Address -= modby4; 

	if(!ReadDWord(Address, ReadData))
	{
		return false;
	}

	ReadData = ReadData & (0xFFFFFFFF-(0xFF<<(modby4*8)));
	ReadData = ReadData + (WriteByte<<(modby4*8));
	
	if(!IICSelAddr(Address))
	{
		return false;
	}
	if(!AHBSetData(ReadData))
	{
		return false;
	}
    return true;    
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::IICSelAddr(unsigned int Address)
{
	unsigned char SubAddress;
	unsigned char Data;
	unsigned int i;

	for(i = 0 ; i < 4 ; i++)
	{
		Data = (Address>>(i*8)) & 0xFF;
		SubAddress = i;
		if(IIC_WriteByte(SubAddress , Data) == false)
		{
			return false;
 		}
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::AHBGetData(unsigned int &ReadData)
{
	unsigned char SubAddress;
	unsigned char Data;
	unsigned int i , count;
	ReadData = 0;

	// Read Enable
	SubAddress = 0x0C;
	Data = 0x02;
	if(IIC_WriteByte(SubAddress , Data) == false)
	{
		return false;
	}

	Data = 0xFF;
	count = 0;
	while((Data!=0) || (count > 1500))
	{
		if(IIC_ReadByte(SubAddress , &Data) == false)
		{
			return false;
		}
		count++;
	}

	if(count >= 1500)
	{
		return false;
	}

	// Read Data
	for(i = 0 ; i < 4 ; i++)
	{
		SubAddress = i+8;
		if(IIC_ReadByte(SubAddress , &Data) == false)
		{
			return false;
		}
		ReadData |= (Data<<(i*8));
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::AHBSetData(unsigned int WriteData)
{
	unsigned char SubAddress;
	unsigned char Data;
	unsigned int i , count;

	// Write Data
	for(i = 0 ; i < 4 ; i++)
	{
		Data = (WriteData>>(i*8)) & 0xFF;
		SubAddress = i+4;
		if(IIC_WriteByte(SubAddress , Data) == false)
		{
			return false;
		}
	}

	// Write Enable
	SubAddress = 0x0C;
	Data = 0x01;
	if(IIC_WriteByte(SubAddress , Data) == false)
	{
		return false;
	}

	Data = 0xFF;
	count = 0;
	while((Data!=0) || (count > 1500))
	{
		if(IIC_ReadByte(SubAddress , &Data) == false)
		{
			return false;
		}
		count++;
	}

	if(count >= 1500)
	{
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::DMALength(unsigned int length)
{
	unsigned char SubAddress;
    unsigned char Data;
    Data = length;///32;
    SubAddress = 0x10;//0x14;
    if(IIC_WriteByte(SubAddress , Data) == false)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::DMATriger(bool isRead)
{
	unsigned char SubAddress;
    unsigned char Data;
    unsigned int i , count;

    // Triger
    SubAddress = 0x0C;
    if(isRead)
        Data = 0x08;//0x02;
    else
        Data = 0x04;//0x01;

    if(IIC_WriteByte(SubAddress , Data) == false)
    {
        return false;
    }

    Data = 0xFF;
    count = 0;
    while((Data!=0) || (count > 1500))
    {
        if(IIC_ReadByte(SubAddress , &Data) == false)
        {
            return false;
        }
        count++;
    }

    //SubAddress = 0x20;
    if(IIC_ReadByte(SubAddress , &Data) == false)
    {
        return false;
    }

    if(count >= 1500)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::DMAReset()
{
	unsigned char SubAddress;
    unsigned char Data;
    SubAddress = 0x20;
    Data = 0x00;
    if(IIC_WriteByte(SubAddress , Data) == false)
    {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::IIC_ReadByte(Byte RegAddr, Byte * bval)
{
    int i;
    if(IsIICExist())
    {
        while(!(IIC->I2CRead(DeviceSlave, &RegAddr, bval)))
        {
            i++;
            if(i>3)
            {
                //throw Exception("I2C Error!");
                return false;
            }
        }
        return true;
    }
	else
	{
        //throw Exception("I2C Error!");
		return false;
	}
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::IIC_WriteByte(Byte RegAddr, Byte bval)
{
    int i;
    i = 0;
    if(IsIICExist())
    {
        while(!(IIC->I2CWrite(DeviceSlave, &RegAddr, &bval)))
        {
            i++;
            if(i>3)
            {
                //throw Exception("I2C Error!");
                return false;
            }
        }
        return true;
    }
	else
	{
        //throw Exception("I2C Error!");
        return false;
	}
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::IsIICExist()
{
    if(IIC == NULL)
    {
        return false;
    }
    else
    {
        //if(IIC->CheckConnect())
        //{
        //if(IIC->GetUSBStatus())
            return true;
        //}
        //else
        //{
            //return false;
        //}
    }
}
//---------------------------------------------------------------------------
void __fastcall I2CProtocol::SetSpeed(int speed)
{
    //IIC->SetSpeed((unsigned short)speed);
    //IIC->LoopCounter = (WORD)speed;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::SetConnect()
{
    
    IIC = oIIC;
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::SetConnect(TComPort * cp)
{
    IIC = oIIC;
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::BurstReadByte(unsigned int startAddr, int byteCount,
		Byte * LineBuffer, int *Count)
{
	unsigned char SubAddr;
    unsigned char data;

    if(!IICSelAddr(startAddr))
    {
        return false;
    }
    if(!DMALength(byteCount-1))
    {
        return false;
    }

    if(!DMAReset())
    {
         return false;
    }

    if(!DMATriger(true))
    {
        return false;
    }

    if(!DMAReset())
    {
        return false;
    }

    SubAddr = 0x22;
    for(int i=0;i<byteCount;i++)
    {
        if(IIC_ReadByte(SubAddr, &data) == false)
        {
            return false;
        }
        LineBuffer[i] = data;
        if(Count != NULL)
        {
            (*Count)++;
        }
    }
    return true;	
}
//---------------------------------------------------------------------------
bool __fastcall I2CProtocol::BurstWriteByte(unsigned int startAddr, int byteCount,
		Byte * LineBuffer, int *Count)
{
	unsigned char SubAddr;
    unsigned char data;

    if(!IICSelAddr(startAddr))
    {
        return false;
    }
    
    if(!DMALength(byteCount-1))
    {
        return false;
    }

    if(!DMAReset())
    {
        return false;
    }


    SubAddr = 0x21;
    for(int i=0;i<byteCount;i++)
    {
        data = LineBuffer[i];
        if(IIC_WriteByte(SubAddr , data) == false)
        {
            return false;
        }
        if(Count!=NULL)
        {
            (*Count)++;
        }
    }

    if(!DMAReset())
    {
        return false;
    }
    
    if(!DMATriger(false))
    {
        return false;
    }
    return true;	
}
//---------------------------------------------------------------------------
void __fastcall I2CProtocol::SetSlave(Byte b)
{
	DeviceSlave	= b;
}
//---------------------------------------------------------------------------
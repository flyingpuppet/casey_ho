//---------------------------------------------------------------------------


#pragma hdrstop

#include "UDSUProtocol.h"
#include <time.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall DSUProtocol::DSUProtocol()
{
	//SetConnect();
    //com->OnRxChar = RxChar;
    bDataReceived = false;
}
//---------------------------------------------------------------------------
void __fastcall DSUProtocol::SetSlave(Byte b)
{
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::SetConnect()
{
    //comPort = Com;
    return true;	
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::SetConnect(TComPort * cp)
{
	com = cp;
	com->OnRxChar = RxChar;
	return true;	
}
//---------------------------------------------------------------------------
void __fastcall DSUProtocol::SetSpeed(int speed)
{
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::ReadDWord(unsigned int Address, unsigned int &ReadDWord)
{
	clock_t start, end;
    
	InitReadWrite();
	bDataReceived = false;
    dataCount = 0;
    
    comBuffer[0] = 0x80;
    comBuffer[1] = (Byte)(Address >> 24);
    comBuffer[2] = (Byte)(Address >> 16);
    comBuffer[3] = (Byte)(Address >> 8);
    comBuffer[4] = (Byte) Address;
    com->Write(comBuffer, 5);
	
	start = clock();
	while(1)
	{
        Application->ProcessMessages();
		end = clock();
		if((end-start) > 2000)
		{
			ShowMessage("Time is out!");
			return false;
		} 
		//if(bDataReceived)
        if(dataCount < 4)
        {
            continue;
        }
        else
		{
			ReadDWord = (Buffer[0]<<24) | (Buffer[1]<<16) | (Buffer[2]<<8) | Buffer[3];
			return true;
		}
	}
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::WriteDWord(unsigned int Address, unsigned int WriteDWord)
{
    InitReadWrite();
    
    comBuffer[0] = 0xC0;
    comBuffer[1] = (Byte)(Address >> 24);
    comBuffer[2] = (Byte)(Address >> 16);
    comBuffer[3] = (Byte)(Address >> 8);
    comBuffer[4] = (Byte) Address;
    comBuffer[5] = (Byte)(WriteDWord >> 24);
    comBuffer[6] = (Byte)(WriteDWord >> 16);
    comBuffer[7] = (Byte)(WriteDWord >> 8);
    comBuffer[8] = (Byte) WriteDWord;

    com->Write(comBuffer, 9);
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::ReadByte(unsigned int Address, unsigned char &ReadByte)
{
	int modby4;
	unsigned int ReadData;
	
	modby4 = Address % 4;
	Address -= modby4;

	if(this->ReadDWord(Address, ReadData))
	{
	
		ReadByte = (ReadData >> (modby4*8)) & 0xFF;
    	return true;
	}
	else
	{
		return false;
	}
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::WriteByte(unsigned int Address, unsigned char WriteByte)
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
	
    return WriteDWord(Address, ReadData);    	    
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::IIC_ReadByte(Byte RegAddr, Byte * bval)
{
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::IIC_WriteByte(Byte RegAddr, Byte bval)
{
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::BurstReadByte(unsigned int startAddr, int byteCount,
    Byte * LineBuffer, int *Count)
{
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::BurstWriteByte(unsigned int startAddr, int byteCount,
    Byte * LineBuffer, int *Count)
{
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall DSUProtocol::CreateConnect()
{
    if(com->Connected)
    {
        try
        {
            com->Close();
        }
        catch(...)
        {
            return false;
        }  
        return false;
    }
    try
    {
        com->Open();
    }
    catch(...)
    {
        return false;
    }               

    if(com->Connected)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//---------------------------------------------------------------------------
void __fastcall DSUProtocol::InitReadWrite()
{
    Byte buf[4];

    if(com == NULL)
    {
        ShowMessage("Please Connect the DSU");
        return;
    }

    if(com->Connected == false)
    {
        ShowMessage("Please Connect the DSU!");
        return;
    }
    buf[0] = 0x55;
    buf[1] = 0x55;
    buf[2] = 0x55;
    buf[3] = 0x55;

    com->Write(buf,4);
}
//---------------------------------------------------------------------------
void __fastcall DSUProtocol::RxChar(TObject *Sender, int Count)
{
    char bval, buf[4];
    int sts;//, n;
    //n = 0;
    while(1)
    {
        sts = com->Read(buf,1);

        if(sts == 0) break;

        bval = buf[0];
        if(dataCount < 512)
        {
            Buffer[dataCount++] = (unsigned char)(bval & 0xFF);
            //if(n>=4)
            //{
                //bDataReceived = true;
            //}
            }

        }
    //com->Read(Buffer,4);
    //bDataReceived = true;
    //ShowMessage(((Buffer[0]<<24) | (Buffer[1]<<16) | (Buffer[2]<<8) | Buffer[3]));
}
//---------------------------------------------------------------------------
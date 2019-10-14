//---------------------------------------------------------------------------


#pragma hdrstop

//#include <vcl.h>
//#include <windows.h>
//#include <stdio.h>
//#include <Controls.hpp>

//#include "ioport.hpp"
#include "I2C.h"
#include "ntport.h"
//#include "USBPort.h"
//#include "conio.h"

#define SCL             0x40
#define SDA             0x80

#define SCL_TIMEOUT     1
#define BAD_NACK        2
#define NOT_IDLE        4
#define SLVADR_NACK     8

// ARLO may also occur when we want to send a data bit 1 and we see a 0 on the bus
#define ARLOSS          16

/////////////
// Access Bus layer error only
#define BAD_CHECKSUM    32
#define BAD_MESSAGE     64

#define  ACK_     0
#define  NACK     1

#define  AHB_BUSY	1
#define  AHB_IDLE	0

/*
#include "I2C.h"

#include "WinIo.h"
#include "USBPort.h"
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////
// Class CI2C

CI2C::CI2C()
{
    m_bIsPrintPort = false;
    m_bIsLibraryExist = FALSE;
    m_bIsUSBConnect = false;
    m_PrinterPortNum = NotConnect;
}

CI2C::~CI2C()
{
}

void CI2C::PrinterPort_StartBit(void)
{
    PROCStartBit();
}

void CI2C::PrinterPort_ReStartBit(void)
{
    PROCReStartBit();
}

void CI2C::PrinterPort_ReleaseBus(void)
{
    PROCReleaseBus();
}

void CI2C::PrinterPort_SendAddress(unsigned char SlaveAddress,unsigned char R_W)
{
    PROCSendAddress(SlaveAddress,R_W);
}

void CI2C::PrinterPort_SendData(unsigned char Data)
{
    PROCSendData(Data);
}

bool CI2C::PrinterPort_ReadData(unsigned char *Data)
{
    return PROCReadData(Data);
}

void CI2C::PrinterPort_StopBit(void)
{
    PROCStopBit();
}

bool CI2C::PrinterPort_ReadResponce(void)
{
    return PROCReadResponce();
}

void CI2C::PrinterPort_SendNAK(void)
{
    PROCSendNAK();
}

void CI2C::PrinterPort_SendACK(void)
{
    PROCSendACK();
}

bool CI2C::I2CBYTEWrite(unsigned char Slave , unsigned char SubAddress , unsigned char Data)
{
    unsigned char WriteSubAddress;
    unsigned char WriteData;
    WriteSubAddress = SubAddress;
    WriteData = Data;

    if(I2CWrite(Slave , &WriteSubAddress , &WriteData) == false)
    {
        return false;
    }

    return true;
}

bool CI2C::I2CBYTERead(unsigned char Slave , unsigned char SubAddress , unsigned char* Data)
{
    unsigned char ReadSubAddress;
    unsigned char ReadData;
    ReadSubAddress = SubAddress;

    if(I2CRead(Slave , &ReadSubAddress , &ReadData) == false)
    {
        return false;
    }
    Data = &ReadData;
    return true;
}

bool CI2C::I2CWrite(unsigned char Slave , unsigned char* SubAddress , unsigned char* Data , unsigned char DataLen , unsigned char SubLen)
{
    if(m_bIsPrintPort)
    {
        PrinterPort_ReleaseBus();
        PrinterPort_StartBit();
        PrinterPort_SendAddress(Slave,I2C_Write);

        if(!PrinterPort_ReadResponce())
        {
            MessageBox(NULL , "Send Slave Error !" , "Error" , MB_OK);
            PrinterPort_StopBit();
            PrinterPort_ReleaseBus();
            return false;
        }
        //MessageBox(NULL , "SendAddress" , "Info" , MB_OK);
        for(int i = 0 ; i < SubLen ; i++)
        {
            unsigned char Temp;
            Temp = *((unsigned char*)(SubAddress + i));
            PrinterPort_SendData(Temp);

            if(!PrinterPort_ReadResponce())
            {
                MessageBox(NULL , "Send Register Error !" , "Error" , MB_OK);
                PrinterPort_StopBit();
                PrinterPort_ReleaseBus();
                return false;
            }
            //MessageBox(NULL , "SendSubAddr" , "Info" , MB_OK);
        }

        for(int i = 0 ; i < DataLen ; i++)
        {
            unsigned char Temp;
            Temp = *((unsigned char*)(Data + i));
            PrinterPort_SendData(Temp);

            if(!PrinterPort_ReadResponce())
            {
                MessageBox(NULL , "Send Data Error !" , "Error" , MB_OK);
                PrinterPort_StopBit();
                PrinterPort_ReleaseBus();
                return false;
            }
            //MessageBox(NULL , "SendData" , "Info" , MB_OK);
        }

        PrinterPort_StopBit();
        PrinterPort_ReleaseBus();
    }
    else
    {
        unsigned char Status;
        if(USBPort.IIC_SendStart(0) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , &Slave , 1) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , SubAddress , SubLen) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , Data , DataLen) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_SendStop(0) != STA_JIG_OK) return false;
    }
    return true;
}

bool CI2C::I2CRead(unsigned char Slave , unsigned char* SubAddress , unsigned char* Data , unsigned char DataLen , unsigned char SubLen)
{
    if(m_bIsPrintPort)
    {
        unsigned char* Data8Bit;
        //PrinterPort_ReleaseBus();
        PrinterPort_StartBit();
        PrinterPort_SendAddress(Slave,I2C_Write);

        if(!PrinterPort_ReadResponce())
        {
            MessageBox(NULL , "Send Slave Error !" , "Error" , MB_OK);
            PrinterPort_StopBit();
            PrinterPort_ReleaseBus();
            return false;
        }
        //MessageBox(NULL , "SendAddress" , "Info" , MB_OK);

        for(int i = 0 ; i < SubLen ; i++)
        {
            unsigned char Temp;
            Temp = *((unsigned char*)(SubAddress + i));
            PrinterPort_SendData(Temp);

            if(!PrinterPort_ReadResponce())
            {
                MessageBox(NULL , "Send Register Error !" , "Error" , MB_OK);
                PrinterPort_StopBit();
                PrinterPort_ReleaseBus();
                return false;
            }
            //MessageBox(NULL , "SendData" , "Info" , MB_OK);
        }

        PrinterPort_ReStartBit();
        PrinterPort_SendAddress(Slave,I2C_Read);

        if(!PrinterPort_ReadResponce())
        {
                MessageBox(NULL , "Send Slave Error !" , "Error" , MB_OK);
                PrinterPort_StopBit();
                PrinterPort_ReleaseBus();
                return false;
        }
        //MessageBox(NULL , "SendAddress" , "Info" , MB_OK);

        for(int i = 0 ; i < DataLen ; i++)
        {
            Data8Bit = ((unsigned char*)(Data + i));
            if(!PrinterPort_ReadData(Data8Bit))
            {
                MessageBox(NULL , "Read Data Error !" , "Error" , MB_OK);
                PrinterPort_StopBit();
                PrinterPort_ReleaseBus();
                return false;
            }
            if(i == DataLen - 1)
            {
                PrinterPort_SendNAK();
            }
            else
            {
                PrinterPort_SendACK();
            }
            //MessageBox(NULL , "ReadData" , "Info" , MB_OK);
        }
        PrinterPort_StopBit();
        PrinterPort_ReleaseBus();
    }
    else
    {
        unsigned char Status;
        if(USBPort.IIC_SendStart(0) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , &Slave , 1) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , SubAddress , SubLen) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_SendRepeatStart(0) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        Slave |= 0x01;
        if(USBPort.IIC_Tx(0 , &Slave , 1) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Rx(0 , Data , DataLen) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_SendStop(0) != STA_JIG_OK) return false;
    }
    return true;
}

void CI2C::ChangeConnect(bool bIsPrintPort)
{
    m_bIsPrintPort = bIsPrintPort;
}

BOOL CI2C::GetConnect()
{
    return m_bIsPrintPort;
}

BOOL CI2C::ConnectPrinterPort(unsigned int PortNum)
{
    if(PortNum == 0x378)
    {
        PROCSetPrintPort(0x378);
        if(!PROCPassword(0xAA))
        {
            return FALSE;
        }
        PROCSetBaudRate(50);
        m_PrinterPortNum = Port378;
    }
    else if(PortNum == 0x278)
    {
        PROCSetPrintPort(0x278);
        if(!PROCPassword(0xAA))
        {
            return FALSE;
        }
        PROCSetBaudRate(50);
        m_PrinterPortNum = Port278;
    }
    else if(PortNum == 0x3BC)
    {
        PROCSetPrintPort(0x3BC);
        if(!PROCPassword(0xAA))
        {
            return FALSE;
        }
        PROCSetBaudRate(50);
        m_PrinterPortNum = Port3BC;
    }
    return TRUE;
}

int CI2C::GetPrinterPortNum()
{
    return m_PrinterPortNum;
}

BOOL CI2C::ConnectUSB(HANDLE hUSBHandle)
{
    if(USBPort.Open(hUSBHandle,NULL) != STA_OK)
    {
        m_bIsUSBConnect = false;
        return false;
    }
    else
    {
        m_bIsUSBConnect = true;
        return true;
    }
}

BOOL CI2C::GetUSBStatus()
{
    return m_bIsUSBConnect;
}

BOOL CI2C::LoadPrinterPortLibrary()
{
    BOOL bResult;
    bResult = InitializeWinIo();
    if (!bResult)
    {
        MessageBox(NULL , "Fail to initialize WinIO" , "Error" , MB_OK);
        return FALSE;
    }

    hInst = LoadLibrary("I2cDll.dll");
    if(!hInst)
    {
        MessageDlg("Open I2CDLL.dll error !",mtError,TMsgDlgButtons()<<mbOK,0);
        return FALSE;
    }

    (FARPROC &)PROCSendData = GetProcAddress(hInst,"SendData");
    if(!PROCSendData)
    {
        return FALSE;
    }
    (FARPROC &)PROCSendAddress = GetProcAddress(hInst,"SendAddress");
    if(!PROCSendAddress)
    {
        return FALSE;
    }
    (FARPROC &)PROCSendACK = GetProcAddress(hInst,"SendACK");
    if(!PROCSendACK)
    {
         return FALSE;
    }
    (FARPROC &)PROCSendNAK = GetProcAddress(hInst,"SendNAK");
    if(!PROCSendNAK)
    {
        return FALSE;
    }
    (FARPROC &)PROCReadData = GetProcAddress(hInst,"ReadData");
    if(!PROCReadData)
    {
        return FALSE;
    }
    (FARPROC &)PROCReStartBit = GetProcAddress(hInst,"ReStartBit");
    if(!PROCReStartBit)
    {
        return FALSE;
    }
    (FARPROC &)PROCStartBit = GetProcAddress(hInst,"StartBit");
    if(!PROCStartBit)
    {
        return FALSE;
    }
    (FARPROC &)PROCStopBit = GetProcAddress(hInst,"StopBit");
    if(!PROCStopBit)
    {
        return FALSE;
    }
    (FARPROC &)PROCCheckWaitState = GetProcAddress(hInst,"CheckWaitState");
    if(!PROCCheckWaitState)
    {
        return FALSE;
    }
    (FARPROC &)PROCReadResponce = GetProcAddress(hInst,"ReadResponce");
    if(!PROCReadResponce)
    {
        return FALSE;
    }
    (FARPROC &)PROCReleaseBus = GetProcAddress(hInst,"ReleaseBus");
    if(!PROCReleaseBus)
    {
        return FALSE;
    }
    (FARPROC &)PROCSetPrintPort = GetProcAddress(hInst,"SetPrintPort");
    if(!PROCSetPrintPort)
    {
        return FALSE;
    }
    (FARPROC &)PROCClearPrintPort = GetProcAddress(hInst,"ClearPrintPort");
    if(!PROCClearPrintPort)
    {
        return FALSE;
    }
    (FARPROC &)PROCSCLPluse = GetProcAddress(hInst,"SCL_Pluse");
    if(!PROCSCLPluse)
    {
        return FALSE;
    }
    (FARPROC &)PROCSetBaudRate = GetProcAddress(hInst,"SetBaudRate");
    if(!PROCSetBaudRate)
    {
        return FALSE;
    }
    (FARPROC &)PROCPassword = GetProcAddress(hInst,"Password");
    if(!PROCPassword)
    {
        return FALSE;
    }
    m_bIsLibraryExist = TRUE;
    return TRUE;
}

BOOL CI2C::IsLibraryExist()
{
    return m_bIsLibraryExist;
}
*/
/****************************************************************************
 SDA_O: PortA_7
 SDA_I: PortB_7 (Inverted)
 SCL_O: PortA_6
 SCL_I: PortB_6
 Vcc  : PortA_2
 CONNECT_O: PortA_0
 CONNECT_I: PortB_5
 ****************************************************************************/

CI2C::CI2C()
{
    m_bIsPrintPort = false;
    m_bIsUSBConnect = false;
    m_PrinterPortNum = NotConnect;
    //Configure();
}

void CI2C::Configure(void)
{
   WORD LptBase = 0x378;
   LicenseInfo("Chang-Yu Liao",104832);     //Licence
   if(IsWinNT())
   {
      if(Lpt == 0)
         LptBase = 0x378;
      else if(Lpt == 1)
         LptBase = 0x278;
      else
         LptBase = 0x3BC;
      PORTAAddr = LptBase;
      PORTBAddr = LptBase+1;
      PORTCAddr = LptBase+2;
      EnablePorts(PORTAAddr,PORTCAddr+2);
      SetFastMode(1);
   }
   LoopCounter = 50;//1000;       // 100: for PIII-450MHz
   porta = 0x14;
   Outport(PORTAAddr,porta);
   portb = 0xfb;
   Outport(PORTBAddr,portb);
   portc = 0x0B;
   Outport(PORTCAddr,portc);
   WSetSCL(0);
   Wait();
   WSetSCL(1);
}

BOOL CI2C::CheckConnect(void)
{
   if((Inport(PORTBAddr) & 0x20) == 0)
   {
      SetSpeed(10);
      return true;
   }
   else
      return false;
}

//------------------------------------------------------------------------------
// Normal I2C Command (Random_w,Random_r,..)
//------------------------------------------------------------------------------
bool __fastcall CI2C::I2CWrite(unsigned char Slave , unsigned char* SubAddress , unsigned char* Data , unsigned int DataLen , unsigned int SubLen)
{
    if(m_bIsPrintPort)
    {
        ReleaseBus();
        SendStart();
        SendByte(Slave);
        for(unsigned int i = 0 ; i < SubLen ; i++)
        {
            SendByte(SubAddress[i]);
        }
        for(unsigned int i = 0 ; i < DataLen ; i++)
        {
            SendByte(Data[i]);
        }
        SendStop();
        ReleaseBus();
        return true;
    }
    else
    {
        unsigned char Status;
        if(USBPort.IIC_SendStart(0) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , &Slave , 1) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , SubAddress , SubLen) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , Data , DataLen) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_SendStop(0) != STA_JIG_OK) return false;
        return true;
    }
}
//------------------------------------------------------------------------------
bool __fastcall CI2C::I2CRead(unsigned char Slave , unsigned char* SubAddress , unsigned char* Data , unsigned int DataLen , unsigned int SubLen)
{
    if(m_bIsPrintPort)
    {
        ReleaseBus();

        SendStart();
        SendByte(Slave);
        for(unsigned int i = 0 ; i < SubLen ; i++)
        {
            SendByte(SubAddress[i]);
        }
        WSetSCL(1);
        Wait();
        SendStart();
        SendByte(Slave|0x01);
        for(unsigned int i = 0 ; i < DataLen - 1 ; i++)
        {
            ReadByte(Data[i] , ACK_);
        }
        ReadByte(Data[DataLen - 1] , NACK);
        SendStop();

        ReleaseBus();
        return true;
    }
    else
    {
        unsigned char Status;
        if(USBPort.IIC_SendStart(0) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , &Slave , 1) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Tx(0 , SubAddress , SubLen) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        //Wait();
        if(USBPort.IIC_SendRepeatStart(0) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        Slave |= 0x01;
        if(USBPort.IIC_Tx(0 , &Slave , 1) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_Rx(0 , Data , DataLen) != STA_JIG_OK)
        {
            USBPort.IIC_SendStop(0);
            return false;
        }
        if(USBPort.IIC_SendStop(0) != STA_JIG_OK) return false;
        return true;
    }
}

//------------------------------------------------------------------------------
// Send Stream
void CI2C::SendStream(BYTE *data)
{
   int i,l;
   
   l = *data++;
   SendStart();
   for(i=0;i<l;i++)
      SendByte(*data++);
   SendStop();
}
// Read Stream
void CI2C::ReadStream(BYTE *data)
{
   SendStart();
   SendByte(0x80);
   ReadByte(*(data++),ACK_);
   ReadByte(*(data++),ACK_);
   ReadByte(*(data),NACK);
   SendStop();
}

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////
// BYTE MANIPULATION FUNCTIONS

BYTE CI2C::ReadByte( BYTE& byte, BOOL Ack, BOOL Forced )
{  // Send one data byte, clean or not
   BYTE    b0,b1,b2,b3,b4,b5,b6,b7;
   BYTE Status;
   // option here!!!!
   Status = ReadBit(b7);
   Status |= ReadBit(b6);
   Status |= ReadBit(b5);
   Status |= ReadBit(b4);
   Status |= ReadBit(b3);
   Status |= ReadBit(b2);
   Status |= ReadBit(b1);
   Status |= ReadBit(b0);
   Status |= SendBit(Ack);

   byte = b7*128 + b6*64 + b5*32 + b4*16 + b3*8 + b2*4 + b1*2 + b0;

   return Status;
}

BYTE CI2C::SendByte( BYTE byte, BOOL Forced )
{  // Read one data byte, clean or not
   BYTE Status;
   BYTE ack = 0;
   // option here!!!!
   Status = SendBit(byte&128);
   Status |= SendBit(byte&64 );
   Status |= SendBit(byte&32 );
   Status |= SendBit(byte&16 );
   Status |= SendBit(byte&8  );
   Status |= SendBit(byte&4  );
   Status |= SendBit(byte&2  );
   Status |= SendBit(byte&1  );
   Status |= ReadBit(ack);
   if(ack==1) Status |= BAD_NACK;
      return Status;
};

//////////////////////////
// I2C BIT MANIPULATION

BYTE CI2C::SendStart( BOOL Forced )
{  // Generate a Start bit, clean or rude ?
   //Assert SDA==1
   /***
   if(IsWinNT())
   {
      EnablePorts(0x378,0x37F);
      SetFastMode(1);
   }
   ***/
   WSetSDA(1);
   // debug 1/10
   Wait();
   if(WGetSDA()==0) return NOT_IDLE;
   // should not occur, maybe we have to generate a stop bit up to 9?
   Wait();
   if(!WaitSCLHigh()) return SCL_TIMEOUT;
   Wait(); // Delay between stop and start? TBD...
   ////////////
   // The real start sequence
   WSetSDA(0);
   Wait();             // seems better for 4 us delay due to calibration
   WaitHalfClock();    // SDA FallingEdge
   WSetSCL(0);
   Wait();             // SCL low half period

   return 0;
}

BYTE CI2C::SendBit( BYTE bit, BOOL Forced )
{  // Send one data bit, clean or not
   // Assert(SCL==0)
   WSetSCL(0);     // SCL forced low optionnal
   Wait();         // Delay optionnal
   WSetSDA(bit);   // update SDA
   Wait();         // wait half period

   if(!WaitSCLHigh()) return SCL_TIMEOUT;
   // Here is the delay for clock stretching
   WaitHalfClock();// Wait SCL
   // if(GetSDA()!=bit) return ARLOSS;
   WSetSCL(0);
   Wait();

   return 0;
}

BYTE    CI2C::ReadBit(BYTE& Bit)
{       // Read one bit on I2C
        WSetSCL(0);      // SCL forced low
        Wait();          // Delay
        WSetSDA(1);      // Raise SDA, for the other guy to handle it low or not
        Wait();
        WaitSCLHigh();   // Here is the delay for clock stretching ***
        WaitHalfClock(); // Wait SCL
        Bit = WGetSDA(); // Sampling SDA
        WSetSCL(0);      // Add-on
        Wait();

        return 0;
};


BYTE    CI2C::SendStop( BOOL Forced )
{       // Generate a Stop bit, clean or not..
        WSetSCL(0);
        Wait();
        WSetSDA(0);
        Wait();
        if(!WaitSCLHigh()) return SCL_TIMEOUT;
        WaitHalfClock();
        WSetSDA(1);
        WaitHalfClock();
		  /***
        if(IsWinNT())
        {
           DisablePorts(0x378,0x37F);
           SetFastMode(0);
        }
        ***/
        return 0;
}

void    CI2C::ErrorRecovery(BYTE Status)
{       // When an I2C error occur,
        // What we want is to recover any stuck situation...
        for( int i=0; i<9; i++ )  // Maximum 9 stop bits...
        {
            if((WGetSDA()==1)&(WGetSCL()==1)) break;
            SendStop();
        };
}

void    CI2C::NineStop()
{
        for( BYTE i=0; i<9; i++ ) SendStop();
}

void    CI2C::ReleaseBus()
{
    WSetSCL(1);         // SCL forced low
    WSetSDA(1);         // Raise SDA, for the other guy to handle it low or not
}
/////////////////////////////////////
// H/W DEPENDENT LOW LAYER ROUTINES

BOOL    CI2C::WGetSDA() // Working
{
    if( (Inport(PORTBAddr)& SDA) ==0 ) return 1; else return 0;
};

BOOL    CI2C::WGetSCL() // Working
{
   if((Inport(PORTBAddr) & SCL) ==0)
      return 1;
   else return 0;
};

void    CI2C::WSetSDA(BYTE Level)       // Working
{
    if(Level==0) Outport(PORTAAddr,porta |= SDA);
    else Outport(PORTAAddr,porta &= (~SDA));
};

void    CI2C::WSetSCL(BYTE Level)       // Working
{
    if(Level==1) Outport(PORTAAddr,porta &= (~SCL));
    else Outport(PORTAAddr,porta|=SCL);
};


/////////////////////////////////////////////
// TIME DEPENDENT LOW LEVEL ROUTINES


BOOL    CI2C::WaitSCLHigh( INT Delay )  // Timeout delay for polling in milisecond (getcurrenttime)
{
   WORD i;
   // the timeout is 2 msec at 100 kHz; WaitHalfClock is 5 us
   // 2000 / 5 us = 400 times wait halfclock... Get Current Time doesn't work
   WSetSCL(1);     // Want to release SCL anyway

   for(i=0; i<5000; i++ )     // timeout of 400 half bit =
   {
       if(WGetSCL()==1)
          break;
       WaitHalfClock();
   };
   if(i > 1000)
      i=0;

   return (WGetSCL()==1);
};

//////////////////////
// Speed calibration

void    CI2C::WaitHalfClock()   // Wait half clock period for sampling data properly, depends on Set Speed
{
        Wait();
        Wait();
}


void    CI2C::Wait()    // Wait routine, in miliseconds...
{
                // works well during 47 dyas after win95 start time
        BYTE j;
        for(WORD i= 0;i<LoopCounter;i++, j++);
}


WORD    CI2C::GetSpeed()        { return LoopCounter;}; // Get current I2C speed

BOOL    CI2C::SetSpeed( WORD speed ) // Calibration for I2C speed at nominal 100 kHz (no quick speed available)
{
        WORD    NbByte;
        DWORD   Time0, Time;
        BYTE    byte;


        // Fumisterie ici!
        NineStop();

        // 981 bytes around 1000 should be 100 msec.
        for(LoopCounter = 1; LoopCounter<speed; LoopCounter++)
        {
                Time0 = GetCurrentTime();
                for(NbByte=0;NbByte<100;NbByte++)       // Send 100 bytes
                {
                        VoidSendByte( 0xFF );                           // Envoyer FF et NACK                       
                        VoidReadByte( byte, FALSE );
								Time = GetCurrentTime() - Time0;
								if(Time>=18) NbByte = 200; // break;
                };

                // Here 100x9x10 us should have elapsed = 18 msec limit
                Time = GetCurrentTime() - Time0;
                if(Time>=18) break;                                     // We have reached the speed limit!
        };

        LoopCounter++;          // Final evaluation

        /////////////
        // Since we have disturbed the I2C bus,
        // Let's do an error recovery!
        ErrorRecovery(0);

        return TRUE;
}

/////////
// For I2C bus speed calibration

BYTE    CI2C::VoidReadByte( BYTE& byte, BOOL Ack, BOOL Forced ) // Send one data byte, clean or not
{
        BYTE    b0,b1,b2,b3,b4,b5,b6,b7;

        BYTE Status = 0;
        // option here!!!!
        Status |= VoidReadBit(b7);
        Status |= VoidReadBit(b6);
        Status |= VoidReadBit(b5);
        Status |= VoidReadBit(b4);
        Status |= VoidReadBit(b3);
        Status |= VoidReadBit(b2);
        Status |= VoidReadBit(b1);
        Status |= VoidReadBit(b0);
        Status |= VoidSendBit(!Ack);

        byte = b7*128 + b6*64 + b5*32 + b4*16 + b3*8 + b2*4 + b1*2 + b0;

        return Status;
};


BYTE    CI2C::VoidSendByte( BYTE byte, BOOL Forced )    // Read one data byte, clean or not
{
        BYTE Status = 0;
        BYTE ack = 0;

        // option here!!!!
        Status |= VoidSendBit(byte&128);
        Status |= VoidSendBit(byte&64 );
        Status |= VoidSendBit(byte&32 );
        Status |= VoidSendBit(byte&16 );
        Status |= VoidSendBit(byte&8  );
        Status |= VoidSendBit(byte&4  );
        Status |= VoidSendBit(byte&2  );
        Status |= VoidSendBit(byte&1  );
        Status |= VoidReadBit(ack);
        if(ack==1) Status |= BAD_NACK;
        return Status;
};

BYTE    CI2C::VoidSendBit( BYTE bit, BOOL Forced ) // Send one data bit, clean or not
{
        // Assert(SCL==0)
        WSetSCL(1);                             // SCL forced low optionnal
        Wait();         // Delay optionnal

        WSetSDA(1);                     // update SDA
        Wait();         // wait half period

        if(!WaitSCLHigh()) return SCL_TIMEOUT;                  // Here is the delay for clock stretching
        WaitHalfClock();                // Wait SCL 
        // if(GetSDA()!=bit) return ARLOSS;
        WSetSCL(1);
        Wait();

        return 0;
};


BYTE    CI2C::VoidReadBit(BYTE& Bit)    // Read one bit on I2C
{
        WSetSCL(1);                             // SCL forced low
        Wait();         // Delay
        WSetSDA(1);                             // Raise SDA, for the other guy to handle it low or not
        Wait();
        WaitSCLHigh();                  // Here is the delay for clock stretching ***
        WaitHalfClock();                // Wait SCL
        Bit = WGetSDA();                        // Sampling SDA
        WSetSCL(1);                             // Add-on
        Wait();

        return 0;
};

void    CI2C::ChangeConnectSetting(BOOL IsPrinterPort)
{
    m_bIsPrintPort = IsPrinterPort;
};

BOOL    CI2C::GetConnect()
{
    return m_bIsPrintPort;
}

BOOL    CI2C::ConnectPrinterPort(unsigned int PortNum)
{
    if(PortNum == 0x378)
    {
        Lpt = 0;
        Configure();
        m_PrinterPortNum = Port378;
    }
    else if(PortNum == 0x278)
    {
        Lpt = 1;
        Configure();
        m_PrinterPortNum = Port278;
    }
    else if(PortNum == 0x3BC)
    {
        Lpt = 2;
        Configure();
        m_PrinterPortNum = Port3BC;
    }
    return TRUE;
}

int     CI2C::GetPrinterPortNum()
{
    return m_PrinterPortNum;
}

BOOL    CI2C::USBConnect(HANDLE hUSBHandle)
{
    if(USBPort.Open(hUSBHandle,NULL) != STA_OK)
    {
        m_bIsUSBConnect = false;
        return false;
    }
    else
    {
        m_bIsUSBConnect = true;
        return true;
    }
};

BOOL    CI2C::GetUSBStatus()
{
    return m_bIsUSBConnect;
}

void    CI2C::USBClose()
{
    USBPort.Close();
};

void    CI2C::USBReset()
{
    USBPort.Reset();
};

BOOL    CI2C::USBDeviceIsAttached()
{
    return USBPort.IsDeviceAttached();
}
#pragma package(smart_init)

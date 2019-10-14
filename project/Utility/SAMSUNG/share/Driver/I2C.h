//---------------------------------------------------------------------------

#ifndef I2CH
#define I2CH

//#include <vcl.h>
//---------------------------------------------------------------------------

/*
enum PrinterPortNum
{
    Port378,
    Port278,
    Port3BC,
    NotConnect
};

class CI2C
{
public:
    CI2C();
    ~CI2C();

    // Basic Operation function
    void    PrinterPort_StartBit(void);
    void    PrinterPort_ReStartBit(void);
    void    PrinterPort_ReleaseBus(void);
    void    PrinterPort_SendAddress(unsigned char SlaveAddress,unsigned char R_W);
    void    PrinterPort_SendData(unsigned char Data);
    bool    PrinterPort_ReadData(unsigned char *Data);
    void    PrinterPort_StopBit(void);
    bool    PrinterPort_ReadResponce(void);
    void    PrinterPort_SendNAK(void);
    void    PrinterPort_SendACK(void);

    // Common Operation function
    bool    I2CBYTEWrite(unsigned char Slave , unsigned char SubAddress , unsigned char Data);
    bool    I2CBYTERead(unsigned char Slave , unsigned char SubAddress , unsigned char* Data);
    bool    I2CWrite(unsigned char Slave , unsigned char* SubAddress , unsigned char* Data , unsigned char DataLen = 1 , unsigned char SubLen = 1);
    bool    I2CRead(unsigned char Slave , unsigned char* SubAddress , unsigned char* Data , unsigned char DataLen = 1 , unsigned char SubLen = 1);

    //
    void    ChangeConnect(bool bIsPrintPort);
    BOOL    GetConnect();

    BOOL    ConnectPrinterPort(unsigned int PortNum);
    int     GetPrinterPortNum();
    BOOL    ConnectUSB(HANDLE hUSBHandle);
    BOOL    GetUSBStatus();
    BOOL    IsLibraryExist();
    BOOL    LoadPrinterPortLibrary();
private:
    BOOL    m_bIsPrintPort;
    BOOL    m_bIsLibraryExist;
    BOOL    m_bIsUSBConnect;
    HINSTANCE hInst;

    PrinterPortNum m_PrinterPortNum;

    bool (*PROCReadData)(unsigned char *);
    bool (*PROCReadResponce)(void);
    bool (*PROCCheckWaitState)(void);
    void (*PROCSendAddress)(unsigned char,unsigned char);
    void (*PROCSendData)(unsigned char);
    void (*PROCReStartBit)(void);
    void (*PROCStartBit)(void);
    void (*PROCStopBit)(void);
    void (*PROCReleaseBus)(void);
    void (*PROCSendNAK)(void);
    void (*PROCSendACK)(void);
    void (*PROCSetPrintPort)(int);
    void (*PROCClearPrintPort)(void);
    void (*PROCSCLPluse)(void);
    void (*PROCSetBaudRate)(int);
    BOOL (*PROCPassword)(unsigned char);

    static const unsigned char I2C_Write = 0;
    static const unsigned char I2C_Read = 1;

};
*/
//#include <Controls.hpp>
#include "USBPort.h"

// I guess that in single master that's all? Maximum 8 error message simultaneously
// Do we have to specify the nuber of retrials?
// Check the CPU dependencies for the I2C Bus speed.

/////////////////////////////////////////////////////////////////////////////
// CEDID view

enum PrinterPortNum
{
    Port378,
    Port278,
    Port3BC,
    NotConnect
};

class CI2C
{
    // Attributes
public:
    void    Configure(void);
    CI2C();

    BOOL    CheckConnect(void);

    void    SendStream(BYTE *data);
    void    ReadStream(BYTE *data);

    virtual bool __fastcall   I2CWrite(unsigned char Slave , unsigned char* SubAddress , unsigned char* Data , unsigned int DataLen = 1 , unsigned int SubLen = 1);
    virtual bool __fastcall   I2CRead(unsigned char Slave , unsigned char* SubAddress , unsigned char* Data , unsigned int DataLen = 1 , unsigned int SubLen = 1);

///////////////////////////////////////////////
// BYTE LEVEL I2C BUS MANAGEMENT COMMUNICATION
    BYTE    ReadByte( BYTE& byte, BOOL Ack = TRUE, BOOL Forced = FALSE ); // Send one data byte, clean or not
    BYTE    SendByte( BYTE byte, BOOL Forced = FALSE ); // Read one data byte, clean or not
///////////////////////////////////////////////
// BIT LEVEL I2C BUS MANAGEMENT COMMUNICATION
    BYTE    ReadBit(BYTE& Bit);     // Read one bit on I2C
    BYTE    SendStart( BOOL Forced = FALSE );       // Generate a Start bit, clean or rude ?
    BYTE    SendStop( BOOL Forced = FALSE ); // Generate a Stop bit, clean or not..
    BYTE    SendBit( BYTE bit, BOOL Forced = FALSE ); // Send one data bit, clean or not
    void    ErrorRecovery(BYTE Status);             // When an I2C error occur,
    void    NineStop();     // Generate 9 stop bits on the bus
    void    ReleaseBus();
///////////////////////////////////////////////
// I/O H/W INTERFACE LEVEL I2C BUS MANAGEMENT COMMUNICATION
    BOOL    WGetSDA();
    BOOL    WGetSCL();
    void    WSetSDA(BYTE Level = 1);
    void    WSetSCL(BYTE Level = 1);

//HINSTANCE _hDdcLibrary;

///////////////////////////////////////////////
// TIME LEVEL I2C BUS MANAGEMENT COMMUNICATION
    BOOL    WaitSCLHigh( INT Delay = 2 );   // Timeout delay for polling in milisecond (getcurrenttime)
    BOOL    SetSpeed( WORD speed ); // Calibration for I2C speed at nominal 100 kHz (no quick speed available)
    WORD    GetSpeed();     // Get current I2C speed
    inline  void    WaitHalfClock();        // Wait half clock period for sampling data properly, depends on Set Speed
    void    Wait(); // Wait routine, in miliseconds...

/////////
// For speed calibration: Identical functions but no real I2C communication
    BYTE    VoidReadByte( BYTE& byte, BOOL Ack = TRUE, BOOL Forced = FALSE );       // Send one data byte, clean or not
    BYTE    VoidSendByte( BYTE byte, BOOL Forced = FALSE ); // Read one data byte, clean or not
    BYTE    VoidReadBit(BYTE& Bit); // Read one bit on I2C
    BYTE    VoidSendBit( BYTE bit, BOOL Forced = FALSE ); // Send one data bit, clean or not

//////////////////////////
// Internal variables
    WORD    Lpt;            // The selected LTP port (0: disabled, 1=LPT1, 2=LPT2...
    WORD    LoopCounter;    // The adjusted loop counter for speed adjustment... speed calibration
    BYTE    buf;            // The byte buffer for serialization
    BYTE    porta,portb,portc;

    WORD	PORTAAddr,PORTBAddr,PORTCAddr;

// Command & Value
    BYTE    WriteCommand(BYTE Sub_Adr,BYTE Data);

// Connection Selection
    void    ChangeConnectSetting(BOOL IsPrinterPort);
    BOOL    GetConnect();
    BOOL    ConnectPrinterPort(unsigned int PortNum);
    int     GetPrinterPortNum();
    BOOL    USBConnect(HANDLE hUSBHandle);
    BOOL    GetUSBStatus();
    void    USBClose();
    void    USBReset();
    BOOL    USBDeviceIsAttached();
//HANDLE  hUSBHandle;

private:
    BOOL    m_bIsPrintPort;
    BOOL    m_bIsUSBConnect;
    PrinterPortNum m_PrinterPortNum;
    //CUSBPort * USBPort;
};

#endif
 
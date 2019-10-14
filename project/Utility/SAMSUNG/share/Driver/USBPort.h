////////////////////////////////////////////////////////////////
/** 

    Copyright (C) 2006 By Novatek Microelectronics Corp.

    @file 	USBPort.h
    @ingroup DOX_NVT_USB_CMD
    @brief  This function implement a USBPort class, the class instance is realize in library,
      just include the header, then you can use USBPort class.

  	@version    V0.0.1
    @author		Chen Min Zon@n Alvin Lin
    @date		2006/01/10

        2006/07/18 By min_zon
            @n * Modify the status defination.
            @n + Add JTAG commands
            
		2006/7/3 by Alvin 
			@n 1.Implement ISP command
			@n 2.New IIC command
			@n 3.Define error messages

*/////////////////////////////////////////////////////////////////
#ifndef USBPortH
#define USBPortH

#include <Windows.h>
#include <winuser.h>
#pragma hdrstop

//#include "guid9x.h"
#include "NVT_USB_CMD.h"

#define WM_USBATTACH  (WM_USER+1)
#define WM_USBDETACH  (WM_USER+2)

//// Status definitioin ////
//#define STA_OK          (1)
#define STA_OK          STA_JIG_OK

#define STA_ERR         (-1)
#define STA_NODEVICE    (-2)
#define STA_ERR_PARAM   (-3)




#define USB_STA_ERR     (0)

//// /////
#define VCMD_WRITE_DATA     (0)
#define VCMD_READ_DATA      (1)

#define USB_EVENT_ATTACH    (0x0001)
#define USB_EVENT_DETACH    (0x0002)


#define ISP_PORTA       (0)
#define ISP_PORTB       (1)
#define ISP_PORTD       (2)

#define Inp(x)      Inport(x)
#define Outp(x)     Outport(x)

/*
    This is the PNP callback function prototype declare
*/
typedef (*USBPortCB)(int Event, unsigned int Param);

class CUSBPort
{
public:
    CUSBPort(void);
    ~CUSBPort(void);

    int     Open(HANDLE hWinHandle, USBPortCB fnCallback);
    int     Close(void);
    bool    IsDeviceAttached(void);

    bool Reset(void);
    bool SendVendorCmd(unsigned char Request, unsigned short Value, unsigned short Index, void* pBuf, unsigned long * pBufLength, bool GetData);

    void ShowMessage(int msg);
    unsigned char GetJigStatus(unsigned char *Status);
    unsigned char GetVersion(unsigned char *Version);
    unsigned char WriteBuffer(unsigned short Addr,unsigned char *buf,unsigned char Length);
    unsigned char ReadBuffer(unsigned short Addr,unsigned char *buf,unsigned char Length);
    //IO
    unsigned char Outport(unsigned short PortNo,unsigned char Dat);
    unsigned char Inport(unsigned short PortNo,unsigned char *Dat);
    //IIC
    unsigned char IIC_SendStart(unsigned char Channel);
    unsigned char IIC_SendStop(unsigned char Channel);
    unsigned char IIC_SendRepeatStart(unsigned char Channel);
    unsigned char IIC_Tx(unsigned char Channel,unsigned char *buf,unsigned char Length);
    unsigned char IIC_Rx(unsigned char Channel,unsigned char *buf,unsigned char Length);
    unsigned char IIC_WriteBytes(unsigned char Channel,unsigned char Slave,unsigned char Addr,unsigned char *buf,unsigned char Length);
    unsigned char IIC_ReadBytes(unsigned char Channel,unsigned char Slave,unsigned char Addr,unsigned char *buf,unsigned char Length);
    unsigned char IIC_SetSpeed(unsigned char Speed);
    unsigned char IIC_Reset(unsigned char Channel);
    //ISP
    unsigned char ISP_On(unsigned char *ID);
    unsigned char ISP_Off(void);
    unsigned char ISP_ChipErase(void);
    unsigned char ISP_WritePage(unsigned short PageNo,unsigned char *buf);
    unsigned char ISP_ReadPage(unsigned short PageNo,unsigned char *buf,unsigned char New);
    unsigned char ISP_GetCheckSum(unsigned short PageNo,unsigned char *buf);
    unsigned char ISP_GetSram(unsigned short Addr,unsigned char *Data);
    unsigned char ISP_SetSram(unsigned short Addr,unsigned char Data);
    //JTAG
    unsigned char JTAG_Reset(void);
    unsigned char JTAG_ReadBytes(unsigned short Addr, unsigned char * pDataBuf, unsigned int BufSize);
    unsigned char JTAG_WriteBytes(unsigned short Addr, unsigned char * pDataBuf, unsigned int BufSize);

private:

private:
	// User declarations


};

extern CUSBPort USBPort;


//---------------------------------------------------------------------------
#endif  // #define USBPortH

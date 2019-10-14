////////////////////////////////////////////////////////////////
/** 

    Copyright (C) 2006 By Novatek Microelectronics Corp.

    @file 	NVT_USB_CMD.h
    @ingroup DOX_NVT_USB_CMD
    @brief  The file define the USB vendor commands. all these commands
        must co-work with associate firmware.

  	@version
    @author		Chen Min Zon @n Alvin Lin
    @date		2006/01/10

        2006/07/18 By min_zon
            @n * Modify the status defination.
            @n + Add JTAG commands
            
		2006/7/3 by Alvin 
			@n 1.Implement ISP command
			@n 2.New IIC command
			@n 3.Define error messages
*/////////////////////////////////////////////////////////////////

#ifndef _NVT_USB_CMD_
#define _NVT_USB_CMD_


// cypress 68013-SSOP56 there is no port C
#define IO_PORT_A   0       ///< mean A IO port, note there is NO C port.
#define IO_PORT_B   1       ///< mean B IO port, note there is NO C port.
#define IO_PORT_D   2       ///< mean D IO port, note there is NO C port.

// Status ID define
/// The  process status OK
#define STA_JIG_OK				0x00

///IIC return NACK
#define STA_IIC_NACK 			0x01
///IIC bus Hold low
#define STA_IIC_BUS_ABNORMAL 	0x02
///IIC Write progress Fail
#define STA_IIC_WRITE_FAIL 		0x03
///IIC Read progress Fail
#define STA_IIC_READ_FAIL 		0x04

///Flash data compare Fail
#define STA_ISP_COMPARE_FAIL 	0x05
///Flash Erase Fail
#define STA_ISP_ERASE_FAIL 		0x06
///Unknow/Undefined command
#define STA_ISP_CMD_ERROR 		0x07
///ISP handShaking Fail
#define STA_ISP_HANDSHAKE_FAIL 	0x08
///ISP in busy state
#define STA_ISP_BUSY 			0x09
///ISP time out
#define STA_ISP_TIME_OUT 		0x0a

///USB state OK
#define STA_USB_OK				STA_JIG_OK
#define STA_USB_OFFSET          0x10
#define STA_USB_NO_DEVICE		(STA_USB_OFFSET + 1)
#define STA_USB_ERROR			(STA_USB_OFFSET + 2)
#define STA_USB_ERR_PARAM		(STA_USB_OFFSET + 3)

/// the JTAG access ok
#define STA_JTAG_OK             STA_JIG_OK
#define STA_JTAG_OFFSET         0X20
#define STA_JTAG_ERROR          (STA_JTAG_OFFSET + 1)       ///< There are error condition on JTAG function.

///IIC speed setting
#define IIC_200K	0
///IIC speed setting
#define IIC_150K	1
///IIC speed setting
#define IIC_120K	2
///IIC speed setting
#define IIC_100K	3
///IIC speed setting
#define IIC_80K		4
///IIC speed setting
#define IIC_70K		5
///IIC speed setting
#define IIC_60K		6
///IIC speed setting
#define IIC_55K		7
///IIC speed setting
#define IIC_50K		8

/////////////////////////////////////////////////////
/*
     USB vendor request(command), 1 bytes.
     @n The MSB of Command:
        @n 0: Read associate commands
        @n 1: Write or simple commmands.
*/
#define USBRQT_WRITE_MULTIBYTES (0xf0)	//reserved
#define USBRQT_READ_MULTIBYTES (0xf1)	//reserved

////////////////////////////////////////////////////////
/**
    get device status.
    @n wValue: which destination.
       @n 0x0000: The first I2C channel device.
       @n 0x0001: The Second I2c channel device.
       @n 0xFFFF: for USB parer.
    @n wIndex: not defined.
    @n wLength[in]: n bytes. the return status.
*/
#define USBRQT_GET_STATUS	(0x00)

////////////////////////////////////////////////////////
/**
    through I2C, Read one byte form slave client device,
    @n wValue: Bit0~7:  Channel,
    @n         Bit8~15:  SlaveAddess
    @n wIndex: SubAddress.
    @n wLength[in]:the read data length.
*/
#define USBRQT_IIC_READ_BYTES	(0x01)

////////////////////////////////////////////////////////
/**
    through I2C, Write one byte to slave client device,
    @n wValue: Bit0~7:  Channel,
    @n         Bit8~15:  SlaveAddess
    @n wIndex: SubAddress.
    @n wLength[in]:the write data length.
*/

#define USBRQT_IIC_WRITE_BYTES	(0x02)


////////////////////////////////////////////////////////
/**
    Read port data
    @n wValue: Bit8~15: Reserved
    @n         Bit0~7:  Which Port (Valid Value : IO_PORT_A, IO_PORT_B or IO_PORT_D)
    @n wIndex: Reserved
    @n wLength: 1, port data
*/
#define USBRQT_IN_PORT	(0x03)


////////////////////////////////////////////////////////
/**
    Write port data
    @n wValue: Bit8~15: Reserved
    @n         Bit0~7:  Which Port (Valid Value : IO_PORT_A, IO_PORT_B or IO_PORT_D)
    @n wIndex: Reserved

    @n wLength: 1, port data
*/
#define USBRQT_OUT_PORT	(0x04)

////////////////////////////////////////////////////////
/**
    IIC send start
    @n wValue: Bit0~7:  Channel,
    @n wIndex: Reserved

    @n wLength: 1
*/
#define USBRQT_IIC_SEND_START	(0x05)

////////////////////////////////////////////////////////
/**
    IIC send stop
    @n wValue: Bit0~7:  Channel,
    @n wIndex: Reserved

    @n wLength: 1
*/
#define USBRQT_IIC_SEND_STOP	(0x06)

////////////////////////////////////////////////////////
/**
    IIC send repeat start
    @n wValue: Bit0~7:  Channel,
    @n wIndex: Reserved

    @n wLength: 1
*/
#define USBRQT_IIC_REPEAT_START	(0x07)

////////////////////////////////////////////////////////
/**
    IIC send byte
    @n wValue: Bit0~7:  Channel,
    @n wIndex: Reserved

    @n wLength[in]:64[max],the write data length.
*/
#define USBRQT_IIC_TX	(0x08)

////////////////////////////////////////////////////////
/**
    IIC read byte
    @n wValue: Bit0~7:  Channel,
    @n wIndex: Reserved

    @n wLength[in]:64[max],the read data length.
*/
#define USBRQT_IIC_RX	(0x09)

////////////////////////////////////////////////////////
/**
    BUFFER assign data to buffer 
    @n wValue: Traget address [0~512]
    @n wIndex: Reserved

    @n wLength: 64[MAX],data
*/
#define USBRQT_WRITETO_BUFFER	(0x0a)

////////////////////////////////////////////////////////
/**
    BUFFER read buffer
    @n wValue: Traget address [0~512]
    @n wIndex: Reserved

    @n wLength: 64[MAX],data
*/
#define USBRQT_READOUT_BUFFER	(0x0b)


////////////////////////////////////////////////////////
/**
    Set IIC speed
    wValue: delay loops
*/
#define USBRQT_SET_IIC_SPEED	(0x0c)

////////////////////////////////////////////////////////
/**
    Reset IIC
*/
#define USBRQT_RESET_IIC	(0x0d)

////////////////////////////////////////////////////////
/**
    Reset ALL
*/
#define USBRQT_RESET_ALL	(0x0e)


////////////////////////////////////////////////////////
/**
    Get Jig FW version
    @n wLength: 1,version
*/
#define USBRQT_GET_FW_VERSION	(0x0f)



////////////////////////////////////// NVT JTAG Command //////////////////////////////////////
////////////////////////////////////////////////////////
/**
    Call JTAG reset function
    
    @n wValue(2st,3st): Reserved
    @n wIndex(4st,5st): Reserved
    @n wLength(6st,7st): Reserved
*/
#define USBRQT_JTAG_RESET           (0x20)


////////////////////////////////////////////////////////
/**
    Read one byte to specified address
    
    @n wValue(2st,3st): Bit0~7: start Address
    @n         Bit8~15: Reserved
    @n wIndex(4st,5st): Reserved
    @n wLength(6st,7st): Reserved
*/
#define USBRQT_JTAG_READ_BYTE       (0x21)

////////////////////////////////////////////////////////
/**
    Write one byte to specified address
    
    @n wValue: Bit0~7: start Address
    @n         Bit8~15: Reserved
    @n wIndex: Bit0~7: Data
    @n         Bit8~15: Reserved
    @n wLength: Reserved
*/
#define USBRQT_JTAG_WRITE_BYTE      (0x22)


////////////////////////////////////// NVT ISP Command //////////////////////////////////////
/**
		ISP on
		@n wValue: 	retry count
		@n wIndex: 	Reserved
		@n wLength: 	1	
*/
#define USBRQT_ISP_ON (0x80)

//============================================
/**
		ISP off
		@n wValue: 	Reserved
		@n wIndex: 	Reserved
		@n wLength: 	1	
*/
#define USBRQT_ISP_OFF (0x81)

//============================================
/**
		ISP chip erase
		@n wValue: 	Reserved
		@n wIndex: 	Reserved
		@n wLength: 	1	
*/
#define USBRQT_ISP_CHIP_ERASE (0x82)

//============================================
/**
		ISP write page
		@n wValue: 	(Word)page no.
		@n wIndex: 	Reserved
		@n wLength: 	1,page	(write Buffer[512] to flash)
*/
#define USBRQT_ISP_WRITE_PAGE (0x83)

//============================================
/**
		ISP get page
		@n wValue: 	(Word)page no.
		@n wIndex: 	Reserved
		@n wLength: 	1,	(read flash data to buffer[512])
*/
#define USBRQT_ISP_READ_PAGE (0x84)

//============================================
/**
		ISP write SRAM
		@n wValue: 	(Word)Address
		@n wIndex: 	Reserved
		@n wLength: 	1 ,data	
*/
#define USBRQT_ISP_WRITE_SRAM (0x85)

//============================================
/**
		ISP read SRAM
		@n wValue: 	(Word)Address
		@n wIndex: 	Reserved
		@n wLength: 	1 ,data	
*/
#define USBRQT_ISP_READ_SRAM (0x86)

//============================================
/**
		ISP get checksum
		@n wValue: 	(Word)page no.
		@n wIndex: 	Reserved
		@n wLength: 	1 ,data	
*/
#define USBRQT_ISP_GET_CHECKSUM (0x87)


#endif // _NVT_USB_CMD_

 

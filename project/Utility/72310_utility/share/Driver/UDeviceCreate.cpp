//---------------------------------------------------------------------------


#pragma hdrstop
#include <vcl.h>
#include "Forms.hpp"
#include "UDeviceCreate.h"
#include "U72310Device.h"
#include "UFrame_RegView.h"
#include "U72312Device.h"
#include "U72312Chip.h"
#include "UProtocol.h"
#include "UI2CProtocol.h"
#include "UDSUProtocol.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
I2CDevice * DeviceCreate::CreateDevice(Byte slave, Con_Type iType)
{
	I2CDevice * Dev;

    Dev = new Dev_72310("NT72310");
    if(iType == conIIC)
    {
        //oPro = new I2CProtocol();
    }
    else if(iType == conDSU)
    {
        oPro = new DSUProtocol();
    }
    Dev->SetProtocol(oPro);
    Dev->SetSlave(slave);

    return Dev;
}
//---------------------------------------------------------------------------
I2CDevice * DeviceCreate::CreateDevice(AnsiString name, Byte slave, Con_Type iType)
{
	I2CDevice * Dev;

    if(iType == conIIC)
    {
        oPro = new I2CProtocol();
    }
    else if(iType == conDSU)
    {
        oPro = new DSUProtocol();
    }

    if (name == "NT72310")
    {
        Dev = new Dev_72310(name);
    }else
    if (name == "NT72312")
    {
        Dev = new Dev_72312_FPGA(name);
    }else
    if (name == "NT72312C")
    {
        Dev = new Dev_72312_Chip(name);
    }

    Dev->SetProtocol(oPro);
    Dev->SetSlave(slave);

    return Dev;
}
//---------------------------------------------------------------------------

bool DeviceCreate::CreateUSBConnection()
{
    return oPro->CreateConnect();
}

TMEMCFrame * CreateFrame(String name)
{
    return NULL;
}

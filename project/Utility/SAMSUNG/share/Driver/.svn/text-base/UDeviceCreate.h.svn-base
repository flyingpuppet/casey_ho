//---------------------------------------------------------------------------

#ifndef UDeviceCreateH
#define UDeviceCreateH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <dstring.h>
#include "I2CDevice.h"
#include "UMEMCFrame.h"
#include "I2C.h"

enum Con_Type{conIIC, conDSU} ;

class DeviceCreate : public TObject
{
    private:
        CProtocol * oPro;
    public:
        I2CDevice * CreateDevice(Byte slave, Con_Type iType = conDSU);
        I2CDevice * CreateDevice(AnsiString name, Byte slave, Con_Type iType = conDSU);
        TMEMCFrame * CreateFrame(String name);
        bool CreateUSBConnection();
};


#endif

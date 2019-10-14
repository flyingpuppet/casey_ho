#ifndef _DCTRLMANAGERINTERFACE_H
#define _DCTRLMANAGERINTERFACE_H

#ifdef _DYNCTRLMANAGER_EXPORT
 #define  _DYNCTRLMANAGERDLL __declspec(dllexport)
#else
 #define  _DYNCTRLMANAGERDLL __declspec(dllimport)
#endif

class I2CDeviceInterface;
class IDCtrlManagerInterface
{
public:
    virtual void ShowDCtrlManager(HWND handle, I2CDeviceInterface *pI2CDevice) = 0;
};

extern "C" _DYNCTRLMANAGERDLL IDCtrlManagerInterface *  __stdcall GetDynamCtrlManager();

#endif
 
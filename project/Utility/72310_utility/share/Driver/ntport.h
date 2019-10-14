/*
NTPort Library
Copyright © 1997-2002 Hai Li, Zeal SoftStudio.
E-Mail: support@zealsoftstudio.com
Web: http://www.zealsoftstudio.com
*/
#ifndef NTPort

#define NTPort

#ifndef WINAPI
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Returns a value indicating the last operation is successful or not.
int APIENTRY GetLastState(char *s);

// Enable your application to read or write specific ports.
void APIENTRY EnablePorts(WORD PortStart, WORD PortStop);

// Disable your application to read or write specific ports.
void APIENTRY DisablePorts(WORD PortStart, WORD PortStop);

// Returns a value indicates whether the application is running under Windows NT/2000 system.
BOOL APIENTRY IsWinNT();

// Returns a value from specific ports.
WORD APIENTRY Inp(WORD PortNum);
WORD APIENTRY Inport(WORD PortNum);
WORD APIENTRY Inpw(WORD PortNum);
WORD APIENTRY InportW(WORD PortNum);
DWORD APIENTRY Inpd(WORD PortNum);
DWORD APIENTRY InportD(WORD PortNum);

// Write a value to specific ports.
//void APIENTRY Outp(WORD PortNum, WORD Data);
void APIENTRY Outport(WORD PortNum, WORD Data);
void APIENTRY Outpw(WORD PortNum, WORD Data);
void APIENTRY OutportW(WORD PortNum, WORD Data);
void APIENTRY Outpd(WORD PortNum, DWORD Data);
void APIENTRY OutportD(WORD PortNum, DWORD Data);

// Set the registration information.
void APIENTRY LicenseInfo(LPSTR sUserName, DWORD sKey);

// Returns the version of NTPort Library.
WORD APIENTRY GetNTPortVersion();

// Set the setting of fast mode
void APIENTRY SetFastMode(BOOL bOption);

// Get the current setting of fast mode
BOOL APIENTRY GetFastMode();

// Get the base address of LPT port
WORD APIENTRY GetLPTPortAddress(WORD PortNo);

const ERROR_NONE = 0;
const ERROR_DRIVER = 2;
const ERROR_SCM_CANT_CONNECT = 9998;

#ifdef __cplusplus
}
#endif

#endif
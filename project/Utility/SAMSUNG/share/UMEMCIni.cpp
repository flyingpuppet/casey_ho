//---------------------------------------------------------------------------


#pragma hdrstop

#include "UMEMCIni.h"

#pragma package(smart_init)

//---------------------------------------------------------------------------
/*__fastcall TMEMCIniFile::TMEMCIniFile():TIniFile()
{

} */
//---------------------------------------------------------------------------
__fastcall TMEMCIniFile::TMEMCIniFile(const AnsiString FileName):TIniFile(FileName)
{
    
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::ReadICType(AnsiString &Name)
{
    Name = ReadString("Utility", "ICTYPE", "NT72310");
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::ReadSlaveAddress(Byte &addr)
{
    AnsiString str;
    ReadSlaveAddress(str);
    addr = str.ToInt();
}
void __fastcall TMEMCIniFile::ReadSlaveAddress(AnsiString &addr)
{
    addr = ReadString("Utility", "SlaveAddress", "0x34");
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::ReadIICSpeed(int &speed)
{
    speed = ReadInteger("Utility", "IICSpeed", 50);
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::ReadICIndex(int &index)
{
    index = ReadInteger("Utility", "ICIndex", 0);    
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::ReadIICIndex(int &index)
{
    index = ReadInteger("Utility", "IICIndex", 0);    
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::ReadConType(int &type)
{
    type = ReadInteger("Utility", "ConType", 0);    
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::WriteICType(AnsiString Name)
{
    WriteString("Utility","ICTYPE", Name);
    UpdateFile();
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::WriteSlaveAddress(Byte addr)
{
    AnsiString str;
    str = "0x"+IntToHex(addr,2);
    this->WriteSlaveAddress(str);
}
void __fastcall TMEMCIniFile::WriteSlaveAddress(AnsiString addr)
{
    WriteString("Utility","SlaveAddress",addr);
    UpdateFile();
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::WriteIICSpeed(int speed)
{
    WriteInteger("Utility", "IICSpeed", speed);
    UpdateFile();
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::WriteICIndex(int index)
{
    WriteInteger("Utility", "ICIndex", index);
    UpdateFile();    
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::WriteIICIndex(int index)
{
    WriteInteger("Utility", "IICIndex", index);
    UpdateFile();    
}
//---------------------------------------------------------------------------
void __fastcall TMEMCIniFile::WriteConType(int type)
{
    WriteInteger("Utility", "ConType", type);
    UpdateFile();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#ifndef UMEMCIniH
#define UMEMCIniH

#include <IniFiles.hpp>

//---------------------------------------------------------------------------
class TMEMCIniFile : TIniFile
{
    public:
        //__fastcall TMEMCIniFile():TIniFile();
        __fastcall TMEMCIniFile(const AnsiString FileName);
        
    public:
        void __fastcall ReadICType(AnsiString &Name);
        void __fastcall ReadSlaveAddress(AnsiString &addr);
        void __fastcall ReadSlaveAddress(Byte &addr);
        void __fastcall ReadIICSpeed(int &speed);
        void __fastcall ReadICIndex(int &index);
        void __fastcall ReadIICIndex(int &index);
        void __fastcall ReadConType(int &type);

        void __fastcall WriteICType(AnsiString Name);
        void __fastcall WriteSlaveAddress(Byte addr);
        void __fastcall WriteSlaveAddress(AnsiString addr);
        void __fastcall WriteIICSpeed(int speed);
        void __fastcall WriteICIndex(int index);
        void __fastcall WriteIICIndex(int index);
        void __fastcall WriteConType(int type);
};
#endif

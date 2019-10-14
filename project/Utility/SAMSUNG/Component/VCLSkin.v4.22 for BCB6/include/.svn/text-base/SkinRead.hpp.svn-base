// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SkinRead.pas' rev: 6.00

#ifndef SkinReadHPP
#define SkinReadHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Dialogs.hpp>	// Pascal unit
#include <WinConvert.hpp>	// Pascal unit
#include <FileCtrl.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Skinread
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct TSkinHeader
{
	int Version;
	int DirLen;
	int U1;
	int U2;
} ;
#pragma pack(pop)

class DELPHICLASS TSkinReader;
class PASCALIMPLEMENTATION TSkinReader : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	Classes::TStringList* Dir;
	int dirlen;
	int Num;
	int sizes[1001];
	Classes::TMemoryStream* ms;
	TSkinHeader header;
	TSkinHeader header2;
	__fastcall TSkinReader(void);
	__fastcall virtual ~TSkinReader(void);
	bool __fastcall loadfromfile(const AnsiString aname);
	void __fastcall readfile(AnsiString aname, Classes::TMemoryStream* m);
	void __fastcall readIni(const AnsiString aname, Classes::TMemoryStream* m, AnsiString &fname);
	void __fastcall Decompress(Classes::TStream* source, Classes::TStream* Dest);
	bool __fastcall Loadfromstream(Classes::TMemoryStream* r2);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Skinread */
using namespace Skinread;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SkinRead

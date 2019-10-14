// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WinSkinMenu.pas' rev: 6.00

#ifndef WinSkinMenuHPP
#define WinSkinMenuHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <WinSkinData.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Winskinmenu
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TWinSkinPopMenu;
class PASCALIMPLEMENTATION TWinSkinPopMenu : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	void *FPrevWndProc;
	void *FObjectInst;
	bool done;
	void __fastcall WinWndProc(Messages::TMessage &aMsg);
	void __fastcall Default(Messages::TMessage &Msg);
	void __fastcall AddLog(const Messages::TMessage &Msg);
	void __fastcall WMPrint(Messages::TMessage &Msg);
	void __fastcall WMPrintClient(Messages::TMessage &Msg);
	void __fastcall UpdateMenu(Messages::TMessage &Msg);
	void __fastcall NcPaint(Messages::TMessage &Msg);
	void __fastcall WMERASEBKGND(Messages::TMessage &Msg);
	
public:
	unsigned hwnd;
	Winskindata::TSkinData* fsd;
	int SelIndex;
	Graphics::TBitmap* MenuBg;
	HMENU hmenu;
	bool crop;
	HRGN clientRgn;
	bool ownerdraw;
	__fastcall TWinSkinPopMenu(void);
	__fastcall virtual ~TWinSkinPopMenu(void);
	void __fastcall InitSkin(unsigned ahwnd, Winskindata::TSkinData* afsd, HMENU amenu);
	void __fastcall UnSubClass(void);
};


//-- var, const, procedure ---------------------------------------------------
#define c_menuprop "WinSkinPopMenu"
extern PACKAGE TWinSkinPopMenu* newskinmenu;

}	/* namespace Winskinmenu */
using namespace Winskinmenu;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WinSkinMenu

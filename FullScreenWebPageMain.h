// ---------------------------------------------------------------------------

#ifndef FullScreenWebPageMainH
#define FullScreenWebPageMainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.OleCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "Registry.hpp"

#include "FullScreenWebPageDocHandler.h"
#include "FullScreenWebPageMouseMove.h"
#include "FullScreenWebPageOnMouseMoveDispatch.h"

#include "UtilsMisc.h"

#include "SHDocVw_OCX.h"
#include "mshtml.h"

// ---------------------------------------------------------------------------
class TMain : public TForm, public IMouseMove {
	bool _DisableHideCursor;

	bool _Fullscreen;

__published: // IDE-managed Components

	TPopupMenu *PopupMenu;
	TMenuItem *miMainClose;
	TCppWebBrowser *CppWebBrowser;
	TMenuItem *miMainAbout;
	TMenuItem *miSeparator01;
	TTimer *TimerHideCursor;
	TMenuItem *miMainFullscreen;
	TMenuItem *miSeparator02;

	void __fastcall miMainCloseClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall CppWebBrowserTitleChange(TObject *Sender, BSTR Text);
	void __fastcall miMainAboutClick(TObject *Sender);
	void __fastcall TimerHideCursorTimer(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
		int X, int Y);

	void __fastcall CppWebBrowserDocumentComplete(TObject *Sender,
		LPDISPATCH pDisp, Variant *URL);
	void __fastcall miMainFullscreenClick(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall miSeparator01Click(TObject *Sender);

private: // User declarations

	static const FormEdges[][4];

	static const int LeftEdge = 0;
	static const int RightEdge = 1;
	static const int TopEdge = 2;
	static const int BottomEdge = 3;

	void __fastcall SetDisableHideCursor(bool Value);
	bool __fastcall GetDisableHideCursor();

	void __fastcall SetFullscreen(bool Value);
	bool __fastcall GetFullscreen();

	TDocHandler *DocHandler;

	bool CompatibleEdge;

	void MouseMoveEvent();

	static void UpdateFeatureBrowserEmulation();

public: // User declarations

	__fastcall TMain(TComponent* Owner);

	__property bool DisableHideCursor = {
		write = SetDisableHideCursor, read = GetDisableHideCursor};

	__property bool Fullscreen = {write = SetFullscreen, read = GetFullscreen};
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif

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

__published: // IDE-managed Components

	TPopupMenu *PopupMenu;
	TMenuItem *miMainClose;
	TCppWebBrowser *CppWebBrowser;
	TMenuItem *miMainAbout;
	TMenuItem *miSeparator01;
	TTimer *TimerHideCursor;

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

private: // User declarations

	void __fastcall SetDisableHideCursor(bool val);
	bool __fastcall GetDisableHideCursor();

	TDocHandler *DocHandler;

	void MouseMoveEvent();

	static void UpdateFeatureBrowserEmulation();

public: // User declarations

	__fastcall TMain(TComponent* Owner);

	__property bool DisableHideCursor = {
		write = SetDisableHideCursor, read = GetDisableHideCursor};
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif

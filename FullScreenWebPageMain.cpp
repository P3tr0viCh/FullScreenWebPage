// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FullScreenWebPageMain.h"

#include <AboutFrm.h>

#include <UtilsStr.h>
#include <UtilsFileIni.h>
#include <UtilsMisc.h>
// ---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
// ---------------------------------------------------------------------------

TMain *Main;
// ---------------------------------------------------------------------------

__fastcall TMain::TMain(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall TMain::miMainCloseClick(TObject *Sender) {
	Close();
}
// ---------------------------------------------------------------------------

WNDPROC OldPopupWndProc;
// ---------------------------------------------------------------------------

LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_ENTERMENULOOP:
		Main->DisableHideCursor = true;
		break;
	case WM_EXITMENULOOP:
		Main->DisableHideCursor = false;
		break;
	}
	return CallWindowProc(OldPopupWndProc, hWnd, msg, wParam, lParam);
}
// ---------------------------------------------------------------------------

void __fastcall TMain::FormCreate(TObject *Sender) {
	UpdateFeatureBrowserEmulation();

	TFileIni* FileIni = TFileIni::GetNewInstance();

	String Url = FileIni->ReadString("Settings", "Url", "");

	bool HideCursor = FileIni->ReadBool("Settings", "HideCursor", true);

	CompatibleEdge = FileIni->ReadBool("Settings", "CompatibleEdge", false);

	delete FileIni;

	Fullscreen = true;

	if (IsEmpty(Url)) {
		// TODO
	}
	else {
		DocHandler = new TDocHandler(PopupMenu);

		CppWebBrowser->Navigate(Url.w_str());

		while (CppWebBrowser->Busy) {
			Application->ProcessMessages();
		}

		ICustomDoc *CustomDoc;
		CppWebBrowser->Document->QueryInterface(&CustomDoc);
		if (CustomDoc) {
			CustomDoc->SetUIHandler(DocHandler);
		}

		if (HideCursor) {
			TimerHideCursor->Enabled = true;
		}
	}

	OldPopupWndProc = (WNDPROC)SetWindowLong(PopupList->Window, GWL_WNDPROC,
		(LONG)PopupWndProc);
}
// ---------------------------------------------------------------------------

void __fastcall TMain::FormDestroy(TObject *Sender) {
	SetWindowLong(PopupList->Window, GWL_WNDPROC, (LONG)OldPopupWndProc);

	if (DocHandler) {
		DocHandler->Release();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMain::CppWebBrowserTitleChange(TObject *Sender, BSTR Text) {
	Caption = Text;
}
// ---------------------------------------------------------------------------

void __fastcall TMain::miMainAboutClick(TObject *Sender) {
	DisableHideCursor = true;

	Fullscreen = false;
	
	ShowAbout(14, 0);

	DisableHideCursor = false;
}
// ---------------------------------------------------------------------------

void __fastcall TMain::TimerHideCursorTimer(TObject *Sender) {
	TimerHideCursor->Enabled = false;
	Screen->Cursor = crNone;
}
// ---------------------------------------------------------------------------

void __fastcall TMain::FormMouseMove(TObject *Sender, TShiftState Shift, int X,
	int Y) {
	MouseMoveEvent();
}
// ---------------------------------------------------------------------------

void TMain::MouseMoveEvent() {
	if (DisableHideCursor) {
		return;
	}
	Screen->Cursor = crDefault;
	TimerHideCursor->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TMain::CppWebBrowserDocumentComplete(TObject *Sender,
	LPDISPATCH pDisp, Variant *URL) {
	IHTMLDocument2 *lpHtmlDocument = NULL;
	CppWebBrowser->Document->QueryInterface(IID_IHTMLDocument2,
		(LPVOID*) &lpHtmlDocument);

	TOnMouseMoveDispatch *pMMDisp = new TOnMouseMoveDispatch(this);

	VARIANT vDocDisp;
	vDocDisp.vt = VT_DISPATCH;
	vDocDisp.pdispVal = pMMDisp;

	lpHtmlDocument->put_onmousemove(vDocDisp);

	lpHtmlDocument->Release();
}
// ---------------------------------------------------------------------------

void __fastcall TMain::SetDisableHideCursor(bool Value) {
	_DisableHideCursor = Value;

	if (_DisableHideCursor) {
		TimerHideCursor->Enabled = false;
		Screen->Cursor = crDefault;
	}
	else {
		TimerHideCursor->Enabled = true;
	}
}
// ---------------------------------------------------------------------------

bool __fastcall TMain::GetDisableHideCursor() {
	return _DisableHideCursor;
}
// ---------------------------------------------------------------------------

// Left, Right, Top, Bottom
const int TMain::FormEdges[][4] = { {0, 0, 0, 0}, {2, 2, 2, 2}};
// ---------------------------------------------------------------------------

void __fastcall TMain::SetFullscreen(bool Value) {
	_Fullscreen = Value;

	miMainFullscreen->Checked = _Fullscreen;

	if (_Fullscreen) {
		FormStyle = fsStayOnTop;

		BorderStyle = bsNone;

		SetBounds(-FormEdges[CompatibleEdge][LeftEdge],
			-FormEdges[CompatibleEdge][TopEdge],
			Screen->Width + FormEdges[CompatibleEdge][LeftEdge] +
			FormEdges[CompatibleEdge][RightEdge],
			Screen->Height + FormEdges[CompatibleEdge][TopEdge] +
			FormEdges[CompatibleEdge][BottomEdge]);
	}
	else {
		FormStyle = fsNormal;

		BorderStyle = bsSizeable;

		SetBounds(100, 100, Screen->Width - 200, Screen->Height - 200);
	}
}
// ---------------------------------------------------------------------------

bool __fastcall TMain::GetFullscreen() {
	return _Fullscreen;
}
// ---------------------------------------------------------------------------

int GetIEVersion() {
	String sVersion = NULL;

	TRegistry *reg = new TRegistry();
	if (reg) {
		reg->RootKey = HKEY_LOCAL_MACHINE;
		if (reg->OpenKeyReadOnly("SOFTWARE\\Microsoft\\Internet Explorer")) {
			if (reg->ValueExists("svcVersion")) {
				sVersion = reg->ReadString("svcVersion");
			}
			else {
				sVersion = reg->ReadString("Version");
			}
			reg->CloseKey();
		}
		delete reg;
	}
	else {
		return -1;
	}

	if (IsEmpty(sVersion)) {
		return -1;
	}

	int P = sVersion.Pos(".");

	if (P > 0) {
		sVersion = sVersion.SubString(0, sVersion.Pos(".") - 1);
	}

	if (IsEmpty(sVersion)) {
		return -1;
	}

	try {
		return StrToInt(sVersion);
	}
	catch (...) {
		return -1;
	}
}
// ---------------------------------------------------------------------------

void WriteFeatureBrowserEmulation(int Version) {
	TRegistry *reg = new TRegistry();
	if (reg) {
		reg->RootKey = HKEY_LOCAL_MACHINE;

		reg->RootKey = HKEY_CURRENT_USER;

		if (reg->OpenKey
			("SOFTWARE\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION",
			true)) {
			reg->WriteInteger(ExtractFileName(Application->ExeName), Version);
			reg->CloseKey();
		}
		delete reg;
	}
}
// ---------------------------------------------------------------------------

void TMain::UpdateFeatureBrowserEmulation() {
	int Version = GetIEVersion();

	int EmulatedVersion;

	if (Version < 8) {
		EmulatedVersion = -1;
	}
	else {
		switch (Version) {
		case 8:
			EmulatedVersion = 8888;
			break;
		case 9:
			EmulatedVersion = 9999;
			break;
		case 10:
			EmulatedVersion = 10001;
			break;
		case 11:
		default:
			EmulatedVersion = 11001;
			break;
		}
	}

	if (EmulatedVersion > 0) {
		WriteFeatureBrowserEmulation(EmulatedVersion);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMain::miMainFullscreenClick(TObject *Sender) {
	Fullscreen = !miMainFullscreen->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TMain::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Shift.Empty() && Key == VK_ESCAPE && Fullscreen) {
		Fullscreen = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMain::miSeparator01Click(TObject *Sender) {
	// TODO:
	// Workaround: CPPWebBrowser перехватывает нажати€ кнопок и
	// FormKeyUp не вызываетс€

	if (Fullscreen) {
		Fullscreen = false;
	}
}
// ---------------------------------------------------------------------------

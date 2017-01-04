//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <System.Win.ComServ.hpp>
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("FullScreenWebPageMain.cpp", Main);
//---------------------------------------------------------------------------
#pragma link "System.Win.ComServ"

static Comserv::TCppActiveXModule _ax_module(true);

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "FullScreenWebPage";
		Application->CreateForm(__classid(TMain), &Main);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

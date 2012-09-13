#include "stdafx.h"

#include "MyApplication.h"

#define MYSETTINGS_REG_KEY "Software\\Playrix Entertainment\\EngineTest"
#define MYWINDOW_CLASS_NAME "ENGINETEST_CLASS"
#define MYAPPLICATION_NAME "Engine Test"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	bool isFullscreen = false;
	std::string str, name, value;
	Core::log.Init("./log.htm", true);

	File::c_file initFile("settings.ini");
	if (initFile.is_open())
	{
		str = initFile.getline();
		if (utils::ReadNvp(str, name, value) && name == "path")
		{
			File::cd(value);
		}
		str = initFile.getline();
		if (utils::ReadNvp(str, name, value) && name == "fullscreen")
		{
			isFullscreen = utils::lexical_cast<bool>(value);
		}
	}

	HWND findWin = NULL;
	findWin = FindWindow(MYWINDOW_CLASS_NAME, MYAPPLICATION_NAME);
	if (findWin == NULL)
	{
		if (CheckDXVersion())
		{
			MyApplication App(hInstance, nCmdShow, isFullscreen);
			App.enableCustomCursor = false;
			App.showFps = true;
			App.maxFps = 0;
			App.SETTINGS_REG_KEY = MYSETTINGS_REG_KEY;
			App.APPLICATION_NAME = MYAPPLICATION_NAME;
			App.WINDOW_CLASS_NAME = MYWINDOW_CLASS_NAME;
			App.Init(true);
			App.Start();
			App.ShutDown();
		}
	}
	else
	{
		SetForegroundWindow(findWin);
		SetFocus(findWin);
		UpdateWindow(findWin);
	}
	
	return 0;
}

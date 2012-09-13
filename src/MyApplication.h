#pragma once

#include "SplashesWidget.h"
#include "TestWidget.h"
#include "MyWidget.h"

namespace MyLua {

}

extern bool needLoadScreen;

class MyApplication: public Core::Application
{
public:
	MyApplication(HINSTANCE hInstance, int nCmdShow, bool fullscreenMode) :
	  Application(hInstance, nCmdShow, fullscreenMode)
	  {
		  //name = "Test";
		  showFps = true;
	  }

	virtual ~MyApplication()
	  {
	  }

	virtual void Splashes()
	{
		needLoadScreen = false;
		Core::guiManager.LoadLayers("Splashes.xml");
		needLoadScreen = true;

		Core::mainScreen.pushLayer(Core::guiManager.getLayer("Splashes"));

		//Core::LuaDoFile("gui.lua");

		if(loadScreen != NULL) {
			loadScreen->Init();
		}

		timer.Start();

		bool bLoop = splashesLoop = mainLoop = true;

		bool bMessageRecieved;
		while (bLoop) 
		{
			bLoop = splashesLoop;
			MSG message;
			if (isPaused)
			{
				if (mainLoop) bMessageRecieved = (GetMessage(&message, NULL, NULL, NULL)!=0);
			}
			else
			{
				bMessageRecieved = (PeekMessage(&message,NULL,0,0,PM_REMOVE)!=0);
			}
			if(bMessageRecieved 
#ifdef USE_CONSOLE
				&& !IsDialogMessage(debugConsole._dialog, &message)
#endif
				) 
			{
				cursor->setNormal();
				if(message.message != WM_QUIT) 
				{ 
					TranslateMessage(&message);
					DispatchMessage(&message);
				} 
				else 
				{
					mainLoop = false;
					bLoop = false;
				}
			}
			else 
			{
				if (/*!isPaused &&*/ !Render::device.isLost())
				{

					if(wnd->needChangeMode) {
						if(wnd->getWindowMode() == Core::Window::fullscreen) {
							setFullscreenMode(false);
							wnd->SetMode(Core::Window::windowed);
						} else {
							setFullscreenMode(true);
							wnd->SetMode(Core::Window::fullscreen);
						}
						wnd->needChangeMode = false;
					}

					if (Core::controllerKernel.isAdded)
					{
						Core::controllerKernel.addQueuedController();
					}

					float dt = timer.getElapsedTime();
					if (dt>0.1f)
					{
						dt = 0.1f;
					}

					timer.Start();

					Core::mainScreen.Update(dt);
					Core::guiManager.Update(dt);

					Render::device.BeginScene();
					Render::device.Begin2DMode();
					Core::mainScreen.Draw();
					Render::device.End2DMode();
					Render::device.EndScene();

					if (Core::controllerKernel.isAdded)
					{
						Core::controllerKernel.addQueuedController();
					}
				}
			}
		}
		Core::mainScreen.Clear();
		//Core::LuaCallVoidFunction("ResetFadeScreens");
		Core::guiManager.getLayer("Splashes")->getWidget("Splashes")->AcceptMessage(Message("Release"));
	}

	virtual void LoadResources()
	{
		Core::LuaDoFile("startup.lua");
	}

	virtual void ScriptMap()
	{
		using namespace luabind;
		/*
		module(Core::luaState)
			[
				class_<GameInfo>("GameInfo")
				.def("setMusicVolume", &GameInfo::setMusicVolume)
				.def("getMusicVolume", &GameInfo::getMusicVolume)
				.def("setSoundVolume", &GameInfo::setSoundVolume)
				.def("getSoundVolume", &GameInfo::getSoundVolume)
			];
			*/
		Application::ScriptMap();
		//object luaGlobal = get_globals(Core::luaState);
		//luaGlobal["gameInfo"] = &gameInfo;
	}

	virtual void RegisterTypes() {
		Application::RegisterTypes();

		REGISTER_WIDGET_XML(SplashesWidget, "SplashesWidget");
		REGISTER_WIDGET_XML(TestWidget, "TestWidget");
		REGISTER_WIDGET_XML(MyWidget, "MyWidget");
	}

	virtual LayerObject* LoadLayerObject(Xml::TiXmlElement* objElem)
	{
		return Application::LoadLayerObject(objElem);
	}

	virtual void setFullscreenMode(bool fs)
	{
	}

	virtual void DrawFps()
	{
		if(!Render::isFontLoaded("arial")) return;
		Render::BindFont("arial");
		int x = Render::device.Width() - 5;
		int y = Render::device.Height() - 20;
		Render::PrintString(x, y, std::string("fps ")+utils::lexical_cast(currentFps), 1.0f, RightAlign);
		Render::PrintString(x, y-20, std::string("Vm ")+utils::lexical_cast(Render::device.GetVideoMemUsage())+std::string("M"), 1.0f, RightAlign);
		Render::PrintString(x, y-40, std::string("Am ")+utils::lexical_cast(MM::manager.GetMemUsage())+std::string("K"), 1.0f, RightAlign);
	}

};
#pragma once

#include "Render/Texture.h"
#include "Timer.h"
#include "LoadScreen.h"
#include "cursor.h"

class LayerObject;

namespace Core
{
	class Window;
}

namespace Core
{
/// Класс приложения
class Application
{

private:

	friend class Window;

	friend class DebugConsole;

	bool _loading;
		// Загружаемся ли;
		// этот флаг нужен во время загрузки, чтобы:
		// * игнорировать паузу;
		// * жестко выходить по требованию пользователя.

	float _dt;
	float _sleep_time;

protected:
	Window* wnd;
	HINSTANCE _hInstance;
	int cmdShow;

	bool isFullscreen;
	bool showCustomCursor;
	int currentFps;
	long _resourceCounter;

	void GetCursorProperties();

	HCURSOR arrowCursor;
	HCURSOR handCursor;

	bool mainLoop;

	string _keyMap[91];
	LoadScreen* loadScreen;

	void WriteComputerInfo();

public:
	bool _saveGfxFileInfo;
	Cursor *cursor;
	
	bool enableCustomCursor;
	bool showFps;
	bool isPaused;
	bool splashesLoop;
	int maxFps;

	Timer timer;

	/// путь в реестре для программы (должно быть заполнено до вызова Init())
	std::string SETTINGS_REG_KEY;
	/// название окна программы (должно быть заполнено до вызова Init())
	std::string APPLICATION_NAME;
	/// класс окна программы (должно быть заполнено до вызова Init())
	std::string WINDOW_CLASS_NAME;
	/// ширина графики игры (должно быть заполнено до вызова Init())
	int GAME_CONTENT_WIDTH;
	/// высота графики игры (должно быть заполнено до вызова Init())
	int GAME_CONTENT_HEIGHT;

	/// если true, то игра будет запускаться в родном разрешении GAME_CONTENT_WIDTHxGAME_CONTENT_HEIGHT
	/// если false, то в случае несовпадения AspectRatio игры и экрана, будут черные полосы по краям
	/// либо сверху-снизу, либо с боков (должно быть заполнено до вызова Init())
	bool FORCE_USE_NATIVE_RESOLUTION;

	/// конструктор
	Application(HINSTANCE hInstance, int nCmdShow, bool fullscreenMode, LoadScreen* ls = 0);
	/// деструктор
	virtual ~Application();

	Window* getMainWindow();

	/// Инициализация генератора случайных чисел таймером.
	void Randomize();

	/// первичная инициализация (не может выполняться в конструкторе, ибо вызывает виртуальные методы).
	/// Можно загружать ресурсы (LoadResources) в ниточке если задать threaded
	/// Этот метод должен быть вызван до Start().
	void Init(bool threaded=false);
	/// основной цикл приложения
	void Start();
	virtual void Update(float dt);
	void CloseWindow();
	/// деинициализация системы
	void ShutDown();
	void LoadKeyMap();

	void DrawCursor();
	bool IsFullscreen();

	/// установка привязок к Lua, должен быть вызван из наследника при переопределении
	virtual void ScriptMap();

	/// обновление экрана загрузки (если есть)
	virtual void UpdateLoadScreen();

	/// регистрация классов в фабрике, должен быть вызван из наследника при переопределении
	virtual void RegisterTypes();

	/// загрузка слоёного объекта
	virtual LayerObject* LoadLayerObject(Xml::TiXmlElement* elem);

	/// вызывается при переключении полноэкранного режима с помощью Alt-Enter
	/// для того, чтобы программа могла мониторить текущее состояние
	virtual void setFullscreenMode(bool);

	/// Показ сплэш экранов, если нужно.
	/// Вызывается из Init().
	virtual void Splashes() {}

	/// Загрузка ресурсов до основной части (НЕбывает отдельным потоком).
	/// Вызывается из Init().
	virtual void PreloadResources() {};
	
	/// Основная загрузка ресурсов (может быть отдельным потоком).
	/// Вызывается из Init().
	virtual void LoadResources() {}

	/// Отрисовка экрана игры
	virtual void PreDraw() {}
	virtual void Draw();
	virtual void PostDraw() {}

	/// Отрисовка эффекта паузы. Вызывается из Draw.
	virtual void DrawPause();

	/// Можно переопределить для отрисовки какой-либо информации в краях экрана,
	/// оставленных пустыми для сохранения Aspect Ratio.
	virtual void DrawBoxBars() {}

	/// Отрисовка FPS, можно (и нужно) переопределять
	virtual void DrawFps() {}
	
	/// Вернуть текущий fps
	int getCurrentFps();

	/// установить(true)/снять(false) паузу
	virtual void SetPause(bool pause);

	/// задать новый LoadScreen или отключить передав NULL
	void SetLoadScreen(LoadScreen* ls);

	/// Завершить приложение
	void Stop();

	/// Сказать, что приложение загружено.
	/// Вызывается из движкового кода, поэтому в игре нет особой необходимости вызывать его.
	/// Может быть переопределено с целью отложить момент окончания загрузки.
	virtual void SetLoaded();
	bool IsLoading() { return _loading; }

	long GetResourceCounter() { return _resourceCounter; }

	// Вызывается при смене режима экрана
	virtual void SetModeCallback();
	
	// Для совместимости с айфоном
	virtual bool IsLiteVersion() {
		return false;
	}
};

extern Application* appInstance;

}

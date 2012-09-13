#pragma once

#include "LoadScreen.h"
#include "Core/Timer.h"
#include "Utils/Vector3.h"

namespace Core {
	class LoadScreen;
};

class LayerObject;

bool isRetina();

namespace Core
{
/// Класс приложения
class Application
{
private:
	
protected:

	int currentFps;
	long _resourceCounter;

	std::string _keyMap[91];
	LoadScreen* loadScreen;
	static std::string locale;
	math::Vector3 accel, accel_lo, accel_hi;
	float rotateOrientation, rotateOrientationPrev, rotateTime;
	bool invertMouse;
	bool _loading;
	std::string debugString;

public:

    static std::string name;
	
	bool showFps;
	bool isPaused;
	bool splashesLoop;
	int  maxFps;

	static int cmdShow;

	Timer timer;

	/// путь в реестре для программы (должно быть заполнено до вызова Init())
	std::string SETTINGS_REG_KEY;
	/// название окна программы (должно быть заполнено до вызова Init())
	std::string APPLICATION_NAME;

	/// конструктор
	Application(LoadScreen* ls = 0);
	/// деструктор
	virtual ~Application();

	/// первичная инициализация (не может выполняться в конструкторе, ибо вызывает виртуальные методы).
	/// Этот метод должен быть вызван до Start().
	// layer must be a CAEAGLLayer
	void Init(void *layer);
	/// основной цикл приложения
	void Start();
	void MainLoop();
	void CloseWindow();
	/// деинициализация системы
	void ShutDown();
	void LoadKeyMap();
	/// Завершить приложение
	void Stop();
	
	void setAccelerationData(float x, float y, float z);
	void setAngle(float a);
	void setMousePos(float x, float y);
	void updateMousePos(float x, float y);
	void setDebugString(const std::string&);

	bool IsFullscreen();
	/// установка привязок к Lua, должен быть вызван из наследника при переопределении
	virtual void ScriptMap();
	/// обновление экрана загрузки (если есть)
	virtual void UpdateLoadScreen();
	/// Обновление экрана загрузки слоя (если есть)
	virtual void UpdateResourceUploadObserver();
	/// Инициализация экрана загрузки слоя (если есть)
	virtual void InitResourceUploadObserver();
	/// регистрация классов в фабрике, должен быть вызван из наследника при переопределении
	virtual void RegisterTypes();
	/// загрузка слоёного объекта
	virtual LayerObject* LoadLayerObject(Xml::TiXmlElement* elem);
	/// вызывается при переключении полноэкранного режима с помощью Alt-Enter
	/// для того, чтобы программа могла мониторить текущее состояние
	virtual void setFullscreenMode(bool);
	/// Показ сплэш экранов, если нужно.
	/// Вызывается из Init().
	virtual void Splashes();
	/// Загрузка ресурсов до основной части (НЕбывает отдельным потоком).
	/// Вызывается из Init().
	virtual void PreloadResources() {};
	/// Основная загрузка ресурсов (может быть отдельным потоком).
	/// Вызывается из Init().
	virtual void LoadResources();
	/// Отрисовка экрана игры
	virtual void Draw();
	/// Отрисовка эффекта паузы. Вызывается из Draw.
	virtual void DrawPause();
	/// Вернуть текущий fps
	int getCurrentFps() {
		return currentFps;
	};
	virtual void Update(float /*dt*/) {}
	void SetLoaded();
	bool IsLoading();

	long GetResourceCounter() { return _resourceCounter; }
	// Вызывается при смене режима экрана
	virtual void SetModeCallback() {}
	
	// Находимся ли в лайт-версии
	// Эта функция помещена именно в Application, ибо мы всегда знаем, что Core::appInstance существует когда нужно
	virtual bool IsLiteVersion();
	
};

extern Application* appInstance;

}

#ifndef _CORE_SCREEN_H_
#define _CORE_SCREEN_H_

#include "Spline.h"
#include <deque>
class Layer;

namespace Core
{

///
/// Экран
///
class ScreenImpl 
{

private:
	
	typedef std::vector<Layer*> LayerList;
	typedef LayerList::iterator LayerIterator;
	/// список слоёв
	LayerList _layers;
	Layer* debugLayer;
	/// Режим обработки пачки слоёв (LayerPack::mode)
	enum {
		/// Фейд замещает собой стек
		L_REPLACE = 0, 
		/// Фэйд добавляется в стек, а не замещают его
		L_APPEND, 
		/// Фэйд убирается
		L_REMOVE
	};
public:
	/// тип эффекта замещения
	/// описание по битам:
	/// 9 - pretty move (with bounce)
	/// 8 - time, 0 - 0.5s, 1 - 1.0s
	/// 7 - enable alpha
	/// 6 - enable zoom
	/// 5 - enable move
	/// 4 - reserved
	/// 3 - reserved
	///                  move enabled                                  zoom enabled
	/// 2 \  000 - move up, 001 - up-right, 010 - right    | 000 - zoom out, 001 - zoom in, 
	/// 1  } 011 - right-down, 100 - down, 101 - down-left | 010 - big zoom out, 011 - small zoom in
	/// 0 /  110 - left, 111 - left-up                     | 1xx - zoom with rotate
	enum {
		FADE_PRETTY_BIT = 0x0200,
		FADE_LONGTIME = 0x0100,
		FADE_ALPHA = 0x0080,
		FADE_ZOOM  = 0x0040,
		FADE_MOVE  = 0x0020,
		FADE_MODE_7 = 0x0007,
		FADE_MODE_6 = 0x0006,
		FADE_MODE_5 = 0x0005,
		FADE_MODE_4 = 0x0004,
		FADE_MODE_3 = 0x0003,
		FADE_MODE_2 = 0x0002,
		FADE_MODE_1 = 0x0001,
		FADE_MODE_0 = 0x0000,
		FADE_IMMEDIATELY = 0
	};
private:
	typedef struct LayerPack {
		float fadetime;
		/// тип эффекта замещения
		/// описание по битам:
		/// 15-10 - reserved
		/// 9 - pretty move (with bounce)
		/// 8 - time, 0 - 0.5s, 1 - 1.0s
		/// 7 - enable alpha
		/// 6 - enable zoom
		/// 5 - enable move
		/// 4 - reserved
		/// 3 - reserved
		///                  move enabled                                  zoom enabled
		/// 2 \  000 - move up, 001 - up-right, 010 - right    | 000 - zoom out, 001 - zoom in, 
		/// 1  } 011 - right-down, 100 - down, 101 - down-left | 010 - big zoom out, 011 - small zoom in
		/// 0 /  110 - left, 111 - left-up                     | 1xx - zoom with rotate
		int fadeType;
		std::string luaFunc;
		int mode;
		LayerList layers;
	} LayerPack;
	std::deque<LayerPack> _fadelayers;

	/// сохранённые слои
	LayerList _savedLayers;
	
	int _savedFadeScreens;
	/// включены альтернативные слои
	bool _alternative; 
	/// процесс замены альтернативных слоёв
	bool alternativing;
	bool _oldAlternative;
	bool delayedAlternative;
	
	TimedSplinePath pretty;
		
	float _fadeTime;
		// время эффекта перехода при добавлении и удалении слоев
	
	//
	// Инициализировать верхний слой
	//
	void InitActiveLayer();
	
	void InternalDraw(const LayerList& layers, float scale = 1.f, float angle = .0f);

	static std::string GetDebugLine(const LayerList& layers);

public:
	
	///
	/// Конструктор
	///
	ScreenImpl();
	
	///
	/// Деструктор
	///
	~ScreenImpl();
	
	///
	/// Обработать сообщения (вызывается из application)
	///
	void ProcessMessages();
	
	///
	/// Функция рисования
	///
	void Draw();
	
	/// Отрисовать только нижние слои
	void DrawLowerLayers();
	/// Отрисовать только верхние слои (те которые в эффектах, они рисуются без альфы и прочих бантиков)
	void DrawUpperLayers();

	///
	/// Рисует отладочный экран
	///
	void DrawDebugScreen(std::string fontName);
	
	///
	/// Вернуть следующий за верхним слой
	///
	Layer* GetSecondLayer();
	
	///
	/// Вернуть верхний слой
	///
	Layer* GetTopLayer();
	
	///
	/// Очистить ТОЛЬКО стек слоев
	/// Извне используется только в Application
	///
	void ClearLayers();

	///
	/// Очистить экран
	///
	void Clear();
	
	///
	/// Затолкать слой в стек
	///
	void pushLayer(Layer* layer);
	void pushLayer(const std::string& layerName);
	
	/// Заменить весь текущий стек на заданный слой (fadeType - эффект перехода)
	/// По окончании перехода вызывается заданная lua функция
	void fadeToLayer(Layer* layer, std::string luaFunc = "", int fadeType = 0);
	void fadeToLayer(const std::string& layerName, std::string luaFunc = "", int fadeType = 0);
	
	/// Добавить в стек заданный слой (fadeType - эффект добавления)
	/// По окончании добавления вызывается заданная lua функция
	void appendLayer(Layer* layer, std::string luaFunc = "", int fadeType = 0);
	void appendLayer(const std::string& layerName, std::string luaFunc = "", int fadeType = 0);
	
	// Добавить слой в отдельном потоке, вызвать luaFunc по окончании
	// Внимание: тестировалось только на iPhone, на других платформах может не работать
	void appendLayerThreaded(std::string layerName, std::string luaCommand, int fadeType = 0);
	
	/// Убрать из стека верхний слой (fadeType - эффект убирания)
	/// По окончании убирания вызывается заданная lua функция
	void eliminateLayer(std::string luaFunc = "", int fadeType = 0);

	/// Убрать из стека N верхних слоёв (fadeType - эффект убирания)
	/// По окончании убирания вызывается заданная lua функция
	void eliminateLayers(int n, std::string luaFunc = "", int fadeType = 0);

	/// Убрать из стека слой с заданным названием (fadeType - эффект убирания)
	/// По окончании убирания вызывается заданная lua функция
	void eliminateLayer(const std::string& layerName, std::string luaFunc = "", int fadeType = 0);
	
	/// Установить данный слой для отладочной информации. Этот слой будет получать копии всех сообщений.
	/// Допускается передавать null.
	void setDebugLayer(Layer* layer);
	void setDebugLayer(const std::string& layerName);
	///
	/// Вернуть имя верхнего лейера
	/// (не рекомендуется использовать,
	/// в большинствве случаев лучше вызывать GetTopLayer())
	///
	std::string getMainLayerName();
	
	///
	/// Выплюнуть слой
	///
	void popLayer();
	
	///
	/// Реакция на течение времени
	///
	void Update(float dt);

	///
	/// Удаляет первый (ближайший к игроку) лейер с таким именем
	///
	void RemoveLayer(const std::string&);

	///
	/// сохранить слои, которые находятся на экране
	///
	void SaveLayers();

	///
	/// вернуть сохранённые слои
	///
	void RestoreLayers();
	
	void SetScaleToAllLayers(float scale);
	bool isLayerOnScreen(const std::string &layerName);
	/// Включён ли режим альтернативных слоёв
	bool isAlternative();
	/// Включить/выключить режим альтернативных слоёв
	void setAlternative(bool a);
	
	/// Обработка мышы и клавиатуры
	void MouseMove(const IPoint& mousePos);
	/// Обработка мышы и клавиатуры
	void MouseDown(const IPoint& mousePos);
	/// Обработка мышы и клавиатуры
	void MouseDoubleClick(const IPoint& mousePos);
	/// Обработка мышы и клавиатуры
	void KeyPress(int keyCode);
	/// Обработка мышы и клавиатуры
	void MouseUp(const IPoint& mousePos);
	/// Обработка мышы и клавиатуры
	void MouseWheel(int delta);
	/// Экран не реагирует на ввод пользователя
	bool isLocked();
	
	// Возвращает информацию о текущих слоях (для отладки)
	std::string GetDebugInfo();
	
	// Устанавливает время эффекта перехода для добавления и удаления слоев
	void SetFadeTime(float fadeTime);
};

extern ScreenImpl mainScreen;

} // namespace Core

#endif

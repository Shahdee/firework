#pragma once

#include "WidgetObserver.h"
#include "MessageManager.h"

#include "Application.h"

namespace Core
{

class InputSystemImpl 
{
	friend class Window;
	friend class Singleton<InputSystemImpl>;

	int _mouse_x,
		_mouse_y;

	bool _mouse_left_button;
	bool _mouse_right_button;
	bool _mouse_middle_button;

	bool _key_press[255];

	// сумма передвижений колёсика мыши
	// так-то оно должно быть кратно 120,
	// но если вдруг у кого не так -
	// то перемещения будут суммироваться
	// пока не окажутся больше 120 или меньше -120
	int _wheelSum;

public:
	InputSystemImpl();
	~InputSystemImpl();

	void GetMousePos(int& mouse_x, int& mouse_y);
	IPoint GetMousePos();
	bool GetMouseLeftButton();
	bool GetMouseRightButton();
	bool GetKeyState(int key_code);
	void SetKeyState(int key_code, bool key_state);

	// только обновляет координаны
	void SetMouseCoords(int mouse_x, int mouse_y);
	// обновляет координаты и вызывает MouseMove
	void UpdateMouseCoords(int mouse_x, int mouse_y);
	void KeyPressed(int key_code);
	void MouseLeftButtonDown();
	void MouseLeftButtonUp();
	void MouseRightButtonDown();
	void MouseRightButtonUp();
	void MouseDoubleClick();
	/// Пришло событие "повёрнуто колёсико мыши"
	void MouseWheel(int delta);
	/// Зажат ли Shift
	bool IsShiftKeyDown();
	/// Зажат ли Ctrl
	bool IsControlKeyDown();

	//
	// Зажата ли клавиша с кодом virtualKey.
	//
	bool IsKeyDown(int virtualKey);

	//
	// Включена ли клавиша с кодом virtualKey;
	// актуально для клавиш CapsLock, NumLock, ScrollLock.
	//
	bool IsKeyToggledOn(int virtualKey);
};

extern InputSystemImpl mainInput;

}

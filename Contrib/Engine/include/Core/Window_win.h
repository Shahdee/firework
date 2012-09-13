#pragma once

namespace Core
{

class Window
{
public:

	enum window_mode {
		fullscreen,
		windowed
	};

private:

	IRect _workArea;
	std::string _className;
	window_mode _mode;

	void GetWorkArea();

	static LRESULT CALLBACK WindowFuncStub(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT WindowFunction(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	IRect CalculateSizes(window_mode mode, DWORD style, DWORD exStyle);

protected:
	Window()
		: _className("")
		, _mode(windowed)
		, needChangeMode(false)
		, hWnd(0)
	{
	}
public:

	/// этим флагом окно сообщает, что пользователь хочет переключить режим
	bool needChangeMode;
	HWND hWnd;

	Window(window_mode wmode, std::string caption, std::string className);
	~Window();
	void Destroy();

	void SetMode(window_mode mode);
	window_mode getWindowMode();

	IRect GetClientSizes();

	bool IsCursorIn();

};

}
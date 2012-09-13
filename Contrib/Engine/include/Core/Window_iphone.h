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

	static bool _key_press[255];

	static int desktopWidth;
	static int desktopHeight;

public:
	static bool hasDestroy;
	/// этим флагом окно сообщает, что пользователь хочет переключить режим
	static bool needChangeMode;
	static int clientOffset;

	unsigned int width, height;

	Window(window_mode wmode, std::string APPLICATION_NAME);
	~Window();

	void Destroy();
	void SetMode(window_mode mode);
	window_mode getWindowMode();
};

}
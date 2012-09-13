#ifndef _PLATFORM_WIN_H_
#define _PLATFORM_WIN_H_

#include <string>

namespace utils
{

void MakeWindowForeground(HWND window);

//���������� �������. �������� �� ���������, ����������� ������� SingleInstance(������: �������� �����)
bool SwitchToPreviousInstance(LPCTSTR uniqueStr, LPCTSTR wndClass, LPCTSTR wndCaption);

void CenterWindow(HWND window);

float GetScreenDpiScale();

bool IsWindows_95_98();

//����� ��� �������� ������������� ���� ����������.
//������ ��������� � ������������ � �������� �� ������ ��������.
class SingleInstance {
public:
	SingleInstance(const std::string &name, const std::string &wndClass, const std::string &wndCaption);
	~SingleInstance();

	bool Check() const;

private:
	HANDLE _mutex;
	std::string _name;
	std::string _wndClass;
	std::string _wndCaption;
	bool _alreadyRunnging;
};

}
#endif

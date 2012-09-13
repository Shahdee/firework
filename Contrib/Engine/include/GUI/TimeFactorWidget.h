#pragma once

#include "GUI/Widget.h"

namespace GUI {

//
// ������, ���������� �� ���������/���������� �������
// � �� ����������� ��������������� ����������.
// �������� ���: ��� ������� ���� � ������� Ctrl �������� (��� ���������)
// ����� � ������� �� ��������� ����� ��������������� �������.
// 
class TimeFactorWidget
	: public Widget
{

public:

	// ����������� - ������ �� XML
	TimeFactorWidget(const std::string& name, Xml::TiXmlElement* xmlElement);

	// ������
	virtual void Draw();

	// ���������
	virtual void Update(float dt);

	// ������� �� �������� �������� ����
	virtual void MouseWheel(int delta);

private:

	const float SHOW_TIME;
		// ����� ������ �������

	const float HIDE_TIME;
		// ����� ������� �������

	float _timer;
		// ������

	std::string _textFormat;
		// ������ ������

	IPoint _position;
		// ������� ������;
		// ����� ������ ����� ������ �������� �������, ������� �� _textFormat;

	enum {
		
		STATE_HIDDEN,
			// ��������� "�� ���������� ������"

		STATE_SHOWING,
			// ��������� "���������� �������"

		STATE_HIDING,
			// ��������� "�������� ������� ������"

	} _state;
		// ������� ���������

	TText _text;
		// �����, ������� �������;
		// ����������, ����� �� ��������� ������ ����

	// �������� ������� � ������� ����������
	void ShowTitle();

};

} // namespace GUI

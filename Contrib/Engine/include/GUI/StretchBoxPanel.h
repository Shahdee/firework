#ifndef _GUI_STRETCHBOXPANEL_H_
#define _GUI_STRETCHBOXPANEL_H_

#include "Widget.h"
#include "StretchBox.h"

// Панель с растягивающейся текстурой
// в xml описывать так:
// <StretchBoxPanel name="Some" mouse_active="true">
//   <box texture="texname" top="10" bottom="10" left="10" right="10"/>
//   <position x="100" y="100" width="200" height="200"/>
// </StretchBoxPanel>
// Параметры top, bottom и т.д. задают размер фиксированной части текстуры, которая не подвергнется растягиванию

// Есть расширенный вариант задания фиксированных и растягивающихся частей:
// внутрь тега box вставить конструкцию вида
// <verticalStripes>
//   <stripe size="20" type="fixed"/>
//   <stripe size="60" type="stretched"/>
//   ...
// полученный список задаёт горизонтальные полосы, указывая их высоту и тип
// аналогичная конструкция <horizontalStripes> задаёт вертикальные полосы в горизонтальном направлении
// Полосы начинаются от левого нижнего угла.
// С помощью расширенной формы можно задавать текстуру с некоторыми элементами, искажать которые нежелательно
// Возможно так же смешивать сокращённую и расширенную форму, например задать left, right и verticalStripes

namespace GUI
{

class StretchBoxPanel : public Widget
{
	StretchBox box;

	// TODO: режим, в котором панель будет ресайзиться под размер вложенных виджетов.

public:

	StretchBoxPanel(const std::string& name, Xml::TiXmlElement* xmlElement);
	virtual ~StretchBoxPanel() {}

	virtual void Draw();
	virtual bool CheckPoint(const IPoint& point);
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void MouseUp(const IPoint& mouse_pos);
};

}

#endif // _GUI_STRETCHBOXPANEL_H_
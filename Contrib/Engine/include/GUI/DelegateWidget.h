#ifndef _GUI_DRAWDELGATEWIDGET_H_
#define _GUI_DRAWDELGATEWIDGET_H_

#include "GUI/Widget.h"

namespace GUI {

//
// Виджет, делегирующий другому виджету следующие виртуальные методы:
//  * Draw() (
//  * MouseDown() (используется QueryState)
//  * MouseUp()
//  * MouseMove()
//  * MouseDoubleClick()
//  * MouseWheel
//
// Описание выглядит так:
// <DelegateWidget
//    layer="QuestLayer"
//    widget="QuestWidgetName"
//    messagePrefix="Above"
//    Draw="true"
//    MouseDown="true"
//    MouseUp="true"
// />
//
// По умолчанию (если не указать атрибут с названием метода), методы не делегируются.
// Если конкретный метод делегируется, виджету посылается сообщение в AcceptMessage с именем
// _messagePrefix + <имя виджета>. Исключение - метод MouseDown, он посылает сообщение в QueryMessage
// и ожидает на выходе либо Message("true") либо Message("false").
//
class DelegateWidget
	: public GUI::Widget
{

public:
	
	//
	// Конструктор
	//
	DelegateWidget(const std::string& name, Xml::TiXmlElement* xe);

private:

	std::string _layerName;
		// имя слоя, куда отправляем сообщение

	std::string _widgetName;
		// имя виджета, куда отправляем сообщение

	std::string _messagePrefix;
		// префикс сообщения (при посылке дополняется именем метода)

	bool _delegateDraw;
		// делегируем ли функцию Draw

	bool _delegateMouseDown;
		// делегируем ли функцию MouseDown

	bool _delegateMouseUp;
		// делегируем ли функцию MouseUp

	bool _delegateMouseMove;
		// делегируем ли функцию MouseMove

	bool _delegateMouseDoubleClick;
		// делегируем ли функцию MouseDoubleClick

	bool _delegateMouseWheel;
		// делегируем ли функцию MouseWheel

	GUI::Widget* _cachedWidget;
		// закешированное значение указателя на виджет

	//
	// Объявления делегируемых функций
	//
	virtual void Draw();
	virtual bool MouseDown(const IPoint& mouse);
	virtual void MouseUp(const IPoint& mouse);
	virtual void MouseMove(const IPoint& mouse);
	virtual void MouseDoubleClick(const IPoint& mouse);
	virtual void MouseWheel(int delta);

	//
	// Функция получения виджета;
	// кеширует значение.
	//
	GUI::Widget* GetWidget();
};

} // namespace GUI

#endif
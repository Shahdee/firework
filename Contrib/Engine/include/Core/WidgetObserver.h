#ifndef _CORE_WIDGETOBSERVER_H_
#define _CORE_WIDGETOBSERVER_H_

#include "GUI/Widget.h"
#include "Layer.h"

namespace Core {

class WidgetObserver 
{
private:
	Layer* _layer;
	// раньше здесь была карта виджетов :)
public:
	WidgetObserver();
	void Clear();
	void SetLayer(Layer* layer);
	void MouseMove(const IPoint& mousePos);
	void MouseDown(const IPoint& mousePos);
	void MouseDoubleClick(const IPoint& mousePos);
	void KeyPress(int keyCode);
	void MouseUp(const IPoint& mousePos);
	void MouseWheel(int delta);
};

//extern WidgetObserver widgetObserver;

} // namespace Core

#endif

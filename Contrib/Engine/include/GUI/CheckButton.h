#pragma once

#include "GUI/Widget.h"

#include "Render/Texture.h"

namespace GUI
{

class CheckButton : public Widget
{
	IPoint _textPosition;

    Render::Texture* _check;
	Render::Texture* _on_check;

	bool _state;

public:
	CheckButton(string name_, string str_, IPoint pos_, string font_, float fontScale_, IPoint textPos_, bool state_);
	CheckButton(string name_, Xml::TiXmlElement* xmlElement);
	~CheckButton();

	virtual void Draw();
	virtual bool MouseDown(const IPoint& mouse_pos);

	virtual void AcceptMessage(const Message& message);
	virtual Message QueryState(const Message& message) const;
};

}
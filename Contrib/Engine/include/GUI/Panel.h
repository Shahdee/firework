#pragma once
#include "widget.h"

#include "Render/Texture.h"

namespace GUI
{

class Panel : public Widget
{
	Render::Texture* _texture;
	bool noInput;
	bool _flippedHor;
		// развернута ли текстура по горизонтали
public:

	Panel(const string &name_, Xml::TiXmlElement* xmlElement);
	virtual ~Panel();

	virtual void Draw();
	virtual bool MouseDown(const IPoint &mouse_pos);
	virtual void MouseMove(const IPoint &mouse_pos);
	virtual void AcceptMessage(const Message& message);
};

}
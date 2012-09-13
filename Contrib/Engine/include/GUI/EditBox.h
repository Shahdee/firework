#ifndef _GUI_EDITBOX_H_
#define _GUI_EDITBOX_H_

#include "widget.h"

namespace GUI
{

class EditBox
	: public Widget
{
protected:

	std::string _text;

	std::string _font;

	int _limit;

	float _timer;

public:

	EditBox(std::string name_, Xml::TiXmlElement* xmlElement);

	~EditBox();

	void Update(float dt);

	virtual void Draw();

	virtual void AcceptMessage(const Message& message);

	virtual Message QueryState(const Message& message) const;

};

}

#endif

#pragma once

#include "Widget.h"
#include "Core/ControllerManager.h"

namespace GUI
{

class TextList : public Widget
{
	friend class ScrollTextController;

	std::list<string> _item_list;
	typedef std::list<string>::iterator item_iterator;
	typedef std::list<string>::const_iterator item_const_iterator;

	string _activeFont;
	string _normalFont;

	string _buttonUpName;
	string _buttonDownName;

	int _string_step;
	int _num_strings;
	int _start_string;

	int _offset;
	int _alpha;

	int _choosed_string;

	bool _isScrolled;

	class ScrollTextController : public IController
	{
	public:
		enum ScrollDirect
		{
			Up,
			Down
		};

	private:
		TextList* _list;
		ScrollDirect _dir;
		float _speed;

	public:

		ScrollTextController(TextList* list, ScrollDirect dir, float speed = 0.2f);
		virtual ~ScrollTextController();

		virtual void Update(float dt);
		virtual bool isFinish();
	};

public:
	TextList(const string& name_, Xml::TiXmlElement* xmlElement);
	~TextList();
	void pushItem(const string& item);
	void eraseItem(const string& item);
	void clear();

	void SetActive(const string& item);
	void UpdateButtons(void);

	virtual void Draw();
	virtual void MouseDoubleClick(const IPoint& mouse_pos);
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void AcceptMessage(const Message& message);
	virtual Message QueryState(const Message& message) const;

};

}

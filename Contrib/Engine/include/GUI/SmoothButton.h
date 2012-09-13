#include "types.h"
#include "GUI/Widget.h"

#include "Render/Texture.h"
#include "SmoothTextureChanger.h"

namespace GUI
{

class SmoothButton : public Widget
{
	float _enableTimer;
	/*string _fontNormal;
	string _fontPress;
	string _fontActive;
	string _fontDeactive;*/

	float _scaleFont;
	IPoint _textPosition;
	Text textPressed;

	RectOrient _orient;

	Render::Texture* _boardNormal;
	Render::Texture* _boardPress;
	Render::Texture* _boardActive;
	Render::Texture* _boardDeactive;

	SmoothTextureChanger *_smooth;

	bool _isActive, _useSound;
public:
	static float ENABLE_TIMER;
public:
	SmoothButton(string name_, Xml::TiXmlElement* xmlElement);

	virtual ~SmoothButton();

	virtual void Draw();
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void MouseUp(const IPoint& mouse_pos);
	virtual void AcceptMessage(const Message& message);
	virtual void MouseMove(const IPoint& mouse_pos);
	virtual void Update(float dt);
};

}

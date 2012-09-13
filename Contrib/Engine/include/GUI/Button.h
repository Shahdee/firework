#include "types.h"
#include "GUI/Widget.h"

#include "Render/Texture.h"
#include "SmoothTextureChanger.h"

namespace GUI
{

class Button : public Widget
{
	std::string sampleOver, samplePress;

	float _scaleFont;
	IPoint _textPosition;
	Text textPressed;
	enum {
		INPUT, OUTPUT, BOTH
	} signal;

	RectOrient _orient;

	Render::Texture* _boardNormal;
	Render::Texture* _boardPress;
	Render::Texture* _boardActive;
	Render::Texture* _boardDeactive;

	SmoothTextureChanger *_smooth;
	
	bool _clientRectHack;
		// используем ли хак с clientrect
	std::string fireMessage;
	
	typedef enum {
		ButtonNormal, ButtonActive, ButtonPress, ButtonDeactive
	} ButtonState;
	ButtonState _state;
	/// возможно ли включение заданного состояния
	bool StatePossible(ButtonState st);
	/// меняет состояние если можно, возвращает false если нельзя
	bool SetState(ButtonState st);
	//bool _isActive;
	void Activate();
	void Deactivate();
	void Fire();
	void ChangeFace();

public:
	Button(string name_, Xml::TiXmlElement* xmlElement);
	virtual ~Button();

	virtual void Draw();
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void MouseUp(const IPoint& mouse_pos);
	virtual void AcceptMessage(const Message& message);
	virtual void MouseMove(const IPoint& mouse_pos);
	virtual void Update(float dt);
	virtual bool CheckPoint(const IPoint& pos);
private:
	void InitWithXml(Xml::TiXmlElement* xmlElement);
};

}
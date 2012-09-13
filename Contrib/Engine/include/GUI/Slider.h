#pragma once

#include "GUI/Widget.h"

#include "Render/Texture.h"
#include "SmoothTextureChanger.h"

namespace GUI
{

class Slider : public Widget
{
	bool _vertical;
	
	int _sliderPosition;
	int _sliderDownPosition;
	int _limit;

	/// Ширина базовой текстуры
	int _unsetWidth; 
	/// Смещение минимальной позиции ползунка по горизонтали относительно position.x
	int _minOffset; 
	/// Смещение максимальной позиции ползунка по горизонтали относительно position.x
	int _maxOffset; 

	IPoint _manipulatorOffset;

	Render::Texture* _sliderSet;
	Render::Texture* _sliderUnset;
	Render::Texture *_sliderManipulator, *_sliderManipulatorActive, *_sliderManipulatorPressed;

	/// тень можно рисовать отдельно, не через SmoothTextureChanger, что устранит мерцание при смене текстур
	Render::Texture *_sliderManipulatorShadow;

	SmoothTextureChanger* _tex_changer;

	IRect _manipulatorRect;

	std::string _mouseDownSound, _mouseUpSound;

	bool _isSliderClick;

public:
	Slider(string name_, Xml::TiXmlElement* xmlElement);

	~Slider();

	virtual void Draw();
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void MouseMove(const IPoint& mouse_pos);
	virtual void MouseUp(const IPoint& mouse_pos);
	virtual void Update(float dt);

	virtual void AcceptMessage(const Message& message);
	virtual Message QueryState(const Message& message) const;
};

}

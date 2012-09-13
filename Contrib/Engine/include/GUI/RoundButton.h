#pragma once

#include "GUI/Widget.h"
#include "Core/EffectObserver.h"

namespace Render {
	class Texture;
}

struct Sprite
{
	float width;
	float height;
	float uStart;
	float uEnd;
	float vStart;
	float vEnd;

	void Draw(float x, float y);
};

namespace GUI
{

class RoundButton : public Widget
{
	/// Текстура тени ненажатой кнопки
	Render::Texture	*_texUShadow;		
	/// Текстура тени нажатой кнопки
	Render::Texture	*_texPShadow;		
	/// Текстура текста
	Render::Texture	*_texCaption;		
	/// Текстура тени текста
	Render::Texture	*_texSCaption;		
	/// Текстура подложки
	Render::Texture	*_texBoard;			
	IPoint				_boardOffset;

	Sprite				_sprUShadow,_sprPShadow,_sprCaption,_sprSCaption,_sprBoard;
	int					_radius;
	IPoint				_center;
	bool				_isActive;
	float				local_time;
	float				pOffsetX,pOffsetY;
	unsigned char		alpha;
	float				_angle;
	bool				_bRotate;

	bool _pressed;

	float _timer;
	EffectsContainer _magicBox;
	/// Магический эффект в кнопке :)
	ParticleEffect *_magicEffect; 
	/// Магический эффект при активной кнопке :)
	ParticleEffect *_activeMagicEffect; 
	/// Время под мышкой (относительное)
	float _underMouseTime; 
	/// Вторая текстура шарика (для постепенного перекрытия первой :))
	/// Должна быть тех же размеров что и 1
	Render::Texture	*_texBall2;			
	Sprite				_sprBall2;
	/// коэффициент перекрытия (0 - то показывается 1 текстура)
	float _blendFactor; 

public:
	IPoint				_textOffset,_pressOffset;
	/// Текстура шарика
	Render::Texture	*_texBall;			
	Sprite				_sprBall;
	
	RoundButton(string name_, Xml::TiXmlElement* xmlElement);

	virtual	~RoundButton();

	virtual void Draw();
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void MouseUp(const IPoint& mouse_pos);
	virtual void MouseMove(const IPoint& mouse_pos);
	virtual void AcceptMessage(const Message& message);
	virtual void Update(float dt);
	void setClientRect(const IRect& rect);
	void setActive(bool bActive);
};

}

void InitSprite(Sprite& spr,Render::Texture* tex);
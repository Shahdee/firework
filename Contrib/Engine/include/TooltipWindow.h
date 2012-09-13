#pragma once

#include "GUI/Widget.h"
#include "Spline.h"

class TooltipWindow
{
	enum Action
	{
		/// ничего не происходит
		NoAction,			
		/// появление окошка для текста
		WndIn,				
		/// окошко отображается на экране
		WndOn,				
		/// исчезание окошка
		WndOut,				
	};

	IPoint _position;
	TText *_text;

	Action _action;
	Color _textColor;

	float _textSize;
	SplinePath<float> _textSizeSpline;

	int _textWidth, _textHeight;
	
	Render::Texture *_ramkaTex;

	float local_time;
	float time_scale;

public:

	TooltipWindow();

	void Draw(float heightFactor = 1.f);
	void Update(float dt);
	void Show();
	void Hide();
	void Reset();

	bool isShow();

	void setTimeScale(float t);
	void setPosition(const IPoint &pos);
	void setText(TText *text);
	void setColor(const Color &_color);
	
	int getTextWidth();
	int getTextHeight();

	float getScale();
	float getAlphaFactor();

	void DrawRamka(IPoint pos);

	void setFrameTexture(Render::Texture *tex);
};


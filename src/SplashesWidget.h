#pragma once

class SplashesWidget : public GUI::Widget
{
	float _timer;

	std::vector<Render::Texture*> splashes;

	int _currentSplash;

	bool _isFade;

	bool _fadeOut, _fadeIn;

	float _fadeTimer;

	void DrawFade();

public:

	SplashesWidget(string name_, Xml::TiXmlElement* xmlElement);

	virtual void Update(float dt);
	virtual void Draw();
	virtual bool MouseDown(const IPoint& mouse_pos);
	virtual void AcceptMessage(const Message& message);
};

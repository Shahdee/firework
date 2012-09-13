#include "stdafx.h"
#include "SplashesWidget.h"
#include "File/DirectoryListing.h"

extern bool needLoadScreen;

SplashesWidget::SplashesWidget(string name_, Xml::TiXmlElement* xmlElement)
	: GUI::Widget(name_)
	, _currentSplash(0)
	, _isFade(true)
	, _timer(0.0f)
	, _fadeTimer(0.0f)
	, _fadeIn(true)
	, _fadeOut(false)
{
	std::vector<std::string> list = File::DirectoryListing::GetFromFs("../splash/*.jpg");
	for(int i = 0; i< list.size(); i++) {
		splashes.push_back(new Render::Texture(list[i]));
		splashes.back()->Upload();
		/*_splash1 = new Render::VideoTexture();
		if (!_splash1->Upload("../splash/logo.ogg"))
			delete _splash1, _splash1 = NULL;
		Sound::device.AddTrack("logo", "", "../../splash/logo.ogg", true);// 2, 1.0f, -1.0f, 	
		*/
	}

	_currentSplash = 0;
}

void SplashesWidget::DrawFade()
{
	if (_fadeTimer < 0.0f)
	{
		_fadeTimer = 0.0f;
	}

	if (_fadeTimer > 1.0f)
	{
		_fadeTimer = 1.0f;
	}

	if (_isFade)
	{
		if (_fadeIn)
		{
			Render::device.SetBlend(true);
			Render::device.SetBlendMode(Render::ALPHA);
			Render::device.SetTexturing(false);
			Render::SetColor(Color(0, 0, 0, 255-math::lerp(0, 255, _fadeTimer)));
			//Render::BeginAlphaMul(1.f - _fadeTimer);
			Render::DrawRect(IRect(0,0, 800, 600));
			//Render::EndAlphaMul();
			Render::ResetColor();
			Render::device.SetTexturing(true);
		}
		else if (_fadeOut)
		{
			Render::device.SetBlend(true);
			Render::device.SetBlendMode(Render::ALPHA);
			Render::device.SetTexturing(false);
			Render::SetColor(Color(0, 0, 0, math::lerp(0, 255, _fadeTimer)));
			//Render::BeginAlphaMul(_fadeTimer);
			Render::DrawRect(IRect(0,0, 800, 600));
			//Render::EndAlphaMul();
			Render::ResetColor();
			Render::device.SetTexturing(true);
		}
	}
}

void SplashesWidget::Draw()
{

    if (_currentSplash < splashes.size())
    {
		splashes[_currentSplash]->Bind();
		splashes[_currentSplash]->Draw(IPoint(0, 0));

		DrawFade();
	}
	else
	{
		/*
		_back->Bind();
		_back->Draw(IPoint(0, 0));

		_progressEmpty->Bind();
		_progressEmpty->Draw(progressPos);

		_panel->Bind();
		_panel->Draw(progressPos + IPoint(-10, -10));
		*/
		Core::appInstance->splashesLoop = false;
	}
}

bool SplashesWidget::MouseDown(const IPoint& mouse_pos)
{
	if (!_isFade)
	{
		_isFade = true;
		_fadeTimer = 0.0f;
		_fadeIn = false;
		_fadeOut = true;
		_timer = 0.0f;
		//if (_currentSplash == 0)
		//	Sound::device.FadeOutTrack("logo", 0.5f);
	}

	return true;
}

void SplashesWidget::AcceptMessage(const Message& message)
{
	if (message.is("Release"))
	{
		for(int i=0; i<splashes.size(); i++)
		{
			splashes[i]->Release();
		}
	}
	else if(message.is("KeyPress"))
	{
		_isFade = true;
		_fadeTimer = 0.0f;
		_fadeIn = false;
		_fadeOut = true;
		_timer = 0.0f;
	}
}

void SplashesWidget::Update(float dt)
{
    if (_isFade)
    {
		_fadeTimer += dt*2.0f;

		if (_fadeTimer >= 1.0f)
		{
			if (_fadeIn)
			{
				_isFade = false;
				_fadeIn = false;
				_fadeOut = false;
				_fadeTimer = 0.0f;
			}
			if (_fadeOut)
			{
				_fadeOut = false;
				_fadeIn = true;
				_fadeTimer = 0.0f;

				_currentSplash++;
			}
		}
    }

	_timer += dt;
	/*if ((_currentSplash == 0) && _splash1)
	{
		_splash1->Update(dt);
		if ((_timer == dt) && !_fadeOut)
			Sound::device.PlayTrack("logo", false);
		float t = (_splash1->getLastPlayedFrame() - _splash1->getFirstPlayedFrame() + 1) * 1.0f / _splash1->getSpeed();
		if (_timer > t)
			Sound::device.StopTrack("logo");
		if (_timer > (t + 1.0f))
		{
			_timer = 0.0f;	
			_isFade = true;
			_fadeTimer = 0.0f;
			_fadeIn = false;
			_fadeOut = true;
		}
	}
	else*/ if (_timer > 3.5f && !_isFade)
	{
		_timer = 0.0f;	
		_isFade = true;
		_fadeTimer = 0.0f;
		_fadeIn = false;
		_fadeOut = true;
	}
}

#pragma once

class TestWidget: public GUI::Widget
{
private:
	float _timer;
	float _timeScale;
	
	std::vector<Render::Texture *> _textures;
	int _curTex;
	float _angle;
	
	SmoothTextureChanger *_smoothTex;	

	EffectsContainer _effCont;
	ParticleEffect *_eff;

	void Init();
public:
	TestWidget(const std::string& name_);
	TestWidget(const std::string& name_, Xml::TiXmlElement* xmlElement);
	~TestWidget();

	virtual void Draw();
	virtual void Update(float dt);
	virtual void AcceptMessage(const Message& message);
	virtual void MouseDoubleClick(const IPoint &mouse_pos);
	virtual bool MouseDown(const IPoint &mouse_pos);
	virtual void MouseMove(const IPoint &mouse_pos);
	virtual void MouseUp(const IPoint &mouse_pos);
};
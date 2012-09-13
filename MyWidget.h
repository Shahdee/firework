#pragma once


class Firework
{
	friend class MyWidget;
private:
	int _pos;
	FPoint _velocity;
	bool _isAlive;
	ParticleEffect* eff;

}

class MyWidget: public GUI::Widget
{
private:

	std::vector<Render::Texture *> _textures;

	bool _isCreated;
	bool _wasLastGroup;
	int _level;
	float _lifeTime;
	int _children;
	int _currLevel;
	int _currAge;
	float _gravity;

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
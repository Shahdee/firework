#pragma once
#include "GUI/Widget.h"

struct AnimLayer;

class LayerObject
{
public:
	string name;

	float x, y, scale, scaleX, scaleY, angle;
	float rotX, rotY;
	bool isVisible;
	Color color;

	LayerObject();

	bool NameCompare(const string& name_);

	virtual void Draw();

	virtual void Update(float dt);

	virtual void DoCommand(const string& command);

	virtual void Release();

	virtual void Upload();

};

class LoTexture : public LayerObject
{
	Render::Texture* texture;

	bool wrapH;
	bool wrapV;

	float rectWidth;
	float rectHeight;
	string textureName;
	bool isTextured;

	bool additive;

	bool fromResourceManager;

	string fileName;

	bool isUpload;

public:

	LoTexture(Xml::TiXmlElement* elem);

	virtual void Upload();

	virtual void Release();

	virtual void Draw();

	virtual void DoCommand(const string& command);
};

class LoEffect : public LayerObject
{
public:

	ParticleEffect* effect;
	string effectName;
	bool canDie;

	LoEffect(Xml::TiXmlElement* elem);

	virtual void Update(float dt);

	virtual void Draw();

	virtual void DoCommand(const string& command);

};

class LoSymbol : public LayerObject
{
public:

	Render::Texture *texture;

	int startFrame;

	bool isPaused;

	float timer;

	LoSymbol(Xml::TiXmlElement* elem);

	virtual void Upload();

	virtual void Release();

    virtual void Draw();

	virtual void Update(float dt);

};

class LoAnimation : public LayerObject
{
public:

	Render::Animation::HardPtr animation;

	bool isPaused;

	string animName;

	LoAnimation(Render::Animation* anim_);

	LoAnimation(Xml::TiXmlElement* elem);

	virtual void Upload();

	virtual void Release();

    virtual void Draw();

	virtual void Update(float dt);
};

struct LayerSet
{
	string name;

	std::vector<AnimLayer*> _layers;

	void Upload();
	void Release();

	AnimLayer* getLayer(const string& name);
	void Load(Xml::TiXmlElement* elem);
	void LinkWithScript();
};

class LayeredAnimationPlayer;
class LayeredAnimation : public GUI::Widget
{
	LayeredAnimationPlayer *_player;
	bool isLoaded;
	bool isUploaded;

public:
	LayerSet layerSet;

	LayeredAnimation(const string& name_, Xml::TiXmlElement* elem);

	virtual ~LayeredAnimation(void);

	void Load();

	virtual void Draw();

	virtual void AcceptMessage(const Message &message);
	virtual Message QueryState(const Message &message) const;
};

void ExportLayerAnimation();

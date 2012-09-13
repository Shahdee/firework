#ifndef _GUI_MOVIEPLAYEROBJECTS_H_
#define _GUI_MOVIEPLAYEROBJECTS_H_

#include "MoviePlayerFloatPoint.h"
#include "Render/Texture.h"
#include "MoviePlayerResMgr.h"
#include "MoviePlayerSpline.h"
#include "MoviePlayerVariableSpeedAnimation.h"
#include <luabind/luabind.hpp>

class MoviePlayerObject;
typedef MoviePlayerObject* MoviePlayerObjectWeakPtr;

//////////////////////////////////////////////////////////////////////////
// Triggers
//////////////////////////////////////////////////////////////////////////

class Trigger
{
public:

	Trigger(Xml::TiXmlElement *triggerXml, MoviePlayerObjectWeakPtr parent);

	void Apply();

	std::string GetCommand();

	void Reset();

private:

	bool _applied;

	MoviePlayerObjectWeakPtr _parent;

	std::string _command;

};

typedef boost::shared_ptr<Trigger> TriggerHardPtr;
typedef Trigger* TriggerWeakPtr;

//////////////////////////////////////////////////////////////////////////
// Keys
//////////////////////////////////////////////////////////////////////////

class ObjectInterpolator
{
public:

	virtual ~ObjectInterpolator();

	void Update(float newTime);

	MoviePlayerFloatPoint GetTranslation();

	MoviePlayerFloatPoint GetCenter();

	float GetAngle();

	float GetXZoom();

	float GetYZoom();

	float GetAlpha();

	Color GetColor();

	void Reset();

protected:

	ObjectInterpolator(Xml::TiXmlElement *object, MoviePlayerObjectWeakPtr parent, int frameCount);

	float GetLocalTime();

	int GetFrameCount();

	float CheckMin(float value, float min);

	float CheckMax(float value, float max);

	float CheckFloat(float value, float min, float max);

	float CheckFloat01(float value);

	float CheckFloat0255(float value);

	float AngleAssert(float angle);

private:

	typedef std::multimap<float, TriggerHardPtr> TriggerMap;

	typedef TriggerMap::value_type TriggerPair;

	typedef TriggerMap::iterator Iterator;

	TriggerMap _triggers;

	float _localTime;

	int _frameCount;

	MoviePlayerObjectWeakPtr _parent;

	MoviePlayerAngleSpline _angle;

	MoviePlayerSpline _x, _y, _xZoom, _yZoom, _centerX, _centerY;

	MoviePlayerSpline _alpha, _red, _green, _blue;

	void LoadObjectSplines(Xml::TiXmlElement *object);

	void ApplyTriggers(float oldTime, float newTime);

	void LoadTriggers(Xml::TiXmlElement *triggersXml);

	virtual void UpdateImpl(float newTime);

};

class PictureInterpolator
	: public ObjectInterpolator
{
public:

	PictureInterpolator(Xml::TiXmlElement *object, MoviePlayerObjectWeakPtr parent, int frameCount);

};

class AnimationInterpolator
	: public ObjectInterpolator
{
public:

	AnimationInterpolator(Xml::TiXmlElement *object, MoviePlayerObjectWeakPtr parent, int frameCount);

	float GetSpeed();

private:

	MoviePlayerSpline _fps;

	void LoadAnimationSplines(Xml::TiXmlElement *object);

};

class EffectInterpolator
	: public ObjectInterpolator
{
public:

	EffectInterpolator(Xml::TiXmlElement *object, MoviePlayerObjectWeakPtr parent, int frameCount);

	MoviePlayerFloatPoint GetEmitterPos();

private:

	MoviePlayerSpline _emitterPosX, _emitterPosY;

	void LoadEffectSplines(Xml::TiXmlElement *object);

};

//////////////////////////////////////////////////////////////////////////
// Objects
//////////////////////////////////////////////////////////////////////////

class MoviePlayerLuaObject
{
public:

	float x, y, xZoom, yZoom, angle;

	std::string id;

	MoviePlayerLuaObject(std::string id_ = "")
		: x(0.0f)
		, y(0.0f)
		, xZoom(1.0f)
		, yZoom(1.0f)
		, angle(0.0f)
		, id(id_)
	{}

};

class MoviePlayerObject
{
public:

	void Draw(int xRemoval, int yRemoval);

	void LuaUpdate(lua_State *state, float localTime);

	void Update(float newTime, float dt);

	virtual void Reset();

	bool ApplyTrigger(TriggerWeakPtr trigger);

	virtual ~MoviePlayerObject();

	MoviePlayerFloatPoint GetTranslation();

	MoviePlayerFloatPoint GetLuaObjPos();

	string GetId() const;

protected:

	typedef ObjectInterpolator* ObjectInterpolatorHardPtr;

	ObjectInterpolatorHardPtr _interpolator;

	MoviePlayerObject(Xml::TiXmlElement *object);

	MoviePlayerFloatPoint GetCenter();

	float GetAngle();

	float GetXZoom();

	float GetYZoom();

	float GetAlpha();

	Color GetColor();

private:

	bool _showed;

	bool _error;

	std::string _id;

	std::string _luaFunction;

	MoviePlayerLuaObject _obj;

	virtual void DrawImpl() = 0;

	virtual void UpdateImpl(float dt) = 0;

	virtual bool ApplyTriggerImpl(TriggerWeakPtr trigger);

};

typedef MoviePlayerObject* MoviePlayerObjectHardPtr;

//////////////////////////////////////////////////////////////////////////

class MoviePlayerStaticObject
	: public MoviePlayerObject
{
protected:

	MoviePlayerStaticObject(Xml::TiXmlElement *object);

private:

	void UpdateImpl(float dt);

};

class MoviePlayerPicture
	: public MoviePlayerStaticObject
{
public:

	MoviePlayerPicture(Xml::TiXmlElement *object, int frameCount, MoviePlayer::ResourceManager &mgr);

private:

	Render::Texture *_texture;

	void DrawImpl();

};

//////////////////////////////////////////////////////////////////////////

class MoviePlayerDynamicObject
	: public MoviePlayerObject
{
protected:

	MoviePlayerDynamicObject(Xml::TiXmlElement *object);

	void Reset();

private:

	void UpdateImpl(float dt);

	virtual void ObjectSelfUpdateImpl(float dt) = 0;

	bool ApplyTriggerImpl(TriggerWeakPtr trigger);

	virtual void StartImpl() = 0;

	virtual void StopImpl() = 0;

	virtual bool ApplyTriggerImpl2(TriggerWeakPtr trigger);

};

class MoviePlayerAnimation
	: public MoviePlayerDynamicObject
{
public:

	MoviePlayerAnimation(Xml::TiXmlElement *object, int frameCount, MoviePlayer::ResourceManager &mgr);

	void Reset();

private:

	typedef AnimationInterpolator* AnimationInterpolatorWeakPtr;

	MoviePlayerVariableSpeedAnimation::HardPtr _animation;

	bool _pingPong;

	float GetSpeed();

	void SetPingPongMode();

	void ObjectSelfUpdateImpl(float dt);

	void DrawImpl();

	void StartImpl();

	void StopImpl();

};

class MoviePlayerEffect
	: public MoviePlayerDynamicObject
{
public:

	MoviePlayerEffect(Xml::TiXmlElement *object, int frameCount, MoviePlayer::ResourceManager &mgr);

	void Reset();

private:

	typedef EffectInterpolator* EffectInterpolatorWeakPtr;

	ParticleEffect _effect;

	MoviePlayerFloatPoint GetEmitterPos();

	void ObjectSelfUpdateImpl(float dt);

	void DrawImpl();

	void StartImpl();

	void StopImpl();

};

#endif

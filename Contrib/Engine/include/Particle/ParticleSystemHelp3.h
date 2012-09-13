#ifndef PARTICLE_SYSTEM_HELP3_H
#define PARTICLE_SYSTEM_HELP3_H

#include "Render/Texture.h"
#include "Core/ResourceManager.h"
#include "Utils/FPoint.h"
#include "Utils/Math.hpp"
#include "Utils/random.hpp"
#include "Spline.h"
#include "BinaryData.h"
#include "Particle/ParticleSystemHelp2.h"

inline float FloatMod(float a, float b)
{
	Assert(b > 0);
	a = a - int(a/b)*b;
	return a < 0 ? a + b : a;
}
class ParticleSystemVer3;
class PS3Param
{
public:
	PS3Param();
	void Update(float dt);
	float operator()()
	{
		return _scale * _value;
	}
	float gradient()
	{
		return _scale * _spline.getGlobalGradient(_timer);
	}

	GradientSpline _spline;
	float _value;
	float _duration;
	float _timer;
	float _scale;
	bool _looped;
};
class PS3ParamInit
{
public:
	PS3ParamInit(std::string name);
	PS3ParamInit(std::string name, float value, float variation = 0);
	struct Variation
	{
		float lower;
		float upper;
		Variation(): lower(0), upper(0) {}
	};
	struct SplineKey
	{
		float time;
		bool fixed_grad;
		Variation value, lgrad, rgrad;
		SplineKey() : time(0), fixed_grad(false) {}
	};


	void operator()(PS3Param *param, float duration);
	void Load(BinaryDataLoader *d);
	void Save(BinaryDataSaver *d);
	void Load(Xml::TiXmlElement *elem);
	void Save(Xml::TiXmlElement *elem);
	Xml::TiXmlElement* ToXml()
	{
		Xml::TiXmlElement *elem = new Xml::TiXmlElement(PSS::PARAM);
		Save(elem);
		return elem;
	}

	std::string _name;
	bool _similar;
//	float _value;
	float _scale;
	float _removal;
	std::vector<SplineKey> _keys;

	float Lerp(const Variation &v, const float t) { return math::lerp<float>(v.lower, v.upper, t); }
};
class PS3Track
{
public:
	PS3Track();
	void Update(float dt);
	FPoint operator()()
	{
		return _value;
	}
	FPoint operator()(float time)
	{
		return _spline.getGlobalFrame(FloatMod(_timer*_duration + time, _duration) / _duration);
	}
	FPoint gradient()
	{
		return _spline.getGlobalGradient(_timer);
	}

	TrackSpline _spline;
	FPoint _value;
	float _duration;
	float _timer;
	bool _looped;
};
class PS3TrackInit
{
public:
	PS3TrackInit(std::string name);
	struct Key
	{
		FPoint value, variation;
		bool linear_in, linear_out;
		Key()
			: linear_in(false)
			, linear_out(false)
		{}
	};

	void operator()(PS3Track *track, bool use_variation = true);
	void Load(BinaryDataLoader *d);
	void Save(BinaryDataSaver *d);
	void Load(Xml::TiXmlElement *elem);
	void Save(Xml::TiXmlElement *elem);
	bool DoCycle() { return _cycled && _keys.size() > 1; }
	Xml::TiXmlElement* ToXml()
	{
		Xml::TiXmlElement *elem = new Xml::TiXmlElement(PSS::TRACK);
		Save(elem);
		return elem;
	}

	std::string _name;
	float _duration;
	bool _similar;
	bool _cycled;
	bool _looped;
	std::vector<Key> _keys;
};
class PS3Mask: public EmitterMask
{
};
struct PS3Position
{
	float x, y, angle;
	PS3Position(float x_ = 0, float y_ = 0, float angle_ = 0)
		: x(x_)
		, y(y_)
		, angle(angle_)
	{
	}
	PS3Position(const FPoint &pos)
		: x(pos.x)
		, y(pos.y)
		, angle(0)
	{
	}
	PS3Position Transform(const FPoint &pos)
	{
		return Transform(PS3Position(pos.x, pos.y));
	}
	PS3Position Transform(const PS3Position &pos)
	{
		math::Vector3 v(x, y, 0);
		RotateVector(v, pos.angle);
		return PS3Position(v.x + pos.x, v.y + pos.y, angle + pos.angle);
	}
};

class PS3Particle
{
public:
	PS3Particle();
	PS3Particle(const PS3Particle& part);
	~PS3Particle();

	void UpdateFrames(float dt);
	void Update(float dt);
	void Reset();
	void CreateSystems();

	void UpdatePos(float dt);
	void UpdateColor();
	PS3Position Pos();
	void Die();
	bool IsDead();

	ParticleSystemVer3* _owner;

	FPoint _offset;
	float _spinOffset;
	PS3Position _pos;
	PS3Position _birthPos;

	Color _color;
	float _lifeTime;
	float _localTime;

	bool _isBorned;
	bool _isDead;
	bool _isAllSystemDead;

	int _currentFrame, _firstFrame, _lastFrame;

	float _speed, _progress;

	PS3Param _x, _y, _size, _angle, _v, _spin, _red, _green, _blue, _alpha, _fps, _ySize;
	PS3Track _track;

	std::vector<ParticleSystemVer3*> _systems;
};

#endif
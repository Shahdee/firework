#ifndef PARTICLE_SYSTEM_HELP2_H
#define PARTICLE_SYSTEM_HELP2_H

#include "Render/Texture.h"
#include "Core/ResourceManager.h"
#include "Utils/Math.hpp"
#include "Utils/random.hpp"
#include "Spline.h"
#include "BinaryData.h"

class EmitterMask
{
public:
	EmitterMask();

	void SetMask(Render::Texture* tex);
	FPoint RandomPoint(float scale = 1);

	void SetAlphaMin(uchar min) { alpha_min = min; }
	void SetAlphaMax(uchar max) { alpha_max = max; }
	void SetScaleX(float scale) { scale_x = scale < 0 ? 0 : scale; }
	void SetScaleY(float scale) { scale_y = scale < 0 ? 0 : scale; }
	uchar AlphaMin() { return alpha_min; }
	uchar AlphaMax() { return alpha_max; }
	float ScaleX() { return scale_x; }
	float ScaleY() { return scale_y; }
private:
	struct ProbablePoints
	{
		float p;
		struct Point { short x, y; };
		std::vector<Point> points;
		void Add(short x, short y)
		{
			Point point;
			point.x = x;
			point.y = y;
			points.push_back(point);
		}
	};

	std::vector<ProbablePoints> mask;
	uchar num_gradations;
	float total_p;
	float scale_x, scale_y;
	uchar alpha_min, alpha_max;

	uchar Gradation(uchar p);
	ProbablePoints& GetProbablePoints(uchar alpha);
};

class TimeParam
{
friend class EffectManager;
friend class GraphSpline;
public:
	TimeParam();
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


	float Reset(GradientSpline *spline);
	void Load(BinaryDataLoader *d);
	void Save(BinaryDataSaver *d);
	void Load(Xml::TiXmlElement *elem);
	void Save(Xml::TiXmlElement *elem);
	Xml::TiXmlElement* ToXml()
	{
		Xml::TiXmlElement *elem = new Xml::TiXmlElement(TAG_PARAM);
		Save(elem);
		return elem;
	}
	void SetValue(float value, float variation = 0);
	void SetScale(float scale)
	{
		_scale = scale;
	}

	void SetName(const std::string &name) { _name = name; }
	float Removal() { return _removal; }

	std::string _name;
	bool _similar;
	float _value;
	float _scale;
	float _removal;
	std::vector<SplineKey> _keys;

public:
	static const char* TAG_PARAM;
	static const char* TAG_KEY;
	static const char* ATTR_NAME;
	static const char* ATTR_SIMILAR;
	static const char* ATTR_REMOVAL;
	static const char* ATTR_TIME;
	static const char* ATTR_FIXED_GRAD;
	static const char* ATTR_VALUE_LOWER;
	static const char* ATTR_VALUE_UPPER;
	static const char* ATTR_LGRAD_LOWER;
	static const char* ATTR_LGRAD_UPPER;
	static const char* ATTR_RGRAD_LOWER;
	static const char* ATTR_RGRAD_UPPER;

	float Lerp(const Variation &v, const float t) { return math::lerp<float>(v.lower, v.upper, t); }
};

#endif
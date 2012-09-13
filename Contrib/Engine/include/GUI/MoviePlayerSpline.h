#ifndef _GUI_MOVIEPLAYERSPLINE_H_
#define _GUI_MOVIEPLAYERSPLINE_H_

class MoviePlayerSpline
{
public:

	MoviePlayerSpline();

	static float SplineInterpolation(float x1, float x2, float r1, float r2, float t);

	static float GradientInterpolation(float x1, float x2, float r1, float r2, float t);

	void FromXml(Xml::TiXmlElement *root, int frameCount);

	void Clear();

	void CalculateGradients();

	float GetValue(float time);

	float GetGradient(float time);

	bool static QueryBoolAttribute(Xml::TiXmlElement *root, std::string attribute);

protected:

	struct KeyFrame {

		float _value;

		float _leftGradient, _rightGradient, _gradient;

		bool _const, _linear;

		KeyFrame(float value, bool constant, bool linear)
			: _value(value)
			, _gradient(0.0f)
			, _leftGradient(0.0f)
			, _rightGradient(0.0f)
			, _const(constant)
			, _linear(linear)
		{}

	};

	typedef std::map<float, KeyFrame> KeyFrameMap;

	typedef KeyFrameMap::value_type KeyFramePair;

	typedef KeyFrameMap::iterator Iterator;

	typedef std::pair<Iterator, Iterator> Bounds;

	bool _calculated;

	KeyFrameMap _keys;

	static float NormalizeAngle(float angle);

	static float AngleAssert(float angle);

	Bounds GetBounds(float time);

};

class MoviePlayerAngleSpline
	: public MoviePlayerSpline
{
public:

	void FromXml(Xml::TiXmlElement *root, int frameCount);

	void CalculateGradients();

	float GetValue(float time);

	float GetGradient(float time);

private:

	float AdjustAngleSplineValue(float leftValue, float rightValue);

	float AdjustAngleSplineValue2(float leftValue, float middleValue, float rightValue);

};

#endif

#pragma once

#include "Assert.h"
#include "Utils/FPoint.h"

float SplineInterpolation(float x1, float x2, float r1, float r2, float t);
float GetGradient(float x1, float x2, float r1, float r2, float t);

template <class T>
class SplinePath
{
public:
	typedef std::pair<T, T> KeyFrame;

	std::vector<KeyFrame> keys;

	void Clear()
	{
		keys.clear();
	}

	void addKey(const T& key)
	{
		keys.push_back(KeyFrame(key, key));
	}

	T getFrame(int sector, float t)
	{
		size_t i = static_cast<size_t>(sector);
		return SplineInterpolation(keys[i].first, keys[i+1].first, keys[i].second, keys[i+1].second, t);
	}

	T getGradient(int sector, float t)
	{
		size_t i = static_cast<size_t>(sector);
		return GetGradient(keys[i].first, keys[i+1].first, keys[i].second, keys[i+1].second, t);
	}

	T getGlobalFrame(float t)
	{
		float timeStep = (1.0f/getSectors());
		int tessSector = static_cast<int>(t/timeStep);
		if (tessSector >= getSectors())
			return keys.back().first;
		float tessLocalTime = (t-tessSector*timeStep)/timeStep;
		return getFrame(tessSector, tessLocalTime);
	}

	T getGlobalGradient(float t)
	{
		float timeStep = (1.0f/getSectors());
		int tessSector = static_cast<int>(t/timeStep);
		if (tessSector >= getSectors())
			return keys.back().second;
		float tessLocalTime = (t-tessSector*timeStep)/timeStep;
		return getGradient(tessSector, tessLocalTime);
	}

	int getSectors()
	{
		return static_cast<int>(keys.size()-1);
	}

	void CalculateGradient(bool cycled = false)
	{
		if (cycled)
		{
			keys.push_back(keys[0]);
		}
		
		if (cycled)
		{
			keys[0].second = 0.5f*(keys[1].first - keys[keys.size() - 2].first);
			keys[keys.size() - 1].second = keys[0].second;
		}
		else
		{
			if (keys.size() > 1)
			{
				keys[0].second = keys[1].first-keys[0].first;
				keys[keys.size()-1].second = keys[keys.size()-1].first-keys[keys.size()-2].first;
			}
		}

		for (size_t i = 1; i < (keys.size()-1); i++)
		{
			keys[i].second = 0.5f*(keys[i+1].first - keys[i-1].first);
		}
	}
};

class TimedSplinePath
{
public:
	typedef std::pair<float, float> KeyValue;

	struct KeyFrame
	{
		KeyValue value;
		float time;

		float td, ts;

		KeyFrame(float key, float time_)
			: value(key, key)
			, time(time_)
			, td(0.0f)
			, ts(0.0f)
		{}

		struct compare
		{
			bool operator() (const KeyFrame &a, const KeyFrame &b)
			{
				return a.time < b.time;
			}
		};
	};

	std::vector<KeyFrame> keys;

	TimedSplinePath() {}
	TimedSplinePath(rapidxml::xml_node<> *node, bool calculateGradient = true, bool cycled = false);
	/*
		<SomeSplineName>
			<key time="" value="" />
			...
			<key time="" value="" />
		</SomeSplineName>
	*/

	void Clear();

	void addKey(const float time, float key);

	float getFrame(size_t sector, float t);

	float getGradient(int sector, float t);

	float getGlobalFrame(float t);

	float getGlobalGradient(float t);

	int getSectors();

	void CalculateGradient(bool cycled = false);
};

class GradientSpline
{
public:
	GradientSpline() {}

	struct Key
	{
		float time;
		float value;
		float left_gradient;
		float right_gradient;
		bool fixed_gradient;
		Key(float t = 0, float v = 0, float lgrad = 0, float rgrad = 0, bool fixed = false)
			: time(t)
			, value(v)
			, left_gradient(lgrad)
			, right_gradient(rgrad)
			, fixed_gradient(fixed)
		{}
		bool operator ==(const Key &k)
		{
			return time == k.time && value == k.value && left_gradient == k.left_gradient && right_gradient == k.right_gradient && fixed_gradient == k.fixed_gradient;
		}
	};


	void Clear() { keys.clear(); }

	void CalculateGradient();

	float getGlobalFrame(float time);
	float getGlobalGradient(float time);

	void addKey(float time, float value, float lgrad = 0, float rgrad = 0, bool fixed_grad = false)
	{
		addKey(Key(time, value, lgrad, rgrad, fixed_grad));
	}
	void addKey(const Key &key);
	void deleteKey(size_t pos) { keys.erase(keys.begin() + pos); }

	size_t size() { return keys.size(); }

	Key& operator [](size_t pos) { return keys[pos]; }

	std::vector<Key> keys;

	float interpolationValue(float time, const Key &key1, const Key &key2);
	float interpolationGradient(float time, const Key &key1, const Key &key2);
};
class TrackSpline
{
public:
	TrackSpline()
		: _cycled(false)
	{}

	struct Key
	{
		float time;
		FPoint value, gradient_in, gradient_out;
		bool linear_in;
		bool linear_out;
	};


	void Clear()
	{
		_keys.clear();
	}

	void addKey(float x, float y, bool linear_in = false, bool linear_out = false)
	{
		_keys.resize(_keys.size() + 1);
		Key &key = _keys.back();
		key.value.x = x;
		key.value.y = y;
		key.linear_in = linear_in;
		key.linear_out = linear_out;
	}

	void deleteKey(size_t pos)
	{
		_keys.erase(_keys.begin() + pos);
	}

	size_t size()
	{
		return _keys.size();
	}

	Key& operator [](size_t pos)
	{
		return _keys[pos];
	}

	void Calculate();

	FPoint getGlobalFrame(float time);

	FPoint getGlobalGradient(float time);

	FPoint interpolationValue(float time, size_t i, size_t j);

	FPoint interpolationGradient(float time, size_t i, size_t j);

	size_t Prev(size_t i);

	size_t Next(size_t i);

	float Length(const Key &key1 , const Key &key2);

	FPoint GradientIn(size_t i);

	FPoint GradientOut(size_t i);

	std::vector<Key> _keys;
	bool _cycled;
	float _length;
};

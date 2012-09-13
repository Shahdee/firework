#ifndef _UTILS_RANDOM_HPP_
#define _UTILS_RANDOM_HPP_

#include "Utils/FPoint.h"

namespace utils 
{
	template <class T>
	inline T random(const T& range)
	{
		return static_cast<T>( rand()/(1.0f + RAND_MAX)*float(range) );
	}

	template <>
	inline math::Vector3 random(const math::Vector3& range)
	{
		return ::rand()/(1.0f + RAND_MAX)*range;
	}

	template <>
	inline Color random(const Color& range)
	{
		return Color
			(
			random<unsigned char>(range.red),
			random<unsigned char>(range.green),
			random<unsigned char>(range.blue),
			random<unsigned char>(range.alpha)
			);
	}

	template <>
	inline float random(const float& range)
	{
		return rand()/(1.0f + RAND_MAX)*range;
	}


	template <class T>
	inline T random(const T& start, const T& end)
	{
		return (start+random(end-start));
	}

	template <>
	inline Color random(const Color& start, const Color& end)
	{
		return Color
			(
			start.red+random(end.red-start.red),
			start.green+random(end.green-start.green),
			start.blue+random(end.blue-start.blue),
			start.alpha+random(end.alpha-start.alpha)
			);
	}

	template <>
	inline math::Vector3 random(const math::Vector3& start, const math::Vector3& end)
	{
		return math::Vector3
			(
			start.x+random(end.x-start.x),
			start.y+random(end.y-start.y),
			start.z+random(end.z-start.z)
			);
	}

	template <>
	inline FPoint random(const FPoint& start, const FPoint& end)
	{
		return start + (end - start).Scale(random(0.0f, 1.0f), random(0.0f, 1.0f));
	}
}


namespace math
{

	template <class T>
	inline T lerp(const T& v1, const T& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return (v1+static_cast<T>(/*static_cast<float>*/(v2-v1)*t));
	}

	template <>
	inline float lerp(const float& v1, const float& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return (v1+(v2-v1)*t);
	}

	template <>
	inline Vector3 lerp(const Vector3& v1, const Vector3& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return (v1+(v2-v1)*t);
	}

	template <>
	inline IPoint lerp(const IPoint& v1, const IPoint& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return IPoint(lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t));
	}

	template <>
	inline FPoint lerp(const FPoint& v1, const FPoint& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;
		
		return FPoint(lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t));
	}
	
	template <>
	inline Color lerp(const Color& v1, const Color& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return Color(	
			lerp<int>(v1.red, v2.red, t), 
			lerp<int>(v1.green, v2.green, t), 
			lerp<int>(v1.blue, v2.blue, t),
			lerp<int>(v1.alpha, v2.alpha, t)
					);
	}

	inline float ease(float t, float a, float b) 
	{
		float k;
		float s = a + b;

		if (s == 0.0f) return t;
		if (s > 1.0f) 
		{
			a = a / s;
			b = b / s;
		}
		k = 1.0f / (2.0f - a - b);
		if (t < a)
		{
			return ((k / a) * t * t);
		}
		else 
		{
			if (t <= 1.0f - b)
			{
				return (k * (2 * t - a));
			} 
			else 
			{
				t = 1.0f - t;
				return (1.0f - (k / b) * t * t);
			}
		}
	}

	// производная для ease()
	inline float ease_deriv(float t, float a, float b) 
	{
		if (t < 0.0f || t > 1.0f || a < 0.0f || b < 0.0f) return 1.0f;

		float k;
		float s = a + b;

		if (s == 0.0f) return 1.0f;
		if (s > 1.0f) 
		{
			a /= s;
			b /= s;
		}
		k = 1.0f / (2.0f - a - b);
		if (t < a)
			return 2*k/a*t;
		else if (t <= 1.0f - b)
			return 2*k;
		else
			return 2*k/b*(1-t);
	}

	// функция, обратная к ease (медленная, нежелательна к применению в каждом кадре)
	inline float ease_inv(float y, float a, float b) 
	{
		if (y < 0.0f || y > 1.0f || a < 0.0f || b < 0.0f) return y;

		float s = a + b;
		if (s == 0.0f) return y;

		if (s > 1.0f) 
		{
			a /= s;
			b /= s;
		}
		
		float k = 1.0f / (2.0f - a - b);
		if (y < k*a) 
			return math::sqrt(a*y/k);
		else if (y < 1-k*b) 
			return (y+a*k)/(2.0f*k);
		else
			return 1.0f - math::sqrt(b*(1-y)/k);
	}

	/** 
	 * Возвращает точку на кривой Безье
	 * Параметры:
	 * start, end, control - начальная, конечная и контрольная точки
	 * time - время от 0 до 1
	 */
	inline FPoint simpleBezier(const FPoint &start, const FPoint &end, const FPoint &control, float time)
	{
		time = math::clamp(0.0f, 1.0f, time);

		const float invertedTime = 1.0f - time;
		const float timePower2 = time * time;
		const float invertedTimePower2 = invertedTime * invertedTime;

		return FPoint(
				invertedTimePower2 * start.x + 2.0f * time * invertedTime * control.x + timePower2 * end.x,
				invertedTimePower2 * start.y + 2.0f * time * invertedTime * control.y + timePower2 * end.y
			);
	}

	template <class T>
	class RandomValue
	{
		T _value;
		T _v1, _v2;
		T _limit;
		float _local_time;
		float _period;
		float _startPeriod, _endPeriod;

	public:
		RandomValue(T limit, float startPeriod, float endPeriod)
			: _limit(limit)
			, _local_time(0.0f)
			, _startPeriod(startPeriod)
			, _endPeriod(endPeriod)
		{
			_period = utils::random(_startPeriod, _endPeriod);
			_v1 = utils::random(_limit);
			_v2 = utils::random(_limit);
		}

		void Update(float dt)
		{
			if (_local_time >= _period)
			{
				_local_time -= _period;
				_period = utils::random(_startPeriod, _endPeriod);
				_v1 = _v2;
				_v2 = utils::random(_limit);
			}
			_value = lerp(_v1, _v2, _local_time/_period);
			_local_time += dt;
		}

		T get()
		{
			return _value;
		}
	};
}

#endif

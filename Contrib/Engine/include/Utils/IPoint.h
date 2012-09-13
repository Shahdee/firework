#ifndef _UTILS_IPOINT_
#define _UTILS_IPOINT_

#include "Utils/Math.hpp"
#include "Utils/Vector3.h"
#include "../rapidxml/rapidxml.hpp"

enum Direction 
{
	Left = 0,
	Right,
	Up,
	Down
};

class FPoint;
struct IRect;

struct IPoint
{
	IPoint();

	IPoint(int x_, int y_);

	IPoint(Xml::TiXmlElement* elem);

	IPoint(rapidxml::xml_node<>* elem);

	/// Инициализация точки левым нижним углом прямоугольника
	explicit IPoint(const IRect& rect);

	int x, 
		y;

	//operator const FPoint() const;
	// У нас уже есть конструктор FPoint(IPoint)

	/// Оператор перевода в math::Vector3 с нулевым Z.
	operator math::Vector3() const;

	/// Оператор унарный минус
	IPoint operator -() const;
	IPoint& operator +=(const IPoint& p);
	IPoint& operator -=(const IPoint& p);
	IPoint operator *(const int& i) const;
};

inline IPoint operator + (const IPoint& a, const IPoint& b)
{
	return IPoint(a.x+b.x, a.y+b.y);
}

inline IPoint operator - (const IPoint& a, const IPoint& b)
{
	return IPoint(a.x-b.x, a.y-b.y);
}

inline bool operator == (const IPoint& a, const IPoint& b)
{
	return a.x == b.x && a.y == b.y;
}

inline bool operator != (const IPoint&a, const IPoint& b)
{
	return a.x != b.x || a.y != b.y;
}

enum RectOrient
{
	Normal,
	Rotate90,
	Rotate180,
	Rotate270
};

struct FRect;

//inline IRect operator + (const IPoint& p, const IRect& r)
//{
//	return IRect(p.x + r.x, p.y + r.y, r.width, r.height);
//}

namespace math
{
	inline bool CheckPointInCircle(const IPoint& point, const IPoint& center, const float radius)
	{
			int xDif = point.x - center.x;
			if (abs(xDif) > radius)
				return false;
			float sq = math::sqrt(radius * radius - xDif * xDif);
			if (point.y <= sq + center.y && point.y  >= -sq + center.y)
				return true;
			else
				return false;
	}
}

#endif

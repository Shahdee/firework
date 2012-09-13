#ifndef _GUI_MOVIEPLAYERFLOATPOINT_H_
#define _GUI_MOVIEPLAYERFLOATPOINT_H_

#include "Math.h"
#include "Utils/FPoint.h"

class MoviePlayerFloatPoint {

private:

	enum {
		INT_FLOAT_RANGE = 16777216
			// от -INT_FLOAT_RANGE до INT_FLOAT_RANGE все целые числа
			// представляются типом float абсолютно точно
	};

public:

	float x, y;

	MoviePlayerFloatPoint()
		: x(0.0f)
		, y(0.0f)
	{}

	MoviePlayerFloatPoint(int x_, int y_)
		: x((float)x_)
		, y((float)y_)
	{
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
	}

	MoviePlayerFloatPoint(float x_, float y_)
		: x(x_)
		, y(y_)
	{
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
	}

	MoviePlayerFloatPoint(FPoint point) {
		point.GetXY(x, y);
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
	}

	//
	// Конструктор получения из целочисленной точки
	//
	MoviePlayerFloatPoint(IPoint p)
		: x((float)p.x)
		, y((float)p.y)
	{
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
	}

	//
	// Округление к целочисленной точке
	//
	IPoint Round() const {
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);

		return IPoint(math::round(x), math::round(y));
	}

	//
	// Вращение вокруг начала координат против часовой стрелки на angle радиан
	//
	MoviePlayerFloatPoint Rotate(float angle) const {
		float newX = x*cosf(angle) - y*sinf(angle);
		float newY = x*sinf(angle) + y*cosf(angle);

		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= newX && newX <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= newY && newY <= INT_FLOAT_RANGE);

		return MoviePlayerFloatPoint(newX, newY);
	}

	//
	// Растяжение относительно начала координат: X в xScale раз, Y в yScale раз
	//
	MoviePlayerFloatPoint Scale(float xScale, float yScale) const {
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= x*xScale && x*xScale <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y*yScale && y*yScale <= INT_FLOAT_RANGE);

		return MoviePlayerFloatPoint(x*xScale, y*yScale);
	}

	//
	// Получение расстояния от точки до начала координат
	//
	float GetDistanceToOrigin() const {
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);

		return sqrtf(x*x + y*y);
	}

	//
	// Получение угла точки в полярной системе координат
	// Ошибка, если точка совпадает с началом координат.
	// Результат - угол в радианах, может быть отрицательным.
	// Угол нулевой у точки (1, 0).
	//
	float GetAngle() const {
		assert(x != 0.0f || y != 0.0f);
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);

		return atan2f(y, x);
	}

	//
	// Получение ориентированного угла поворота от текущей точки ко второй
	// против часовой стрелки относительно начала координат.
	// Ошибка, если какая-нибудь точка совпадает с началом координат.
	// Результат - угол в радианах, может быть отрицательным.
	//
	float GetDirectedAngle(MoviePlayerFloatPoint second) const {
		float angle1 = GetAngle();
		float angle2 = second.GetAngle();
		return angle2 - angle1;
	}

	inline MoviePlayerFloatPoint operator + (MoviePlayerFloatPoint a) const {
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= a.x && a.x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= a.y && a.y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= x + a.x && x + a.x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y + a.y && y + a.y <= INT_FLOAT_RANGE);

		return MoviePlayerFloatPoint(x + a.x, y + a.y);
	}

	inline MoviePlayerFloatPoint operator - (MoviePlayerFloatPoint a) const {
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= a.x && a.x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= a.y && a.y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= x - a.x && x - a.x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y - a.y && y - a.y <= INT_FLOAT_RANGE);

		return MoviePlayerFloatPoint(x - a.x, y - a.y);
	}

	inline MoviePlayerFloatPoint operator - () const {
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);

		return MoviePlayerFloatPoint(-x, -y);
	}

	inline bool operator == (MoviePlayerFloatPoint a) const {
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= a.x && a.x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= a.y && a.y <= INT_FLOAT_RANGE);

		return ( x == a.x && y == a.y );
	}

	inline bool operator != (MoviePlayerFloatPoint a) const {
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= a.x && a.x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= a.y && a.y <= INT_FLOAT_RANGE);

		return ( x != a.x || y != a.y );
	}

	//
	// Вычитание с присваиванием.
	//
	MoviePlayerFloatPoint & operator -= (MoviePlayerFloatPoint second) {
		return *this = *this - second;
	}

	//
	// Добавление с присваиванием.
	//
	MoviePlayerFloatPoint & operator += (MoviePlayerFloatPoint second) {
		return *this = *this + second;
	}

	//
	// Оператор перевода в math::Vector3 с нулевым Z.
	//
	operator math::Vector3() {
		return math::Vector3(x, y, 0.0f);
	}

	operator FPoint() {
		return FPoint(x, y);
	}
};

//
// Умножение скаляра на точку.
//
inline MoviePlayerFloatPoint operator * (float scale, MoviePlayerFloatPoint p) {
	return p.Scale(scale, scale);
}

//
// Умножение точки на скаляр.
//
inline MoviePlayerFloatPoint operator * (MoviePlayerFloatPoint p, float scale) {
	return p.Scale(scale, scale);
}

class FloatRect {

private:

	enum {
		INT_FLOAT_RANGE = 16777216
			// от -INT_FLOAT_RANGE до INT_FLOAT_RANGE все целые числа
			// представляются типом float абсолютно точно
	};

	inline void CurrentStateAssert() const {
		assert(width >= 0.0f);
		assert(height >= 0.0f);
		assert(-INT_FLOAT_RANGE <= x && x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y && y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= x + width && x + width <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y + height && y + height <= INT_FLOAT_RANGE);
	}

public:

	float x, y;

	float width, height;

	FloatRect()
		: x(0.0f)
		, y(0.0f)
		, width(0.0f)
		, height(0.0f)
	{}

	FloatRect(int x_, int y_, int width_, int height_)
		: x((float)x_)
		, y((float)y_)
		, width((float)width_)
		, height((float)height_)
	{
		CurrentStateAssert();
	}

	FloatRect(float x_, float y_, float width_, float height_)
		: x(x_)
		, y(y_)
		, width(width_)
		, height(height_)
	{
		CurrentStateAssert();
	}

	FloatRect(const IRect &r)
		: x((float)r.x)
		, y((float)r.y)
		, width((float)r.width)
		, height((float)r.height)
	{
		CurrentStateAssert();
	}

	//
	// Содержит ли прямоугольник точку
	//
	bool DoesContain(const MoviePlayerFloatPoint &p) const {
		CurrentStateAssert();

		return ( x <= p.x && p.x < x + width && y <= p.y && p.y < y + height );
	}

	//
	// Установка начала прямоугольника в точку p
	//
	FloatRect MoveTo(const MoviePlayerFloatPoint &p) {
		CurrentStateAssert();
		assert(-INT_FLOAT_RANGE <= p.x && p.x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= p.y && p.y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= p.x + width && p.x + width <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= p.y + height && p.y + height <= INT_FLOAT_RANGE);

		return FloatRect(p.x, p.y, width, height);
	}

	//
	// Смещение начала прямоугольника на (p.x, p.y)
	//
	FloatRect MoveBy(const MoviePlayerFloatPoint &p) {
		CurrentStateAssert();
		assert(-INT_FLOAT_RANGE <= x + p.x && x + p.x <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y + p.y && y + p.y <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= x + p.x + width && x + p.x + width <= INT_FLOAT_RANGE);
		assert(-INT_FLOAT_RANGE <= y + p.y + height && y + p.y + height <= INT_FLOAT_RANGE);

		return FloatRect(x + p.x, y + p.y, width, height);
	}

};

#endif

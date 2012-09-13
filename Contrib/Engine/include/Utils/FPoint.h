#ifndef _FPOINT_H_
#define _FPOINT_H_

#include "Utils/Math.hpp"
#include "Utils/IPoint.h"
#include "Utils/Vector3.h"

/// Класс работы с двумерными точками с координатами типа float.
/// Инвариант: значения по модулю не больше максимального целого числа,
/// представимого типом float абсолютно точно.
class FPoint
{
private:

	/// от -INT_FLOAT_RANGE до INT_FLOAT_RANGE все целые числа
	/// представляются типом float абсолютно точно
	static const int INT_FLOAT_RANGE = 16777216;

public:

	/// x-координата точки
	float x;

	/// y-координата точки
	float y;

	/// Конструктор по умолчанию - заполнение нулями.
	FPoint();

	/// Конструктор из значений отдельных координат.
	FPoint(float x_, float y_);

	/// Конструктор получения из целочисленной точки.
	FPoint(const IPoint &p);

	FPoint(rapidxml::xml_node<>* elem);

	/// Получение x и y компонент.
	/// Не GetX и GetY - это намёк использовать операции над FPoint,
	/// а не реализовывать покомпонентные операции самостоятельно.
	void GetXY(float &x, float &y) const;

	/// Округление к целочисленной точке.
	IPoint Round() const;

	/// Вычитание точки.
	FPoint operator - (FPoint second) const;

	/// Добавление точки.
	FPoint operator + (FPoint second) const;

	/// Вычитание с присваиванием.
	FPoint & operator -= (FPoint second);

	/// Добавление с присваиванием.
	FPoint & operator += (FPoint second);

	/// Унарный минус.
	FPoint operator - () const;

	/// Сравнение точек на точное (!) равенство.
	/// Равенство можно гарантировать только после присваивания,
	/// но не как результат вычисления по формулам.
	bool operator == (FPoint second) const;

	/// Сравнение точек на точное (!) неравенство.
	/// Неравные на самом деле точки как правило неравны и при точном сравнении.
	/// См. также замечание к сравнению на равенство.
	bool operator != (FPoint second) const;

	/// Оператор перевода в math::Vector3 с нулевым Z.
	operator math::Vector3() const;

	/// Вращение вокруг начала координат против часовой стрелки на angle радиан.
	FPoint Rotate(float angle) const;

	/// Растяжение относительно начала координат: X в xScale раз, Y в yScale раз.
	FPoint Scale(float xScale, float yScale) const;

	/// Получение расстояния от точки до начала координат.
	float GetDistanceToOrigin() const;

	/// Получение расстояния от этой точки до другой.
	float GetDistanceTo(FPoint second) const;

	/// Получение угла точки в полярной системе координат
	/// Ошибка, если точка совпадает с началом координат.
	/// Результат - угол в радианах, может быть отрицательным.
	/// Угол нулевой у точки (1, 0).
	float GetAngle() const;

	/// Получение ориентированного угла поворота от текущей точки ко второй
	/// против часовой стрелки относительно начала координат.
	/// Ошибка, если какая-нибудь точка совпадает с началом координат.
	/// Результат - угол в радианах, может быть отрицательным.
	float GetDirectedAngle(FPoint second) const;

	/// Аналог GetDirectedAngle, приводящий результат к [0; 2PI).
	float GetDirectedAngleNormalize(FPoint second) const;

	/// Z-координата векторного произведения двух векторов,
	/// идущих из начала координат в эту и вторую точку.
	///
	/// Модуль получаемого числа является площадью параллелограмма
	/// с вершинами в 0, this, second и this + second.
	float GetVectorProduct(FPoint second) const;

	/// Вернуть скалярное произведение
	float GetDotProduct(FPoint second) const;

	/// Функция для использования FPoint в качестве параметра шаблона SplinePath.
	/// Не вникая в смысл, используем функцию для компонентов.
	static FPoint SplineInterpolation(FPoint v1, FPoint v2, FPoint g1, FPoint g2, float t);

	/// Функция для использования FPoint в качестве параметра шаблона SplinePath.
	/// Не вникая в смысл, используем функцию для компонентов.
	static FPoint GetGradient(FPoint v1, FPoint v2, FPoint g1, FPoint g2, float t);
	
	//operator const IPoint() const;
	// Так нельзя. Могу аргументированно пояснить :)
	// Если чо, у нас есть FPoint::Round()
};

/// Умножение скаляра на точку.
FPoint operator * (float scale, FPoint p);

/// Умножение точки на скаляр.
FPoint operator * (FPoint p, float scale);

/// Деление точки на скаляр.
FPoint operator / (FPoint p, float scale);

/// Умножение на другой вектор
FPoint operator * (FPoint p1, FPoint p2);

/// Функция для использования FPoint в качестве параметра шаблона SplinePath.
/// Не вникая в смысл, используем функцию для компонентов.
FPoint SplineInterpolation(FPoint v1, FPoint v2, FPoint g1, FPoint g2, float t);

/// Функция для использования FPoint в качестве параметра шаблона SplinePath.
/// Не вникая в смысл, используем функцию для компонентов.
FPoint GetGradient(FPoint v1, FPoint v2, FPoint g1, FPoint g2, float t);

#endif
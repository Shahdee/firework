#pragma once

#include "Utils/Int.h"
#include "Utils/Matrix4.h"
#include "Utils/EasingFunctions.h"

#undef min
#undef max

/// Пространство имён для математических функций
namespace math
{
	extern const float PI;
	extern const float OneByPI;

	template <typename T>
	inline T min(const T& v1, const T& v2) { return v1 < v2? v1 : v2; }

	template <typename T>
	inline T max(const T& v1, const T& v2) { return v1 > v2? v1 : v2; }
	
	/// Округление к ближайшему числу
	int round(float value);
	
	int floor(float value);
	int ceil(float value);

	/// Получение модуля числа типа float
	float abs(float value);

	/// Получение модуля числа типа int
	int abs(int value);

	/// Получение знака (-1/0/1) числа типа float
	int sign(float value);

	/// Получение знака (-1/0/1) числа типа int
	int sign(int value);

	/// Косинус числа типа float
	float cos(float value);
	
	/// Синус числа типа float
	float sin(float value);

	/// Квадратный корень числа
	float sqrt(float value);
	
	/// Тангенс
	float tan(float value);
	
	/// Арктангенс
	float atan(float y, float x);

	/// Возвращает left, если value<left; right, если value>right; иначе value
	float clamp(float left, float right, float value);
	int clamp(int left, int right, int value);

	/// Возвращает наименьшую степень двойки, бОльшую k.
	int GetNextPow2(int k);

	/// true, если i - степень двойки
	bool IsPow2(int i);

	/// Десятичный логарифм
	float log10(float v);

	/// Сравнивает два вещественных числа на приблизительное равенство
	bool IsEqualFloat(float float1, float float2, float delta = 0.00001f);
	
	/// Проверяет, является ли число Not a Number
	bool IsFloatNaN(float f);
	
	/// Возвращает значение Not a Number
	float FloatQuietNaN();
	
	/// Возвращает значение Infinity
	float FloatInfinity();
	
	/// Возвращает 1/value
	float FloatReciprocal(float value);
	
	/// Возвращает sqrt(value)
	float FloatSqrt(float value);
	
	/// Возвращает 1/sqrt(value)
	float FloatReciprocalSqrt(float value);
	
	/// Выделяет из матрицы преобразования отдельные составляющие смещения, поворота и масштабирования.
	void MatrixDecompose(const Matrix4& m, Vector3& translation, Quaternion& rotation, Vector3& scale);
	
	/// Линейная интерполяция двух матриц преобразования
	void MatrixLerp(Matrix4& out, const Matrix4& m1, const Matrix4& m2, float s);
};
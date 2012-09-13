#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

namespace math {

class Matrix4;

///
/// Четырёхмерный вектор.
///
class Vector4 {
public:
	static const Vector4 Zero;
		/// Нулевой вектор
	
	static const Vector4 One;
		/// Единичный вектор
	
	static const Vector4 UnitX;
		/// Единичный вектор, направленный вдоль оси X
	
	static const Vector4 UnitY;
		/// Единичный вектор, направленный вдоль оси Y
	
	static const Vector4 UnitZ;
		/// Единичный вектор, направленный вдоль оси Z
	
	static const Vector4 UnitW;
		/// Единичный вектор, направленный вдоль оси W
	
	Vector4();
	
	Vector4(float n);
	
	Vector4(float x, float y, float z, float w);
	
	Vector4(const Vector4& other);
	
	float& operator () (std::size_t item);
	
	float operator () (std::size_t item) const;
	
	operator float* ();
	
	operator const float* () const;
	
	Vector4& operator = (const Vector4& other);
	
	Vector4 operator - () const;
	
	Vector4 operator + (float value) const;
	
	Vector4 operator + (const Vector4& other) const;
	
	Vector4 operator - (float value) const;
	
	Vector4 operator - (const Vector4& other) const;
	
	Vector4 operator * (float value) const;
	
	Vector4 operator * (const Vector4& other) const;
	
	Vector4 operator / (float value) const;
	
	Vector4 operator / (const Vector4& other) const;
	
	Vector4& operator += (float value);
	
	Vector4& operator += (const Vector4& other);
	
	Vector4& operator -= (float value);
	
	Vector4& operator -= (const Vector4& other);
	
	Vector4& operator *= (float value);
	
	Vector4& operator *= (const Vector4& other);
	
	Vector4& operator /= (float value);
	
	Vector4& operator /= (const Vector4& other);
	
	bool operator < (const Vector4& other) const;
	
	bool operator <= (const Vector4& other) const;
	
	bool operator > (const Vector4& other) const;
	
	bool operator >= (const Vector4& other) const;
	
	bool operator == (const Vector4& other) const;
	
	bool operator != (const Vector4& other) const;
	
	bool Equals(const Vector4& other, float delta = 0.00001f) const;
		/// Проверяет, равен ли вектор указанному
	
	float Length() const;
		/// Возвращает длину вектора
	
	float LengthSquared() const;
		/// Возвращает квадрат длины вектора
	
	Vector4& SetLength(float length);
		/// Устанавливает длину вектора
	
	Vector4& Normalize();
		/// Нормализует вектор
	
	float Distance(const Vector4& other) const;
		/// Возвращает расстояние до указанного вектора
	
	float DistanceSquared(const Vector4& other) const;
		/// Возвращает квадрат расстояния до указанного вектора
	
	float DotProduct(const Vector4& other) const;
		/// Возвращает скалярное произведение на указанный вектор
	
	Vector4 Transform(const Matrix4& transform) const;
		/// Трансформирует вектор
	
	Vector4 Lerp(const Vector4& other, float s) const;
		/// Возвращает линейно интерполированный вектор

public:
	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};
};

} // namespace math

#endif // __VECTOR4_H__

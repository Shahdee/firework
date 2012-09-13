#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

namespace SceneGraph {

class Matrix4;

///
/// Трёхмерный вектор.
///
class Vector3 {
public:
	Vector3();
	
	Vector3(float n);
	
	Vector3(float x, float y, float z);
	
	Vector3(const Vector3& other);
	
	float& operator () (std::size_t item);
	
	float operator () (std::size_t item) const;
	
	operator float* ();
	
	operator const float* () const;
	
	Vector3& operator = (const Vector3& other);
	
	Vector3 operator - () const;
	
	Vector3 operator + (float value) const;
	
	Vector3 operator + (const Vector3& other) const;
	
	Vector3 operator - (float value) const;
	
	Vector3 operator - (const Vector3& other) const;
	
	Vector3 operator * (float value) const;
	
	Vector3 operator * (const Vector3& other) const;
	
	Vector3 operator / (float value) const;
	
	Vector3 operator / (const Vector3& other) const;
	
	Vector3& operator += (float value);
	
	Vector3& operator += (const Vector3& other);
	
	Vector3& operator -= (float value);
	
	Vector3& operator -= (const Vector3& other);
	
	Vector3& operator *= (float value);
	
	Vector3& operator *= (const Vector3& other);
	
	Vector3& operator /= (float value);
	
	Vector3& operator /= (const Vector3& other);
	
	bool operator < (const Vector3& other) const;
	
	bool operator <= (const Vector3& other) const;
	
	bool operator > (const Vector3& other) const;
	
	bool operator >= (const Vector3& other) const;
	
	bool operator == (const Vector3& other) const;
	
	bool operator != (const Vector3& other) const;
	
	bool Equals(const Vector3& other, float delta = 0.00001f) const;
		/// Проверяет, равен ли вектор указанному
	
	float Length() const;
		/// Возвращает длину вектора
	
	float LengthSq() const;
		/// Возвращает квадрат длины вектора
	
	Vector3& SetLength(float length);
		/// Устанавливает длину вектора
	
	Vector3& Normalize();
		/// Нормализует вектор
	
	float Distance(const Vector3& other) const;
		/// Возвращает расстояние до указанного вектора
	
	float DistanceSq(const Vector3& other) const;
		/// Возвращает квадрат расстояния до указанного вектора
	
	float DotProduct(const Vector3& other) const;
		/// Возвращает скалярное произведение на указанный вектор
	
	Vector3 CrossProduct(const Vector3& other) const;
		/// Возвращает векторное произведение на указанный вектор
	
	Vector3 TransformCoord(const Matrix4& transform) const;
		/// Трансформирует вектор как точку в пространстве
	
	Vector3 TransformNormal(const Matrix4& transform) const;
		/// Трансформирует вектор как нормаль, т.е. без перемещения
	
	Vector3 Lerp(const Vector3& other, float s) const;
		/// Производит линейную интерполяцию двух векторов

public:
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float v[3];
	};
};

} // namespace SceneGraph

#endif // __VECTOR3_H__

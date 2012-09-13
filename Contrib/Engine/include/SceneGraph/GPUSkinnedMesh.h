#ifndef __GPUSKINNEDMESH_H__
#define __GPUSKINNEDMESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SkinnedMesh.h"
#include "Render/ShaderProgram.h"

namespace SceneGraph {

///
/// Специальная структура матрицы кости для аппаратного скиннинга
/// За счёт удаления одного столбца можно вычислять больше костей в шейдере
///
class Matrix4x3
{
public:
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
		};
		float m[3][4];
		float v[12];
	};

	// Оператор присваивания транспонирует матрицу 4x4 и берёт только верхние 3 ряда матрицы
	Matrix4x3 & operator = (const math::Matrix4 &source)
	{
		_11 = source._11; _12 = source._21; _13 = source._31; _14 = source._41;
		_21 = source._12; _22 = source._22; _23 = source._32; _24 = source._42;
		_31 = source._13; _32 = source._23; _33 = source._33; _34 = source._43;
		return (*this);
	}
};

///
/// Скелетный меш с аппаратным скиннингом на GPU.
///
class GPUSkinnedMesh : public SkinnedMesh {
public:
	typedef boost::shared_ptr<GPUSkinnedMesh> HardPtr;
	
	typedef boost::weak_ptr<GPUSkinnedMesh> WeakPtr;
	
	struct Vertex {
		math::Vector3 position;
		union {
			float beta[5];
			struct {
				float weights[4];
				unsigned char indices[4];
			};
		};
		math::Vector3 normal;
		float tu, tv;
		
		static const unsigned long FVF;
	};
	
	Mesh::HardPtr Clone();
		/// Клонирует экземпляр объекта
	
	void LoadData();
		/// Загружает данные меша в аппаратные буферы
	
	void Draw() const;
		/// Рисует себя
	
	static GPUSkinnedMesh::HardPtr Create(std::size_t vertexCount, std::size_t faceCount);
		/// Создаёт объект меша, но не заполняет его данными

	virtual ~GPUSkinnedMesh();

protected:
	GPUSkinnedMesh(DWORD FVF, std::size_t stride, std::size_t vertexCount, std::size_t faceCount);
	
	GPUSkinnedMesh(const GPUSkinnedMesh& rhs);
	
	GPUSkinnedMesh& operator = (const GPUSkinnedMesh& rhs);
	
private:
	Render::ShaderProgram *_program;
		/// Шейдер для аппаратного скиннинга
	Matrix4x3 *_bones;
		/// Массив матриц костей
	unsigned int _bonesCount;
		/// Количество костей
};

} // namespace SceneGraph

#endif // __GPUSKINNEDMESH_H__

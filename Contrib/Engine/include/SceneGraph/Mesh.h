#ifndef __MESH_H__
#define __MESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/SceneNode.h"
#include "SceneGraph/DeviceBuffer.h"
#include "SceneGraph/Material.h"
#include "Utils/Vector3.h"

namespace SceneGraph {

class MeshData;

typedef boost::shared_ptr<MeshData> MeshDataHardPtr;
	// Здесь определяется дублирующий тип умного указателя для класса MeshData,
	// т.к. мы не можем включить здесь весь заголовочный файл во имя предотвращения
	// циклической зависимости.

///
/// Меш.
///
class Mesh {
public:
	typedef boost::shared_ptr<Mesh> HardPtr;
	
	typedef boost::weak_ptr<Mesh> WeakPtr;
	
	///
	/// Формат вершины.
	///
	struct Vertex {
		math::Vector3 position;
		math::Vector3 normal;
		float tu, tv;
		
		static const unsigned long FVF;
	};
	
	virtual ~Mesh();
	
	virtual Mesh::HardPtr Clone();
		/// Клонирует экземпляр объекта
	
	DeviceBuffer::HardPtr GetVertices() const;
		/// Возвращает буфер вершин
	
	DeviceBuffer::HardPtr GetIndices() const;
		/// Возвращает буфер индексов
	
	Material::HardPtr GetMaterial() const;
		/// Возвращает материал меша
	
	void SetMaterial(Material::HardPtr material);
		/// Устанавливает материал меша
	
	const MeshDataHardPtr GetData() const;
		/// Возвращает данные меша
	
	void SetData(MeshDataHardPtr data);
		/// Устанавливает данные меша
	
	virtual void LoadData();
		/// Загружает данные меша в аппаратные буферы
	
	virtual void Draw() const;
		/// Отрисовывает себя
	
	static Mesh::HardPtr Create(std::size_t vertexCount, std::size_t faceCount);
		/// Создаёт объект меша, но не заполняет его данными

protected:
	Mesh(DWORD FVF, std::size_t stride, std::size_t vertexCount, std::size_t faceCount);
	
	Mesh(const Mesh& rhs);
	
	Mesh& operator = (const Mesh& rhs);

protected:
	std::size_t _stride;
		/// Ширина структуры вершины в буфере
	
	std::size_t _vertexCount;
		/// Количество вершин
	
	std::size_t _faceCount;
		/// Количество граней
	
	DeviceBuffer::HardPtr _vertices;
		/// Буфер вершин
	
	DeviceBuffer::HardPtr _indices;
		/// Буфер индексов
	
	Material::HardPtr _material;
		/// Материал меша
	
	MeshDataHardPtr _data;
		/// Данные меша
};

} // namespace SceneGraph

#endif // __MESH_H__

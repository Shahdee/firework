#ifndef __MESHDATA_H__
#define __MESHDATA_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Mesh.h"
#include "AxisAlignedBoundingBox.h"

namespace SceneGraph {

///
/// Данные меша.
///
class MeshData {
public:
	typedef boost::shared_ptr<MeshData> HardPtr;
	
	typedef boost::weak_ptr<MeshData> WeakPtr;
	
	MeshData();
	
	MeshData(std::size_t vertices, std::size_t indices);
	
	void AddVertex(const Mesh::Vertex& vertex);
		/// Добавляет вершину в коллекцию
	
	void AddIndex(WORD index);
		/// Добавляет индекс в коллекцию
	
	const std::vector<Mesh::Vertex>& GetVertexData() const;
		/// Возвращает коллекцию вершин
	
	const std::vector<WORD>& GetIndexData() const;
		/// Возвращает коллекцию индексов
	
	const AxisAlignedBoundingBox& GetBoundingBox() const;
		/// Возвращает ограничивающий параллелепипед

private:
	std::vector<Mesh::Vertex> _vertices;
		/// Данные буфера вершин
	
	std::vector<WORD> _indices;
		/// Данные буфера индексов
	
	AxisAlignedBoundingBox _aabbox;
		/// Ограничивающий параллелепипед для набора точек
};

} // namespace SceneGraph

#endif // __MESHDATA_H__

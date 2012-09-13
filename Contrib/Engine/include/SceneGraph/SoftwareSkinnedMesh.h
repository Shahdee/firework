#ifndef __SOFTWARESKINNEDMESH_H__
#define __SOFTWARESKINNEDMESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SkinnedMesh.h"

namespace SceneGraph {

///
/// Скелетный меш с программным скиннингом.
///
class SoftwareSkinnedMesh : public SkinnedMesh {
public:
	typedef boost::shared_ptr<SoftwareSkinnedMesh> HardPtr;
	
	typedef boost::weak_ptr<SoftwareSkinnedMesh> WeakPtr;
	
	using Mesh::Vertex;
		/// Используется формат вершины статического меша
	
	Mesh::HardPtr Clone();
		/// Клонирует экземпляр объекта
	
	void LoadData();
		/// Загружает данные меша в аппаратные буферы
	
	void Draw() const;
		/// Рисует себя
	
	static SoftwareSkinnedMesh::HardPtr Create(std::size_t vertexCount, std::size_t faceCount);
		/// Создаёт объект меша, но не заполняет его данными

protected:
	SoftwareSkinnedMesh(DWORD FVF, std::size_t stride, std::size_t vertexCount, std::size_t faceCount);
	
	SoftwareSkinnedMesh(const SoftwareSkinnedMesh& rhs);
	
	SoftwareSkinnedMesh& operator = (const SoftwareSkinnedMesh& rhs);
	
	void UpdateSkin() const;
		/// Обновляет данные в буфере вершин для нового положения костей

private:
	std::vector< std::vector<BoneContent::VertexWeight> > _vertexWeights;
		/// Веса вершин, сформированные для программного блендинга костей
};

} // namespace SceneGraph

#endif // __SOFTWARESKINNEDMESH_H__

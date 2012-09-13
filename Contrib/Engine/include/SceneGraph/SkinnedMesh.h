#ifndef __SKINNEDMESH_H__
#define __SKINNEDMESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/Mesh.h"
#include "SceneGraph/BoneContent.h"
#include "Utils/Vector3.h"

namespace SceneGraph {

///
/// Скелетный меш.
///
class SkinnedMesh : public Mesh {
public:
	typedef boost::shared_ptr<SkinnedMesh> HardPtr;
	
	typedef boost::weak_ptr<SkinnedMesh> WeakPtr;
	
	///
	/// Формат вершины.
	///
	struct Vertex {
		math::Vector3 position;
		union {
			float beta[4];
			struct {
				float weights[3];
				unsigned char indices[4];
			};
		};
		math::Vector3 normal;
		float tu, tv;
		
		static const unsigned long FVF;
	};
	
	Mesh::HardPtr Clone();
		/// Клонирует экземпляр объекта
	
	void AddBoneContent(BoneContent::HardPtr content);
		/// Добавляет веса вершин для кости
	
	std::vector<BoneContent::HardPtr>& GetBonesContent();
		/// Возвращает коллекцию весов вершин меша
	
	void LoadData();
		/// Загружает данные меша в аппаратные буферы
	
	void Draw() const;
		/// Рисует себя
	
	static SkinnedMesh::HardPtr Create(std::size_t vertexCount, std::size_t faceCount);
		/// Создаёт объект меша, но не заполняет его данными

protected:
	SkinnedMesh(DWORD FVF, std::size_t stride, std::size_t vertexCount, std::size_t faceCount);
	
	SkinnedMesh(const SkinnedMesh& rhs);
	
	SkinnedMesh& operator = (const SkinnedMesh& rhs);
	
	void UpdateBoneMatrices() const;
		/// Обновляет матрицы смещения костей

protected:
	std::vector<BoneContent::HardPtr> _bonesContent;
		/// Кости, к которым привязан данный меш
	
	mutable std::vector<math::Matrix4> _matrices;
	mutable std::vector<math::Matrix4> _matricesOld;
		/// Массив матриц костей
	
	mutable int _differenceOfMatrices;
		/// Количество несовпадающих матриц после обновления костей
};

} // namespace SceneGraph

#endif // __SKINNEDMESH_H__

#ifndef __MESHNODE_H__
#define __MESHNODE_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneNode.h"
#include "Mesh.h"

namespace SceneGraph {

///
/// Узел сцены, визуализирующий набор мешей.
///
class MeshNode : public SceneNode {
public:
	typedef boost::shared_ptr<MeshNode> HardPtr;
	
	typedef boost::weak_ptr<MeshNode> WeakPtr;
	
	MeshNode(const std::string& name, SceneNode::WeakPtr parent, SceneWeakPtr scene);
	
	virtual SceneNode::HardPtr Clone();
	
	unsigned int GetRenderPass() const;
		/// Возвращает типы проходов визуализации, при которых должна производиться отрисовка узла

	void AddMesh(Mesh::HardPtr mesh);
		/// Добавляет меш к коллекции мешей узла
	
	std::vector<Mesh::HardPtr>& GetMeshes();
		/// Возвращает коллекцию мешей узла
	
	void Draw() const;
		/// Вызывается каждый фрейм для отрисовки узла

protected:
	MeshNode(const MeshNode& rhs);
	
	MeshNode& operator = (const MeshNode& rhs);

protected:
	std::vector<Mesh::HardPtr> _meshes;
		/// Набор мешей
};

} // namespace SceneGraph

#endif // __MESHNODE_H__

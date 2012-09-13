#ifndef __CAMERANODE_H__
#define __CAMERANODE_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/SceneNode.h"
#include "SceneGraph/Camera.h"

namespace SceneGraph {

class CameraNode : public SceneNode {
public:
	typedef boost::shared_ptr<CameraNode> HardPtr;
	
	typedef boost::weak_ptr<CameraNode> WeakPtr;
	
	CameraNode(const std::string& name, SceneNode::WeakPtr parent, SceneWeakPtr scene);
	
	CameraNode(const CameraNode& rhs);
	
	CameraNode& operator = (const CameraNode& rhs);
	
	SceneNode::HardPtr Clone();
	
	unsigned int GetRenderPass() const;
		/// Возвращает типы проходов визуализации, при которых должна производиться отрисовка узла
	
	Camera::HardPtr GetCamera() const;
		/// Возвращает камеру
	
	void SetCamera(Camera::HardPtr camera);
		/// Устанавливает камеру
	
	void SetActive() const;
		/// Делает камеру активной
	
	void Update(float dt);
		/// Вызывается каждый фрейм для реакции узла на течение времени
	
	void Draw() const;
		/// Устанавливает вид и перспективу

protected:
	Camera::HardPtr _camera;
};

} // namespace SceneGraph

#endif // __CAMERANODE_H__

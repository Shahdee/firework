#ifndef __SCENE_H__
#define __SCENE_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/SceneNode.h"
#include "SceneGraph/CameraNode.h"
#include "SceneGraph/LightNode.h"
#include "SceneGraph/ContentProvider.h"

namespace SceneGraph {

///
/// Типы проходов визуализации.
///
struct RenderPass {
	enum Type {
		Unknown = 0,
		Camera = 1,
		Light = 2,
		Opaque = 4,
		Transparent = 8,
		TransparentEffect = 16
	};
};

///
/// Сцена.
///
class Scene : public boost::enable_shared_from_this<Scene> {
public:
	typedef boost::shared_ptr<Scene> HardPtr;
	
	typedef boost::weak_ptr<Scene> WeakPtr;

	Scene();
	
	virtual ~Scene();
	
	SceneNode::HardPtr GetRootNode();
		/// Возвращает корневой узел сцены
	
	SceneNode::HardPtr AddSceneNode(SceneNode::HardPtr node
									, const math::Vector3& position = math::Vector3(0.0f, 0.0f, 0.0f)
									, const math::Vector3& rotation = math::Vector3(0.0f, 0.0f, 0.0f) // pitch, yaw, roll
									, const math::Vector3& scale = math::Vector3(1.0f, 1.0f, 1.0f));
		/// Добавляет новый узел в сцену
	
	CameraNode::HardPtr AddCamera(Camera::HardPtr camera);
		/// Добавляет камеру в сцену
	
	LightNode::HardPtr AddLight(Light::HardPtr light);
		/// Добавляет источник света в сцену
	
	Camera::HardPtr GetActiveCamera() const;
		/// Возвращает активную камеру
	
	void SetActiveCamera(Camera::HardPtr camera);
		/// Устанавливает активную камеру
	
	RenderPass::Type GetCurrentRenderPass() const;
		/// Возвращает текущий проход визуализации
	
	virtual void Update(float dt);
		/// Обновляет состояние сцены
	
	virtual void Draw();
		/// Отрисовывает сцену

protected:
	SceneNode::HardPtr _root;
		/// Корневой узел сцены
	
	Camera::HardPtr _activeCamera;
		/// Активная камера
	
	RenderPass::Type _currentRenderPass;
		/// Текущий проход визуализации
	
protected:
	static void RenderSceneNodes(SceneNode::HardPtr node, RenderPass::Type pass);
		/// Визуализирует узлы указанного типа, начиная с определённого узла
};

} // namespace SceneGraph

#endif // __SCENE_H__

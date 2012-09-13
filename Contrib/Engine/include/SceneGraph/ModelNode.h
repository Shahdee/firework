#ifndef __MODELNODE_H__
#define __MODELNODE_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/SceneNode.h"
#include "SceneGraph/Mesh.h"
#include "SceneGraph/Animation.h"

namespace SceneGraph {

///
/// Модель, которая может состоять из нескольких мешей и скелета.
/// Содержит набор анимаций, которые могут комбинироваться друг с другом.
///
class ModelNode : public SceneNode {
public:
	typedef boost::shared_ptr<ModelNode> HardPtr;
	
	typedef boost::weak_ptr<ModelNode> WeakPtr;
	
	typedef std::map<std::string, Animation::HardPtr> Animations;

	ModelNode(const std::string& name, SceneNode::WeakPtr parent, SceneWeakPtr scene);
	
	ModelNode::HardPtr CloneModel() const;
	
	SceneNode::HardPtr Clone();
	
	unsigned int GetRenderPass() const;
		/// Возвращает типы проходов визуализации, при которых должна производиться отрисовка узла
	
	SceneNode::HardPtr FindFrame(const std::string& name) const;
		/// Рекурсивно ищет узел среди фреймов
	
	bool AddFrame(SceneNode::HardPtr bone);
		/// Добавляет фрейм в коллекцию
	
	const Animations& GetAnimations() const;
		/// Возвращает коллекцию анимаций
	
	Animation::HardPtr GetAnimation(const std::string& name) const;
		/// Находит анимацию по имени
	
	void AddAnimation(Animation::HardPtr animation);
		/// Добавляет анимацию в коллекцию
	
	void Update(float dt);
		/// Реакция на течение времени
	
	void Draw() const;
		/// Рисует модель
	
	void ShowSkeleton(bool show);
		/// Отображать ли скелет
	
	void ShowBoundingBox(bool show);
		/// Отображать ли ограничивающий прямоугольник

	bool HitBoundingBox(const IPoint &mouse_pos) const;
		// Пересекает ли указанный луч из курсора BoundingBox модели 

protected:
	ModelNode(const ModelNode& rhs);
	
	ModelNode& operator = (const ModelNode& rhs);
	
	void DrawSkeleton() const;
		/// Рисует скелет
	
	void DrawSkeleton(SceneNode::HardPtr node, const math::Matrix4& matParent) const;
		/// Вспомогательный метод для рекурсивного рисования скелета
	
	void DrawBoundingBox() const;
		/// Рисует ограничивающий прямоугольник

protected:
	SceneNodesMap _frames;
		/// Иерархия фреймов модели
	
	Animations _animations;
		/// Набор анимаций модели.
		/// Модель может состоять из нескольких мешей в иерархии фреймов.
		/// Каждая анимация может включать в себя трансформации нескольких фреймов.
	
	bool _showSkeleton;
		/// Отображать ли скелет
	
	bool _showBoundingBox;
		/// Отображать ли ограничивающий прямоугольник
};

} // namespace SceneGraph

#endif // __MODELNODE_H__

#ifndef _RENDER_MODELANIMATION_H_
#define _RENDER_MODELANIMATION_H_

#include "SceneGraph.h"

namespace Render {

///
/// Класс анимации, воспроизводящей анимированные 3D модели.
///
class ModelAnimation {
public:
	typedef boost::shared_ptr<ModelAnimation> HardPtr;
	
	typedef boost::weak_ptr<ModelAnimation> WeakPtr;
	
	static ModelAnimation* getFromXml(rapidxml::xml_node<>* elem);
	
	ModelAnimation(rapidxml::xml_node<>* elem);
	
	ModelAnimation(const ModelAnimation& rhs);
		// Конструктор копий, используется для клонирования
	
	virtual ~ModelAnimation() {}
	
	virtual ModelAnimation* Clone() const;
		// Метод для клонирования объекта, используется в менеджере ресурсов
	
	SceneGraph::ModelNode::HardPtr GetModel() const;
	
	void MoveTo(const FPoint& position);
	
	void Update(float dt);
	
	void Draw();

private:
	math::Vector3 ExtractVector3(rapidxml::xml_node<>* elem);
	
	void RenderNodeHelper(SceneGraph::SceneNode::HardPtr node);

private:
	SceneGraph::ModelNode::HardPtr _model;
		// Отображаемая модель
	
	math::Matrix4 _modelTransform;
		// Трансформация исходной модели
	
	math::Matrix4 _viewProjTransform;
		// Трансформация вида-проекции для вывода модели на экран
	
	ModelAnimation& operator = (const ModelAnimation&);
		// Присваивание запрещено и неопределено
};

inline SceneGraph::ModelNode::HardPtr ModelAnimation::GetModel() const {
	return _model;
}

} // namespace Render

#endif // _RENDER_MODELANIMATION_H_

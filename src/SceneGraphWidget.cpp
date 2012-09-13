#include "stdafx.h"
#include "SceneGraphWidget.h"

///
/// Анимация движения узла по окружности.
///
class CirclePathAnimationChannel : public AnimationChannel {
public:
	CirclePathAnimationChannel(const math::Vector3& origin, const math::Vector3& axis, float radiansPerSec)
		: AnimationChannel("CirclePath")
		, _origin(origin)
		, _axis(axis)
		, _radiansPerSec(radiansPerSec)
	{
	}
	
	void OnAnimate(SceneNode::HardPtr node, float dt) {
		// Вычислить изменение трансформации узла с течением времени
		math::Matrix4 transform =
			math::Matrix4::Translation(-_origin) *
			math::Matrix4::RotationAxis(_axis, _radiansPerSec * dt) *
			math::Matrix4::Translation(_origin);
		// Применить трансформацию к узлу
		node->MultiplyRelativeTransform(transform);
	}

private:
	math::Vector3 _origin;
		/// Центр вращения
	math::Vector3 _axis;
		/// Ось вращения
	float _radiansPerSec;
		/// Угловая скорость
};


SceneGraphWidget::SceneGraphWidget(const std::string& name, Xml::TiXmlElement* xe)
	: GUI::Widget(name, xe)
	, _scene(new Scene())
{
	// Добавить в сцену камеру
	CameraNode::HardPtr pCameraNode = _scene->AddCamera(Camera::HardPtr(new Camera()));
	// ...и сделать эту камеру активной
	pCameraNode->SetActive();
	
	// Добавить в сцену направленный сверху источник света
	Light::HardPtr pLight = DirectionalLight::Create(math::Vector3(math::PI * 0.5f, 0, 0));
	pLight->SetDiffuseColor(ColorValue(1.0f, 1.0f, 1.0f));
	pLight->SetAmbientColor(ColorValue(0.4f, 0.4f, 0.4f));
	_scene->AddLight(pLight);
	
	// Сдвинуть всю сцену вдаль на 500 единиц
	_scene->GetRootNode()->SetRelativeTransform(math::Matrix4::Translation(0, 0, 500));
	
	// Загрузить модель из файла
	ModelNode::HardPtr pModel = _scene->LoadModel("models\\fish_01.xml");
	if (pModel) {
		// Добавить модель в сцену
		_scene->AddSceneNode(pModel, math::Vector3(150, 0, 0), math::Vector3(0, math::PI * 0.5f, 0));
		
		// Добавить пользовательскую анимацию к модели
		Animation::HardPtr pCustomAnim(new Animation("Custom Animation"));
		AnimationChannel::HardPtr pCirclePathAnim(
			new CirclePathAnimationChannel(math::Vector3(0, 0, 0), math::Vector3(0, 1, 0), -0.25f));
		pCustomAnim->AddChannel(pModel, pCirclePathAnim);
		pModel->AddAnimation(pCustomAnim);
		//pCustomAnim->Play();
		
		// Запустить все анимации
		const ModelNode::Animations& animations = pModel->GetAnimations();
		for (ModelNode::Animations::const_iterator it = animations.begin(); it != animations.end(); ++it) {
			(*it).second->Play();
		}
	}
}

void SceneGraphWidget::Update(float dt) {
	_scene->Update(dt);
}

void SceneGraphWidget::Draw() {
	_scene->Draw();
}

#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Light.h"

namespace SceneGraph {

///
/// Направленный источник света.
///
class DirectionalLight : public Light {
public:
	typedef boost::shared_ptr<DirectionalLight> HardPtr;
	
	typedef boost::weak_ptr<DirectionalLight> WeakPtr;
	
	Light::HardPtr Clone();

	Type GetType() const;
		/// Возвращает тип источника света
	
	static DirectionalLight::HardPtr Create(const math::Vector3& direction = math::Vector3(0.0f, -1.0f, 0.0f));

protected:
	DirectionalLight(const math::Vector3& direction);
};

} // namespace SceneGraph

#endif // __DIRECTIONALLIGHT_H__

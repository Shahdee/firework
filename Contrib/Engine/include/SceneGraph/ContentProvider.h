#ifndef __CONTENTPROVIDER_H__
#define __CONTENTPROVIDER_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/ModelNode.h"

namespace Render {
	class Texture;
}

namespace SceneGraph {

class Scene;

typedef boost::weak_ptr<Scene> SceneWeakPtr;
	// Здесь определяется дублирующий тип слабой ссылки для класса Scene,
	// т.к. мы не можем включить здесь весь заголовочный файл во имя предотвращения
	// циклической зависимости.

///
/// Базовый класс для провайдеров контента.
///
class ContentProvider {
public:
	typedef boost::shared_ptr<ContentProvider> HardPtr;
	
	typedef boost::weak_ptr<ContentProvider> WeakPtr;

	ContentProvider();
	
	virtual ~ContentProvider();
	
	virtual ModelNode::HardPtr LoadModel(const std::string& filename) = 0;
		/// Загружает модель из файла
};

} // namespace SceneGraph

#endif // __CONTENTPROVIDER_H__

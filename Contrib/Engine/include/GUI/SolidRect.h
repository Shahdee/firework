#pragma once

#include "GUI/Widget.h"

#include "Render/Texture.h"

namespace GUI {

	/// Прямоугольник залитый заданным цветом.

	/// Для создания экземпляра через Layer используется код подобный следующему:
	/// \code
	/// <SolidRect name="BlueRect">
	/// 	<rectangle x="150" y="200" width="200" height="200"/>
	/// 	<color r="0" g="0" b="255" a="255"/>
	/// </SolidRect>
	/// \endcode
	/// Где rectangle - координаты прямоугольника, color - цвет.

	class SolidRect : public GUI::Widget
	{

	public:
		SolidRect(const string& name_);
		SolidRect(const string& name_, Xml::TiXmlElement* xmlElement);
		virtual ~SolidRect();
		virtual void Draw();
	};
}
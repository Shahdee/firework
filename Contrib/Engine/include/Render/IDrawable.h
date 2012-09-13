#pragma once

#include "Utils/IPoint.h"

namespace Render {

	/// Интерфейс ко всему, что можно рисовать (Texture, Animation)
	class IDrawable {
	public:
		//virtual void Bind();
		virtual void Bind(int channel = 0) = 0;
		//virtual void Draw();
		virtual void Draw(const IPoint& p = IPoint(0,0)) = 0;
	};
}
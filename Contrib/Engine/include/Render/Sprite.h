#pragma once

#include "Render/Texture.h"
#include "Render/Animation.h"
#include "Utils/IPoint.h"
#include "Render/VertexBuffer.h"
#include <vector>

namespace Render {
	/// Высокоуровневый спрайт.

	/// Класс спрайта, кеширует информацию о положении текстуры,
	/// а так же умеет мультитекстурирование
	class Sprite
	{
	public:
		Sprite();
		Sprite(Texture *tex_, FRect pos_ = FRect(0, 0, 0, 0), FRect uv_ = FRect(.0f, 1.f, .0f, 1.f));
		~Sprite();

		void Draw();

		IRect GetRectangle();
		void SetRectangle(FRect r);
		void MoveTo(FPoint pos_);
		//FRect GetUV();
		//void SetUV(FRect uv_);
		void AppendLayer(Texture* tex, FRect uv = FRect(.0f, 1.f, .0f, 1.f));
		void AppendLayer(Animation* anim, FRect uv = FRect(.0f, 1.f, .0f, 1.f));
		void Clear();

	private:
		struct Layer {
			Texture * tex;
			Animation * anim;
			Layer();
		};
		std::vector<struct Layer> layers;
		std::vector<FRect> uvs;
		FRect position;
		VertexBuffer buffer;

		void UpdateBuffer();
	};

}
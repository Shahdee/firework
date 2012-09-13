#pragma once

#include "theora/theora.h"
#include "Render/Texture.h"

/// Эта текстура умеет загружать кадр yuv.
namespace Render {

	class YuvTexture: public Texture
	{
	public:
		YuvTexture(int x, int y, int width, int height);

		void LoadYuv(yuv_buffer* buffer);
		void Draw(int x, int y, int width, int height);
	
		virtual void TranslateUV(FRect &rect, FRect &uv);
	private:
		int _x;
		int _y;
		float _fUStart;
		float _fUEnd;
		float _fVEnd;
		float _fVStart;
	};
}
#pragma once

#include "Render/Texture.h"

namespace Render {

	class Sheet;

	/// Псевдо текстура ссылающаяся на участок более другой текстуры.

	/// Это псевдотекстура, которая не хранит в себе изображение, а отрисовывает часть родительского Sheet'а. Обращение к унаследованному image и всем его полям небезопасно, ибо данных там нет.
	/// Можно рисовать текстуру переопределёнными здесь методами, а так же можно использовать
	/// RenderDeviceImpl::TranslateUV.
	class PartialTexture: public Texture 
	{
		friend class Render::Sheet;

	protected:
		/// Текстура с изображением
		Texture* texture;
		/// координаты изображения в текстуре
		int baseX, baseY, width, height, innerX, innerY, frameWidth, frameHeight;
		/// создавать эту текстуру можно только из Sheet::GetTexture.
		PartialTexture(Texture* _t, int _x, int _y, int _w, int _h, int _ix, int _iy, int _fw, int _fh);

	public:
		virtual ~PartialTexture();

		/// Указывает нужно ли трансформировать текстурные координаты. Если да, то необходимо вызвать TranslateUV перед отрисовкой.
		virtual bool needTranslate();
		/// Трансформация текстурных координат. Вызывается в RenderDeviceImpl если needTranslate возвращает true.
		virtual void TranslateUV(FPoint &uv);
		/// Трансформация текстурных координат. Вызывается в RenderDeviceImpl если needTranslate возвращает true.
		virtual void TranslateUV(FRect &rect, FRect &uv);

		/// загрузить текстуру
		virtual void Upload(bool bCleanAfterUpload = true);
		/// забиндить текстуру
		virtual void Bind(int channel = 0, int stageOp = 0);
		/// забиндить альфа-канал текстуры
		virtual void BindAlpha();
		/// выгрузить текстуру
		virtual void Release();

		virtual void LoadFromFile(const string& filename);
		virtual void LoadFromImage(const Image& image_);
		virtual void GetPropertiesFromFile(const string& filename);
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IPoint& position);
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IPoint& position, const IRect& rect);
		/// отрисовка текстуры в заданной позиции с поворотом, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IPoint& position, const RectOrient orient);
		/// отрисовка текстуры в заданной позиции с поворотом, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IRect& rect, float xStart, float xEnd, float yStart, float yEnd);
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IRect& rect, const FRect& uv);
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(float x, float y, float width, float height, const FRect& uv);
		/// отрисовка текстуры в заданной позиции с деформацией, если текстура ещё не забиндена, она биндится
		virtual void DrawCut(const IPoint& position, float cut_factor_x, float cut_factor_y = 1.0f);
		
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const FPoint& position);
		/// отрисовка текстуры в заданной позиции с поворотом, если текстура ещё не забиндена, она биндится
		virtual void Draw(const FPoint& position, const RectOrient orient);
		/// отрисовка текстуры в заданной позиции с деформацией, если текстура ещё не забиндена, она биндится
		virtual void DrawCut(const FPoint& position, float cut_factor_x, float cut_factor_y = 1.0f);
		
		virtual bool isPixelTransparent(int x, int y);
		virtual bool isPixelOpaque(int x, int y);
	};

}

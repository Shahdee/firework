#ifndef _GUI_STRETCHBOX_H_
#define _GUI_STRETCHBOX_H_

#include "Render/Texture.h"

/**
 * Класс для отрисовки текстуры в прямоугольник произвольного размера,
 * с растягиванием внутренней части без растягивания углов.
 * Используется, к примеру, для отрисовки панелей с однородным в середине
 * фоном (в т.ч. для тултипов).
 * 
 * Есть также режим REPEAT - заполнение при помощи тайлинга.
 * 
 * Если размеры отрисовываемого прямоугольника отрицательные, то изображение
 * будет отражено.
 */
class StretchBox
{
protected:
	Render::Texture * tex;
	
	int left, right, top, bottom; /// отступы с каждой стороны текстуры.

	bool tiled; /// Использовать тайлинг вместо стретча.
	bool no_center; /// Не отрисовывать центр (для рамок)
	
	void GenStripes();
	
public:
	typedef enum {ST_FIXED, ST_STRETCHED} StripeType;
	
	typedef struct Stripe {
		int size;
		StripeType type;
		Stripe(int s, StripeType t) : size(s), type(t) {}
	} Stripe;
	
	StretchBox()
		: tex()
		, left(), right(), top(), bottom()
		, tiled(false)
		, no_center(false)
	{}
	StretchBox(Render::Texture * tex, int left, int right, int top, int bottom, bool tiled = false, bool no_center = false)
		: tex(tex)
		, left(left), right(right), top(top), bottom(bottom)
		, tiled(tiled)
		, no_center(no_center)
	{
		GenStripes();
	}

	StretchBox(Render::Texture *tex, const std::vector<Stripe> hor, const std::vector<Stripe> vert, bool tiled = false, bool no_center = false)
	:tex(tex)
	, horStripes(hor)
	, vertStripes(vert)
	, tiled(tiled)
	, no_center(no_center)
	{}

	~StretchBox() {}
	
	void initFromXml(Xml::TiXmlElement* xmlElement);

public:
	void Draw(float x1, float x2, float y1, float y2);
	
	void Draw(FRect rect) { Draw(rect.xStart, rect.xEnd, rect.yStart, rect.yEnd); }
	void Draw(IRect rect) { Draw(rect.x, rect.x + rect.width, rect.y, rect.y + rect.height); }
	void Draw(FPoint p, float w, float h) { Draw(p.x, p.x + w, p.y, p.y + h); }

	/// Проверка прозрачности точки.
	/// x, y отсчитываются от левого нижнего угла прямоугольника w x h.
	bool isPixelTransparent(float x, float y, float w, float h);

	Render::Texture * getTexture() { return tex; }

private:
	// Вспомогательные методы
	void DrawPart(float x1, float y1, float x2, float y2,
		float tx1, float ty1, float tx2, float ty2, float ww, float hh);
	void DrawTiled(float x, float y, float w, float h,
		float tx, float ty, float tw, float th, float ww, float hh);
	std::vector<Stripe> vertStripes, horStripes;	
};

#endif // _GUI_STRETCHBOX_H_

#ifndef _REDNER_RENDERFUNC_H_
#define _REDNER_RENDERFUNC_H_

/// Тут собраны платформо независымые функции для разнообразной отрисовки и прочего

#include <stack>
#include "Render/RenderDevice.h"
#include "Render/BitmapFont.h"

namespace Render {

	// для BitmapFontImpl
	void AddFontAlias(const std::string &newName, const std::string &oldName);

	struct BitmapCharImpl
	{
		int aWidth;
			// см. BitmapFont::CharInfo::aWidth

		int bWidth;
			// см. BitmapFont::CharInfo::bWidth

		int cWidth;
			// см. BitmapFont::CharInfo::cWidth

		float minU;
			// текстурная координата левой стороны квадрата буквы

		float maxU;
			// текстурная координата правой стороны квадрата буквы

		float minV;
			// текстурная координата нижней стороны квадрата буквы

		float maxV;
			// текстурная координата верхней стороны квадрата буквы
	};

	//
	// Растровый шрифт для использования в RenderDevice
	//
	struct BitmapFontImpl
	{
		Texture *tex;
			// текстура с изображением букв

		int fontHeight;
			// высота шрифта в пикселях

		int charTrack;
			// дополнительное расстояние между символами

		int yOffset;
			// отступы сверху и снизу для декорирования, не должны учитываться

		int spaceWidth;
			// spaceWidth == fontHeight / 4 - ширина пробела

		std::string fontName;
			// имя шрифта для загрузки текстуры

		// Коэффициент, на который умножается размер пробела при выводе его в качестве разделителя групп в больших числах
		float spaceCoeff;
		
		float scale;

		BitmapFontImpl();

		~BitmapFontImpl();

		BitmapFontImpl(const BitmapFontImpl& src);

		BitmapFontImpl& operator=(const BitmapFontImpl& src);

		//
		// Получение символа по его коду. Если символа не было - создаётся.
		//
		BitmapCharImpl& GetChar(int code);

		//
		// Занесён ли в таблицу символ code.
		//
		bool IsCharSet(int code);

		//
		// Зарезервировать место под символы
		//
		void ReserveChars(size_t size);

		void UploadTexture();
		void ReleaseTexture();
		
		float Height() { return (float)fontHeight * scale; }

	private:

		friend void AddFontAlias(const std::string &newName, const std::string &oldName);

		bool isAlias;

		typedef ushort CharIndex, *CharIndexPtr;

		std::vector<CharIndexPtr> charOffsets;
			// массив указателей на блоки длиной 256 элементов
			// старший байт кода символа - это индекс в charOffsets
			// младший - индекс в соответсвующем блоке
			// значение в блоке - индекс символа в массиве chars

		std::vector<BitmapCharImpl> chars;
			// Занесённые символы в порядке занесения,
			// индекс - не код символа.
	};

	/// Является ли символ пробелом
	bool CharIsASpace(int code);

	void FillStringBuffer(const std::string& str, Color* c = 0);
	QuadVert& getLetter(int i);

	int getFontHeight(const std::string& fontName);
	int getFontHeight();

	float getFontSpaceCoeff(const std::string &fontName);

	void setFontTrack(const std::string& fontName, int trackValue);
	void setFontTrack(int trackValue);
	void setSpaceWidthCorrect(int value);
	inline int getSpaceWidthCorrect();
	// Возвращает ширину пробела-разделителя групп разрядов в числах
	float getThousandsSpaceSeparatorWidth(BitmapFontImpl *fnt);

	int getStringBufferCount();

	int getStringWidth(const std::string& str, const std::string& fontName);
	int getStringWidth(const std::string& str);

//	void FillLetterRect(const std::string& str, const std::string& fontName, std::vector<FRect>& rects);
	void Upload(BitmapFont *font);
	bool isFontLoaded(const std::string &font_name);
	void UploadFontTexture(const std::string &fontName);
	void ReleaseFontTexture(const std::string &fontName);

	void Bind(BitmapFont *font);
	void BindFont(const std::string& font_name);
	void BindAlpha(BitmapFont* font);
	void BindFontAlpha(const std::string& font_name);
	BitmapFontImpl* GetFont(const std::string& font_name);
	BitmapFontImpl* GetFont();

	int getSpaceSize(const std::string& font);

	/// Печатать строку в буфер, можно принудительно задать цвет букф
	void PrintStringToBuffer(const std::string& str, VertexBuffer* vbuffer, Color* c = 0);
	void PrintString(int x, int y, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, bool centerHeight = false, bool formatNumbers = true);
	void PrintString(float x, float y, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, bool centerHeight = false, bool formatNumbers = true);
	void PrintString(const IPoint& pos, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, bool centerHeight = false, bool formatNumbers = true);
	void PrintString(const FPoint& pos, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, bool centerHeight = false, bool formatNumbers = true);
	// Собственно, рисует строку
	void PrintStringInternal(float x, float y, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, bool centerHeight = false);
	// Рисует строку с бликом шириной count символов, local_time in [0.0f, 1.0f], 
	void PrintBlickString(int count, float local_time, const Color &color, const FPoint &pos, const string& str, int fakeLen = 0, float scale = 1.0f, TextAlign align = LeftAlign, bool centerHeight = false, bool formatNumbers = true);
	// Рисует строку, сменяющую цвет
	void PrintStringChangingColor(const FPoint &pos, const std::string &str, float local_time, const Color &color, float scale = 1.0f, TextAlign align = LeftAlign, bool centerHeight = false, bool formatNumbers = true);
	// Печатать одну (или больше) букв. Отрисовка происходит без использования вертексного буфера.
	void PrintLetter(float x, float y, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, bool centerHeight = false);

	/// Текущая альфа домножается на multiplier,
	/// старая запоминается в стеке,
	/// восстановление с помощью EndAlphaMul
	///
	/// Множитель ожидается из отрезка [0;1]
	void BeginAlphaMul(float multiplier);
	/// Восстановление старой альфы после BeginAlphaMul
	void EndAlphaMul();

	/// Установка текущего цвета, как произведения заданного и предыдущего.
	/// Используется для управления цветом/альфой для вложенных объектов, значения их цвета/альфы не будут превышать заданных здесь.
	/// Обязательно нужно в конце блока использовать ResetColor, который восстановит исходное значение цвета.
	void SetColor(const Color& color);

	/// Восстанавливает предыдущее сохранённое значение цвета. Используется после SetColor.
	void ResetColor();
	/// Используется для контроля за глубиной стека
	int GetColorStackSize();

	// Псевдоним SetColor с более подходящим названием
	inline void BeginColor(const Color& color) {
		SetColor(color);
	}

	// Псевдоним ResetColor с более подходящим названием
	inline void EndColor() {
		ResetColor();
	}

	void DrawRect(int x, int y, int width, int height, float uStart = 0.f, float uEnd = 1.f, float vStart = 0.f, float vEnd = 1.f);
	void DrawRect(const IRect& rect, float uStart, float uEnd, float vStart, float vEnd);
	void DrawRect(const IRect& rect, const FRect& frect);
	void DrawRect(const IRect& rect, const FRect& frect, RectOrient orient);
	void DrawRect(int x, int y, int width, int height, float factorX, float factorY);
	void DrawRect(const IRect& rect);
	void DrawRect(const IRect& rect, float factorX, float factorY);
	void DrawRect(const IRect& rect, RectOrient orient);
	void DrawRect(const IRect& rect, float uStart, float uEnd, float vStart, float vEnd, RectOrient orient);

	void DrawRotatedQuad(float x, float y, float width, float height, float angle);
	void DrawQuad(const FRect& xy, const FRect& uv);
	void DrawQuad(float x, float y, float width, float height);
	void DrawQuad(float x, float y, float width, float height, FRect uv);
	void DrawQuad(float x, float y, float width, float height, FRect uv, FRect uv2);
	void DrawQuad(float x, float y, float width, float height, FRect uv, FRect uv2, FRect uv3);
	void DrawQuad(float x, float y, float width, float height, 
				  float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4,
				  float u21, float v21, float u22, float v22, float u23, float v23, float u24, float v24);
	void DrawQuad(float x, float y, float width, float height, RectOrient orient);
	void DrawQuad(float x, float y, float width, float height, float tex_delta);
	void DrawQuad(float x, float y, float width, float height, float factorX, float factorY);
	void DrawQuad(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4
		, float uStart=0.f, float uEnd=1.f, float vStart=0.f, float vEnd=1.f);
	void DrawQuad(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4
		, const Color& cv1, const Color& cv2, const Color& cv3, const Color& cv4
		, float uStart=0.f, float uEnd=1.f, float vStart=0.f, float vEnd=1.f);

	// функция, необходимая для DrawBlic
	int getAlphaForBlic(int x, int y, float alpha, float local_time);

	// рисуем блик слева направо (тексуру по которой пускаем блик, кол-во столбцов в сетке текстуры, время от 0 до 1, яркость блика)
	void DrawBlic(Texture *tex, int count, float local_time, float alpha);

	// рисуем диагональный блик слева направо
	void DrawDiagonalBlic(Texture *tex, int countX, int countY, float fi, float time, int alpha, Color c = Color(255, 255, 255));
	// аналог предыдущей функции, без использования текстуры 
	// (хорошо подходит для блика на полностью непрозрачных текстурах);
	// time всегда приводится к [0,1];
	// width определяет ширину бликовой полосы (0 -- отсутствует, 1 -- максимальная);
	// brightness >= 0 влияет на яркость полосы
	void DrawDiagonalGlare(const FRect& rect, int gridRows, int gridCols, float time, 
		float width = 1.0f, float brightness = 1.0f, int alpha = 255, Color c = Color(255, 255, 255));

	// появление текстуры слева-направо
	// blurring - количество пикселей размытия (для нечеткой границы)
	void DrawFromLeftToRight(Texture *tex, FPoint pos, float part, float blurring);
	
	// появление текстуры справа-налево
	// blurring - количество пикселей размытия (для нечеткой границы)
	void DrawFromRightToLeft(Texture *tex, FPoint pos, float part, float blurring);
	
	// появление текстуры снизу-вверх
	// blurring - количество пикселей размытия (для нечеткой границы)
	void DrawFromBottomToTop(Texture *tex, FPoint pos, float part, float blurring);
	
	// появление текстуры сверху-вниз
	// blurring - количество пикселей размытия (для нечеткой границы)
	void DrawFromTopToBottom(Texture *tex, FPoint pos, float part, float blurring);

	void DrawBlic(float w, float h, float wr, float hr, int count, float local_time, float alpha);
	
	/// Рисует отрезок [p1, p2)
	/// Важно: последний пиксел при этом не рисуется
	void DrawLine(FPoint p1, FPoint p2);

	// Рисует внутреннюю рамку прямоугольника толщиной 1 пиксель.
	// То есть если поверх нарисовать DrawRect, то рамка закроется
	// При этом MatrixScale не сможет повлиять на толщину.
	void DrawFrame(IRect r);

	// Проверить, входит ли прямоугольник в единичный квадрат (при текущей текстуре с адресацией CLAMP)
	bool CheckUV(const FRect& r);

	/// Стек цвета. Все Draw... методы (кроме Direct... методов) пересчитывают цвет/альфу точек, относительно заданных ранее. То есть, если был задан цвет ARGB=0.5,0.3,1,1, то рисование точки с цветом 1,0.5,0.5,1 приведёт к реальному значению 0.5,0.15,0.5,1. При восстановлении из стека предыдущего значения, пересчёт прекращается. Смотри SetColor и ResetColor.
	extern std::stack<Color> _colorStack;
}

#endif

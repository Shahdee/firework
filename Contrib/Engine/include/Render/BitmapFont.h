#ifndef _REDNER_BITMAPFONT_H_
#define _REDNER_BITMAPFONT_H_

#include "PixelType.h"

namespace Render
{

class Texture;
struct BitmapFontImpl;

//
// Растровый шрифт
// См. MSDN: Windows GDI/Fonts and Text/About Text Output/Formatting Text/
// В статье "Character Widths" освещены aWidth, bWidth, cWidth
// http://msdn2.microsoft.com/en-us/library/ms534206.aspx
// В статье "String Widths and Heights" освещены ascent и descent
// http://msdn2.microsoft.com/en-us/library/ms534015.aspx
//
class BitmapFont
{
public:

	std::string _fontName;
		// имя шрифта

	Texture *_texture;
		// текстура, на которой нарисованы буквы

	int _fontHeight;
		// высота строки текста/расстояние между последовательными строками

	int _charTrack;
		// дополнительное горизонтальное расстояние между символами

	int _spaceWidth;
		// ширина пробела

	int _yOffset;
		// Дополнительный отступ по Y сверху и снизу буквы для нанесения эффектов.
		// Эффекты-то должны наноситься, а вот расстояние между строками
		// зависеть от _yOffset не должно.

	int _width, _height;
		// размеры текстуры шрифта

	// Коэффициент, на который умножается размер пробела при выводе его в качестве разделителя групп в больших числах
	float _spaceCoeff;

	float _scale;

	// Этот флаг используется для iphone Retina и масштабирует шрифт в 2 раза меньше
	bool downscale;

	//
	// Информация об одном символе
	//
	struct CharInfo
	{
		int code;
			// код символа, >= 0

		int aWidth;
			// горизонтальный отступ от конца предыдущей буквы до начала текущей

		int bWidth;
			// ширина рисуемой части текущей буквы

		int cWidth;
			// горизонтальный отступ от конца рисуемой части буквы до конца буквы

		int x;
			// расстояние от левого края текстуры до места буквы, куда прибавляется B

		int y;
			// расстояние от нижнего края текстуры до буквы с отступом yOffset
	};

	std::vector<CharInfo> charInfo;
		// массив с информацией о символах

	typedef std::vector<CharInfo>::iterator Iterator;
		// прямой итератор по charInfo

	//
	// Получение свойств одной буквы по её номеру в списке
	//
	void GetCharProperties(size_t index, int &code, int &aWidth, int &bWidth, int &cWidth, int &x, int &y);

	//~ static std::string GenFontPath(const std::string &fontName);

public:

	//
	// Загрузка шрифта из файлов
	//
	BitmapFont(const std::string &fontName);
	
	void Load(const std::string &path, bool autoUpload, PixelType pixelType = PIXEL_TYPE_DEFAULT);

	std::string GetName() { return _fontName; }

	//
	// Заполнение BitmapFontImpl
	//
	void LoadTo(BitmapFontImpl& bf);

	//~ static Texture* LoadFontTexture(const std::string &fontName, PixelType pixelType = PIXEL_TYPE_DEFAULT);

	// Возвращает коэффициент, на который умножается размер пробела при отображении его в качестве разделителя разрядов
	float GetSpaceCoeff() const { return _spaceCoeff; }
};

}

#endif

#ifndef _PLAYRIX_TEXT_H_
#define _PLAYRIX_TEXT_H_

namespace Render
{
	class RenderDeviceImpl;
}

#include "Utils/IPoint.h"
#include "Render/RenderDevice.h"
#include "Render/VertexBuffer.h"

/// Аттрибуты текста, могут быть применены к любому отдельному слову
struct TextAttributes
{
	/// конструктор по умолчанию
	TextAttributes();
	/// название шрифта
	std::string font;
	/// масштаб вертикальный
	float yScale;
	/// масштаб горизонтальный
	float xScale;
	/// сдвиг по вертикали
	float shift;
	/// цвет
	Color color;
	/// ограничить ширину текста (обрабатывается только в TText)
	float width;

	/// выравнивание
	TextAlign align, valign;
};

/// Абстрактный элемент текста.
class TElement
{
public:
	TElement() {}
	/// отрисовка
	virtual void Draw(FPoint) = 0;
	/// замена аттрибутов совпадающих с src на соответствующие значения dest
	virtual void ChangeAttributes(const TextAttributes& src, const TextAttributes& dest);
	/// Получить атрибуты (для текста и строки возвращаются атрибуты первого слова)
	virtual const TextAttributes& GetAttributes() const = 0;
	/// размер слова на экране
	virtual IPoint GetSize() const = 0;
	/// перепарсить шаблоны заново (нужно при смене игрока, или при изменении включаемых переменных)
	virtual void Update() = 0;
	int getHeight() const { return GetSize().y; }
	int getWidth() const { return GetSize().x; }
	
	/// выискивание в строке аттрибутов и запись их в структуру
	static void ParseAttributes(const std::string& format, TextAttributes& attr);
	/// распарсить текст, заменить шаблоны, %username% и другие
	/// Возвращает true если найдены вхождения переменных
	static bool ParseText(std::string& str, std::map<std::string, std::string> *variables = 0);
	/// Найти место вставки аттрибутов в строку, начинает поиск с максимального значения входных индексов
	/// Возвращает четыре индекса - открывающую и закрывающую скобку для аттрибутов и для конца текста
	/// Если валидные аттрибуты не найдены, возвращает false
	static bool FindAttributes(const std::string& text, std::string::size_type& begin1, std::string::size_type& begin2, std::string::size_type& end1, std::string::size_type& end2);
	/// разделить строку на массив пар, в которых первый элемент аттрибут (может быть пустой строкой), а второй элемент собственно текст
	static std::vector<std::pair<std::string, std::string> > SplitTextAttributes(const std::string& text);
	/// Получить список свойств текста (те, что между # или %)
	static std::vector<std::string> GetTextProperties(const std::string &str);
protected:
	/// атрибуты
	TextAttributes attr;
};

/// Слово из текста.
/// Словом считается участок текста на строке с постоянными аттрибутами форматирования.
class TWord : public TElement
{
public:
	/// конструктор по умолчанию
	TWord();
	/// конструктор с данными, текст, явные атрибуты, атрибуты предка
	TWord(const std::string& _text, const std::string& _format = "", const TextAttributes* _attr = 0);
	/// возвращает чистый текст
	const std::string& ToString() const;
	/// отрисовка
	virtual void Draw(FPoint p);
	/// замена аттрибутов совпадающих с src на соответствующие значения dest
	virtual void ChangeAttributes(const TextAttributes& src, const TextAttributes& dest);
	/// Получить атрибуты (для текста и строки возвращаются атрибуты первого слова)
	virtual const TextAttributes& GetAttributes() const;
	/// размер слова на экране
	virtual IPoint GetSize() const;
	/// перепарсить шаблоны заново (нужно при смене игрока, или при изменении включаемых переменных)
	virtual void Update();
	/// деструктор
	~TWord();
	/// Добавляет к ширине пробела указанную величину. Используется для выравнивания строки по ширине.
	void AppendSpaceWidth(int w);

	const std::string& GetChars() const;

	/// Поместить координаты левых нижних углов всех символов слова в вектор
	/// Также поместить сами символы в вектор
	/// Гарантируется, что длины векторов будут равны
	void GetCoordinates(IPoint p, std::vector<IPoint>* coord, std::vector<std::string>* chars);
	const char& operator[](int i) const;

private:
	/// собственно текст
	std::string str;
	/// сохранённый размер слова
	IPoint _size;
	/// вершинный буфер
	VertexBuffer vbuffer;
	/// нужно обновить вершинный буфер
	bool needToUpdate;
	/// дополнительная ширина пробела
	int spaceWidth;
	/// вычисление размера слова
	void CalcSize();
};

/// Строка текста. Содержит одно или более слов TWord.
class TLine : public TElement
{
public:
	/// конструктор по умолчанию
	TLine();
	/// конструктор с данными, текст, явные атрибуты, атрибуты предка
	/// Контроль ширины не выполняется, вся входная строка будет обработана
	TLine(const std::string& _text, const std::string& _format = "", const TextAttributes* _attr = 0);
	/// добавить слово к строке, выполняется контроль ширины, не вместившийся остаток может быть возвращён назад
	/// Возвращает true если вся строка влезла по ширине
	bool AppendWord(const std::string& _text, const std::string& _format = "", const TextAttributes* _attr = 0, std::string* perenosica = 0);
	/// Добавляет к ширине пробела указанную величину. Используется для выравнивания строки по ширине.
	void AppendSpaceWidth(int w);
	/// возвращает чистый текст
	std::string ToString() const;
	/// отрисовка
	virtual void Draw(FPoint p);
	/// замена аттрибутов совпадающих с src на соответствующие значения dest
	virtual void ChangeAttributes(const TextAttributes& src, const TextAttributes& dest);
	/// Получить атрибуты (для текста и строки возвращаются атрибуты первого слова)
	virtual const TextAttributes& GetAttributes() const;
	/// размер строки на экране
	virtual IPoint GetSize() const;
	/// перепарсить шаблоны заново (нужно при смене игрока, или при изменении включаемых переменных)
	virtual void Update();
	/// деструктор
	~TLine();

	const std::vector<TWord>& GetWords() const;
	
	/// Поместить координаты левых нижних углов всех символов в вектор
	void GetCoordinates(IPoint p, std::vector<IPoint>* coord, std::vector<std::string>* chars);

	const TWord& operator[](int i) const;
private:
	/// слова
	std::vector<TWord> words;
	/// дополнительная ширина пробела
	int spaceWidth;
};

/// Класс текста. Содержит одну или более строк TLine.
class TText : public TElement
{
public:
	/// конструктор по умолчанию
	TText();
	/// конструктор копирования
	TText(const TText& text);
	/// конструктор с данными, текст, явные атрибуты, атрибуты предка
	TText(const std::string& _text, const std::string& _format = "", const TextAttributes* _attr = 0);
	/// создание из xml
	static TText GetFromXml(rapidxml::xml_node<>* elem);
	static TText GetFromXml(Xml::TiXmlElement* elem);
	/// добавить строку в текст
	void AppendLine(const std::string& _line, const std::string& format = "", const TextAttributes* attr = 0);
	/// возвращает чистый текст - строки, разделённые символов '\n'
	std::string ToString();
	/// отрисовка
	virtual void Draw(FPoint p);
	/// замена аттрибутов совпадающих с src на соответствующие значения dest
	virtual void ChangeAttributes(const TextAttributes& src, const TextAttributes& dest);
	/// Получить атрибуты (для текста и строки возвращаются атрибуты первого слова)
	virtual const TextAttributes& GetAttributes() const;
	/// размер текста на экране
	virtual IPoint GetSize() const;
	/// перепарсить шаблоны заново (нужно при смене игрока)
	/// при этом сбрасывается кеш переменных
	virtual void Update();
	/// деструктор
	~TText();
	const std::vector<TLine>& GetLines() const;

	/// Поместить координаты левых нижних углов всех символов текста в вектор
	void GetCoordinates(std::vector<IPoint>* coord, std::vector<std::string>* chars); 
	const TLine& operator[](int i) const;

	/// Обновить значение переменной в тексте
	TText& SetTextProperty(const std::string &propName, const std::string &propValue);
	/// Обновить текст, заменяя свойства на значения из кеша
	/// Ничего не делает !!! LEGACYCODE !!!
	void UpdateProperties();
	
	// Вернуть исходник строки
	std::string GetSource() const { return src; }

	// Установить новый исходник строки
	void SetSource(const std::string &str);
	
	// Содержит ли переменные
	bool IsMutable() const { return isMutable; }

	/// Операция присваивания для текстов
	TText &operator = (const TText &src);

	/// Обновить с проверкой
	void TrueUpdate();
	
	bool empty() { return ToString().size() == 0; }

private:
	/// строки
	std::vector<TLine> lines;
	
	/// исходный текст (без замены шаблонов) нужен для перегенерации
	std::string src;
	
	/// есть ли в тексте переменные
	bool isMutable;
	
	/// сами эти переменные
	std::map<std::string, std::string> variables;
	
	/// Нужно ли обновить перед рисованием (для реализации "ленивых" апдейтов)
	bool _update;
	
private:
	/// Пересчитать размер пробела на строках для выравнивания строк по ширине
	void CalcLinesWidth();

	/// Вставляет разделители в число (на входе должно быть валидное число)
	static std::string FormatNumbersHelper(const std::string &str);

	/// Требуется ли форматирование чисел с учетом региональных настроек? (нужно, если разделитель групп разрядов не пустая строка)
	static bool _isLocaleNumberFormatNeeded;

	/// Разделитель групп разрядов в числах
	static std::string _thousandsSeparator;

	/// Десятичная точка (символ, разделяющий целую и дробную части в десятичных дробях)
	static std::string _decimalPoint;
public:
	/// Указан ли разделитель групп разрядов в числах
	static bool IsLocaleNumberFormatNeeded();

	/// Возвращает разделитель групп разрядов в числах
	static const std::string & GetThousandsSeparator();

	/// Возвращает десятичную точку
	static const std::string & GetDecimalPoint();

	/// Устанавливает разделитель тысячных разрядов в числах. Разделитель задается в настройках приложения
	static void SetNumberFormatParameters(const std::string &thousandsSeparator);

	/// Возвращает отформатированное число с учетом разделителей групп разрядов в числах
	/// lookingInText - ищем в текстах? Если да, то игнорируются числа в тегах, например {color=255;255;255;255}...{}
	static std::string FormatNumbers(const std::string &str, bool lookingInText = false);

	/// Возвращает список позиций начал и концов чисел в строке
	/// str - строка, в которой ищутся числа
	/// lookingInText - ищем в текстах? Если да, то игнорируются числа в тегах, например {color=255;255;255;255}...{}
	static std::list<size_t> GetNumbersPositions(const std::string &str, bool lookingInText = false);

	/// Возвращает тру, если переданный символ является допустимым символом при записи числа
	static bool IsValidNumberChar(int code);

	/// Равен ли разделитель пробелу
	static bool IsThousandsSeparatorSpace();
	
	/// Обрезает с концов строки пробельные символы
	static std::string TrimString(const std::string& s);
};

typedef TText Text;

#endif

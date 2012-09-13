#ifndef UTILS_IRECT_H_INCLUDED
#define UTILS_IRECT_H_INCLUDED

//
// Целочисленый прямоугольник
//
struct IRect
{

public: /* members */
    
    int x;
    
    int y;
    
	int width;
    
    int height;

public: /* methods */
    
    // Конструктор по умолчанию - создает "нулевой" прямоугольник
	IRect();
    
    // Покомпонентный конструктор
	IRect(int x_, int y_, int width_, int height_);
	
    // Конструктор из FRect
	explicit IRect(const FRect& r);
    
    // Конструктор из XML
	IRect(rapidxml::xml_node<>*  elem);
    
    // Конструктор из XML
	IRect(Xml::TiXmlElement* elem);
    
    // Конструктор из точки, ширины и высоты
	IRect(IPoint p, int width_, int height_);
    
	// Содержит ли прямоугольник пиксел point
	// В отличие от CheckPoint не "захватывает"
	// пиксели снизу и справа.
	bool DoesContain(const IPoint& point) const;
    
	// Содержит ли другой прямоугольник полностью
	bool DoesContain(const IRect& rect) const;
    
	// расширить прямоугольник с каждой стороны на delta
	void Inflate(int delta);
    
	// Установка начала прямоугольника в точку p
	IRect MoveTo(IPoint p) const;
    
	// Смещение начала прямоугольника на (p.x, p.y)
	IRect MoveBy(IPoint p) const;
	
	// Результатом функции является
	// отсечение от текущего прямоугольника всего, что не попадает в second
	// Если прямоугольники имеют нулевую площадь пересечения - результат
	// вырождается в точку или отрезок на стороне second.
	// В случае отсутствия у прямоугольников хотя бы одной общей точки
	// функция некоммутативна
	IRect CutBy(const IRect& second) const;
	
	// Проверка на равенство с другим экземпляром
	bool operator == (const IRect& rect) const;
    
	bool operator != (const IRect& rect) const;

    // Древняя функция, рекомендуется использовать DoesContain()
	bool CheckPoint(const IPoint& point);
    
	void Rotate(RectOrient orient);
    
};

#endif UTILS_IRECT_H_INCLUDED
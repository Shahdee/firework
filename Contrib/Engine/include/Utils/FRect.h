#ifndef UTILS_FRECT_H_INCLUDED
#define UTILS_FRECT_H_INCLUDED

// Нецелочисленный прямоугольник
struct FRect
{
public: /* methods */
	
    // Конструктор по умолчанию (заполняет нулями)
    FRect();
    
    // Покомпонентный конструктор
	FRect(float xStart_, float xEnd_, float yStart_, float yEnd_);
    
    // Конструктор из целочисленного прямоугольника
	explicit FRect(const IRect& r);
    
    // Округление к целочисленному
	IRect Round();
    
	// Проверка на равенство с другим экземпляром
	bool operator ==(const FRect& rect);
    
    // Проверка на неравенство
	bool operator !=(const FRect& rect);
    
public: /* members */
    
    float xStart;

    float xEnd;
	
    float yStart;
    
    float yEnd;

};

#endif // UTILS_FRECT_H_INCLUDED
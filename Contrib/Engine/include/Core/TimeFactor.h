#pragma once

namespace Core {

//
//  ласс-множитель времени, умеющий замедл€ть и ускор€ть врем€.
//
class TimeFactor {

public:

	//
	//  онструктор по умолчанию
	// 
	TimeFactor();

	//
	// ¬озвращает значение множител€ времени
	//
	float GetValue();

	//
	// ¬ернуть строковое значение множител€ времени
	// 
	std::string ToString();

	//
	// ”величить множитель времени (ускорить всЄ)
	//
	void Increase();

	//
	// ”меньшить множитель времени (замедлить всЄ)
	//
	void Decrease();

	//
	// ¬ернуть к множитель к значению по умолчанию (1)
	//
	void Reset();

private:

	size_t DEFAULT_SCALE_INDEX;
		// индекс массива множителей по умолчанию

	size_t _currentScaleIndex;
		// текущий индекс массива множителей

	std::vector<float> _scales;
		// массив множителей времени

};

extern TimeFactor timeFactor;

} // namespace Core
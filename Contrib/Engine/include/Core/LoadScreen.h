#pragma once
#include "types.h"

namespace Core {
/// Абстрактный класс для экрана загрузки
class LoadScreen {
public:
	LoadScreen();
	virtual ~LoadScreen();
	virtual void Init() = 0;
	virtual void Update() = 0;
};
}
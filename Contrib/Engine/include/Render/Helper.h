#pragma once
#ifndef _HELPER_H_
#define _HELPER_H_

#include "Render/RenderDevice.h"

namespace Render {
/// Класс помощник. Гарантирует корректное восстановление стека матриц, контролирует стек цветов.
/// Нужно только лишь создать переменную экземпляра класса в начале процедуры или ограниченной области видимости
class Helper {
private:
	Render::MatrixMode oldmatrix;
	int worldStackSize;
	int projectionStackSize;
	int textureStackSize;
	int modelStackSize;
	int colorStackSize;
public:
	Helper(Render::MatrixMode newmatrix = Render::MODELVIEW);
	~Helper();
};

};
#endif // _HELPER_H_
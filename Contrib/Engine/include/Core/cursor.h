#ifndef _CORE_CURSOR_H_
#define _CORE_CURSOR_H_

#include "Render/Texture.h"

namespace Core
{

class Cursor
{
private:

	Render::Texture normal;
	Render::Texture active;
	Render::Texture press;

	Render::Texture* current;
	bool _isActive;
	bool _isPressed;

public:

	static IPoint HOT_POINT_REMOVAL;

	Cursor();
	virtual ~Cursor();
	virtual void Load();
	virtual void setNormal();
	virtual void setActive();
	virtual void setPress();
	virtual void Draw(const IPoint& pos);
	virtual bool isActive();
	virtual bool isPressed();
	virtual void Update(float dt);

	// Показать системный курсор мыши.
	static void ShowSystem();
	// Скрыть системный курсор мыши. Обычно чтобы его самим нарисовать.
	static void HideSystem();

};

}

#endif

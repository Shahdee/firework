#ifndef _GAMEFEATURES_H_
#define _GAMEFEATURES_H_

#include "Render/Texture.h"

namespace Screensaver
{

void RegisterName(const std::string &name);
// имя должно быть по типу "Fishdom Screensaver", все остальное приделается само

bool Install();
// выбрать наш скринсейвер в системе

void Uninstall();
// отключить скринсейвер (Windows), либо выбрать случайный (Mac)

bool IsInstalled();
// проверить, является ли наш скринсейвер выбранным в системе

}

bool InstallImageFileAsWallpaper(const std::string &name);
// установить картинку на рабочий стол
// под Windows - bmp
// под Mac - все поддерживаемые Маком (jpg, png, bmp)

bool SaveScreenshot(const std::string &name, Render::Texture **tex, const IRect &rect, const std::string &sigPath = "", const IPoint &sigPos = IPoint(0, 0));
// сохранить скриншот в файл на диске, если name непусто
// сохранить скриншот в текстуру, если tex не NULL
// добавить на скриншот логотип в позицию sigPos, если sigPath не пуст
// возвращает true, если name непусто и файл удачно сохранился
// если текстура создалась, то *tex не NULL, иначе - NULL

#endif

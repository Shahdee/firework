#pragma once

#include "FileAttributesCondition.h"

typedef std::vector<std::string> StringVector;

namespace File {
/// Статический класс, умеющий выдавать названия файлов в каталоге.
/// Обёртка ::FindFirstFile - ::FindNextFile - ::FindClose.
class DirectoryListing
{
public:

	/// Получение файлов с именем, удовлетворяющим маске mask,
	/// и атрибутами, удовлетворяющими attrCond.
	static StringVector Get(std::string mask, FileAttributesCondition attrCond = FileAttributesCondition());
	/// Получение файлов из пакета с именем, удовлетворяющим маске mask,
	/// и атрибутами, удовлетворяющими attrCond.
	static StringVector GetFromPack(std::string mask, FileAttributesCondition attrCond = FileAttributesCondition());
	/// Получение файлов из файловой системы с именем, удовлетворяющим маске mask,
	/// и атрибутами, удовлетворяющими attrCond.
	static StringVector GetFromFs(std::string mask, FileAttributesCondition attrCond = FileAttributesCondition());
};
}

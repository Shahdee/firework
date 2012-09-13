#pragma once

#ifndef ENGINE_TARGET_WIN32
#	define FILE_ATTRIBUTE_DIRECTORY 10
#	define FILE_ATTRIBUTE_HIDDEN 2
#endif

namespace File {
/// Условие на атрибуты файлов. Используется, скажем,
/// когда не хочется находить скрытые файлы и подкаталоги.
/// Обёртка для констант FILE_ATTRIBUTE_DIRECTORY и т.п.
class FileAttributesCondition
{
private:

	/// В единицы установлены биты небезразличных атрибутов.
	int _and;

	/// Значения битов, соответствующих единичным битам _and,
	/// показывают, какие значения атрибутов нужны.
	/// Остальные биты нулевые.
	int _eq;

	/// Создание условия на атрибуты с заданными параметрами _and и _eq.
	FileAttributesCondition(int _and, int _eq);

public:

	/// Создание всё принимающего условия на атрибуты.
	FileAttributesCondition();

	/// Проверка, что атрибуты удовлетворяют условию, заданному этим экземпляром.
	bool IsGood(int attributes);

	/// Добавление условия "только каталоги".
	FileAttributesCondition DirectoriesOnly();

	/// Добавление условия "без каталогов".
	FileAttributesCondition NoDirectories();

	/// Добавление условия "только скрытые".
	FileAttributesCondition HiddenOnly();

	/// Добавление условия "только не скрытые".
	FileAttributesCondition NoHidden();

};
}

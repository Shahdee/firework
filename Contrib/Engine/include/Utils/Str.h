#ifndef _UTILS_STR_H_
#define _UTILS_STR_H_

/// Статический класс с набором служебных функций.

/// Статический класс, содержащий функции работы со значениями типа std::string
/// В частности чтения XML-атрибутов с проверкой их существования
class String
{
public:

	/// Чтение строки из файла до перевода строки (который не возвращается частью строки)
	/// или до конца файла. Если уже конец файла - будет выдана пустая строка
	static std::string ReadLine(FILE *f);

	/// Если head является началом s, то оно отрезается и выдаётся true,
	/// в противном случае с s ничего не происходит и выдаётся false.
	static bool IsHeadCut(std::string &s, const char *head);

	/// Возвращает транслитерованную строку
	static std::string Translit(const std::string& s);

	/// заменяет слеши \ на вот такие / и убирает двойные, тройные и прочие
	static std::string SwapSlashes(const std::string& str);

	/// заменяет слеши / на вот такие \ и убирает двойные, тройные и прочие
	static std::string ReverseSwapSlashes(const std::string& str);

	/// возвращает имя файла без расширения 
	static std::string FilenameWithoutExtension(const std::string& filename);
	
	/// переводит в нижний регистр
	static std::string ToLower(const std::string& str);

	/// переводит в верхний регистр
	static std::string ToUpper(const std::string& str);

	/// сравнение строки с маской
	static bool CheckMask(const std::string& mask, const std::string& str);

	/// отсекание от концов строки пробелов (или других заданных символов)
	static std::string Trim(const std::string& str, char ch = ' ');

	/// разбивание одной строки на массив подстрок по указанному разделителю
	static std::vector<std::string> Split(const std::string& str, char ch, bool autotrim = false);

	static std::string Pad(const std::string& str, const std::string& pad, bool not_first_line = false);
};

#endif

#ifndef _CORE_LOCALE_H_
#define _CORE_LOCALE_H_

namespace Core
{

class Locale
{
public:

	Locale();

	// получить префикс для локальной папки в base например: de/, fr/, it/, es/ и т.д.
	// файлы из такой папки грузятся вместо файлов из base
	// работает при _useMUI = true
	std::string GetSystemLanguagePrefix();

/*	//
	// Замена в строке where всех вхождений what на by
	// Параметр-переменная isChanged устанавливается в true, если замена была.
	// (скопировано из TemplateLib)
	//
	static void ReplaceSingleText(std::string &where, std::string what, std::string by, bool &isChanged);

	//
	// Применить текущую локаль к тинихмл-элементу
	//
	void UseLocale(Xml::TiXmlElement* xe);

	//
	// Применить текущую локаль к строке
	//
	void UseLocale(std::string &res);*/

	//
	// Текущая локаль в виде строки
	//
	void SetLocale(const std::string &locale);
	std::string GetLocale();

	//
	// Игнорирование пробелов, для японского.
	// Не печатается пробел 0x20, пробел 0xA0 - печатается
	//
	void SetIgnoreSpaces(bool ignore);
	bool GetIgnoreSpaces();

	//
	// Кодировка для трансляции ввода с клпавиатуры. При юникоде (Mac, iPhone(?)) не должна использоваться.
	// 1251 - кириллица, 1252 - Latin 1 и т.д.
	//
	void SetCodepage(UINT codepage);
	UINT GetCodepage();

	void UseMui(const std::string &forceLocalePath = "");

	bool IsMuiUsed();

	// Вернуть идентификатор языка (для айфона: "en", "de", "fr")
	std::string GetLanguage();
	
private:

	std::string _locale;

	bool _ignoreSpaces;

	UINT _codepage;

	bool _useMui;

	std::string _muiPrefix;

	std::string _language;
		// языка для айфона
};

extern Locale locale;

}

#endif

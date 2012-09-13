#ifndef _UTF8_H_
#define _UTF8_H_

//
// Чтение символа из i-й позиции строки s и продвижение i на следующий символ.
// Аналог s[i++] & 0xFF при 8-битной кодировке. Чуть сложнее для UTF-8.
//
int Utf8_ReadChar(const std::string &s, size_t &i);

size_t Utf8_Length(const std::string &s);

std::string Utf8_Substr(const std::string &s, size_t off, size_t length);

std::string Utf8_Erase(const std::string &s, size_t off, size_t length);

std::string Utf8_Insert(const std::string &s, size_t off, const std::string &addStr);

#ifdef ENGINE_TARGET_WIN32
// для пейджа можно смотреть (ms-help://MS.MSDNQTR.2003APR.1033/intl/unicode_81rn.htm)

std::string codepage_to_utf8(const std::string &str, UINT page);

std::wstring codepage_to_unicode(const std::string &str, UINT page);

std::string unicode_to_utf8(const std::wstring &unicode);

std::string utf8_to_codepage(const std::string &str, UINT page);

std::wstring utf8_to_unicode(const std::string &utf8);

std::string unicode_to_codepage(const std::wstring &unicode, UINT page);

#else
#define codepage_to_utf8(s, p) (s)
#endif

#endif

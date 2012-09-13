#pragma once

///
/// Класс для чтения Zip архивов.
///
/// В случае ошибок бросает исключение std::runtime_error.
///
class ZipArchive {
public:
	ZipArchive();
	ZipArchive(const std::string& filename);
	
	virtual ~ZipArchive();
	
	void Open(const std::string& filename);
		/// Открывает архив. Открытый ранее архив автоматически закрывается
	void Close();
		/// Закрывает архив. Так же вызывается в деструкторе
	bool IsOpen() const;
		/// Проверяет, открыт ли архив
	
	void ListFiles(std::vector<std::string>& vec);
		/// Составляет список всех файлов, содержащихся в архиве
	bool FileExists(const std::string& filename);
		/// Проверяет, содержится ли файл в архиве
	void ReadFile(const std::string& filename, std::vector<unsigned char>& data, int appendExtraZeros = 0);
		/// Читает содержимое файла в буфер. Добавляет к данным указанное количество нулей

private:	
	ZipArchive(const ZipArchive&);
	ZipArchive& operator=(const ZipArchive&);
		// Запрещает копирование экземпляров класса

private:
	struct Impl;
	Impl* _pimpl;
		// Внутренняя реализация
};

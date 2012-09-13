#pragma once

#include <string>

namespace File {

	/// Проверка существования файла
	bool Exist(const std::string& filename);

	/// Проверка существования файла на файловой системе
	bool ExistInFs(const std::string& filename);

	/// Проверка существования файла в пакете
	bool ExistInPack(const std::string& filename);

	/// Установить заданную директорию текущей. Возвращает false при ошибке.
	bool cd(const std::string& dir);

	/// Копировать файл, если файл существует, то он не перезаписывается, и возвращается false;
	bool cp(const std::string& src, const std::string& dst);

	/// Перемещение файла, если файл существует, то он не перезаписывается, и возвращается false;
	bool mv(const std::string& src, const std::string& dst);

	/// Удаление файла.
	bool rm(const std::string& file);

	/// Удаление директории.
	void rmdirr(const std::string& path);

	/// Создать директорию
	void mkdir(const std::string& theDir);

	/// Извлечь имя файла из полного пути
	std::string fileName(const std::string &path);

	/// Каталог для записи всего
	std::string outputDirectory();

	/// Возвращает текущую директорию
	std::string pwd();

	/// Каталог "Документы"
	std::string GetDocumentsPath();

	/// Каталог "Общие Данные"
	std::string GetCommonAppDataPath();

	/// Каталог "Личные данне"
	std::string GetUserAppDataPath();
	
	/// загрузка файла целиком в память, возвращает 0 при неудаче
	/// буфер с файлом нужно потом очищать самим
	/// Загружается только файл из файловой системы, не из пакета, 
	/// так что пользоваться с осторожностью. См. ExistInFs()
	char* LoadFile(const std::string& fname, long *filesize=0, int appendSize = 0);
	
}
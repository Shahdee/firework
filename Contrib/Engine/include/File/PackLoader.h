#pragma once

extern "C" {
#include "jpeglib.h"
}

#include "png.h"

#define PACK_USE_MMAP
	/// Определяет, будет ли использованы проецируемые на адресное пространство файлы

#ifdef PACK_USE_MMAP
namespace boost { namespace interprocess {
class mapped_region;
}}
#include <boost/shared_ptr.hpp>
#endif

namespace File {

/// классы и процедуры для загрузки текстур из единого архивного файла

#define PACK_LOADED File::PackLoader::Self().IsPackFound()

/// это элемент пакета
typedef struct _PackItem {
	_PackItem();
	// название файла
	std::string name;
	/// размер файла
	long size;
	/// смещение относительно начала пакета в байтах
	long offset;
	bool operator<(const struct _PackItem& r2) const;
	bool operator>(const struct _PackItem& r2) const;
} PackItem;

typedef std::vector<PackItem> PackItemMap;

typedef enum {
	LoadOpenOnly = 0,
	LoadToMem,
	LoadTemporary
} PackLoadMode;

/// это содержимое пакета
typedef struct _Pack {
	/// Конструктор
	_Pack();
	/// В деструкторе освобождаются все ресурсы
	~_Pack();
	/// Сортировка индекса по алфавиту. Вызывать после загрузки индекса.
	void sort();
	/// Двоичный поиск элемента в индексе
	PackItem* find(const std::string& file);
	/// Собственно индекс
	PackItemMap index;
	/// Режим загрузки пакета
	PackLoadMode mode;
#ifdef PACK_USE_MMAP
	boost::shared_ptr<boost::interprocess::mapped_region> mapped;
#else
	/// Если пакет открыт, тут указатель на файловый поток.
	FILE* file;
	/// Если пакет загружен, тут указатель на память.
	void* pool;
#endif // PACK_USE_MMAP
} Pack;

typedef std::vector<Pack*> PackVector;

#ifndef PACK_USE_MMAP

/// Элемент кеша. Файл загружаемый из открываемого пакета будет положен сюда.
typedef struct _CacheItem {
	_CacheItem();
	/// размер файла
	long size;
	/// содержимое файла
	void* ptr;
} CacheItem;

typedef std::map<std::string, CacheItem> CacheItemMap;

#endif // PACK_USE_MMAP

/////////////////////////
///
/// класс загрузки пакета текстур
///
/////////////////////////

/// Менеджер пакетов ресурсов.
class PackLoader {
public:
	/// возвращает экземпляр объекта
	static PackLoader& Self();
	/// инициализирован ли пакет текстур
	bool IsPackFound();
	/// проверка существования файла
	bool IsFileExist(const std::string &filename);
	/// поиск файлов соответствующих маске в пакете
	std::vector<std::string> FindFiles(const std::string& mask);
	/// позиционирование на заданный файл
	bool Open(const std::string& file);
	/// освобождать ресурсы ранее открытого файла
	/// При работе с незагружаемым пакетом этот метод освобождает выделенную память.
	bool Close(const std::string& file);
	/// буфер, в котором содержится заданный ранее файл
	void* MemBuff();
	/// размер файлового буфера в байтах
	long SizeBuff();
	/// указатель на сохранённую позицию в буфере (0 если файл не инициализирован, равен MemBuff после Open)
	void* GetCurPtr();
	/// сохранить указатель на позицию в буфере (если произойдёт Open, то указатель сбросится на начало MemBuf)
	void SetCurPtr(void * ptr);
	/// деструктор
	~PackLoader();
private:
	/// флаг, инициализирован ли пакет
	bool inited;
	/// тут лежит текущий файл
	void* buff;
	/// тут позиция чтения текущего файла
	void* ptr;
	/// тут размер текущего файла
	long size;
	/// содержимое загруженных пакетов
	PackVector packs;

#ifndef PACK_USE_MMAP
	/// закешированные файлы из открываемых пакетов
	CacheItemMap cache;
#endif

	PackLoader(const std::string& packname);
	/// Удаляет загруженные пакеты
	void Clear();
	/// Пытается загрузить индексный файл с описанием пакетов. При неудаче возвращает false.
	bool LoadIndex(const std::string& indexfile);
	/// Пытается загрузить индекс из пакета, сам пакет загружается согласно mode.
	bool LoadIndexFromPackage(const std::string& package, PackLoadMode mode = LoadOpenOnly);
};

}
/////////////////////////
//
// процедуры для JPEG
//
/////////////////////////
/*
METHODDEF(void) PT_init_source(j_decompress_ptr pcinfo);
METHODDEF(boolean) PT_fill_input_buffer(j_decompress_ptr pcinfo);
METHODDEF(boolean) PT_resync_to_restart(j_decompress_ptr pcinfo, int desired);
METHODDEF(void) PT_skip_input_data(j_decompress_ptr pcinfo, long num_bytes);
*/
void PT_init_source(j_decompress_ptr pcinfo);
boolean PT_fill_input_buffer(j_decompress_ptr pcinfo);
boolean PT_resync_to_restart(j_decompress_ptr pcinfo, int desired);
void PT_skip_input_data(j_decompress_ptr pcinfo, long num_bytes);

/////////////////////////
//
// процедуры для PNG
//
/////////////////////////

void PT_read_png(png_structp _png, png_bytep _byte, png_size_t size);

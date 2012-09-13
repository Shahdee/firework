#pragma once

extern "C" {
#include "jpeglib.h"
}

#include "png.h"

#define PACK_USE_MMAP
	/// ����������, ����� �� ������������ ������������ �� �������� ������������ �����

#ifdef PACK_USE_MMAP
namespace boost { namespace interprocess {
class mapped_region;
}}
#include <boost/shared_ptr.hpp>
#endif

namespace File {

/// ������ � ��������� ��� �������� ������� �� ������� ��������� �����

#define PACK_LOADED File::PackLoader::Self().IsPackFound()

/// ��� ������� ������
typedef struct _PackItem {
	_PackItem();
	// �������� �����
	std::string name;
	/// ������ �����
	long size;
	/// �������� ������������ ������ ������ � ������
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

/// ��� ���������� ������
typedef struct _Pack {
	/// �����������
	_Pack();
	/// � ����������� ������������� ��� �������
	~_Pack();
	/// ���������� ������� �� ��������. �������� ����� �������� �������.
	void sort();
	/// �������� ����� �������� � �������
	PackItem* find(const std::string& file);
	/// ���������� ������
	PackItemMap index;
	/// ����� �������� ������
	PackLoadMode mode;
#ifdef PACK_USE_MMAP
	boost::shared_ptr<boost::interprocess::mapped_region> mapped;
#else
	/// ���� ����� ������, ��� ��������� �� �������� �����.
	FILE* file;
	/// ���� ����� ��������, ��� ��������� �� ������.
	void* pool;
#endif // PACK_USE_MMAP
} Pack;

typedef std::vector<Pack*> PackVector;

#ifndef PACK_USE_MMAP

/// ������� ����. ���� ����������� �� ������������ ������ ����� ������� ����.
typedef struct _CacheItem {
	_CacheItem();
	/// ������ �����
	long size;
	/// ���������� �����
	void* ptr;
} CacheItem;

typedef std::map<std::string, CacheItem> CacheItemMap;

#endif // PACK_USE_MMAP

/////////////////////////
///
/// ����� �������� ������ �������
///
/////////////////////////

/// �������� ������� ��������.
class PackLoader {
public:
	/// ���������� ��������� �������
	static PackLoader& Self();
	/// ��������������� �� ����� �������
	bool IsPackFound();
	/// �������� ������������� �����
	bool IsFileExist(const std::string &filename);
	/// ����� ������ ��������������� ����� � ������
	std::vector<std::string> FindFiles(const std::string& mask);
	/// ���������������� �� �������� ����
	bool Open(const std::string& file);
	/// ����������� ������� ����� ��������� �����
	/// ��� ������ � ������������� ������� ���� ����� ����������� ���������� ������.
	bool Close(const std::string& file);
	/// �����, � ������� ���������� �������� ����� ����
	void* MemBuff();
	/// ������ ��������� ������ � ������
	long SizeBuff();
	/// ��������� �� ���������� ������� � ������ (0 ���� ���� �� ���������������, ����� MemBuff ����� Open)
	void* GetCurPtr();
	/// ��������� ��������� �� ������� � ������ (���� ��������� Open, �� ��������� ��������� �� ������ MemBuf)
	void SetCurPtr(void * ptr);
	/// ����������
	~PackLoader();
private:
	/// ����, ��������������� �� �����
	bool inited;
	/// ��� ����� ������� ����
	void* buff;
	/// ��� ������� ������ �������� �����
	void* ptr;
	/// ��� ������ �������� �����
	long size;
	/// ���������� ����������� �������
	PackVector packs;

#ifndef PACK_USE_MMAP
	/// �������������� ����� �� ����������� �������
	CacheItemMap cache;
#endif

	PackLoader(const std::string& packname);
	/// ������� ����������� ������
	void Clear();
	/// �������� ��������� ��������� ���� � ��������� �������. ��� ������� ���������� false.
	bool LoadIndex(const std::string& indexfile);
	/// �������� ��������� ������ �� ������, ��� ����� ����������� �������� mode.
	bool LoadIndexFromPackage(const std::string& package, PackLoadMode mode = LoadOpenOnly);
};

}
/////////////////////////
//
// ��������� ��� JPEG
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
// ��������� ��� PNG
//
/////////////////////////

void PT_read_png(png_structp _png, png_bytep _byte, png_size_t size);

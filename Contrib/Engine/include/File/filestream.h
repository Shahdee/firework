#ifndef _FILE_FILESTREAM_H_
#define _FILE_FILESTREAM_H_

namespace File
{

//
// файл находящийся внутри пакета
//
class mem_file
{
private:

	BYTE *pMemBuf;

	size_t size_in_bytes, current_position;

	std::string file;
	
	bool standalone;

public:

	mem_file(bool standalone = false);

	~mem_file();

	bool is_open();

	void open(const std::string &filename);

	void close();

	std::string getline();

	bool eof();

	size_t read(void *buf, size_t size);

	size_t size();
	
	void rewind();

};

//
// файл на диске, совместим с FILE*, может использоваться для записи
//
class c_file
{
public:

	typedef FILE *descriptor_type;

private:

	descriptor_type fp;

public:

	c_file();

	c_file(const std::string& filename);

	~c_file();

	bool is_open();

	void open(const std::string &filename);

	void open_to_write(const std::string &filename);

	void close();

	bool eof();

	std::string getline();

	size_t read(void *buf, size_t size);

	size_t size();

	descriptor_type descriptor();
	
	void rewind();

};

//
// универсальный файл, сам определяет из какого места читаться
//
class uni_file
{
private:

	c_file file;

	mem_file mem;

public:

	uni_file(bool standalone = false);

	uni_file(const std::string& filename, bool standalone = false);

	bool is_open();

	void open(const std::string &filename);

	void close();

	bool eof();

	template <class T>
	uni_file& operator >> (T& in) {
		read(&in, sizeof(T));
		return *this;
	}

	std::string getline();

	size_t read(void *buf, size_t size);

	size_t size();
	
	void rewind();

};

}

#endif

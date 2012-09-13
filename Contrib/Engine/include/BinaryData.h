#ifndef _BINARYDATA_H_
#define _BINARYDATA_H_

typedef std::vector<BYTE> ByteVector;

class BinaryDataLoader
{
public:

	BinaryDataLoader();

	bool Load(std::string filename);

	bool LoadBool();

	BYTE LoadByte();

	int LoadInt();

	float LoadFloat();

	std::string LoadString();

private:

	size_t ptr;

	ByteVector data;

};

class BinaryDataSaver
{
public:

	BinaryDataSaver();

	bool Save(std::string filename);

	void SaveBool(bool value);

	void SaveByte(BYTE value);

	void SaveInt(int value);

	void SaveFloat(float value);

	void SaveString(const std::string &value);

private:

	ByteVector data;

};

#endif

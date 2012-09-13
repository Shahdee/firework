#ifndef _DATASTORE_H_
#define _DATASTORE_H_

#include "Utils/IPoint.h"

class Xml::TiXmlElement;

class DataVariable
{
private:

	enum VARIABLE_TYPE { TYPE_NONE=0, TYPE_INT, TYPE_FLOAT, TYPE_STRING, TYPE_BOOLEAN, TYPE_POINT, TYPE_RECT, TYPE_ARRAY };

	VARIABLE_TYPE type;

	// simple types
	union {
		int iValue;
		float fValue;
		bool bValue;
	};
	std::string sValue;
	IPoint iPValue;
	IRect iRValue;
	std::vector<DataVariable> array;

public:

	DataVariable();

	void Load(Xml::TiXmlElement* elem);
	void Save(Xml::TiXmlElement* elem);

	void Load(const std::string &strType, const std::string &strValue);
	void Save(std::string &strType, std::string &strValue);

	bool getBool() const;
	int getInt() const;
	float getFloat() const;
	std::string getString() const;
	IPoint getPoint() const;
	IRect getRect() const;

	DataVariable& element(int index);
	const DataVariable& getElement(int index) const;
	DataVariable& appendElement();
	int arraySize() const;

	void setBool(bool value);
	void setInt(int value);
	void setFloat(float value);
	void setString(const std::string &value);
	void setPoint(const IPoint &value);
	void setRect(const IRect &value);
};

class DataStore
{
private:

	typedef std::map<std::string, DataVariable> Data;

	Data _data;

	std::string DotToComma(const std::string &str);
	std::string CommaToDot(const std::string &str);
public:

	DataStore();
	~DataStore();

	void Clear();

	void Load(Xml::TiXmlElement* elem);
	void Save(Xml::TiXmlElement* elem);

	void LoadCSV(const std::wstring &filename);
	void SaveCSV(const std::wstring &filename);

	bool findName(const std::string &name);
	void erase(const std::string &name);

	bool getBool(const std::string &varName, bool def = false);
	int getInt(const std::string &varName, int def = 0);
	float getFloat(const std::string &varName, float def = 0.0f);
	std::string getString(const std::string &varName, const std::string &def = "");
	IPoint getPoint(const std::string &varName, const IPoint &def = IPoint());
	IRect getRect(const std::string &varName, const IRect &def = IRect());

	bool getArrBool(const std::string &varName, int index, bool def = false);
	int getArrInt(const std::string &varName, int index, int def = 0);
	float getArrFloat(const std::string &varName, int index, float def = 0.0f);
	std::string getArrString(const std::string &varName, int index, const std::string &def = "");
	IPoint getArrPoint(const std::string &varName, int index, const IPoint &def = IPoint());
	IRect getArrRect(const std::string &varName, int index, const IRect &def = IRect());
	int getArraySize(const std::string &varName);
	
	void setBool(const std::string &varName, bool value);
	void setInt(const std::string &varName, int value);
	void setFloat(const std::string &varName, float value);
	void setString(const std::string &varName, const std::string &value);
	void setPoint(const std::string &varName, const IPoint &value);
	void setRect(const std::string &varName, const IRect &value);

	void setArrBool(const std::string &varName, int index, bool value);
	void setArrInt(const std::string &varName, int index, int value);
	void setArrFloat(const std::string &varName, int index, float value);
	void setArrString(const std::string &varName, int index, const std::string &value);
	void setArrPoint(const std::string &varName, int index, const IPoint &value);
	void setArrRect(const std::string &varName, int index, const IRect &value);
	
};

#endif

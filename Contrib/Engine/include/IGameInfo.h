#ifndef _IGAMEINFO_H_
#define _IGAMEINFO_H_

#include "DataStore.h"

class IGameInfo
{
private:

	// глобальные переменные, сохраняются/загружаются из XML (global:)
	DataStore _globals;

	// глобальные свойства, создаются на время работы программы (temp:)
	DataStore _properties;

	// возможно сюда стоит добавить константы и локальные переменные (const и local:), но пока без них обойдемся
	DataStore _consts;

protected:

	void LoadGlobalData(Xml::TiXmlElement* elem);
	void SaveGlobalData(Xml::TiXmlElement* elem);
	void LoadConstData(Xml::TiXmlElement* elem);
	
	// доопределить в потомке для поддержки getString("local:..."), на вход уже пойдет просто имя переменной
	virtual std::string getLocalProperty(const std::string &name, const std::string &def = "") = 0;
	virtual void setLocalProperty(const std::string &name, const std::string &value) = 0;

public:

	IGameInfo();

	// выдают/задают значение строки по шаблону "тип_хранения:имя", например temp:ActivePlayerName
	std::string getProperty(const std::string &name, const std::string &def = "");
	void setProperty(const std::string &name, const std::string &value);
	template <class T>
	void setProperty(const std::string &name, const T &value) {
		std::string strValue = utils::lexical_cast(value);
		setProperty(name, strValue);
	}


	// Функции для работы с глобальными переменными
	int getGlobalInt(const std::string &name, int def = 0);
	void setGlobalInt(const std::string &name, int value);

	float getGlobalFloat(const std::string &name, float def = 0);
	void setGlobalFloat(const std::string &name, float value);

	bool getGlobalBool(const std::string &name, bool def = false);
	void setGlobalBool(const std::string &name, bool value);

	std::string getGlobalString(const std::string &name, const std::string &def = "");
	void setGlobalString(const std::string &name, const std::string &value);

	IPoint getGlobalPoint(const std::string &name, const IPoint &def = IPoint());
	void setGlobalPoint(const std::string &name, const IPoint &value);

	IRect getGlobalRect(const std::string &name, const IRect &def = IRect());
	void setGlobalRect(const std::string &name, const IRect &value);

	int getGlobalArrInt(const std::string &name, int index, int def = 0);
	void setGlobalArrInt(const std::string &name, int index, int value);
	
	float getGlobalArrFloat(const std::string &name, int index, float def = 0);
	void setGlobalArrFloat(const std::string &name, int index, float value);
	
	bool getGlobalArrBool(const std::string &name, int index, bool def = false);
	void setGlobalArrBool(const std::string &name, int index, bool value);
	
	std::string getGlobalArrString(const std::string &name, int index, const std::string &def = "");
	void setGlobalArrString(const std::string &name, int index, const std::string &value);
	
	IPoint getGlobalArrPoint(const std::string &name, int index, const IPoint &def = IPoint());
	void setGlobalArrPoint(const std::string &name, int index, const IPoint &value);
	
	IRect getGlobalArrRect(const std::string &name, int index, const IRect &def = IRect());
	void setGlobalArrRect(const std::string &name, int index, const IRect &value);
	
	bool globalNameDefined(const std::string &name);
	
	// Функции для работы с константами
	int getConstInt(const std::string &name, int def = 0);
	float getConstFloat(const std::string &name, float def = 0);
	bool getConstBool(const std::string &name, bool def = false);
	std::string getConstString(const std::string &name, const std::string &def = "");
	IPoint getConstPoint(const std::string &name, const IPoint &def = IPoint());
	IRect getConstRect(const std::string &name, const IRect &def = IRect());
	int getConstArrInt(const std::string &name, int index, int def = 0);
	float getConstArrFloat(const std::string &name, int index, float def = 0);
	bool getConstArrBool(const std::string &name, int index, bool def = false);
	std::string getConstArrString(const std::string &name, int index, const std::string &def = "");
	IPoint getConstArrPoint(const std::string &name, int index, const IPoint &def = IPoint());
	IRect getConstArrRect(const std::string &name, int index, const IRect &def = IRect());
	
};

extern IGameInfo *Engine_gameInfoPointer;

#endif

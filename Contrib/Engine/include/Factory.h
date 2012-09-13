#pragma once

#include "Core/MessageManager.h"
#include "Core/ControllerManager.h"
#include "GUI/Widget.h"

template<typename BaseClassType, typename ClassType>
BaseClassType *CreateObjectByVarList(VariableSet& varSet)
{
	return new ClassType(varSet);
}

template<typename BaseClassType, typename UniqueIdType>
class VarlistObjectFactory
{
protected:
	typedef BaseClassType *(*CreateObjectFunc)(VariableSet&);

public:
	typedef typename std::map<UniqueIdType, CreateObjectFunc>::const_iterator ConstIterator;
	typedef typename std::map<UniqueIdType, CreateObjectFunc>::iterator Iterator;


	template<typename ClassType>
		bool Register(UniqueIdType unique_id)
	{
		if (m_object_creator.find(unique_id) != m_object_creator.end())
			return false;

		m_object_creator[unique_id] = &CreateObjectByVarList<BaseClassType, ClassType>;

		return true;
	}

	bool Unregister(UniqueIdType unique_id)
	{
		return (m_object_creator.erase(unique_id) == 1);
	}

	BaseClassType *Create(UniqueIdType unique_id, VariableSet& varSet)
	{
		Iterator iter = m_object_creator.find(unique_id);

		if (iter == m_object_creator.end())
			return NULL;

		return ((*iter).second)(varSet);
	}

	ConstIterator GetBegin() const
	{
		return m_object_creator.begin();
	}

	Iterator GetBegin()
	{
		return m_object_creator.begin();
	}

	ConstIterator GetEnd() const
	{
		return m_object_creator.end();
	}

	Iterator GetEnd()
	{
		return m_object_creator.end();
	}

protected:
	std::map<UniqueIdType, CreateObjectFunc> m_object_creator;
};

template<typename WidgetType>
GUI::Widget *CreateWidgetFromXml(Xml::TiXmlElement* elem)
{
	string widgetName;
	if (!Xml::TiXmlQueryAttribute(elem, "name", widgetName))
	{
		//assert(false); // пропущено имя
		//return NULL;
	}
	return new WidgetType(widgetName, elem);
}

class XmlWidgetFactory
{
protected:
	typedef GUI::Widget *(*CreateObjectFunc)(Xml::TiXmlElement* elem);

public:
	typedef std::map<string, CreateObjectFunc>::const_iterator ConstIterator;
	typedef std::map<string, CreateObjectFunc>::iterator Iterator;


	template<typename WidgetType>
	bool Register(const string& unique_id)
	{
		if (m_object_creator.find(unique_id) != m_object_creator.end())
			return false;

		m_object_creator[unique_id] = &CreateWidgetFromXml<WidgetType>;

		return true;
	}

	bool Unregister(const string& unique_id)
	{
		return (m_object_creator.erase(unique_id) == 1);
	}

	GUI::Widget *Create(Xml::TiXmlElement* elem)
	{
		string widgetClass;
		widgetClass = string(elem->Value());
		Iterator iter = m_object_creator.find(widgetClass);
		if (iter == m_object_creator.end()) {
			assert(false); // вываливаемся здесь, чтобы видеть какого виджета не хватает
			return NULL;
		}

		return ((*iter).second)(elem);
	}
	
	// рекурсивный вариант предыдущего метода
	GUI::Widget *CreateTree(Xml::TiXmlElement* elem);

	ConstIterator GetBegin() const
	{
		return m_object_creator.begin();
	}

	Iterator GetBegin()
	{
		return m_object_creator.begin();
	}

	ConstIterator GetEnd() const
	{
		return m_object_creator.end();
	}

	Iterator GetEnd()
	{
		return m_object_creator.end();
	}

protected:
	std::map<string, CreateObjectFunc> m_object_creator;
};

namespace Factory
{
	typedef VarlistObjectFactory<IController, string> TControllerFactory;
	extern TControllerFactory controllerFactory;
	extern XmlWidgetFactory widgetFactoryXml;
	void RegisterTypes();
}

#define REGISTER_CONTROLLER(name) Factory::controllerFactory.Register<name>(#name)
#define REGISTER_WIDGET_XML(className, regName) Factory::widgetFactoryXml.Register<className>(regName)
#define UNREGISTER_WIDGET_XML(regName) Factory::widgetFactoryXml.Unregister(regName)

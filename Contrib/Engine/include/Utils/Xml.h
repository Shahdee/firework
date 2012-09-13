#pragma once

//
// Функции для более удобной работы с TinyXml.
// (установка и получение XML-атрибутов)
//
namespace Xml {

// Есть ли у xe атрибут name.
bool HasAttribute(Xml::TiXmlElement* xe, const std::string& name);

// Получить из элемента xe атрибут типа float; атрибут с таким именем обязан существовать.
float GetFloatAttribute(Xml::TiXmlElement* xe, const std::string& name);

// Получить из элемента xe атрибут типа bool; атрибут с таким именем обязан существовать.
bool GetBoolAttribute(Xml::TiXmlElement* xe, const std::string& name);

// Получить из элемента xe атрибут типа int; атрибут с таким именем обязан существовать.
int GetIntAttribute(Xml::TiXmlElement* xe, const std::string& name);

// Получить из элемента xe атрибут типа color; атрибут с таким именем обязан существовать.
Color GetColorAttribute(Xml::TiXmlElement* xe, const std::string& name);

// Получить из элемента xe атрибут типа std::string; атрибут с таким именем обязан существовать.
std::string GetStringAttribute(Xml::TiXmlElement* xe, const std::string& name);

// Получить из элемента xe атрибут типа float или вернуть значение по умолчанию
float GetFloatAttributeOrDef(Xml::TiXmlElement* xe, const std::string& name, float defaultValue);

// Получить из элемента xe атрибут типа bool или вернуть значение по умолчанию
bool GetBoolAttributeOrDef(Xml::TiXmlElement* xe, const std::string& name, bool defaultValue);

// Получить из элемента xe атрибут типа int или вернуть значение по умолчанию
int GetIntAttributeOrDef(Xml::TiXmlElement* xe, const std::string& name, int defaultValue);

// Получить из элемента xe атрибут типа color или вернуть значение по умолчанию
Color GetColorAttributeOrDef(Xml::TiXmlElement* xe, const std::string& name, Color defaultValue);

// Получить из элемента xe атрибут типа std::string или вернуть значение по умолчанию
std::string GetStringAttributeOrDef(Xml::TiXmlElement* xe, const std::string& name, std::string defaultValue);

// Установить в элементе xe атбирут типа bool
void SetBoolAttribute(Xml::TiXmlElement* xe, const std::string& name, bool value);

// Установить в элементе xe атбирут типа int
void SetIntAttribute(Xml::TiXmlElement* xe, const std::string& name, int value);

// Установить в элементе xe атбирут типа float
void SetFloatAttribute(Xml::TiXmlElement* xe, const std::string& name, float value);

// Установить в элементе xe атбирут типа std::string
void SetStringAttribute(Xml::TiXmlElement* xe, const std::string& name, const std::string& value);

// Установить в элементе xe атбирут типа Color
void SetColorAttribute(Xml::TiXmlElement* xe, const std::string& name, const Color& value);

// Открыть документ для чтения (осторожно - возвращает объект)
TiXmlDocument ReadDocument(const std::string& filename);

// rapid
// Есть ли у xe атрибут name.
bool HasAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа float; атрибут с таким именем обязан существовать.
float GetFloatAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа bool; атрибут с таким именем обязан существовать.
bool GetBoolAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа int; атрибут с таким именем обязан существовать.
int GetIntAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа color; атрибут с таким именем обязан существовать.
Color GetColorAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа std::string; атрибут с таким именем обязан существовать.
std::string GetStringAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа float или вернуть значение по умолчанию
float GetFloatAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, float defaultValue);

// Получить из элемента xe атрибут типа bool или вернуть значение по умолчанию
bool GetBoolAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, bool defaultValue);

// Получить из элемента xe атрибут типа int или вернуть значение по умолчанию
int GetIntAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, int defaultValue);

// Получить из элемента xe атрибут типа color или вернуть значение по умолчанию
Color GetColorAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, Color defaultValue);

// Получить из элемента xe атрибут типа std::string или вернуть значение по умолчанию
std::string GetStringAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, std::string defaultValue);

} // namespace Xml

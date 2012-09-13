#pragma once
#include "widget.h"

#include "Render/RenderDevice.h"

namespace GUI
{
	/// Статический текст.

	/// Для создания экземпляра через Layer нужно использовать код типа:
	/// \code
	///	<Text name="Text1">
	///	 <position x="400" y="300"/>
	///	 <text font="arial" scale="1.5" align="center">
	///   <line>Fishdom {color=255;0;0;255}C{}{scale=1.0}2{}{color=0;255;0;255}H{}{scale=1.0}5{}{color=0;0;255;255}OH{}</line>
    ///  </text>
	///	</Text>
	/// \endcode
	/// или
	/// \code
	/// <Text name="Text2">
	/// 	<position x="400" y="300"/>
	/// 	<text id="TextID_in_Language_xml"/>
	/// </Text>
	/// \endcode
	/// Если содержимое text начинается с # или с @, то остаток обрабатывается через Core::resourceManager.GetText.

	class StaticText : public Widget
	{
		TText* _text;
		bool textDelete;
		TextAttributes _attributes;

	public:
		StaticText(const string name_);
		StaticText(const string name_, Xml::TiXmlElement* xmlElement);

		~StaticText();

		virtual void Draw();
		virtual bool MouseDown(const IPoint& mouse_pos);
		virtual void AcceptMessage(const Message& message);

		/// Возвращает ссылку на текст.
		TText& GetText();
	};

}
#pragma once

#include "GUI/Widget.h"
#include "Render/Texture.h"
#include "GUI/CheckButton.h"

namespace GUI {

	/// Надо бы от этого класса избавиться
	class MessageWindow : public Widget
	{
		TText _text;
		Render::Texture* _tileTex;
		int _tileSize;
		double _space;

	public:
		GUI::CheckButton *checkButton;

		MessageWindow(string messageName, Render::Texture* tile);
		~MessageWindow();

		virtual void Draw();
	};
}
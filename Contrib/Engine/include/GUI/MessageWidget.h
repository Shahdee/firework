#pragma once
/*
 *  MessageWidget.h
 *  Engine
 *
 *  Created by vasiliym on 02.03.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GUI/Widget.h"
#include "Render/Texture.h"
#include "Render/VertexBuffer.h"

namespace GUI {
	
	class MessageWidget : public Widget {
	public:
		MessageWidget(const std::string &name_, Xml::TiXmlElement* xmlElement);
		~MessageWidget();
		
	private:
		TText *_text;
		Render::Texture* _tileTex;
		Render::Texture* _shadowTex;
		float _space;
		bool _slowMethod;
		VertexBuffer vb, vb_s;
		
		virtual bool MouseDown(const IPoint& mouse_pos);
		virtual void MouseUp(const IPoint& mouse_pos);
		virtual void Draw();
		virtual void AcceptMessage(const Message& message);
		
		void SetText(const std::string& textId);
		void DrawBackground(Render::Texture* tex);
	};
};
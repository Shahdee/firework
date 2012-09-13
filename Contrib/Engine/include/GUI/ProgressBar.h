/*
 *  ProgressBar.h
 *  Engine
 *
 *  Created by vasiliym on 13.05.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "GUI/Widget.h"
#include "Render/Texture.h"

namespace GUI {
	class ProgressBar: public Widget
	{
		int from, to;
		float pos, target, speed;
		Render::Texture* back, *front;
	public:
		ProgressBar(const std::string& name, Xml::TiXmlElement* xmlElement);

		virtual void Draw();
		virtual void Update(float);
		virtual void AcceptMessage(const Message& message);
	};

}
#pragma once
/*
 *  Slideshow.h
 *  Engine
 *
 *  Created by vasiliym on 01.03.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "GUI/Widget.h"
#include "Render/Texture.h"

namespace GUI {

	class Slideshow: public GUI::Widget {
	private:
		typedef struct Slide {
			Render::Texture* texture;
			TText* text;
			Slide();
			Slide(const std::string& textureId, const std::string& textId);
			void Draw(const IPoint& pos, float alpha = 1.f);
		} Slide;
		std::vector<Slide> slides;
		float timeout, curtime, changetime;
		bool loop, changing;
		int curslide, nextslide;
	public:
		Slideshow(const std::string &name_, Xml::TiXmlElement* xmlElement);
		virtual void AcceptMessage(const Message& message);
		virtual void Draw();
		virtual void Update(float dt);
		virtual bool MouseDown(const IPoint& mouse_pos);
	};
};


/*
 *  Color.h
 *  Engine
 *
 *  Created by Slava on 24.06.10.
 *  Copyright 2010 Playrix Entertainment. All rights reserved.
 *
 */

#pragma once

struct Color
{
	static const Color WHITE;
	
	static const Color BLACK;
	
	static const Color RED;
	
	static const Color GREEN;
	
	static const Color BLUE;
	
	static const Color BLACK_TRANSPARENT;
	
	static const Color WHITE_TRANSPARENT;
	
	union 
	{
		unsigned char pColor[4];
		struct 
		{
			unsigned char	red,
			green,
			blue,
			alpha;
		};
	};
	
	Color();
	
	Color(unsigned char red_, unsigned char green_, unsigned char blue_);
	
	Color(unsigned char red_, unsigned char green_, unsigned char blue_, unsigned char alpha_);
	
	Color(Xml::TiXmlElement* elem);

	Color(rapidxml::xml_node<>* elem);
	
	Color(DWORD argb);
	
	//
	// Читает цвет из строки.
	// Цвет задаётся в двух возможных форматах:
	// 1) "#RRGGBBAA", например #FFFFFFFF, #A10000;
	// 2) "RRR;GGG;BBB;AAA", например "128;255;60;50".
	//
	Color(const std::string& c);
	
	Color(unsigned char alpha_);

	Color& operator*=(const Color& c);
	
	bool operator==(const Color& c) const;
	
	bool operator!=(const Color& c) const { return !operator == (c); }
};

Color operator*(const Color& c1, const Color& c2);

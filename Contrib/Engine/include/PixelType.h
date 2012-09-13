/*
 *  PixelType.h
 *  Engine
 *
 *  Created by Slava on 2/18/11.
 *  Copyright 2011 Playrix Entertainment. All rights reserved.
 *
 */
#ifndef PIXEL_TYPE_H_INCLUDED
#define PIXEL_TYPE_H_INCLUDED

// Тип хранения цвета пикселя в видеопамяти
enum PixelType
{
	PIXEL_TYPE_DEFAULT = 0,
	
	PIXEL_TYPE_8888,
		// RGBA по 8 бит на каждый канал
		// в XML: pixelType="8888"
	
	PIXEL_TYPE_888,
		// RGB по 8 бит на канал (без альфа-канала)
		// в XML: pixelType="888"
	
	PIXEL_TYPE_4444,
		// 4 бита на каждый канал (16-битный цвет)
		// в XML: pixelType="4444"
	
	PIXEL_TYPE_5551,
		// по 5 бит на R, G, B и 1 бит на A
		// в XML: pixelType="5551"
	
	PIXEL_TYPE_565,
		// 5 бит на R, 6 бит на G, 5 бит на B, каждый пиксел подразумевается полностью непрозрачным
		// в XML: pixelType="565"
	
	PIXEL_TYPE_GRAY_8,
		// Монохромное изображение 8 бит на пиксел.
	
	PIXEL_TYPE_COMPRESSED,
		// Для сжатых изображений
};

// Прочитать PixelType из элемента TinyXML
// читается атрибут "pixelType", возможные значения:
// "4444", "5551", "565", "8888", "default"
PixelType ParsePixelType(Xml::TiXmlElement* xe);

// Прочитать PixelType из элемента RapidXML
// читается атрибут "pixelType", возможные значения:
// "4444", "5551", "565", "8888", "default"
PixelType ParsePixelType(rapidxml::xml_node<>* xn);

#endif

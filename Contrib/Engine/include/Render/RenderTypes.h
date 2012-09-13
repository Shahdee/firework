#pragma once

enum TextAlign
{
	LeftAlign,
	RightAlign,
	CenterAlign,
	TopAlign,
	BottomAlign,
	WidthAlign
};

enum DeviceMode
{
	DevFullscreen,
	DevWindowed
};

namespace Render
{
	enum MatrixMode
	{
		WORLD,
		MODELVIEW,
		PROJECTION,
		TEXTURE,
		TEXTURE0 = TEXTURE,
		TEXTURE1,
		TEXTURE2,
		TEXTURE3,
		TEXTURE4,
		TEXTURE5,
		TEXTURE6,
		TEXTURE7
	};

	enum BlendMode
	{
		ALPHA,
		MULTIPLY,	// не примен€етс€ в режиме premultiplied alpha
		ADD,
		REPLACE,	// не примен€етс€ в режиме premultiplied alpha
		INVMULTIPLY // инверсный multiply
	};

	enum AlphaBlendMode
	{
		DEFAULT,    // Ad * (1 - As) + As*As
		MULTIPLY_ALPHA,	// As * Ad
		ADD_ALPHA,		// As + Ad
		HOLD_ALPHA,		// Ad
	};
	
	enum FogMode
	{
		FOG_NONE,
		FOG_EXP,
		FOG_EXP2,
		FOG_LINEAR,
	};

	enum FogRenderState
	{
		RS_FOGTABLEMODE,
		RS_FOGVERTEXMODE,
	};

	enum StageOperation 
	{
		STAGE_DEFAULT = 0,     // режим совместимости со старым кодом
		
		STAGE_A_SKIP = 0x0000,        // не использовать альфу
		STAGE_A_REPLACE = 0x0001,     // заменить альфу
		STAGE_A_MODULATE = 0x0002,    // умножить альфу
		STAGE_A_INVMODULATE = 0x0003, // умножить на 1-A
		STAGE_A_ADD = 0x0004,         // сложить альфу
		STAGE_A_SUB = 0x0005,         // вычесть альфу
		STAGE_A_INTERPOLATE = 0x0006, // линейна€ интерпол€ци€ от предыдущего значени€ до текущего (задаЄтс€ альфой операции)

		STAGE_C_SKIP = 0x0000,        // не использовать цвет
		STAGE_C_REPLACE = 0x0100,     // заменить цвет
		STAGE_C_MODULATE = 0x0200,    // умножить цвет
		STAGE_C_INVMODULATE = 0x0300, // умножить на 1-C
		STAGE_C_ADD = 0x0400,         // сложить цвет
		STAGE_C_SUB = 0x0500,         // вычесть цвет
		STAGE_C_INTERPOLATE = 0x0600, // линейна€ интерпол€ци€ от предыдущего значени€ до текущего (задаЄтс€ альфой операции)
		STAGE_C_BLEND = 0x0700,        // смешение цвета Cp*(1-As)+Cs*As
		
		STAGE_PROJECTED = 0x00010000,

		STAGE_A_MASK = 0x00ff,
		STAGE_C_MASK = 0xff00
	};

	enum MultisampleType
	{
		MULTISAMPLE_NONE = 0,
		MULTISAMPLE_2_SAMPLES,
		MULTISAMPLE_3_SAMPLES,
		MULTISAMPLE_4_SAMPLES,
		MULTISAMPLE_5_SAMPLES,
		MULTISAMPLE_6_SAMPLES,
		MULTISAMPLE_7_SAMPLES,
		MULTISAMPLE_8_SAMPLES,
		MULTISAMPLE_9_SAMPLES,
		MULTISAMPLE_10_SAMPLES,
		MULTISAMPLE_11_SAMPLES,
		MULTISAMPLE_12_SAMPLES,
		MULTISAMPLE_13_SAMPLES,
		MULTISAMPLE_14_SAMPLES,
		MULTISAMPLE_15_SAMPLES,
		MULTISAMPLE_16_SAMPLES
	};

	enum PrimitiveType
	{
		POINTLIST,
		LINELIST,
		LINESTRIP,
		TRIANGLELIST,
		TRIANGLESTRIP,
		TRIANGLEFAN
	};

	struct QuadVert
	{
		QuadVert();
		QuadVert(float x_, float y_, float z_, DEVCOLOR color_, float u_, float v_);
		float x, y, z;
		DEVCOLOR color;
		float u, v;
	};

	struct QuadVertT2
	{
		QuadVertT2();
		QuadVertT2(float x_, float y_, float z_, DEVCOLOR color_, float u1_, float v1_, float u2_, float v2_);
		float x, y, z;
		DEVCOLOR color;
		float u1, v1;
		float u2, v2;
	};

	struct QuadVertT3
	{
		QuadVertT3();
		QuadVertT3(float x_, float y_, float z_, DEVCOLOR color_, float u1_, float v1_, float u2_, float v2_, float u3_, float v3_);
		float x, y, z;
		DEVCOLOR color;
		float u1, v1;
		float u2, v2;
		float u3, v3;
	};

	enum IndexFormat
	{
		INDEX16,
		INDEX32
	};
	


} // namespace Render

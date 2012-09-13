#pragma once

#include <list>
#include "BuildSettings.h"
#include "Render/Texture.h"

#ifndef MAKEFOURCC
	#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
		((unsigned int)(unsigned char)(ch0) | ((unsigned int)(unsigned char)(ch1) << 8) | \
		((unsigned int)(unsigned char)(ch2) << 16) | ((unsigned int)(unsigned char)(ch3) << 24))
#endif

//FOURCC codes for DX compressed-texture pixel formats.
#define FOURCC_DXT1 MAKEFOURCC('D', 'X', 'T', '1')
#define FOURCC_DXT2 MAKEFOURCC('D', 'X', 'T', '2')
#define FOURCC_DXT3 MAKEFOURCC('D', 'X', 'T', '3')
#define FOURCC_DXT4 MAKEFOURCC('D', 'X', 'T', '4')
#define FOURCC_DXT5 MAKEFOURCC('D', 'X', 'T', '5')

enum IMAGETYPE {
	IT_NONE = 0,
	IT_PNG,
	IT_JPG,
	IT_TGA,
	IT_PVRTC,
	IT_DDS
};

/* Structure matching the Microsoft's "DDS File Reference" documentation. */
struct DDS_file_header {
	int magic; /* must be "DDS\0" */
	int size; /* must be 124 */
	int flags;
	int height;
	int width;
	int pitchOrLinearSize;
	int depth;
	int mipMapCount;
	int reserved[11];
	struct {
		int size;
		int flags;
		int fourCC;
		int bitsPerPixel;
		int redMask;
		int greenMask;
		int blueMask;
		int alphaMask;
	} pixelFormat;
	struct {
		int caps;
		int caps2;
		int caps3;
		int caps4;
	} caps;
	int reserved2[1];
};

class ImageLoader
{
	friend class Render::Image;

	Render::Image* _image;
	std::string _filename;

	struct TGA_t
	{
		unsigned char IDLength;
		unsigned char ColorMapType;
		unsigned char ImageType;
		unsigned short ColorMapStart;
		unsigned short ColorMapLength;
		unsigned char ColorMapDepth;
		unsigned short XOffset;
		unsigned short YOffset;
		unsigned short Width;
		unsigned short Height;
		unsigned char Depth;
		unsigned char ImageDescriptor;
		unsigned char *ColorMap;
		unsigned char *Data;
	};

	static void TGA_GetPackets(unsigned char *data, int width, int height, int depth, FILE *stream);

	static bool LoadJpgHelper(Render::Image* image, const std::string& file, Render::Image::GfxFileInfo *info = 0);

public:
	ImageLoader(Render::Image* image, const std::string& filename);

	~ImageLoader();

	void Load();
	
	static void LoadJPG(Render::Image* image, const std::string& file, Render::Image::GfxFileInfo *info = 0);
	static void LoadTGA(Render::Image* image, const std::string& file, Render::Image::GfxFileInfo *info = 0);
	static void LoadPNG(Render::Image* image, const std::string& file, Render::Image::GfxFileInfo *info = 0);
	static void LoadBaseWithMask(Render::Image* image, const std::string& file, const std::string& file_a);
	static void LoadPVRTC(Render::Image* image, const std::string& file, Render::Image::GfxFileInfo *info = 0);
	static void LoadDDS(Render::Image* image, const std::string& file, Render::Image::GfxFileInfo *info = 0);

	static IMAGETYPE SelectImageType(std::string &file, std::string &file_a);
};

class ResizeToPowerOfTwo
{
public:
	ResizeToPowerOfTwo();
	~ResizeToPowerOfTwo();

	void apply(Render::Image *image);
};

class AddAlphaFromImage
{
	Render::Image *_alpha_source;
public:
	AddAlphaFromImage(Render::Image* alpha_source);

	~AddAlphaFromImage();

	void apply(Render::Image *image);
};

// все функии сохранения используют в качестве источника Image::image_pool

bool SavePNG(const std::string &baseName/*без расширения*/,bool needAlpha = false, int w_=0, int h_=0);

bool SaveImageAsJpeg(const std::string &path, int width, int height, int quality);
bool SaveImageAsPng(const std::string &path, int width, int height);
bool SaveImageAsBmp(const std::string &path, int width, int height);

/*
 *  Image.h
 *  Engine
 *
 *  Created by Slava on 2/17/11.
 *  Copyright 2011 Playrix Entertainment. All rights reserved.
 *
 */

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED
#include <set>
#include "PixelType.h"

namespace Render {
	
/// Изображение, загруженная в память текстура.
class Image
{
public:
	struct GfxFileInfo
	{
		std::string fileName;
		int width;
		int height;
		bool alphaChannel;
		
		bool operator == (const GfxFileInfo &second);
		bool operator < (const GfxFileInfo &second) const;
		bool operator > (const GfxFileInfo &second);
		bool operator <= (const GfxFileInfo &second);
		bool operator >= (const GfxFileInfo &second);
	};

public:
	static unsigned char* image_pool;
	static unsigned char* data_pool;
	
	static std::set<std::string> _usedFileInfo;
	static std::set<GfxFileInfo> _gfxFileInfo;
	static bool _gfxFileInfoLoaded;
	
	static void LoadGfxFileInfo();
	static void SaveGfxFileInfo();

public:
	unsigned int width, height;
	unsigned int components;
	unsigned int compressedSize;
	unsigned int compressedFormat;
	unsigned int mipLevels;

	unsigned char *data; ///< Используется ф-ей getPixel(). Чтобы заполнить data, нужно вызвать CopyFromPool().

	PixelType pixelType; ///< Формат пиксельных данных.

	bool alphaChannel;

private:
	bool _isAlphaMask;
	std::vector<BYTE> _alphaMask;
	unsigned int maskWidth, maskHeight;

public:
	Image();
	Image(const std::string& filename);
	~Image();

	void LoadFromFile(const std::string& filename);
	void ApplyPixelType(PixelType new_type);
	
	void GetPropertiesFromFile(const std::string& filename);
	
	template <class Loader>
	void Load(Loader& loader, PixelType pixelType)
	{
		loader.Load(pixelType);
	}
	
	template <class ImageAlgorithm>
	void Apply(ImageAlgorithm& algoritm)
	{
		algoritm.apply(this);
	}
	
	void CopyFromPool();
	void CopyToPool();
	void Clear();

	// Возвращает заданную компонентру пикселя. Не используйте этот метод, так как Image обычно не хранит эти данные.
	// Для альфа канала используйте Render::Texture::isPixelTransparent
	int getPixel(const IPoint& p, int offset = 0);
	
	bool IsPixelTransparent(int x, int y);
	
	void CreateAlphaMask(int alphaLimit, int w, int h, float scale_x = 1.f, float scale_y = 1.f);
	void LoadAlphaMask(const std::string& file, int w, int h, float scale_x = 1.f, float scale_y = 1.f);
};

} // namespace Render

#endif

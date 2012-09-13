#pragma once

#include <set>
#include <vector>
#include <map>
#include "Render/Image.h"
#include "Utils/FPoint.h"
#include "Utils/Math.hpp"

namespace Core
{
	class ResourceManagerImpl;
}

//typedef std::pair<math::Vector3, FPoint> TexturePoint;


//bool operator < () (const Image::GfxFileInfo& a, const Image::GfxFileInfo& b) {}

#ifdef ENGINE_TARGET_WIN32_DX9
struct IDirect3DTexture9;
#	define DEVTEXTURE IDirect3DTexture9*
#endif

#ifdef ENGINE_TARGET_WIN32_DX8
struct IDirect3DTexture8;
#	define DEVTEXTURE IDirect3DTexture8*
#endif

#ifdef ENGINE_TARGET_IPHONE
#	include <OpenGLES/ES1/gl.h>
#	define DEVTEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_MACOS
#	include <OpenGL/OpenGL.h>
#	define DEVTEXTURE GLuint
#endif

namespace Render
{

	class RenderDeviceImpl;
	class RenderDeviceGLES1;
	class RenderDeviceGLES2;
	class PartialTexture;

	/// Класс текстуры, всё умеет
	class Texture
	{
		friend class Render::RenderDeviceImpl;
		friend class Render::RenderDeviceGLES1;
		friend class Render::RenderDeviceGLES2;
		friend class Render::PartialTexture;
		friend class Core::ResourceManagerImpl;

	public:
		static std::size_t _memoryUsage;
		std::string textureID;
		std::string groupID;
		std::string path;
		/// текстура в принципе хоть раз биндилась
		bool wasBinded;

		enum FilteringType
		{
			NEAREST,
			BILINEAR,
			TRILINEAR
		};

		enum AdressType
		{
			REPEAT,
			CLAMP
		};

		enum ColorOperation
		{
			ADD,		// не применяется в режиме premultiplied alpha
			MODULATE
		};
		
	protected:
		/// текстура сейчас забиндена
		bool binded;
		/// была ли текстура загружена
		bool wasUploaded;
		DEVTEXTURE _tex;
		FilteringType _filter;
		AdressType _adress;
		ColorOperation _colorOp;

		/// прямоугольник вывода
		int _rect_width, _rect_height;

		/// размер изображения
		int _bitmap_width, _bitmap_height;

		float factorX, factorY; // Отношение bitmap_rect / render_rect
		bool padded; ///< true, если bitmap_rect != render_rect

		bool _dynamicTexture;

		/// Разрешить аппаратное сжатие для текстуры
		bool _allowCompress;

		/// количество mip уровней для генерации
		/// по умолчанию 1, нужно устанавливать 0 для генерации всех уровней
		int mipmaps;


		PixelType _pixelType; ///< тип хранения цвета пикселя в видеопамяти

		int crop_x, crop_y; ///< использовать только часть изображения (например, для PVRTC).

		float _prescale_x, _prescale_y; ///< премасштабировать текстуру при загрузке.
		
		bool _isAlphaMask; ///< Нужно ли загружать альфа-маску.
		int _alphaLimit; ///< Пороговое значение для альфа-маски.
		
	public:
		Image image;

		Texture();
		Texture(const std::string& filename, bool needBiteMask = false, int alphaLimit = 1);
		Texture(int width, int height, unsigned char fill);
		Texture(int width, int height, PixelType pixelType, unsigned char fill);

		static Texture* getFromXml(rapidxml::xml_node<>* elem);
		static Texture* getFromXml(Xml::TiXmlElement* elem);
		virtual ~Texture();

		/// Текстура не загружена, или принудительно выгружена. Принудительно выгружаются динамические текстуры при переинициализации RenderDeviceImpl. См. Texture::setDynamic
		bool Empty();
		/// Динамическая текстура, используется для отображения видео ogg/theora. Динамическая текстура может быть принудительно выгружена при переинициализации RenderDeviceImpl. См. Texture::Empty, RenderDeviceImpl::RegisterDynamicTexture
		void setDynamic(bool dynamic);
		/// Указывает нужно ли трансформировать текстурные координаты. Если да, то необходимо вызвать TranslateUV перед отрисовкой.
		virtual bool needTranslate();
		/// Трансформация текстурных координат. Вызывается в RenderDeviceImpl если needTranslate возвращает true.
		virtual void TranslateUV(FPoint &uv);
		/// Трансформация текстурных координат. Вызывается в RenderDeviceImpl если needTranslate возвращает true.
		virtual void TranslateUV(FRect &rect, FRect &uv);

		void setFilter(FilteringType filter);
		void setAdress(AdressType adress);

		/// Вернуть тип адресации текстуры
		AdressType GetAddressType();

		void setColorOperation(ColorOperation colorOp);
		/// загрузить текстуру
		virtual void Upload(bool bCleanAfterUpload = true);
		
		///перегрузить прямоугольник текстуры
		///es1 only
		virtual void UploadRegion(int x, int y, int width, int height, const char* data);
		
		/// перезагрузка динамической текстуры
		void Reload();
		// две функции Lock&Unlock для записи непосредственно в текстуру, минуя назойливый image_pool
		void Lock(DWORD *&frame);
		void Unlock();
		/// забиндить текстуру в заданный канал
		virtual void Bind(int channel = 0, int stageOp = 0);
		/// забиндить альфа-канал текстуры
		virtual void BindAlpha();
		/// выгрузить текстуру
		virtual void Release();

		virtual void LoadFromFile(const std::string& filename);
		void LoadFromFileWithoutMask(const std::string& filename);
		virtual void LoadFromImage(const Image& image_);
		virtual void GetPropertiesFromFile(const std::string& filename);

		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IPoint& position = IPoint(0,0));
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IPoint& position, const IRect& rect);
		/// отрисовка текстуры в заданной позиции с поворотом, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IPoint& position, const RectOrient orient);
		/// отрисовка текстуры в заданной позиции с деформацией, если текстура ещё не забиндена, она биндится
		virtual void DrawCut(const IPoint& position, float cut_factor_x, float cut_factor_y = 1.0f);
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IRect& rect, float xStart, float xEnd, float yStart, float yEnd);
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const IRect& rect, const FRect& uv);
		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(float x, float y, float width, float height, const FRect& uv);

		/// отрисовка текстуры в заданной позиции, если текстура ещё не забиндена, она биндится
		virtual void Draw(const FPoint& position);
		/// отрисовка текстуры в заданной позиции с поворотом, если текстура ещё не забиндена, она биндится
		virtual void Draw(const FPoint& position, const RectOrient orient);
		/// отрисовка текстуры в заданной позиции с деформацией, если текстура ещё не забиндена, она биндится
		virtual void DrawCut(const FPoint& position, float cut_factor_x, float cut_factor_y = 1.0f);

		//
		// Вернуть физические размеры текстуры - размер хранения текстуры в файле
		//
		IRect getBitmapRect();

		//
		// Вернуть логические размеры текстуры - сколько она занимает в видеопамяти;
		// именно этот размер нужно использовать при расчете текстурных координат в
		// некоторых функциях вывода.
		// На большинстве современных видеокарт результат функции совпадает с getBitmapRect(),
		// однако некоторые старые видеокарты и отличные от Win игровые платформы (Mac, IPhone)
		// требуют текстуры с размерами равными степеням двойки.
		//
		IRect getRenderRect();

		virtual bool isPixelTransparent(int x, int y);
		virtual bool isPixelOpaque(int x, int y);
		virtual bool isPixelOpaque(const IPoint& p);
		void SetCompress(bool allowCompress);
		
		// Установить способ хранения пикселя в видеопамяти
		void SetPixelType(PixelType pixelType) {
			_pixelType = pixelType;
		}
	};
}

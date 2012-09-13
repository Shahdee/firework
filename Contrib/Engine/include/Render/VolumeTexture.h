#pragma once

#include <set>
#include <vector>
#include <map>
#include "Utils/FPoint.h"
#include "Utils/Math.hpp"
#include "Render/Texture.h"

namespace Core
{
	class ResourceManagerImpl;
}

#ifdef ENGINE_TARGET_WIN32_DX9
struct IDirect3DVolumeTexture9;
#	define DEVVOLUMETEXTURE IDirect3DVolumeTexture9*
#endif

#ifdef ENGINE_TARGET_WIN32_DX8
struct IDirect3DVolumeTexture8;
#	define DEVVOLUMETEXTURE IDirect3DVolumeTexture8*
#endif

#ifdef ENGINE_TARGET_IPHONE
#	include <OpenGLES/ES1/gl.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

#ifdef ENGINE_TARGET_MACOS
#	include <OpenGL/OpenGL.h>
#	define DEVVOLUMETEXTURE GLuint
#endif

namespace Render
{
	class RenderDeviceImpl;
	class PartialTexture;

	//  ласс 3д текстуры
	class VolumeTexture
	{
		friend class Render::RenderDeviceImpl;
		friend class Core::ResourceManagerImpl;

	public:
		std::string textureID;
		std::string groupID;
		std::string path;
		/// текстура в принципе хоть раз биндилась
		bool wasBinded;

	protected:
		/// текстура сейчас забиндена
		bool binded;
		/// была ли текстура загружена
		bool wasUploaded;
		DEVVOLUMETEXTURE _tex;
		Texture::FilteringType _filter;
		Texture::AdressType _adress;

	public:
		VolumeTexture();
				
		static VolumeTexture* getFromXml(rapidxml::xml_node<>* elem);
		virtual ~VolumeTexture();

		/// “екстура не загружена, или принудительно выгружена. ѕринудительно выгружаютс€ динамические текстуры при переинициализации RenderDeviceImpl. —м. Texture::setDynamic
		bool Empty();
		void setFilter(Texture::FilteringType filter);
		void setAdress(Texture::AdressType adress);
		Texture::AdressType GetAddressType();
		/// загрузить текстуру
		virtual void Upload();
		/// забиндить текстуру в заданный канал
		virtual void Bind(int channel = 0, int stageOp = 0);
		/// выгрузить текстуру
		virtual void Release();
	};
}
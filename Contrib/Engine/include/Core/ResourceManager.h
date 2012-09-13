#pragma once

#include "singleton.hpp"
#include "Application.h"
#include "Render/Texture.h"
#include "Render/sheet.h"
#include "Render/Animation.h"
#include "Render/StreamingAnimation.h"
#include "PixelType.h"
#include "Text.h"
#include "Core/ResourceFactory.h"

#include <map>

class VertexBuffer;

namespace Core
{
	extern ResourceFactory	*resourceFactory;
	
class ScreenImpl;

template<class T>
class ResourceMap
{
	friend class ResourceManagerImpl;
	friend class ScreenImpl;

	struct ResourceProxy
	{
		T* resource;
		bool isUploaded;
		std::string fileName;
		std::string group;

		void UploadImpl();
		void ReleaseImpl();

		void Release()
		{
			if (isUploaded)
			{
				isUploaded = false;
				resourceFactory->Release(resource);
			}
		}

		void Upload()
		{
			if (!isUploaded)
			{
				isUploaded = true;
				resourceFactory->Upload(resource);
			}
		}

		void CreateDataWithoutMask()
		{
			resource->LoadFromFileWithoutMask(fileName);
		}
	};

	typedef std::map<std::string, ResourceProxy> MapResource;
	MapResource _resource;
		// отображение "идентификатор ресурса - прокси ресурса"
		// для получения ресурса по идентификатору
	
	typedef std::multimap<std::string, ResourceProxy*> MapGroupResource;
	MapGroupResource _mapGroupResource;
		// многозначное отображение "имя группы - ресурс"
		// для эффективной загрузки и выгрузки по имени группы

public:
	
	std::map<std::string, int> groupReferences;

	ResourceMap()
	{}
	~ResourceMap()
	{}

	bool exist(const std::string& id)
	{
		return _resource.find(id) != _resource.end();
	}

	T* get(const std::string& id)
	{
		typename MapResource::iterator i = _resource.find(id);
		if (i != _resource.end())
		{
			return i->second.resource;
		}
		else
		{
			Core::Error("Resource not found. id=" + id, "Resource not found. id=" + id);
			return NULL;
		}
	}

	void Upload(const std::string& id)
	{
		typename MapResource::iterator i = _resource.find(id);
		if (i != _resource.end())
		{
			if (!i->second.isUploaded)
			{
				i->second.Upload();
				i->second.isUploaded = true;
			}
		}
	}

	void Release(const std::string& id)
	{
		typename MapResource::iterator i = _resource.find(id);
		if (i != _resource.end())
		{
			if (i->second.isUploaded)
			{
				i->second.Release();
				i->second.isUploaded = false;
			}
		}
	}

	void UploadGroup(const std::string& group)
	{
		typename MapGroupResource::iterator b = _mapGroupResource.lower_bound(group);
		typename MapGroupResource::iterator e = _mapGroupResource.upper_bound(group);
		for (typename MapGroupResource::iterator i = b; i != e; ++i) {
			i->second->Upload();
		}
		//for (resource_iterator i = _resource.begin(), e = _resource.end(); i!=e; i++)
		//{
		//	if (i->second.group == group)
		//	{
		//		i->second.Upload();
		//	}
		//}
	}

	void ReleaseGroup(const std::string& group)
	{
		//for (resource_iterator i = _resource.begin(), e = _resource.end(); i!=e; i++)
		//{
		//	if (i->second.group == group)
		//	{
		//		i->second.Release();
		//	}
		//}
		typename MapGroupResource::iterator begin = _mapGroupResource.lower_bound(group);
		typename MapGroupResource::iterator end = _mapGroupResource.upper_bound(group);
		for (typename MapGroupResource::iterator i = begin; i != end; ++i) {
			i->second->Release();
		}
	}

	void CreateDataWithoutMask(const std::string& id)
	{
		typename MapResource::iterator i = _resource.find(id);
		if (i != _resource.end())
		{
			i->second.CreateDataWithoutMask();
		}
	}


	void add(const std::string& id, T* res, const std::string& fileName, const std::string& group)
	{
		ResourceProxy proxy;
		proxy.resource = res;
		proxy.fileName = fileName;
		proxy.group = group;
		proxy.isUploaded = false;
		_resource.insert(std::make_pair(id, proxy));
		_mapGroupResource.insert(std::make_pair(proxy.group, &_resource[id]));
	}

	/*~
	void add(std::pair<std::string, T*>& resource, const std::string& fileName, const std::string& group)
	{
		ResourceProxy proxy;
		proxy.resource = resource.second;
		proxy.fileName = fileName;
		proxy.group = group;
		proxy.isUploaded = false;
		_resource.insert(std::make_pair(resource.first, proxy));
		_mapGroupResource.insert(std::make_pair(group, proxy.resource));
	}
	*/
};

template<class T>
class ResourceMultiMap
{
	friend class ResourceManagerImpl;

	struct ResourceProxy
	{
		T* resource;
		bool isUploaded;
		std::vector<std::string> uploadGroups;	// группы, которые аплоадили ресурс
		std::set<std::string> referenceGroups;	// группы, которые содержат ресурс

		void UploadByGroup(const std::string &group)
		{
			if (uploadGroups.empty()) {
				if (!isUploaded)
				{
					isUploaded = true;
					resourceFactory->Upload(resource);
				}
			}
			uploadGroups.push_back(group);
		}

		void ReleaseByGroup(const std::string &group)
		{
			if (uploadGroups.empty()) {
				return;
			}
			for (size_t i = 0; i < uploadGroups.size(); i++) {
				if (uploadGroups[i] == group) {
					uploadGroups.erase(uploadGroups.begin() + i);
					break;
				}
			}
			if (uploadGroups.empty()) {
				if (isUploaded)
				{
					isUploaded = false;
					resourceFactory->Release(resource);
				}
			}
		}

		void Upload()
		{
			if (!isUploaded)
			{
				isUploaded = true;
				resourceFactory->Upload(resource);
			}
		}

		void Release()
		{
			if (uploadGroups.empty()) 
			{
				if (isUploaded)
				{
					isUploaded = false;
					resourceFactory->Release(resource);
				}
			}
		}
	};

	
	typedef std::map<std::string, ResourceProxy> MapResource;
	MapResource _resource;

	
	typedef std::multimap<std::string, ResourceProxy*> MapGroupResource;
	MapGroupResource _mapGroupResource;

public:

	ResourceMultiMap()
	{}
	~ResourceMultiMap()
	{}


	bool exist(const std::string& id)
	{
		return _resource.find(id) != _resource.end();
	}


	T* get(const std::string& id)
	{
		typename MapResource::iterator i = _resource.find(id);
		if (i != _resource.end())
		{
			return i->second.resource;
		}
		else
		{
			Core::Error("Resource not found. id=" + id, "Resource not found. id=" + id);
			return NULL;
		}
	}

	void UploadGroup(const std::string& group)
	{
		typename MapGroupResource::iterator b = _mapGroupResource.lower_bound(group);
		typename MapGroupResource::iterator e = _mapGroupResource.upper_bound(group);
		for (typename MapGroupResource::iterator i = b; i != e; ++i) {
			i->second->UploadByGroup(group);
		}
	}

	void ReleaseGroup(const std::string& group)
	{
		typename MapGroupResource::iterator begin = _mapGroupResource.lower_bound(group);
		typename MapGroupResource::iterator end = _mapGroupResource.upper_bound(group);
		for (typename MapGroupResource::iterator i = begin; i != end; ++i) {
			i->second->ReleaseByGroup(group);
		}
	}

	void Upload(const std::string& id)
	{
		if (_resource.find(id) != _resource.end())
		{
			_resource[id].Upload();
		}
	}

	void UploadResourceWithGroup(const std::string& id, const std::string group)
	{
		if (_resource.find(id) != _resource.end())
		{
			_resource[id].UploadByGroup(group);
		}
	}

	void Release(const std::string& id)
	{
		if (_resource.find(id) != _resource.end())
		{
			_resource[id].Release();
		}
	}


	void add(const std::string& id, T* res, const std::string& group)
	{
		if (!exist(id))
		{
			_resource.insert(std::make_pair(id, ResourceProxy()));
			ResourceProxy *proxy = &_resource[id];
			proxy->resource = res;
			proxy->isUploaded = false;
			proxy->referenceGroups.insert(group);
			_mapGroupResource.insert(std::make_pair(group, proxy));
		}
		else
		{
			ResourceProxy *proxy = &_resource[id];
			if (proxy->referenceGroups.find(group) == proxy->referenceGroups.end())
			{
				proxy->isUploaded = false;
				proxy->referenceGroups.insert(group);
				_mapGroupResource.insert(std::make_pair(group, proxy));
			}
			
		}
	}

};

class ResourceManagerImpl : public Singleton<ResourceManagerImpl>
{
	friend class Singleton<ResourceManagerImpl>;
	friend class ScreenImpl;
	friend class ::TText;

	typedef std::map<std::string, boost::shared_ptr<TText> > TextMap;
	typedef std::map<std::string, Render::Texture*> TextureCache;
	typedef TextureCache::iterator TextureCacheIterator;
	typedef std::map<std::string, std::string> TextureAliases;
	ResourceMap<Render::Texture> _textures;
	TextureAliases _textureAliases;
	ResourceMap<Render::VolumeTexture> _volumeTextures;
	ResourceMap<Render::ShaderProgram> _shaders;
	ResourceMap<Render::Animation> _animations;
	ResourceMap<Render::StreamingAnimation> _streamingAnimations;
	ResourceMap<Render::ModelAnimation> _modelAnimations;
	ResourceMultiMap<Render::Texture> _particleTextures;
	TextureCache _textureCache;
	TextMap _texts;
	TText _emptyText;
	std::vector<TText*> knownTexts;
#ifdef THREADED
	boost::recursive_mutex uploadMutex;
#endif
	typedef std::map<std::string, std::vector<Render::Sheet*> > Sheets;
	Sheets _sheets;
	
	typedef std::map<std::string, Render::Sheet*> SheetCache;
	SheetCache _sheet_cache;

	void LoadFonts(rapidxml::xml_node<>* el);
	void LoadSheets(rapidxml::xml_node<>* el);
	void LoadTextures(rapidxml::xml_node<>* el);
	void LoadTextures2D(rapidxml::xml_node<>* el);
	void LoadTextures3D(rapidxml::xml_node<>* el);
	void LoadAnimations(rapidxml::xml_node<>* el);
	void LoadStreamingAnimations(rapidxml::xml_node<>* el);
	void LoadModelAnimations(rapidxml::xml_node<>* el);
	void LoadShaders(rapidxml::xml_node<>* el);
	void LoadSounds(rapidxml::xml_node<>* el);
protected: 
	void RegisterText(TText *text);
	void UnregisterText(TText *text);

public:
	ResourceManagerImpl();
	~ResourceManagerImpl();

	/*~
	// Не нужно использовать этот шаблон, вместо него используйте методы Core::resourceFactory.
	template<class T>
	bool getResourceFromXml(rapidxml::xml_node<>* elem, std::pair<std::string, T*>& resource)
	{
		std::string _id;
		if (elem->first_attribute("id"))
		{
			_id = std::string(elem->first_attribute("id")->value());
		}
		else
		{
			return false;
		}

		T* res = T::getFromXml(elem);
		if (res)
		{
			resource = std::make_pair(_id, res);
		}
		else
		{
			return false;
		}

		return true;
	}
	*/
	/// Загрузить вручную одну текстуру, если не задаётся needUpload, то текстура загружается сразу если указанная группа загружена
	void LoadTexture(const std::string& resFilename, const std::string& textureId, const std::string& groupId, bool needUpload = false, bool bitMask = false);
	bool HasTexture(const std::string& textureId);
	/// Получить текстуру по идентификатору
	Render::Texture* getTexture(const std::string& id, bool setBilinearFilter = true);
	Render::Texture * getResFromSheetByGroup(const std::string& shortName, const std::string& groupId);
	Render::Texture* getParticleTexture(const std::string& id, const std::string& group, bool setBilinearFilter = true);
	void UploadParticleTexture(const std::string& id);
	void ReleaseParticleTexture(const std::string& id);
	/// Загрузка новой "простыни", или возвращает из кеша если уже загружена
	Render::Sheet* getSheet(const std::string& xml, const std::string& file, const std::string& group, bool allowCompress, PixelType pixelType);
	/// Возвращает загруженную "простыню". Загруженную через xml как обычный ресурс.
	Render::Sheet* getSheet(const std::string& sheetId, const std::string& group);
	Render::VolumeTexture* getVolumeTexture(const std::string& id, bool setBilinearFilter = true);

	/// Возвращается копия запрошенной текстуры. Её нужно удалять самостоятельно, когда станет не нужна.
	Render::Animation::HardPtr getAnimation(const std::string& id);
	Render::StreamingAnimation::HardPtr getStreamingAnimation(const std::string& id);
	Render::ModelAnimation::HardPtr getModelAnimation(const std::string& id);
	
	Render::ShaderProgram* getShaderProgram(const std::string& id);
	bool hasShaderProgram(const std::string& id);

	/// Загрузка текстов из XML файлов ODT
	bool LoadTextODT(const std::string& filename);
	bool RLoadTextODT(const std::string& filename);  // rapidxml
	void ClearTexts(); // очистка текстов. Нужна, чтобы обновить все тектсы, запускается перед LoadText
	/// Загрузка текстов из Excel-файла (в формате XML)
	bool LoadText(const std::string& filename, bool reload = false);
	bool RLoadText(const std::string& filename);
	// Обновить заданную переменную в текстах, или все тексты, если ничего не задано
	void UpdateText(const std::string* varName = 0, const std::string* varValue = 0);
	// Эквивалентно UpdateText без параметров. LEGACYCODE !!!
	void UpdateTextProperties();
	TText& GetText(const std::string& _text);
	
	// Добавить текст в рантайме
	// При этом подразумевается, что текстом будет владеть ресурс-менеджер,
	// то есть самостоятельно удалять его не нужно.
	void AddText(const std::string& idText, TText* text);
	
	bool HasText(const std::string& _text);

	/// Выгрузка одной текстуры
	void Release(const std::string& id);
	/// Загрузка одной текстуры
	void Upload(const std::string& id);
	/// Простая загрузка группы
	void UploadGroup(const std::string& group);

	/// «‡„ÛÁÍ‡ „ÛÔÔ˚ Ò ÔÓ‰Ò˜∏ÚÓÏ ÍÓÎË˜ÂÒÚ‚‡ ‚˚ÁÓ‚Ó‚, ‡·ÓÚ‡˛˘‡ˇ ‚ ÓÚ‰ÂÎ¸ÌÓÏ ÔÓÚÓÍÂ
	/// ÃÓÊÂÚ ÔË„Ó‰ËÚ¸Òˇ ‰Îˇ ÒÓÁ‰‡ÌËˇ ÏÂÊ˝Í‡ÌÌÓÈ ÏÌÓ„ÓÔÓÚÓ˜ÌÓÈ Á‡„ÛÁÍË. ¬ ˝ÚÓÏ ÒÎÛ˜‡Â ‡Î„ÓËÚÏ ‡·ÓÚ˚ ÒÎÂ‰Û˛˘ËÈ:
	/// 1. ◊ÂÂÁ CrossFade ËÎË ËÌ˚Ï ÒÔÓÒÓ·ÓÏ ÔÂÂıÓ‰ËÏ Ì‡ ˝Í‡Ì Á‡„ÛÁÍË ÒÎÓˇ;
	/// 2. «‡ÔÛÒÍ‡ÂÏ ‚ ÓÚ‰ÂÎ¸ÌÓÏ ÔÓÚÓÍÂ Á‡„ÛÁÍÛ „ÛÔÔ˚ ÂÒÛÒÓ‚ Á‡„ÛÊ‡ÂÏÓ„Ó ÒÎÓˇ Ò ÔÓÏÓ˘¸˛ ÏÂÚÓ‰‡ SmartUploadGroupThreaded
	/// 3. ƒÎˇ ÔÓ‰Ò˜ÂÚ‡ ÂÒÛÒÓ‚ Upload'ËÏ˚ı ÂÒÛÒÓ‚ ‚ÓÒÔÓÎ¸ÁÓ‚‡Ú¸Òˇ Ì‡ÒÎÂ‰ÌËÍÓÏ ÍÎ‡ÒÒ‡ ResourceUploadObserver
	/// 4. œÓÒÎÂ Á‡„ÛÁÍË ‚ÒÂı ÂÒÛÒÓ‚ „ÛÔÔ˚ ·Û‰ÂÚ ÔÓÒÎ‡ÌÓ ÒÓÓ·˘ÂÌËÂ "SmartResourceGroupUploaded", ÍÓÚÓÓÂ ÌÛÊÌÓ Ó·‡·ÓÚ‡Ú¸ ‚ ˝Í‡ÌÂ Á‡„ÛÁÍË ÒÎÓˇ
	/// 5. ◊ÂÂÁ CrossFade ËÎË ËÌ˚Ï ÒÔÓÒÓ·ÓÏ ÔÂÂÈÚË Ì‡ ÌÛÊÌ˚È ÒÎÓÈ
	void UploadGroupThreaded(const std::string &layerName);
	/// Прострая выгрузка группы
	void ReleaseGroup(const std::string& group);
	/// Загрузка группы с подсчётом количества вызовов
	void SmartUploadGroup(const std::string& group);
	/// Выгрузка группы с подсчётом количества вызовов
	void SmartReleaseGroup(const std::string& group);
	void LoadResource(const std::string& filename);
    void Release();

	void CreateTextureData(const std::string& id);
	// Выполняет LoadFromFile. После надо не забыть выполнить image.Clear()
	
	void SaveParticleGroupsInfo() const;

};

extern ResourceManagerImpl resourceManager;

}

#ifndef _GUI_MOVIEPLAYERANIMATION_H_
#define _GUI_MOVIEPLAYERANIMATION_H_

#include "Render/Texture.h"
#include "boost/shared_ptr.hpp"

class MoviePlayerTextureCutter
{
public:

	typedef boost::shared_ptr<MoviePlayerTextureCutter> HardPtr;

	MoviePlayerTextureCutter()
		: _width(0)
		, _height(0)
	{}

	MoviePlayerTextureCutter(const Render::Image &img, int width, int height, int number) {
		bool checkData = CheckData(img, width, height, number);
		Assert(checkData);
		_width = width;
		_height = height;
		Assert(img.components == 3 || img.components == 4);
		_alphaChannel = img.alphaChannel;
		_components = img.components;
		_data.resize(_width*_height*img.components);
		int wCount = img.width/width;
		//int hCount = img.height/height;
		int xNum = number%wCount;
		int yNum = number/wCount;

		BYTE *p = &_data[0];
		BYTE *base = Render::Image::image_pool + (img.height - height*(yNum + 1))*img.width*img.components + xNum*width*img.components;
		for (int j = 0; j < height; j++, p += width * img.components) {
			memcpy(p, base + j * img.width * img.components, width * img.components);
		}
	}

	Render::Texture* ToRectangleTexture() {
		Render::Image img;
		img.alphaChannel = _alphaChannel;
		img.width = _width;
		img.height = _height;
		img.components = _components;
		memcpy(Render::Image::image_pool, &_data[0], _width * _height * _components);
		Render::Texture *tex = new Render::Texture;
		tex->LoadFromImage(img);
		return tex;
	}

private:

	std::vector<BYTE> _data;

	int _width, _height;

	int _components;

	bool _alphaChannel;

	bool CheckData(const Render::Image &img, int width, int height, int number) {
		if (width > static_cast<int>(img.width) || height > static_cast<int>(img.height)) {
			return false;
		}
		if (width <= 0 || height <= 0) {
			return false;
		}
		int wCount = img.width/width;
		int hCount = img.height/height;
		return number < wCount*hCount;
	}

};

class MoviePlayerAnimationResource
{
public:

	typedef boost::shared_ptr<MoviePlayerAnimationResource> HardPtr;
		// тип указателя со счётчиком ссылок

	typedef MoviePlayerAnimationResource* WeakPtr;
		// тип указателя, совместимого со счётчиком ссылок,
		// но не удерживающего объект от удаления

	MoviePlayerAnimationResource()
	{}

	static HardPtr Load(Xml::TiXmlElement *root)
	{
		if (root->Value() == std::string("Animation")) {
			return CreateOneTextureAnimation(root);
		}
		if (root->Value() == std::string("FrameAnimation")) {
			return CreateMultipleTexturesAnimation(root);
		}
		Assert(false);
		return (HardPtr)(MoviePlayerAnimationResource*)NULL;
	}

	~MoviePlayerAnimationResource() {
		for (size_t i = 0; i < _frames.size(); i++) {
			_frames[i]->Release();
			delete _frames[i];
		}
		_frames.resize(0);
	}

	Render::Texture* GetFrame(int number) {
		return _frames[number];
	}

	int size() {
		return int(_frames.size());
	}

private:

	std::vector<Render::Texture*> _frames;

	static HardPtr CreateOneTextureAnimation(Xml::TiXmlElement *root) {
		Assert(root->Value() == std::string("Animation"));
		HardPtr animation = (HardPtr)(new MoviePlayerAnimationResource);

		std::string path = root->Attribute("path");
		int width = 0;
		root->QueryIntAttribute("width", &width);
		Assert(width >= 1);
		int height = 0;
		root->QueryIntAttribute("height", &height);
		Assert(height >= 1);
		int count = 0;
		root->QueryIntAttribute("count", &count);
		Assert(count >= 1);
		int first = 0;
		root->QueryIntAttribute("first", &first);
		Assert(0 <= first && first < count);
		int last = 0;
		root->QueryIntAttribute("last", &last);
		Assert(0 <= last && last < count && first <= last);
		int size = last - first + 1;
		Render::Image img(path);

		std::vector<MoviePlayerTextureCutter::HardPtr> framesImages;
		framesImages.resize(size);
		for (int i = 0; i < size; i++) {
			framesImages[i] = (MoviePlayerTextureCutter::HardPtr)(new MoviePlayerTextureCutter(img, width, height, i + first));
		}

		animation->_frames.resize(size);
		for (int i = 0; i < size; i++) {
			animation->_frames[i] = framesImages[i]->ToRectangleTexture();
			animation->_frames[i]->setFilter(Render::Texture::BILINEAR);
			animation->_frames[i]->setAdress(Render::Texture::CLAMP);

			animation->_frames[i]->Upload();
		}

		return animation;
	}

	static HardPtr CreateMultipleTexturesAnimation(Xml::TiXmlElement *root) {
		Assert(root->Value() == std::string("FrameAnimation"));
		HardPtr animation = (HardPtr)(new MoviePlayerAnimationResource);

		std::string dir = root->Attribute("path");
		std::string name = root->Attribute("prefix");
		std::string ext = root->Attribute("extension");
		int numKeys = 0;
		root->QueryIntAttribute("count", &numKeys);
		Assert(numKeys >= 1);
		int startKey = 0;
		root->QueryIntAttribute("start", &startKey);
		Assert(startKey >= 1);
		int keyStep = 0;
		root->QueryIntAttribute("step", &keyStep);
		Assert(keyStep >= 1);

		int keyId = 0;
		animation->_frames.resize(numKeys);
		for (int i = 0; i < numKeys; i++) {
			std::string filename = dir + name;
			size_t fullNameSize = (filename + Int::ToString(startKey + numKeys)).size();
			while ((filename + Int::ToString(startKey + keyId)).size() < fullNameSize) {
				filename += "0";
			}
			filename += Int::ToString(startKey + keyId) + "." + ext;
			animation->_frames[i] = new Render::Texture(filename);
			animation->_frames[i]->setFilter(Render::Texture::BILINEAR);
			animation->_frames[i]->setAdress(Render::Texture::CLAMP);
			animation->_frames[i]->Upload();
			keyId += keyStep;
		}

		return animation;
	}

};

#endif

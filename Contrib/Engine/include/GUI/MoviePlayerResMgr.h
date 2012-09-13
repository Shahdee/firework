#ifndef _GUI_MOVIEPLAYERRESMGR_H_
#define _GUI_MOVIEPLAYERRESMGR_H_

#include "Render/Texture.h"
#include "ParticleSystem.h"
#include "MoviePlayerAnimation.h"

namespace MoviePlayer
{

class ResourceManager
{
private:

	struct TextureWrapper
	{

		Render::Texture *texture;

		TextureWrapper();

		TextureWrapper(Xml::TiXmlElement *root);

		~TextureWrapper();

	};

	class EffectWrapper
	{
	public:

		ParticleEffect effect;

		EffectWrapper();

		void Release();

		explicit EffectWrapper(Xml::TiXmlElement *root);

	};

	class AnimationWrapper
	{
	public:

		MoviePlayerAnimationResource::HardPtr animation;

		AnimationWrapper();

		explicit AnimationWrapper(Xml::TiXmlElement *root);

	};

	typedef std::map<std::string, TextureWrapper*> Textures;

	typedef Textures::iterator TextureIterator;

	typedef std::map<std::string, EffectWrapper> ParticleEffects;

	typedef ParticleEffects::iterator ParticleEffectIterator;

	typedef std::map<std::string, AnimationWrapper> Animations;

	typedef Animations::iterator AnimationIterator;

	std::set<std::string> _textFiles;

	Textures _textures;

	ParticleEffects _effects;

	Animations _animations;

public:
	typedef boost::shared_ptr<ResourceManager> HardPtr;
	
	typedef boost::weak_ptr<ResourceManager> WeakPtr;

	void Clear();

	void Load(Xml::TiXmlElement *root);

	Render::Texture* GetTexture(std::string textureId);

	ParticleEffect GetEffect(std::string effectId);

	MoviePlayerAnimationResource::WeakPtr GetAnimation(std::string animationId);

};

};

#endif

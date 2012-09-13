/*
 *  ResourceFactory.h
 *  Engine
 *
 *  Created by vasiliym on 04.05.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "Render/Texture.h"
#include "Render/VolumeTexture.h"
#include "Render/Animation.h"
#include "Render/StreamingAnimation.h"
#include "Render/ModelAnimation.h"
#include "Render/ShaderProgram.h"

/**
 * Наследуйте фабрику ресурсов, чтобы управлять созданием ресурсов.
 * Например, можно создавать свои анимации и текстуры, наследованные от стандартных.
 * 
 * @see resourceFactory = new ResourceFactory() в конструкторе Application.
 */
class ResourceFactory
{
public:
	ResourceFactory();
	virtual ~ResourceFactory();
	virtual void StartUploadGroup(const std::string& groupName);
	virtual void EndUploadGroup();

	virtual Render::Animation* CreateAnimation(rapidxml::xml_node<>* elem);
	virtual Render::Texture* CreateTexture(rapidxml::xml_node<>* elem);
	virtual Render::VolumeTexture* CreateVolumeTexture(rapidxml::xml_node<>* elem);
	virtual Render::StreamingAnimation* CreateStreamingAnimation(rapidxml::xml_node<>* elem);
	virtual Render::ModelAnimation* CreateModelAnimation(rapidxml::xml_node<>* elem);
	virtual Render::ShaderProgram* CreateShaderProgram(rapidxml::xml_node<>* elem);

	/* Следующие методы дублируют методы Create* выше.
	 * Они могут быть полезны в случае использования в шаблонах, но пока что не используются.
	virtual Render::Animation* Create(rapidxml::xml_node<>* elem, Render::Animation** res);
	virtual Render::Texture* Create(rapidxml::xml_node<>* elem, Render::Texture** res);
	virtual Render::VolumeTexture* Create(rapidxml::xml_node<>* elem, Render::VolumeTexture** res);
	virtual Render::StreamingAnimation* Create(rapidxml::xml_node<>* elem, Render::StreamingAnimation** res);
	virtual Render::ModelAnimation* Create(rapidxml::xml_node<>* elem, Render::ModelAnimation** res);
	virtual Render::ShaderProgram* Create(rapidxml::xml_node<>* elem, Render::ShaderProgram** res);
	*/

	/* Методы Clone пока что не используются, но если вдруг понадобятся,
	 * то их обязательно надо перенести в класс ResourceManager - по сути это должны быть его методы.
	virtual Render::Animation* Clone(Render::Animation*);
	virtual Render::Texture* Clone(Render::Texture*);
	virtual Render::VolumeTexture* Clone(Render::VolumeTexture*);
	virtual Render::StreamingAnimation* Clone(Render::StreamingAnimation*);
	virtual Render::ModelAnimation* Clone(Render::ModelAnimation*);
	virtual Render::ShaderProgram* Clone(Render::ShaderProgram*);
	*/

	virtual void Upload(Render::Animation* a);
	virtual void Upload(Render::Texture* t);
	virtual void Upload(Render::VolumeTexture* t);
	virtual void Upload(Render::StreamingAnimation* s);
	virtual void Upload(Render::ModelAnimation* m);
	virtual void Upload(Render::ShaderProgram* s);
	
	virtual void Release(Render::Animation *a);
	virtual void Release(Render::Texture* t);
	virtual void Release(Render::VolumeTexture* t);
	virtual void Release(Render::StreamingAnimation* s);
	virtual void Release(Render::ModelAnimation* m);
	virtual void Release(Render::ShaderProgram* s);
};

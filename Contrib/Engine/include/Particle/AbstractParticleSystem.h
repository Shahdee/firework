#ifndef ABSTRACT_PARTICLE_SYSTEM_H
#define ABSTRACT_PARTICLE_SYSTEM_H

#include "Render/VertexBuffer.h"
#include "Render/RenderDevice.h"
#include "Render/Texture.h"
#include "Core/ResourceManager.h"
#include "Core/Locale.h"
#include "Utils/Math.hpp"
#include "Utils/Str.h"
#include "Utils/random.hpp"
#include "File.h"
#include "Spline.h"
#include "BinaryData.h"
#include "ParticleSystemStrings.h"

class AbstractParticleSystem
{
	friend class EffectManager;
	friend class EffectTree;

protected:
	AbstractParticleSystem(uchar version);
public:
	//enum ParamID
	//{
	//	PARAM_X,
	//	PARAM_Y,
	//	PARAM_V,
	//	PARAM_SPIN,
	//	PARAM_SIZE,
	//	PARAM_YSIZE,
	//	PARAM_ANGLE,
	//	PARAM_FPS,
	//	PARAM_ALPHA,
	//	PARAM_RED,
	//	PARAM_GREEN,
	//	PARAM_BLUE,
	//};
	virtual ~AbstractParticleSystem();
	virtual AbstractParticleSystem *Clone() = 0;
	virtual void Upload() = 0;
	virtual void Release() = 0;
	virtual bool Load(BinaryDataLoader *d) = 0;
	virtual void Save(BinaryDataSaver *d) = 0;
	virtual bool Load(Xml::TiXmlElement *elem) = 0;
	virtual void Save(Xml::TiXmlElement *elem) = 0;
	virtual void Reset() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void DrawBlend() = 0;
	virtual bool IsDead() = 0;
	virtual bool IsPermanent() = 0;
	virtual void Finish() = 0;
	virtual void SetPositionOffset(float x, float y) = 0;
	virtual void SetAlphaFactor(float alpha) = 0;
	virtual void SetRGBFactor(float r, float g, float b) = 0;
	virtual void SetInitialForParamKey(const char *id, size_t key_index, float initial) = 0;
	virtual int FrameWidth() = 0;
	virtual int FrameHeight() = 0;

	uchar Version();



	static const int MAX_PARTICLES;

	static const char* PARAM_X;
	static const char* PARAM_Y;
	static const char* PARAM_V;
	static const char* PARAM_SPIN;
	static const char* PARAM_ANGLE;
	static const char* PARAM_SIZE;
	static const char* PARAM_YSIZE;
	static const char* PARAM_FPS;
	static const char* PARAM_ALPHA;
	static const char* PARAM_RED;
	static const char* PARAM_GREEN;
	static const char* PARAM_BLUE;

	static void InitParticleStuff();
	static std::string NormalizeTextureName(const std::string &name);
	static void SetTexturesPath(const std::string &path);
	static std::string TexturesPath();
	static void SetErrorMessage(const std::string &msg);
	static std::string ErrorMessage();
	static void SetEditorMode(bool mode = true);
	static bool EditorMode() { return _editor_mode; }
	static void CreateTexturePlug();
	static void DestroyTexturePlug();

	void SetResourceGroup(const std::string &group) { _resourceGroup = group; };
	
protected:
	static const float PI;
	static const float RAD;
	static bool _editor_mode;
	static Render::Texture* _texture_plug;
	static std::string _error_message;
	static std::string _textures_path;
	static VertexBufferIndexed* _drawBuffer;

	uchar _version;
	std::string _resourceGroup;

	std::string BoolToString(bool value);

private:
	AbstractParticleSystem& operator=(const AbstractParticleSystem&);
};


typedef AbstractParticleSystem ParticleSystem;

#endif
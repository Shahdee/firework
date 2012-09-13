#ifndef PARTICLE_SYSTEM_VER3_H
#define PARTICLE_SYSTEM_VER3_H

#include "Particle/AbstractParticleSystem.h"
#include "Particle/ParticleSystemHelp3.h"

class ParticleSystemVer3: public AbstractParticleSystem
{
	friend class EffectManager;
	friend class EffectTree;

	ParticleSystemVer3(const ParticleSystemVer3&);
	ParticleSystemVer3& operator=(const ParticleSystemVer3&);
public:
	ParticleSystemVer3();
	virtual ~ParticleSystemVer3();
	virtual AbstractParticleSystem *Clone();

	virtual bool Load(BinaryDataLoader *d);
	virtual bool Load(Xml::TiXmlElement *elem);
	virtual void Save(BinaryDataSaver *d);
	virtual void Save(Xml::TiXmlElement *elem);
	virtual void SetPositionOffset(float x, float y);
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void DrawBlend();
	virtual bool IsDead();
	virtual bool IsPermanent();
	virtual void Finish();
	virtual void SetAlphaFactor(float alpha);
	virtual void SetRGBFactor(float r, float g, float b);
	virtual void SetInitialForParamKey(const char *id, size_t key_index, float initial);
	virtual int FrameWidth() { return _frameWidth; }
	virtual int FrameHeight() { return _frameHeight; }

	void DrawParticles();
	void DrawChildren();
	bool HasFocus();
	bool HasParticleTrack();

	PS3Position Pos();
	PS3Position Pos(float time);

	ParticleSystemVer3* ParentSystem() { return _owner ? _owner->_owner : 0; }
	PS3Particle* _owner;
	bool _auto_reset;	//	ресетить, если частица-владелец перерождаетс€
	std::vector<ParticleSystemVer3 *> _children;
	std::vector<PS3Particle> _particles;

	PS3Track _track;
	PS3Track _focusTrack;
	PS3TrackInit _trackInit;
	PS3TrackInit _particleTrackInit;
	PS3TrackInit _focusTrackInit;

	PS3ParamInit _xInit, _yInit, _sizeInit, _ySizeInit;
	PS3ParamInit _angleInit, _vInit, _spinInit, _fpsInit;
	PS3ParamInit _redInit, _greenInit, _blueInit, _alphaInit;

	enum EmitterType
	{
		POINT = 0,
		LINE,
		AREA,
		CIRCLE,
		MASK
	};
	float _lifeInitial;
	float emitterAngle, emitterRange, emitterOrientation;
	float emitterSizeX, emitterSizeY, emitterFactor;

	float _scale;


	bool _isVisible;
	size_t _numOfParticles;

	float _lifeVariation;

	float _localTime;
	float _startTime;

	std::string name;
	std::string _texName;
	std::string _texId;
	Render::Texture* _tex;

	bool _isAnimation;
	int _frameWidth, _frameHeight;

	bool _isScaledNonproportional;
	bool _isEqualCreateTime;

	int _deadParticleCounter;
	bool _addBlend;

	EmitterType emitType;
	std::string emitterMaskName;
	PS3Mask emitterMask;
	Render::Texture *emitterTex;
	bool showEmitter;
	bool _linkedFocus;
	bool _vFactored;
	float _vFactor;


	enum { SLEEP, LIVE, DYING, DEAD } _state;
	float bornTime;
	bool _needStartDeadCounter;
	float _deadCountTime;

	float redFactor, greenFactor, blueFactor, alphaFactor;

	FPoint _offset;

	bool linkParticles;
	bool orientParticles;
	bool isVelocity;
	bool fixedAngleStep;

	bool _isExpanded;	//используетс€ только в редакторе эффектов

	void SetParticleNumber(size_t numOfParticle);

	void RebornParticle(PS3Particle *part, size_t index);

	void SetPositionScale(float xScale, float yScale);

	void LoadTexture(std::string filename);
	void Upload();
	void Release();
	void LoadTextureMask(std::string filename);

	PS3ParamInit * GetParam(const char *id);
};


#endif
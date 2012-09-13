#ifndef PARTICLE_SYSTEM_VER2_H
#define PARTICLE_SYSTEM_VER2_H

#include "Particle/AbstractParticleSystem.h"
#include "Particle/ParticleSystemHelp2.h"

class ParticleSystemVer2: public AbstractParticleSystem
{
	friend class EffectManager;
	friend class EffectTree;

	ParticleSystemVer2(const ParticleSystemVer2&);
	ParticleSystemVer2& operator=(const ParticleSystemVer2&);
public:
	ParticleSystemVer2();
	virtual ~ParticleSystemVer2();
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
	virtual void DisableFog(bool disable);

	struct Particle
	{
		float lifeTime;
		float localTime;

		float emitX;
		float emitY;

		float xStart;
		float yStart;

		float xValue;
		float yValue;

		float spinStart;
		bool isVisible;

		int _currentFrame, _firstFrame, _lastFrame;

		float _speed, _progress;

		float x, y, size, angle, v, spin, red, green, blue, alpha, fps, ySize;		
		TimeParam *xPar, *yPar, *sizePar, *anglePar, *vPar, *spinPar, *redPar, *greenPar, *bluePar, *alphaPar, *fpsPar, *ySizePar;
		GradientSpline xSpl, ySpl, sizeSpl, angleSpl, vSpl, spinSpl, redSpl, greenSpl, blueSpl, alphaSpl, fpsSpl, ySizeSpl;

		void UpdateFrames(float dt, float normTime);
		void ResetFrames();
		void Update(float dt);
		void UpdateVelocity(float dt);
		void Reset();
	};

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
private:
	std::vector<Particle> _particles;

	bool _isVisible;
	int _numOfParticles;

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

	ParticleSystemVer2* _flameLink;

	bool _needParticleReborn;
	bool _needDeadCount;
	int _deadParticleCounter;
	bool _allParticlesIsDead;
	bool _addBlend;

	EmitterType emitType;
	std::string emitterMaskName;
	EmitterMask emitterMask;
	Render::Texture *emitterTex;
	bool showEmitter;


	// для копирования в ParticleSystemComposite
	float bornTime;
	bool _needStartDeadCounter;
	float _deadCountTime;
	bool _isFreeze;
	bool _isDead;

	TimeParam x, y, size, angle, v, spin, colorRed, colorGreen, colorBlue, colorAlpha, fps, ySize;

	float redFactor, greenFactor, blueFactor, alphaFactor;

	float posX, posY;

	bool linkParticles;
	bool orientParticles;
	bool isVelocity;
	bool fixedAngleStep;

	FPoint _hotPoint;

	bool _disableFog;	//флаг, с которым отключается туман на время рисования частитц в режиме ADD

//	void LoadTimePar(Xml::TiXmlElement* elem, const std::string& paramName, TimePar *param);
	Xml::TiXmlElement* GetParamElement(Xml::TiXmlElement *elem, const std::string &name);

	void LinkFlameEmitter(ParticleSystemVer2* ps);

	void SetParticleNumber(int numOfParticle);

	void RebornParticle(Particle& part, int index);

	void SetPositionScale(float xScale, float yScale);

	void LoadTexture(std::string filename);
	void Upload();
	void Release();
	void LoadTextureMask(std::string filename);
	void PrepareParticles(int numOfParticles);

	TimeParam * GetParam(const char *id);
};


#endif
#ifndef PARTICLE_SYSTEM_VER1_H
#define PARTICLE_SYSTEM_VER1_H

#include "Particle/AbstractParticleSystem.h"


class ParticleSystemVer1: public AbstractParticleSystem
{
	friend class EffectManager;
	friend class EffectTree;

	ParticleSystemVer1(const ParticleSystemVer1&);
	ParticleSystemVer1& operator=(const ParticleSystemVer1&);
public:
	ParticleSystemVer1();
	virtual ~ParticleSystemVer1();
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


	struct TimeParam
	{
		float value;
		//float startValue;

		float inital;
		float variation;

		float scaleFactor;
		float yRemoval;

		float dValue;
		float dValueInitial;
		float dValueVariation;

		float d2Value;
		float d2ValueInitial;
		float d2ValueVariation;

		bool isKeyFramed;

		struct SplineKey
		{
			float value;
			float time;

			float inital;
			float variation;

			bool isOffsetKey;

			SplineKey(float time_ = 0, float initial_ = 0, float  variation_ = 0, bool isOffsetKey_ = false);
		};

		std::vector<SplineKey> keys;

		TimedSplinePath spline;
//		GradientSpline spline;

		TimeParam();

		void Update(float dt, float lifeTime);

		void InitSpline();

		void ResetDiffValue();

		void ResetValue();

		void Reset();

		void LoadBinary(BinaryDataLoader *d, float scale = 1.0f);

		void Load(Xml::TiXmlElement* elem, float scale = 1.0f);
		Xml::TiXmlElement* ToXml(const std::string& name);

	};

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

		TimeParam x, y, size, angle, v, spin, colorRed, colorGreen, colorBlue, colorAlpha, fps, ySize;

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

	ParticleSystemVer1* _flameLink;

	bool _needParticleReborn;
	bool _needDeadCount;
	int _deadParticleCounter;
	bool _allParticlesIsDead;
	bool _addBlend;

	EmitterType emitType;


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


	void LoadTimeParam(Xml::TiXmlElement* elem, const std::string& paramName, TimeParam& param, float scale = 1.0f);

	void LinkFlameEmitter(ParticleSystemVer1* ps);

	void SetParticleNumber(int numOfParticle);

	void RebornParticle(Particle& part, int index);

	void SetPositionScale(float xScale, float yScale);

	void LoadTexture(std::string filename);
	void Upload();
	void Release();
	void PrepareParticles(int numOfParticles);
	TimeParam * GetParam(const char *id);
};


#endif
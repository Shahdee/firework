#pragma once

#include "Particle/AbstractParticleSystem.h"
#include "Particle/ParticleSystemVer1.h"
#include "Particle/ParticleSystemVer2.h"
#include "Particle/ParticleSystemVer3.h"


class ParticleEffect
{
public:

	float posX, posY;

	float localTime;
	bool needTimeCount;
	bool ended;
	std::string name, group;

	bool _paused;

	typedef std::vector<ParticleSystem*> SystemVector;
	SystemVector _systems;

	bool _isExpanded;	//используется только в редакторе эффектов

public:

	ParticleEffect();
	ParticleEffect(const std::string& gr);
	ParticleEffect(const ParticleEffect&);
	ParticleEffect& operator=(const ParticleEffect&);
	virtual ~ParticleEffect() { ClearSystems(); }

	bool isEnd() const
	{
		return ended;
	}

	void Kill(void)
	{
		ended = true;
	}

	void Reset();
	bool Load(Xml::TiXmlElement *elem, uchar version);	//	загрузка эффекта нужной версии
														//	добавлено из-за загрузки эффектов НЕ через EffectPresets
														// в частности тут MoviePlayer::ResourceManager::EffectWrapper
	bool Load(Xml::TiXmlElement *elem);

	bool Load(BinaryDataLoader *d);
	void Save(Xml::TiXmlElement *elem);
	void Save(BinaryDataSaver *d);
	virtual void Update(float dt);
	virtual void Draw();
	void DrawBlend();
	void Finish();
	void SetCurrentGroup(const std::string &group);

	void Upload();
	void Release();

	/*	Устанавливает системам частиц флаг, с которым отключается туман на время
		рисования частитц в режиме ADD. Флаг пока есть только для ParticleSystemVer2. */
	void DisableFog(bool disable);

	void Pause();
	void Continue();
	bool IsPermanent();
	void SetAlphaFactor(float alpha);
	void SetPos(const FPoint& pos);
	void SetPos(float x, float y) { SetPos(FPoint(x, y)); }
	void ClearSystems();
	ParticleEffect * Clone() { return new ParticleEffect(*this); }
};

class EffectPresets
{
//	std::map<std::string, ParticleSystem> _partPresets;
//	std::map<std::string, ParticleEffect> _partEffectPresets;

public:
	EffectPresets();
	~EffectPresets();
	//void LoadParticles(const std::string& filename);
	void UploadEffect(const std::string& name);
	void ReleaseEffect(const std::string& name);
	bool LoadEffects(const std::string& filename, const std::string& group = "Common");
	bool LoadEffectsGroup(const std::string& filename, const std::string& group)
	{
		return LoadEffects(filename, group);
	}
	bool LoadBinaryEffects(const std::string& filename, const std::string& group)
	{
		return LoadEffects(filename, group);
	}
	bool SaveEffects(const std::string& filename);
	/// Выгрузка эффектов заданной группы
	void UnloadEffectsGroup(const std::string& group);
//	void ClearEffects() { _effects.clear(); }

//	ParticleSystem& getParticleSystem(const std::string& name);

	ParticleEffect& getParticleEffect(const std::string& name);
	std::vector<ParticleEffect*> & getEffects();

	uchar LastVersion();
	ParticleEffect* Find(const std::string &name);
	void ReloadBinaryEffects(const std::string& filename, const std::string& group = "Common");

private:
//	typedef std::vector<ParticleEffect*> EffectVector;
//	typedef EffectVector::iterator EffectIter;
	std::vector<ParticleEffect*> _effects;

	bool LoadFromXml(const std::string& filename, const std::string& group);
	bool LoadFromBin(const std::string& filename, const std::string& group);
	bool SaveToXml(const std::string& filename);
	bool SaveToBin(const std::string& filename);
};

extern EffectPresets effectPresets;
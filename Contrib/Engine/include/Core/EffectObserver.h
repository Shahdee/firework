#pragma once

#include "ControllerManager.h"
#include "ParticleSystem.h"
#include "Poolable.h"
#include <boost/shared_ptr.hpp>

struct EffectProxy
{
	std::string name;
	bool canDie;

	ParticleEffect* particleEffect;
	EffectsContainer* effectOwner;

	bool onScreen;
	bool lastOnScreen;

	void Update(float dt);
	bool isEnd();

	void Draw();
	void DrawBlend();

	EffectProxy(ParticleEffect* eff, EffectsContainer* effOwner, const std::string &name_, bool canDie_);
	~EffectProxy();
};

typedef boost::shared_ptr<EffectProxy> EffectProxySharedPtr;
typedef std::list<EffectProxySharedPtr> EffectProxySharedPtrList;

class EffectsContainer 
{
public:
	EffectProxySharedPtrList _effects;

	ParticleEffect* AddEffect(const std::string& effectName);
	/// возвращает true если указатель числится среди живых
	bool CheckEffect(const ParticleEffect* eff);

	void Draw();
	void DrawBlend();
	void Pause();
	void Finish();
	void Continue();

	void KillAllEffects();
	void SetAlphaFactor(float alphaFactor);

	virtual ~EffectsContainer();
};

namespace Core
{
	class ScreenImpl;

	// EffectObserver хранит в себе указатели на абсолютно все эффекты, которые 
	// находятся также в своих контейнерах. Цель EffectObserver -- централизованно 
	// обновлять и удалять закончившиеся эффекты. Добавление эффекта в EffectObserver
	// происходит в методе EffectContainer::AddEffect(). То есть на один эффект есть
	// два указателя: в классе EffectContainer и в классе EffectObserver

	// Важно! EffectContainer сам ничего не удаляет, он лишь 
	// помечает эффект на удаление вызовом Kill()

	class EffectObserver : public IController
	{
		friend class EffectsContainer;
		friend class ScreenImpl;

	public:
		EffectProxySharedPtrList _effects;
		std::vector<ParticleEffect*> garbage;

		EffectObserver();
		~EffectObserver();

		void ClearGarbage();
		void DeleteFinished();
		int getGlobalEffectsNumbers();

		virtual bool isFinish();
		virtual void Update(float dt);
		virtual void Pause();
		virtual void Continue();
	};

	extern EffectObserver effectObserver;
}

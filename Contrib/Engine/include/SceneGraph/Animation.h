#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/AnimationChannel.h"
#include "SceneGraph/Delegate.h"

namespace SceneGraph {

///
/// Состояние анимации.
///
struct AnimationState {
	enum Type {
		Stopped,
			/// Остановлена
		Playing,
			/// Проигрывается
		Paused
			/// Приостановлена
	};
};

///
/// Подсказка завершения анимации.
///
struct AnimationFinishHint {
	enum Type {
		Begin,
			/// Завершилась в начале
		End
			/// Завершилась в конце
	};
};

///
/// Поведение анимации после достижения конца.
///
struct AnimationFinishBehaviour {
	enum Type {
		Stop,
			/// Остановиться
		Pause,
			/// Встать на паузу
		Continue,
			/// Продолжить без изменения
		PingPong
			/// Продолжить в обратном направлении
	};
};

///
/// Аргументы события OnStarted
///
class AnimationStartedEventArgs : public EventArgs {
public:
};

///
/// Аргументы события OnFinished
///
class AnimationFinishedEventArgs : public EventArgs {
public:
	AnimationFinishedEventArgs(AnimationFinishHint::Type hint, AnimationFinishBehaviour::Type behaviour);
	
	AnimationFinishHint::Type FinishedAt() const;
		/// Возвращает место остановки
	
	AnimationFinishBehaviour::Type GetBehaviour() const;
		/// Возвращает поведение после остановки
	
	void SetBehaviour(AnimationFinishBehaviour::Type behaviour);
		/// Устанавливает поведение после остановки

private:
	AnimationFinishHint::Type _hint;
		/// Подсказка завершения
	
	AnimationFinishBehaviour::Type _behaviour;
		/// Поведение после завершения
};

///
/// Аргументы события OnStateChanged
///
class AnimationStateChangedEventArgs : public EventArgs {
public:
	AnimationStateChangedEventArgs(AnimationState::Type oldState, AnimationState::Type newState);
	
	AnimationState::Type OldState() const;
		/// Возвращает прежнее состояние анимации
	
	AnimationState::Type NewState() const;
		/// Возвращает новое состояние анимации

private:
	AnimationState::Type _oldState;
		/// Прежнее состояние анимации
	
	AnimationState::Type _newState;
		/// Новое состояние анимации
};

///
/// Аргументы события OnAdvanceTime
///
class AnimationAdvanceTimeEventArgs : public EventArgs {
public:
	AnimationAdvanceTimeEventArgs(float deltaTime);
	
	float DeltaTime() const;
		/// Возвращает время, на сколько продвинулась анимация

private:
	float _deltaTime;
		/// Время продвижения анимации
};

///
/// Анимация.
///
class Animation {
public:
	typedef boost::shared_ptr<Animation> HardPtr;
	
	typedef boost::weak_ptr<Animation> WeakPtr;
	
	typedef std::multimap<SceneNode::WeakPtr, AnimationChannel::HardPtr> ChannelsMap;
	
	Animation(const std::string& name);
	
	virtual ~Animation();
	
	virtual Animation::HardPtr Clone();
		/// Клонирует экземпляр объекта
	
	const std::string& GetName() const;
		/// Возвращает имя анимации
	
	AnimationState::Type GetState() const;
		/// Возвращает состояние анимации
	
	AnimationFinishBehaviour::Type GetBehaviour() const;
		/// Возвращает поведение анимации после достижения конца
	
	void SetBehaviour(AnimationFinishBehaviour::Type behaviour);
		/// Устанавливает поведение анимации после достижения конца
	
	float GetSpeed() const;
		/// Возвращает скорость проигрывания анимации
	
	void SetSpeed(float speed);
		/// Устанавливает скорость проигрывания анимации
	
	float GetBlend() const;
		/// Возвращает коэффициент смешивания анимации
	
	void SetBlend(float blend);
		/// Устанавливает коэффициент смешивания анимации
	
	bool IsInversed() const;
		/// Позволяет узнать, инвертирована ли анимация
	
	virtual void SetInversed(bool value);
		/// Устанавливает инвертирование анимации
	
	ChannelsMap& GetChannels();
		/// Возвращает коллекцию каналов анимации
	
	void FindChannels(SceneNode::WeakPtr node, std::vector<AnimationChannel::HardPtr>& channels) const;
		/// Ищет каналы анимации, ассоциированные с указанным узлом сцены
	
	AnimationChannel::HardPtr FindChannel(SceneNode::WeakPtr node, const std::string& name) const;
		/// Ищет канал анимации с указанным именем, ассоциированный с указанным узлом сцены
	
	void AddChannel(SceneNode::WeakPtr node, AnimationChannel::HardPtr channel);
		/// Добавляет канал анимации
	
	bool RemoveChannel(SceneNode::WeakPtr node, AnimationChannel::HardPtr channel);
		/// Удаляет канал анимации
	
	bool RemoveChannel(SceneNode::WeakPtr node, const std::string& name);
		/// Удаляет канал анимации с указанным именем
	
	bool RemoveChannels(SceneNode::WeakPtr node);
		/// Удаляет все каналы анимации для указанного узла сцены
	
	virtual void Play();
		/// Начинает проигрывание анимации. Продолжает, если была на паузе
	
	virtual void Pause();
		/// Ставит проигрывание анимации на паузу
	
	virtual void Stop();
		/// Останавливает проигрывание анимации
	
	virtual void AdvanceTime(float dt);
		/// Продвигает проигрывание анимации на указанное время

	virtual void SetFrame(int /*frame*/) {};
		/// устанавливаем номер фрейма
	
	Event<AnimationStartedEventArgs> OnStarted;
		/// Вызывается при старте анимации
	
	Event<AnimationFinishedEventArgs> OnFinished;
		/// Вызывается при завершении анимации
	
	Event<AnimationStateChangedEventArgs> OnStateChanged;
		/// Вызывается при изменении состояния анимации
	
	Event<AnimationAdvanceTimeEventArgs> OnAdvanceTime;
		/// Вызывается при продвижении анимации

protected:
	Animation(const Animation& rhs);
	
	Animation& operator = (const Animation& rhs);

protected:
	std::string _name;
		/// Имя анимации.
		/// Должно быть уникальным в пределах одной модели.
	
	ChannelsMap _channels;
		/// Каналы анимации
	
	AnimationState::Type _state;
		/// Состояние анимации
	
	AnimationFinishBehaviour::Type _behaviour;
		/// Поведение анимации после достижения конца
	
	float _speed;
		/// Скорость проигрывания анимации
	
	float _blend;
		/// Коэффициент смешивания анимации
	
	bool _inversed;
		/// Инвертирована ли анимация
};

} // namespace SceneGraph

#endif // __ANIMATION_H__

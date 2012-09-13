#ifndef __KEYFRAMEDANIMATION_H__
#define __KEYFRAMEDANIMATION_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/Animation.h"
#include "SceneGraph/KeyFramedAnimationChannel.h"

namespace SceneGraph {

///
/// Анимация, основанная на ключевых кадрах.
///
class KeyFramedAnimation : public Animation {
public:
	typedef boost::shared_ptr<KeyFramedAnimation> HardPtr;
	
	typedef boost::weak_ptr<KeyFramedAnimation> WeakPtr;
	
	KeyFramedAnimation(const std::string& name, double duration, double ticksPerSec);
	
	Animation::HardPtr Clone();
	
	double GetDuration() const;
		/// Возвращает продолжительность анимации в тиках
	
	double GetTicksPerSec() const;
		/// Возвращает количество тиков в секунду
	
	double GetAdvanceTime() const;
		/// Возвращает время продвижения анимации в секундах
	
	void AdvanceTime(float dt);
		/// Продвигает проигрывание анимации на указанное время
	
	void SetInversed(bool inversed);
		// запускает анимацию в обратном порядке	

	void Stop();
		/// Останавливает проигрывание анимации

	void SetFrame(int frame);

protected:
	KeyFramedAnimation(const KeyFramedAnimation& rhs);
	
	KeyFramedAnimation& operator = (const KeyFramedAnimation& rhs);
	
protected:
	double _duration;
		/// Продолжительность анимации в тиках
	
	double _ticksPerSec;
		/// Количество тиков в секунду
	
	double _advanceTime;
		/// Время продвижения анимации в секундах
};

} // namespace SceneGraph

#endif // __KEYFRAMEDANIMATION_H__

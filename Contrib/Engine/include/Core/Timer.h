#ifndef _CORE_TIMER_H_
#define _CORE_TIMER_H_

#include "Platform/TargetPlatforms.h"

#ifdef ENGINE_TARGET_WIN32
#	define TimeType __int64

#elif defined(ENGINE_TARGET_IPHONE)
//#	define TimeType double
#define TimeType uint64_t

#elif defined(ENGINE_TARGET_MACOS)
#define TimeType uint64_t

#endif

namespace Core
{

class Timer
{
	TimeType _startTime;
	TimeType _elapsedTime;
	TimeType _idleTicks;
	TimeType _idleStartTime;

	TimeType _freq;
	float _inv_freq;

	TimeType getTime();
	/// Задание одного ядра, на котором этот поток будет выполняться
	void static ChooseOneCore(bool &alreadySingleCoreMode);

public:
	Timer();

	void Start();

	void Pause();

	void Resume();

	float getElapsedTime();

	void Randomize();
};

}

#endif

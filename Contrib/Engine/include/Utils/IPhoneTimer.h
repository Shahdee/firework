/*
 *  IPhoneTimer.h
 *  Engine
 *
 *  Created by Slava on 30.07.10.
 *  Copyright 2010 Playrix Entertainment. All rights reserved.
 *
 */

#pragma once

//
// Класс подсчета тиков; считает тики между Start() и Stop() и 
// выводит в консоль среднее количество тиков (в деструкторе).
// Использовать как локальную статическую переменную.
//

#ifdef ENGINE_TARGET_IPHONE

class IPhoneTimer {
	
public:
	
	IPhoneTimer(std::string timerName);
	
	void Start();
	
	void Stop();
	
	~IPhoneTimer();
	
private:
	
	uint64_t _start;
	
	uint64_t _ticks;
	
	unsigned long _calls;
	
	bool _isStarted;
	
	//SYSTEMTIME _startTime;
	
	std::string _timerName;
};

#else
// Простая заглушка чтобы не компилировать cpp-файл
class IPhoneTimer {
public:
	IPhoneTimer(std::string timerName) {}
	void Start() {}
	void Stop() {}
};

#endif
#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <deque>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#include <boost\thread\mutex.hpp>


namespace MM
{

class AudioDeviceWinMM
{
public:
	~AudioDeviceWinMM();
	static bool IsOk() { return true; }
	static AudioDeviceWinMM* NewSource(int ch, int rate, int bits);
	void Play();
	void Pause();
	void Stop();
	void SetVolume(float);
	void SendSoundData(void* buffer, long size);
	void Callback(WAVEHDR*);
	bool Finished();
	int BuffersCount();
	void Update() {};

protected:
	AudioDeviceWinMM(HWAVEOUT h);
	AudioDeviceWinMM();
	void SetHWO(HWAVEOUT h);
	float volume;
	HWAVEOUT hwo;
	struct BUFDATA {
		WAVEHDR whdr;
		void* ptr;
		long size;
	} BUFDATA;
	std::deque<struct AudioDeviceWinMM::BUFDATA> play;
	boost::recursive_mutex audiomutex;
};

}
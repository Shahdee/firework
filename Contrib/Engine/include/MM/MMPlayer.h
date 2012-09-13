#pragma once
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Render/YuvTexture.h"
#include "File.h"

#include "MM.h"
//#include "MM/AudioDeviceWinMM.h"
//#include "MM/AudioDeviceDSound.h"
//#include "AudioDeviceAL.h"
//#include "MM/OggDecoder.h"

namespace MM
{
/// Проигрыватель аудио/видео файлов.
class MMPlayer
{
public:
	MMPlayer(const std::string& filename, bool loop = false, bool onlysound = false, bool frameDrop = true);
	~MMPlayer();
	
	void FadeInTrack(float s);
	void FadeOutTrack(float s);
	
	void Pause(bool pause);

	void Update(float dt);
	bool Finished();
	Render::Texture* GetVideoTexture() const { return video; }
	void Draw(int x, int y, int width, int height);
	bool isReady() {return _ready;}
	void Rewind();

private:
	std::string filename;
	bool loop, onlysound, frameDrop;
	File::uni_file file;
	AudioDevice *audio;
	Render::YuvTexture *video;
	OggDecoder  *ogg;
	bool _fadeIn;
	bool _fadeOut;
	float _fadeInTime;
	float _fadeOutTime;
	float _fadeLength;
	bool _ready;
	bool paused;
	
	void Open();
	void Close();
};

//typedef MMPlayerTemplate<AudioDeviceWinMM, VideoDeviceSDL> MMPlayer;
}
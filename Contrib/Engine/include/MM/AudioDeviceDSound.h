#pragma once
//#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#pragma comment(lib, "dsound.lib")
#include <stack>

namespace MM
{

/// Устройство воспроизведения для DirectSound
class AudioDeviceDSound
{
public:
	/// Этот тип нужен для того, чтобы менеджер ресурсов мог хранить у себя загруженные буферы
	typedef LPDIRECTSOUNDBUFFER AudioBuffer;
	static const AudioBuffer NullBuffer;

	~AudioDeviceDSound();
	static bool IsOk() { return true; }
	/// Создать новый поток воспроизведения, возможно указать аудио данные и зацикленность
	static AudioDeviceDSound* NewStream(int ch, int rate, int bits, void* data = 0, long size=0, bool loop = false);
	/// Создать источник звука как копию уже загруженного буфера
	static AudioDeviceDSound* NewSound(AudioBuffer, bool looping = false);
	/// Загрузить буфер данными для дальнейшего использования
	static AudioBuffer NewBuffer(int ch, int rate, int bits, void* data, long size);
	/// Освободить буфер созданный NewBuffer
	static void ReleaseBuffer(AudioBuffer);
	/// Освободить звуковое устройство
	static void ReleaseDevice();
	/// Количество памяти используемой для буферов (в байтах)
	static long long GetMemUsage();

	void Play();
	void Pause();
	void Stop();
	bool IsPlaying();
	void SetVolume(float);
	/// Установить панораму (-1.f - только левый канал, 0 - оба канала, 1.f - только правый канал)
	void SetPan(float);
	/// Записать в поток воспроизведения очередную порцию данных. Нужно только для потоков созданных NewStream.
	void SendSoundData(void* buffer, long size);
	/// Предупредить устройство, что данных больше не будет. Нужно только для потокового воспроизведения.
	void EndData();
	/// Завершилось ли воспроизведение
	bool Finished();
	/// Сколько данных запасено в закромах родины. Нужно только для потоков созданных NewStream.
	int BuffersCount();
	/// Обязательно вызывать один раз во фрейм
	void Update();
	/// Зацикленный звук?
	bool IsLooping();
	/// Расциклить звук
	void Unloop();

	/// нужны грязные хаки (масдайка даже звук через окно выводит)
	static HWND hwnd;

protected:
	AudioDeviceDSound(LPDIRECTSOUNDBUFFER buf, bool stream, bool loop);
	static HRESULT RestoreBuffer( LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored );
	LPDIRECTSOUNDBUFFER buffer;
	long write_ptr;
	HANDLE hEvent;
	long id;
	static long curid;
	bool looping, streaming;

	/// false - если состояние playing или stopped
	/// true - если при проигрывании поставили на паузу.
	bool paused;

private:
	static IDirectSound8* pDS;
};

}
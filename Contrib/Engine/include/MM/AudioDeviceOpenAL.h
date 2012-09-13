#ifndef _AUDIODEVICEOPENAL_H_
#define _AUDIODEVICEOPENAL_H_

#ifdef ENGINE_TARGET_IPHONE
#	include <OpenAL/al.h>
#	include <OpenAL/alc.h>
#else
#	pragma comment(lib, "openal32.lib")
#	include <al.h>
#	include <alc.h>
#endif

#ifdef THREADED
#	include <boost/thread.hpp>
#endif

namespace MM
{

//
// Устройство воспроизведения для OpenAL
//
class AudioDeviceAL {

public:

	typedef ALuint AudioBuffer;
		// Этот тип нужен для того, чтобы менеджер ресурсов мог хранить у себя загруженные буферы
	
	static const AudioBuffer NullBuffer = 0;
		// Это нулевая константа (идентификатор невалидного буфера)

	~AudioDeviceAL();
	
	// Создать новый поток воспроизведения, возможно указать аудио данные и зацикленность
	static AudioDeviceAL* NewStream(int ch, int rate, int bits, void* data = 0, long size=0, bool loop = AL_FALSE);
	
	// Создать источник звука как копию уже загруженного буфера
	static AudioDeviceAL* NewSound(AudioBuffer, bool _looping = AL_FALSE);

	// Загрузить буфер данными для дальнейшего использования
	static AudioBuffer NewBuffer(int ch, int rate, int bits, void* data, long size);
	
	// Загрузить в буфер wav/aif/caf - файл
	static AudioBuffer LoadUncompressed(const char* filename);
	
	// Освободить буфер созданный NewBuffer
	static void ReleaseBuffer(AudioBuffer);
	
	// Освободить звуковое устройство
	static void ReleaseDevice();
	
	// Количество памяти используемой для буферов (в байтах)
	static long long GetMemUsage();
	
	static bool IsOk();
	
	// Обновить потерянные буферы
	// (вызывать раз во фрейм)
	static void UpdateLostBuffers(float dt);
	
	// Запомнить, что size байт памяти были заняты
	// (для загрузки "внешними" методами)
	static void UseMemory(long long size);

	// Обнулить текущий контекст
	// нужно в iOS, когда приходит аудио-прерывание (звонок, будильник, и т.п.)
	static void SuspendContext();
	
	// Восстановить текущий контекст
	// нужно в iOS, когда заканчивается аудио-прерывание
	static void ResumeContext();
	
	void Play();
	
	void Pause();
	
	void Stop();
	
	bool IsPlaying();
	
	void SetVolume(float);
	
	// -1 - только левый канал, 0 - оба, 1 - только правый канал
	void SetPan(float);
	
	void SetLooping(bool);
	
	// Записать в поток воспроизведения очередную порцию данных. Нужно только для потоков созданных NewStream.
	void SendSoundData(void* buffer, long size);
	
	// Эта функция используется MM:Manager'ом, чтобы если source вдруг закончил играть
	// (кончился буфер), то после добавления данных он продолжил играть.
	void GoOn();
	
	// Предупредить устройство, что данных больше не будет. Нужно только для потокового воспроизведения.
	void EndData();
	
	// Завершилось ли воспроизведение
	bool Finished();
	
	// Сколько данных запасено в закромах родины. Нужно только для потоков созданных NewStream.
	int BuffersCount();
	
	// Обязательно вызывать один раз во фрейм
	void Update();
	
	// Зацикленный звук?
	bool IsLooping();
	
	// Расциклить звук
	void Unloop();

private:
	
	// Конструкторы приватные, ибо объекты создаются статическими методами
	AudioDeviceAL(AudioDeviceAL::AudioBuffer buff, bool loop = AL_FALSE);
	AudioDeviceAL(int ch, int rate, int bits, void* data, long size, bool loop);

	static ALuint NewSource();

	float _volume;
	
	bool _looping;
	
	ALuint _source;
	
	ALsizei _frequency;
	
	ALenum _format;
	
	const ALuint _sourceBuffer;
	
	// отложенное действие, выполняется в Update
	enum { NONE = 0, STOP, PLAY, PAUSE} deferredTask, currentState;
	
	std::vector<ALuint> _buffers;
		// используемые объектом буферы, которые нужно будет удалить
	
	/* -- Статические методы и члены -- */
	
	// Инициализация устройства
	static void Init();
	
	// Распечатать ошибку, если она есть
	// Возвращает true, если ошибка таки была
	static bool PrintError(const char* file, int line);
	
	static ALCdevice *_device;
	
	static ALCcontext *_context;
	
	static int _instances;
		// количество экземпляров класса
	
	static long long _usedMemory;
		// используемая сейчас память
	
	static std::vector<ALuint> _lostBuffers;
		// массив буферов, которые не удалось вовремя освободить
		// (для освобождения в будущем)
		
	static std::deque<ALuint> _sourcesCache;
		// кэш сорсов (создание под айфоном дорого, поэтому храним на будущее)

#ifdef THREADED
	static boost::recursive_mutex& AudioMutex();
#endif
};

}

#endif //_AUDIODEVICEOPENAL_H_

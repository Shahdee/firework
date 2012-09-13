#pragma once

#include <string>
#include <map>
#include <deque>
#include <algorithm>
#include "types.h"
//#include "MM/AudioDeviceDSound.h"
//#include "MM/OggDecoder.h"
#include "MM.h"
#include "File/filestream.h"

namespace MM {

	/// Менеджер звуковых (и видео) ресурсов
	class Manager
	{
	public:
		~Manager();
		static Manager& Self();
		void StartUpdateThread();
		/// Вызывать при завершении приложения
		void ShutDown();

		/// Режимы загрузки звуковых ресурсов
		typedef enum {
			/// Грузится из файла по требованию весь целиком, освобождается по окончании проигрывания
			OnDemand = 0,
			/// Играется потоком
			Streamed = 1,
			/// Сразу загружается весь целиком, никогда не выгружается
			Cached = 2,
			/// Играется потоком, загружается целиком в сжатом виде
			StreamedCached = 3
		} LoadMode;

		/// Режим управления громкостью семпла
		typedef enum {
			/// выбирается из метода запуска
			Managed = 0,
			/// всегда SoundVolume
			ForceSound = 1,
			/// всегда MusicVolume
			ForceMusic = 2, 
			/// всегда Ambience 
			ForceAmbience = 3 
		} VolumeMode;

		/// Загрузка заданного ресурса
		bool LoadSample(const std::string& id, const std::string& file, LoadMode mode = OnDemand, int mix = 2, float volumeFactor = 1.f, std::string group = "", VolumeMode volMode = Managed, float defPan = 0.f, bool pausable = true);
		/// Загрузить все ресурсы типа Cached с заданной группой.
		/// Если будет обращение к ещё не загруженному ресурсу, то он будет обработан как OnDemand
		void LoadGroup(const std::string& group);
		/// Выгрузить все ресурсы типа Cached с заданной группой.
		/// Если будет обращение к ещё не загруженному ресурсу, то он будет обработан как OnDemand
		void UnloadGroup(const std::string& group);
		/// Запустить заданный семпл, возвращает уникальный идентификатор буфера возпроизведения
		/// дополнительно можно указать цикличность воспроизведения и является ли семпл музыкальным треком.
		/// (Трек может быть всего один. К треку потом можно будет обращаться через специальный метод.)
		long PlaySample(const std::string& id, bool looping, float startvolume, bool istrack=false, float freq=1.f);
		long PlaySample(const std::string& id, bool looping = false);
		/// Запустить семпл с множителем частоты
		long PlaySampleFreq(const std::string& id, float freq);
		/// Запустить заданный трек.
		/// Дополнительно можно указать цикличность воспроизведения и является ли семпл музыкальным треком.
		/// Трек может быть всего один. К треку потом можно будет обращаться через специальные методы.
		bool PlayTrack(const std::string& id, bool looping = false, float startvolume = 1.f);
		/// Включить проигрывание семпла по окончании уже запущенного. Если запущенный семпл зацикленный, то он расцикливается.
		bool QueueSample(const std::string& id, long id_buffer, float startvolume = 1.f);
		/// Включить проигрывание семпла по окончании уже запущенного трека. Если запущенный трек зацикленный, то он расцикливается
		bool QueueTrack(const std::string& id, float startvolume = 1.f);
		/// Установить вызов пользовательской функции по завершению семпла. При установке на зацикленный семпл он расцикливается.
		bool SetCallback(long id_buffer, Callback func, void* userData);
		/// Проверить идентификатор буфера на валидность
		bool IsValid(long id_buffer);
		/// Возвращает идентификатор буфера для текущего музыкального трека (или -1 в случае отсутствия такового)
		long GetTrackId();
		
		// Быстро прервать
		// нужно в iOS в начале аудио-прерывания (звонок, будильник, и т.п.)
		void InterruptNow();
		
		// Быстро закончить прерывание
		// нужно в iOS в конец аудио-прерывания
		void ContinueNow();
		
		// Запаузить / отпаузить все играющие сейчас звуки
		void SetPause(bool pause);
		
		/// Запаузить/отпаузить заданный звуковой буфер
		bool SetPauseSample(long id_buffer, bool pause);
		
		/// Проверить запаузен ли буфер
		bool IsPaused(long id_buffer);
		/// Остановить воспроизведение
		void Stop();
		/// Остановить воспроизведение заданного буфера, после этого буфер становится невалидным (все его ресурсы освобождаются)
		bool StopSample(long id_buffer);
		/// Остановить воспроизведение трека, после этого буфер становится невалидным (все его ресурсы освобождаются)
		bool StopTrack();
		/// Установить громкость (для вновь создаваемых буферов громкость равна 1.0f)
		/// Реальная громкость будет умножена на SoundVolume.
		bool SetVolume(long id_buffer, float volume);
		/// Установить громкость (для вновь создаваемых буферов громкость равна 1.0f)
		/// Реальная громкость будет умножена на MusicVolume.
		bool SetTrackVolume(float volume);
		/// Получить громкость буфера
		float GetVolume(long id_buffer);
		/// Установить панораму (-1.f - только левый канал, 0 - оба канала, 1.f - только правый канал)
		bool SetPan(long id_buffer, float p);
		/// Погасить все буферы за заданное время. Если задать targetvolume отличный от нуля, то все буферы будут приведены к заданной громкости
		void Fade(float time, float targetvolume = 0.f);
		/// Погасить все буферы, кроме трека за заданное время.
		void FadeOutAllSample(float time);
		void ChangeTrack(std::string id, float time);
		/// Погасить буфер за заданное время. Если задать targetvolume отличный от нуля, то буфер будет приведён к заданной громкости
		bool FadeSample(long id_buffer, float time, float targetvolume = 0.f);
		/// Погасить текущий трек за заданное время
		bool FadeOutTrack(float time);
		/// Включить текущий трек за заданное время
		bool FadeInTrack(const std::string& id, float time, bool looping = false);
		/// Получить громкость музыки. Этот множитель передаётся в каждый трек.
		float GetMusicVolume();
		/// Получить громкость звуков. Этот множитель передаётся в каждый сэмпл.
		float GetSoundVolume();
		/// Получить громкость звуков окружения. Этот множитель передается в каждый семпл с установленным параметром volumeMode = "ambience"
		float GetAmbienceVolume();
		/// Установить громкость музыки. Этот множитель передаётся в каждый трек.
		void  SetMusicVolume(float);
		/// Установить громкость звуков. Этот множитель передаётся в каждый сэмпл.
		void  SetSoundVolume(float);
		/// Установить громкость звуков окружения. Этот множитель передается в каждый семпл с установленным параметром volumeMode = "ambience"
		void  SetAmbienceVolume(float);
		
		/// Количество используемой памяти (в Кб)
		long GetMemUsage();

		/// Обновить состояние
		void Update(float dt);
		std::string lastPlayedSample;
	private:
		Manager();
		bool LoadSampleData(File::uni_file& file, int& ch, int& rate, int& bits, void** data, long& size);
		int FindResource(const std::string& id);
		struct Sample {
			AudioDevice *device;
			std::deque<OggDecoder*> files;
			float curvolume, targetvolume, fadetime, fadetargettime, volumeFactor;
			bool looping;
			Callback func;
			void* userData;
			struct Sample* next;
			VolumeMode volMode;
			std::string id;
			bool pausable;		// Affected by SetPause
			Sample();
		} Sample;
		typedef std::map<long, struct Sample> SampleMap;
		SampleMap samples;
		typedef std::map<std::string, long> SampleMixMap;
		SampleMixMap samplesMix;
		struct Resource {
			std::string id;
			std::string filename;
			LoadMode mode;
			int mix;
			AudioDevice::AudioBuffer buffer;
			float volumeFactor;
			std::string group;
			OggDecoder* preload;
			File::uni_file* file;
			VolumeMode volMode;
			float defaultPan;
			bool pausable;	// Affected by SetPause
			Resource();
			bool operator<(const struct Manager::Resource& r2) const;
			bool operator>(const struct Manager::Resource& r2) const;
		} Resource;
		typedef std::deque<struct Resource> ResourceVector;
		bool GenSample(struct Sample& sample, ResourceVector::iterator res, bool looping, float freq = 1.f);
		bool DelSample(long id, struct Sample& sample);
		void GenVolume(struct Sample& sample, bool isTrack = false);
		ResourceVector resources;
		bool needToSortResources;
		bool pause;
		
		bool _interrupted;
			// прерван ли менеджер звонком
			// почти пауза, только круче
		
		long track;
		float musicvolume, soundvolume, ambiencevolume;
		static long nextId;
		
		std::string idNextTrack;
		float pauseBeforNextTrack;
		float timeFadeInNextTrack;
#ifdef THREADED
		boost::recursive_mutex updateMutex;
#endif
	};

	extern Manager& manager;
};

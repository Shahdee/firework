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

	/// �������� �������� (� �����) ��������
	class Manager
	{
	public:
		~Manager();
		static Manager& Self();
		void StartUpdateThread();
		/// �������� ��� ���������� ����������
		void ShutDown();

		/// ������ �������� �������� ��������
		typedef enum {
			/// �������� �� ����� �� ���������� ���� �������, ������������� �� ��������� ������������
			OnDemand = 0,
			/// �������� �������
			Streamed = 1,
			/// ����� ����������� ���� �������, ������� �� �����������
			Cached = 2,
			/// �������� �������, ����������� ������� � ������ ����
			StreamedCached = 3
		} LoadMode;

		/// ����� ���������� ���������� ������
		typedef enum {
			/// ���������� �� ������ �������
			Managed = 0,
			/// ������ SoundVolume
			ForceSound = 1,
			/// ������ MusicVolume
			ForceMusic = 2, 
			/// ������ Ambience 
			ForceAmbience = 3 
		} VolumeMode;

		/// �������� ��������� �������
		bool LoadSample(const std::string& id, const std::string& file, LoadMode mode = OnDemand, int mix = 2, float volumeFactor = 1.f, std::string group = "", VolumeMode volMode = Managed, float defPan = 0.f, bool pausable = true);
		/// ��������� ��� ������� ���� Cached � �������� �������.
		/// ���� ����� ��������� � ��� �� ������������ �������, �� �� ����� ��������� ��� OnDemand
		void LoadGroup(const std::string& group);
		/// ��������� ��� ������� ���� Cached � �������� �������.
		/// ���� ����� ��������� � ��� �� ������������ �������, �� �� ����� ��������� ��� OnDemand
		void UnloadGroup(const std::string& group);
		/// ��������� �������� �����, ���������� ���������� ������������� ������ ���������������
		/// ������������� ����� ������� ����������� ��������������� � �������� �� ����� ����������� ������.
		/// (���� ����� ���� ����� ����. � ����� ����� ����� ����� ���������� ����� ����������� �����.)
		long PlaySample(const std::string& id, bool looping, float startvolume, bool istrack=false, float freq=1.f);
		long PlaySample(const std::string& id, bool looping = false);
		/// ��������� ����� � ���������� �������
		long PlaySampleFreq(const std::string& id, float freq);
		/// ��������� �������� ����.
		/// ������������� ����� ������� ����������� ��������������� � �������� �� ����� ����������� ������.
		/// ���� ����� ���� ����� ����. � ����� ����� ����� ����� ���������� ����� ����������� ������.
		bool PlayTrack(const std::string& id, bool looping = false, float startvolume = 1.f);
		/// �������� ������������ ������ �� ��������� ��� �����������. ���� ���������� ����� �����������, �� �� ��������������.
		bool QueueSample(const std::string& id, long id_buffer, float startvolume = 1.f);
		/// �������� ������������ ������ �� ��������� ��� ����������� �����. ���� ���������� ���� �����������, �� �� ��������������
		bool QueueTrack(const std::string& id, float startvolume = 1.f);
		/// ���������� ����� ���������������� ������� �� ���������� ������. ��� ��������� �� ����������� ����� �� ��������������.
		bool SetCallback(long id_buffer, Callback func, void* userData);
		/// ��������� ������������� ������ �� ����������
		bool IsValid(long id_buffer);
		/// ���������� ������������� ������ ��� �������� ������������ ����� (��� -1 � ������ ���������� ��������)
		long GetTrackId();
		
		// ������ ��������
		// ����� � iOS � ������ �����-���������� (������, ���������, � �.�.)
		void InterruptNow();
		
		// ������ ��������� ����������
		// ����� � iOS � ����� �����-����������
		void ContinueNow();
		
		// ��������� / ��������� ��� �������� ������ �����
		void SetPause(bool pause);
		
		/// ���������/��������� �������� �������� �����
		bool SetPauseSample(long id_buffer, bool pause);
		
		/// ��������� �������� �� �����
		bool IsPaused(long id_buffer);
		/// ���������� ���������������
		void Stop();
		/// ���������� ��������������� ��������� ������, ����� ����� ����� ���������� ���������� (��� ��� ������� �������������)
		bool StopSample(long id_buffer);
		/// ���������� ��������������� �����, ����� ����� ����� ���������� ���������� (��� ��� ������� �������������)
		bool StopTrack();
		/// ���������� ��������� (��� ����� ����������� ������� ��������� ����� 1.0f)
		/// �������� ��������� ����� �������� �� SoundVolume.
		bool SetVolume(long id_buffer, float volume);
		/// ���������� ��������� (��� ����� ����������� ������� ��������� ����� 1.0f)
		/// �������� ��������� ����� �������� �� MusicVolume.
		bool SetTrackVolume(float volume);
		/// �������� ��������� ������
		float GetVolume(long id_buffer);
		/// ���������� �������� (-1.f - ������ ����� �����, 0 - ��� ������, 1.f - ������ ������ �����)
		bool SetPan(long id_buffer, float p);
		/// �������� ��� ������ �� �������� �����. ���� ������ targetvolume �������� �� ����, �� ��� ������ ����� ��������� � �������� ���������
		void Fade(float time, float targetvolume = 0.f);
		/// �������� ��� ������, ����� ����� �� �������� �����.
		void FadeOutAllSample(float time);
		void ChangeTrack(std::string id, float time);
		/// �������� ����� �� �������� �����. ���� ������ targetvolume �������� �� ����, �� ����� ����� ������� � �������� ���������
		bool FadeSample(long id_buffer, float time, float targetvolume = 0.f);
		/// �������� ������� ���� �� �������� �����
		bool FadeOutTrack(float time);
		/// �������� ������� ���� �� �������� �����
		bool FadeInTrack(const std::string& id, float time, bool looping = false);
		/// �������� ��������� ������. ���� ��������� ��������� � ������ ����.
		float GetMusicVolume();
		/// �������� ��������� ������. ���� ��������� ��������� � ������ �����.
		float GetSoundVolume();
		/// �������� ��������� ������ ���������. ���� ��������� ���������� � ������ ����� � ������������� ���������� volumeMode = "ambience"
		float GetAmbienceVolume();
		/// ���������� ��������� ������. ���� ��������� ��������� � ������ ����.
		void  SetMusicVolume(float);
		/// ���������� ��������� ������. ���� ��������� ��������� � ������ �����.
		void  SetSoundVolume(float);
		/// ���������� ��������� ������ ���������. ���� ��������� ���������� � ������ ����� � ������������� ���������� volumeMode = "ambience"
		void  SetAmbienceVolume(float);
		
		/// ���������� ������������ ������ (� ��)
		long GetMemUsage();

		/// �������� ���������
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
			// ������� �� �������� �������
			// ����� �����, ������ �����
		
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

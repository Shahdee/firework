#pragma once
//#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#pragma comment(lib, "dsound.lib")
#include <stack>

namespace MM
{

/// ���������� ��������������� ��� DirectSound
class AudioDeviceDSound
{
public:
	/// ���� ��� ����� ��� ����, ����� �������� �������� ��� ������� � ���� ����������� ������
	typedef LPDIRECTSOUNDBUFFER AudioBuffer;
	static const AudioBuffer NullBuffer;

	~AudioDeviceDSound();
	static bool IsOk() { return true; }
	/// ������� ����� ����� ���������������, �������� ������� ����� ������ � �������������
	static AudioDeviceDSound* NewStream(int ch, int rate, int bits, void* data = 0, long size=0, bool loop = false);
	/// ������� �������� ����� ��� ����� ��� ������������ ������
	static AudioDeviceDSound* NewSound(AudioBuffer, bool looping = false);
	/// ��������� ����� ������� ��� ����������� �������������
	static AudioBuffer NewBuffer(int ch, int rate, int bits, void* data, long size);
	/// ���������� ����� ��������� NewBuffer
	static void ReleaseBuffer(AudioBuffer);
	/// ���������� �������� ����������
	static void ReleaseDevice();
	/// ���������� ������ ������������ ��� ������� (� ������)
	static long long GetMemUsage();

	void Play();
	void Pause();
	void Stop();
	bool IsPlaying();
	void SetVolume(float);
	/// ���������� �������� (-1.f - ������ ����� �����, 0 - ��� ������, 1.f - ������ ������ �����)
	void SetPan(float);
	/// �������� � ����� ��������������� ��������� ������ ������. ����� ������ ��� ������� ��������� NewStream.
	void SendSoundData(void* buffer, long size);
	/// ������������ ����������, ��� ������ ������ �� �����. ����� ������ ��� ���������� ���������������.
	void EndData();
	/// ����������� �� ���������������
	bool Finished();
	/// ������� ������ �������� � �������� ������. ����� ������ ��� ������� ��������� NewStream.
	int BuffersCount();
	/// ����������� �������� ���� ��� �� �����
	void Update();
	/// ����������� ����?
	bool IsLooping();
	/// ���������� ����
	void Unloop();

	/// ����� ������� ���� (�������� ���� ���� ����� ���� �������)
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

	/// false - ���� ��������� playing ��� stopped
	/// true - ���� ��� ������������ ��������� �� �����.
	bool paused;

private:
	static IDirectSound8* pDS;
};

}
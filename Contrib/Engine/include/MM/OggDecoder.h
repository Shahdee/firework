#pragma once

#include <fstream>

#pragma comment(lib, "libogg.lib")
#pragma comment(lib, "libvorbis.lib")
#pragma comment(lib, "libtheora.lib")

#include "File/filestream.h"

namespace MM
{
/// Раскодировщик потока ogg/vorbis/theora
class OggDecoder 
{
protected:
	OggDecoder(bool allowFrameDrop = true, bool standalone = false);
public:
	static OggDecoder* NewOggDecoder(bool allowFrameDrop = true, bool standalone = false);
	virtual ~OggDecoder();

	/// Открыть входной файл
	virtual bool OpenStream(const std::string& filename) = 0;
	/// Открыть входной файл
	virtual bool OpenStream(File::uni_file& input) = 0;
	/// Есть ли видео поток
	virtual bool HasVideoStream() = 0;
	/// Есть ли аудио поток
	virtual bool HasAudioStream() = 0;
	/// Получить размер видео кадра
	virtual void GetVideoFrameSize(int& w, int& h, int& x, int& y) = 0;
	/// Получить параметры аудио потока
	virtual void GetAudioParams(int& channels, int& rate, int& bits) = 0;
	/// Конец файла?
	virtual bool IsEof() = 0;
	/// Закончился аудио поток?
	virtual bool IsAudioFinished() = 0;
	/// Закончился видео поток?
	virtual bool IsVideoFinished() = 0;
	/// В цикле получения данных обязательно нужно вызывать этот метод, возвращает true если данные готовы
	virtual bool Update() = 0;
	/// Получить аудио данные. Возвращается указатель на внутренний буфер декодера или 0, если данные не готовы.
	virtual void GetAudioFrame(void** buf, long* size) = 0;
	/// Получить видео данные. Возвращается указатель на внутренний буфер декодера или 0, если данные не готовы.
	virtual void GetVideoFrame(void** buffer) = 0;
	virtual void GetVideoFrame2(void** buffer) = 0;
	/// Получить время от начала воспроизведения
	double GetTime();
	/// Получить запомненное имя файла
	std::string GetFileName();
	///
	bool IsStandalone() const { return standalone; }
	
	virtual void GetPage() = 0;
	virtual void GetVideoPacket() = 0;
	virtual void GetAudioPacket() = 0;
protected:
	bool frameDrop;
	bool standalone;
	// playing time
	double timebase;
	std::string fileName;
};

}

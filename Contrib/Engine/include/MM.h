#pragma once

// этот дифайн предназначен для быстрой замены одного устройства вывода на другое
//#define AudioDevice AudioDeviceAL

/// Пространство имён для мультимедийной подсистемы. Вывод звука и видео здесь.
namespace MM {
}

//#ifdef ENGINE_TARGET_WIN32
//#define AUDIODEVICE_DSOUND
//#define AudioDevice AudioDeviceDSound
//#include "MM/AudioDeviceDSound.h"
//#endif

#define AudioDevice AudioDeviceAL
#include "MM/AudioDeviceOpenAL.h"
#include "MM/OggDecoder.h"
#include "MM/MMPlayer.h"
#include "MM/Manager.h"

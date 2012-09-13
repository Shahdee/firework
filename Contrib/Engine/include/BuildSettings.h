#pragma once
/// \file тут собраны конфигурационные флаги, влияющие на компиляцию движка

/// если выключить будет trial версия
#define FULL_VERSION

/// использовать лог-файл в xml
#define USE_LOG
/// использовать вывод сообщений в консоль
#define USE_DEBUG_MESSAGES
/// выводить отладочную информацию об использовании памяти
#undef WriteDebugMemoryInfo

/// Включить если надо найти баг с памятью
#undef TO_FIND_MEMORY_BUG

#undef NeedDebugScreen

//#define SETTINGS_REG_KEY			"Software\\Playrix Entertainment\\4Elements"
#define DXVERSION_ERROR_CAPTION		"DirectX Version:"
#if defined(ENGINE_TARGET_WIN32_DX9)
#define DXVERSION_ERROR_MESSAGE		"Required DirectX 9.0 or latest"
#elif defined(ENGINE_TARGET_WIN32_DX8)
#define DXVERSION_ERROR_MESSAGE		"Required DirectX 8.0 or latest"
#endif
#define TRIAL_TIME					120

/// Максимальный размер изображения (одна сторона)
#ifdef ENGINE_TARGET_IPHONE
#	define IMAGE_SIZE 1024
#else
#	define IMAGE_SIZE 2048
#endif

/// Профилировать движок
#define SHINY_PROFILER FALSE
/// Включить ниточки
#define THREADED
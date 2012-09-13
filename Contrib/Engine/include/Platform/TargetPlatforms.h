// унифицированные #define для поддерживаемых платформ

#ifndef _PLATFORM_TARGETPLATFORMS_H_
#define _PLATFORM_TARGETPLATFORMS_H_

/////////////////////////////////////////////////////////////////////////////////
// винда
/////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)

	#define ENGINE_TARGET_WIN32

	#if defined(DX9)

		#define ENGINE_TARGET_WIN32_DX9

	#else

		#define ENGINE_TARGET_WIN32_DX8

	#endif

#endif

/////////////////////////////////////////////////////////////////////////////////
// системы от apple
/////////////////////////////////////////////////////////////////////////////////

#if defined(__APPLE__)

#include "TargetConditionals.h"

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE

	// iPhone (настоящий или симулятор)
	#define ENGINE_TARGET_IPHONE

	#if defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR

		// iPhone Simulator
		#define ENGINE_TARGET_IPHONE_SIMULATOR
	
	#else

		// iPhone OS
		#define ENGINE_TARGET_IPHONEOS

	#endif

#else

	// Mac OS
	#define ENGINE_TARGET_MACOS

#endif

#endif

/////////////////////////////////////////////////////////////////////////////////
// ??????
/////////////////////////////////////////////////////////////////////////////////

#endif

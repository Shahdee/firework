// Platform specific staff

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "Platform/TargetPlatforms.h"

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef uchar byte;

#ifdef ENGINE_TARGET_WIN32
#	define DEVCOLOR DWORD
#	define MAKECOLOR4(a, r, g, b) D3DCOLOR_ARGB((a), (r), (g), (b))
#	define MAKECOLOR(c) MAKECOLOR4((c).alpha, (c).red, (c).green, (c).blue)
#	define COLOR_GET_ALPHA(c) (uchar)(((c) & 0xFF000000) >> 24)
#	define COLOR_SET_ALPHA(c, a) { c = ((c) & 0xFFFFFF) | (((a) & 0xFF) << 24); }
#else
#	include <sys/types.h>
#	define MAX_PATH 512
#	define __forceinline
#	define DEVCOLOR Color
#	define MAKECOLOR4(a, r, g, b) Color(r, g, b, a)
#	define MAKECOLOR(c) c
#	define COLOR_GET_ALPHA(c) (c.alpha)
#	define COLOR_SET_ALPHA(c, a) c.alpha = a

typedef unsigned int UINT;
typedef u_int8_t BYTE;
typedef u_int16_t WORD;
typedef u_int32_t DWORD;
typedef int64_t __int64;

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
} SYSTEMTIME;

#define MAKELONG(a, b) ((long)(((WORD)(a & 0xffff)) | ((DWORD)((WORD)(b & 0xffff))) << 16))

#endif

#ifdef ENGINE_TARGET_WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#	include <CommCtrl.h>
#include "Platform/win.h"
#endif

#ifdef ENGINE_TARGET_IPHONE
#include "Platform/iphone.h"
#endif

#if defined(ENGINE_TARGET_IPHONE) || defined(ENGINE_TARGET_MACOS)
// по другому переворачиваются ARGB
#	define ANOTHER_BYTE_ORDER
#endif

#endif // _PLATFORM_H_
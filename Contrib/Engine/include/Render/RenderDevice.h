#ifndef _RENDERDEVICE_H_
#define _RENDERDEVICE_H_

#include "Platform/TargetPlatforms.h"
#include "Render/RenderTypes.h"

#if defined( ENGINE_TARGET_WIN32_DX8 )
#	include "Render/RenderDevice_win.h"
#elif defined( ENGINE_TARGET_WIN32_DX9 )
#	include "Render/RenderDevice_win_dx9.h"
#elif defined( ENGINE_TARGET_IPHONE )
#	include "Render/RenderDeviceInterface.h"
#elif defined( ENGINE_TARGET_MACOS )
#	include "Render/RenderDeviceGL.h"
#else
#	error "Target platform isn't selected"
#endif

#endif //_RENDERDEVICE_H_

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#ifdef ENGINE_TARGET_WIN32
#	include "Core/Application_win.h"
#endif
#ifdef ENGINE_TARGET_IPHONE
#	include "Core/Application_iphone.h"
#endif

#endif //_APPLICATION_H_
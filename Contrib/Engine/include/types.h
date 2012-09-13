#ifndef _TYPES_H_
#define _TYPES_H_
#if !defined(_DEBUG)
#	if defined(_SECURE_SCL)
#		undef _SECURE_SCL
#	endif
#	if defined(_HAS_ITERATOR_DEBUGGING)
#		undef _HAS_ITERATOR_DEBUGGING
#	endif
#	define _HAS_ITERATOR_DEBUGGING 0
#	define _SECURE_SCL 0
#endif

#include "platform.h"

#include "BuildSettings.h"

#ifdef TO_FIND_MEMORY_BUG
#	define _CRTDBG_MAP_ALLOC
#	include <stdlib.h>
#endif
#include <new>
#if defined(TO_FIND_MEMORY_BUG) && defined(ENGINE_TARGET_WIN32)
#	include <crtdbg.h>
#	define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <string>
#include <algorithm>

#include <cmath>
#include <cassert>
#include <limits>

#if !defined(TO_FIND_MEMORY_BUG) && defined(WIN32)
#	include <crtdbg.h>
#endif

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#undef min
#undef max

///////////////////////////////////////////////////////////////
#ifdef ENGINE_TARGET_IPHONE
#undef nil
#define nil _nil
#endif

#include <luabind/luabind.hpp>

#ifdef ENGINE_TARGET_IPHONE
#undef nil
#define nil __null
#endif
///////////////////////////////////////////////////////////////

#ifndef ENGINE_TARGET_WIN32
#define TIXML_USE_STL
#endif
#include "../TinyXML/tinyxml.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"

using std::string;
typedef std::vector<std::string> StringVector;
typedef std::vector<char> CharVector;

#include "Utils/utils.hpp"
#include "Utils/IPoint.h"
#include "Utils/IRect.h"
#include "Utils/FRect.h"
#include "Utils/FPoint.h"
#include "Utils/Color.h"
#include "singleton.hpp"
#include "Utils/Vector3.h"

#define XML_HEADER "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
#define INTRANDOM(num) ( (int)( (float)rand()/RAND_MAX*( (float)num - 0.02f) ) )

typedef void (*Callback)(void *);

#include "Core/Log.h"

#endif //_TYPES_H_
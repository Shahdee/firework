#pragma once

#include "BuildSettings.h"

#ifdef WriteDebugMemoryInfo
#include "psapi.h"
#endif

#ifdef WriteDebugMemoryInfo

void WriteMemoryLogString(string str);

string CreateMemorySizeStr(int size);

int GetUsedMemorySize();

#endif


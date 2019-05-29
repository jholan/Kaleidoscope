#pragma once

#define WIN32_LEAN_AND_MEAN		// Always #define this before #including <windows.h>
#include <windows.h>			// #include this (massive, platform-specific) header in very few places



#define ReleaseCOMHandle(comHandle)  if (comHandle != nullptr) { comHandle->Release(); comHandle = nullptr; }
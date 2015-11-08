#pragma once

#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <windows.h>
#include <string>
#include <memory>
#include <cctype>
#include <vector>
#include "Server.h"

extern void _WriteMemory( DWORD Address, DWORD Value, DWORD nBytes = 4 );
#define WRITEMEMORY _WriteMemory
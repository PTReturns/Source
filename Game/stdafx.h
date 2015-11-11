#pragma once

#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <windows.h>
#include <string>
#include <memory>
#include <cctype>
#include <vector>
#include <iostream>
#include "Game.h"

#include "..\Exception.h"
#include "..\OpCode.h"
#include "..\Structs.h"

extern void _WriteMemory( DWORD Address, DWORD Value, DWORD nBytes = 4 );
#define WRITEMEMORY _WriteMemory
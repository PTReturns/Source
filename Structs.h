#pragma once

struct smPacket
{
	DWORD Size;
	DWORD Code;
	DWORD Params[ 4 ];
};

struct smChat
{
	DWORD Size;
	DWORD Code;
	DWORD Color;
	DWORD ObjectSerial;
	CHAR Message[ 256 ];
};

struct smLevelTable
{
	DWORD Size;
	DWORD Code;
	DWORD Cap;
	FLOAT Multiplier;
	DWORD Base;
};
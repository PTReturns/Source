#pragma once

typedef double DOUBLE;

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

struct smEarnExp
{
	DWORD Size;
	DWORD Code;
	DWORD MonInfo;
	DWORD OldChecks[ 3 ];
	DWORD MemberCount;
	DWORD Divisor;
	INT64 Exp;
	DOUBLE CheckSum;
};

struct smUserInfo
{
	DWORD Size;
	DWORD Code;
	DWORD Params[ 3 ];
	CHAR  ID[ 32 ];
	CHAR  Name[ 32 ];
};

struct smThrowItem2
{
	DWORD Size;
	DWORD Code;
	DWORD Head;
	DWORD ItemCode;
	DWORD ItemCheckSum;
	DWORD PremiumCheckSum;
};

struct smExpireTime
{
	DWORD Size;
	DWORD Code;
	DWORD ExpireTime;

};
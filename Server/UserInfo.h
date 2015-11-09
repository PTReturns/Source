#pragma once
#include "UserData.h"

class CUserInfo
{
public:
	CUserData* AllocUser( const int PlayInfo );
	bool DeAllocUser( const int PlayInfo );
	
	CUserData* GetData( const int PlayInfo );
	CUserData* GetData( const char* ID );
};

extern std::shared_ptr<CUserInfo> pActivePlayers;
#define USERS pActivePlayers
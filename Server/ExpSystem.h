#pragma once
#include "UserInfo.h"
#include "MonsterData.h"

#define MAX_PARTY_DISTANCE 0x144000
#define MAX_PARTY_MEMBERS 6

class CExpSystem
{
public:
	CExpSystem( CUserData* UserData );
	CExpSystem( CUserData* UserData, CMonsterData* MonsterData );

	bool is2BIError( int Exp );
	bool inParty( );
	void GetSoloExp( );
	void GetPartyExp( );
	INT64 GetRealExp( INT64 Exp, int LevelVariation );
	bool GetDistance( CUserData* User );
private:
	int m_Divisor;
	CUserData* m_UserData;
	CMonsterData* m_MonsterData;
};


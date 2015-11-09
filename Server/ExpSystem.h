#pragma once
#include "UserInfo.h"

class CExpSystem
{
public:
	CExpSystem( CUserData* UserData );
	//CExpSystem( CUserData* UserData, CMonsterData* MonsterData );
	~CExpSystem( );

	bool is2BIError( int Exp );
private:
	CUserData* m_UserData;
};


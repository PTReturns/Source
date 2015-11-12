#pragma once
#include "UserInfo.h"

class CLoadUser
{
public:
	CLoadUser( CUserData* User );

	void LoadChar( );
	void SendWelcome( );
	void SendGift( );

private:
	CUserData* m_User;

};


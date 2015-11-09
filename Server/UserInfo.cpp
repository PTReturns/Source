#include "stdafx.h"
#include "UserInfo.h"

std::vector<CUserData*> pUsers;
std::shared_ptr<CUserInfo> pActivePlayers = std::make_shared<CUserInfo>( );

CUserData* CUserInfo::AllocUser( const int PlayInfo )
{
	DeAllocUser( PlayInfo );
	CUserData* UserData = new CUserData( PlayInfo );
	pUsers.push_back( UserData );
	return UserData;
}

bool CUserInfo::DeAllocUser( const int PlayInfo )
{
	int i = 0;
	for( auto &User : pUsers )
	{
		if( User )
		{
			if( User->GetPlayInfo( ) == PlayInfo )
			{
				delete User;
				pUsers.erase( pUsers.begin( ) + i );
				return true;
				break;
			};
		};
		i++;
	};
	return false;
}

CUserData* CUserInfo::GetData( const int PlayInfo )
{
	for( auto &User : pUsers )
	{
		if( User )
		{
			if( User->GetPlayInfo( ) == PlayInfo )
				return User;
		}
	};

	return nullptr;
}

CUserData* CUserInfo::GetData( const char* ID )
{
	for( auto &User : pUsers )
	{
		if( User )
		{
			if( lstrcmpiA( User->GetID( ), ID ) == 0 )
				return User;
		}
	};

	return nullptr;
}
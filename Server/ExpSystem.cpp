#include "stdafx.h"
#include "ExpSystem.h"

CExpSystem::CExpSystem( CUserData* UserData )
{
	m_UserData = UserData;
}

CExpSystem::~CExpSystem( )
{

}

bool CExpSystem::is2BIError( int Exp )
{
	if( m_UserData->GetPrivilege( ) >= PRIVILEGE_LEVEL_SUPPORT )
		return false;

	int Level = m_UserData->GetLevel( );
	if( Level >= 100 )
	{

	}
	else if( Level >= 75 )
	{

	}
	else if( Level >= 50 )
	{

	}
	else if( Level >= 25 )
	{

	}
	else if( Level < 25 )
	{

	}

	return true;
}

bool CheckExperienceEarned( int PlayInfo, int Exp )
{
	CExpSystem* pExp = new CExpSystem( USERS->GetData( PlayInfo ) );
	if( pExp->is2BIError( Exp ) )
	{
		delete pExp;
		return true;
	}
	else
	{
		delete pExp;
		return false;
	};
	return true;
}
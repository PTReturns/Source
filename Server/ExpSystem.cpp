#include "stdafx.h"
#include "ExpSystem.h"

CExpSystem::CExpSystem( CUserData* UserData )
{
	m_UserData = UserData;
}

CExpSystem::CExpSystem( CUserData* UserData, CMonsterData* MonsterData )
{
	m_UserData = UserData;
	m_MonsterData = MonsterData;
}

bool CExpSystem::is2BIError( int Exp )
{
	if( m_UserData->GetPrivilege( ) >= PRIVILEGE_LEVEL_SUPPORT )
		return false;

	int Level = m_UserData->GetLevel( );
	if( Level >= 100 )
	{
		if( Exp >= 0 && Exp < 31250000 )
			return false;
	}
	else if( Level >= 75 )
	{
		if( Exp >= 0 && Exp < 6250000 )
			return false;
	}
	else if( Level >= 50 )
	{
		if( Exp >= 0 && Exp < 1250000 )
			return false;
	}
	else if( Level >= 25 )
	{
		if( Exp >= 0 && Exp < 250000 )
			return false;
	}
	else if( Level < 25 )
	{
		if( Exp >= 0 && Exp < 50000 )
			return false;
	}

#ifdef _DEBUG_MODE_
	std::cout << m_UserData->GetNick( ) << ": 2BIError[ " << Exp << " ]." << std::endl;
#endif

	return true;
}

bool CExpSystem::inParty( )
{
	if( m_UserData->GetPartyState( ) != PARTY_STATE_NONE )
	{
		if( m_UserData->GetPartyMasterData( ) != NULL )
		{
			return true;
		}
		else
		{
			m_UserData->DeleteParty( );
			return false;
		};
	};
	return false;
}

void CExpSystem::GetSoloExp( )
{
	smEarnExp Experience = { 0 };
	Experience.Size = sizeof( smEarnExp );
	Experience.Code = Code::AddSoloExp;
	Experience.MonInfo = m_MonsterData->GetInfo( );
	Experience.MemberCount = 1;
	Experience.Exp = GetRealExp( m_MonsterData->GetExp( ), m_MonsterData->GetLevel( ) - m_UserData->GetLevel( ) );

	// TODO: POTIONS
	if( m_UserData->m_ExpBoost )
	{
		double BoostPercent = ( double )( m_UserData->m_ExpBoost / 100.00 ) + 1.00;

		Experience.Exp *= ( INT64 )BoostPercent;
	};
	//

	m_UserData->AddTotalExp( ( int )Experience.Exp );
	Experience.OldChecks[ 0 ] = ( int )Experience.Exp;
	Experience.OldChecks[ 1 ] = ( ( int )Experience.Exp * 3 + Experience.MonInfo * 13 ) * 2002;
	Experience.OldChecks[ 2 ] = Experience.OldChecks[ 1 ] ^ m_UserData->GetExpOut( );

	Experience.CheckSum = ( double )( ( Experience.MonInfo / 3 ) ^ Experience.Code +
									  ( ( Experience.Exp ^ 0x6B2E9F7D8A5C8F9E ) / 5 ) + Experience.MemberCount );


	Experience.Divisor = m_Divisor;
	m_UserData->SendInt( &Experience );

#ifdef _DEBUG_MODE_
	std::cout << m_UserData->GetNick( ) << ": Solo EXP Earned[ " << Experience.Exp << " ]." << std::endl;
#endif

}

void CExpSystem::GetPartyExp( )
{
	smEarnExp Experience = { 0 };
	Experience.Size = sizeof( smEarnExp );
	Experience.Code = Code::AddPartyExp;
	Experience.MonInfo = m_MonsterData->GetInfo( );
	Experience.Exp = GetRealExp( m_MonsterData->GetExp( ), m_MonsterData->GetLevel( ) - m_UserData->GetPartyAverageLevel( ) );

	CUserData* Members[ MAX_PARTY_MEMBERS ] = { 0 };
	for( int i = 0; i < MAX_PARTY_MEMBERS; i++ )
	{
		Members[ i ] = USERS->GetData( *( int* )( m_UserData->GetPartyMasterData( ) + 0xAFB8 + ( i * 4 ) ) );
		if( Members[ i ] && Members[ i ]->GetInfo( ) )
		{
			Experience.MemberCount++;
			if( Members[ i ]->GetInfo( ) == m_UserData->GetInfo( ) )
			{
				Members[ i ] = nullptr;
			};
			if( GetDistance( Members[ i ] ) )
			{
				Members[ i ] = nullptr;
				Experience.MemberCount--;
			};
		};
	}

	double Exp = ( double )Experience.Exp;
	switch( Experience.MemberCount )
	{
		case 2: Exp *= 0.75; break;
		case 3: Exp *= 0.57; break;
		case 4: Exp *= 0.47; break;
		case 5: Exp *= 0.42; break;
		case 6: Exp *= 0.38; break;
	};

	Experience.Exp = ( INT64 )Exp;

	INT64 LeaderExp = Experience.Exp;
	INT64 MemberExp = Experience.Exp;

	// TODO: POTIONS
	if( m_UserData->m_ExpBoost )
	{
		double BoostPercent = ( double )( m_UserData->m_ExpBoost / 100.00 ) + 1.00;

		LeaderExp *= ( INT64 )BoostPercent;
	};
	//

	Experience.Exp = MemberExp;
	Experience.CheckSum = ( double )( ( Experience.MonInfo / 3 ) ^ Experience.Code +
									  ( ( Experience.Exp ^ 0x6B2E9F7D8A5C8F9E ) / 5 ) + Experience.MemberCount );

	Experience.OldChecks[ 0 ] = ( int )MemberExp;
	Experience.OldChecks[ 1 ] = ( ( int )MemberExp * 3 + Experience.MonInfo * 13 ) * 2002;
	Experience.Divisor = m_Divisor;

	for( auto &Member : Members )
	{
		if( Member )
		{
			if( Member->GetInfo( ) != m_UserData->GetInfo( ) )
			{
				Member->AddTotalExp( ( int )MemberExp );

				Experience.OldChecks[ 2 ] = Experience.OldChecks[ 1 ] ^ Member->GetExpOut( );

				Member->SendInt( &Experience );

#ifdef _DEBUG_MODE_
				std::cout << Member->GetNick( ) << ": Party EXP Earned[ " << MemberExp << " ]." << std::endl;
#endif
			};
		};
	};

	m_UserData->AddTotalExp( ( int )LeaderExp );

	Experience.Exp = LeaderExp;
	Experience.CheckSum = ( double )( ( Experience.MonInfo / 3 ) ^ Experience.Code +
									  ( ( Experience.Exp ^ 0x6B2E9F7D8A5C8F9E ) / 5 ) + Experience.MemberCount );

	Experience.OldChecks[ 0 ] = ( int )LeaderExp;
	Experience.OldChecks[ 1 ] = ( ( int )LeaderExp * 3 + Experience.MonInfo * 13 ) * 2002;
	Experience.OldChecks[ 2 ] = Experience.OldChecks[ 1 ] ^ m_UserData->GetExpOut( );

	m_UserData->SendInt( &Experience );

#ifdef _DEBUG_MODE_
	std::cout << m_UserData->GetNick( ) << ": Party EXP Earned[ " << LeaderExp << " ]." << std::endl;
#endif
}

INT64 CExpSystem::GetRealExp( INT64 Exp, int LevelVariation )
{
	// Módulo da variação do level.
	if( LevelVariation < 0 ) LevelVariation *= -1;

	if( LevelVariation >= 50 )
	{
		m_Divisor = 0;
		return 0;
	}
	else if( LevelVariation >= 40 )
	{
		m_Divisor = 25;
		return ( INT64 )( Exp * 0.25 );
	}
	else if( LevelVariation >= 30 )
	{
		m_Divisor = 50;
		return ( INT64 )( Exp * 0.50 );
	}
	else if( LevelVariation >= 20 )
	{
		m_Divisor = 75;
		return ( INT64 )( Exp * 0.75 );
	}
	else if( LevelVariation < 20 )
	{
		m_Divisor = 100;
		return ( INT64 )( Exp );
	}

	m_Divisor = 0;
	return 0;
}

bool Check_Experience_Earned( int PlayInfo, int Exp )
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

bool CExpSystem::GetDistance( CUserData* User )
{
	if( User )
	{
		int DistX = ( m_UserData->GetPositionX( ) - User->GetPositionX( ) ) >> 8;
		int DistZ = ( m_UserData->GetPositionZ( ) - User->GetPositionZ( ) ) >> 8;
		int TotalDist = DistX * DistX + DistZ * DistZ;

		if( TotalDist < MAX_PARTY_DISTANCE )
			return false;
		return true;
	};
	return false;
}

void Get_Experience( const int PlayInfo, const int MonsterInfo )
{
	CMonsterData* MonsterData = new CMonsterData( MonsterInfo );
	CExpSystem* pExp = new CExpSystem( USERS->GetData( PlayInfo ), MonsterData );
	if( pExp->inParty( ) )
		pExp->GetPartyExp( );
	else
		pExp->GetSoloExp( );
	delete pExp;
	delete MonsterData;
}
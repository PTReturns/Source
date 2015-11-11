#include "stdafx.h"
#include "ExpSystem.h"
#include "MonsterData.h"
#include "LevelTable.h"
#include "UserData.h"

CExpSystem::CExpSystem( )
{
	m_Exp = nullptr;
}

CExpSystem::CExpSystem( smEarnExp* Exp )
{
	m_Exp = Exp;
}

void CExpSystem::System( )
{
	int MonsterInfo = GetMonsterInfo( m_Exp->MonInfo );
	if( MonsterInfo )
	{
		if( m_Exp->CheckSum == ( double )( ( m_Exp->MonInfo / 3 ) ^ m_Exp->Code +
			( ( m_Exp->Exp ^ 0x6B2E9F7D8A5C8F9E ) / 5 ) + m_Exp->MemberCount ) )
		{
			CMonsterData* MonsterData = new CMonsterData( MonsterInfo );
			AddExp( m_Exp->Exp );
			MonsterData->SetExp( ( int )m_Exp->Exp );

			std::string ExpText = std::to_string( m_Exp->Exp );
			for( int i = ExpText.size( ) - 3; i > 0; i -= 3 )
			{
				ExpText.insert( ExpText.begin( ) + i, ',' );
			}

			char Buffer[ 256 ] = { 0 };
			if( m_Exp->Code == Code::AddPartyExp )
			{
				sprintf_s( Buffer, "> Ganhou: %s de Experiência[ %d%% ].", ExpText.c_str( ), m_Exp->Divisor );
				AddChatMsg( Buffer, 9 );

				CheckPartyQuest1( MonsterData->GetCode( ) );
				CheckPartyQuest2( ( int* )0x035F36C0, MonsterData->GetCode( ) );
			}
			else
			{
				sprintf_s( Buffer, "> Ganhou: %s de Experiência[ %d%% ].", ExpText.c_str( ), m_Exp->Divisor );
				AddChatMsg( Buffer, 9 );

				CheckQuest1( MonsterData->GetCode( ) );
				CheckQuest2( ( int* )0x035F36C0, MonsterData->GetCode( ) );
			};
			delete MonsterData;
		}
		else
		{
			USER->SendHackLog( HackCode::Exp, ( int )m_Exp->Exp );
		};
	};
}

void CExpSystem::AddExp( INT64 Exp )
{
	if( Exp < 0 )
		return;

	__int64 CharExp = XorExp( );
	CharExp += Exp;
	if( CharExp >= Levels[ LEVEL_CAP ] )
		CharExp = Levels[ LEVEL_CAP ] - 1;

	SetExp( USER->GetCharAddress( ), CharExp );
	XorExp( );
	ReformChar( );

	int OldLevel = USER->GetLevel( );
	int CharLevel = OldLevel;
	if( Exp && OldLevel < LEVEL_CAP )
	{
		while( true )
		{
			if( Levels[ CharLevel ] > CharExp && CharExp <= Levels[ CharLevel + 1 ] )
				break;
			CharLevel++;
			if( CharLevel >= LEVEL_CAP )
				break;
		};

		if( OldLevel == CharLevel )
			return;

		LevelUp( CharLevel );
	};
}

void CExpSystem::LevelUp( int CharLevel )
{
	USER->SetLevel( CharLevel );
	USER->SetNextLevelExp( ( int )Levels[ CharLevel + 1 ] );

	StartEffect( USER->GetPositionX( ),
				 USER->GetPositionY( ) + 8192,
				 USER->GetPositionZ( ),
				 300, 1 );
	PlaySound( 7, 400 );
	ReformChar( );
	SendPlayerInfo( );
	SaveGame( );
}

void Add_Exp( INT64 Exp )
{
	CExpSystem* pExp = new CExpSystem( );
	pExp->AddExp( Exp );
	delete pExp;
}

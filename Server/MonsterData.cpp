#include "stdafx.h"
#include "MonsterData.h"

CMonsterData::CMonsterData( const int MonsterInfo )
{
	m_MonInfo = MonsterInfo;
}

int CMonsterData::GetLevel( ) const
{
	return *( int* )( m_MonInfo + 0x3944 );
}

int CMonsterData::GetExp( ) const
{
	return *( int* )( m_MonInfo + 0x3ABC );
}

int CMonsterData::GetInfo( ) const
{
	return *( int* )( m_MonInfo + 0x10 );
}
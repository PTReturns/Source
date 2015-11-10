#include "stdafx.h"
#include "MonsterData.h"

CMonsterData::CMonsterData( const int MonsterInfo )
{
	m_MonInfo = MonsterInfo;
}

int CMonsterData::GetCode( ) const
{
	return *( int* )( m_MonInfo + 0x3A74 );
}


void CMonsterData::SetExp( int Exp ) const
{
	*( int* )( m_MonInfo + 0x2B0 ) = Exp;
}
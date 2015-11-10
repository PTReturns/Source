#pragma once

class CMonsterData
{
	//Conversions
public:
	operator int( ) { return m_MonInfo; }
	int operator=( const int value ) { m_MonInfo = value; return m_MonInfo; };
public:
	CMonsterData( const int MonsterInfo );

	int GetLevel( ) const;
	int GetExp( ) const;
	int GetInfo( ) const;

	void SetAddress( const int MonsterInfo ) { m_MonInfo = MonsterInfo; };
private:
	int m_MonInfo;
};

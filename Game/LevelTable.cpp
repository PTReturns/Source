#include "stdafx.h"
#include "LevelTable.h"

std::vector<INT64> Levels;
int LevelCap = 0;

CLevelTable::CLevelTable( int LevelCap, float LevelMultipler, int LevelBase )
{
	::LevelCap = LevelCap;
	m_LevelCap = LevelCap;
	m_LevelMultiplier = LevelMultipler;
	m_LevelBase = LevelBase;

	INT64 Buff = 0;
	Levels.clear( );
	Levels.resize( m_LevelCap + 2 );
	Levels[ 0 ] = 0;
	Levels[ 1 ] = m_LevelBase;
	for( int i = 2; i <= m_LevelCap; i++ )
	{
		Buff = ( INT64 )( Levels[ i - 1 ] * m_LevelMultiplier );
		Levels[ i ] = Buff + m_LevelBase;
	};
	Levels[ m_LevelCap + 1 ] = -1;

	ReferenceLevel( );
}

void CLevelTable::ReferenceLevel( )
{
	LPVOID LevelData = VirtualAlloc( nullptr, Levels.size( ) * sizeof( INT64 ) + 8,
									 MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	*( INT64* )( 0x0A00090009 );
	memcpy_s( ( LPVOID )( ( int )LevelData + 8 ), Levels.size( ) * sizeof( INT64 ),
			  &Levels[ 0 ], Levels.size( ) * sizeof( INT64 ) );

	WRITEMEMORY( 0x0045B1C5 + 3, ( int )LevelData );
	WRITEMEMORY( 0x00461FBC + 3, ( int )LevelData );
	WRITEMEMORY( 0x004620D6 + 3, ( int )LevelData );
	WRITEMEMORY( 0x004A9A57 + 3, ( int )LevelData );
	WRITEMEMORY( 0x004A9A92 + 3, ( int )LevelData );
	WRITEMEMORY( 0x004A9AB3 + 3, ( int )LevelData );
	WRITEMEMORY( 0x004A9AFC + 3, ( int )LevelData );
	WRITEMEMORY( 0x004ACF02 + 3, ( int )LevelData );

	WRITEMEMORY( 0x0045B1CD + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x00461FC4 + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x004620DF + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x004A9A42 + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x004A9A9E + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x004A9B08 + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x004ACEFB + 3, ( int )LevelData + 4 );

	WRITEMEMORY( 0x0045B1EF + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x0045B254 + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x00461FCD + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x004620C7 + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x004A9A5E + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x004A9ABA + 3, ( int )LevelData + 8 );

	WRITEMEMORY( 0x0045A5EC + 1, ( int )LevelData + 10 );

	WRITEMEMORY( 0x0045B1F8 + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x0045B25B + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x00461FD4 + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x004620CE + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x004A9A67 + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x004A9AC3 + 3, ( int )LevelData + 12 );
}

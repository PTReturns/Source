#include "stdafx.h"
#include "LevelTable.h"

std::shared_ptr<CLevelTable> pLevelTable = std::make_shared<CLevelTable>( );

std::vector<INT64> Levels;

CLevelTable::CLevelTable( )
{
	INT64 Buff = 0;
	Levels.clear( );
	Levels.resize( LEVEL_CAP + 2 );
	Levels[ 0 ] = 0;
	Levels[ 1 ] = LEVEL_BASE;
	for( int i = 2; i <= LEVEL_CAP; i++ )
	{
		Buff = ( INT64 )( Levels[ i - 1 ] * LEVEL_MULTIPLIER );
		Levels[ i ] = Buff + LEVEL_BASE;
	};
	Levels[ LEVEL_CAP + 1 ] = -1;

	ReferenceLevel( );
}

void CLevelTable::ReferenceLevel( )
{
	LPVOID LevelData = VirtualAlloc( nullptr, Levels.size( ) * sizeof( INT64 ) + 8,
									 MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	*( INT64* )( 0x0A00090009 );
	memcpy_s( ( LPVOID )( ( int )LevelData + 8 ), Levels.size( ) * sizeof( INT64 ),
			  &Levels[ 0 ], Levels.size( ) * sizeof( INT64 ) );

	WRITEMEMORY( 0x00443B05 + 3, ( int )LevelData );
	WRITEMEMORY( 0x0044A26C + 3, ( int )LevelData );
	WRITEMEMORY( 0x0044A3A6 + 3, ( int )LevelData );
	WRITEMEMORY( 0x0047DD57 + 3, ( int )LevelData );
	WRITEMEMORY( 0x0047DD92 + 3, ( int )LevelData );
	WRITEMEMORY( 0x0047DDB3 + 3, ( int )LevelData );
	WRITEMEMORY( 0x0047DDFC + 3, ( int )LevelData );
	WRITEMEMORY( 0x0048052C + 3, ( int )LevelData );
	WRITEMEMORY( 0x00443B0D + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x0044A274 + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x0044A3AF + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x0047DD42 + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x0047DD9E + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x0047DE08 + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x00480525 + 3, ( int )LevelData + 4 );
	WRITEMEMORY( 0x00443B2F + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x00443B94 + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x0044A185 + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x0044A27D + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x0044A397 + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x0047DD5E + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x0047DDBA + 3, ( int )LevelData + 8 );
	WRITEMEMORY( 0x004431CC + 1, ( int )LevelData + 10 );
	WRITEMEMORY( 0x00443B38 + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x00443B9B + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x0044A17C + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x0044A284 + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x0044A39E + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x0047DD67 + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x0047DDC3 + 3, ( int )LevelData + 12 );
	WRITEMEMORY( 0x0044A1D7 + 3, ( int )LevelData + 16 );

	WRITEMEMORY( 0x005DEC20 + 6, LEVEL_CAP );
	WRITEMEMORY( 0x004439E8 + 1, LEVEL_CAP );
}

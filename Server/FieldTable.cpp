#include "stdafx.h"
#include "FieldTable.h"
#include "SQLApi.h"

void CFieldTable::BuildFields( )
{
	int nMaps = 0;
	SQLBuffer Maps;
	SecureZeroMemory( ( void* )0x0075B038, 0x3AA00 );
	if( SQL->Select( Maps, "SELECT * FROM ServerDB.dbo.Maps" ) )
	{
		nMaps = Maps.size( ) - 1;
		if( nMaps > MAX_TOTAL_FIELD )
			nMaps = MAX_TOTAL_FIELD;

		int Address = 0x0075B038;
		int nFieldAddr = 0x0075BE94;

#ifdef _DEBUG_MODE_
		std::cout << "Reading Maps[ " << nMaps << " ]..." << std::endl;
#endif
		for( int i = 0; i < nMaps; i++ )
		{
			*( int* )( nFieldAddr ) = atoi( Maps[ i ][ 0 ].c_str( ) );

			strcpy_s( ( char* )( Address + 0x4 ), 0x40, Maps[ i ][ 2 ].c_str( ) );
			*( int* )( Address + 0xC4 ) = GetEnvironmentFromString( Maps[ i ][ 3 ].c_str( ) );
			*( int* )( Address + 0xCB8 ) = atoi( Maps[ i ][ 4 ].c_str( ) );

			Address += 0xEA8;
			nFieldAddr += 0xEA8;

#ifdef _DEBUG_MODE_
			std::cout << "Map read[ " << Maps[ i ][ 2 ].c_str( ) << " ]..." << std::endl;
#endif
		};
	};

#ifdef _DEBUG_MODE_
	std::cout << "All found maps are read." << std::endl;
#endif
}

int CFieldTable::GetEnvironmentFromString( const char* String )
{
	if( lstrcmpiA( String, "City" ) == 0 )
		return FieldEnvironment::City;
	else if( lstrcmpiA( String, "Forest" ) == 0 )
		return FieldEnvironment::Forest;
	else if( lstrcmpiA( String, "Desert" ) == 0 )
		return FieldEnvironment::Desert;
	else if( lstrcmpiA( String, "Ruins" ) == 0 )
		return FieldEnvironment::Ruins;
	else if( lstrcmpiA( String, "Dungeon" ) == 0 )
		return FieldEnvironment::Dungeon;
	else if( lstrcmpiA( String, "Iron" ) == 0 )
		return FieldEnvironment::Iron;
	else if( lstrcmpiA( String, "Office" ) == 0 )
		return FieldEnvironment::Office;
	else if( lstrcmpiA( String, "Ice" ) == 0 )
		return FieldEnvironment::Ice;
	else if( lstrcmpiA( String, "Castle" ) == 0 )
		return FieldEnvironment::Castle;
	else if( lstrcmpiA( String, "Mini-Game" ) == 0 )
		return FieldEnvironment::MiniGame;
	return FieldEnvironment::Invalid;
}

void Initialize_Maps( )
{
	CFieldTable* pField = new CFieldTable( );
	pField->BuildFields( );
	delete pField;
}
#include "stdafx.h"
#include "Main.h"

#ifdef _DEBUG_MODE_
void StartConsole( )
{
	FILE* Console = nullptr;
	AllocConsole( );
	freopen_s( &Console, "CONOUT$", "w", stdout );
}
#endif

void Server( )
{
#ifdef _DEBUG_MODE_
	StartConsole( ); 
#endif

	CMain* pMain = new CMain( );
	pMain->Hook( );
	delete pMain;
}
#include "stdafx.h"
#include "Main.h"

void Game( )
{
	CMain* pMain = new CMain( );
	pMain->Hook( );
	delete pMain;
}
#include "stdafx.h"
#include "Main.h"



void Server( )
{
	CMain* pMain = new CMain( );
	pMain->Hook( );
	delete pMain;
}
#include "stdafx.h"
#include "Main.h"

extern void Initialize_Maps( );


CMain::CMain( )
{

}

void CMain::Hook( )
{
	*( UINT* )( PSTALE + 0x4 ) = ( UINT )&Initialize_Maps;
}
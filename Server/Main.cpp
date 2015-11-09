#include "stdafx.h"
#include "Main.h"

//extern void Network_Packet( );
extern void Initialize_Maps( );

CMain::CMain( )
{

}

void CMain::Hook( )
{
	//*( UINT* )( PSTALE + 0x0 ) = ( UINT )&Network_Packet;
	*( UINT* )( PSTALE + 0x4 ) = ( UINT )&Initialize_Maps;
}
#include "stdafx.h"
#include "Main.h"

extern void Network_Packet( smPacket* Packet );

CMain::CMain( )
{

}

void CMain::Hook( )
{
	*( UINT* )( PSTALE + 0x0 ) = ( UINT )&Network_Packet;
}
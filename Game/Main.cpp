#include "stdafx.h"
#include "Main.h"

extern void Network_Packet( smPacket* Packet );
extern void Add_Exp( INT64 Exp );
extern void Render_Premium( );

CMain::CMain( )
{

}

void CMain::Hook( )
{
	*( UINT* )( PSTALE + 0x0 ) = ( UINT )&Network_Packet;
	*( UINT* )( PSTALE + 0x4 ) = ( UINT )&Add_Exp;
	*( UINT* )( PSTALE + 0x8 ) = ( UINT )&Render_Premium;
}
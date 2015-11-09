#include "stdafx.h"
#include "Main.h"

extern void Network_Packet( const int PlayInfo, smPacket* Packet );
extern void Initialize_Maps( );
extern bool CheckExperienceEarned( int PlayInfo, int Exp );


CMain::CMain( )
{

}

void CMain::Hook( )
{
	*( UINT* )( PSTALE + 0x0 ) = ( UINT )&Network_Packet;
	*( UINT* )( PSTALE + 0x4 ) = ( UINT )&Initialize_Maps;
	*( UINT* )( PSTALE + 0x8 ) = ( UINT )&CheckExperienceEarned;

}
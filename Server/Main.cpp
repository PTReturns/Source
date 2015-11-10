#include "stdafx.h"
#include "Main.h"

extern void Network_Packet( const int PlayInfo, smPacket* Packet );
extern void Initialize_Maps( );
extern bool Check_Experience_Earned( int PlayInfo, int Exp );
extern void Get_Experience( const int PlayInfo, const int MonsterInfo );

CMain::CMain( )
{

}

void CMain::Hook( )
{
	*( UINT* )( PSTALE + 0x0 ) = ( UINT )&Network_Packet;
	*( UINT* )( PSTALE + 0x4 ) = ( UINT )&Initialize_Maps;
	*( UINT* )( PSTALE + 0x8 ) = ( UINT )&Check_Experience_Earned;
	*( UINT* )( PSTALE + 0xC ) = ( UINT )&Get_Experience;

}
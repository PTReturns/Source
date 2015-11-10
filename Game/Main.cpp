#include "stdafx.h"
#include "Main.h"


extern void Network_Packet( smPacket* Packet );

extern DWORD __cdecl readConfigHook( );

CMain::CMain( )
{

}

void CMain::Hook( )
{
	*( UINT* )( PSTALE + 0x0 ) = ( UINT )&Network_Packet;
	*( DWORD* )0x04BC5740 = ( DWORD )&readConfigHook;
}
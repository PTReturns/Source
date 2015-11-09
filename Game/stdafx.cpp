#include "stdafx.h"

void _WriteMemory( DWORD Address, DWORD Value, DWORD nBytes )
{
	DWORD VP = 0;
	VirtualProtect( ( LPVOID )Address, nBytes, PAGE_EXECUTE_READWRITE, &VP );
	switch( nBytes )
	{
		case 1:
			*( BYTE* )( Address ) = ( BYTE )Value;
			break;
		case 2:
			*( WORD* )( Address ) = ( WORD )Value;
			break;
		case 4:
			*( DWORD* )( Address ) = ( DWORD )Value;
			break;
	};
	VirtualProtect( ( LPVOID )Address, nBytes, VP, &VP );
}
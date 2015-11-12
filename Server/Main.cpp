#include "stdafx.h"
#include "Main.h"

#include "UserInfo.h"
#include "Premium.h"

extern void Network_Packet( const int PlayInfo, smPacket* Packet );
extern void Initialize_Maps( );
extern bool Check_Experience_Earned( int PlayInfo, int Exp );
extern void Get_Experience( const int PlayInfo, const int MonsterInfo );
extern void Load_User( int PlayInfo );

void __stdcall MainTimer( HWND hWnd, UINT Message, UINT_PTR ID, DWORD Time );

CMain::CMain( )
{
	SetTimer( NULL, NULL, 60000, MainTimer );
}

void CMain::Hook( )
{
	*( UINT* )( PSTALE + 0x0 ) = ( UINT )&Network_Packet;
	*( UINT* )( PSTALE + 0x4 ) = ( UINT )&Initialize_Maps;
	*( UINT* )( PSTALE + 0x8 ) = ( UINT )&Check_Experience_Earned;
	*( UINT* )( PSTALE + 0xC ) = ( UINT )&Get_Experience;
	*( UINT* )( PSTALE + 0x10 ) = ( UINT )&Load_User;
}

void __stdcall MainTimer( HWND hWnd, UINT Message, UINT_PTR ID, DWORD Time )
{
	for( auto &User : pUsers )
	{
		if( User && User->GetInfo( ) && User->m_PremiumCount )
		{
			PREMIUM->SetUser( User );
			PREMIUM->SavePremiums( );
		};
	};
}
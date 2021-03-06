#include "stdafx.h"
#include "NetworkPacket.h"
#include "LevelTable.h"
#include "ExpSystem.h"

#include "Premium.h"

//Premium Externals
extern void __stdcall CheckPremiums( HWND hWnd, UINT Message, UINT_PTR ID, DWORD Time );
extern bool TimerCount;
//

CNetworkPacket::CNetworkPacket( smPacket* Packet )
{
	m_Packet = Packet;
}

bool CNetworkPacket::VerifyPacket( )
{
	switch( m_Packet->Code )
	{
		case Code::BuildLevelTable:
			{
				smLevelTable &GameTable = *( smLevelTable* )m_Packet;
				CLevelTable* pGameLevel = new CLevelTable( GameTable.Cap,
														   GameTable.Multiplier,
														   GameTable.Base );
				delete pGameLevel;
			}
			return true;

		case Code::SendPremiumItem:
		case Code::LoadPremiumItem:
			{
				smPremiumItem &PremiumItem = *( smPremiumItem* )m_Packet;

				if( !TimerCount )
				{
					SetTimer( NULL, NULL, 1000, CheckPremiums );
					TimerCount = true;
				};

				PREMIUM->AddItem( &PremiumItem );
			}
			return true;

		case Code::AddSoloExp:
		case Code::AddPartyExp:
			{
				smEarnExp &Exp = *( smEarnExp* )m_Packet;
				CExpSystem* pExp = new CExpSystem( &Exp );
				pExp->System( );
				delete pExp;
			}
			return true;

	};

	return false;
}

void CNetworkPacket::DeletePacket( )
{
	m_Packet->Code = NULL;
}

void Network_Packet( smPacket* Packet )
{
	CNetworkPacket* pGameNet = new CNetworkPacket( Packet );
	if( pGameNet->VerifyPacket( ) )
		pGameNet->DeletePacket( );
	delete pGameNet;
}
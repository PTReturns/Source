#include "stdafx.h"
#include "NetworkPacket.h"
#include "LevelTable.h"
#include "ExpSystem.h"

#include "Premium.h"

//Premium Externals
extern DWORD WINAPI CheckPremiuns( LPVOID Item );
extern bool ThreadMode;
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
			{
				smExpireTime &PremiumItem = *( smExpireTime* )m_Packet;
				if( !ThreadMode )
				{
					DWORD tID = 0;
					CreateThread( NULL, NULL, CheckPremiuns, ( LPVOID )&PremiumItem, NULL, &tID );
					ThreadMode = true;
				}
				else
				{
					CPremium* pPremium = new CPremium( );
					pPremium->AddItem( &PremiumItem );
					delete pPremium;
				};
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
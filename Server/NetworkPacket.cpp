#include "stdafx.h"
#include "NetworkPacket.h"

CNetworkPacket::CNetworkPacket( const int PlayInfo, smPacket* Packet )
{
	m_UserData = USERS->GetData( PlayInfo );
	m_Packet = Packet;
	m_PlayInfo = PlayInfo;
}

bool CNetworkPacket::VerifyPacket( )
{
	if( !m_UserData && m_Packet->Code != Code::Connection )
		m_UserData = USERS->AllocUser( m_PlayInfo );

	switch( m_Packet->Code )
	{
		case Code::Connection:
			{
				// TODO: Anti-Buum!
				smLevelTable Level = { 0 };
				Level.Size = sizeof( smLevelTable );
				Level.Code = Code::BuildLevelTable;
				Level.Cap = LEVEL_CAP;
				Level.Multiplier = LEVEL_MULTIPLIER;
				Level.Base = LEVEL_BASE;
				m_UserData = USERS->AllocUser( m_PlayInfo );
				m_UserData->SendInt( &Level );
			}
			break;
	};

	return false;
}

void CNetworkPacket::DeletePacket( )
{
	m_Packet->Code = 0;
};

void Network_Packet( const int PlayInfo, smPacket* Packet )
{
	CNetworkPacket* pServerNet = new CNetworkPacket( PlayInfo, Packet );
	if( pServerNet->VerifyPacket( ) )
		pServerNet->DeletePacket( );
	delete pServerNet;
}
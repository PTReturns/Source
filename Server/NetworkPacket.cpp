#include "stdafx.h"
#include "NetworkPacket.h"
#include "Premium.h"

CNetworkPacket::CNetworkPacket( const int PlayInfo, smPacket* Packet )
{
	m_UserData = USERS->GetData( PlayInfo );
	m_Packet = Packet;
	m_PlayInfo = PlayInfo;
}

bool CNetworkPacket::VerifyPacket( )
{
	if( !m_UserData && m_Packet->Code != Code::Connection )
	{
		m_UserData = USERS->AllocUser( m_PlayInfo );
#ifdef _DEBUG_MODE_
		std::cout << "Realocated[ 0x"
			<< std::hex << std::uppercase << m_UserData->GetInfo( )
			<< std::dec << std::nouppercase << " ]." << std::endl;
#endif
	};

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

				smUserInfo &User = *( smUserInfo* )m_Packet;

#ifdef _DEBUG_MODE_
				std::cout << User.ID << ": Allocated[ 0x"
					<< std::hex << std::uppercase << m_UserData->GetInfo( )
					<< std::dec << std::nouppercase << " ]." << std::endl;
#endif
			}
			break;
		case Code::SaveThrowItem2:
			{
				smThrowItem2 &ThrowItem2 = *( smThrowItem2* )m_Packet;
				PREMIUM->SetUser( m_UserData );
				PREMIUM->AddItem( &ThrowItem2 );
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
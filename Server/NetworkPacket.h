#pragma once
#include "UserInfo.h"

class CNetworkPacket
{
public:
	CNetworkPacket( const int PlayInfo, smPacket* Packet );
	
	bool VerifyPacket( );
	void DeletePacket( );
private:
	int m_PlayInfo;
	smPacket* m_Packet;
	CUserData* m_UserData;
};
#pragma once

class CNetworkPacket
{
public:
	CNetworkPacket( smPacket* Packet );
	bool VerifyPacket( );
	void DeletePacket( );
private:
	smPacket* m_Packet;
};


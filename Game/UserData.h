#pragma once

namespace HackCode
{
	enum
	{
		Exp = 0x708,
	};
};

class CUserData
{
private:
	typedef void( __cdecl* t_SendHackLog )( int HackCode, int HackInfo );
	typedef void( __thiscall *t_SendPacket ) ( DWORD, void *, DWORD, DWORD );
public:
	t_SendHackLog SendHackLog = ( t_SendHackLog )0x0063AEF0;
	t_SendPacket SendIntPacket = ( t_SendPacket )0x0046FA70;
	t_SendPacket SendStrPacket = ( t_SendPacket )0x0046FB70;
public:
	int GetLevel( ) const;
	int GetCharAddress( ) const;
	int GetPositionX( ) const;
	int GetPositionY( ) const;
	int GetPositionZ( ) const;

	void SetLevel( int Level ) const;
	void SetNextLevelExp( int Exp ) const;
	void SendInt( void* Packet ) const;
	void SendStr( void* Packet ) const;
};

extern std::shared_ptr<CUserData> lpPlayer;
#define USER lpPlayer
#pragma once

#define RED_ALERT_MESSAGE			0
#define PURPLE_WELCOME_MESSAGE		3
#define BLUE_TRADE_MESSAGE			6

#define	JOBCODE_MECHANICIAN			0
#define	JOBCODE_FIGHTER				1
#define	JOBCODE_ARCHER				2
#define	JOBCODE_PIKEMAN				3
#define	JOBCODE_ATALANTA			4
#define	JOBCODE_KNIGHT				5
#define	JOBCODE_MAGICIAN			6
#define	JOBCODE_PRIESTESS			7

#define PARTY_STATE_NONE			0
#define PARTY_STATE_LEADER			1
#define PARTY_STATE_MEMBER			2

#define PRIVILEGE_LEVEL_ADM			4
#define PRIVILEGE_LEVEL_EVENT		3
#define PRIVILEGE_LEVEL_SUPPORT		2
#define PRIVILEGE_LEVEL_VIP			1
#define PRIVILEGE_LEVEL_NONE		0

class CUserData
{
	//Conversions
public:
	operator int( ) { return m_PlayInfo; }
	int operator=( const int value ) { m_PlayInfo = value; return m_PlayInfo; };
public:
	CUserData( const int PlayInfo );

	const char* GetNick( ) const;
	const char* GetID( ) const;
	const char* GetIP( ) const;

	int GetLevel( ) const;
	int GetSocket( ) const;
	int GetInfo( ) const { return m_PlayInfo; };
	int GetField( ) const;
	int GetPartyState( ) const;
	int GetPartyMasterData( ) const;
	int GetPartyAverageLevel( ) const;
	int GetTotalPartyMembers( ) const;
	int GetPositionX( ) const;
	int GetPositionY( ) const;
	int GetPositionZ( ) const;
	int GetExpOut( ) const;

	int GetPrivilege( ) const;
	short int GetJobCode( ) const;

	void SetAddress( const int PlayInfo ) { m_PlayInfo = PlayInfo; };
	void SendInt( void* Packet ) const;
	void SendStr( void* Packet ) const;
	void SendMsg( int Type, const char* Msg, ... ) const;
	void PutItem( int ItemID ) const;
	void SetPartyState( int State ) const;
	void SetPartyMasterData( int Data ) const;
	void SetPrivilege( int PrivilegeLevel );
	void DeleteParty( );
	void AddTotalExp( int Exp );

	// Premium
	int m_ExpBoost;

private:
	int m_PlayInfo;

	//ASM Call
	typedef void( __thiscall* TSendPacket ) ( DWORD, LPVOID, DWORD, DWORD );
	TSendPacket SendIntPacket = ( TSendPacket )0x00451E80;
	TSendPacket SendStrPacket = ( TSendPacket )0x00450DF0;

	typedef void( __cdecl* TPutItem ) ( DWORD, DWORD );
	TPutItem PutItem3 = ( TPutItem )0x00552A90;
};

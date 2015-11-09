#include "stdafx.h"
#include "UserData.h"

CUserData::CUserData( const int PlayInfo )
{
	m_PlayInfo = PlayInfo;
}


const char* CUserData::GetNick( ) const
{
	return ( ( const char* )( m_PlayInfo + 0x40 ) );
}

const char* CUserData::GetID( ) const
{
	return ( ( const char* )( m_PlayInfo + 0x20 ) );
}

const char* CUserData::GetIP( ) const
{
	return ( ( const char* )( GetSocket( ) + 0x430C ) );
}


int CUserData::GetLevel( ) const
{
	return *( int* )( m_PlayInfo + 0x15C );
}

int CUserData::GetSocket( ) const
{
	return *( int* )( m_PlayInfo + 0x06DFC );
}

int CUserData::GetField( ) const
{
	return *( int* )( m_PlayInfo + 0x7C );
}

int CUserData::GetPartyState( ) const
{
	return *( int* )( m_PlayInfo + 0xAFAC );
}

int CUserData::GetPartyMasterData( ) const
{
	return *( int* )( m_PlayInfo + 0xAFB0 );
}

int CUserData::GetPartyAverageLevel( ) const
{
	return *( int* )( m_PlayInfo + 0xAFE8 );
}

int CUserData::GetTotalPartyMembers( ) const
{
	return *( int* )( m_PlayInfo + 0xAFEC );
}

int CUserData::GetPositionX( ) const
{
	return *( int* )( m_PlayInfo + 0x80 );
}

int CUserData::GetPositionY( ) const
{
	return *( int* )( m_PlayInfo + 0x84 );
}

int CUserData::GetPositionZ( ) const
{
	return *( int* )( m_PlayInfo + 0x88 );
}

int CUserData::GetExpOut( ) const
{
	return *( int* )( m_PlayInfo + 0xAF14 );
}


int CUserData::GetPrivilege( ) const
{
	return *( int * )( m_PlayInfo + 0x6E1C );
}

short int CUserData::GetJobCode( ) const
{
	return *( short int* )( m_PlayInfo + 0x158 );
}


void CUserData::SendInt( void* Packet ) const
{
	SendIntPacket( GetSocket( ), Packet, *( DWORD* )( Packet ), TRUE );
}

void CUserData::SendStr( void* Packet ) const
{
	SendStrPacket( GetSocket( ), Packet, *( DWORD* )( Packet ), TRUE );
}

void CUserData::SendMsg( int Type, const char* Msg, ... ) const
{
	smChat Chat = { 0 };
	va_list Args = { 0 };
	va_start( Args, Msg );
	Chat.Size = sizeof( smChat );
	Chat.Code = Code::WhisperMessage;
	Chat.Color = Type;
	Chat.ObjectSerial = 0;
	vsprintf_s( Chat.Message, Msg, Args );
	SendStr( &Chat );
	va_end( Args );
}

void CUserData::PutItem( int ItemID ) const
{
	PutItem3( this->m_PlayInfo, ItemID );
}

void CUserData::SetPartyState( int State ) const
{
	*( int* )( m_PlayInfo + 0xAFAC ) = State;
}

void CUserData::SetPartyMasterData( int Data ) const
{
	*( int* )( m_PlayInfo + 0xAFB0 ) = Data;
}

void CUserData::SetExpOut( int ExpOut ) const
{
	*( int* )( m_PlayInfo + 0xAF14 ) = ExpOut;
}

void CUserData::SetPrivilege( int PrivilegeLevel )
{
	*( int * )( m_PlayInfo + 0x6E1C ) = PrivilegeLevel;
}
#include "stdafx.h"
#include "UserData.h"

#define USER_DATA *( int* )( 0x00D22894 )

std::shared_ptr<CUserData> lpPlayer = std::make_shared<CUserData>( );

int CUserData::GetLevel( ) const
{
	return *( int* )( USER_DATA + 0x39DC );
}

int CUserData::GetCharAddress( ) const
{
	return USER_DATA + 0x3924;
}

int CUserData::GetPositionX( ) const
{
	return *( int* )( USER_DATA + 0x1E0 );
}

int CUserData::GetPositionY( ) const
{
	return *( int* )( USER_DATA + 0x1E4 );
}

int CUserData::GetPositionZ( ) const
{
	return *( int* )( USER_DATA + 0x1E8 );
}


void CUserData::SetLevel( int Level ) const
{
	*( int* )( USER_DATA + 0x39DC ) = Level;
}

void CUserData::SetNextLevelExp( int Exp ) const
{
	*( int* )( USER_DATA + 0x3A64 ) = Exp;
}

void CUserData::SendInt( void* Packet ) const
{
	DWORD Sock = *( DWORD* )0x03AD1F88;
	if( !Sock ) Sock = *( DWORD* )0x03AD1F8C;

	SendIntPacket( Sock, Packet, *( DWORD* )Packet, TRUE );
}

void CUserData::SendStr( void* Packet ) const
{
	DWORD Sock = *( DWORD* )0x03AD1F88;
	if( !Sock ) Sock = *( DWORD* )0x03AD1F8C;

	SendStrPacket( Sock, Packet, *( int* )Packet, TRUE );
}
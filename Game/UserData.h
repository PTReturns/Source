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
public:
	t_SendHackLog SendHackLog = ( t_SendHackLog )0x0063AEF0;
public:
	int GetLevel( ) const;
	int GetCharAddress( ) const;
	int GetPositionX( ) const;
	int GetPositionY( ) const;
	int GetPositionZ( ) const;

	void SetLevel( int Level ) const;
	void SetNextLevelExp( int Exp ) const;
};

extern std::shared_ptr<CUserData> lpPlayer;
#define USER lpPlayer
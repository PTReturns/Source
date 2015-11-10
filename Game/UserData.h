#pragma once

class CUserData
{
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
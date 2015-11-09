#pragma once

namespace FieldEnvironment
{
	enum
	{
		City = 0x100,
		Forest = 0x200,
		Desert = 0x300,
		Ruins = 0x400,
		Dungeon = 0x500,
		Iron = 0x600,
		Invalid = 0x700,
		Office = 0x800,
		Ice = 0x900,
		Castle = 0xA00,
		MiniGame = 0xB00
	};
};

class CFieldTable
{
public:
	void BuildFields( );
	int GetEnvironmentFromString( const char* String );
};


#pragma once

struct smItemTable
{
	int 	ID;
	char	Name[ 32 ];
	char	Code1[ 16 ];
	int		Width;
	int     Height;
	char	FilePath[ 64 ];
	int 	Class;
	char    Code2[ 64 ];
	int     InventoryPos;
	int		SoundIndex;
	int     WeaponClass;
	char	InvalidParams[ 584 ];
};

extern smItemTable Items[ ITEM_QUANTITY + 1 ];

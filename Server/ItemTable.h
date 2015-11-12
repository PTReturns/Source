#pragma once

#define BI 0x080B0000

#define Item01 0x100
#define Item02 0x200
#define Item03 0x300
#define Item04 0x400
#define Item05 0x500
#define Item06 0x600
#define Item07 0x700
#define Item08 0x800
#define Item09 0x900
#define Item10 0xA00
#define Item11 0xB00
#define Item12 0xC00
#define Item13 0xD00

class CItemTable
{
public:
	CItemTable( );
	void CreateItem( const int ID, const char* Code1, const char* Code2, const int Width,
					 const int Height, const char* Folder, const int HoldMode, const int CityType,
					 const int Sound, const int Range, const int Unknown );
	void BuildItems( );
	void ReferenceItems( );
	int GetID( const char* Code );
	const char* GetCode( int ID );

private:
	int m_ItemTable;
	int m_ItemCount;
};

extern std::shared_ptr<CItemTable> pItemTable;
#define ITEMTABLE pItemTable
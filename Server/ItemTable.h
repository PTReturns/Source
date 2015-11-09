#pragma once

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
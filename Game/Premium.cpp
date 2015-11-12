#include "stdafx.h"
#include "Premium.h"

#include "UserData.h"

std::shared_ptr<CPremium> pPremium = std::make_shared<CPremium>( );
std::vector<smPremiumItem*> PremiumItems;

bool TimerCount = false;

void CPremium::AddItem( smPremiumItem* PremiumItem )
{
	smPremiumItem* Premium = new smPremiumItem( );
	memcpy_s( Premium, sizeof( smPremiumItem ), PremiumItem, sizeof( smPremiumItem ) );

	PremiumItems.push_back( Premium );

#ifdef _DEBUG_MODE_
	std::cout << "Item: 0x"
		<< std::hex << std::uppercase << Premium->ItemID << std::nouppercase << std::dec
		<< " added on TimerCount." << std::endl;
#endif
}

void CPremium::UpdateItems( )
{
	for( auto &Item : PremiumItems )
	{
		if( Item )
		{
			Item->ElapsedTime++;
#ifdef _DEBUG_MODE_
			std::cout << "Item: 0x"
				<< std::hex << std::uppercase << Item->ItemID << std::nouppercase << std::dec
				<< " [ " << Item->DurationTime - Item->ElapsedTime << " ]." << std::endl;
#endif
		};
	};
}

void CPremium::CheckTimes( )
{
	int i = 0;
	for( auto &Item : PremiumItems )
	{
		if( Item )
		{
			if( Item->ElapsedTime >= Item->DurationTime )
			{
#ifdef _DEBUG_MODE_
				std::cout << "Item: 0x"
					<< std::hex << std::uppercase << Item->ItemID << std::nouppercase << std::dec
					<< " expired." << std::endl;
#endif

				USER->SendInt( Item );

				delete Item;
				PremiumItems.erase( PremiumItems.begin( ) + i );
			};
		};
		i++;
	};
}

void __stdcall CheckPremiums( HWND hWnd, UINT Message, UINT_PTR ID, DWORD Time )
{
	pPremium->UpdateItems( );
	pPremium->CheckTimes( );
};

void CPremiumUI::ShowPremium( smPremiumItem* Item )
{
	switch( Item->ItemID )
	{
		case 0x080B0D00:
			{
				SetType( ( int* )0x03604EF8, 9 );
				ShowImg( ( int* )0x03604EF8, 2, ( Item->DurationTime - Item->ElapsedTime ),
						 TRUE, "Ravelzando 30%", 30, 0, 0, 0, 0 );
			}
			break;
	};
}
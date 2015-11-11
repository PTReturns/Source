#include "stdafx.h"
#include "Premium.h"

std::shared_ptr<CPremium> pPremium = std::make_shared<CPremium>( );
std::vector<smExpireTime*> PremiumItems;

bool TimerCount = false;

void CPremium::AddItem( smExpireTime* PremiumItem )
{
	smExpireTime* Premium = new smExpireTime( );
	memcpy_s( Premium, sizeof( smExpireTime ), PremiumItem, sizeof( smExpireTime ) );

	PremiumItems.push_back( Premium );

#ifdef _DEBUG_MODE_
	std::cout << "Item: 0x"
		<< std::hex << std::uppercase << Premium->ItemCode << std::nouppercase << std::dec
		<< " added on TimerCount." << std::endl;
#endif
}

void CPremium::UpdateItems( )
{
	for( auto &Item : PremiumItems )
	{
		if( Item )
		{
			Item->TotalSeconds--;
#ifdef _DEBUG_MODE_
			std::cout << "Item: 0x"
				<< std::hex << std::uppercase << Item->ItemCode << std::nouppercase << std::dec
				<< " [ " << Item->TotalSeconds << " ]." << std::endl;
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
			if( Item->TotalSeconds <= 0 )
			{
#ifdef _DEBUG_MODE_
				std::cout << "Item: 0x"
					<< std::hex << std::uppercase << Item->ItemCode << std::nouppercase << std::dec
					<< " expired." << std::endl;
#endif
				delete Item;
				PremiumItems.erase( PremiumItems.begin( ) + i );
				//DeleteItem
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
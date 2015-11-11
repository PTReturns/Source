#include "stdafx.h"
#include "Premium.h"

std::shared_ptr<CPremium> pPremium = std::make_shared<CPremium>( );
std::vector<smExpireTime*> PremiumItems;

bool ThreadMode = false;

void CPremium::AddItem( smExpireTime* PremiumItem )
{
	PremiumItems.push_back( PremiumItem );

#ifdef _DEBUG_MODE_
	std::cout << "Item: 0x"
		<< std::hex << std::uppercase << PremiumItem->ItemCode << std::nouppercase << std::dec
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

DWORD WINAPI CheckPremiuns( LPVOID Item )
{
	DWORD CurrentTime = CURRENT_TIME;
	DWORD Time = CurrentTime;
	ThreadMode = true;

	if( Item )
		pPremium->AddItem( ( smExpireTime* )Item );

	while( true )
	{
		if( CurrentTime != CURRENT_TIME )
		{
			CurrentTime = CURRENT_TIME;

			pPremium->UpdateItems( );
		};

		if( Time + 60 <= CurrentTime )
		{
			pPremium->CheckTimes( );
		};
	};

	return 0;
}
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
}

void CPremium::UpdateItems( )
{
	for( auto &Item : PremiumItems )
	{
		if( Item )
		{
			Item->Duration--;
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
			if( Item->Duration <= 0 )
			{
				delete Item;
				PremiumItems.erase( PremiumItems.begin( ) + i );
			};
		};
		i++;
	};
}

void __stdcall CheckPremiums( HWND hWnd, UINT Message, UINT_PTR ID, DWORD Time )
{
	PREMIUM->UpdateItems( );
	PREMIUM->CheckTimes( );
};
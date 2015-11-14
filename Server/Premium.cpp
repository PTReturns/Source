#include "stdafx.h"
#include "Premium.h"
#include "SQLApi.h"

#include "ItemTable.h"

std::shared_ptr<CPremium> pPremium = std::make_shared<CPremium>( );

void CPremium::SetUser( CUserData* User )
{
	m_User = User;
}

void CPremium::AddItem( smPremiumItem* Item )
{
	if( m_User && Item )
	{
		Item->Size = sizeof( smPremiumItem );

#ifdef _DEBUG_MODE_
		std::cout << "AddItem: [ " << Item->Duration << " ]." << std::endl;
#endif

		m_User->SendInt( Item );
		UpdateCharEffects( Item );
	};
}

void CPremium::AddItem( smThrowItem2* Item )
{
	if( m_User && Item )
	{
		int CheckSum = Item->PremiumCheckSum ^ Item->ItemCheckSum ^ Item->Code;
		if( ( Item->ItemID & 0xFFFF0000 ) >= 0x080B0000 && ( Item->ItemID & 0xFFFF0000 ) <= 0x080C0000 )
		{
			bool isPremium = true;
			smPremiumItem PremiumItem = { 0 };
			PremiumItem.Size = sizeof( smPremiumItem );
			PremiumItem.Code = Code::SendPremiumItem;

			if( CheckSum == POTION_EXPUP )
			{
				switch( Item->ItemID )
				{
					case BI | Item13:
						{
							PremiumItem.ItemID = BI | Item13;
							PremiumItem.Duration = 1 * MINUTE;
						}
						break;

					default:
						isPremium = false;
						break;
				};
			};

			if( isPremium )
			{
				m_User->SendInt( &PremiumItem );
				UpdateCharEffects( &PremiumItem );
				SQL->Execute( "INSERT INTO ServerDB.dbo.Premiuns "
							  "VALUES( '%s', '%s', %d, %d )", m_User->GetID( ), m_User->GetNick( ),
							  PremiumItem.ItemID, PremiumItem.Duration );
			};

		};
	};
}

void CPremium::SavePremiums( int ElapsedTime )
{
	m_User->m_LastSaveTime = CURRENT_TIME;

	if( !m_User ) return;
	if( !m_User->m_PremiumCount ) return;
	SQLBuffer UserPremiums;
	if( !SQL->Select( UserPremiums, "SELECT * FROM ServerDB.dbo.Premiuns WHERE ID = '%s' and Nick = '%s'",
		m_User->GetID( ), m_User->GetNick( ) ) ) return;

	smPremiumItem* PremiumItem = new smPremiumItem( );
	for( unsigned int i = 0; i < UserPremiums.size( ); i++ )
	{
		PremiumItem->ItemID = atoi( UserPremiums[ i ][ 2 ].c_str( ) );
		PremiumItem->Duration = atoi( UserPremiums[ i ][ 3 ].c_str( ) );
		PremiumItem->Duration -= ElapsedTime;
		if( PremiumItem->Duration <= 0 )
		{
			RemovePremium( PremiumItem );
		}
		else
		{
			SQL->Execute( "UPDATE ServerDB.dbo.Premiuns SET Duration = %d WHERE ID = '%s' AND Nick = '%s' AND ItemID = %d",
						  PremiumItem->Duration, m_User->GetID( ), m_User->GetNick( ), PremiumItem->ItemID );
		};
	};
	delete PremiumItem;
}

void CPremium::LoadPremiums( )
{
	if( !m_User ) return;

	SQLBuffer CharPremiuns;
	if( SQL->Select( CharPremiuns, "SELECT * FROM ServerDB.dbo.Premiuns WHERE ID = '%s' AND Nick = '%s'",
		m_User->GetID( ), m_User->GetNick( ) ) )
	{
		smPremiumItem* PremiumItem = new smPremiumItem( );
		PremiumItem->Size = sizeof( smPremiumItem );
		PremiumItem->Code = Code::LoadPremiumItem;
		for( unsigned int i = 0; i < CharPremiuns.size( ); i++ )
		{
			PremiumItem->ItemID = atoi( CharPremiuns[ i ][ 2 ].c_str( ) );
			PremiumItem->Duration = atoi( CharPremiuns[ i ][ 3 ].c_str( ) );
			AddItem( PremiumItem );
		};
		m_User->m_LastSaveTime = CURRENT_TIME;
		delete PremiumItem;
	};
}

void CPremium::RemovePremium( smPremiumItem* Item )
{
	if( !m_User || !Item ) return;

#ifdef _DEBUG_MODE_
	std::cout << "RemovePremium: [ " << Item->Duration << " ]." << std::endl;
#endif

	if( SQL->Execute( "DELETE FROM ServerDB.dbo.Premiuns WHERE ID = '%s' AND Nick = '%s' AND ItemID = %d",
		m_User->GetID( ), m_User->GetNick( ), Item->ItemID ) )
	{
		UpdateCharEffects( Item );
	};
}

void CPremium::UpdateCharEffects( smPremiumItem* Item )
{
	if( Item )
	{

#ifdef _DEBUG_MODE_
		std::cout << "UpdateCharEffects: [ " << Item->Duration << " ]." << std::endl;
#endif

		if( Item->Duration <= 0 )
			m_User->m_PremiumCount--;
		else
			m_User->m_PremiumCount++;

		switch( Item->ItemID )
		{
			case BI | Item13:
				{
					if( Item->Duration <= 0 )
						m_User->m_ExpBoost -= EXP_BOOST_30;
					else
						m_User->m_ExpBoost += EXP_BOOST_30;
				}
				break;
			default:
				if( Item->Duration <= 0 )
					m_User->m_PremiumCount++;
				else
					m_User->m_PremiumCount--;
				break;
		};

	};
}
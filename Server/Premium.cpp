#include "stdafx.h"
#include "Premium.h"
#include "SQLApi.h"

#include "ItemTable.h"


CPremium::CPremium( smThrowItem2* PremiumItem, CUserData* User )
{
	m_ThrowItem = PremiumItem;
	m_User = User;
	m_PremiumItem = nullptr;
}

CPremium::CPremium( smPremiumItem* PremiumItem, CUserData* User )
{
	m_ThrowItem = nullptr;
	m_User = User;
	m_PremiumItem = PremiumItem;
}

CPremium::CPremium( CUserData* User )
{
	m_User = User;
	m_ThrowItem = nullptr;
	m_PremiumItem = nullptr;
}

void CPremium::System( )
{
	if( !m_ThrowItem ) return;

	int CheckSum = m_ThrowItem->PremiumCheckSum ^ m_ThrowItem->ItemCheckSum ^ m_ThrowItem->Code;
	if( ( m_ThrowItem->ItemID & 0xFFFF0000 ) >= 0x080B0000 && ( m_ThrowItem->ItemID & 0xFFFF0000 ) <= 0x080C0000 )
	{
		if( CheckSum == EXPUP_CHECKSUM )
		{
			switch( m_ThrowItem->ItemID )
			{
				case ItemCode::ExpUp1M:
					{
						if( SQL->Execute( "INSERT INTO ServerDB.dbo.Premiuns "
							"VALUES( '%s', '%s', %d, %d, %d )", m_User->GetID( ), m_User->GetNick( ),
							m_ThrowItem->ItemID, ( 1 * MINUTE ), NULL ) )
						{
							smPremiumItem PremiumItem = { 0 };
							PremiumItem.Size = sizeof( smPremiumItem );
							PremiumItem.Code = Code::SendPremiumItem;
							PremiumItem.ItemID = m_ThrowItem->ItemID;
							PremiumItem.DurationTime = ( 1 * MINUTE );
							PremiumItem.ElapsedTime = 0;

							m_User->SendInt( &PremiumItem );
							m_User->m_ExpBoost += EXPUP_POTION_30;
						};
					}
					break;
			};
		};
		m_User->m_LastSaveGameTime = CURRENT_TIME;
	};
}

void CPremium::CheckRemovedPremium( )
{
	if( !m_PremiumItem ) return;

	m_User->m_PremiumCount--;

	switch( m_PremiumItem->ItemID )
	{
		case ItemCode::ExpUp1M:
			{
				m_User->m_ExpBoost -= EXPUP_POTION_30;
			}
			break;
	};
}

void CPremium::CheckLoadedPremium( )
{
	if( !m_PremiumItem ) return;

	m_User->m_PremiumCount++;

	switch( m_PremiumItem->ItemID )
	{
		case ItemCode::ExpUp1M:
			{
				m_User->m_ExpBoost += EXPUP_POTION_30;
			}
			break;
	};
}

void CPremium::DeletePremium( )
{
	if( !m_PremiumItem ) return;

	if( m_PremiumItem->ElapsedTime == m_PremiumItem->DurationTime )
	{
		SQLBuffer PremiumInfo;
		if( SQL->Select( PremiumInfo, "SELECT * FROM ServerDB.dbo.Premiuns WHERE ID = '%s' AND Nick = '%s' AND ItemID = %d",
			m_User->GetID( ), m_User->GetNick( ), m_PremiumItem->ItemID ) )
		{
			if( m_PremiumItem->ElapsedTime >= atoi( PremiumInfo[ 0 ][ 3 ].c_str( ) ) )
			{
				if( SQL->Execute( "DELETE FROM ServerDB.dbo.Premiuns WHERE ID = '%s' AND Nick = '%s' AND ItemID = %d",
					m_User->GetID( ), m_User->GetNick( ), m_PremiumItem->ItemID ) )
					CheckRemovedPremium( );
			}
			else
			{
#ifdef _DEBUG_MODE_
				std::cout << m_User->GetNick( ) << ": Banned[ PREMIUM TIME HACK ]" << std::endl;
#endif
			};
		};
	};
}

void CPremium::SavePremium( )
{
	SQLBuffer PremiumTime;
	if( m_User->m_PremiumCount && 
		SQL->Select( PremiumTime, "SELECT * FROM ServerDB.dbo.Premiuns WHERE ID = '%s' and Nick = '%s'",
		m_User->GetID( ), m_User->GetNick( ) ) )
	{
		for( unsigned int i = 0; i < PremiumTime.size( ); i++ )
		{
			int ID = atoi( PremiumTime[ i ][ 2 ].c_str( ) );
			int Duration = atoi( PremiumTime[ i ][ 3 ].c_str( ) );
			int Elapsed = atoi( PremiumTime[ i ][ 4 ].c_str( ) ) + 1;
			if( Duration <= Elapsed )
			{
				smPremiumItem PremiumItem = { 0 };
				PremiumItem.Size = sizeof( smPremiumItem );
				PremiumItem.Code = Code::DeletePremiumItem;
				PremiumItem.ItemID = ID;
				PremiumItem.DurationTime = Duration;
				PremiumItem.ElapsedTime = Elapsed;
				m_PremiumItem = &PremiumItem;
				DeletePremium( );
			}
			else
			{
				SQL->Execute( "UPDATE ServerDB.dbo.Premiuns SET ElapsedTime = %d WHERE ID = '%s' AND Nick = '%s' AND ItemID = %d",
							  Elapsed, m_User->GetID( ), m_User->GetNick( ), ID );
			};
		};
	};
}

void CPremium::LoadPremium( )
{
	SQLBuffer CharItems;
	if( SQL->Select( CharItems, "SELECT * FROM ServerDB.dbo.Premiuns WHERE ID = '%s' AND Nick = '%s'",
		m_User->GetID( ), m_User->GetNick( ) ) )
	{
		for( unsigned int i = 0; i < CharItems.size( ); i++ )
		{
			smPremiumItem PremiumItem = { 0 };
			PremiumItem.Size = sizeof( PremiumItem );
			PremiumItem.Code = Code::LoadPremiumItem;
			PremiumItem.ItemID = atoi( CharItems[ i ][ 2 ].c_str( ) );
			PremiumItem.DurationTime = atoi( CharItems[ i ][ 3 ].c_str( ) );
			PremiumItem.ElapsedTime = atoi( CharItems[ i ][ 4 ].c_str( ) );

			m_User->SendInt( &PremiumItem );

			m_PremiumItem = &PremiumItem;

			CheckLoadedPremium( );
		};
		m_User->m_LastSaveGameTime = CURRENT_TIME;
	};
}
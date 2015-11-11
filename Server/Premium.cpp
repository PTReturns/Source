#include "stdafx.h"
#include "Premium.h"
#include "SQLApi.h"

CPremium::CPremium( smThrowItem2* PremiumItem, CUserData* User )
{
	m_Premium = PremiumItem;
	m_User = User;
}

void CPremium::System( )
{
	int CheckSum = m_Premium->PremiumCheckSum ^ m_Premium->ItemCheckSum ^ m_Premium->Code;
	if( ( m_Premium->ItemCode & 0xFFFF0000 ) >= 0x080B0000 && ( m_Premium->ItemCode & 0xFFFF0000 ) <= 0x080C0000 )
	{
		if( CheckSum == EXPUP_CHECKSUM )
		{
			switch( m_Premium->ItemCode )
			{
				case ItemCode::ExpUp1M:
					{
						DWORD ExpireTime = CURRENT_TIME + ( 1 * MINUTE );
						if( SQL->Execute( "INSERT INTO ServerDB.dbo.Premiuns "
										  "VALUES( '%s', '%s', %d, %d, %d, %d )",
										  m_User->GetID( ), m_User->GetNick( ), 
										  m_Premium->ItemCode, CURRENT_TIME, ExpireTime, ( 1 * MINUTE ) ) )
						{
							m_User->m_ExpBoost += EXPUP_POTION_30;

							smExpireTime PremiumItem = { 0 };
							PremiumItem.Size = sizeof( smExpireTime );
							PremiumItem.Code = Code::SendPremiumItem;
							PremiumItem.ItemCode = m_Premium->ItemCode;
							PremiumItem.TotalSeconds = ( 1 * MINUTE );
						};
					}
					break;
			};
		};
	};
}
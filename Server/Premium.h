#pragma once
#include "UserData.h"

//CONFIGURAÇÕES DO USUÁRIO
#define EXPUP_POTION_30 30


#define EXPUP_CHECKSUM 300

#define MINUTE	(          60 )
#define HOUR	( MINUTE * 60 )
#define DAY		( HOUR	 * 24 )
#define WEEK	( DAY	 * 7  )
#define MONTH	( WEEK	 * 30 )

namespace ItemCode
{
	enum
	{
		ExpUp1M = 0x080B0D00,
	};
};


class CPremium
{
public:
	CPremium( smThrowItem2* PremiumItem, CUserData* User );
	CPremium( smPremiumItem* PremiumItem, CUserData* User );
	CPremium( CUserData* User );

	void CheckLoadedPremium( );
	void CheckRemovedPremium( );
	void DeletePremium( );
	void System( );
	void SavePremium( );
	void LoadPremium( );
private:
	CUserData* m_User;
	smThrowItem2* m_ThrowItem;
	smPremiumItem* m_PremiumItem;
};


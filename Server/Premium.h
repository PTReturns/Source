#pragma once
#include "UserData.h"

//CONFIGURAÇÕES DO USUÁRIO
#define EXP_BOOST_10 10
#define EXP_BOOST_20 20
#define EXP_BOOST_30 30
#define EXP_BOOST_40 40
#define EXP_BOOST_50 50


#define POTION_EXPUP 300

#define MINUTE	(          60 )
#define HOUR	( MINUTE * 60 )
#define DAY		( HOUR	 * 24 )
#define WEEK	( DAY	 * 7  )
#define MONTH	( WEEK	 * 30 )


class CPremium
{
public:
	CPremium( ) { m_User = 0; InitializeCriticalSection( &m_SaveSection ); };
	~CPremium( ) { DeleteCriticalSection( &m_SaveSection ); };

	void SetUser( CUserData* User );

	void AddItem( smPremiumItem* Item );
	void AddItem( smThrowItem2* Item );
	void SavePremiums( int ElapsedTime = 1 );
	void LoadPremiums( );
	void RemovePremium( smPremiumItem* Item );
	void UpdateCharEffects( smPremiumItem* Item );
private:
	CUserData* m_User;
	CRITICAL_SECTION m_SaveSection;
};

extern std::shared_ptr<CPremium> pPremium;
#define PREMIUM pPremium
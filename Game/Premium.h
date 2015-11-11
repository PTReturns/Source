#pragma once

#define MINUTE	(          60 )
#define HOUR	( MINUTE * 60 )
#define DAY		( HOUR	 * 24 )
#define WEEK	( DAY	 * 7  )
#define MONTH	( WEEK	 * 30 )

class CPremium
{
public:
	void AddItem( smExpireTime* PremiumItem );
	void UpdateItems( );
	void CheckTimes( );
private:
	smExpireTime* m_ExpireItem;
};


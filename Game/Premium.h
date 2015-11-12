#pragma once

#define MINUTE	(          60 )
#define HOUR	( MINUTE * 60 )
#define DAY		( HOUR	 * 24 )
#define WEEK	( DAY	 * 7  )
#define MONTH	( WEEK	 * 30 )

class CPremium
{
public:
	void AddItem( smPremiumItem* PremiumItem );
	void UpdateItems( );
	void CheckTimes( );
private:
	smPremiumItem* m_ExpireItem;
};

class CPremiumUI
{
private:
	typedef void( __thiscall *t_SetType ) ( int*, int );
	typedef void( __thiscall *t_ShowImg ) ( int*, int, int Time, int Show, char* Text, int Boost, int, int, int, int );
public:
	t_SetType SetType = ( t_SetType )0x00497B10;
	t_ShowImg ShowImg = ( t_ShowImg )0x004956A0;
public:
	void ShowPremium( smPremiumItem* Item );
private:
};
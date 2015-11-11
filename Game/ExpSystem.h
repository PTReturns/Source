#pragma once

class CExpSystem
{
private:
	typedef __int64( __cdecl* t_XorExp ) ( );
	typedef void( __cdecl* t_SetExp ) ( int, __int64 );
	typedef void( __cdecl* t_ReformChar )( );
	typedef void( __cdecl* t_StartEffect )( int, int, int, int, int );
	typedef void( __cdecl* t_PlaySound )( int, int );
	typedef void( __cdecl* t_SendPlayerUpdateInfo )( );
	typedef void( __cdecl* t_SaveGame )( );
	typedef int( __cdecl* t_GetMonsterInfo ) ( int );
	typedef void( __cdecl* t_AddChatMsg )( const char*, int );
	typedef void( __cdecl* t_CheckQuest1 )( int );
	typedef void( __thiscall* t_CheckQuest2 )( int*, int );
	typedef void( __cdecl* t_CheckPartyQuest1 )( int );
	typedef void( __thiscall* t_CheckPartyQuest2 )( int*, int );
public:
	t_XorExp XorExp = ( t_XorExp )0x0045AFE0;
	t_SetExp SetExp = ( t_SetExp )0x0045B190;
	t_ReformChar ReformChar = ( t_ReformChar )0x0045D430;
	t_StartEffect StartEffect = ( t_StartEffect )0x00587240;
	t_PlaySound PlaySound = ( t_PlaySound )0x0054BE80;
	t_SendPlayerUpdateInfo SendPlayerInfo = ( t_SendPlayerUpdateInfo )0x00636B20;
	t_SaveGame SaveGame = ( t_SaveGame )0x00636770;
	t_GetMonsterInfo GetMonsterInfo = ( t_GetMonsterInfo )0x0062D820;
	t_AddChatMsg AddChatMsg = ( t_AddChatMsg )0x0062DEB0;
	t_CheckQuest1 CheckQuest1 = ( t_CheckQuest1 )0x004DFB10;
	t_CheckQuest2 CheckQuest2 = ( t_CheckQuest2 )0x0048F930;
	t_CheckPartyQuest1 CheckPartyQuest1 = ( t_CheckPartyQuest1 )0x00636110;
	t_CheckPartyQuest2 CheckPartyQuest2 = ( t_CheckPartyQuest2 )0x0048F930;

public:
	CExpSystem( );
	CExpSystem( smEarnExp* Exp );
	void System( );
	void AddExp( INT64 Exp );
	void LevelUp( int CharLevel );
private:
	smEarnExp* m_Exp;
};


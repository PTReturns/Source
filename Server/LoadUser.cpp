#include "stdafx.h"
#include "LoadUser.h"
#include "SQLApi.h"
#include "ItemTable.h"
#include "Premium.h"

CLoadUser::CLoadUser( CUserData* User )
{
	m_User = User;
}

void CLoadUser::LoadChar( )
{
	if( !m_User ) return;
	SQLBuffer Char;
	if( !SQL->Select( Char, "SELECT * FROM ServerDB.dbo.Users WHERE ID = '%s' AND Nick = '%s'",
		m_User->GetID( ), m_User->GetNick( ) ) )
		SendGift( );

	PREMIUM->SetUser( m_User );
	PREMIUM->LoadPremiums( );

	SendWelcome( );
}

void CLoadUser::SendWelcome( )
{
	smChat Welcome = { 0 };
	Welcome.Code = Code::WhisperMessage;
	Welcome.Size = sizeof( smChat );
	Welcome.Color = PURPLE_WELCOME_MESSAGE;
	Welcome.ObjectSerial = NULL;
	sprintf_s( Welcome.Message, "Bem Vindo ao Priston Tale - Returns." );
	m_User->SendStr( &Welcome );
}

void CLoadUser::SendGift( )
{
	if( SQL->Execute( "INSERT INTO ServerDB.dbo.Users VALUES( '%s', '%s', 'True' )", m_User->GetID( ), m_User->GetNick( ) ) )
	{
		switch( m_User->GetJobCode( ) )
		{
			case JOBCODE_MECHANICIAN:
				m_User->PutItem( ITEMTABLE->GetID( "WC103" ) );
				m_User->PutItem( ITEMTABLE->GetID( "DS103" ) );
				break;
			case JOBCODE_FIGHTER:
				m_User->PutItem( ITEMTABLE->GetID( "WA103" ) );
				break;
			case JOBCODE_PIKEMAN:
				m_User->PutItem( ITEMTABLE->GetID( "WP103" ) );
				break;
			case JOBCODE_ARCHER:
				m_User->PutItem( ITEMTABLE->GetID( "WS103" ) );
				break;
			case JOBCODE_ATALANTA:
				m_User->PutItem( ITEMTABLE->GetID( "WT103" ) );
				break;
			case JOBCODE_KNIGHT:
				m_User->PutItem( ITEMTABLE->GetID( "WS203" ) );
				break;
			case JOBCODE_MAGICIAN:
			case JOBCODE_PRIESTESS:
				m_User->PutItem( ITEMTABLE->GetID( "WM103" ) );
				m_User->PutItem( ITEMTABLE->GetID( "DA204" ) );
				break;
		};

		if( m_User->GetJobCode( ) <= JOBCODE_KNIGHT )
		{
			m_User->PutItem( ITEMTABLE->GetID( "DA104" ) );
		};

		m_User->PutItem( ITEMTABLE->GetID( "OS103" ) );
		m_User->PutItem( ITEMTABLE->GetID( "OR103" ) );
		m_User->PutItem( ITEMTABLE->GetID( "OR103" ) );
		m_User->PutItem( ITEMTABLE->GetID( "OA203" ) );
		m_User->PutItem( ITEMTABLE->GetID( "DG103" ) );
		m_User->PutItem( ITEMTABLE->GetID( "DB103" ) );
	};
}

void Load_User( int PlayInfo )
{
	CLoadUser* pUser = new CLoadUser( USERS->GetData( PlayInfo ) );
	pUser->LoadChar( );
	delete pUser;
}
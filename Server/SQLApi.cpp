#include "stdafx.h"
#include "SQLApi.h"
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

std::shared_ptr<CSQLApi> pSql = std::make_shared<CSQLApi>( );

CSQLApi::CSQLApi( )
{
	char ConnectionString[ 256 ] = { 0 };
	sprintf_s( ConnectionString, "DRIVER={SQL Server};SERVER=%s;UID=%s;PWD=%s;",
			   SQL_INST, SQL_USER, SQL_PASS );
	SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_Environment );
	SQLSetEnvAttr( m_Environment, SQL_ATTR_ODBC_VERSION, ( SQLPOINTER )SQL_OV_ODBC3, 0 );
	SQLAllocHandle( SQL_HANDLE_DBC, m_Environment, &m_Connection );
	SQLDriverConnectA( m_Connection, NULL, ( SQLCHAR* )( ConnectionString ),
					   SQL_NTS, NULL, NULL, NULL, SQL_DRIVER_NOPROMPT );
}

CSQLApi::~CSQLApi( )
{
	if( m_Connection )
		SQLDisconnect( m_Connection );
	if( m_Environment )
		SQLFreeEnv( m_Environment );
	if( m_Statement )
		SQLFreeStmt( m_Statement, SQL_CLOSE );
}

bool CSQLApi::Select( SQLBuffer& Buffer, const char* Query, ... )
{
	SecureZeroMemory( m_Buffer, sizeof( m_Buffer ) );
	va_list pArgs = { 0 };
	va_start( pArgs, Query );
	std::string strBuffer = "";
	strBuffer.resize( 200 );
	short int nColumn = 0;
	m_Statement = nullptr;

	vsprintf_s( m_Buffer, Query, pArgs );
	SQLAllocHandle( SQL_HANDLE_STMT, m_Connection, &m_Statement );
	SQLExecDirectA( m_Statement, ( SQLCHAR* )m_Buffer, SQL_NTS );
	SQLNumResultCols( m_Statement, &nColumn );

	int j = 0;
	while( SQLFetch( m_Statement ) == SQL_SUCCESS )
	{
		Buffer.resize( j + 1 );
		for( short int i = 1; i <= nColumn; i++ )
		{
			SQLGetData( m_Statement, i, SQL_C_CHAR, ( SQLPOINTER )( strBuffer.c_str( ) ), 200, nullptr );
			Buffer[ j ].resize( i );
			Buffer[ j ][ i - 1 ] = strBuffer;
		};
		j++;
	};
	SQLFreeHandle( SQL_HANDLE_STMT, m_Statement );
	va_end( pArgs );
	if( j )
		return true;
	else
	{
		return false;
	};
}

bool CSQLApi::Execute( const char* Query, ... )
{
	SecureZeroMemory( m_Buffer, sizeof( m_Buffer ) );
	va_list pArgs = { 0 };
	va_start( pArgs, Query );
	m_Statement = nullptr;

	vsprintf_s( m_Buffer, Query, pArgs );
	SQLAllocHandle( SQL_HANDLE_STMT, m_Connection, &m_Statement );
	SQLExecDirectA( m_Statement, ( SQLCHAR* )m_Buffer, SQL_NTS );
	SQLFreeHandle( SQL_HANDLE_STMT, m_Statement );

	va_end( pArgs );
	return true;
}
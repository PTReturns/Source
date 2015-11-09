#pragma once

typedef std::vector<std::vector<std::string>> SQLBuffer;

class CSQLApi
{
public:
	bool Select( SQLBuffer& Buffer, const char* Query, ... );
	bool Execute( const char* Query, ... );
	CSQLApi( );
	~CSQLApi( );
private:
	LPVOID m_Environment, m_Connection, m_Statement;
	char m_Buffer[ 1024 ];
};

extern std::shared_ptr<CSQLApi> pSql;
#define SQL pSql
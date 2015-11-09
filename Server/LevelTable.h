#pragma once

extern std::vector<INT64> Levels;

class CLevelTable
{
public:
	CLevelTable( );

	void ReferenceLevel( );
};

extern std::shared_ptr<CLevelTable> pLevelTable;
#define LEVELTABLE pLevelTable
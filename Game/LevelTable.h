#pragma once

extern std::vector<INT64> Levels;

class CLevelTable
{
public:
	CLevelTable( int LevelCap, float LevelMultipler, int LevelBase );

	void ReferenceLevel( );
private:
	int m_LevelCap;
	float m_LevelMultiplier;
	int m_LevelBase;
};
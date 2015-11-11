#pragma once

class CSkillTranslate
{
public:
	CSkillTranslate( );

	void SetTranslations( );

	void Name( std::string Name );
	void Description( std::string Description );
private:
	DWORD m_VP;
	DWORD m_Address;
	DWORD m_SpaceCount;
};

class CTranslate : public CSkillTranslate
{
public:
	CTranslate( );

	void SetTranslations( );

	void Translate( DWORD Offset, std::string Text );
private:
	DWORD m_Address;
	DWORD m_SpaceCount;
};
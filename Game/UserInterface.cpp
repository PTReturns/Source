#include "stdafx.h"
#include "UserInterface.h"

std::shared_ptr<CUserInterface> pUI = std::make_shared<CUserInterface>( );
bool wasInitialized = false;

CUserInterface::CUserInterface( )
{
	m_Direct3D9 = nullptr;
	m_Direct3DDevice9 = nullptr;
}

void CUserInterface::Init( )
{
	m_Direct3D9 = ( IDirect3D9* )0x03AD4CAC;
	m_Direct3DDevice9 = ( IDirect3DDevice9* )0x03AD4CA0;

	CDX9Sprite* ExpUp = new CDX9Sprite( 30, 30, 0 );
	ExpUp->ReadImage( m_Direct3DDevice9, "expup_.png", 38, 38 );
	m_Sprites.push_back( ExpUp );
}

void CUserInterface::System( )
{
	m_Direct3DDevice9->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 100, 100 ), 1.0f, 0 );
	m_Direct3DDevice9->BeginScene( );
	if( m_Sprites[ 0 ]->wasCreated( ) )
		m_Sprites[ 0 ]->Draw( );
	m_Direct3DDevice9->EndScene( );
	m_Direct3DDevice9->Present( NULL, NULL, NULL, NULL );
}

bool CUserInterface::MouseInPosition( int X, int Y, int Width, int Height )
{
	int MousePos[ 2 ] = { *( int* )( 0x0A441A4 ), *( int* )( 0x0A441A8 ) };
	if( MousePos[ 0 ] >= X && MousePos[ 0 ] <= X + Width - 1 )
	{
		if( MousePos[ 1 ] <= Y && MousePos[ 1 ] >= Y - Height + 1 )
		{
			return true;
		};
	};
	return false;
}

bool CUserInterface::GetClick( )
{
	return false;
}

void Render_Premium( )
{
	if( !wasInitialized )
	{
		wasInitialized = true;
		UI->Init( );
	};

	UI->System( );
}

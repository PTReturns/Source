#include "stdafx.h"
#include "DX9Sprite.h"

CDX9Sprite::CDX9Sprite( )
{
	//Configurações padrões.
	SetPosition( 0, 0, 0 );

	//Cor branca = Imagem normal.
	m_Color = D3DCOLOR_ARGB( 255, 255, 255, 255 );

	//Classe sem imagem.
	m_Created = false;
}

CDX9Sprite::CDX9Sprite( float X, float Y, float Z )
{
	//Configurações padrões.
	SetPosition( X, Y, Z );

	//Cor branca = Imagem normal.
	m_Color = D3DCOLOR_ARGB( 255, 255, 255, 255 );

	//Classe sem imagem.
	m_Created = false;
}

CDX9Sprite::~CDX9Sprite( )
{
	if( m_Sprite )
	{
		m_Sprite->Release( );
		m_Sprite = nullptr;
	};

	if( m_Texture )
	{
		m_Texture->Release( );
		m_Texture = nullptr;
	};
}

bool CDX9Sprite::ReadImage( IDirect3DDevice9* DXDevice, LPCSTR Path, INT Width, INT Height )
{
	if( !SUCCEEDED( D3DXCreateTextureFromFileEx( DXDevice, Path,
		Width, Height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, 0, NULL, NULL, &m_Texture ) ) )
	{
		std::cout << "Image: [ " << Path << " ] not found or DirectX problems" << std::endl;
		return false;
	};

	if( !SUCCEEDED( D3DXCreateSprite( DXDevice, &m_Sprite ) ) )
	{
		std::cout << "Image: [ " << Path << " ] with sprite problems." << std::endl;
		return false;
	}

	m_Created = true;

	return true;
}

void CDX9Sprite::Draw( )
{
	if( m_Sprite && m_Texture )
	{
		m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );
		m_Sprite->Draw( m_Texture, NULL, NULL, &m_Position, m_Color );
		m_Sprite->End( );
	};
}

void CDX9Sprite::SetPosition( float X, float Y, float Z )
{
	m_Position.x = X;
	m_Position.y = Y;
	m_Position.z = Z;
}
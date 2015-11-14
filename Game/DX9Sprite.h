#pragma once
#include <d3dx9.h>
#include <string>

class CDX9Sprite
{
public:
	//Construtores e destrutor.
	CDX9Sprite( );
	CDX9Sprite( float X, float Y, float Z = 0 );
	~CDX9Sprite( );

	//Funções do sprite.
	bool ReadImage( IDirect3DDevice9* DXDevice, LPCSTR Path, INT Width, INT Height );
	bool wasCreated( ) { return m_Created; };
	void Draw( );
	void SetPosition( float X, float Y, float Z );

private:
	//Atributos
	ID3DXSprite*		m_Sprite;
	D3DXVECTOR3			m_Position;
	IDirect3DTexture9*	m_Texture;
	D3DCOLOR			m_Color;
	bool				m_Created;
};
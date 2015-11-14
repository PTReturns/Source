#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include "DX9Sprite.h"

class CUserInterface
{
public:
	//Construtor
	CUserInterface( );

	//Inicializa a classe;
	void Init( );

	// Sistema de imagens.
	void System( );

	// Funções do mouse.
	bool MouseInPosition( int X, int Y, int Width, int Height );
	bool GetClick( );

private:
	std::vector<CDX9Sprite*>	m_Sprites;
	IDirect3D9*					m_Direct3D9;
	IDirect3DDevice9*			m_Direct3DDevice9;
};

extern std::shared_ptr<CUserInterface> pUI;
#define UI pUI
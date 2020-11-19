#pragma once
#include <D2D1.h>
#include <D2D1Helper.h>
#include <DWrite.h>
#include <vector>
#include <string>
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")

struct MTextArray
{
	UINT iSize;
	D2D1_RECT_F rt;
	std::wstring text;
	D3DCOLORVALUE color;
	D2D1_MATRIX_3X2_F matrix;
	MTextArray()
	{
		iSize = 0;
		matrix = D2D1::IdentityMatrix();
	}
};
class MWrite
{
public:
	std::vector<MTextArray>	m_TextList;
	void Draw(UINT iSize, const TCHAR* szBuffer, RECT rt,
		D2D1::ColorF color = D2D1::ColorF(1, 0, 0, 1));
public:
	ID2D1Factory*		m_pD2DFactory;
	IDWriteFactory*		m_pDWriteFactory;
	IDWriteTextFormat*	m_pTextFormat[4];
	ID2D1RenderTarget*	m_pd2dRT;
	float m_fDpiX;
	float m_fDpiY;
	ID2D1SolidColorBrush*	m_pDefaultBrush;

	IDWriteTextLayout*		m_pTextLayout;
	bool SetTextLayout(const TCHAR* text);
public:
	bool Init();
	bool OnResize(IDXGISurface* pSurface);
	bool Release();
	bool Render();
	void DeleteDXResource();
public:
	MWrite();
	~MWrite();
};


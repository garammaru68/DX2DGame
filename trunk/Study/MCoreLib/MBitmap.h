#pragma once
#include "MStd.h"
class MBitmap
{
public:
	HBITMAP				m_hBitmap;
	HDC					m_hMemDC;
	HDC					m_hScreenDC;
	BITMAP				m_BmpInfo;
	T_STR				m_csName;
	BITMAPFILEHEADER	m_bitFileHeader;
	PVOID				m_pRaster = nullptr;
public:
	bool	Load(HDC hScreenDC, T_STR szName);
	bool	LoadDIB(HDC hScreenDC, T_STR szLoadFileName);
	bool	Release();
	bool	Frame();
	bool	Render();
	bool	Init();
public:
	MBitmap();
	~MBitmap();
};


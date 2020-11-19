#pragma once
#include "MStd.h"
class MBitmap
{
public:
	HBITMAP		m_hBitmap;
	HDC			m_hMemDC;
	HDC			m_hScreenDC;
	BITMAP		m_BmpInfo;
public:
	bool	Load(HDC hScreenDC, T_STR szName);
	bool	Release();
public:
	MBitmap();
	~MBitmap();
};


#include "MBitmap.h"

bool	MBitmap::Load(HDC hScreenDC, T_STR szName)
{
	m_hScreenDC = hScreenDC;
	m_hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szName.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BmpInfo);
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);
	return true;
}
bool	MBitmap::Release()
{
	DeleteObject(m_hBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}
MBitmap::MBitmap()
{

}
MBitmap::~MBitmap()
{

}
#include "MainScreen.h"

bool MainScreen::Init(HDC hScreenDC)
{
	return true;
}
bool MainScreen::Frame()
{
	return true;
}

bool MainScreen::Render(HDC hOffScreenDC)
{
	BitBlt(g_hOffScreenDC,
		m_rtDest.left,
		m_rtDest.top,
		m_rtDest.right,
		m_rtDest.bottom,
		m_pBitmap->m_hMemDC,
		m_rtSrc.left,
		m_rtSrc.top, SRCCOPY);

	return true;
}
bool MainScreen::Release()
{
	return true;
}

MainScreen::MainScreen()
{

}
MainScreen::~MainScreen()
{

}
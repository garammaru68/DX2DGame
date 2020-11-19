#include "Sample.h"
bool	Sample::Init()
{
	m_hScreenDC = GetDC(m_hWnd);
	m_BackGround.Load(m_hScreenDC, L"../../../data/KGCABK.bmp");
	if (m_Hero.Load(m_hScreenDC, L"../../../data/bitmap1.bmp"))
	{
		RECT rtSrc, rtDesk;
		rtSrc.left = 133;
		rtSrc.top = 1;
		rtDesk.left = g_rtClient.right / 2;
		rtDesk.top = g_rtClient.bottom / 2;
		rtDesk.right = 42;
		rtDesk.bottom = 60;
		m_Hero.SetRect(rtSrc, rtDesk);
	}
	return true;
}
bool	Sample::Render()
{
	m_BackGround.Render();
	m_Hero.Render();
	return true;
}
bool	Sample::Release()
{
	m_BackGround.Release();
	m_Hero.Release();
	ReleaseDC(m_hWnd, m_hScreenDC);
	return true;
}
MWINGAME;
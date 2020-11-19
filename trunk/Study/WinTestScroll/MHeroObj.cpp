#include "MHeroObj.h"
#include "MInput.h"

bool MHeroObj::Frame()
{
	if (I_Input.KeyCheck('W'))
	{
		m_fPosY -= g_fSecondPerFrame * m_fSpeed;
	}
	if (I_Input.KeyCheck('A'))
	{
		m_fPosX -= g_fSecondPerFrame * m_fSpeed;
	}
	if (I_Input.KeyCheck('S'))
	{
		m_fPosY += g_fSecondPerFrame * m_fSpeed;
	}
	if (I_Input.KeyCheck('D'))
	{
		m_fPosX += g_fSecondPerFrame * m_fSpeed;
	}
	if (m_fPosX < 0) m_fPosX = 0;
	if (m_fPosX > g_rtClient.right - m_rtDest.right)
	{
		m_fPosX = g_rtClient.right - m_rtDest.right;
	}
	if (m_fPosY < 0) m_fPosY = 0;
	if (m_fPosY > g_rtClient.bottom - m_rtDest.bottom)
	{
		m_fPosY = g_rtClient.bottom - m_rtDest.bottom;
	}
	SetPos(m_fPosX, m_fPosY);
	return true;
}
bool MHeroObj::Render(HDC hOffScreenDC)
{
	if (m_pBitmapMask != nullptr)
	{
		BitBlt(hOffScreenDC,
			m_rtDest.left,
			m_rtDest.top,
			m_rtDest.right,
			m_rtDest.bottom,
			m_pBitmapMask->m_hMemDC,
			m_rtSrc.left,
			m_rtSrc.top, SRCAND);
		BitBlt(hOffScreenDC,
			m_rtDest.left,
			m_rtDest.top,
			m_rtDest.right,
			m_rtDest.bottom,
			m_pBitmap->m_hMemDC,
			m_rtSrc.left,
			m_rtSrc.top, SRCINVERT);
		BitBlt(hOffScreenDC,
			m_rtDest.left,
			m_rtDest.top,
			m_rtDest.right,
			m_rtDest.bottom,
			m_pBitmapMask->m_hMemDC,
			m_rtSrc.left,
			m_rtSrc.top, SRCINVERT);
	}
	else
	{
		TransparentBlt(hOffScreenDC,
			m_rtDest.left,
			m_rtDest.top,
			m_rtDest.right,
			m_rtDest.bottom,
			m_pBitmap->m_hMemDC,
			m_rtSrc.left,
			m_rtSrc.top,
			m_rtDest.right,
			m_rtDest.bottom,
			RGB(255, 255, 255));
	}
	return true;
}
MHeroObj::MHeroObj()
{
	m_fSpeed = 200.0f;
}
MHeroObj::~MHeroObj()
{

}
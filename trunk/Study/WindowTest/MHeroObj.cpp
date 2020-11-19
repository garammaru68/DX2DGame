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
	m_rtDest.left = m_fPosX;
	m_rtDest.top = m_fPosY;
	return true;
}
bool	MHeroObj::Render(HDC hOffScreenDC)
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

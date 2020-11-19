#include "MSprite.h"
#include "MBitmapMgr.h"

bool MSprite::Frame()
{
	return true;
}
bool MSprite::Render(HDC hOffScreenDC)
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
	return true;
}
MSprite::MSprite()
{

}
MSprite::~MSprite()
{

}
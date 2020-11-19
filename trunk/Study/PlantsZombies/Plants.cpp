#include "Plants.h"

bool Plants::Render(HDC hOffScreenDC)
{
	StretchBlt(hOffScreenDC,
		m_rtDest.left,
		m_rtDest.top,
		m_rtDest.right,
		m_rtDest.bottom,
		m_pBitmap->m_hMemDC,
		m_rtSrc.left,
		m_rtSrc.top,
		m_rtDest.right,
		m_rtDest.bottom,
		SRCCOPY);

	return true;
}
Plants::Plants()
{

}
Plants::~Plants()
{

}
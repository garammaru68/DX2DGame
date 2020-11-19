#include "MapScreen.h"

bool MapScreen::Frame()
{
	return true;
};
bool MapScreen::Render(HDC hOffScreenDC)
{
	RECT rt;
	rt.left = m_rtSrc.left;
	rt.right = m_rtDest.right;
	rt.top = m_rtSrc.top;
	rt.bottom = m_rtDest.bottom;
	Draw(0, 0, rt);

	return true;
}
void MapScreen::Draw(float x, float y, RECT rt)
{
	BitBlt(g_hOffScreenDC,
		x,
		y,
		rt.right,
		rt.bottom,
		m_pBitmap->m_hMemDC,
		220,
		rt.top,
		SRCCOPY);
}
MapScreen::MapScreen()
{
}
MapScreen::~MapScreen()
{

}

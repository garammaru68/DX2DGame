#pragma once
#include "MObject.h"
class MMap : public MObject
{
public:
	float	m_fScroll;
	float	m_fScrollSrc;
	float	m_fSpeed;
	BOOL	m_bScroll;
	POINT	m_ptPos;
public:
	bool Frame()
	{
		m_bScroll = 2;

		if (m_ptPos.y < 200)
			m_bScroll = 0;
		if (m_ptPos.y > 400)
			m_bScroll = 1;

		if (m_bScroll == 1) AutoUp();
		if (m_bScroll == 0) AutoDown();
		return true;
	};
	void Draw(float x, float y, RECT rt)
	{
		BitBlt(g_hOffScreenDC,
			x,
			y,
			rt.right,
			rt.bottom,
			m_pBitmap->m_hMemDC,
			rt.left,
			rt.top, SRCCOPY);
	}
	bool AutoUp()
	{
		m_fScroll += g_fSecondPerFrame * m_fSpeed;
		m_fScrollSrc += g_fSecondPerFrame * m_fSpeed;
		if (m_fScrollSrc > m_pBitmap->m_BmpInfo.bmHeight)
		{
			m_fScrollSrc = 0;
			m_fScroll = 0;
		}
		return true;
	};
	bool AutoDown()
	{
		m_fScroll -= g_fSecondPerFrame * m_fSpeed;
		m_fScrollSrc -= g_fSecondPerFrame * m_fSpeed;
		if (m_fScrollSrc < 0)
		{
			m_fScrollSrc = m_pBitmap->m_BmpInfo.bmHeight;
			m_fScroll = m_rtDest.bottom;
		}
		return true;
	};
	bool Render(HDC hOffScreenDC)
	{
		RECT rt;
		rt.left = m_rtSrc.left;
		rt.right = m_rtDest.right;

		rt.top = m_fScrollSrc;
		rt.bottom = m_rtDest.bottom - m_fScroll;
		Draw(0, 0, rt);

		rt.top = 0;
		rt.bottom = m_fScroll;
		Draw(0, m_rtDest.bottom - m_fScroll, rt);
		return true;
	};
public:
	MMap() {
		m_fScroll	= 0.0f;
		m_bScroll	= false;
		m_fSpeed	= 100.0f;
	}
	~MMap() {};
};


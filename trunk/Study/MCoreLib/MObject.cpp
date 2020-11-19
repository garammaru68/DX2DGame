#include "MObject.h"
#include "MBitmapMgr.h"

void	MObject::SetPos(MPoint pos, MObject* pOwner)
{
	SetPos(pos.x, pos.y);
}
void	MObject::SetPos(float x, float y, MObject* pOwner)
{
	m_rtDest.left	= x;
	m_rtDest.top	= y;
	m_fPosX			= x;
	m_fPosY			= y;
	m_rtCollision.left		= x;
	m_rtCollision.top		= y;
	m_rtCollision.right		= m_rtCollision.left + m_rtDest.right;
	m_rtCollision.bottom	= m_rtCollision.top + m_rtDest.bottom;

	m_Sphere.vCenter.x	= (m_rtCollision.left + m_rtCollision.right) / 2;
	m_Sphere.vCenter.y	= (m_rtCollision.top + m_rtCollision.bottom) / 2;
	float fA			= m_rtCollision.right - m_Sphere.vCenter.x;
	float fB			= m_Sphere.vCenter.y - m_rtCollision.top;
	m_Sphere.fRadius	= sqrt(fA*fA + fB * fB);
}
void	MObject::SetRect(RECT rtSrc, RECT rtDest, MObject* pOwner)
{
	m_rtSrc		= rtSrc;
	m_rtDest	= rtDest;
	SetPos(m_rtDest.left, m_rtDest.top, pOwner);
}
void	MObject::SetMaskBitmap(HDC hScreenDC, T_STR szFileName)
{
	m_iMaskIndex	= I_BitmapMgr.Load(hScreenDC, szFileName);
	m_pBitmapMask	= I_BitmapMgr.GetPtr(m_iMaskIndex);
}
bool	MObject::Load(HDC hScreenDC, T_STR szFileName)
{
	m_iIndex		= I_BitmapMgr.Load(hScreenDC, szFileName);
	m_pBitmap		= I_BitmapMgr.GetPtr(m_iIndex);
	m_rtSrc.left	= 0;
	m_rtSrc.top		= 0;
	m_rtSrc.right	= m_pBitmap->m_BmpInfo.bmWidth;
	m_rtSrc.bottom	= m_pBitmap->m_BmpInfo.bmHeight;
	m_rtDest.left	= 0;
	m_rtDest.top	= 0;
	m_rtDest.right	= m_rtSrc.right;
	m_rtDest.bottom = m_rtSrc.bottom;
	
	m_fPosX			= 0;
	m_fPosY			= 0;
	m_tPosition.x	= m_fPosX;
	m_tPosition.y	= m_fPosY;

	return true;
}
bool	MObject::Init()
{
	return true;
}
bool	MObject::Frame()
{
	return true;
}
bool	MObject::Render(HDC hOffScreenDC)
{
	if (m_pBitmap->m_BmpInfo.bmBitsPixel == 32)
	{
		BLENDFUNCTION ftn;
		ftn.BlendOp				= AC_SRC_OVER;
		ftn.BlendFlags			= 0;
		ftn.SourceConstantAlpha = 255;
		ftn.AlphaFormat			= AC_SRC_ALPHA;
		AlphaBlend(hOffScreenDC, m_rtDest.left, m_rtDest.top, m_rtDest.right, m_rtDest.bottom,
			m_pBitmap->m_hMemDC, m_rtSrc.left, m_rtSrc.top, m_rtDest.right, m_rtDest.bottom,
			ftn);
	}
	else
	{
		BLENDFUNCTION ftn;
		ftn.BlendOp				= AC_SRC_OVER;
		ftn.BlendFlags			= 0;
		ftn.SourceConstantAlpha = 0xff;
		ftn.AlphaFormat			= AC_SRC_OVER;
		AlphaBlend(hOffScreenDC, m_rtDest.left, m_rtDest.top, m_rtDest.right, m_rtDest.bottom,
			m_pBitmap->m_hMemDC, m_rtSrc.left, m_rtSrc.top, m_rtDest.right, m_rtDest.bottom,
			ftn);
		/*BitBlt(hOffScreenDC,
			m_rtDest.left,
			m_rtDest.top,
			m_rtDest.right,
			m_rtDest.bottom,
			m_pBitmap->m_hMemDC,
			m_rtSrc.left,
			m_rtSrc.top, SRCCOPY);*/
	}
	return true;
}
bool	MObject::Release()
{
	return true;
}

bool MObject::DrawColorKey(HDC hOffScreenDC, COLORREF color)
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

		color);
	return true;
}

MObject::MObject()
{
}
MObject::~MObject()
{
}

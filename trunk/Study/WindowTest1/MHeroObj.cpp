#include "MHeroObj.h"
#include "MInput.h"

bool	MHeroObj::Init()
{
	m_hColorDC = CreateCompatibleDC(g_hScreenDC);
	m_hMaskDC = CreateCompatibleDC(g_hScreenDC);
	return true;
}
bool	MHeroObj::Release()
{
	MObject::Release();
	DeleteDC(m_hColorDC);
	DeleteDC(m_hColorDC);
	return true;
}

bool	MHeroObj::Frame()
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
	SetPos(m_fPosX, m_fPosY);
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
int		MHeroObj::RotateBlt(HDC hOffScreenDC, HDC srcDC, HDC onwerDC, float fAngle)
{
	int iSize = sqrt(m_rtDest.right * m_rtDest.right +
					m_rtDest.bottom * m_rtDest.bottom);

	HBITMAP hbmResult = MakeDIBSection(iSize, iSize);
	HBRUSH hbrBack = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(srcDC, hbmResult);
	SelectObject(srcDC, hbrBack);
	PatBlt(srcDC, 0, 0, iSize, iSize, PATCOPY);

	int iOldGraphic = SetGraphicsMode(srcDC, GM_ADVANCED);

	float fRadian = fAngle * 3.141592f / 180.0f;
	XFORM xForm;

	xForm.eM11 = cos(fRadian);	xForm.eM12 = -sin(fRadian);
	xForm.eM21 = sin(fRadian);	xForm.eM22 = cos(fRadian);
	xForm.eDx  = iSize / 2;	    xForm.eDy  = iSize / 2;
	SetWorldTransform(srcDC, &xForm);

	BitBlt(srcDC,
		-(m_rtDest.right / 2.0f),
		-(m_rtDest.bottom / 2.0f),
		m_rtDest.right, m_rtDest.bottom,
		onwerDC,
		m_rtSrc.left, m_rtSrc.top,
		SRCCOPY);

	xForm.eM11 = 1;	xForm.eM12 = 0;
	xForm.eM21 = 0;	xForm.eM22 = 1;
	xForm.eDx  = 0;	xForm.eDy  = 0;
	SetWorldTransform(srcDC, &xForm);
	SetGraphicsMode(srcDC, iOldGraphic);
	DeleteObject(hbrBack);
	DeleteObject(hbmResult);
	return iSize;
}
HBITMAP MHeroObj::MakeDIBSection(int iWidth, int iHeight)
{
	BITMAPINFO bmi;
	ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biHeight = iHeight;
	bmi.bmiHeader.biWidth = iWidth;
	bmi.bmiHeader.biPlanes = 1;

	LPVOID	pBits;
	HBITMAP hBitmap;
	hBitmap = CreateDIBSection(
		g_hScreenDC, &bmi,
		DIB_RGB_COLORS,
		(void**)&pBits, NULL, 0);
	return hBitmap;
}
void	MHeroObj::SetAngle(float fDegree)
{
	m_fAngle = fDegree;
}
MHeroObj::MHeroObj()
{
	m_fSpeed = 200.0f;
	m_fAngle = 0.0f;
}
MHeroObj::~MHeroObj()
{

}
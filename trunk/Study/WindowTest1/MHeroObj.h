#pragma once
#include "MObject.h"
class MHeroObj : public MObject
{
public:
	float	m_fSpeed;
	float	m_fAngle;
	HDC		m_hColorDC;
	HDC		m_hMaskDC;
public:
	bool	Init();
	bool	Release();
	bool	Frame();
	bool	Render(HDC hOffScreenDC);
	int		RotateBlt(HDC hOffScreenDC, HDC srcDC, HDC ownerDC, float fAngle = 0.0f);
	HBITMAP	MakeDIBSection(int iWidth, int iHeight);
	void	SetAngle(float fDegree);
public:
	MHeroObj();
	virtual ~MHeroObj();
};


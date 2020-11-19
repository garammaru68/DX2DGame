#pragma once
#include "MCollision.h"

class MObject
{
public:
	MObject*	m_pOwner;
	int			m_iIndex;
	MBitmap*	m_pBitmap;
	int			m_iMaskIndex;
	MBitmap*	m_pBitmapMask;

	RECT		m_rtSrc;
	RECT		m_rtDest;
	RECT		m_rtCollision;
	MSphere		m_Sphere;
	float		m_fPosX;
	float		m_fPosY;
	MPoint		m_tPosition;
public:
	MPoint		GetPos() { return m_tPosition; }
	virtual void		SetPos(MPoint pos, MObject* pOwner = nullptr);
	virtual void		SetPos(float x, float y, MObject* pOwner = nullptr);
	virtual void		SetRect(RECT rtSrc, RECT rtDest, MObject* pOwner = nullptr);
	void		SetMaskBitmap(HDC hScreenDC, T_STR szFileName);
	bool		Load(HDC hScreenDC, T_STR szFileName);
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render(HDC hOffScreenDC);
	virtual bool	Release();
public:
	bool		DrawColorKey(HDC hOffScreenDC, COLORREF color = RGB(255, 255, 255));
public:
	MObject();
	virtual ~MObject();
};


#pragma once
#include "MBitmap.h"
class MObject
{
private:
	MBitmap		m_Bitmap;
	RECT		m_rtSrc;
	RECT		m_rtDesk;
public:
	void		SetRect(RECT rtSrc, RECT rtDesk);
	bool		Load(HDC hScreenDC, T_STR szFileName);
	bool		Render();
	bool		Release();
public:
	MObject();
	virtual ~MObject();
};


#pragma once
#include "MObject.h"
class MNpcObj : public MObject
{
public:
	bool	m_bDead;
	float	m_fDirX = 1.0f;
	float	m_fDirY = 1.0f;
public:
	bool	Frame();
	bool	Render(HDC hOffScreenDC);
public:
	MNpcObj();
	virtual ~MNpcObj();
};


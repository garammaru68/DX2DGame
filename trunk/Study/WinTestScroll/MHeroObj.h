#pragma once
#include "MObject.h"
class MHeroObj : public MObject
{
public:
	float	m_fSpeed;
public:
	bool	Frame();
	bool	Render(HDC hOffScreenDC);
public:
	MHeroObj();
	virtual ~MHeroObj();
};


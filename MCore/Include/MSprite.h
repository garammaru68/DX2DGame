#pragma once
#include "MObject.h"
class MSprite : public MObject
{
public:
	std::vector<RECT>		m_rtList;
	std::vector<int>		m_bmpList;
public:
	bool Frame();
	bool Render(HDC hOffScreenDC);
public:
	MSprite();
	virtual ~MSprite();
};


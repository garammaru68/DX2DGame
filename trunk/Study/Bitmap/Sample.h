#pragma once
#include "MCore.h"
#include "MObject.h"
class Sample : public MCore
{
	HDC			m_hScreenDC;
	MObject		m_Hero;
	MObject		m_BackGround;
public:
	bool	Init();
	bool	Render();
	bool	Release();
};


#pragma once
#include "MWindow.h"
#include "MSoundMgr.h"
#include "MTimer.h"
#include "MInput.h"
class MCore : public MWindow
{
public:
	MTimer	m_Timer;

	HFONT	m_hDefaultFont;
	HFONT	m_hGameFont;
	HBRUSH	m_hbrBack;
	HDC		m_hScreenDC;
	HDC		m_hOffScreenDC;
	HBITMAP	m_hOffScreenBitmap;
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();
private:
	bool MCoreInit();
	bool MCoreFrame();
	bool MCoreRender();
	bool MCoreRelease();
public:
	bool MRun();
public:
	MCore();
	virtual ~MCore();
};


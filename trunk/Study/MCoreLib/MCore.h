#pragma once
#include "MWindow.h"
#include "MWrite.h"
//#include "MSoundMgr.h"
//#include "MTimer.h"
//#include "MInput.h"
class MCore : public MWindow
{
public:
	MWrite		m_Write;
	//MTimer	m_Timer;
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();
	virtual void	CreateDXResource() override;
	virtual void	DeleteDXResource() override;
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


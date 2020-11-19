#pragma once
#include "MDevice.h"
class MWindow : public MDevice
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	bool		m_bExit;
	RECT		m_rtClient;
	RECT		m_rtWindow;
private:
	MSG			msg;
public:
	bool SetWindow(HINSTANCE hInstance);
	bool WinRun();
	virtual LRESULT MsgProc(
		HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);
	virtual bool GameRun();
public:
	MWindow();
	virtual ~MWindow();
};


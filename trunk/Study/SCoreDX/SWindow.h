#pragma once
#include "SDevice.h"

class SWindow : public SDevice
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	DWORD		m_dwWindowStyle;
	RECT		m_rcWindowBounds;
	RECT		m_rcWindowClient;
	UINT		m_iwindowWidth;
	UINT		m_iWindowHeight;
private:
	MSG			msg;
public:
	bool InitWindow(	HINSTANCE hInstance,
						int cCmdShow,
						const TCHAR* strWindowTitle = _T("MBasis Sample"),
						int iWidth = 800,
						int iHeight = 600,
						BOOL IsFullScreen = FALSE);
	void CenterWindow(HWND hwnd);
	bool CheckWindowSize();

public:
	virtual int WndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT		WindowMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	SWindow();
	virtual ~SWindow();
};


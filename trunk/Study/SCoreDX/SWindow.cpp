#include "SWindow.h"

SWindow* g_pWindow = NULL;

namespace SBASIS
{
	HWND		g_hWnd;
	HINSTANCE	g_hInstance;
	RECT		g_rtClient;
};

LRESULT WINAPI StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);
	return g_pWindow->WindowMsgProc(hWnd, msg, wParam, lParam);
}

int SWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return -1;
}

LRESULT SWindow::WindowMsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int iReturn = WndProc(hWnd, message, wParam, lParam);
	if (iReturn >= 0)
	{
		return iReturn;
	}
	
	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case '0':
		{
			if (GetSwapChain() )
			{
				BOOL IsScreenMode = FALSE;
				GetSwampChain
			}
		}
		}
	}
	}
}
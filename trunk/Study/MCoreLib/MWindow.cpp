#include "MWindow.h"
HINSTANCE	g_hInstance = 0;
HWND		g_hWnd = 0;
RECT		g_rtClient;

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
MWindow::MWindow()
{
	ZeroMemory(&msg, sizeof(MSG));
}
MWindow::~MWindow()
{

}
bool MWindow::GameRun() { return true; }
bool MWindow::SetWindow(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	g_hInstance = hInstance;

	WNDCLASSEXW	wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEXW));
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.hInstance = hInstance;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"SSMWIN";
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}
	RECT rt = { 0,0,800,600 };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWnd = CreateWindowEx(
		0,
		L"SSMWIN",
		L"MWindow",
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		rt.right-rt.left,
		rt.bottom-rt.top,
		0, 0, m_hInstance, 0);

	if (m_hWnd == NULL) return 1;

	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);

	g_rtClient = m_rtClient;
	g_hWnd = m_hWnd;

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
bool MWindow::WinRun()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			m_bExit = true;
		}
		return false;
	}
	return true;
}
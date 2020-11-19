#include "MCore.h"

void MCore::CreateDXResource()
{
	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**))
}
bool MCore::Init() { return true; }
bool MCore::Frame() { return true; }
bool MCore::PreRender()
{
	PatBlt(m_hOffScreenDC,
		0, 0, m_rtClient.right,
		m_rtClient.bottom,
		PATCOPY );
	return true;
}
bool MCore::Render() { return true; }
bool MCore::PostRender()
{
	BitBlt(m_hScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool MCore::Release() { return true; }

bool MCore::MCoreInit()
{	
	m_Timer.Init();
	I_SoundMgr.Init();
	I_Input.Init();

	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	g_hScreenDC = m_hScreenDC;
	g_hOffScreenDC = m_hOffScreenDC;

	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC,
												m_rtClient.right,
												m_rtClient.bottom);

	COLORREF bkColor = RGB(255, 0, 0);
	m_hbrBack = CreateSolidBrush(bkColor);

	m_hDefaultFont = CreateFont(
		20, 0, 0, FW_BOLD, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0, L"±Ã¼­");
	m_hGameFont = CreateFont(
		30, 0, 0, FW_BOLD, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0, 0, L"°íµñ");
	
	SelectObject(m_hOffScreenDC, m_hbrBack);
	SelectObject(m_hOffScreenDC, m_hDefaultFont);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	Init();
	return true;
}
bool MCore::MCoreFrame()
{
	m_Timer.Frame();
	I_SoundMgr.Frame();
	I_Input.Frame();

	if (g_InputMap.bExit == KEY_PUSH)
	{
		m_bExit = true;
		return false;
	}

	Frame();
	return true;
}
bool MCore::MCoreRender()
{
	PreRender();
	Render();

	m_Timer.Render();
	I_SoundMgr.Render();
	I_Input.Render();

	T_STR strBuffer = L"GameTime";
	strBuffer += m_Timer.m_csBuffer;
	SetTextColor(m_hOffScreenDC, RGB(255, 0, 0));
	SetBkColor(m_hOffScreenDC, RGB(0, 0, 255));
	SetBkMode(m_hOffScreenDC, TRANSPARENT);
	DrawText(m_hOffScreenDC, strBuffer.c_str(), -1, &g_rtClient, DT_LEFT | DT_VCENTER);

	PostRender();
	return true;
}
bool MCore::MCoreRelease()
{
	Release();

	DeleteObject(m_hDefaultFont);
	DeleteObject(m_hGameFont);
	DeleteObject(m_hbrBack);
	DeleteObject(m_hOffScreenBitmap);
	ReleaseDC(m_hWnd, m_hOffScreenDC);
	ReleaseDC(m_hWnd, m_hScreenDC);

	m_Timer.Release();
	I_SoundMgr.Release();
	return true;
}
bool MCore::MRun()
{
	MCoreInit();
	while (!m_bExit)
	{
		if (WinRun())
		{
			MCoreFrame();
			MCoreRender();
			Sleep(1);
		}
	}
	MCoreRelease();
	return true;
}
MCore::MCore()
{
	m_bExit = false;
}
MCore::~MCore()
{

}
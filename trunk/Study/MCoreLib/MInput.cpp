#include "MInput.h"
POINT			g_MousePos;
MInputActionMap	g_InputMap;

bool MInput::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	return true;
}
bool MInput::Frame() 
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);
	g_MousePos = m_MousePos;

	g_InputMap.bWKey = KeyCheck('W');
	g_InputMap.bSKey = KeyCheck('S');
	g_InputMap.bAKey = KeyCheck('A');
	g_InputMap.bDKey = KeyCheck('D');

	g_InputMap.bLeftClick = KeyCheck(VK_LBUTTON);
	g_InputMap.bRightClick = KeyCheck(VK_RBUTTON);
	g_InputMap.bMiddleClick = KeyCheck(VK_MBUTTON);
	g_InputMap.bAttack = g_InputMap.bLeftClick;
	g_InputMap.bExit = KeyCheck(VK_ESCAPE);
	return true;
}
bool MInput::Render() 
{
	return true;
}
bool MInput::Release() 
{
	return true;
}
POINT MInput::GetPos()
{
	return m_MousePos;
}
DWORD MInput::KeyCheck(DWORD dwKey)
{
	SHORT sKey = GetAsyncKeyState(dwKey);
	// 0x8000 -> 10000000 00000000
	if (sKey & 0x8000)
	{
		if (m_dwKeyState[dwKey] == KEY_FREE ||
			m_dwKeyState[dwKey] == KEY_UP)
		{
			m_dwKeyState[dwKey] = KEY_PUSH;
		}
		else
		{
			m_dwKeyState[dwKey] = KEY_HOLD;
		}
	}
	else
	{
		if (m_dwKeyState[dwKey] == KEY_PUSH ||
			m_dwKeyState[dwKey] == KEY_HOLD)
		{
			m_dwKeyState[dwKey] = KEY_UP;
		}
		else
		{
			m_dwKeyState[dwKey] = KEY_FREE;
		}
	}
	return m_dwKeyState[dwKey];
}
MInput::MInput()
{

}
MInput::~MInput()
{

}
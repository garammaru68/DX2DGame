#include "UI.h"
#include "MInput.h"

// Button
void Button::SetState(int iIndex)
{
	if (m_ButtonState.size() <= 0) return;
	m_pBitmap = I_BitmapMgr.GetPtr(m_ButtonState[iIndex]);
}
bool Button::Frame()
{
	m_iState = 0;
	if (MCollision::RectInPt(m_rtCollision, I_Input.GetPos()))
	{
		m_iState = 1;
		//if (g_InputMap.bLeftClick == KEY_PUSH || g_InputMap.bLeftClick == KEY_HOLD)
		//{
		//	m_iState = 2;
		//}
	}
	SetState(m_iState);
	return true;
}
bool Button::Render(HDC hOffSCreenDC)
{
	TransparentBlt(g_hOffScreenDC,
		m_rtDest.left,
		m_rtDest.top,
		m_rtSrc.right,
		m_rtSrc.bottom,
		m_pBitmap->m_hMemDC,
		m_rtSrc.left,
		m_rtSrc.top,
		m_rtSrc.right,
		m_rtSrc.bottom,
		RGB(255, 0, 255));

	return true;
}
void Button::SetPos(MPoint pos, MObject* pOwner)
{
	SetPos(pos.x, pos.y, pOwner);
}
void Button::SetPos(float x, float y, MObject* pOwner)
{
	if (pOwner == nullptr)
	{
		m_rtDest.left = x;
		m_rtDest.top = y;
		m_fPosX = x;
		m_fPosY = y;
		m_rtCollision.left = x;
		m_rtCollision.top = y;
		m_rtCollision.right = m_rtCollision.left + m_rtSrc.right;
		m_rtCollision.bottom = m_rtCollision.top + m_rtSrc.bottom;
	}
	else
	{
		m_rtDest.left = pOwner->m_fPosX + x;
		m_rtDest.top = pOwner->m_fPosX + y;
		m_fPosX = pOwner->m_fPosX + x;
		m_fPosY = pOwner->m_fPosX + y;
		m_rtCollision.left = pOwner->m_fPosX + x;
		m_rtCollision.top = pOwner->m_fPosX + y;
		m_rtCollision.right = m_rtCollision.left + m_rtDest.right;
		m_rtCollision.bottom = m_rtCollision.top + m_rtDest.bottom;
	}
}
void Button::SetRect(RECT rtSrc, RECT rtDest, MObject* pOwner)
{
	m_rtSrc = rtSrc;
	m_rtDest = rtDest;
	SetPos(m_rtDest.left, m_rtDest.top, pOwner);
}
///////////////////////////////////////////////////////
// UI
void UI::SetState(int iIndex)
{
	if (m_ButtonState.size() <= 0) return;
	m_pBitmap = I_BitmapMgr.GetPtr(m_ButtonState[iIndex]);
}
bool UI::Frame()
{
	Button::Frame();

	for (auto btn : m_UI)
	{
		btn->Frame();
	}
	return true;
}
bool UI::Render(HDC hdc)
{
	TransparentBlt(g_hOffScreenDC,
		m_rtDest.left,
		m_rtDest.top,
		m_rtSrc.right,
		m_rtSrc.bottom,
		m_pBitmap->m_hMemDC,
		m_rtSrc.left,
		m_rtSrc.top,
		m_rtSrc.right,
		m_rtSrc.bottom,
		RGB(255, 0, 255));
	
	for (auto btn : m_UI)
	{
		btn->Render(hdc);
	}
	return true;
}
void UI::SetPos(MPoint pos, MObject* pOwner)
{
	SetPos(pos.x, pos.y, pOwner);
}
void UI::SetPos(float x, float y, MObject* pOwner)
{
	m_rtDest.left = x;
	m_rtDest.top = y;
	m_fPosX = x;
	m_fPosY = y;
	m_rtCollision.left = x;
	m_rtCollision.top = y;
	m_rtCollision.right = m_rtCollision.left + m_rtSrc.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtSrc.bottom;
}
void UI::SetRect(RECT rtSrc, RECT rtDest, MObject* pOwner)
{
	m_rtSrc = rtSrc;
	m_rtDest = rtDest;
	SetPos(m_rtDest.left, m_rtDest.top, pOwner);
}
///////////////////////////////////////////////////////
// List
bool UIList::CreateUIList(MObject* pOwner, int x, int y, int iWidth, int iHeight, int iNumBtn)
{
	float fOffsetX = iWidth / iNumBtn;
	float fOffsetY = iHeight;

	RECT rtSrc, rtDest;
	rtSrc.left = 0;
	rtSrc.top = 0;
	rtSrc.right = iWidth;
	rtSrc.bottom = iHeight;
	rtDest.left = (pOwner) ? pOwner->m_fPosX + x : x;
	rtDest.top = (pOwner) ? pOwner->m_fPosY + y : y;
	rtDest.right = iWidth;
	rtDest.bottom = iWidth;
	SetRect(rtSrc, rtDest);

	TCHAR UIListBuffer[][64] = {
				L"../../../data/API/resource/SunFlowerOn.bmp",	L"../../../data/API/resource/SunFlowerOff.bmp",
				L"../../../data/API/resource/WallNutOn.bmp",	L"../../../data/API/resource/WallNutOff.bmp",
				L"../../../data/API/resource/PeaShooterOn.bmp", L"../../../data/API/resource/PeaShooterOff.bmp",
				L"../../../data/API/resource/RepeaterOn.bmp",	L"../../../data/API/resource/RepeaterOff.bmp",
				L"../../../data/API/resource/SnowPeaOn.bmp",	L"../../../data/API/resource/SnowPeaOff.bmp",
	};
	m_iNumUI = wcslen(reinterpret_cast<const wchar_t *>(UIListBuffer));

	m_Button.resize(iNumBtn);
	for (int iButton = 0; iButton < iNumBtn; iButton++)
	{
		m_Button[iButton].Load(g_hScreenDC, L"../../../data/API/resource/SunFlowerOn.bmp");

		for (int i = 0; i < m_iNumUI; i++)
		{
			int iIndex = I_BitmapMgr.Load(g_hScreenDC, UIListBuffer[i]);
			m_Button[iButton].m_ButtonState.push_back(iIndex);
		}
		MPoint pos;
		pos.x = 0;
		pos.y = fOffsetY * iButton;
		m_Button[iButton].SetPos(pos, this);

		m_Button[iButton].m_rtDest.right = fOffsetX;
		m_Button[iButton].m_rtDest.bottom = fOffsetY;

		m_Button[iButton].SetState(0);
	}
	return true;
}
void UIList::SetState(int iIndex)
{
	if (m_ButtonState.size() <= 0) return;
	m_pBitmap = I_BitmapMgr.GetPtr(m_ButtonState[iIndex]);
}
bool UIList::Frame()
{
	Button::Frame();
	for (auto& btn : m_Button)
	{
		btn.Frame();
	}
	return true;
}
bool UIList::Render(HDC hdc)
{
	if (m_pBitmap != nullptr)
	{

		TransparentBlt(g_hOffScreenDC,
			m_rtDest.left,
			m_rtDest.top,
			m_rtSrc.right,
			m_rtSrc.bottom,
			m_pBitmap->m_hMemDC,
			m_rtSrc.left,
			m_rtSrc.top,
			m_rtSrc.right,
			m_rtSrc.bottom,
			RGB(255, 0, 255));
	}

	for (auto& btn : m_Button)
	{
		btn.Render(hdc);
	}
	return true;
}
void UIList::SetPos(MPoint pos, MObject* pOwner)
{
	SetPos(pos.x, pos.y, pOwner);
}
void UIList::SetPos(float x, float y, MObject* pOwner)
{
	m_rtDest.left = x;
	m_rtDest.top = y;
	m_fPosX = x;
	m_fPosY = y;
	m_rtCollision.left = x;
	m_rtCollision.top = y;
	m_rtCollision.right = m_rtCollision.left + m_rtSrc.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtSrc.bottom;
}
void UIList::SetRect(RECT rtSrc, RECT rtDest, MObject* pOwner)
{
	m_rtSrc = rtSrc;
	m_rtDest = rtDest;
	SetPos(m_rtDest.left, m_rtDest.top, pOwner);
}

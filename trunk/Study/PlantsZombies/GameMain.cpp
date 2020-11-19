#include "GameMain.h"

void (Sample::*ScreenRender)();

bool Sample::Init()
{
	// Main
	m_MainMenu.Load(m_hScreenDC, L"../../../data/API/resource/Main.bmp");
	m_MainButton.Load(m_hScreenDC, L"../../../data/API/resource/StartBarOff.bmp");

	TCHAR mainUI[][64] = {
		L"../../../data/API/resource/StartBarOff.bmp",
		L"../../../data/API/resource/StartBarOn.bmp",
	};
	for (int i = 0; i < 2; i++)
	{
		int iIndex = I_BitmapMgr.Load(m_hScreenDC, mainUI[i]);
		m_MainButton.m_ButtonState.push_back(iIndex);
	}
	m_MainButton.SetPos(235, 520);
	
	
	// InGame
	// UI
	m_Battlefield.Load(m_hScreenDC, L"../../../data/API/resource/Background.bmp");

	TCHAR mapUI[][64] = {
		L"../../../data/API/resource/SeedBank.bmp",
		L"../../../data/API/resource/ShovelBank.bmp",
		L"../../../data/API/resource/GaugeBlack.bmp",
	};
	m_NumUI = wcslen(reinterpret_cast<const wchar_t *>(mapUI));

	m_MapUI.resize(m_NumUI);
	for (int i = 0; i < m_NumUI; i++)
	{
		m_MapUI[i].Load(m_hScreenDC, mapUI[i]);
	}
	m_MapUI[0].SetPos(5, 0);
	m_MapUI[1].SetPos(450, 0);
	m_MapUI[2].SetPos(600, 578);

	m_PlantCards.Load(m_hScreenDC, L"../../../data/API/resource/SunFlowerOn.bmp");

	UIList* pPlantCards = new UIList;
	pPlantCards->CreateUIList(&m_PlantCards, 100, 100, 70, 50, 2);
	m_PlantCards.m_UI.push_back(pPlantCards);

	ScreenRender = &Sample::MainScreenRender;

	return true;
}
bool Sample::Frame()
{
	m_MainButton.Frame();
	m_PlantCards.Frame();

	return true;
}
bool Sample::Render()
{
	(this->*ScreenRender)();

	return true;
}
bool Sample::Release()
{
	// Main
	m_MainMenu.Release();
	m_MainButton.Release();

	// InGame
	m_Battlefield.Release();
	m_MapUI.clear();
	m_PlantCards.Release();

	return true;
}

void Sample::MainScreenRender()
{
	m_MainMenu.Render(g_hOffScreenDC);
	m_MainButton.Render(g_hOffScreenDC);

	if (MCollision::RectInPt(m_MainButton.m_rtCollision, I_Input.GetPos()))
	{
		if (g_InputMap.bLeftClick == KEY_PUSH)
		{
			ScreenRender = &Sample::MapScreenRender;
		}
	}
}
void Sample::MapScreenRender()
{
	m_Battlefield.Render(g_hOffScreenDC);

	for (int i = 0; i < 17; i++)
	{
		m_MapUI[i].Render(g_hOffScreenDC);
	}

	m_PlantCards.Render(g_hOffScreenDC);
}

Sample::Sample()
{

}
Sample::~Sample()
{

}
MWINGAME;
#pragma once
#include "MCore.h"
#include "MainScreen.h"
#include "MapScreen.h"
#include "UI.h"
#include "Plants.h"
#include "Zombies.h"

class Sample : public MCore
{
	int				m_NumUI;
	// Main
	MainScreen		m_MainMenu;
	Button			m_MainButton;
	// InGame
	MapScreen		m_Battlefield;
	vector<UI>		m_MapUI;
	UI				m_PlantCards;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void MainScreenRender();
	void MapScreenRender();
public:
	Sample();
	~Sample();
};


#pragma once
#include "MObject.h"

class MainScreen : public MObject
{
public:
	bool Init(HDC hScreenDC);
	bool Frame();
	bool Render(HDC hOffScreenDC);
	bool Release();
public:
	MainScreen();
	~MainScreen();
};


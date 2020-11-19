#pragma once
#include "MObject.h"

class MapScreen : public MObject
{
public:
public:
	bool Frame();
	bool Render(HDC hOffScreenDC);
	void Draw(float x, float y, RECT rt);
public:
	MapScreen();
	~MapScreen();
};


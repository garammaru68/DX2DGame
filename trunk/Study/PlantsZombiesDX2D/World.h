#pragma once
#include "Object.h"
#include <list>

struct WorldObject
{
	RECT entity;
};

class World
{
private:
	Object background;
	Texture obstacle;
	std::list<WorldObject> objectList;
	int maxObstacle = 0;

public:
	void Initialize(std::wstring backgroundPath);
	void Render(RECT scope);
	void Release();

	int GetMaxObstacle() { return maxObstacle; }
	RECT GetObstacleRect(int index);
};
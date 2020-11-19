#pragma once
#include "Character.h"

class SunLight : public Character
{
public:
	void Initialize(Vector2D spawnPos, RECT worldRect);
	void Update(Vector2D pivot, float delta);
	void Render();
	void LoadGFX();

private:
	void Move(float delta);
	void UpdateRenderPos(Vector2D pivot);
};


#include "Camera.h"
#include <Graphics.h>

void Camera::Initialize(RECT scope, RECT worldRect, Vector2D pos)
{
	this->scopeRange = scope;
	border = worldRect;
	position = pos;
}

void Camera::Update(Vector2D target)
{
	scopeRange = { 0, 0, (LONG)Graphics::GetScreenWidth(), (LONG)Graphics::GetScreenHeight() };

	position = { 0, 0 };

	//if (position.x < scopeRange.right / 2)
	//	position.x = scopeRange.right / 2;
	//if (position.x > border.right - scopeRange.right / 2)
	//	position.x = border.right - scopeRange.right / 2;
	//if (position.y < scopeRange.bottom / 2)
	//	position.y = scopeRange.bottom / 2;
	//if (position.y > border.bottom - scopeRange.bottom / 2)
	//	position.y = border.bottom - scopeRange.bottom / 2;
}
#pragma once
#include "GMath.h"
#include <Windows.h>

class Camera
{
private:
	RECT scopeRange;
	RECT border;
	Vector2D position;

public:
	void Initialize(RECT scope, RECT worldRect, Vector2D pos);
	void Update(Vector2D target);

public:
	RECT GetScope() {
		return { LONG(position.x),
				LONG(position.y),
				LONG(position.x + scopeRange.right),
				LONG(position.y + scopeRange.bottom) };

		//return { LONG(position.x - scopeRange.right),
		//LONG(position.y - scopeRange.bottom),
		//LONG(position.x + scopeRange.right),
		//LONG(position.y + scopeRange.bottom) };

		//return { LONG(position.x - scopeRange.right / 2),
		//				LONG(position.y - scopeRange.bottom / 2),
		//				LONG(position.x + scopeRange.right / 2),
		//				LONG(position.y + scopeRange.bottom / 2) };
	}
	Vector2D GetPosition() { return position; }
};
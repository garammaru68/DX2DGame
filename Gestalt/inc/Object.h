#pragma once
#include "Texture.h"
#include "Gmath.h"

class Object
{
protected:
	Vector2D	position;
	Vector2D	renderPosition;
	Vector2D	direction;
	Vector2D displacement;
public:
	Texture texture;
public:
	void SetPosition(Vector2D pos) {
		this->position = pos;
	}
	void SetRenderPosition(Vector2D pos) {
		this->renderPosition = pos;
	}

	Vector2D GetPosition() {
		return position;
	}
	Vector2D GetRenderPosition() {
		return renderPosition;
	}
	Vector2D GetDisplacement() {
		return displacement;
	}
};
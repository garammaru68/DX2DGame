#pragma once
#include "Object.h"
#include <string>

class UI : public Object
{
private:
	Object* parent;
	Vector2D offset;
public:
	void Initialize(std::wstring imagePath,
		UINT width, UINT height, UINT NumFrame, UINT Line,
		Object* parent = nullptr,
		Vector2D offset = { 0, 0 });
	void Update();
	void Render();
};
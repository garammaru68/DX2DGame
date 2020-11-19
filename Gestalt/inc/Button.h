#pragma once
#include "Object.h"
#include <string>

class Button : public Object
{
public:
	enum class State {
		IDLE,
		HOVERED,
		PRESSED,
		DISABLED,
	};
private:
	Object* parent;
	Vector2D offset;
	State state;

	bool disabled;
	bool ptInButton;
public:
	bool pressed;
public:
	void Initialize(std::wstring imagePath,
		UINT width, UINT height, UINT NumFrame, UINT Line,
		Object* parent = nullptr,
		Vector2D offset = { 0, 0 });
	void Update(RECT cur);
	void Render();
	void UpdateCard(RECT cur);
	void RenderCard();
	bool IsPressed() { return state == State::PRESSED; }
	void Enable() { disabled = false; }
	void Disable() { disabled = true; }

};
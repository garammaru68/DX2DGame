#pragma once
#include <Windows.h>

class Mouse
{
	friend class MainWindow;
private:
	enum class State
	{
		FREE,
		DOWN,
		HOLD,
		RELEASE
	};
	static State lButtonState;
	static State rButtonState;
	static State oldLBState;
	static State oldRBState;
	static float pos_x;
	static float pos_y;
	static float wheel;

private:
	static void Update();
	static void OnLBPressed() { lButtonState = State::DOWN; }
	static void OnLBRelease() { lButtonState = State::RELEASE; }
	static void OnRBPressed() { rButtonState = State::DOWN; }
	static void OnRBRelease() { rButtonState = State::RELEASE; }
	static void OnMove(float x, float y) { pos_x = x, pos_y = y; }
	static void OnWheelScroll(float distance) { wheel = distance; }

public:
	static bool LBIsFree() { return lButtonState == State::FREE; }
	static bool LBIsDown() { return lButtonState == State::DOWN; }
	static bool LBIsHold() { return lButtonState == State::HOLD; }
	static bool LBIsRelease() { return lButtonState == State::RELEASE; }
	static bool RBIsFree() { return rButtonState == State::FREE; }
	static bool RBIsDown() { return rButtonState == State::DOWN; }
	static bool RBIsHold() { return rButtonState == State::HOLD; }
	static bool RBIsRelease() { return rButtonState == State::RELEASE; }

	static float GetPosX() { return pos_x; }
	static float GetPosY() { return pos_y; }

	static void SetPosX(float x_in) { pos_x = x_in; }
	static void SetPosY(float y_in) { pos_y = y_in; }
	static bool WheelIsUp();
	static bool WheelIsDown();
};

class Keyboard
{
	friend class MainWindow;
public:
	static constexpr UINT nKey = 256;
	enum class State
	{
		FREE,
		DOWN,
		HOLD,
		RELEASE
	};
	class Event
	{
	public:
		Keyboard::State state;
		DWORD key;
	};
private:
	static State stateTable[nKey];
	static State oldStateTable[nKey];

	static bool autoRepeat;

private:
	static void Update();
	static void OnKeyPress(DWORD key) { stateTable[key] = State::DOWN; }
	static void OnKeyRelease(DWORD key) { stateTable[key] = State::FREE; }

public:
	static bool KeyIsFree(DWORD key) { return stateTable[key] == State::FREE; }
	static bool KeyIsDown(DWORD key) { return stateTable[key] == State::DOWN; }
	static bool KeyIsHold(DWORD key) { return stateTable[key] == State::HOLD; }
	static bool KeyIsRelease(DWORD key) { return stateTable[key] == State::RELEASE; }

	static void EnableAutoRepeat() { autoRepeat = true; }
	static void DisableAutoRepeat() { autoRepeat = false; };
};
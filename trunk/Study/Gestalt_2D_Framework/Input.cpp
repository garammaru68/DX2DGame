#include "Input.h"

Mouse::State Mouse::lButtonState = State::FREE;
Mouse::State Mouse::rButtonState = State::FREE;
Mouse::State Mouse::oldLBState = Mouse::State::FREE;
Mouse::State Mouse::oldRBState = Mouse::State::FREE;
float Mouse::pos_x = 100.0f;
float Mouse::pos_y = 100.0f;
float Mouse::wheel = 0.0f;

void Mouse::Update()
{
	if (lButtonState == State::DOWN
		&& oldLBState == State::DOWN)
	{
		lButtonState = State::HOLD;
	}

	if (lButtonState == State::RELEASE
		&& oldLBState == State::RELEASE)
	{
		lButtonState = State::FREE;
	}

	if (rButtonState == State::DOWN
		&& oldLBState == State::DOWN)
	{
		rButtonState = State::HOLD;
	}

	if (rButtonState == State::DOWN
		&& oldLBState == State::DOWN)
	{
		rButtonState = State::HOLD;
	}

	oldLBState = lButtonState;
	oldRBState = rButtonState;
}

bool Mouse::WheelIsUp()
{
	if (wheel > 0.0f) {
		wheel = 0.0f;
		return true;
	}
	return false;
}

bool Mouse::WheelIsDown()
{
	if (wheel < 0.0f) {
		wheel = 0.0f;
		return true;
	}
	return false;
}

Keyboard::State Keyboard::stateTable[Keyboard::nKey] = {};
Keyboard::State Keyboard::oldStateTable[Keyboard::nKey] = {};
bool Keyboard::autoRepeat = false;

void Keyboard::Update()
{
	for (int iKey = 0; iKey < nKey; iKey++)
	{
		if (stateTable[iKey] == State::DOWN
			&& oldStateTable[iKey] == State::DOWN)
		{
			stateTable[iKey] = State::HOLD;
		}

		if (stateTable[iKey] == State::RELEASE
			&& oldStateTable[iKey] == State::RELEASE)
		{
			stateTable[iKey] = State::FREE;
		}

		oldStateTable[iKey] = stateTable[iKey];
	}
}
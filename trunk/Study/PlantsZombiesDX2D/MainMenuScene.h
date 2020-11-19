#pragma once
#include "Scene.h"
#include "Button.h"

class MainMenuScene : public Scene
{
private:
	Object background;
	Button startButton;
	Object cursor;
private:
	virtual void Initialize() override;
	virtual void Update(float delta) override;
	virtual void Render(float delta) override;

private:
	void UpdateElements();
};
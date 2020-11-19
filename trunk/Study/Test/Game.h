#pragma once
#include <MainWindow.h>
#include "Texture.h"

class Object
{
public:
	Texture texture;
};

class Game : public MainWindow
{
private:
	Object testObject;

public:
	Game(HINSTANCE hInstance);
	virtual void Update (float deltaTime) override;
	virtual void Render(float deltaTime) override;
};


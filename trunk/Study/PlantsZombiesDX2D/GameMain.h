#pragma once
#include <MainWindow.h>

class GameMain : public MainWindow
{
private:

public:
	GameMain(HINSTANCE hInstance);
	virtual void Update(float delta) override;
	virtual void Render(float delta) override;

};
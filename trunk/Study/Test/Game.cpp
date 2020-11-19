#include "Game.h"

Game::Game(HINSTANCE hInstance)
	:
	MainWindow(hInstance)
{
	testObject.texture.LoadTexture(Graphics::GetInstance().GetDevice(), L"Main.bmp");
	testObject.texture.LoadSprite(100, 100, 80);
}

void Game::Update(float deltaTime)
{
	
}

void Game::Render(float deltaTime)
{
	for (int iFrame = 0; iFrame < 8; iFrame++)
	{
		testObject.texture.SetFrame(iFrame);
		testObject.texture.SetDestRect({ (float)iFrame * 100, 0.0f, (float)iFrame * 100 + 100.0f, 100.0f });
		Graphics::GetInstance().mesh.Render(testObject.texture);
	}
}
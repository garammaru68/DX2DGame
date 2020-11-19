#include "MainMenuScene.h"
#include "SceneManager.h"
#include <Graphics.h>
#include <Input.h>
#include "GlobalSetting.h"
#include "BattlefieldScene.h"

void MainMenuScene::Initialize()
{
	background.texture.LoadTexture(Graphics::GetInstance().GetDevice(), L"../../../data/DX2D/resource/Main.bmp");

	startButton.Initialize(L"../../../data/DX2D/resource/startBar.bmp", 330, 75, 2, 1,
							&background, { (float)Graphics::GetScreenWidth() / 2 - 165, (float)Graphics::GetScreenHeight() - 75.0f });
}
void MainMenuScene::Update(float delta)
{
	UpdateElements();

	if (startButton.IsPressed())
	{
		SceneManager::GetInstance().SwapScene(new BattlefieldScene);

		return;
	}
	//if (exitButton.IsPressed())
	//{
	//	PostQuitMessage(0);
	//}
}
void MainMenuScene::Render(float delta)
{
	Graphics::GetInstance().mesh.Render(background.texture);
	startButton.Render();
	//exitButton.Render();
	//Graphics::GetInstance().mesh.Render(cursor.texture);
}
void MainMenuScene::UpdateElements()
{
	background.texture.SetDestRect({ 0, 0, (float)Graphics::GetScreenWidth(), (float)Graphics::GetScreenHeight() });

	cursor.texture.SetDestRect({
		Mouse::GetPosX() - cursor.texture.GetWidth() / 2,
		Mouse::GetPosY() - cursor.texture.GetHeight() / 2,
		Mouse::GetPosX() + cursor.texture.GetWidth() / 2,
		Mouse::GetPosY() + cursor.texture.GetHeight() / 2 });

	RECT cursorRect = {
		cursor.texture.GetDestRect().left - cursor.texture.GetWidth() / 2,
		cursor.texture.GetDestRect().top - cursor.texture.GetHeight() / 2,
		cursor.texture.GetWidth(),
		cursor.texture.GetHeight()
	};

	startButton.Update(cursorRect);
	//exitButton.Update(cursorRect);
}
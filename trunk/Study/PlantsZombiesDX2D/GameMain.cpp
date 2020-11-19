#include "GameMain.h"
#include "SceneManager.h"
#include "MainMenuScene.h"

GameMain::GameMain(HINSTANCE hInstance) : MainWindow(hInstance)
{
	SceneManager::GetInstance().Initialize(new MainMenuScene);
}
void GameMain::Update(float delta)
{
	SceneManager::GetInstance().Update(0.008);
}
void GameMain::Render(float delta)
{
	SceneManager::GetInstance().Render(0.008);
}
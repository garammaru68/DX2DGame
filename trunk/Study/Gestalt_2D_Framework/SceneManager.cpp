#include "SceneManager.h"

void SceneManager::Initialize(Scene* initialScene)
{
	currentScene = initialScene;
	currentScene->Initialize();
}
void SceneManager::Update(float delta)
{
	return currentScene->Update(delta);
}
void SceneManager::Render(float delta)
{
	currentScene->Render(delta);
}
void SceneManager::Release()
{
	currentScene->Release();
}
void SceneManager::SwapScene(Scene* nextScene)
{
	currentScene->Release();
	delete currentScene;
	currentScene = nextScene;
	currentScene->Initialize();
	currentScene->Update(0.016f);
}
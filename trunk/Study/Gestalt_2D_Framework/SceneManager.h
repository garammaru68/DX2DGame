#pragma once
#include "Scene.h"

class SceneManager
{
private:
	Scene* currentScene;
private:
	SceneManager() {}
public:
	static SceneManager& GetInstance() {
		static SceneManager mgr;
		return mgr;
	}
public:
	void Initialize(Scene* initialScene);
	void Update(float delta);
	void Render(float delta);
	void Release();
	void SwapScene(Scene* nextScene);
};
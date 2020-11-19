#pragma once
class Scene
{
	friend class SceneManager;
protected:
	virtual void Initialize() = 0;
	virtual void Update(float delta) = 0;
	virtual void Render(float delta) = 0;
	virtual void Release() {};

public:
	virtual ~Scene() {}
};
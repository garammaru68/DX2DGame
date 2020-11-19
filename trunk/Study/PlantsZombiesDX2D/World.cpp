#include "World.h"

#include <Graphics.h>

void World::Initialize(std::wstring backgroundPath)
{
	background.texture.LoadTexture(Graphics::GetInstance().GetDevice(), backgroundPath);
	obstacle.LoadTexture(Graphics::GetInstance().GetDevice(), backgroundPath);
	background.texture.SetDestRect({ 0, 0, (float)Graphics::GetScreenWidth(), (float)Graphics::GetScreenHeight() });
}

void World::Render(RECT scope)
{
	background.texture.SetDestRect({ 0, 0, (float)Graphics::GetScreenWidth(), (float)Graphics::GetScreenHeight() });
	background.texture.SetSrcRect({ (float)scope.left, (float)scope.top, (float)scope.right, (float)scope.bottom });
	Graphics::GetInstance().mesh.Render(background.texture);
}

RECT World::GetObstacleRect(int index)
{
	obstacle.SetFrame(index);
	RECT res = { obstacle.GetSrcRect().left, obstacle.GetSrcRect().top, obstacle.GetSingleWidth(index), obstacle.GetSingleHeight(index) };
	return res;
}
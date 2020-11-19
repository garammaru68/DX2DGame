#include "SunLight.h"
#include "Collision.h"
#include <Graphics.h>

void SunLight::Initialize(Vector2D spawnPos, RECT worldRect)
{
	bodyWidth = 28;
	bodyHeight = 30;

	movementSpeed = 150.0f;
	SetPosition(spawnPos);
	LoadGFX();
}
void SunLight::Update(Vector2D pivot, float delta)
{
	Move(delta);
	UpdateRenderPos(pivot);
}
void SunLight::Render()
{
	Graphics::GetInstance().mesh.Render(texture);
}
void SunLight::LoadGFX()
{
	texture.LoadTexture(Graphics::GetInstance().GetDevice(), L"../../../data/DX2D/resource/Sunlight.bmp");
	texture.LoadSprite(28, 30, 1, 1);
}

void SunLight::Move(float delta)
{
	direction.y = 1;

	position.x += delta * direction.x * movementSpeed;
	position.y += delta * direction.y * movementSpeed;
}

void SunLight::UpdateRenderPos(Vector2D pivot)
{
	Vector2D screenGap = { Graphics::GetScreenWidth() / 2 - pivot.x, Graphics::GetScreenHeight() / 2 - pivot.y };
	renderPosition = position;
	renderPosition.x -= texture.GetSingleWidth() / 2.0f;
	renderPosition.y -= texture.GetSingleHeight() / 2.0f;
	texture.SetDestRect({
		renderPosition.x,
		renderPosition.y,
		renderPosition.x + texture.GetSingleWidth() * 1.3f,
		renderPosition.y + texture.GetSingleHeight() * 1.3f });
}

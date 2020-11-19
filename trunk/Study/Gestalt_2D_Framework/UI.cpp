#include "UI.h"
#include "Graphics.h"
#include "GlobalSetting.h"
#include "Input.h"

void UI::Initialize(std::wstring imagePath,
	UINT width, UINT height, UINT NumFrame, UINT Line,
	Object* parent,
	Vector2D offset)
{
	texture.LoadTexture(Graphics::GetInstance().GetDevice(), imagePath);
	texture.LoadSprite(width, height, NumFrame, Line);

	if (parent) this->parent = parent;
	this->offset = offset;
}
void UI::Update()
{
	if (parent)
	{
		position = parent->GetRenderPosition() + offset;
	}
	else
	{
		position = offset;
	}
	texture.SetDestRect({ position.x, position.y, position.x + texture.GetSingleWidth(), position.y + texture.GetSingleHeight() });
}
void UI::Render()
{
	//texture.SetFrame(0);
	Graphics::GetInstance().mesh.Render(texture);
}
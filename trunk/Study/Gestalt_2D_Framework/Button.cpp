#include "Button.h"
#include "Graphics.h"
#include "GlobalSetting.h"
#include "Collision.h"
#include "Input.h"

void Button::Initialize(std::wstring imagePath,
	UINT width, UINT height, UINT NumFrame, UINT Line,
	Object* parent,
	Vector2D offset)
{
	texture.LoadTexture(Graphics::GetInstance().GetDevice(), imagePath);
	texture.LoadSprite(width, height, NumFrame, Line);

	if (parent) this->parent = parent;
	this->offset = offset;

	pressed = false;
	disabled = false;
}
void Button::Update(RECT cur)
{
	if (parent)
	{
		position = parent->GetRenderPosition() + offset;
	}
	else
	{
		position = offset;
	}
	texture.SetDestRect({ position.x, position.y, 
		(position.x + texture.GetSingleWidth()), (position.y + texture.GetSingleHeight()) });

	if (state == State::DISABLED)
	{
		return;
	}

	if (Collision::RectToRect({ (LONG)position.x, (LONG)position.y, (LONG)texture.GetSingleWidth(), (LONG)texture.GetSingleHeight() }, cur))
	{
		if (ptInButton == false)
		{
			ptInButton = true;
		}
		state = State::HOVERED;

		if (Mouse::LBIsHold() && pressed == false)
		{
			pressed = true;
			state = State::PRESSED;
		}
		if (Mouse::LBIsHold() == false)
		{
			pressed = false;
		}
	}
	else
	{
		ptInButton = false;
		state = State::IDLE;
	}
}
void Button::Render()
{
	switch (state)
	{
	case State::IDLE: texture.SetFrame(0); break;
	case State::HOVERED: texture.SetFrame(1);  break;
	case State::PRESSED: texture.SetFrame(1);  break;
	case State::DISABLED: texture.SetFrame(0);  break;
	}
	Graphics::GetInstance().mesh.Render(texture);
}
void Button::UpdateCard(RECT cur)
{
	if (parent)
	{
		position = parent->GetRenderPosition() + offset;
	}
	else
	{
		position = offset;
	}
	texture.SetDestRect({ position.x, position.y,
		(position.x + texture.GetSingleWidth()), (position.y + texture.GetSingleHeight()) });

	if (state == State::DISABLED)
	{
		return;
	}

	if (Collision::RectToRect({ (LONG)position.x, (LONG)position.y, (LONG)texture.GetSingleWidth(), (LONG)texture.GetSingleHeight() }, cur))
	{
		if (ptInButton == false)
		{
			ptInButton = true;
		}
		state = State::HOVERED;

		if (Mouse::LBIsHold() && pressed == false)
		{
			pressed = true;
			state = State::PRESSED;
		}
		//if (Mouse::LBIsHold() && pressed == true)
		//{
		//	pressed = false;
		//	state = State::IDLE;
		//}

		if (Mouse::LBIsHold() == false)
		{
			pressed = false;
		}
	}
	else
	{
		ptInButton = false;
		state = State::IDLE;
	}
}
void Button::RenderCard()
{
	switch (state)
	{
	case State::IDLE:  break;
	case State::HOVERED:   break;
	case State::PRESSED:   break;
	case State::DISABLED:  break;
	}
	Graphics::GetInstance().mesh.Render(texture);
}

#include "Plants.h"
#include "Collision.h"
#include <Graphics.h>

void Plants::Initialize(float width, float height, Vector2D spawnPos, std::wstring imagePath,
						UINT NumFrame, UINT Line)
{
	bodyWidth = width;
	bodyHeight = height;

	maxHealth = 100.0f;
	health = 100.0f;
	meleeDamage = 10.0f;

	alive = true;
	targetFound = false;

	SetPosition(spawnPos);

	LoadGFX(imagePath, width, height, NumFrame, Line);
}
void Plants::InitializeTest(Vector2D spawnPos)
{
	bodyWidth = 36;
	bodyHeight = 30;

	maxHealth = 100.0f;
	health = 100.0f;
	meleeDamage = 10.0f;

	alive = true;
	targetFound = false;

	SetPosition(spawnPos);

	LoadGFX();
}
void Plants::Update(Vector2D pivot, float delta, int idleFrom, int idleTo, int attackFrome, int attackTo)
{
	Move(delta);

	UpdateStatus();
	UpdateTimers(delta);
	UpdateState();
	UpdateModel(delta, idleFrom, idleTo, attackFrome, attackTo);
	UpdateRenderPos(pivot);
}

void Plants::Render(float delta)
{
	Graphics::GetInstance().mesh.Render(texture);
}

void Plants::LoadGFX(std::wstring imagePath, UINT width, UINT height, UINT NumFrame, UINT Line)
{
	texture.LoadTexture(Graphics::GetInstance().GetDevice(), imagePath);
	texture.LoadSprite(width, height, NumFrame, Line);
}
void Plants::LoadGFX()
{
	texture.LoadTexture(Graphics::GetInstance().GetDevice(), L"../../../data/DX2D/resource/PeaShooter.bmp");
	texture.LoadSprite(36, 30, 13, 1);
}
void Plants::Move(float delta)
{
	if (invincibleTimer <= 0.0f)
	{
		if (targetFound) Attack();
	}

	position.x += delta * direction.x * movementSpeed;
	position.y += delta * direction.y;
	//if (position.x < mapBorder.left + bodyWidth) position.x = mapBorder.left + bodyWidth;
	//if (position.x > mapBorder.right - bodyWidth) position.x = mapBorder.right - bodyWidth;
}

void Plants::Attack()
{
	if (attackTimer <= 0.0f) attackTimer = 0.3f;
}

void Plants::UpdateStatus()
{
	sightRange = {
		LONG(position.x - sight / 2),
		LONG(position.y - sight / 2),
		LONG(sight),
		LONG(sight)
	};

	if (health <= 0.0f) alive = false;
}

void Plants::UpdateTimers(float delta)
{
	if (attackTimer > 0.0f) {
		attackTimer -= delta;
		if (facingLeft)
			attackRect = {
				   LONG(position.x - (bodyWidth / 2) - attackRange) ,
				   LONG(position.y - bodyHeight / 2),
				   LONG(attackRange + bodyWidth / 2),
				   LONG(attackRange * 2)
		};
		else
			attackRect = {
				   LONG(position.x),
				   LONG(position.y - bodyHeight / 2),
				   LONG(attackRange + bodyWidth / 2),
				   LONG(attackRange * 2)
		};
	}
	else {
		attackRect = { 0, 0, 0, 0 };
	}
	if (invincibleTimer > 0.0f) invincibleTimer -= delta;
}

void Plants::UpdateState()
{
	if (attackTimer > 0.0f) {
		state = ActionState::ATTACK;
	}
	if (movementSpeed == defaultSpeed) state = ActionState::IDLE;
	//else if (direction.y == 0) {
	//}
}


void Plants::UpdateRenderPos(Vector2D pivot)
{
	Vector2D screenGap = { Graphics::GetScreenWidth() / 2 - pivot.x, Graphics::GetScreenHeight() / 2 - pivot.y };
	renderPosition = position;
	renderPosition.x -= texture.GetSingleWidth() / 2.0f;
	renderPosition.y -= texture.GetSingleHeight() / 2.0f;
	texture.SetDestRect({
		renderPosition.x,
		renderPosition.y,
		renderPosition.x + texture.GetSingleWidth() * 2.5f,
		renderPosition.y + texture.GetSingleHeight() * 2.5f});
}

void Plants::UpdateModel(float delta, int idleFrom, int idleTo, int attackFrome, int attackTo)
{
	switch (state)
	{
	case ActionState::IDLE:
	{
		frameFrom = idleFrom;
		frameTo = idleTo;
	}
	frameDelay = 13 * delta;
	loop = true;
	break;
	case ActionState::ATTACK:
	{
		frameFrom = attackFrome;
		frameTo = attackTo;
	}
	frameDelay = 2 * delta;
	loop = true;
	break;
	}

	if (state != tmpState) {
		currentFrame = frameFrom;
		tmpState = state;
		elapsed = 0.0f;
	}

	texture.SetFrame(currentFrame);

	elapsed += frameDelay;
	if (elapsed > 1.0f) {
		if (++currentFrame > frameTo)
		{
			if (loop) currentFrame = frameFrom;
			else currentFrame = frameTo;
		}
		elapsed -= 1.0f;
	}
}

void Plants::HitNothing()
{
	if (direction.y == 0) direction.y = 1;
}

bool Plants::GetHit(float damage)
{
	if (invincibleTimer > 0.0f) return false;
	health -= damage;
	invincibleTimer = maxInvincibleTime;
	if (health <= 0.0f) return true;
	return false;
}

void Plants::FoundTarget(Vector2D target)
{
	targetFound = true;
	destination = target;
}

void Plants::LostTarget()
{
	targetFound = false;
	destination = Vector2D(-1, -1);
}
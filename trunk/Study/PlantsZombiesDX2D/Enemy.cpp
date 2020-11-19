#include "Enemy.h"
#include "Collision.h"
#include <Graphics.h>

void Enemy::Initialize(Vector2D spawnPos, RECT worldRect)
{
	bodyWidth = 120;
	bodyHeight = 220;

	defaultSpeed = 40.0f;
	movementSpeed = defaultSpeed;
	maxHealth = 100.0f;
	health = 100.0f;
	meleeDamage = 10.0f;

	alive = true;
	targetFound = false;

	SetPosition(spawnPos);

	LoadGFX();
}

void Enemy::Update(Vector2D pivot, float delta)
{
	Move(delta);

	UpdateStatus();
	UpdateTimers(delta);
	UpdateState();
	UpdateModel(delta);
	//UpdatePos(pivot);
	UpdateRenderPos(pivot);
}

void Enemy::Render(float delta)
{
	Graphics::GetInstance().mesh.Render(texture);
}

void Enemy::LoadGFX()
{
	texture.LoadTexture(Graphics::GetInstance().GetDevice(), L"../../../data/DX2D/resource/Zombie.bmp");
	texture.LoadSprite(180, 220, 15, 4);
}

void Enemy::Move(float delta)
{
	if (invincibleTimer <= 0.0f)
	{
		if (targetFound)
		{
			direction.x = 0;
			Attack();
		}
		else
		{
			direction.x = -1;
		}
	}
	position.x += delta * direction.x * movementSpeed;
	position.y += delta * direction.y;
}

void Enemy::Attack()
{
	if (attackTimer <= 0.0f) attackTimer = 0.3f;
}

void Enemy::UpdateStatus()
{
	sightRange = {
		LONG(position.x - sight / 2),
		LONG(position.y - sight / 2),
		LONG(sight),
		LONG(sight)
	};

	if (health <= 0.0f) alive = false;
}

void Enemy::UpdateTimers(float delta)
{
	if (attackTimer > 0.0f) {
		attackTimer -= delta;
		attackRect = { LONG(position.x - bodyWidth / 2),
						LONG(position.y - bodyHeight / 2),
						LONG(bodyWidth),
						LONG(bodyHeight) };
	}
	else {
		attackRect = { 0, 0, 0, 0 };
	}
	if (invincibleTimer > 0.0f) invincibleTimer -= delta;
}

void Enemy::UpdateState()
{
	if (attackTimer > 0.0f) {
		state = ActionState::ATTACK;
	}
	if (movementSpeed == defaultSpeed) state = ActionState::WALK;
	//else if (direction.y == 0) {
	//}
}

void Enemy::UpdateRenderPos(Vector2D pivot)
{
	Vector2D screenGap = { Graphics::GetScreenWidth() / 2 - pivot.x, Graphics::GetScreenHeight() / 2 - pivot.y };
	renderPosition = position;
	renderPosition.x -= texture.GetSingleWidth() / 2.0f;
	renderPosition.y -= texture.GetSingleHeight() / 2.0f;
	texture.SetDestRect({
		renderPosition.x,
		renderPosition.y,
		renderPosition.x + texture.GetSingleWidth() * 0.6f,
		renderPosition.y + texture.GetSingleHeight() * 0.6f });
}

void Enemy::UpdateModel(float delta)
{
	switch (state)
	{
	case ActionState::WALK:
		{
			frameFrom = 0;
			frameTo = 32;
		}
		frameDelay = 20 * delta;
		loop = true;
		break;
	case ActionState::ATTACK:
		{
			frameFrom = 33;
			frameTo = 56;
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

void Enemy::HitGround(float height)
{
}

void Enemy::HitNothing()
{
	if (direction.y == 0) direction.y = 1;
}

bool Enemy::GetHit(float damage)
{
	if (invincibleTimer > 0.0f) return false;
	health -= damage;
	invincibleTimer = maxInvincibleTime;
	if (health <= 0.0f) return true;
	return false;
}

void Enemy::FoundTarget(Vector2D target)
{
	targetFound = true;
	destination = target;
}

void Enemy::LostTarget()
{
	targetFound = false;
	destination = Vector2D(-1, -1);
}
#include "Player.h"
#include <Input.h>
#include <Graphics.h>
#include <stdlib.h>

#define GRAVITY 9.8

void Player::Initialize(Vector2D pos, RECT worldRect)
{
	bodyWidth = 44;
	bodyHeight = 124;
	defaultSpeed = 200.0f;
	movementSpeed = defaultSpeed;

	maxHealth = 100.0f;
	health = 100.0f;
	meleeDamage = 10.0f;
	currentDamage = meleeDamage;
	alive = true;


	mapBorder = worldRect;
	SetPosition(pos);

	LoadGFX();
}

void Player::Update(Vector2D pivot, float delta)
{
	if (!dying)
	{
		GetInput();
		Move(delta);

		UpdateRenderPos(pivot);
	}
	UpdateState();
	UpdateStatus(delta);
	UpdateTimers(delta);
	UpdateModel(delta);
}

void Player::Render(float delta)
{
	Graphics::GetInstance().mesh.Render(this->texture);

	static Vector2D prevPos = position;
	displacement = position - prevPos;
	if (position.x < Graphics::GetScreenWidth() / 2 || position.x > mapBorder.right - Graphics::GetScreenWidth() / 2)
		displacement.x = 0.0f;
	if (position.y < Graphics::GetScreenHeight() / 2 || position.y > mapBorder.bottom - Graphics::GetScreenHeight() / 2)
		displacement.y = 0.0f;
	prevPos = position;

}

void Player::LoadGFX()
{
	texture.LoadTexture(Graphics::GetInstance().GetDevice(), L"../../../data/DX2D/resource/PeaShooterIdle.bmp");
	//texture.LoadScript(L"../../../../Script/adventurer_player.txt");
}


static bool clicked = false;
static float attackTimer = 0.0f;
static float leftKeyTimer = 0.0f;
static float rightKeyTimer = 0.0f;
static bool leftKeyUp = true;
static bool rightKeyUp = true;
static float hitTimer = 0.0f;

void Player::GetInput()
{
	if (Mouse::LBIsHold() == false)
	{
		clicked = false;
	}

	if (Keyboard::KeyIsHold('A') && attackTimer <= 0.0f)
	{
		if (leftKeyUp) leftKeyTimer += 0.2f;
		leftKeyUp = false;
		facingLeft = true;
		direction.x = -1;
	}
	else if (Keyboard::KeyIsHold('D') && attackTimer <= 0.0f)
	{
		if (rightKeyUp) rightKeyTimer += 0.2f;
		rightKeyUp = false;
		facingLeft = false;
		direction.x = 1;
	}
	else direction.x = 0;
}

void Player::Move(float delta)
{
	position.x += delta * direction.x * movementSpeed;
	position.y += delta * direction.y;

	if (position.x < mapBorder.left + bodyWidth) position.x = mapBorder.left + bodyWidth;
	if (position.x > mapBorder.right - bodyWidth) position.x = mapBorder.right - bodyWidth;
}

void Player::Attack()
{
	if (attackTimer <= 0.0f) attackTimer = 0.3f;
}

void Player::UpdateStatus(float delta)
{
	static float statusUpdater = 0.0f;
	static float stepTimer = 0.0f;
	static bool runFlag = false;
	statusUpdater += delta;
	stepTimer += delta;

	if (statusUpdater > 1.0f)
	{
		statusUpdater = 0.0f;
		health += 1.0f;
		if (health > maxHealth)
			health = maxHealth;
	}

	if (health <= 0.0f) dying = true;
	if (deathTimer <= 0.0f) alive = false;
	meleeDamage = currentDamage;
}

void Player::UpdateTimers(float delta)
{
	if (attackTimer > 0.0f) {
		attackTimer -= delta;
		if (facingLeft)
			attackRect = {
				   LONG(position.x - (bodyWidth / 2) - attackRange),
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
	if (leftKeyTimer > 0.0f) leftKeyTimer -= delta;
	if (rightKeyTimer > 0.0f) rightKeyTimer -= delta;
	if (invincibleTimer > 0.0f) invincibleTimer -= delta;
	if (hitTimer > 0.0f) hitTimer -= delta;
	if (dying) deathTimer -= delta;
}

void Player::UpdateState()
{
	if (dying) state = ActionState::DEAD;
	else if (attackTimer > 0.0f)
	{
		state = ActionState::ATTACK1;
	}

	else if(direction.y == 0) {
		if (direction.x == 0) 	state = ActionState::IDLE;
		else if (movementSpeed == defaultSpeed) state = ActionState::WALK;
	}
}

void Player::UpdateRenderPos(Vector2D pivot)
{
	Vector2D screenGap = { Graphics::GetScreenWidth() / 2 - pivot.x, Graphics::GetScreenHeight() / 2 - pivot.y };
	renderPosition = position + screenGap;
	renderPosition.x -= texture.GetSingleWidth() / 2;
	renderPosition.y -= texture.GetSingleHeight() / 2 + 8;
	texture.SetDestRect({
		renderPosition.x,
		renderPosition.y,
		renderPosition.x + texture.GetSingleWidth() ,
		renderPosition.y + texture.GetSingleHeight() });
}

void Player::UpdateModel(float delta)
{
	static int frameFrom = 0;
	static int frameTo = 0;
	static float frameDelay = 0;
	static bool loop = true;

	switch (state)
	{
	case ActionState::IDLE:
		if (facingLeft) {
			frameFrom = 76;
			frameTo = 79;
		}
		else {
			frameFrom = 16;
			frameTo = 19;
		}
		frameDelay = 6;
		loop = true;
		break;
	case ActionState::WALK:
		if (facingLeft) {
			frameFrom = 60;
			frameTo = 65;
		}
		else {
			frameFrom = 0;
			frameTo = 5;
		}
		frameDelay = 6;
		loop = true;
		break;
	case ActionState::ATTACK1:
		if (facingLeft) {
			frameFrom = 80;
			frameTo = 85;
		}
		else {
			frameFrom = 20;
			frameTo = 25;
		}
		frameDelay = 16;
		loop = false;
		break;
	case ActionState::DEAD:
		if (facingLeft) {
			frameFrom = 97;
			frameTo = 106;
		}
		else {
			frameFrom = 37;
			frameTo = 46;
		}
		frameDelay = 5;
		loop = false;
		break;
	}

	static int currentFrame = 0;
	static float elapsed = 0.0f;

	static ActionState tmpState = ActionState::IDLE;
	if (state != tmpState) {
		currentFrame = frameFrom;
		tmpState = state;
		elapsed = 0.0f;
	}

	texture.SetFrame(currentFrame);

	elapsed += frameDelay * delta;
	if (elapsed > 1.0f) {
		if (++currentFrame > frameTo)
		{
			if (loop) currentFrame = frameFrom;
			else currentFrame = frameTo;
		}
		elapsed -= 1.0f;
	}
}

void Player::HitEnemy()
{
	if (hitTimer <= 0.0f)
	{
		hitTimer = 0.3f;
	}
}

void Player::HitNothing()
{
}

void Player::GetHit(float damage, bool left)
{
	if (invincibleTimer > 0.0f || dying) return;
	health -= damage;
	invincibleTimer = maxInvincibleTime;
	movementSpeed = defaultSpeed;
}
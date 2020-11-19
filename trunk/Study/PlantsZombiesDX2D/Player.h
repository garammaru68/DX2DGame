#pragma once
#include "Character.h"

class Player : public Character
{
public:
	enum class ActionState {
		IDLE,
		WALK,
		ATTACK1,
		HIT,
		DEAD
	};
private:
	static constexpr float maxInvincibleTime = 1.0f;
	float currentDamage;

	RECT mapBorder;

	float attackRange = 50.0f;
	RECT attackRect;

	ActionState state;
	bool dying = false;

	float invincibleTimer = 0.0f;
	float deathTimer = 2.0f;

private:
	void GetInput();
	void Move(float delta);
	void Attack();

	void UpdateStatus(float delta);
	void UpdateTimers(float delta);
	void UpdateState();
	void UpdateRenderPos(Vector2D pivot);
	void UpdateModel(float delta);

public:
	void Initialize(Vector2D pos, RECT worldRect);
	void Update(Vector2D pivot, float delta);
	void Render(float delta);
	void LoadGFX();

public:
	RECT GetAttackRect() { return attackRect; }
	void HitEnemy();
	void HitNothing();
	void GetHit(float damage, bool left);
};
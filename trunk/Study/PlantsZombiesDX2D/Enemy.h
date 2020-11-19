#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	enum class ActionState {
		WALK,
		ATTACK
	};
private:

	static constexpr float attackRange = 50.0f;
	static constexpr float maxInvincibleTime = 0.3f;
	float invincibleTimer = 0.0f;
	float sight = 100.0f;

	ActionState state;

	RECT attackRect;
	RECT sightRange;
	bool targetFound;

	Vector2D destination = { -1, -1 };

	float attackTimer = 0.0f;

	int frameFrom = 0;
	int frameTo = 0;
	float frameDelay = 0;
	bool loop = true;
	int currentFrame = 0;
	float elapsed = 0.0f;
	ActionState tmpState = ActionState::WALK;
	bool tmpDirectionX = false;

private:
	void Move(float delta);
	void Attack();

	void UpdateStatus();
	void UpdateTimers(float delta);
	void UpdateState();
	void UpdateRenderPos(Vector2D pivot);
	void UpdateModel(float delta);

public:
	void Initialize(Vector2D spawnPos, RECT worldRect);
	void Update(Vector2D pivot, float delta);
	void Render(float delta);
	void LoadGFX();

public:
	bool IsChasing() { return targetFound; }
	RECT GetSightRange() { return sightRange; }
	RECT GetAttackRect() { return attackRect; }

	void HitGround(float height);
	void HitNothing();
	bool GetHit(float damage);
	void FoundTarget(Vector2D target);
	void LostTarget();
};
#pragma once
#include "Character.h"

class Plants : public Character
{
public:
	enum class ActionState {
		IDLE,
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
	ActionState tmpState = ActionState::IDLE;
	bool tmpDirectionX = false;

private:
	void Move(float delta);
	void Attack();

	void UpdateStatus();
	void UpdateTimers(float delta);
	void UpdateState();
	void UpdateRenderPos(Vector2D pivot);
	void UpdateModel(float delta, int idleFrom, int idleTo, int attackFrome, int attackTo);

public:
	void Initialize(float width, float height, Vector2D spawnPos, std::wstring imagePath,
					UINT NumFrame, UINT Line);
	void InitializeTest(Vector2D spawnPos);
	void Update(Vector2D pivot, float delta, int idleFrom, int idleTo, int attackFrome, int attackTo);
	void Render(float delta);
	void LoadGFX(std::wstring imagePath, UINT width, UINT height, UINT NumFrame, UINT Line);
	void LoadGFX();

public:
	bool IsChasing() { return targetFound; }
	RECT GetSightRange() { return sightRange; }
	RECT GetAttackRect() { return attackRect; }

	void HitNothing();
	bool GetHit(float damage);
	void FoundTarget(Vector2D target);
	void LostTarget();
};
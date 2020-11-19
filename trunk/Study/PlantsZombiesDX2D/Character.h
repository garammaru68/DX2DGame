#pragma once
#include "Object.h"

class Character : public Object
{
protected:
	int bodyWidth;
	int bodyHeight;
	float movementSpeed;
	float defaultSpeed;

	float health;
	float maxHealth;
	float meleeDamage;
	float rangeDamage;
	float magicDamage;

	bool alive;
	bool facingLeft;

public:
	float GetHP() const { return health; }
	float GetMaxHP() const { return maxHealth; }

	RECT GetHitBox() const {
		//return { LONG(position.x),
		//		LONG(position.y),
		//		LONG(position.x) + LONG(bodyWidth),
		//		LONG(position.y) + LONG(bodyHeight) };
		return { LONG(position.x - bodyWidth / 2),
						LONG(position.y - bodyHeight / 2),
						LONG(bodyWidth),
						LONG(bodyHeight) };
	}

	float GetMeleeDamage() const { return meleeDamage; }
	float GetRangeDamage() const { return rangeDamage; }
	float GetMagicDamage() const { return magicDamage; }

	bool IsAlive() const { return alive; }

	void RegenerateHP(float amount) {
		health += amount;
		if (health > maxHealth)
			health = maxHealth;
	}
};
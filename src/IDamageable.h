#pragma once
class IDamageable
{
public:
	virtual void TakeDamage(int damage) = 0;
	virtual void Heal(int healAmount) = 0;
};

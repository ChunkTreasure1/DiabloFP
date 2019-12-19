#include "pch.h"
#include "Enemy.h"

namespace Diablo
{
	EnemyChoice Enemy::GetCombatChoice()
	{
		float tempHealthPercent = myHealth / myMaxHealth;

		if (tempHealthPercent > 0.25)
		{
			return EnemyChoice::Attack;
		}
		else
		{
			return EnemyChoice::Defend;
		}

		return EnemyChoice();
	}
}
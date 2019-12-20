#include "pch.h"
#include "EnemyFactory.h"

#include "Gameplay/Items/HealthPotion.h"
#include "Gameplay/Items/Scroll.h"
#include "Gameplay/Items/Tome.h"

#include "Gameplay/Fighting/Attacks/Axe.h"
#include "Gameplay/Fighting/Attacks/Sword.h"
#include "Gameplay/Fighting/Attacks/Spell.h"

#include "Gameplay/LevelSystem.h"

namespace Diablo
{
	Ref<Enemy> EnemyFactory::Create(const glm::vec2& aCharPos)
	{
		//Generate stats
		int tempDiff = LevelSystem::GetDifficulty();

		Ref<Enemy> tempEnemy = CreateRef<Enemy>(8.f);
		tempEnemy->SetCharPos(aCharPos);

		std::tuple<Stats, std::string, Ref<Attack>> tempTuple = GetEnemyStats();
		tempEnemy->SetStats(std::get<0>(tempTuple));
		tempEnemy->SetName(std::get<1>(tempTuple));

		tempEnemy->SetAttack(std::get<2>(tempTuple));
		tempEnemy->SetHealth(tempEnemy->GetHealth() * tempEnemy->GetStats().Constitution);

		uint32_t tempXP = rand() % tempDiff * 10 + 2;
		tempEnemy->SetKillXP(tempXP);

		if ((rand() % 100 + 1) <= 50)
		{
			float tempVal = (float)(rand() % 100 + 1);
			tempVal /= 100.f;

			Ref<Item> tempItem;
			if (tempVal <= 0.7f)
			{
				tempItem = CreateRef<HealthPotion>();
				auto tempI = std::dynamic_pointer_cast<HealthPotion>(tempItem);
				tempI->SetAddAmount((float)(rand() % 20 + 10));
			}
			else if (tempVal > 0.7f && tempVal < 0.9f)
			{
				tempItem = CreateRef<Scroll>();
			}
			else if (tempVal > 0.95f)
			{
				tempItem = CreateRef<Tome>();
			}

			tempEnemy->SetLoot(std::move(tempItem));
		}

		return tempEnemy;
	}

	std::tuple<Stats, std::string, Ref<Attack>> EnemyFactory::GetEnemyStats()
	{
		Stats tempStats = Stats();
		std::string tempName;
		Ref<Attack> tempAttack;

		int tempVal = rand() % 3 + 1;
		if (tempVal == 1)
		{
			tempStats.Agility = rand() % 5 + 2;
			tempStats.Charisma = rand() % 6 + 1;
			tempStats.Constitution = rand() % 7 + 4;

			tempStats.Defence = rand() % 8 + 3;
			tempStats.Intelligence = rand() % 5 + 1;

			tempStats.Strength = rand() % 8 + 4;
			tempStats.Wisdom = rand() % 4 + 1;

			tempAttack = CreateRef<Axe>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Strength / 4));

			tempName = "Orch";
		}
		else if (tempVal == 2)
		{
			tempStats.Agility = rand() % 6 + 2;
			tempStats.Charisma = rand() % 7 + 3;
			tempStats.Constitution = rand() % 3 + 1;

			tempStats.Defence = rand() % 4 + 1;
			tempStats.Intelligence = rand() % 6 + 2;

			tempStats.Strength = rand() % 4 + 1;
			tempStats.Wisdom = rand() % 6 + 2;

			tempAttack = CreateRef<Sword>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Strength / 1));

			tempName = "Goblin";
		}
		else if (tempVal == 3)
		{
			tempStats.Agility = rand() % 6 + 2;
			tempStats.Charisma = rand() % 8 + 3;
			tempStats.Constitution = rand() % 5 + 1;

			tempStats.Defence = rand() % 6 + 2;
			tempStats.Intelligence = rand() % 8 + 4;

			tempStats.Strength = rand() % 6 + 3;
			tempStats.Wisdom = rand() % 8 + 3;

			tempAttack = CreateRef<Spell>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Wisdom / 3));

			tempName = "Wizard";
		}
		return std::make_tuple(tempStats, tempName, std::move(tempAttack));
	}
}
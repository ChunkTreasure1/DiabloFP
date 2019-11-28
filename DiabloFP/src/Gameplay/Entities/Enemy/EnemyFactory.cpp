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
	std::shared_ptr<Enemy> EnemyFactory::CreateEnemy()
	{
		//Generate stats
		int tempDiff = LevelSystem::GetDifficulty();

		std::shared_ptr<Enemy> tempEnemy = std::make_shared<Enemy>(8.f);

		std::tuple<Stats, std::string, std::shared_ptr<Attack>> tempTuple = GetEnemyStats();
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

			std::shared_ptr<Item> tempItem;
			if (tempVal <= 0.7f)
			{
				tempItem = std::make_shared<HealthPotion>((float)(rand() % 20 + 10));
			}
			else if (tempVal > 0.7f && tempVal < 0.9f)
			{
				tempItem = std::make_shared<Scroll>();
			}
			else if (tempVal > 0.95f)
			{
				tempItem = std::make_shared<Tome>();
			}

			tempEnemy->SetLoot(std::move(tempItem));
		}

		return tempEnemy;
	}

	std::tuple<Stats, std::string, std::shared_ptr<Attack>> EnemyFactory::GetEnemyStats()
	{
		Stats tempStats = Stats();
		std::string tempName;
		std::shared_ptr<Attack> tempAttack;

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

			tempAttack = std::make_shared<Axe>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Strength / 4));

			tempName = "Orch";
		}
		else if (tempVal == 2)
		{
			tempStats.Agility = rand() % 9 + 5;
			tempStats.Charisma = rand() % 7 + 3;
			tempStats.Constitution = rand() % 3 + 1;

			tempStats.Defence = rand() % 4 + 1;
			tempStats.Intelligence = rand() % 6 + 2;

			tempStats.Strength = rand() % 4 + 1;
			tempStats.Wisdom = rand() % 6 + 2;

			tempAttack = std::make_shared<Sword>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Strength / 1));

			tempName = "Goblin";
		}
		else if (tempVal == 3)
		{
			tempStats.Agility = rand() % 7 + 3;
			tempStats.Charisma = rand() % 8 + 3;
			tempStats.Constitution = rand() % 5 + 1;

			tempStats.Defence = rand() % 6 + 2;
			tempStats.Intelligence = rand() % 8 + 4;

			tempStats.Strength = rand() % 6 + 3;
			tempStats.Wisdom = rand() % 8 + 3;

			tempAttack = std::make_shared<Spell>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Wisdom / 3));

			tempName = "Wizard";
		}
		return std::make_tuple(tempStats, tempName, std::move(tempAttack));
	}
}
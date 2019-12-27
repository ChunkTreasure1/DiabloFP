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

		if (Random::Int(1, 100) <= 60)
		{
			float tempVal = (float)(Random::Int(1, 100));
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

	Ref<Enemy> EnemyFactory::CreateBoss()
	{
		//Generate stats
		int tempDiff = LevelSystem::GetDifficulty();

		Ref<Enemy> tempEnemy = CreateRef<Enemy>(20.f);

		std::tuple<Stats, std::string, Ref<Attack>> tempTuple = GetEnemyStats();
		tempEnemy->SetStats(std::get<0>(tempTuple));
		tempEnemy->SetName(std::get<1>(tempTuple));

		tempEnemy->SetAttack(std::get<2>(tempTuple));
		tempEnemy->SetHealth(tempEnemy->GetHealth() * tempEnemy->GetStats().Constitution);

		uint32_t tempXP = Random::Int(2, tempDiff * 10);
		tempEnemy->SetKillXP(tempXP);

		if (Random::Int(1, 100) <= 60)
		{
			float tempVal = (float)(Random::Int(1, 100));
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

		int tempVal = Random::Int(1, 3);
		if (tempVal == 1)
		{
			tempStats.Agility = Random::Int(2, 5);
			tempStats.Charisma = Random::Int(1, 6);
			tempStats.Constitution = Random::Int(4, 7);

			tempStats.Defence = Random::Int(3, 8);
			tempStats.Intelligence = Random::Int(1, 5);

			tempStats.Strength = rand() % Random::Int(4, 8);
			tempStats.Wisdom = rand() % Random::Int(1, 4);

			tempAttack = CreateRef<Axe>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Strength / 4));

			tempName = "Orch";
		}
		else if (tempVal == 2)
		{
			tempStats.Agility = Random::Int(2, 6);
			tempStats.Charisma = Random::Int(3, 7);
			tempStats.Constitution = Random::Int(1, 3);

			tempStats.Defence = Random::Int(1, 4);
			tempStats.Intelligence = Random::Int(2, 6);

			tempStats.Strength = Random::Int(1, 4);
			tempStats.Wisdom = Random::Int(2, 6);

			tempAttack = CreateRef<Sword>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Strength / 1));

			tempName = "Goblin";
		}
		else if (tempVal == 3)
		{
			tempStats.Agility = Random::Int(2, 6);
			tempStats.Charisma = Random::Int(3, 8);
			tempStats.Constitution = Random::Int(1, 5);

			tempStats.Defence = Random::Int(2, 6);
			tempStats.Intelligence = Random::Int(4, 8);

			tempStats.Strength = Random::Int(3, 6);
			tempStats.Wisdom = Random::Int(3, 8);

			tempAttack = CreateRef<Spell>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (tempStats.Wisdom / 3));

			tempName = "Wizard";
		}
		return std::make_tuple(tempStats, tempName, std::move(tempAttack));
	}
}
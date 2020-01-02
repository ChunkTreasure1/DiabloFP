#include "pch.h"
#include "FightSystem.h"

#include "Gameplay/Entities/Player.h"
#include "Gameplay/LevelSystem.h"

#include "Core/Input/Input.h"
#include "Core/Game.h"
#include "Core/Utility/ExitException.h"

namespace Diablo
{
	Ref<FightSystem> FightSystem::mypInstance = nullptr;

	FightSystem::FightSystem()
	{
		mypInstance.reset(this);
	}

	FightSystem::~FightSystem()
	{}

	void FightSystem::GameOver()
	{
		Print::Clear();
		Print::ColorText("GAME OVER", Color::RED);
		Print::ColorText("Press ENTER to exit", Color::RED);
		std::cin.get();

		throw ExitException();
	}

	FightExit FightSystem::FightEnemy(Ref<Enemy>& apEnemy)
	{
		Game::Get()->SetIs3D(false);
		bool tempRunning = true;
		do
		{
			Player* tempPlayer = Player::Get();

			Print::Clear();

			Print::ColorText("What would you like to do?\n", Color::YELLOW);

			Print::ColorText("1. Attack\n", Color::RED);
			Print::ColorText("2. Use Magic\n", Color::RED);
			Print::ColorText("3. Defend\n", Color::RED);
			Print::ColorText("4. Flee\n", Color::RED);
			Print::ColorText("5. Use Item\n", Color::RED);

			Print::Stats(apEnemy);

			std::string tempInput = Input::GetInput();
			if (tempInput == "1")
			{
				Ref<Attack> tempAttack = tempPlayer->GetAttack(apEnemy);

				if (apEnemy->GetCombatChoice() == EnemyChoice::Attack)
				{
					//Check attack speed
					if (tempAttack->GetSpeed() > apEnemy->GetAttack()->GetSpeed())
					{
						Print::Clear();

						if (AttackEnemy(apEnemy, tempAttack)) { Game::Get()->SetIs3D(true); return FightExit::EnemyKilled; }
						if (AttackPlayer(apEnemy)) { return FightExit::PlayerKilled; }

						std::cin.get();
					}
					else
					{
						Print::Clear();

						if (AttackPlayer(apEnemy)) { return FightExit::PlayerKilled; }
						if (AttackEnemy(apEnemy, tempAttack)) { Game::Get()->SetIs3D(true); return FightExit::EnemyKilled; }

						std::cin.get();
					}
				}
				else
				{
					Print::Clear();

					if (AttackEnemy(apEnemy, tempAttack)) { Game::Get()->SetIs3D(true); return FightExit::EnemyKilled; }

					std::cin.get();
				}
			}
			else if (tempInput == "2")
			{

			}
			else if (tempInput == "3")
			{
				Print::Clear();

				if (apEnemy->GetCombatChoice() == EnemyChoice::Attack)
				{
					if (AttackPlayer(apEnemy, tempPlayer->GetDefence())) { return FightExit::PlayerKilled; }

					std::cin.get();
				}
			}
			else if (tempInput == "4")
			{
				Print::Clear();
				Print::ColorText("You have decided to flee!", Color::GREEN);

				std::cin.get();
				return FightExit::Fleed;
			}
			else if (tempInput == "5")
			{
				Player::Get()->GetInventory()->OpenInventory();
			}
			else
			{
				Print::Clear();
				Print::ColorText("Wrong input!", Color::RED);
				std::cin.get();
			}

		} while (tempRunning);

		return FightExit::Fleed;
	}

	bool FightSystem::AttackPlayer(Ref<Enemy>& apEnemy)	
	{
		uint32_t tempVal = rand() % 10 + 1;

		if (tempVal > Player::Get()->GetAgility())
		{
			Player::Get()->SetHealth(Player::Get()->GetHealth() - apEnemy->GetAttack()->GetDamage());
			if (Player::Get()->GetHealth() <= 0)
			{
				return true;
			}

			Print::ColorText(apEnemy->GetName() + " damaged you by " + Print::ToString(apEnemy->GetAttack()->GetDamage()) + "HP!\n", Color::RED);
		}
		else
		{
			Print::ColorText("You evaded an attack from " + apEnemy->GetName() + "!\n", Color::GREEN);
		}
		return false;
	}

	bool FightSystem::AttackPlayer(Ref<Enemy>& apEnemy, uint32_t aValue)
	{
		float tempDamage = apEnemy->GetAttack()->GetDamage() * (aValue / 7);
		uint32_t tempVal = rand() % 10 + 1;

		if (tempVal > Player::Get()->GetAgility())
		{
			Player::Get()->SetHealth(Player::Get()->GetHealth() - tempDamage);
			if (Player::Get()->GetHealth() <= 0)
			{
				return true;
			}

			Print::ColorText(apEnemy->GetName() + " damaged you by " + Print::ToString(apEnemy->GetAttack()->GetDamage()) + "HP!\n", Color::RED);
		}
		else
		{
			Print::ColorText("You evaded an attack from " + apEnemy->GetName() + "!\n", Color::GREEN);
		}
		return false;
	}

	bool FightSystem::AttackEnemy(Ref<Enemy>& apEnemy, Ref<Attack>& apAttack)
	{
		uint32_t tempVal = rand() % 10 + 1;

		if (tempVal > apEnemy->GetAgility())
		{
			apEnemy->SetHealth(apEnemy->GetHealth() - apAttack->GetDamage());

			if (apEnemy->GetHealth() <= 0)
			{
				LevelSystem::AddXPToPlayer(apEnemy->GetKillXP());
				Print::ColorText("You gained " + Print::ToString(apEnemy->GetKillXP()) + " XP!\n", Color::GREEN);
				Player::Get()->GetInventory()->AddItem(apEnemy->GetDropLoot());
				Print::ColorText("The enemy dropped item " + apEnemy->GetDropLoot()->GetName() + "!\n", Color::GREEN);

				return true;
			}

			Print::ColorText("You damaged " + apEnemy->GetName() + " by " + Print::ToString(apAttack->GetDamage()) + "HP!\n", Color::GREEN);
		}
		else
		{
			Print::ColorText(apEnemy->GetName() + " evaded your attack!\n", Color::RED);
		}
		return false;
	}
}
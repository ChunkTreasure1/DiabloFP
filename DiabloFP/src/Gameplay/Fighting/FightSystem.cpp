#include "FightSystem.h"

#include "Gameplay/Entities/Player.h"
#include "Gameplay/LevelSystem.h"

#include "Core/Utility/Print.h"
#include "Core/Input/Input.h"
#include "Core/Game.h"
#include "Core/Utility/ExitException.h"

namespace Diablo
{
	std::shared_ptr<FightSystem> FightSystem::mypInstance = nullptr;

	FightSystem::FightSystem()
	{
		mypInstance.reset(this);
	}

	FightSystem::~FightSystem()
	{}

	void FightSystem::GameOver()
	{
		Print::Clear();
		Print::PrintColorText("GAME OVER", COLOR_RED);
		Print::PrintColorText("Press ENTER to exit", COLOR_RED);
		std::cin.get();

		throw ExitException();
	}

	FightExit FightSystem::FightEnemy(std::shared_ptr<Enemy> apEnemy)
	{
		Game::Get()->SetIs3D(false);
		bool tempRunning = true;
		do
		{
			Player* tempPlayer = Player::Get();

			Print::Clear();

			Print::PrintColorText("Player health: " + Print::ToString(Player::Get()->GetHealth()) + "\n", COLOR_YELLOW);
			Print::PrintColorText("Enemy health: " + Print::ToString(apEnemy->GetHealth()) + "\n\n", COLOR_YELLOW);

			Print::PrintColorText("What would you like to do?\n", COLOR_YELLOW);

			Print::PrintColorText("1. Attack\n", COLOR_RED);
			Print::PrintColorText("2. Defend\n", COLOR_RED);
			Print::PrintColorText("3. Flee\n", COLOR_RED);
			Print::PrintColorText("4. Use Item\n", COLOR_RED);

			std::string tempInput = Input::GetInput();
			if (tempInput == "1")
			{
				std::shared_ptr<Attack> tempAttack = tempPlayer->GetAttack();

				if (apEnemy->GetCombatChoice() == EnemyChoice::Attack)
				{
					//Check attack speed
					if (tempAttack->GetSpeed() > apEnemy->GetAttack()->GetSpeed())
					{
						Print::Clear();

						if (AttackEnemy(apEnemy, tempAttack)) { return FightExit::EnemyKilled; }
						if (AttackPlayer(apEnemy)) { Game::Get()->SetIs3D(true); return FightExit::PlayerKilled; }

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
				Print::Clear();

				if (apEnemy->GetCombatChoice() == EnemyChoice::Attack)
				{
					if (AttackPlayer(apEnemy, tempPlayer->GetDefence())) { return FightExit::PlayerKilled; }

					std::cin.get();
				}
			}
			else if (tempInput == "3")
			{
				Print::Clear();
				Print::PrintColorText("You have decided to flee!", COLOR_GREEN);

				std::cin.get();
				return FightExit::Fleed;
			}
			else if (tempInput == "4")
			{
				Player::Get()->GetInventory()->OpenInventory();
			}
			else
			{
				Print::Clear();
				Print::PrintColorText("Wrong input!", COLOR_RED);
				std::cin.get();
			}

		} while (tempRunning);

		return FightExit::Fleed;
	}

	bool FightSystem::AttackPlayer(std::shared_ptr<Enemy>& apEnemy)
	{
		uint32_t tempVal = rand() % 10 + 1;

		if (tempVal > Player::Get()->GetAgility())
		{
			Player::Get()->SetHealth(Player::Get()->GetHealth() - apEnemy->GetAttack()->GetDamage());
			if (Player::Get()->GetHealth() <= 0)
			{
				return true;
			}

			Print::PrintColorText(apEnemy->GetName() + " damaged you by " + Print::ToString(apEnemy->GetAttack()->GetDamage()) + "HP!\n", COLOR_RED);
		}
		else
		{
			Print::PrintColorText("You evaded an attack from " + apEnemy->GetName() + "!\n", COLOR_GREEN);
		}
		return false;
	}

	bool FightSystem::AttackPlayer(std::shared_ptr<Enemy>& apEnemy, uint32_t aValue)
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

			Print::PrintColorText(apEnemy->GetName() + " damaged you by " + Print::ToString(apEnemy->GetAttack()->GetDamage()) + "HP!\n", COLOR_RED);
		}
		else
		{
			Print::PrintColorText("You evaded an attack from " + apEnemy->GetName() + "!\n", COLOR_GREEN);
		}
		return false;
	}

	bool FightSystem::AttackEnemy(std::shared_ptr<Enemy>& apEnemy, std::shared_ptr<Attack>& apAttack)
	{
		uint32_t tempVal = rand() % 10 + 1;

		if (tempVal > apEnemy->GetAgility())
		{
			apEnemy->SetHealth(apEnemy->GetHealth() - apAttack->GetDamage());

			if (apEnemy->GetHealth() <= 0)
			{
				return true;
			}

			Print::PrintColorText("You damaged " + apEnemy->GetName() + " by " + Print::ToString(apAttack->GetDamage()) + "HP!\n", COLOR_GREEN);
		}
		else
		{
			Print::PrintColorText(apEnemy->GetName() + " evaded your attack!\n", COLOR_RED);
		}
		return false;
	}
}
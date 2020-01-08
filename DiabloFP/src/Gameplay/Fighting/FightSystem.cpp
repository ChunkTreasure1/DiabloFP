#include "pch.h"
#include "FightSystem.h"

#include "Gameplay/Entities/Player.h"
#include "Gameplay/LevelSystem.h"

#include "Core/Input/Input.h"
#include "Core/Game.h"
#include "Core/Utility/ExitException.h"

#include "Attacks/Spell.h"
#include "Attacks/Spells/Heal.h"
#include "Attacks/Spells/Freeze.h"

#include "Attacks/Spells/Slowness.h"
#include "Attacks/Spells/Weakness.h"
#include "Attacks/Spells/Avoidance.h"

#include "Attacks/Spells/Buff.h"
#include "Attacks/Spells/Fire.h"

namespace Diablo
{
	Ref<FightSystem> FightSystem::mypInstance = nullptr;

	FightSystem::FightSystem()
		: mySlowed(false), myBuffValue(0.f), myFireAttackValue(0.f)
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

			if (apEnemy->GetFrozen())
			{
				apEnemy->Update();
			}

			if (tempInput == "1")
			{
				Ref<Attack> tempAttack = tempPlayer->GetAttack(apEnemy);

				if (apEnemy->GetCombatChoice() == EnemyChoice::Attack)
				{
					//Check attack speed
					if (tempAttack->GetSpeed() > apEnemy->GetAttack()->GetSpeed() || mySlowed)
					{
						mySlowed = false;
						Print::Clear();

						if (AttackEnemy(apEnemy, tempAttack)) { Game::Get()->SetIs3D(true); return FightExit::EnemyKilled; }
						
						if (!myAvoiding)
						{
							if (AttackPlayer(apEnemy) && !apEnemy->GetFrozen()) { return FightExit::PlayerKilled; }
						}
						else 
						{
							myAvoiding = false;
						}

						std::cin.get();
					}
					else
					{
						Print::Clear();

						if (!myAvoiding)
						{
							if (AttackPlayer(apEnemy) && !apEnemy->GetFrozen()) { return FightExit::PlayerKilled; }
						}
						else 
						{
							myAvoiding = false;
						}
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
				Ref<Spell> tempSpell = tempPlayer->GetSpell(apEnemy);

				if (tempSpell->GetCategory() == SpellCategory::Attack)
				{
					if (Ref<Fire> tempF = std::dynamic_pointer_cast<Fire>(tempSpell))
					{
						myFireAttackValue = tempF->GetDamage();
						continue;
					}

					if (apEnemy->GetCombatChoice() == EnemyChoice::Attack)
					{
						Print::Clear();

						if (AttackEnemy(apEnemy, tempSpell)) { Game::Get()->SetIs3D(true); return FightExit::EnemyKilled; }
						if (AttackPlayer(apEnemy) && !apEnemy->GetFrozen()) { return FightExit::PlayerKilled; }

						std::cin.get();
					}
					else
					{
						Print::Clear();

						if (AttackEnemy(apEnemy, tempSpell)) { Game::Get()->SetIs3D(true); return FightExit::EnemyKilled; }

						std::cin.get();
					}
				}
				else if (tempSpell->GetCategory() == SpellCategory::Support)
				{
					if (Ref<Heal> tempH = std::dynamic_pointer_cast<Heal>(tempSpell))
					{
						//Not actually damaging, but adding health
						Player::Get()->SetHealth(Player::Get()->GetHealth() + tempH->GetDamage());
					}
					else if (Ref<Weakness> tempW = std::dynamic_pointer_cast<Weakness>(tempSpell))
					{
						apEnemy->GetAttack()->SetDamage(apEnemy->GetAttack()->GetDamage() - tempW->GetDamage());
					}
					else if (Ref<Buff> tempB = std::dynamic_pointer_cast<Buff>(tempSpell))
					{
						myBuffValue = tempB->GetDamage();
					}
				}
				else if (tempSpell->GetCategory() == SpellCategory::Control)
				{
					if (Ref<Freeze> tempF = std::dynamic_pointer_cast<Freeze>(tempSpell))
					{
						apEnemy->SetFrozen(true);
					}
					else if (Ref<Slowness> tempS = std::dynamic_pointer_cast<Slowness>(tempSpell))
					{
						mySlowed = true;
					}
					else if (Ref<Avoidance> tempA = std::dynamic_pointer_cast<Avoidance>(tempSpell))
					{
						myAvoiding = true;
					}
				}
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
		if (myFireAttackValue > 0)
		{
			apEnemy->SetHealth(apEnemy->GetHealth() - 5.f);
			myFireAttackValue -= 5.f;

			Print::ColorText("Enemy damaged by 5HP from fire!\n", Color::GREEN);
		}
		else if (myFireAttackValue < 0)
		{
			myFireAttackValue = 0;
		}

		uint32_t tempVal = rand() % 10 + 1;

		if (tempVal > apEnemy->GetAgility())
		{
			apEnemy->SetHealth(apEnemy->GetHealth() - (apAttack->GetDamage() + myBuffValue));
			myBuffValue = 0;

			if (apEnemy->GetHealth() <= 0)
			{
				LevelSystem::AddXPToPlayer(apEnemy->GetKillXP());
				Print::ColorText("You gained " + Print::ToString(apEnemy->GetKillXP()) + " XP!\n", Color::GREEN);
				Player::Get()->GetInventory()->AddItem(apEnemy->GetDropLoot());
				Print::ColorText("The enemy dropped item " + apEnemy->GetDropLoot()->GetName() + "!\n", Color::GREEN);

				Player::Get()->AddMana(50);
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

	bool FightSystem::AttackEnemy(Ref<Enemy>& apEnemy, Ref<Spell>& apSpell)
	{
		if (myFireAttackValue > 0)
		{
			apEnemy->SetHealth(apEnemy->GetHealth() - 5.f);
			myFireAttackValue -= 5.f;

			Print::ColorText("Enemy damaged by 5HP from fire!\n", Color::GREEN);
		}
		else if (myFireAttackValue < 0)
		{
			myFireAttackValue = 0;
		}

		apEnemy->SetHealth(apEnemy->GetHealth() - (apSpell->GetDamage() + myBuffValue));
		myBuffValue = 0;

		Player::Get()->AddMana(-(apSpell->GetManaCost()));
		if (apEnemy->GetHealth() <= 0)
		{
			LevelSystem::AddXPToPlayer(apEnemy->GetKillXP());
			Print::ColorText("You gained " + Print::ToString(apEnemy->GetKillXP()) + " XP!\n", Color::GREEN);
			Player::Get()->GetInventory()->AddItem(apEnemy->GetDropLoot());
			Print::ColorText("The enemy dropped item " + apEnemy->GetDropLoot()->GetName() + "!\n", Color::GREEN);

			Player::Get()->AddMana(50);
			return true;
		}

		Print::ColorText("You damaged " + apEnemy->GetName() + " by " + Print::ToString(apSpell->GetDamage()) + "HP!\n", Color::GREEN);

		return false;
	}
}
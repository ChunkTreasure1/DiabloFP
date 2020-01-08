#include "pch.h"
#include "Player.h"

#include "Gameplay/Fighting/Attacks/Axe.h"
#include "Gameplay/Fighting/Attacks/Spell.h"
#include "Gameplay/Fighting/Attacks/Sword.h"

#include "Gameplay/Fighting/Attacks/Spells/Firebolt.h"
#include "Gameplay/Fighting/Attacks/Spells/HolyBolt.h"

#include "Gameplay/LevelSystem.h"
#include "Core/Input/Input.h"
#include "Core/Utility/ExitException.h"

namespace Diablo
{
	Player* Player::myInstance = nullptr;

	Player::Player(float aHealth, uint32_t aMapWidth)
		: Entity(aHealth), myDepth(16.f), myFOV(3.14159f / 4.f), mySpeed(5.f),
		myXPos(3.f), myYPos(5.09f), myAngle(0), myMapWidth(aMapWidth), myBaseHealth(aHealth),
		myShouldExit(false), myMana(100), myMaxMana(100)
	{
		myInstance = this;
		mypInventory = CreateScope<Inventory>();
	}

	void Player::SetXPos(float aPos)
	{
		myXPos = aPos;
		if (Map::Get()->GetEnemies().size() > 0)
		{
			CheckForEnemy();
		}
		else
		{
			CheckForExit();
			CheckForChest();
		}
	}

	void Player::SetYPos(float aPos)
	{
		myYPos = aPos;
		if (Map::Get()->GetEnemies().size() > 0)
		{
			CheckForEnemy();
		}
		else
		{
			CheckForExit();
			CheckForChest();
		}
	}

	void Player::SetStats(PlayerType aPlayerType)
	{
		if (aPlayerType == PlayerType::Warrior)
		{
			myStats.Strength = rand() % 8 + 4;
			myStats.Agility = rand() % 4 + 1;
			myStats.Defence = rand() % 7 + 3;

			myStats.Constitution = rand() % 6 + 1;
			myStats.Intelligence = rand() % 4 + 1;
			myStats.Wisdom = rand() % 5 + 2;

			myStats.Charisma = rand() % 6 + 2;

			Ref<Axe> tempAttack = CreateRef<Axe>();
			tempAttack->SetDamage(tempAttack->GetBaseDamage() * (myStats.Strength / 2.f));

			myAttacks.push_back(std::move(tempAttack));

			Ref<Firebolt> tempSpell = CreateRef<Firebolt>();
			mySpells.push_back(std::move(tempSpell));
		}
		else if (aPlayerType == PlayerType::Sorcerer)
		{
			myStats.Strength = rand() % 5 + 2;
			myStats.Agility = rand() % 8 + 4;
			myStats.Defence = rand() % 5 + 2;

			myStats.Constitution = rand() % 3 + 1;
			myStats.Intelligence = rand() % 7 + 3;
			myStats.Wisdom = rand() % 8 + 4;

			myStats.Charisma = rand() % 7 + 2;

			Ref<Sword> tempAttack = CreateRef<Sword>();
			tempAttack->SetDamage(tempAttack->GetBaseDamage() * (myStats.Wisdom / 2.f));

			myAttacks.push_back(std::move(tempAttack));

			Ref<HolyBolt> tempSpell = CreateRef<HolyBolt>();
			mySpells.push_back(std::move(tempSpell));
		}
		else if (aPlayerType == PlayerType::Rogue)
		{
			myStats.Strength = rand() % 6 + 2;
			myStats.Agility = rand() % 7 + 3;
			myStats.Defence = rand() % 6 + 2;

			myStats.Constitution = rand() % 6 + 2;
			myStats.Intelligence = rand() % 6 + 1;
			myStats.Wisdom = rand() % 4 + 1;

			myStats.Charisma = rand() % 8 + 4;

			Ref<Sword> tempAttack = CreateRef<Sword>();
			tempAttack->SetDamage(tempAttack->GetBaseDamage() * (myStats.Strength / 2.f));

			myAttacks.push_back(std::move(tempAttack));

			Ref<Firebolt> tempSpell = CreateRef<Firebolt>();
			mySpells.push_back(std::move(tempSpell));
		}

		myHealth *= myStats.Constitution;
	}

	Ref<Attack> Player::GetAttack(Ref<Enemy>& someEnemy)
	{
		do
		{
			Print::Clear();

			//Show opponent stats
			Print::ColorText("Press 0 to return\n", Color::GREEN);
			Print::ColorText("Choose an attack to use on opponent!\n", Color::GREEN);

			for (size_t i = 0; i < myAttacks.size(); i++)
			{
				Print::ColorText(std::to_string(i + 1) + ". " + myAttacks[i]->GetName() + "\n", Color::YELLOW);
			}

			Print::Stats(someEnemy);

			std::string tempInput = Input::GetInput();
			for (size_t i = 0; i < myAttacks.size(); i++)
			{
				if (tempInput == std::to_string(i + 1))
				{
					return myAttacks[i];
				}
			}

			if (tempInput == "0")
			{
				break;
			}

			Print::ColorText("Wrong input!", Color::RED);
			std::cin.get();

		} while (true);

		return nullptr;
	}

	Ref<Spell> Player::GetSpell(Ref<Enemy>& someEnemy)
	{
		do
		{
			Print::Clear();

			//Show opponent stats
			Print::ColorText("Press 0 to return\n", Color::GREEN);
			Print::ColorText("Choose an attack to use on opponent!\n", Color::GREEN);

			for (size_t i = 0; i < mySpells.size(); i++)
			{
				Print::ColorText(std::to_string(i + 1) + ". " + mySpells[i]->GetName() + " (" + Spell::CategoryToString(mySpells[i]->GetCategory()) + ")\n", Color::YELLOW);
			}

			Print::Stats(someEnemy);

			std::string tempInput = Input::GetInput();
			for (size_t i = 0; i < myAttacks.size(); i++)
			{
				if (tempInput == std::to_string(i + 1))
				{
					return mySpells[i];
				}
			}

			if (tempInput == "0")
			{
				break;
			}

		} while (true);

		return Ref<Spell>();
	}

	void Player::Update()
	{
		for (size_t i = 0; i < mypInventory->GetVector().size(); i++)
		{
			mypInventory->GetVector()[i]->Update();
		}
	}

	void Player::UpdateAttacks()
	{
		for (auto& tempA : myAttacks)
		{
			tempA->SetDamage(tempA->GetBaseDamage() * (GetStrength() / 2));
		}
	}

	void Player::AttackEnemy(Ref<Enemy>& aEnemy)
	{
		auto tempRet = FightSystem::Get()->FightEnemy(aEnemy);

		if (tempRet == FightExit::EnemyKilled)
		{
			Map::Get()->GetStringMap()[aEnemy->GetStrPos()] = '.';

			auto tempIT = std::find(Map::Get()->GetEnemies().begin(), Map::Get()->GetEnemies().end(), aEnemy);
			if (tempIT != Map::Get()->GetEnemies().end())
			{
				Map::Get()->GetEnemies().erase(tempIT);
			}
		}
		else if (tempRet == FightExit::PlayerKilled)
		{
			FightSystem::Get()->GameOver();
		}
	}

	void Player::OpenChest(Ref<Chest>& aChest)
	{
		aChest->OpenChest(aChest);
	}

	void Player::Exit()
	{
		if (Map::Get()->GetBoss()->GetHealth() > 0)
		{
			auto tempS = FightSystem::Get()->FightEnemy(Map::Get()->GetBoss());
			if (tempS == FightExit::EnemyKilled)
			{
				myShouldExit = true;
				LevelSystem::IncreseDifficulty();
			}
			else
			{
				throw ExitException();
			}
		}
		else
		{
			myShouldExit = true;
		}
	}

	void Player::CheckForEnemy()
	{
		uint32_t tempCharPos = Utility::Rounded(myYPos) + Utility::Rounded(myXPos) * myMapWidth;
		if (Map::Get()->GetStringMap().c_str()[tempCharPos - myMapWidth] == '*')
		{
			for (auto& tempE : Map::Get()->GetEnemies())
			{
				uint32_t tempCheck = Utility::Rounded(tempE->GetCharPos().y) + Utility::Rounded(tempE->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos - myMapWidth)
				{
					continue;
				}

				AttackEnemy(tempE);
				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos + myMapWidth] == '*')
		{
			for (auto& tempE : Map::Get()->GetEnemies())
			{
				uint32_t tempCheck = Utility::Rounded(tempE->GetCharPos().y) + Utility::Rounded(tempE->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos + myMapWidth)
				{
					continue;
				}

				AttackEnemy(tempE);
				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos - 1] == '*')
		{
			for (auto& tempE : Map::Get()->GetEnemies())
			{
				uint32_t tempCheck = Utility::Rounded(tempE->GetCharPos().y) + Utility::Rounded(tempE->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos)
				{
					continue;
				}

				AttackEnemy(tempE);
				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos + 1] == '*')
		{
			for (auto& tempE : Map::Get()->GetEnemies())
			{
				uint32_t tempCheck = Utility::Rounded(tempE->GetCharPos().y) + Utility::Rounded(tempE->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos)
				{
					continue;
				}

				AttackEnemy(tempE);
				break;
			}
		}
	}

	void Player::CheckForChest()
	{
		uint32_t tempCharPos = Utility::Rounded(myYPos) + Utility::Rounded(myXPos) * myMapWidth;
		if (Map::Get()->GetStringMap().c_str()[tempCharPos - myMapWidth] == '=')
		{
			for (auto& tempC : Map::Get()->GetChests())
			{
				uint32_t tempCheck = Utility::Rounded(tempC->GetCharPos().y) + Utility::Rounded(tempC->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos - myMapWidth)
				{
					continue;
				}

				OpenChest(tempC);
				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos + myMapWidth] == '=')
		{
			for (auto& tempC : Map::Get()->GetChests())
			{
				uint32_t tempCheck = Utility::Rounded(tempC->GetCharPos().y) + Utility::Rounded(tempC->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos + myMapWidth)
				{
					continue;
				}

				OpenChest(tempC);
				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos - 1] == '=')
		{
			for (auto& tempC : Map::Get()->GetChests())
			{
				uint32_t tempCheck = Utility::Rounded(tempC->GetCharPos().y) + Utility::Rounded(tempC->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos)
				{
					continue;
				}

				OpenChest(tempC);
				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos + 1] == '=')
		{
			for (auto& tempC : Map::Get()->GetChests())
			{
				uint32_t tempCheck = Utility::Rounded(tempC->GetCharPos().y) + Utility::Rounded(tempC->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos)
				{
					continue;
				}

				OpenChest(tempC);
				break;
			}
		}
	}

	void Player::CheckForExit()
	{
		uint32_t tempCharPos = Utility::Rounded(myYPos) + Utility::Rounded(myXPos) * myMapWidth;
		if (Map::Get()->GetStringMap().c_str()[tempCharPos - myMapWidth] == '&')
		{
			for (auto& tempC : Map::Get()->GetChests())
			{
				uint32_t tempCheck = Utility::Rounded(tempC->GetCharPos().y) + Utility::Rounded(tempC->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos - myMapWidth)
				{
					continue;
				}
				Exit();

				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos + myMapWidth] == '&')
		{
			for (auto& tempC : Map::Get()->GetChests())
			{
				uint32_t tempCheck = Utility::Rounded(tempC->GetCharPos().y) + Utility::Rounded(tempC->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos + myMapWidth)
				{
					continue;
				}

				Exit();
				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos - 1] == '&')
		{
			for (auto& tempC : Map::Get()->GetChests())
			{
				uint32_t tempCheck = Utility::Rounded(tempC->GetCharPos().y) + Utility::Rounded(tempC->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos)
				{
					continue;
				}

				Exit();
				break;
			}
		}
		else if (Map::Get()->GetStringMap().c_str()[tempCharPos + 1] == '&')
		{
			for (auto& tempC : Map::Get()->GetChests())
			{
				uint32_t tempCheck = Utility::Rounded(tempC->GetCharPos().y) + Utility::Rounded(tempC->GetCharPos().x) * myMapWidth;

				if (tempCheck != tempCharPos)
				{
					continue;
				}

				Exit();
				break;
			}
		}
	}
}
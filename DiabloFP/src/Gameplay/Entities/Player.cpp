#include "Player.h"

#include "Gameplay/Fighting/Attacks/Axe.h"
#include "Gameplay/Fighting/Attacks/Spell.h"
#include "Gameplay/Fighting/Attacks/Sword.h"

#include "Core/Utility/Print.h"
#include "Core/Input/Input.h"
#include "Core/Utility/Utility.h"

namespace Diablo
{
	Player* Player::myInstance = nullptr;

	Player::Player(float aHealth, uint32_t aMapWidth)
		: Entity(aHealth), myDepth(16.f), myFOV(3.14159f / 4.f), mySpeed(5.f),
		myXPos(3.f), myYPos(5.09f), myAngle(0), myMapWidth(aMapWidth)
	{
		myInstance = this;
		mypInventory = std::make_unique<Inventory>();
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
			CheckForChest();
		}
	}

	void Player::SetPlayerStats(PlayerType aPlayerType)
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

			std::shared_ptr<Axe> tempAttack = std::make_shared<Axe>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (myStats.Strength / 3.f));

			myAttacks.push_back(std::move(tempAttack));
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

			std::shared_ptr<Spell> tempAttack = std::make_shared<Spell>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (myStats.Wisdom / 3.f));

			myAttacks.push_back(std::move(tempAttack));
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

			std::shared_ptr<Sword> tempAttack = std::make_shared<Sword>();
			tempAttack->SetDamage(tempAttack->GetDamage() * (myStats.Strength / 2.f));

			myAttacks.push_back(std::move(tempAttack));
		}

		myHealth *= myStats.Constitution;
	}

	std::shared_ptr<Attack> Player::GetAttack(std::shared_ptr<Enemy>& someEnemy)
	{
		do
		{
			Print::Clear();

			//Show opponent stats
			Print::ColorText("Press 0 to return\n", COLOR_GREEN);
			Print::ColorText("Choose an attack to use on opponent!\n", COLOR_GREEN);

			for (size_t i = 0; i < myAttacks.size(); i++)
			{
				Print::ColorText(std::to_string(i + 1) + ". " + myAttacks[i]->GetName() + "\n", COLOR_YELLOW);
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

			Print::ColorText("Wrong input!", COLOR_RED);
			std::cin.get();

		} while (true);

		return nullptr;
	}

	void Player::Update()
	{
		for (size_t i = 0; i < mypInventory->GetVector().size(); i++)
		{
			mypInventory->GetVector()[i]->Update();
		}
	}

	void Player::AttackEnemy(std::shared_ptr<Enemy>& aEnemy)
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

	void Player::OpenChest(std::shared_ptr<Chest>& aChest)
	{
		aChest->OpenChest(aChest);
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
}
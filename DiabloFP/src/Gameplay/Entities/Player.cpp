#include "Player.h"

#include "Gameplay/Fighting/Attacks/Axe.h"
#include "Gameplay/Fighting/Attacks/Spell.h"
#include "Gameplay/Fighting/Attacks/Sword.h"

#include "Core/Print.h"
#include "Core/Input/Input.h"

namespace Diablo
{
	Player* Player::myInstance = nullptr;

	Player::Player(float aHealth)
		: Entity(aHealth), myDepth(16.f), myFOV(3.14159f / 4.f), mySpeed(5.f),
		myXPos(14.7f), myYPos(5.09f), myAngle(0)
	{
		myInstance = this;
		mypInventory = std::make_unique<Inventory>();
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

	std::shared_ptr<Attack> Player::GetAttack()
	{
		do
		{
			Print::Clear();

			//Show opponent stats
			Print::PrintColorText("Press 0 to return\n", COLOR_GREEN);
			Print::PrintColorText("Choose an attack to use on opponent!\n", COLOR_GREEN);

			for (size_t i = 0; i < myAttacks.size(); i++)
			{
				Print::PrintColorText(std::to_string(i + 1) + ". " + myAttacks[i]->GetName() + "\n", COLOR_YELLOW);
			}

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

			Print::PrintColorText("Wrong input!", COLOR_RED);
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
}
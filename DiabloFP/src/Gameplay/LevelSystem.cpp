#include "pch.h"
#include "LevelSystem.h"
#include "Entities/Player.h"

#include "Core/Input/Input.h"

namespace Diablo
{
	uint32_t LevelSystem::myPlayerXP = 0;
	uint32_t LevelSystem::myPlayerLevel = 1;
	uint32_t LevelSystem::myDifficulty = 1;

	void LevelSystem::Update()
	{
		if (myPlayerXP >= myPlayerLevel * 5 + 250)
		{
			myPlayerLevel++;
			AddStat();
			UpgradeSpell();
		}
	}

	void LevelSystem::AddStat()
	{
		Game::Get()->SetIs3D(false);
		do
		{
			Print::Clear();
			Print::ColorText("Your level have increased to " + std::to_string(myPlayerLevel) + "!\n", Color::GREEN);
			Print::ColorText("Choose a stat to increase!\n", Color::YELLOW);
			Print::ColorText("1. Defence: " + std::to_string(Player::Get()->GetDefence()) + "\n", Color::YELLOW);

			Print::ColorText("2. Agility: " + std::to_string(Player::Get()->GetAgility()) + "\n", Color::YELLOW);
			Print::ColorText("3. Strength: " + std::to_string(Player::Get()->GetStrength()) + "\n", Color::YELLOW);
			Print::ColorText("4. Constitution: " + std::to_string(Player::Get()->GetConstitution()) + "\n", Color::YELLOW);

			Print::ColorText("5. Intelligence: " + std::to_string(Player::Get()->GetIntelligence()) + "\n", Color::YELLOW);
			Print::ColorText("6. Wisdom: " + std::to_string(Player::Get()->GetWisdom()) + "\n", Color::YELLOW);
			Print::ColorText("7. Charisma: " + std::to_string(Player::Get()->GetCharisma()) + "\n", Color::YELLOW);

			Print::Stats(nullptr);

			std::string tempInput = Input::GetInput();
			if (tempInput == "1")
			{
				Player::Get()->GetStats().Defence += 1;
				return;
			}
			else if (tempInput == "2")
			{
				Player::Get()->GetStats().Agility += 1;
				return;
			}
			else if (tempInput == "3")
			{
				Player::Get()->GetStats().Strength += 1;
				return;
			}
			else if (tempInput == "4")
			{
				Player::Get()->GetStats().Constitution += 1;
				return;
			}
			else if (tempInput == "5")
			{
				Player::Get()->GetStats().Intelligence += 1;
				return;
			}
			else if (tempInput == "6")
			{
				Player::Get()->GetStats().Wisdom += 1;
				return;
			}
			else if (tempInput == "7")
			{
				Player::Get()->GetStats().Charisma += 1;
				return;
			}
			else
			{
				Print::Clear();
				Print::ColorText("Wrong input!", Color::RED);
				std::cin.get();
			}

			Player::Get()->UpdateAttacks();

		} while (true);
	}

	void LevelSystem::UpgradeSpell()
	{
		do
		{
			Print::Clear();
			Print::ColorText("Choose a spell to upgrade!\n", Color::YELLOW);

			for (uint32_t i = 0; i < Player::Get()->GetSpells().size(); i++)
			{
				Print::ColorText(Print::ToString(i + 1) + ". " + Player::Get()->GetSpells()[i]->GetName() + " (" + Spell::CategoryToString(Player::Get()->GetSpells()[i]->GetCategory()) + "\n", Color::BLUE);
			}

			std::string tempInput = Input::GetInput();
			for (uint32_t i = 0; i < Player::Get()->GetSpells().size(); i++)
			{
				if (tempInput == Print::ToString(i + 1))
				{
					auto& tempS = Player::Get()->GetSpells()[i];
					tempS->SetDamage(tempS->GetBaseDamage() * (myPlayerLevel - 0.5f));

					Print::Clear();
					Print::ColorText("You have upgraded spell " + tempS->GetName() + "!\n", Color::GREEN);
					std::cin.get();

					return;
				}
			}

			Print::ColorText("Wrong input!", Color::RED);

		} while (true);
	}
}
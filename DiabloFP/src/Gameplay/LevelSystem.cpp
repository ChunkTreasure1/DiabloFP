#include "LevelSystem.h"
#include "Entities/Player.h"
#include "Core/Utility/Print.h"
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
		}
	}

	void LevelSystem::AddStat()
	{
		do
		{
			Print::Clear();
			Print::ColorText("Your level have increased to " + std::to_string(myPlayerLevel) + "!\n", COLOR_GREEN);
			Print::ColorText("Choose a stat to increase!\n", COLOR_YELLOW);
			Print::ColorText("1. Defence: " + std::to_string(Player::Get()->GetDefence()) + "\n", COLOR_YELLOW);

			Print::ColorText("2. Agility: " + std::to_string(Player::Get()->GetAgility()) + "\n", COLOR_YELLOW);
			Print::ColorText("3. Strength: " + std::to_string(Player::Get()->GetStrength()) + "\n", COLOR_YELLOW);
			Print::ColorText("4. Constitution: " + std::to_string(Player::Get()->GetConstitution()) + "\n", COLOR_YELLOW);

			Print::ColorText("5. Intelligence: " + std::to_string(Player::Get()->GetIntelligence()) + "\n", COLOR_YELLOW);
			Print::ColorText("6. Wisdom: " + std::to_string(Player::Get()->GetWisdom()) + "\n", COLOR_YELLOW);
			Print::ColorText("7. Charisma: " + std::to_string(Player::Get()->GetCharisma()) + "\n", COLOR_YELLOW);

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
				Print::ColorText("Wrong input!", COLOR_RED);
				std::cin.get();
			}

		} while (true);
	}
}
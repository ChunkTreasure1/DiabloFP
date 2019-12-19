#include "pch.h"
#include "Tome.h"
#include "Gameplay/Entities/Player.h"

#include "Core/Input/Input.h"

#include "Systems/ItemFactory.h"

namespace Diablo
{
	bool Tome::myRegistered = REGISTER_ITEM(Tome)

	Tome::Tome()
		: Item("Tome")
	{
		myStat = GetStat();
	}

	bool Tome::Use()
	{
		if (myStat == "Defence")
		{
			if (Player::Get()->GetDefence() < 10)
			{
				Player::Get()->GetStats().Defence += 1;
				return true;
			}

			Print::Clear();
			Print::ColorText("You have already maxed this stat!", Color::RED);
			std::cin.get();

			return false;
		}
		else if (myStat == "Agility")
		{
			if (Player::Get()->GetAgility() < 10)
			{
				Player::Get()->GetStats().Agility += 1;
				return true;
			}

			Print::Clear();
			Print::ColorText("You have already maxed this stat!", Color::RED);
			std::cin.get();

			return false;
		}
		else if (myStat == "Strength")
		{
			if (Player::Get()->GetStrength() < 10)
			{
				Player::Get()->GetStats().Strength += 1;
				return true;
			}

			Print::Clear();
			Print::ColorText("You have already maxed this stat!", Color::RED);
			std::cin.get();

			return false;
		}
		else if (myStat == "Constitution")
		{
			if (Player::Get()->GetConstitution() < 10)
			{
				Player::Get()->GetStats().Constitution += 1;
				return true;
			}

			Print::Clear();
			Print::ColorText("You have already maxed this stat!", Color::RED);
			std::cin.get();

			return false;
		}
		else if (myStat == "Intelligence")
		{
			if (Player::Get()->GetIntelligence() < 10)
			{
				Player::Get()->GetStats().Intelligence += 1;
				return true;
			}

			Print::Clear();
			Print::ColorText("You have already maxed this stat!", Color::RED);
			std::cin.get();

			return false;
		}
		else if (myStat == "Wisdom")
		{
			if (Player::Get()->GetWisdom() < 10)
			{
				Player::Get()->GetStats().Wisdom += 1;
				return true;
			}

			Print::Clear();
			Print::ColorText("You have already maxed this stat!", Color::RED);
			std::cin.get();

			return false;
		}
		else if (myStat == "Charisma")
		{
			if (Player::Get()->GetCharisma() < 10)
			{
				Player::Get()->GetStats().Charisma += 1;
				return true;
			}

			Print::Clear();
			Print::ColorText("You have already maxed this stat!", Color::RED);
			std::cin.get();

		}
		return false;
	}

	std::string Tome::GetStat()
	{
		int tempNum = rand() % 7 + 1;

		if (tempNum == 1)
		{
			return "Defence";
		}
		else if (tempNum == 2)
		{
			return "Agility";
		}
		else if (tempNum == 3)
		{
			return "Strength";
		}
		else if (tempNum == 4)
		{
			return "Constitution";
		}
		else if (tempNum == 5)
		{
			return "Intelligence";
		}
		else if (tempNum == 6)
		{
			return "Wisdom";
		}
		else if (tempNum == 7)
		{
			return "Charisma";
		}

		return "null";
	}
}
#include "Scroll.h"

#include "Gameplay/Entities/Player.h"
#include "Core/Utility/Print.h"
#include "Core/Input/Input.h"

#include "Systems/ItemFactory.h"

namespace Diablo
{
	//bool Scroll::myRegistered = ItemFactory::Register(Scroll::GetFactoryName(), Scroll::CreateMethod);

	Scroll::Scroll()
		: Item("Scroll")
	{
		myIsScroll = true;

		myLifeTime = rand() % 5 + 2;
		myStat = GetStat();
	}

	void Scroll::Update()
	{
		if (myIsUsed == true)
		{
			myLifeTime -= 1;
			if (myLifeTime <= 0)
			{
				Unuse();
			}
		}
	}

	bool Scroll::Use()
	{
		myUsable = false;

		if (myStat == "Defence")
		{
			if (Player::Get()->GetDefence() < 10)
			{
				Player::Get()->GetStats().Defence += 1;
				return true;
			}

			Print::Clear();
			Print::ColorText("You have already maxed this stat!", COLOR_RED);
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
			Print::ColorText("You have already maxed this stat!", COLOR_RED);
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
			Print::ColorText("You have already maxed this stat!", COLOR_RED);
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
			Print::ColorText("You have already maxed this stat!", COLOR_RED);
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
			Print::ColorText("You have already maxed this stat!", COLOR_RED);
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
			Print::ColorText("You have already maxed this stat!", COLOR_RED);
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
			Print::ColorText("You have already maxed this stat!", COLOR_RED);
			std::cin.get();

			return false;
		}

		return false;
	}

	void Scroll::Unuse()
	{
		if (myStat == "Defence")
		{
			Player::Get()->GetStats().Defence -= 1;
		}
		else if (myStat == "Agility")
		{
			Player::Get()->GetStats().Agility -= 1;
		}
		else if (myStat == "Strength")
		{
			Player::Get()->GetStats().Strength -= 1;
		}
		else if (myStat == "Constitution")
		{
			Player::Get()->GetStats().Constitution -= 1;
		}
		else if (myStat == "Intelligence")
		{
			Player::Get()->GetStats().Intelligence -= 1;
		}
		else if (myStat == "Wisdom")
		{
			Player::Get()->GetStats().Wisdom -= 1;
		}
		else if (myStat == "Charisma")
		{
			Player::Get()->GetStats().Charisma -= 1;
		}
	}

	std::string Scroll::GetStat()
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
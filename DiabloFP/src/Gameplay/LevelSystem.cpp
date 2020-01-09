#include "pch.h"
#include "LevelSystem.h"
#include "Entities/Player.h"

#include "Core/Input/Input.h"

#include "Gameplay/Fighting/Attacks/Spells/Heal.h"
#include "Gameplay/Fighting/Attacks/Spells/Freeze.h"

#include "Gameplay/Fighting/Attacks/Spells/Slowness.h"
#include "Gameplay/Fighting/Attacks/Spells/Weakness.h"
#include "Gameplay/Fighting/Attacks/Spells/Avoidance.h"

#include "Gameplay/Fighting/Attacks/Spells/Buff.h"
#include "Gameplay/Fighting/Attacks/Spells/Fire.h"
#include "Gameplay/Fighting/Attacks/Spells/Firebolt.h"
#include "Gameplay/Fighting/Attacks/Spells/Harm.h"

#include "Gameplay/Fighting/Attacks/Spells/HolyBolt.h"

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

			GetNewSpell();
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

	void LevelSystem::GetNewSpell()
	{
		do
		{
			Print::Clear();
			Print::ColorText("Choose a new spell!\n", Color::BLUE);

			Print::ColorText("1. Avoidance(Control)\n", Color::DARK_BLUE);
			Print::ColorText("2. Buff(Support)\n", Color::DARK_BLUE);
			Print::ColorText("3. Fire(Attack)\n", Color::DARK_BLUE);
			Print::ColorText("4. Firebolt(Attack)\n", Color::DARK_BLUE);
			Print::ColorText("5. Freeze(Support)\n", Color::DARK_BLUE);
			Print::ColorText("6. Harm(Attack)\n", Color::DARK_BLUE);
			Print::ColorText("7. Heal(Support)\n", Color::DARK_BLUE);
			Print::ColorText("8. HolyBlot(Attaxk)\n", Color::DARK_BLUE);
			Print::ColorText("9. Slowness(Control)\n", Color::DARK_BLUE);
			Print::ColorText("10. Weakness(Control)\n", Color::DARK_BLUE);

			std::string tempInput = Input::GetInput();
			if (tempInput == "1")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Avoidance> tempA = std::dynamic_pointer_cast<Avoidance>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Avoidance added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Avoidance>());

				std::cin.get();
				return;
			}
			else if (tempInput == "2")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Buff> tempA = std::dynamic_pointer_cast<Buff>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Buff added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Buff>());

				std::cin.get();
				return;
			}
			else if (tempInput == "3")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Fire> tempA = std::dynamic_pointer_cast<Fire>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Fire added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Fire>());

				std::cin.get();
				return;
			}
			else if (tempInput == "4")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Firebolt> tempA = std::dynamic_pointer_cast<Firebolt>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Firebolt added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Firebolt>());

				std::cin.get();
				return;
			}
			else if (tempInput == "5")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Freeze> tempA = std::dynamic_pointer_cast<Freeze>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Freeze added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Freeze>());

				std::cin.get();
				return;
			}
			else if (tempInput == "6")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Harm> tempA = std::dynamic_pointer_cast<Harm>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Harm added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Harm>());

				std::cin.get();
				return;
			}
			else if (tempInput == "7")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Heal> tempA = std::dynamic_pointer_cast<Heal>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Heal added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Heal>());

				std::cin.get();
				return;
			}
			else if (tempInput == "8")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<HolyBolt> tempA = std::dynamic_pointer_cast<HolyBolt>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell HolyBolt added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<HolyBolt>());

				std::cin.get();
				return;
			}
			else if (tempInput == "9")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Slowness> tempA = std::dynamic_pointer_cast<Slowness>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Slowness added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Slowness>());

				std::cin.get();
				return;
			}
			else if (tempInput == "10")
			{
				bool tempFound = false;

				for (auto& tempS : Player::Get()->GetSpells())
				{
					if (Ref<Weakness> tempA = std::dynamic_pointer_cast<Weakness>(tempS))
					{
						Print::Clear();
						Print::ColorText("You already have this spell!\n", Color::RED);
						tempFound = true;
						std::cin.get();
					}
				}

				if (tempFound)
				{
					continue;
				}

				Print::Clear();
				Print::ColorText("Spell Weakness added to spells!\n", Color::GREEN);
				Player::Get()->GetSpells().push_back(CreateRef<Weakness>());

				std::cin.get();
				return;
			}
		} while (true);
	}
}
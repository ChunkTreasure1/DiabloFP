#pragma once
#include "pch.h"

#include "Gameplay/Items/Equipment/Equipment.h"
#include "Gameplay/Items/Equipment/EquipmentFactory.h"

#include "Gameplay/Entities/Player.h"

namespace Diablo
{
	class Chestplate : public Equipment
	{
	public:
		Chestplate(const std::string& aName)
			: Equipment(aName)
		{}

		virtual bool Use() override
		{
			Stats tempS = Player::Get()->GetStats();

			tempS.Agility += myStatIncrease.Agility;
			tempS.Charisma += myStatIncrease.Charisma;
			tempS.Constitution += myStatIncrease.Constitution;

			tempS.Defence += myStatIncrease.Defence;
			tempS.Intelligence += myStatIncrease.Intelligence;
			tempS.Strength += myStatIncrease.Strength;

			tempS.Wisdom += myStatIncrease.Wisdom;

			Player::Get()->SetStats(tempS);

			return true;
		}
		virtual void Unuse() override
		{
			Stats tempS = Player::Get()->GetStats();

			tempS.Agility -= myStatIncrease.Agility;
			tempS.Charisma -= myStatIncrease.Charisma;
			tempS.Constitution -= myStatIncrease.Constitution;

			tempS.Defence -= myStatIncrease.Defence;
			tempS.Intelligence -= myStatIncrease.Intelligence;
			tempS.Strength -= myStatIncrease.Strength;

			tempS.Wisdom -= myStatIncrease.Wisdom;

			Player::Get()->SetStats(tempS);
		}

	public:
		static Equipment* Create() { return new Chestplate(""); }
		static std::string GetFactoryName() { return "Chestplate"; }

	private:
		static bool myRegistered;
	};
}
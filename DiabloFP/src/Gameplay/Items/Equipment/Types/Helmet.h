#pragma once
#include "pch.h"

#include "Gameplay/Items/Equipment/Equipment.h"
#include "Gameplay/Items/Equipment/EquipmentFactory.h"

#include "Gameplay/Entities/Player.h"

namespace Diablo 
{
	class Helmet : public Equipment
	{
	public:
		Helmet(const std::string& aName)
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
		static Ref<Equipment> Create() { return CreateScope<Helmet>(""); }
		static std::string GetFactoryName() { return "Helmet"; }

	private:
		static bool myRegistered;
	};
}
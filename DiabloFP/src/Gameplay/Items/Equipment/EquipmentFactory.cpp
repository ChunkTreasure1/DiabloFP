#include "pch.h"
#include "EquipmentFactory.h"

namespace Diablo 
{
	std::map<std::string, EquipmentFactory::TCreateMethod> EquipmentFactory::myMethods;

	Ref<Equipment> EquipmentFactory::CreateRandom()
	{
		Ref<Equipment> tempE = Create(Random::Int(0, myMethods.size() - 1));
		if (tempE == nullptr)
		{
			return nullptr;
		}

		std::string tempNames[6] = { "Epicality", "Slaughter", "Longsword", "Thomas", "Comp", "Radical" };
		tempE->SetName(tempNames[Random::Int(0, 5)]);

		Stats tempS;
		tempS.Agility = Random::Int(0, 5);
		tempS.Charisma = Random::Int(0, 5);

		tempS.Constitution = Random::Int(0, 5);
		tempS.Defence = Random::Int(0, 5);
		tempS.Intelligence = Random::Int(0, 5);

		tempS.Strength = Random::Int(0, 5);
		tempS.Wisdom = Random::Int(0, 5);

		tempE->SetStats(tempS);

		return tempE;
	}

	Ref<Equipment> EquipmentFactory::CreateHelmet(uint32_t aMax)
	{
		Ref<Equipment> tempE = Create("Helmet");
		std::string tempNames[3] = { "Skullcrack", "Headpunch", "Mindbreaker" };
		tempE->SetName(tempNames[Random::Int(0, 2)]);

		Stats tempS;
		tempS.Agility = Random::Int(0, aMax);
		tempS.Charisma = Random::Int(0, aMax);

		tempS.Constitution = Random::Int(0, aMax);
		tempS.Defence = Random::Int(0, aMax);
		tempS.Intelligence = Random::Int(0, aMax);

		tempS.Strength = Random::Int(0, aMax);
		tempS.Wisdom = Random::Int(0, aMax);

		tempE->SetStats(tempS);

		return tempE;
	}

	Ref<Equipment> EquipmentFactory::CreateChestplate(uint32_t aMax)
	{
		Ref<Equipment> tempE = Create("Chestplate");
		std::string tempNames[3] = { "ChestProt", "Skinbearer", "Armdes" };
		tempE->SetName(tempNames[Random::Int(0, 2)]);

		Stats tempS;
		tempS.Agility = Random::Int(0, aMax);
		tempS.Charisma = Random::Int(0, aMax);

		tempS.Constitution = Random::Int(0, aMax);
		tempS.Defence = Random::Int(0, aMax);
		tempS.Intelligence = Random::Int(0, aMax);

		tempS.Strength = Random::Int(0, aMax);
		tempS.Wisdom = Random::Int(0, aMax);

		tempE->SetStats(tempS);

		return tempE;
	}

	Ref<Equipment> EquipmentFactory::CreateLeggings(uint32_t aMax)
	{
		Ref<Equipment> tempE = Create("Leggings");
		std::string tempNames[3] = { "Legkrush", "Bonebreak", "LegProt" };
		tempE->SetName(tempNames[Random::Int(0, 2)]);

		Stats tempS;
		tempS.Agility = Random::Int(0, aMax);
		tempS.Charisma = Random::Int(0, aMax);

		tempS.Constitution = Random::Int(0, aMax);
		tempS.Defence = Random::Int(0, aMax);
		tempS.Intelligence = Random::Int(0, aMax);

		tempS.Strength = Random::Int(0, aMax);
		tempS.Wisdom = Random::Int(0, aMax);

		tempE->SetStats(tempS);

		return tempE;
	}

	Ref<Equipment> EquipmentFactory::CreateBoots(uint32_t aMax)
	{
		Ref<Equipment> tempE = Create("Boots");
		std::string tempNames[3] = { "Feetkeep", "Bearer", "FeetProt" };
		tempE->SetName(tempNames[Random::Int(0, 2)]);

		Stats tempS;
		tempS.Agility = Random::Int(0, aMax);
		tempS.Charisma = Random::Int(0, aMax);

		tempS.Constitution = Random::Int(0, aMax);
		tempS.Defence = Random::Int(0, aMax);
		tempS.Intelligence = Random::Int(0, aMax);

		tempS.Strength = Random::Int(0, aMax);
		tempS.Wisdom = Random::Int(0, aMax);

		tempE->SetStats(tempS);

		return tempE;
	}

	bool EquipmentFactory::Register(const std::string& aName, TCreateMethod aFunc)
	{
		if (auto tempIT = myMethods.find(aName); tempIT == myMethods.end())
		{
			myMethods[aName] = aFunc;
			return true;
		}

		return false;
	}
	Ref<Equipment> EquipmentFactory::Create(const std::string& aName)
	{
		if (auto tempIT = myMethods.find(aName); tempIT != myMethods.end())
		{
			return tempIT->second();
		}

		return nullptr;
	}
}
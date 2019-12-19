#include "pch.h"
#include "EquipmentFactory.h"

namespace Diablo 
{
	std::map<std::string, EquipmentFactory::TCreateMethod> EquipmentFactory::myMethods;

	Equipment* EquipmentFactory::CreateRandom()
	{
		Equipment* tempE = Create(Random::Int(0, myMethods.size() - 1));
		
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

	Equipment* EquipmentFactory::CreateHelmet(uint32_t aMax)
	{
		Equipment* tempE = Create("Helmet");
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

	Equipment* EquipmentFactory::CreateChestplate(uint32_t aMax)
	{
		Equipment* tempE = Create("Chestplate");
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

	Equipment* EquipmentFactory::CreateLeggings(uint32_t aMax)
	{
		Equipment* tempE = Create("Leggings");
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

	Equipment* EquipmentFactory::CreateBoots(uint32_t aMax)
	{
		Equipment* tempE = Create("Boots");
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
}
#pragma once
#include "Equipment.h"

namespace Diablo
{
	class EquipmentFactory 
	{
		using TCreateMethod = Equipment * (*)();

	public:
		EquipmentFactory() = delete;

		static Equipment* CreateRandom();

		static Equipment* CreateHelmet(uint32_t aMax);
		static Equipment* CreateChestplate(uint32_t aMax);
		static Equipment* CreateLeggings(uint32_t aMax);
		static Equipment* CreateBoots(uint32_t aMax);


		static bool Register(const std::string& aName, TCreateMethod aFunc) 
		{
			if (myMethods.count(aName) == 0)
			{
				myMethods[aName] = aFunc;
				return true;
			}

			return false;
		}
		static Equipment* Create(const std::string& aName)
		{
			if (auto tempIT = myMethods.find(aName); tempIT != myMethods.end())
			{
				return tempIT->second();
			}

			return nullptr;
		}
		static Equipment* Create(uint32_t anI)
		{
			std::map<std::string, TCreateMethod>::const_iterator tempEnd = myMethods.end();
			
			int tempCounter = 0;
			for (std::map<std::string, TCreateMethod>::const_iterator tempIT = myMethods.begin(); tempIT != tempEnd; ++tempIT)
			{
				tempCounter++;
				if (tempCounter == anI)
				{
					return tempIT->second();
				}
			}

			return nullptr;
		}

		static uint32_t GetSize() { return (uint32_t)myMethods.size(); }
	private:
		static std::map<std::string, TCreateMethod> myMethods;
	};
}
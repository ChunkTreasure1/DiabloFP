#pragma once
#include "Equipment.h"

#include "Core/Utility/Utility.h"

namespace Diablo
{
	class EquipmentFactory
	{
	public:
		using TCreateMethod = Ref<Equipment>(*)();

	public:
		EquipmentFactory() = delete;

		static Ref<Equipment> CreateRandom();

		static Ref<Equipment> CreateHelmet(uint32_t aMax);
		static Ref<Equipment> CreateChestplate(uint32_t aMax);
		static Ref<Equipment> CreateLeggings(uint32_t aMax);
		static Ref<Equipment> CreateBoots(uint32_t aMax);


		static bool Register(const std::string& aName, TCreateMethod aFunc);
		static Ref<Equipment> Create(const std::string& aName);
		static Ref<Equipment> Create(uint32_t anI)
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
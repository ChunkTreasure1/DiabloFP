#pragma once

#include "Gameplay/Items/Item.h"
#include "Core/Utility/Utility.h"

namespace Diablo
{
	class ItemFactory
	{
	public:
		using TCreateMethod = Scope<Item>(*)();

	public:
		ItemFactory() = delete;

		static bool Register(const std::string& aName, TCreateMethod aFunc)
		{
		if (auto tempIT = myMethods.find(aName); tempIT == myMethods.end())
			{
				myMethods[aName] = aFunc;
				return true;
			}

			return false;
		}

		static Scope<Item> Create(const std::string& aName)
		{
			if (auto tempIT = myMethods.find(aName); tempIT != myMethods.end())
			{
				return tempIT->second();
			}

			return nullptr;
		}

		static Scope<Item> Create(uint32_t anI)
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
#pragma once

#include "Gameplay/Items/Item.h"

#include <map>

namespace Diablo
{
	class ItemFactory
	{
	public:
		using TCreateMethod = Item * (*)();

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

		static Item* Create(const std::string& aName)
		{
			if (auto tempIT = myMethods.find(aName); tempIT != myMethods.end())
			{
				return tempIT->second();
			}

			return nullptr;
		}

		static Item* Create(uint32_t anI)
		{
			std::map<std::string, TCreateMethod>::const_iterator tempEnd = myMethods.end();

			int counter = 0;
			for (std::map<std::string, TCreateMethod>::const_iterator tempIT = myMethods.begin(); tempIT != tempEnd; ++tempIT)
			{
				counter++;

				if (counter == anI)
					return tempIT->second();
			}
		}

		static uint32_t GetSize() { return myMethods.size(); }

	private:
		static std::map<std::string, TCreateMethod> myMethods;
	};
}
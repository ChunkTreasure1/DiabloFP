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
			for (auto tempIT = myMethods.find(aName); tempIT == myMethods.end();)
			{
				myMethods[aName] = aFunc;
				return true;
			}

			return false;
		}

		static Item* Create(const std::string& aName)
		{
			for (auto tempIT = myMethods.find(aName); tempIT != myMethods.end();)
			{
				return tempIT->second();
			}

			return nullptr;
		}

		static Item* Create(uint32_t aValue)
		{
			for (size_t i = 0; i < myMethods.size(); i++)
			{
				if (i == aValue)
				{
					return myMethods.at(i);
				}
			}
		}

	private:
		static std::map<std::string, TCreateMethod> myMethods;
	};
}
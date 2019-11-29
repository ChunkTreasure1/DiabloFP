#pragma once

#include <vector>
#include <memory>

#include "Gameplay/Items/Item.h"

namespace Diablo
{
	class Chest
	{
	public:
		Chest() {}

		void AddItem(Item* anItem) { myItems.push_back(anItem); }

	private:
		std::vector<Item*> myItems;
	};
}
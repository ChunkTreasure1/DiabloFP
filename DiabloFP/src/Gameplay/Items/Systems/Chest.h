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

		inline void AddItem(Item* anItem) { myItems.push_back(anItem); }

		inline void SetCharPos(uint32_t aPos) { myCharPos = aPos; }
		inline const uint32_t GetCharPos() { return myCharPos; }

	private:
		std::vector<Item*> myItems;
		uint32_t myCharPos;
	};
}
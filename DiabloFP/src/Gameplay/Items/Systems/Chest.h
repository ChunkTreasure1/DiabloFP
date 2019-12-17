#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Gameplay/Items/Item.h"

namespace Diablo
{
	class Chest
	{
	public:
		Chest() = default;

		inline void AddItem(Item* anItem) { myItems.push_back(anItem); }

		//Setting
		inline void SetCharPos(const glm::vec2& aPos) { myCharPos = aPos; }
		inline void SetStrPos(uint32_t aPos) { myStrPos = aPos; }

		//Getting
		inline const glm::vec2& GetCharPos() { return myCharPos; }
		inline const uint32_t GetStrPos() { return myStrPos; }
		inline std::vector<Item*>& GetItems() { return myItems; }

		void OpenChest(std::shared_ptr<Chest>& someChest);

	private:
		std::vector<Item*> myItems;
		glm::vec2 myCharPos;
		uint32_t myStrPos;
	};
}
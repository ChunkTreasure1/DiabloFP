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

		inline void AddItem(Ref<Item> anItem) { myItems.push_back(std::move(anItem)); }

		//Setting
		inline void SetCharPos(const glm::vec2& aPos) { myCharPos = aPos; }
		inline void SetStrPos(uint32_t aPos) { myStrPos = aPos; }

		//Getting
		inline const glm::vec2& GetCharPos() { return myCharPos; }
		inline const uint32_t GetStrPos() { return myStrPos; }
		inline std::vector<Ref<Item>>& GetItems() { return myItems; }

		void OpenChest(Ref<Chest>& someChest);

	private:
		std::vector<Ref<Item>> myItems;
		glm::vec2 myCharPos;
		uint32_t myStrPos;
	};
}
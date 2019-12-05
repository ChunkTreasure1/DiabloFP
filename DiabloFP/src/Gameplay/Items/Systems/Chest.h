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
		Chest() {}

		inline void AddItem(Item* anItem) { myItems.push_back(anItem); }

		inline void SetCharPos(const glm::vec2& aPos) { myCharPos = aPos; }
		inline const glm::vec2& GetCharPos() { return myCharPos; }

	private:
		std::vector<Item*> myItems;
		glm::vec2 myCharPos;
	};
}
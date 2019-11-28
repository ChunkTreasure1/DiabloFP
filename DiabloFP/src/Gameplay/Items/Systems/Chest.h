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

	private:
		std::vector<std::shared_ptr<Item>> mypItems;
	};
}
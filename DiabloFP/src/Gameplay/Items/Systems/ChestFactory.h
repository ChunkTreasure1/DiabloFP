#pragma once

#include <memory>
#include "Chest.h"

namespace Diablo
{
	class ChestFactory
	{
	public:
		static std::shared_ptr<Chest> CreateChest(uint32_t aCharPos);
	};
}
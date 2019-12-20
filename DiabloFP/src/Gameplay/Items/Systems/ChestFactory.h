#pragma once

#include <memory>
#include "Chest.h"

namespace Diablo
{
	class ChestFactory
	{
	public:
		static Ref<Chest> CreateChest(const glm::vec2& aCharPos);
	};
}
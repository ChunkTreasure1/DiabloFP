#include "ChestFactory.h"
#include "Gameplay/Items/Systems/ItemFactory.h"
#include "Core/Utility/Random.h"

#include <time.h>

namespace Diablo
{
	std::shared_ptr<Chest> ChestFactory::CreateChest(const glm::vec2& aCharPos)
	{
		std::shared_ptr<Chest> tempChest = std::make_shared<Chest>();

		tempChest->SetCharPos(aCharPos);
		uint32_t tempLootCount = Random::Int(1, 10);
		for (size_t i = 0; i < tempLootCount; i++)
		{
			tempChest->AddItem(ItemFactory::Create(Random::Int(0, ItemFactory::GetSize())));
		}

		return tempChest;
	}
}
#include "ChestFactory.h"
#include "Gameplay/Items/Systems/ItemFactory.h"

#include <time.h>

namespace Diablo
{
	std::shared_ptr<Chest> ChestFactory::CreateChest()
	{
		srand(time(NULL));
		std::shared_ptr<Chest> tempChest;

		uint32_t tempLootCount = rand() % 10 + 1;
		for (size_t i = 0; i < tempLootCount; i++)
		{
			tempChest->AddItem(ItemFactory::Create());
		}

		return std::move(tempChest);
	}
}
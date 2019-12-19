#include "pch.h"
#include "ChestFactory.h"
#include "Gameplay/Items/Systems/ItemFactory.h"
#include "Gameplay/Items/Equipment/EquipmentFactory.h"

namespace Diablo
{
	std::shared_ptr<Chest> ChestFactory::CreateChest(const glm::vec2& aCharPos)
	{
		std::shared_ptr<Chest> tempChest = std::make_shared<Chest>();

		tempChest->SetCharPos(aCharPos);
		uint32_t tempLootCount = Random::Int(1, 10);
		for (size_t i = 0; i < tempLootCount; i++)
		{
			int tempI = Random::Int(0, 1);
			if (tempI == 0)
			{
				tempChest->AddItem(ItemFactory::Create(Random::Int(0, ItemFactory::GetSize() - 1)));
			}
			else 
			{
				tempChest->AddItem(EquipmentFactory::CreateRandom());
			}
		}

		return tempChest;
	}
}
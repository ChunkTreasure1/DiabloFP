#include "pch.h"
#include "ChestFactory.h"
#include "Gameplay/Items/HealthPotion.h"
#include "Gameplay/Items/Scroll.h"
#include "Gameplay/Items/Tome.h"

#include "Gameplay/Items/Equipment/EquipmentFactory.h"

namespace Diablo
{
	Ref<Chest> ChestFactory::CreateChest(const glm::vec2& aCharPos)
	{
		Ref<Chest> tempChest = CreateRef<Chest>();

		tempChest->SetCharPos(aCharPos);
		uint32_t tempLootCount = Random::Int(1, 10);
		for (size_t i = 0; i < tempLootCount; i++)
		{
			int tempI = Random::Int(0, 1);
			if (tempI == 0)
			{
				int tempI = Random::Int(0, 2);
				if (tempI == 0)
				{
					tempChest->AddItem(CreateRef<HealthPotion>());
				}
				else if (tempI == 1)
				{
					tempChest->AddItem(CreateRef<HealthPotion>());
				}
				else if (tempI == 2)
				{
					tempChest->AddItem(CreateRef<HealthPotion>());
				}
			}
			else 
			{
				auto tempE = EquipmentFactory::CreateRandom();

				if (tempE != nullptr)
				{
					tempChest->AddItem(tempE);
				}
			}
		}

		return tempChest;
	}
}
#include "HealthPotion.h"

#include "Gameplay/Entities/Player.h"
#include "Systems/ItemFactory.h"

namespace Diablo
{
	//bool HealthPotion::myRegistered = ItemFactory::Register(HealthPotion::GetFactoryName(), HealthPotion::CreateMethod);

	HealthPotion::HealthPotion()
		: Item("Health Potion")
	{}

	bool HealthPotion::Use()
	{
		Player* tempPlayer = Player::Get();
		tempPlayer->SetHealth(tempPlayer->GetHealth() + myHealthAdd);

		return true;
	}
}
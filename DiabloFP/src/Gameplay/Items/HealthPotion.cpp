#include "pch.h"
#include "HealthPotion.h"

#include "Gameplay/Entities/Player.h"
#include "Systems/ItemFactory.h"

namespace Diablo
{
	//bool HealthPotion::myRegistered = REGISTER_ITEM(HealthPotion)

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
#include "HealthPotion.h"

#include "Gameplay/Entities/Player.h"

namespace Diablo
{
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
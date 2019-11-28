#include "HealthPotion.h"

#include "Gameplay/Entities/Player.h"

namespace Diablo
{
	HealthPotion::HealthPotion(float anAmount)
		: Item("Health Potion"), myHealthAdd(anAmount)
	{}

	bool HealthPotion::Use()
	{
		Player* tempPlayer = Player::Get();
		tempPlayer->SetHealth(tempPlayer->GetHealth() + myHealthAdd);

		return true;
	}
}
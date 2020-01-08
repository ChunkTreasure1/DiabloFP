#pragma once

#include "Gameplay/Fighting/Attack.h"

namespace Diablo
{
	class Sword : public Attack
	{
	public:
		Sword()
			: Attack("Sword")
		{
			myBaseDamage = 5.f;
			mySpeed = 7; //0 - 10
		}
	};
}
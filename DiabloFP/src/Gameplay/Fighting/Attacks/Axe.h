#pragma once

#include "Gameplay/Fighting/Attack.h"

namespace Diablo
{
	class Axe : public Attack
	{
	public:
		Axe()
			: Attack("Axe")
		{
			myBaseDamage = 5.5f;
			mySpeed = 6;
		}
	};
}
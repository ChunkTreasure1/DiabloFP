#pragma once

#include "Gameplay/Fighting/Attack.h"

namespace Diablo
{
	class Spell : public Attack
	{
	public:
		Spell()
			: Attack("Spell")
		{
			myDamage = 8.f;
			mySpeed = 4; //0 - 10
		}
	};
}
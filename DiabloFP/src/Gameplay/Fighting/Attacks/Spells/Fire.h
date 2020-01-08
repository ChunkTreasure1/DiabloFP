#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Fire final : public Spell
	{
	public:
		Fire()
			: Spell("Fire")
		{
			myBaseDamage = 15.f;
			myDamage = myBaseDamage;
			myManaCost = 35.f;

			myCategory = SpellCategory::Attack;
		}
	};
}
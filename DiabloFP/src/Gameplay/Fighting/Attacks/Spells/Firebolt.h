#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Firebolt final : public Spell
	{
	public:
		Firebolt()
			: Spell("Firebolt")
		{
			myBaseDamage = 7.f;
			myDamage = myBaseDamage;
			myManaCost = 25.f;

			myCategory = SpellCategory::Attack;
		}
	};
}
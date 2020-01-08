#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Heal final : public Spell
	{
	public:
		Heal()
			: Spell("Heal")
		{
			myBaseDamage = 10.f;
			myDamage = myBaseDamage;
			myManaCost = 16.f;

			myCategory = SpellCategory::Support;
		}
	};
}
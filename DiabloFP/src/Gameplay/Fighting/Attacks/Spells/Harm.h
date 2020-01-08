#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Harm final : public Spell
	{
	public:
		Harm()
			: Spell("Harm")
		{
			myBaseDamage = 10.f;
			myDamage = myBaseDamage;
			myManaCost = 23.f;

			myCategory = SpellCategory::Attack;
		}
	};
}
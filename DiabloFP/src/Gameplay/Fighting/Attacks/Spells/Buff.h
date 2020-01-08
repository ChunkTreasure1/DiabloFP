#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Buff final : public Spell
	{
	public:
		Buff()
			: Spell("Buff")
		{
			myBaseDamage = 3.f;
			myDamage = myBaseDamage;
			myManaCost = 20.f;

			myCategory = SpellCategory::Support;
		}
	};
}
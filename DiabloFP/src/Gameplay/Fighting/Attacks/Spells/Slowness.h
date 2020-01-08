#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Slowness final : public Spell
	{
	public:
		Slowness()
			: Spell("Slowness")
		{
			myBaseDamage = 0.f;
			myDamage = myBaseDamage;
			myManaCost = 19.f;

			myCategory = SpellCategory::Control;
		}
	};
}
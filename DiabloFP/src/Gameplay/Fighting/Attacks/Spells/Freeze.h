#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Freeze final : public Spell
	{
	public:
		Freeze()
			: Spell("Freeze")
		{
			myBaseDamage = 0;
			myDamage = myBaseDamage;

			myManaCost = 18.f;
			myCategory = SpellCategory::Control;
		}
	};
}
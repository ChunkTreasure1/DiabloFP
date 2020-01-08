#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Avoidance final : public Spell
	{
	public:
		Avoidance()
			: Spell("Avoidance")
		{
			myBaseDamage = 0;
			myDamage = 0;
			myManaCost = 30.f;

			myCategory = SpellCategory::Control;
		}
	};
}
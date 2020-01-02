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
			myDamage = 7.f;
			myManaCost = 5.f;

			myCategory = SpellCategory::Attack;
		}
	};
}
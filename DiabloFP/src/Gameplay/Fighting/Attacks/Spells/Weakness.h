#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class Weakness final : public Spell
	{
	public:
		Weakness()
			: Spell("Weakness")
		{
			myBaseDamage = 5.f;
			myDamage = myBaseDamage;
			myManaCost = 18.f;

			myCategory = SpellCategory::Support;
		}
	};
}
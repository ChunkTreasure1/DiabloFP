#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class HolyBolt final : public Spell
	{
	public:
		HolyBolt()
			: Spell("HolyBolt")
		{
			myBaseDamage = 3.f;
			myDamage = myBaseDamage;
			myManaCost = 15.f;

			myCategory = SpellCategory::Attack;
		}
	};
}
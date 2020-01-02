#pragma once

#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	class HolyBolt final : public Spell
	{
		HolyBolt()
			: Spell("HolyBolt")
		{
			myDamage = 3.f;
			myManaCost = 2.f;

			myCategory = SpellCategory::Attack;
		}
	};
}
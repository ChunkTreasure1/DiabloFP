#pragma once

#include "Gameplay/Fighting/Attack.h"

namespace Diablo
{
	enum class SpellCategory
	{
		Attack,
		Support,
		Control
	};

	class Spell : public Attack
	{
	public:
		Spell(const std::string& someName)
			: Attack(someName)
		{}

	protected:
		float myManaCost;
		SpellCategory myCategory;
	};
}
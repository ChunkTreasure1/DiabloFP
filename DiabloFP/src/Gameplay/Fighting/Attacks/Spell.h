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
			: Attack(someName), myCategory(SpellCategory::Control), myManaCost(0.f)
		{}

		virtual ~Spell() { }

		inline const float GetManaCost() { return myManaCost; }
		inline const SpellCategory GetCategory() { return myCategory; }

	protected:
		float myManaCost;
		SpellCategory myCategory;

	public:

		static std::string CategoryToString(SpellCategory someCat)
		{
			switch (someCat)
			{
				case SpellCategory::Attack:   return "Attack";
				case SpellCategory::Control:  return "Control";
				case SpellCategory::Support:  return "Support;";
			}
		}
	};
}
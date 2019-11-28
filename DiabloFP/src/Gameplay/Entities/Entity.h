#pragma once

#include <functional>

namespace Diablo
{
	struct Stats
	{
		int Defence;
		int Agility;

		int Strength;
		int Constitution;
		int Intelligence;

		int Wisdom;
		int Charisma;
	};

	class Entity
	{
	public:
		//Getting
		virtual inline const float GetHealth() const { return myHealth; }
		virtual inline const uint32_t GetStrength() const { return myStats.Strength; }
		virtual inline const uint32_t GetDefence() const { return myStats.Defence; }

		virtual inline const uint32_t GetAgility() const { return myStats.Agility; }
		virtual inline const uint32_t GetConstitution() const { return myStats.Constitution; }
		virtual inline const uint32_t GetIntelligence() const { return myStats.Intelligence; }

		virtual inline const uint32_t GetWisdom() const { return myStats.Wisdom; }
		virtual inline const uint32_t GetCharisma() const { return myStats.Charisma; }
		virtual inline Stats& GetStats() { return myStats; }
		//Setting
		virtual inline void SetHealth(float aHealth) { myHealth = aHealth; }
		virtual inline void SetStrength(int anAttackDamage) { myStats.Strength = anAttackDamage; }
		virtual inline void SetDefence(int aDefence) { myStats.Defence = aDefence; }

		virtual inline void SetStats(Stats someStats) { myStats = someStats; }

	protected:
		Entity(float aHealth)
			: myHealth(aHealth)
		{}

		float myHealth;
		Stats myStats = Stats();
	};
}
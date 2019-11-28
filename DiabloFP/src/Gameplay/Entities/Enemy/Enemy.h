#pragma once

#include <memory>

#include "Gameplay/Entities/Entity.h"
#include "Gameplay/Items/Item.h"
#include "Gameplay/Fighting/Attack.h"

namespace Diablo
{
	enum class EnemyChoice
	{
		Attack,
		Defend
	};

	class Enemy : public Entity
	{
	public:
		Enemy(float aHealth)
			: Entity(aHealth), myMaxHealth(aHealth)
		{}
		~Enemy() {}

		//Getting
		inline const std::string GetName() const { return myName; }
		inline const uint32_t GetKillXP() const { return myKillXP; }
		inline std::shared_ptr<Item>& GetDropLoot() { return myDropLoot; }

		inline float GetMaxHealth() const { return myMaxHealth; }
		inline std::shared_ptr<Attack> GetAttack() const { return myAttack; }

		//Setting
		inline void SetName(std::string aName) { myName = aName; }
		inline void SetKillXP(uint32_t someValue) { myKillXP = someValue; }
		inline void SetLoot(std::shared_ptr<Item> someLoot) { myDropLoot = std::move(someLoot); }

		inline void SetMaxHealth(float aHealth) { myMaxHealth = aHealth; }
		inline void SetAttack(std::shared_ptr<Attack>& anAttack) { myAttack = std::move(anAttack); }

		EnemyChoice GetCombatChoice();

	private:
		std::string myName;
		uint32_t myKillXP;

		float myMaxHealth;
		std::shared_ptr<Item> myDropLoot;
		std::shared_ptr<Attack> myAttack;
	};
}
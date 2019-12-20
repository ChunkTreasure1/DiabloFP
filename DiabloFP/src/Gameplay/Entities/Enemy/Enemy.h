#pragma once

#include <memory>

#include "Gameplay/Entities/Entity.h"
#include "Gameplay/Items/Item.h"
#include "Gameplay/Fighting/Attack.h"

#include <glm/glm.hpp>

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
			: Entity(aHealth), myMaxHealth(aHealth), myStrPos(0), myCharPos(0, 0),
			myKillXP(0)
		{}
		~Enemy() {}

		//Getting
		inline const std::string GetName() const { return myName; }
		inline const uint32_t GetKillXP() const { return myKillXP; }
		inline Ref<Item>& GetDropLoot() { return myDropLoot; }

		inline float GetMaxHealth() const { return myMaxHealth; }
		inline const glm::vec2& GetCharPos() { return myCharPos; }
		inline const uint32_t GetStrPos() { return myStrPos; }
		inline Ref<Attack> GetAttack() const { return myAttack; }


		//Setting
		inline void SetName(std::string aName) { myName = aName; }
		inline void SetKillXP(uint32_t someValue) { myKillXP = someValue; }
		inline void SetLoot(Ref<Item> someLoot) { myDropLoot = std::move(someLoot); }

		inline void SetMaxHealth(float aHealth) { myMaxHealth = aHealth; }
		inline void SetAttack(Ref<Attack>& anAttack) { myAttack = std::move(anAttack); }
		inline void SetCharPos(const glm::vec2& aPos) { myCharPos = aPos; }
		inline void SetStrPos(uint32_t aPos) { myStrPos = aPos; }

		EnemyChoice GetCombatChoice();

	private:
		std::string myName;
		uint32_t myKillXP;
		glm::vec2 myCharPos;
		uint32_t myStrPos;

		float myMaxHealth;
		Ref<Item> myDropLoot;
		Ref<Attack> myAttack;
	};
}
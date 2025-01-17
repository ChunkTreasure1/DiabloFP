#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "Gameplay/Fighting/Attack.h"
#include "Gameplay/Items/Systems/Inventory.h"

#include "Gameplay/Map/Map.h"
#include "Gameplay/Fighting/FightSystem.h"
#include "Gameplay/Fighting/Attacks/Spell.h"

namespace Diablo
{
	enum class PlayerType
	{
		Warrior,
		Rogue,
		Sorcerer
	};

	class Player : public Entity
	{
	public:
		Player(float aHealth, uint32_t aMapWidth);
		~Player() = default;

		//Setting
	    void SetXPos(float aPos);
		void SetYPos(float aPos);
		inline void SetAngle(float anAngle) { myAngle = anAngle; }

		inline void SetType(PlayerType aPlayerType) { myPlayerType = aPlayerType; }
		void SetStats(PlayerType aPlayerType);
		inline void SetStats(Stats someStats) { myStats = someStats; myHealth = myBaseHealth * myStats.Constitution; }

		inline void SetShouldExit(bool someState) { myShouldExit = someState; }
		inline void SetMana(float someVal) { myMana = someVal; }
		inline void AddMana(float someVal) { myMana += someVal; }

		//Getting
		inline const float GetXPos() { return myXPos; }
		inline const float GetYPos() { return myYPos; }
		inline const float GetAngle() { return myAngle; }

		inline const float GetSpeed() { return mySpeed; }
		inline const float GetFOV() { return myFOV; }
		inline const float GetDepth() { return myDepth; }

		inline const PlayerType GetType() const { return myPlayerType; }
		inline static Player* Get() { return myInstance; }
		inline const Scope<Inventory>& GetInventory() const { return mypInventory; }

		Ref<Attack> GetAttack(Ref<Enemy>& someEnemy);
		Ref<Spell> GetSpell(Ref<Enemy>& someEnemy);

		inline const bool GetShouldExit() { return myShouldExit; }
		inline const float GetMana() { return myMana; }
		inline std::vector<Ref<Spell>>& GetSpells() { return mySpells; }

		void Update();
		void UpdateAttacks();

	private:
		void AttackEnemy(Ref<Enemy>& aEnemy);
		void OpenChest(Ref<Chest>& aChest);
		void Exit();

		void CheckForEnemy();
		void CheckForChest();
		void CheckForExit();

	private:
		float myXPos;
		float myYPos;
		float myFOV;

		float myDepth;
		float mySpeed;
		float myAngle;

		float myLevel;
		float myBaseHealth;
		float myMana;
		float myMaxMana;
		
		bool myShouldExit;
		PlayerType myPlayerType;
		uint32_t myMapWidth;

		Scope<Inventory> mypInventory;
		std::vector<Ref<Attack>> myAttacks;
		std::vector<Ref<Spell>> mySpells;

	private:
		static Player* myInstance;
	};
}
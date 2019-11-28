#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "Gameplay/Fighting/Attack.h"
#include "Gameplay/Items/Systems/Inventory.h"

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
		Player(float aHealth);
		~Player() = default;

		//Setting
		inline void SetXPos(float aPos) { myXPos = aPos; }
		inline void SetYPos(float aPos) { myYPos = aPos; }
		inline void SetAngle(float anAngle) { myAngle = anAngle; }

		inline void SetPlayerType(PlayerType aPlayerType) { myPlayerType = aPlayerType; }
		void SetPlayerStats(PlayerType aPlayerType);

		//Getting
		inline const float GetXPos() { return myXPos; }
		inline const float GetYPos() { return myYPos; }
		inline const float GetAngle() { return myAngle; }

		inline const float GetSpeed() { return mySpeed; }
		inline const float GetFOV() { return myFOV; }
		inline const float GetDepth() { return myDepth; }

		inline const PlayerType GetPlayerType() const { return myPlayerType; }
		inline static Player* Get() { return myInstance; }
		inline const std::unique_ptr<Inventory>& GetInventory() const { return mypInventory; }

		std::shared_ptr<Attack> GetAttack();
		void Update();

	private:
		float myXPos;
		float myYPos;
		float myFOV;

		float myDepth;
		float mySpeed;
		float myAngle;

		float myLevel;
		PlayerType myPlayerType;

		std::unique_ptr<Inventory> mypInventory;
		std::vector<std::shared_ptr<Attack>> myAttacks;

	private:
		static Player* myInstance;
	};
}
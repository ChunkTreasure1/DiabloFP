#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "Gameplay/Fighting/Attack.h"
#include "Gameplay/Items/Systems/Inventory.h"

#include "Gameplay/Map/Map.h"
#include "Gameplay/Fighting/FightSystem.h"

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
		inline void SetXPos(float aPos)
		{
			myXPos = aPos;
			uint32_t tempCharPos = (int)myYPos + (int)myXPos * myMapWidth;
			if (Map::Get()->GetStringMap().c_str()[tempCharPos - myMapWidth] == '*')
			{
				for (auto& tempE : Map::Get()->GetEnemies())
				{
					FightSystem::Get()->FightEnemy(tempE);
				}
			}
			else if (Map::Get()->GetStringMap().c_str()[tempCharPos + myMapWidth] == '*')
			{
				for (auto& tempE : Map::Get()->GetEnemies())
				{
					FightSystem::Get()->FightEnemy(tempE);
				}
			}
			else if (Map::Get()->GetStringMap().c_str()[tempCharPos - 1] == '*')
			{
				for (auto& tempE : Map::Get()->GetEnemies())
				{
					FightSystem::Get()->FightEnemy(tempE);
				}
			}
			else if (Map::Get()->GetStringMap().c_str()[tempCharPos + 1] == '*')
			{
				for (auto& tempE : Map::Get()->GetEnemies())
				{
					FightSystem::Get()->FightEnemy(tempE);
				}
			}
		}
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
		uint32_t myMapWidth;

		std::unique_ptr<Inventory> mypInventory;
		std::vector<std::shared_ptr<Attack>> myAttacks;

	private:
		static Player* myInstance;
	};
}
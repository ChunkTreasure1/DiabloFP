#pragma once

#include <string>
#include "Gameplay/Entities/Enemy/Enemy.h"
#include "Gameplay/Items/Systems/Chest.h"

#include "Core/Utility/Utility.h"

namespace Diablo
{
	class Map
	{
	public:
		Map(std::wstring aMap, uint32_t aSize, uint32_t aRoomCount, std::vector<Ref<Enemy>> someEnemies, std::vector<Ref<Chest>> someChests, Ref<Enemy> aBoss)
			: myStringMap(aMap), myMapSize(aSize), myRoomCount(aRoomCount), myEnemies(someEnemies), myChests(someChests), myBoss(aBoss)
		{
			myInstance = this;
		}
		~Map() = default;

		//Getting
		inline std::wstring& GetStringMap() { return myStringMap; }
		inline const uint32_t GetRoomCount() { return myRoomCount; }
		inline const uint32_t GetMapSize() { return myMapSize; }

		inline std::vector<Ref<Enemy>>& GetEnemies() { return myEnemies; }
		inline std::vector<Ref<Chest>>& GetChests() { return myChests; }
		inline Ref<Enemy>& GetBoss() { return myBoss; }

	public:
		static Map* Get() { return myInstance; }
		static void Set(Map* aMap) { myInstance = aMap; }

	private:
		std::vector<Ref<Enemy>> myEnemies;
		std::vector<Ref<Chest>> myChests;

		Ref<Enemy> myBoss;

		std::wstring myStringMap;
		uint32_t myRoomCount;
		uint32_t myMapSize;

	private:
		static Map* myInstance;
	};
}
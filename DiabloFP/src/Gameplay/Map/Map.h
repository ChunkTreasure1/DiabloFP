#pragma once

#include <string>
#include "Gameplay/Entities/Enemy/Enemy.h"
#include "Gameplay/Items/Systems/Chest.h"

namespace Diablo
{
	class Map
	{
	public:
		Map(std::wstring aMap, uint32_t aSize, uint32_t aRoomCount, std::vector<Ref<Enemy>> someEnemies, std::vector<Ref<Chest>> someChests)
			: myStringMap(aMap), myMapSize(aSize), myRoomCount(aRoomCount), myEnemies(someEnemies), myChests(someChests)
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

	public:
		static Map* Get() { return myInstance; }

	private:
		std::vector<Ref<Enemy>> myEnemies;
		std::vector<Ref<Chest>> myChests;

		std::wstring myStringMap;
		uint32_t myRoomCount;
		uint32_t myMapSize;

	private:
		static Map* myInstance;
	};
}
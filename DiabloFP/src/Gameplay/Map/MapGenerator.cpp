#include "MapGenerator.h"
#include "Map.h"

#include <utility>
#include <time.h>

#include "Gameplay/Entities/Enemy/EnemyFactory.h"
#include "Gameplay/Items/Systems/ChestFactory.h"

namespace Diablo
{
	Map* MapGenerator::GenerateMap()
	{
		uint32_t tempMapSize = 18;
		uint32_t tempMaxRoomSize = 5;

		std::vector<Room> tempRooms = GenerateRooms(tempMapSize, tempMaxRoomSize);

		std::wstring tempMap;

		for (size_t i = 0; i < tempMapSize * tempMapSize; i++)
		{
			tempMap += L" ";
		}

		for (auto& aR : tempRooms)
		{
			for (auto& aT : aR.GetTiles())
			{
				float y = aT.Position.y;
				float x = aT.Position.x;

				if (aT.Position.y > 0)
				{
					tempMap[x + (y * tempMapSize - 1)] = aT.Type;
				}
				else
				{
					tempMap[x] = aT.Type;
				}
			}
		}
		for (size_t i = 0; i < tempMapSize - 3; i++)
		{
			tempMap[i + ((tempMapSize - 1) * (tempMapSize - 1) - tempMapSize - 1)] = '#';
		}

		std::vector<std::shared_ptr<Enemy>> tempEnemies = GenerateEnemies(tempMapSize);
		std::vector<std::shared_ptr<Chest>> tempChests = GenerateChests(tempMapSize);

		//map += L"################";
		//map += L"#....#.....#...#";
		//map += L"#....#.....#...#";
		//map += L"#....#.....#...#";
		//map += L"####.#.....#####";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"#..............#";
		//map += L"################";

		return new Map(tempMap, tempMapSize, 1, tempEnemies);
	}

	std::vector<Room> MapGenerator::GenerateRooms(uint32_t aMapSize, uint32_t aRoomSize)
	{
		std::vector<Room> tempRooms;

		vec2 tempLastStartPos(1, 0);

		uint32_t tempRoomCount = (aMapSize * aMapSize) / (aRoomSize * aRoomSize) - aMapSize / aRoomSize;
		for (size_t i = 0; i < tempRoomCount; i++)
		{
			vec2 tempStart = vec2(tempLastStartPos);
			vec2 tempEnd = vec2(tempStart.x + aRoomSize, tempStart.y + aRoomSize);

			if (tempEnd.x >= aMapSize)
			{
				tempStart.x = 1;
				tempStart.y += aRoomSize;
				tempEnd = vec2(tempStart.x + aRoomSize, tempStart.y + aRoomSize);
			}

			Room tempRoom;
			for (size_t i = 0; i < aRoomSize; i++)
			{
				if (i == aRoomSize / 2 && tempStart.y != 0)
				{
					tempRoom.GetTiles().push_back(Tile('.', vec2(tempStart.x + i - 1, tempStart.y)));
				}
				else if (tempStart.y == 0)
				{
					tempRoom.GetTiles().push_back(Tile('#', vec2(tempStart.x + i - 1, tempStart.y)));
				}
				else
				{
					tempRoom.GetTiles().push_back(Tile('#', vec2(tempStart.x + i, tempStart.y)));
				}
			}

			for (size_t y = 1; y < aRoomSize; y++)
			{
				int tempVal = aRoomSize;

				if (tempStart.x == 0)
				{
					tempVal = aRoomSize + 1;
				}

				for (size_t x = 0; x < aRoomSize; x++)
				{
					if (tempStart.x + x == 1)
					{
						tempRoom.GetTiles().push_back(Tile('#', vec2(tempStart.x + x, tempStart.y + y)));
						continue;
					}

					if (x == aRoomSize - 1)
					{
						if (y == aRoomSize / 2 && tempEnd.x != aMapSize - 2)
						{
							tempRoom.GetTiles().push_back(Tile('.', vec2(tempStart.x + x, tempStart.y + y)));
						}
						else
						{
							tempRoom.GetTiles().push_back(Tile('#', vec2(tempStart.x + x, tempStart.y + y)));
						}
						continue;
					}

					tempRoom.GetTiles().push_back(Tile('.', vec2(tempStart.x + x, tempStart.y + y)));
				}
			}

			tempLastStartPos = vec2(tempStart.x + aRoomSize, tempStart.y);

			tempRooms.push_back(tempRoom);
		}

		/*std::vector<Room> tempRooms;

		vec2 tempLastStartPos(0, 0);
		vec2 tempLastEndPos(aRoomSize, aRoomSize);

		uint32_t tempRoomCount = (aMapSize * aMapSize) / (aRoomSize * aRoomSize);

		for (size_t i = 0; i < tempRoomCount; i++)
		{
			vec2 tempStart = vec2(tempLastStartPos.x, tempLastStartPos.y);
			vec2 tempEnd(tempStart.x + aRoomSize, tempStart.y + aRoomSize);

			if (tempEnd.x >= aMapSize)
			{
				tempStart.x = 0;
				tempStart.y = tempStart.y + aRoomSize;
			}

			Room tempRoom;

			for (size_t i = 0; i < aRoomSize; i++)
			{
				tempRoom.GetTiles().push_back(Tile('#', vec2(tempStart.x + i, tempLastStartPos.y + aRoomSize)));
			}

			for (size_t y = 1; y < aRoomSize; y++)
			{
				for (size_t x = 0; x < aRoomSize; x++)
				{
					if (x == 0 || x == aRoomSize - 1)
					{
						tempRoom.GetTiles().push_back(Tile('#', vec2(tempStart.x + x, tempStart.y + y)));
						continue;
					}
					
					tempRoom.GetTiles().push_back(Tile('.', vec2(tempStart.x + x, tempStart.y + y)));
				}
			}

			for (size_t i = 0; i < aRoomSize; i++)
			{
				tempRoom.GetTiles().push_back(Tile('#', vec2(tempStart.x + i, tempLastStartPos.y + 2 * aRoomSize)));
			}

			tempRooms.push_back(tempRoom);

			tempLastStartPos = tempStart;
			tempLastEndPos = vec2(tempStart.x + aRoomSize, tempStart.y + aRoomSize);
		}*/

		return tempRooms;
	}

	std::vector<std::shared_ptr<Enemy>> MapGenerator::GenerateEnemies(uint32_t aMapSize)
	{
		srand(time(NULL));
		std::vector<std::shared_ptr<Enemy>> tempEnemies;

		uint32_t tempEnemyCount = rand() % 10 + 1;

		for (size_t i = 0; i < tempEnemyCount; i++)
		{
			std::shared_ptr<Enemy> tempEnemy = EnemyFactory::CreateEnemy(rand() % (aMapSize * aMapSize));

			tempEnemies.push_back(std::move(tempEnemy));
		}

		return tempEnemies;
	}
	std::vector<std::shared_ptr<Chest>> MapGenerator::GenerateChests(uint32_t aMapSize)
	{
		srand(time(NULL));
		std::vector<std::shared_ptr<Chest>> tempChests;

		uint32_t tempChestCount = rand() % 10 + 1;
		for (size_t i = 0; i < tempChestCount; i++)
		{
			std::shared_ptr<Chest> tempChest = ChestFactory::CreateChest();
		}

		return tempChests;
	}
}
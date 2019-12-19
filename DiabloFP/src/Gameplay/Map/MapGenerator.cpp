#include "pch.h"
#include "MapGenerator.h"
#include "Map.h"

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
					tempMap[(uint32_t)(x + (y * tempMapSize - 1))] = aT.Type;
				}
				else
				{
					tempMap[(uint32_t)x] = aT.Type;
				}
			}
		}
		for (size_t i = 0; i < tempMapSize - 3; i++)
		{
			tempMap[i + ((tempMapSize - 1) * (tempMapSize - 1) - tempMapSize - 1)] = '#';
		}

		std::vector<std::shared_ptr<Enemy>> tempEnemies = GenerateEnemies(tempMapSize);
		std::vector<std::shared_ptr<Chest>> tempChests = GenerateChests(tempMapSize);

		for (auto& tempE : tempEnemies)
		{
			uint32_t tempPos = (uint32_t)(tempE->GetCharPos().y + (tempMapSize * tempE->GetCharPos().x) - 1);
			tempE->SetStrPos(tempPos);
			tempMap[tempPos] = '*';
		}
		for (auto& tempC : tempChests)
		{
			uint32_t tempPos = (uint32_t)(tempC->GetCharPos().y + (tempMapSize * tempC->GetCharPos().x) - 1);
			tempC->SetStrPos(tempPos);
			tempMap[tempPos] = '=';
		}

		//(2, 3)
		//map += L"################..";
		//map += L"#....#.....#...#..";
		//map += L"#....#.....#...#..";
		//map += L"#....#.....#...#..";
		//map += L"####.#.....#####..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"#..............#..";
		//map += L"################..";

		return new Map(tempMap, tempMapSize, 1, tempEnemies, tempChests);
	}

	std::vector<Room> MapGenerator::GenerateRooms(uint32_t aMapSize, uint32_t aRoomSize)
	{
		std::vector<Room> tempRooms;

		glm::vec2 tempLastStartPos(1, 0);

		uint32_t tempRoomCount = (aMapSize * aMapSize) / (aRoomSize * aRoomSize) - aMapSize / aRoomSize;
		for (size_t i = 0; i < tempRoomCount; i++)
		{
			glm::vec2 tempStart(tempLastStartPos);
			glm::vec2 tempEnd(tempStart.x + aRoomSize, tempStart.y + aRoomSize);

			if (tempEnd.x >= aMapSize)
			{
				tempStart.x = 1;
				tempStart.y += aRoomSize;
				tempEnd = glm::vec2(tempStart.x + aRoomSize, tempStart.y + aRoomSize);
			}

			Room tempRoom;
			for (size_t i = 0; i < aRoomSize; i++)
			{
				if (i == aRoomSize / 2 && tempStart.y != 0)
				{
					tempRoom.GetTiles().push_back(Tile('.', glm::vec2(tempStart.x + i - 1, tempStart.y)));
				}
				else if (tempStart.y == 0)
				{
					tempRoom.GetTiles().push_back(Tile('#', glm::vec2(tempStart.x + i - 1, tempStart.y)));
				}
				else
				{
					tempRoom.GetTiles().push_back(Tile('#', glm::vec2(tempStart.x + i, tempStart.y)));
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
						tempRoom.GetTiles().push_back(Tile('#', glm::vec2(tempStart.x + x, tempStart.y + y)));
						continue;
					}

					if (x == aRoomSize - 1)
					{
						if (y == aRoomSize / 2 && tempEnd.x != aMapSize - 2)
						{
							tempRoom.GetTiles().push_back(Tile('.', glm::vec2(tempStart.x + x, tempStart.y + y)));
						}
						else
						{
							tempRoom.GetTiles().push_back(Tile('#', glm::vec2(tempStart.x + x, tempStart.y + y)));
						}
						continue;
					}

					tempRoom.GetTiles().push_back(Tile('.', glm::vec2(tempStart.x + x, tempStart.y + y)));
				}
			}

			tempLastStartPos = glm::vec2(tempStart.x + aRoomSize, tempStart.y);

			tempRooms.push_back(tempRoom);
		}

		return tempRooms;
	}

	std::vector<std::shared_ptr<Enemy>> MapGenerator::GenerateEnemies(uint32_t aMapSize)
	{
		std::vector<std::shared_ptr<Enemy>> tempEnemies;

		uint32_t tempEnemyCount = Random::Int(1, 10);

		for (size_t i = 0; i < tempEnemyCount; i++)
		{
			std::shared_ptr<Enemy> tempEnemy = EnemyFactory::Create(GeneratePosition(aMapSize));

			tempEnemies.push_back(std::move(tempEnemy));
		}

		return tempEnemies;
	}
	std::vector<std::shared_ptr<Chest>> MapGenerator::GenerateChests(uint32_t aMapSize)
	{
		std::vector<std::shared_ptr<Chest>> tempChests;

		uint32_t tempChestCount = Random::Int(1, 10);
		for (size_t i = 0; i < tempChestCount; i++)
		{
			std::shared_ptr<Chest> tempChest = ChestFactory::CreateChest(GeneratePosition(aMapSize));
			tempChests.push_back(tempChest);
		}

		return tempChests;
	}

	glm::vec2 MapGenerator::GeneratePosition(uint32_t aMapSize)
	{
		glm::vec2 tempPos;
		tempPos.x = Random::Int(1, aMapSize - 4);
		tempPos.y = Random::Int(1, aMapSize - 3);

		return tempPos;
	}
}
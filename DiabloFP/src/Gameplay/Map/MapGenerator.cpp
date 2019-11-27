#include "MapGenerator.h"
#include "Map.h"

#include <utility>

namespace Diablo
{
	Map* MapGenerator::GenerateMap()
	{
		uint32_t tempMapSize = 16;
		uint32_t tempMaxRoomSize = 4;

		std::vector<Room> tempRooms = GenerateRooms(tempMapSize, tempMaxRoomSize);

		std::wstring tempMap;
		for (size_t i = 0; i < tempMapSize; i++)
		{
			tempMap += L"#";
		}

		for (size_t x = 0; x < tempMapSize; x++)
		{
			for (size_t y = 0; y < tempMapSize; y++)
			{
				if (y == 0 || y == tempMapSize - 1)
				{
					tempMap += L"#";
					continue;
				}


				tempMap += L".";
			}
		}

		for (size_t i = 0; i < tempMapSize; i++)
		{
			tempMap += L"#";
		}

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

		return new Map(tempMap, tempMapSize, 1);
	}

	std::vector<Room> MapGenerator::GenerateRooms(uint32_t aMapSize, uint32_t aRoomSize)
	{
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
				tempRoom.GetWalls().insert(std::pair<char, vec2>('#', vec2(tempStart.x + i, 0)));
			}

			for (size_t x = 0; x < aRoomSize; x++)
			{
				for (size_t y = 0; y < aRoomSize - 2; y++)
				{
					if (y == 0 || y == aRoomSize - 1)
					{
						tempRoom.GetWalls().insert(std::pair<char, vec2>('#', vec2(tempStart.x + x, tempStart.y + y)));
					}
					
				}
			}

			for (size_t i = 0; i < aRoomSize; i++)
			{
				tempRoom.GetWalls().insert(std::pair<char, vec2>('#', vec2(tempStart.x + i, aRoomSize)));
			}
		}

		return std::vector<Room>();
	}
}
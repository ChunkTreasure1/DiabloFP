#pragma once

#include <string>
#include <vector>

#include "Gameplay/Room/Room.h"
#include "Map.h"

namespace Diablo
{
	class MapGenerator
	{
	public:
		static Map* GenerateMap();

	private:
		static std::vector<Room> GenerateRooms(uint32_t aMapSize, uint32_t aRoomSize);
	};
}
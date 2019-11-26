#pragma once

#include <string>
#include "Gameplay/Map/Map.h"

namespace Diablo
{
	class MapGenerator
	{
	public:
		static Map* GenerateMap();
	};
}
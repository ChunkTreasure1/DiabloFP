#include "MapGenerator.h"
#include "Map.h"

namespace Diablo
{
	Map* MapGenerator::GenerateMap()
	{
		std::wstring map;
		map += L"#########.......";
		map += L"#...............";
		map += L"#.......########";
		map += L"#..............#";
		map += L"#......##......#";
		map += L"#......##......#";
		map += L"#..............#";
		map += L"###............#";
		map += L"##.............#";
		map += L"#......####..###";
		map += L"#......#.......#";
		map += L"#......#.......#";
		map += L"#..............#";
		map += L"#......#########";
		map += L"#..............#";
		map += L"################";

		return new Map(map, 16);
	}
}
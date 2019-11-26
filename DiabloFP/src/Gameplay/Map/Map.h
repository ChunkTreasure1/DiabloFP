#pragma once

#include <string>

namespace Diablo
{
	class Map
	{
	public:
		Map(std::wstring map, uint32_t size) 
			: myStringMap(map), myMapSize(size)
		{}
		~Map() = default;

		//Getting
		inline const std::wstring& GetStringMap() { return myStringMap; }
		inline const uint32_t GetRoomCount() { return myRoomCount; }
		inline const uint32_t GetMapSize() { return myMapSize; }

	private:
		std::wstring myStringMap;
		uint32_t myRoomCount;
		uint32_t myMapSize = 64;
	};
}
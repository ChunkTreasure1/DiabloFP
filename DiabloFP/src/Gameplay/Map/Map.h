#pragma once

#include <string>

namespace Diablo
{
	class Map
	{
	public:
		Map(std::wstring aMap, uint32_t aSize, uint32_t aRoomCount) 
			: myStringMap(aMap), myMapSize(aSize), myRoomCount(aRoomCount)
		{}
		~Map() = default;

		//Getting
		inline const std::wstring& GetStringMap() { return myStringMap; }
		inline const uint32_t GetRoomCount() { return myRoomCount; }
		inline const uint32_t GetMapSize() { return myMapSize; }

	private:
		std::wstring myStringMap;
		uint32_t myRoomCount;
		uint32_t myMapSize;
	};
}
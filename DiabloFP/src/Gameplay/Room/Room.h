#pragma once

#include <map>
#include <string>

namespace Diablo
{
	struct vec2
	{
	public:
		vec2(float anX, float aY)
		{
			x = anX;
			y = aY;
		}

		float x, y;
	};

	struct Tile
	{
	public:
		Tile(char aT, vec2 aPos)
			: Type(aT), Position(aPos)
		{}

		char Type;
		vec2 Position;
	};

	class Room
	{
	public:
		Room() {}

		//Getting
		inline std::vector<Tile>& GetTiles() { return myTiles; }
		
	private:
		std::vector<Tile> myTiles;
	};
}
#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

namespace Diablo
{
	struct Tile
	{
	public:
		Tile(char aT, glm::vec2 aPos)
			: Type(aT), Position(aPos)
		{}

		char Type;
		glm::vec2 Position;
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
#pragma once

#include <map>
#include <string>

namespace Diablo
{
	class vec2
	{
	public:
		vec2(float anX, float aY)
		{
			x = anX;
			y = aY;
		}

		float x, y;
	};

	class Room
	{
	public:
		Room() {}

		//Getting
		inline std::map<char, vec2> GetWalls() const { return myWalls; }
		
	private:
		std::map<char, vec2> myWalls;
	};
}
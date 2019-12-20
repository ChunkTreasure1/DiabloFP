#pragma once

#include <string>
#include "Gameplay/Entities/Enemy/Enemy.h"
#include "Gameplay/Items/Systems/Chest.h"

#define BUFFER_WIDTH 120

namespace Diablo
{
	enum class Color
	{
		DARK_BLUE = 1,
		DARK_GREEN,
		DARK_TORQUSE,
		DARK_RED,
		DARK_PURPLE,
		DARK_YELLOW,
		DARK_WHITE,
		DARK_GREY,
		BLUE,
		GREEN,
		TORQUSE,
		RED,
		PURPLE,
		YELLOW,
		WHITE
	};

	class Print
	{
	public:
		static void Clear(char aFill = ' ');
		static void Text(std::string aText);
		static void ColorText(const std::string& aText, Color aColor);
		static void Middle(const std::string& aText, Color aColor, uint32_t aY);

		static void Stats(const Ref<Enemy>& someEnemy);
		static void Chests(Ref<Chest>& someChest);
		static void SetPosition(uint32_t anX, uint32_t aY);

		//To strings
		static std::string ToString(float aValue);
		static std::string ToString(int aValue);
		static std::string ToString(uint32_t aValue);
	};
}
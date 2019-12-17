#pragma once

#include <string>
#include "Gameplay/Entities/Enemy/Enemy.h"
#include "Gameplay/Items/Systems/Chest.h"

namespace Diablo
{
	enum ColorCodes
	{
		COLOR_DARK_BLUE = 1,
		COLOR_DARK_GREEN,
		COLOR_DARK_TORQUSE,
		COLOR_DARK_RED,
		COLOR_DARK_PURPLE,
		COLOR_DARK_YELLOW,
		COLOR_DARK_WHITE,
		COLOR_DARK_GREY,
		COLOR_BLUE,
		COLOR_GREEN,
		COLOR_TORQUSE,
		COLOR_RED,
		COLOR_PURPLE,
		COLOR_YELLOW,
		COLOR_WHITE
	};

	class Print
	{
	public:
		static void Clear(char aFill = ' ');
		static void Text(std::string aText);
		static void ColorText(const std::string& aText, ColorCodes aColor);
		static void Middle(const std::string& aText, ColorCodes aColor, uint32_t aY);

		static void Stats(const std::shared_ptr<Enemy>& someEnemy);
		static void Chests(std::shared_ptr<Chest>& someChest);
		static void SetPosition(uint32_t anX, uint32_t aY);

		//To strings
		static std::string ToString(float aValue);
		static std::string ToString(int aValue);
		static std::string ToString(uint32_t aValue);
	};
}
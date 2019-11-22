#pragma once

#include <string>

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
		static void PrintText(std::string aText);
		static void PrintColorText(const std::string& aText, ColorCodes aColor);
		static void PrintMiddle(const std::string& aText, ColorCodes aColor);

		static void PrintPlayer();
		static void PrintStats();
		static std::string ToString(float aValue);
	};
}
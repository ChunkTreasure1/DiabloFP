#include "Print.h"

#include <iostream>
#include <iomanip>
#include <sstream>

#include <Windows.h>

namespace Diablo
{
	void Print::Clear(char aFill)
	{
		COORD tempTL = { 0,0 };
		CONSOLE_SCREEN_BUFFER_INFO s;
		HANDLE tempConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(tempConsole, &s);
		DWORD tempWritten, tempCells = s.dwSize.X * s.dwSize.Y;
		FillConsoleOutputCharacter(tempConsole, aFill, tempCells, tempTL, &tempWritten);
		FillConsoleOutputAttribute(tempConsole, s.wAttributes, tempCells, tempTL, &tempWritten);
		SetConsoleCursorPosition(tempConsole, tempTL);
	}

	void Print::PrintText(std::string aText)
	{
		std::cout << aText.c_str();
	}

	void Print::PrintColorText(const std::string& aText, ColorCodes aColor)
	{
		HANDLE tempHConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(tempHConsole, aColor);
		std::cout << aText.c_str();
		SetConsoleTextAttribute(tempHConsole, 15);                    
	}

	void Print::PrintMiddle(const std::string& aText, ColorCodes aColor)
	{
		std::cout << std::setw((140 / 2) + aText.length() / 2) << std::right << aText;
	}

	std::string Print::ToString(float aValue)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << aValue;

		return ss.str();
	}
}
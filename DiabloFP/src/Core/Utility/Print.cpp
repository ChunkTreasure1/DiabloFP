#include "pch.h"
#include "Print.h"
#include "Gameplay/Entities/Player.h"

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

	void Print::Text(std::string aText)
	{
		std::cout << aText.c_str();
	}

	void Print::ColorText(const std::string& aText, Color aColor)
	{
		HANDLE tempHConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(tempHConsole, static_cast<int>(aColor));
		std::cout << aText.c_str();
		SetConsoleTextAttribute(tempHConsole, 15); 
	}

	void Print::Middle(const std::string& aText, Color aColor, uint32_t aY)
	{
		SetPosition(BUFFER_WIDTH / 2, aY);
		ColorText(aText, aColor);
	}

	void Print::Stats(const std::shared_ptr<Enemy>& someEnemy)
	{
		uint32_t tempHeight = 20;

		////////Frame////////
		SetPosition(BUFFER_WIDTH / 2, 0);
		for (uint32_t i = 0; i < BUFFER_WIDTH / 2; i++)
		{
			Print::Text("-");
		}

		for (uint32_t i = 1; i < tempHeight; i++)
		{
			SetPosition(BUFFER_WIDTH / 2, i);
			Print::Text("|");
		
			SetPosition((BUFFER_WIDTH / 4) * 3, i);
			Print::Text("|");

			SetPosition(BUFFER_WIDTH - 1, i);
			Print::Text("|");
		}

		SetPosition(BUFFER_WIDTH / 2, tempHeight);
		for (uint32_t i = 0; i < BUFFER_WIDTH / 2; i++)
		{
			Print::Text("-");
		}
		//////////////////////

		////////Player////////
		SetPosition(BUFFER_WIDTH / 2 + 2, 2);
		Print::ColorText("Name: Player", Color::GREEN);

		SetPosition(BUFFER_WIDTH / 2 + 2, 4);
		Print::ColorText("Defence: " + ToString(Player::Get()->GetDefence()), Color::GREEN);

		SetPosition(BUFFER_WIDTH / 2 + 2, 5);
		Print::ColorText("Agility: " + ToString(Player::Get()->GetAgility()), Color::GREEN);

		SetPosition(BUFFER_WIDTH / 2 + 2, 6);
		Print::ColorText("Strength: " + ToString(Player::Get()->GetStrength()), Color::GREEN);

		SetPosition(BUFFER_WIDTH / 2 + 2, 7);
		Print::ColorText("Constitution: " + ToString(Player::Get()->GetConstitution()), Color::GREEN);

		SetPosition(BUFFER_WIDTH / 2 + 2, 8);
		Print::ColorText("Intelligence: " + ToString(Player::Get()->GetIntelligence()), Color::GREEN);

		SetPosition(BUFFER_WIDTH / 2 + 2, 9);
		Print::ColorText("Wisdom: " + ToString(Player::Get()->GetWisdom()), Color::GREEN);

		SetPosition(BUFFER_WIDTH / 2 + 2, 10);
		Print::ColorText("Charisma: " + ToString(Player::Get()->GetCharisma()), Color::GREEN);

		SetPosition(BUFFER_WIDTH / 2 + 2, 12);
		Print::ColorText("Health: " + ToString(Player::Get()->GetHealth()), Color::GREEN);
		//////////////////////

		////////Enemy////////
		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 2);
		Print::ColorText("Name: " + someEnemy->GetName(), Color::GREEN);

		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 4);
		Print::ColorText("Defence: " + ToString(someEnemy->GetDefence()), Color::GREEN);

		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 5);
		Print::ColorText("Agility: " + ToString(someEnemy->GetAgility()), Color::GREEN);

		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 6);
		Print::ColorText("Strength: " + ToString(someEnemy->GetStrength()), Color::GREEN);

		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 7);
		Print::ColorText("Constitution: " + ToString(someEnemy->GetConstitution()), Color::GREEN);

		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 8);
		Print::ColorText("Intelligence: " + ToString(someEnemy->GetIntelligence()), Color::GREEN);

		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 9);
		Print::ColorText("Wisdom: " + ToString(someEnemy->GetWisdom()), Color::GREEN);

		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 10);
		Print::ColorText("Charisma: " + ToString(someEnemy->GetCharisma()), Color::GREEN);

		SetPosition((BUFFER_WIDTH / 4) * 3 + 2, 12);
		Print::ColorText("Health: " + ToString(someEnemy->GetHealth()), Color::GREEN);
		/////////////////////

		SetPosition(0, 6);
	}

	void Print::Chests(std::shared_ptr<Chest>& someChest)
	{
		uint32_t tempHeight = 20;
		uint32_t tempOffset = 2;
		tempHeight += tempOffset;

		////////Frame////////
		SetPosition(BUFFER_WIDTH / 4, 1);
		for (uint32_t i = 0; i < BUFFER_WIDTH / 2 + 1; i++)
		{
			ColorText("-", Color::DARK_PURPLE);
		}

		for (uint32_t i = tempOffset; i < tempHeight; i++)
		{
			SetPosition(BUFFER_WIDTH / 4, i);
			ColorText("|", Color::DARK_PURPLE);

			SetPosition((BUFFER_WIDTH / 4) * 3, i);
			ColorText("|", Color::DARK_PURPLE);
		}

		SetPosition(BUFFER_WIDTH / 4, tempHeight);
		for (uint32_t i = 0; i < BUFFER_WIDTH / 2 + 1; i++)
		{
			ColorText("-", Color::DARK_PURPLE);
		}
		/////////////////////

		////////Content////////
		Middle("Chest", Color::PURPLE, 3);

		for (uint32_t i = 0; i < someChest->GetItems().size(); i++)
		{
			SetPosition(BUFFER_WIDTH / 4 + 2, i + 5);
			ColorText(ToString(i + 1) + ". " + someChest->GetItems()[i]->GetName(), Color::RED);
		}
		///////////////////////

		SetPosition(0, 0);
	}

	void Print::SetPosition(uint32_t anX, uint32_t aY)
	{
		COORD tempCoord;
		tempCoord.X = anX;
		tempCoord.Y = aY;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tempCoord);
	}

	std::string Print::ToString(float aValue)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << aValue;

		return ss.str();
	}
	std::string Print::ToString(int aValue)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << aValue;

		return ss.str();
	}
	std::string Print::ToString(uint32_t aValue)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << aValue;

		return ss.str();
	}
}
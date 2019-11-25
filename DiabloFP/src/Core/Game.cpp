#include "Game.h"

#include <chrono>

#include "Input/Input.h"
#include "Print.h"

namespace Diablo
{
	Game* Game::myInstance = nullptr;

	Game::Game()
		: myIsRunning(true), myScreenWidth(120), myScreenHeight(40),
		myMapHeight(16), myMapWidth(16), myIs3D(false), myDefaultConsole(GetStdHandle(STD_OUTPUT_HANDLE))
	{
		myInstance = this;
		Renderer::Initialize(myScreenWidth, myScreenHeight);

		myPlayer = new Player();
	}

	Game::~Game()
	{
		delete myPlayer;
	}

	void Game::Run()
	{
		std::wstring tempMap;
		tempMap += L"#########.......";
		tempMap += L"#...............";
		tempMap += L"#.......########";
		tempMap += L"#..............#";
		tempMap += L"#......##......#";
		tempMap += L"#......##......#";
		tempMap += L"#..............#";
		tempMap += L"###............#";
		tempMap += L"##.............#";
		tempMap += L"#......####..###";
		tempMap += L"#......#.......#";
		tempMap += L"#......#.......#";
		tempMap += L"#..............#";
		tempMap += L"#......#########";
		tempMap += L"#..............#";
		tempMap += L"################";
		

		auto tempTP1 = std::chrono::system_clock::now();
		auto tempTP2 = std::chrono::system_clock::now();

		StartMenu();

		while (myIsRunning)
		{
			//Setup timing so the console runs at constant speed
			tempTP2 = std::chrono::system_clock::now();
			std::chrono::duration<float> tempElapsed = tempTP2 - tempTP1;
			tempTP1 = tempTP2;
			float tempElapsedTime = tempElapsed.count();

			if (myIs3D)
			{
				Input::HandleInput(tempElapsedTime, tempMap);

				//Draws all of the "3D";
				Renderer::Draw(tempElapsedTime);
			}
		}
	}

	void Game::StartMenu()
	{
		Print::Clear();
		do
		{
			Print::Clear();
			Print::PrintColorText("DIABLO\n\n", COLOR_RED);
			Print::PrintColorText("1. Start Game\n", COLOR_DARK_RED);
			Print::PrintColorText("2. Quit\n", COLOR_DARK_RED);

			std::string tempInput = Input::GetInput();
			if (tempInput == "1")
			{

			}
			else if (tempInput == "2")
			{

			}

		} while (true);
	}
}
#include "Game.h"

#include <chrono>

#include "Input/Input.h"
#include "Gameplay/Map/MapGenerator.h"
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

		myDefaultConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		myPlayer = new Player();
	}

	Game::~Game()
	{
		delete myPlayer;
	}

	void Game::Run()
	{
		auto tempTP1 = std::chrono::system_clock::now();
		auto tempTP2 = std::chrono::system_clock::now();

		do
		{
			bool tempRunning = StartMenu();
			myMap = MapGenerator::GenerateMap();
			Renderer::Update(myMap->GetMapSize(), myMap->GetStringMap());

			while (tempRunning)
			{
				//Setup timing so the console runs at constant speed
				tempTP2 = std::chrono::system_clock::now();
				std::chrono::duration<float> tempElapsed = tempTP2 - tempTP1;
				tempTP1 = tempTP2;
				float tempElapsedTime = tempElapsed.count();

				if (myIs3D)
				{
					Input::HandleInput(tempElapsedTime, myMap);

					//Draws all of the "3D";
					Renderer::Draw(tempElapsedTime);
				}
			}

		} while (myIsRunning);
	}

	bool Game::StartMenu()
	{
		do
		{
			Print::Clear();

			for (size_t i = 0; i < 4; i++)
			{
				for (size_t j = 0; j < 4; j++)
				{
					Print::PrintColorText("x", COLOR_GREEN);
				}
				std::cout << "\n";
			}

			Print::PrintColorText("DIABLO\n\n", COLOR_RED);
			Print::PrintColorText("1. Start Game\n", COLOR_DARK_RED);
			Print::PrintColorText("2. Quit\n", COLOR_DARK_RED);

			std::string tempInput = Input::GetInput();
			if (tempInput == "1")
			{
				Print::Clear();
				Print::PrintColorText("You wake up in a cold and dark room. Where are you? How will you get out?\n", COLOR_GREEN);
				Print::PrintColorText("Use your instincts.\n", COLOR_GREEN);
				Print::PrintColorText("Press ANY button to continue.", COLOR_BLUE);
				std::cin.get();

				SetIs3D(true);
				return true;
			}
			else if (tempInput == "2")
			{
				return false;
			}
			else
			{
				Print::Clear();
				Print::PrintColorText("Wrong input!", COLOR_RED);
			}

		} while (true);

		return false;
	}
}
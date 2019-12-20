#include "pch.h"
#include "Game.h"

#include "Input/Input.h"
#include "Gameplay/Map/MapGenerator.h"
#include "Utility/Print.h"

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

		myPlayer = new Player(50.f, myMapWidth + 2);
		myFightSystem = CreateRef<FightSystem>();
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
			Print::ColorText("DIABLO\n\n", Color::RED);
			Print::ColorText("1. Start Game\n", Color::DARK_RED);
			Print::ColorText("2. Quit\n", Color::DARK_RED);

			std::string tempInput = Input::GetInput();
			if (tempInput == "1")
			{
				myPlayer->SetType(GetPlayerType());

				Print::Clear();
				Print::ColorText("You wake up in a cold and dark room. Where are you? How will you get out?\n", Color::GREEN);
				Print::ColorText("Use your instincts...\n", Color::GREEN);
				Print::ColorText("Press ANY button to continue.", Color::BLUE);
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
				Print::ColorText("Wrong input!", Color::RED);
			}

		} while (true);

		return false;
	}

	PlayerType Game::GetPlayerType()
	{
		bool tempSelecting = true;
		do
		{
			Print::Clear();
			Print::ColorText("Choose player type: \n", Color::DARK_BLUE);
			Print::ColorText("1. Warrior\n", Color::DARK_BLUE);
			Print::ColorText("2. Rogue\n", Color::DARK_BLUE);
			Print::ColorText("3. Sorcerer\n", Color::DARK_BLUE);

			std::string tempSelected = Input::GetInput();

			if (tempSelected == "1")
			{
				Print::Clear();
				Print::ColorText("You selected warrior!", Color::YELLOW);
				myPlayer->SetStats(PlayerType::Warrior);
				std::cin.get();

				return PlayerType::Warrior;
			}
			else if (tempSelected == "2")
			{
				Print::Clear();
				Print::ColorText("You selected rogue!", Color::YELLOW);
				myPlayer->SetStats(PlayerType::Rogue);
				std::cin.get();

				return PlayerType::Rogue;
			}
			else if (tempSelected == "3")
			{
				Print::Clear();
				Print::ColorText("You selected sorcerer", Color::YELLOW);
				myPlayer->SetStats(PlayerType::Sorcerer);
				std::cin.get();

				return PlayerType::Sorcerer;
			}
			else
			{
				Print::ColorText("Wrong input!\n", Color::RED);
				continue;
			}
			tempSelecting = false;
		} while (tempSelecting);

		return PlayerType();
	}
}
#include "Game.h"

#include <chrono>

#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "Print.h"

namespace Diablo
{
	Game* Game::myInstance = nullptr;

	Game::Game()
		: myIsRunning(true), myScreenWidth(120), myScreenHeight(40), 
		myMapHeight(16), myMapWidth(16), myIs3D(true)
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

		//StartMenu();

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
				Prnt

		} while (true);
	}
}
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>

#include "Core/Game.h"
#include "Core/Utility/ExitException.h"

int main()
{
	Diablo::Game* tempGame;

	try
	{
		tempGame = new Diablo::Game();
		tempGame->Run();

		delete tempGame;
		return 0;
	}
	catch (const Diablo::ExitException& e)
	{
		return 0;
	}
}

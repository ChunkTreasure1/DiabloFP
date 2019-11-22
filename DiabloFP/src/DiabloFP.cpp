#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>

#include "Core/Game.h"

int main()
{
	Diablo::Game* tempGame = new Diablo::Game();
	tempGame->Run();

	delete tempGame;
	return 0;
}

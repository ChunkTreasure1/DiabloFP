#include "Chest.h"

#include "Core/Utility/Print.h"
#include "Core/Game.h"

#include <iostream>

namespace Diablo
{
	void Chest::OpenChest()
	{
		Game::Get()->SetIs3D(false);

		Print::Clear();
		Print::PrintColorText("Chest:\n", ColorCodes::COLOR_PURPLE);

		uint32_t tempCount = 0;
		for (auto& tempI : myItems)
		{
			tempCount++;
			Print::PrintColorText(tempCount + ". " + tempI->GetName() + "\n", COLOR_DARK_PURPLE);
		}

		std::cin.get();
	}
}
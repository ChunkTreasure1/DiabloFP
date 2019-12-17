#include "Chest.h"

#include "Core/Utility/Print.h"
#include "Core/Game.h"

#include <iostream>

namespace Diablo
{
	void Chest::OpenChest(std::shared_ptr<Chest>& someChest)
	{
		Game::Get()->SetIs3D(false);

		Print::Clear();
		Print::Chests(someChest);

		std::cin.get();
	}
}
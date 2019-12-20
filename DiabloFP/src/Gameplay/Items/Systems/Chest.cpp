#include "pch.h"
#include "Chest.h"
#include "Core/Game.h"

namespace Diablo
{
	void Chest::OpenChest(Ref<Chest>& someChest)
	{
		Game::Get()->SetIs3D(false);

		Print::Clear();
		Print::Chests(someChest);

		std::cin.get();
	}
}
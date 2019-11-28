#pragma once

#include "Gameplay/Items/Item.h"
#include <memory>
#include <vector>

namespace Diablo
{
	class Inventory
	{
	public:

		//Adding
		bool AddItem(std::shared_ptr<Item> apItem);

		//Get
		std::vector<std::shared_ptr<Item>>& GetVector() { return mypItems; }

		void OpenInventory();

	private:
		void Show();
		void ShowItemList();
		void UseItem();

		void RemoveItem();

	private:
		uint32_t myMaxSpace;
		std::vector<std::shared_ptr<Item>> mypItems;
	};
}
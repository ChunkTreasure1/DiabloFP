#pragma once

#include "Gameplay/Items/Item.h"
#include <memory>
#include <vector>

#include "Gameplay/Items/Equipment/Equipment.h"

namespace Diablo
{
	class Inventory
	{
	public:
		Inventory();
		~Inventory();

		//Adding
		bool AddItem(std::shared_ptr<Item> apItem);

		//Get
		std::vector<std::shared_ptr<Item>>& GetVector() { return mypItems; }

		void OpenInventory();
		void SelectEquipment();

	private:
		void Show();
		void ShowItemList();
		void UseItem();

		void RemoveItem();
	private:
		uint32_t myMaxSpace;
		std::vector<std::shared_ptr<Item>> mypItems;
		std::vector<Equipment*> myEquipment;
	};
}
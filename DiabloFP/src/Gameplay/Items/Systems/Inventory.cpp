#include "Inventory.h"

#include "Gameplay/Items/Scroll.h"
#include "Core/Utility/Print.h"
#include "Core/Input/Input.h"

namespace Diablo
{
	bool Inventory::AddItem(std::shared_ptr<Item> apItem)
	{
		if (mypItems.size() < myMaxSpace)
		{
			mypItems.push_back(apItem);
			return true;
		}

		return false;
	}

	void Inventory::OpenInventory()
	{
		do
		{
			Print::Clear();
			Print::PrintColorText("What would you like to do?\n", COLOR_YELLOW);
			Print::PrintColorText("1. Show inventory\n", COLOR_DARK_GREEN);
			Print::PrintColorText("2. Use item\n", COLOR_DARK_GREEN);
			Print::PrintColorText("3. Remove item\n", COLOR_DARK_GREEN);
			Print::PrintColorText("4. Go back\n", COLOR_DARK_GREEN);

			std::string tempSelected = Input::GetInput();
			if (tempSelected == "1")
			{
				Show();
			}
			else if (tempSelected == "2")
			{
				UseItem();
			}
			else if (tempSelected == "3")
			{
				RemoveItem();
			}
			else if (tempSelected == "4")
			{
				return;
			}
			else
			{
				Print::Clear();
				Print::PrintColorText("Wrong input!", COLOR_RED);
				std::cin.get();
			}

		} while (true);
	}

	void Inventory::Show()
	{
		Print::Clear();
		Print::PrintColorText("Your inventory\n", COLOR_YELLOW);

		for (size_t i = 0; i < mypItems.size(); i++)
		{
			Print::PrintColorText(i + ". " + mypItems[i]->GetName() + "\n", COLOR_DARK_GREEN);
		}

		Print::PrintColorText("\nPress ENTER to go back\n", COLOR_YELLOW);
		std::cin.get();

		Print::Clear();
	}

	void Inventory::ShowItemList()
	{
		for (size_t i = 0; i < mypItems.size(); i++)
		{
			Print::PrintColorText((i + 1) + ". " + mypItems[i]->GetName() + "\n", COLOR_DARK_GREEN);
		}
	}

	void Inventory::UseItem()
	{
		do
		{
			Print::Clear();
			Print::PrintColorText("Choose an item\n", COLOR_YELLOW);
			Print::PrintColorText("Select 0 to go back\n\n", COLOR_YELLOW);

			ShowItemList();

			std::string tempSelected = Input::GetInput();
			if (tempSelected == "0")
			{
				return;
			}

			for (size_t i = 0; i < mypItems.size(); i++)
			{
				if (tempSelected == std::to_string(i + 1))
				{
					Print::Clear();
					if (mypItems[i]->Use())
					{
						Print::PrintColorText("You used item " + mypItems[i]->GetName() + "!\n", COLOR_YELLOW);
						if (mypItems[i]->GetIsScroll())
						{
							std::dynamic_pointer_cast<Scroll>(mypItems[i])->SetIsUsed(true);
						}
					}

					auto tempIt = std::find(mypItems.begin(), mypItems.end(), mypItems[i]);
					if (tempIt != mypItems.end())
					{
						if (!mypItems[i]->GetIsScroll())
						{
							mypItems.erase(tempIt);
						}
					}

					Print::PrintColorText("Press ENTER to go back\n", COLOR_YELLOW);
					std::cin.get();
					break;
				}
			}

		} while (true);
	}

	void Inventory::RemoveItem()
	{
		do
		{
			Print::Clear();
			Print::PrintColorText("Choose an item to remove\n", COLOR_YELLOW);
			Print::PrintColorText("Select 0 to go back\n\n", COLOR_YELLOW);

			ShowItemList();

			std::string tempSelection = Input::GetInput();
			if (tempSelection == "0")
			{
				return;
			}

			for (size_t i = 0; i < mypItems.size(); i++)
			{
				if (tempSelection == std::to_string(i + 1))
				{
					Print::Clear();
					Print::PrintColorText("You removed item " + mypItems[i]->GetName() + "!\n", COLOR_YELLOW);
					mypItems.erase(mypItems.begin() + i);
					Print::PrintColorText("Press ENTER to go back", COLOR_YELLOW);
					std::cin.get();
					break;
				}
			}
		} while (true);
	}
}
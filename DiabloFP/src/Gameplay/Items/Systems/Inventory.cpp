#include "pch.h"
#include "Inventory.h"
#include "Gameplay/Items/Scroll.h"
#include "Core/Input/Input.h"

#include "Gameplay/Items/Equipment/Types/Boots.h"
#include "Gameplay/Items/Equipment/Types/Chestplate.h"
#include "Gameplay/Items/Equipment/Types/Helmet.h"
#include "Gameplay/Items/Equipment/Types/Leggings.h"

#include "Gameplay/Items/Equipment/EquipmentFactory.h"

namespace Diablo
{
	Inventory::Inventory()
	{
		myEquipment.push_back(EquipmentFactory::CreateHelmet(3));
		myEquipment[0]->SetEquiped(true);

		myEquipment.push_back(EquipmentFactory::CreateChestplate(3));
		myEquipment[1]->SetEquiped(true);

		myEquipment.push_back(EquipmentFactory::CreateLeggings(3));
		myEquipment[2]->SetEquiped(true);

		myEquipment.push_back(EquipmentFactory::CreateBoots(3));
		myEquipment[3]->SetEquiped(true);
	}

	Inventory::~Inventory()
	{}

	bool Inventory::AddItem(Ref<Item> apItem)
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
			Print::ColorText("What would you like to do?\n", Color::YELLOW);
			Print::ColorText("1. Show inventory\n", Color::DARK_GREEN);
			Print::ColorText("2. Use item\n", Color::DARK_GREEN);
			Print::ColorText("3. Select Equipment\n", Color::DARK_GREEN);
			Print::ColorText("4. Remove item\n", Color::DARK_GREEN);
			Print::ColorText("5. Go back\n", Color::DARK_GREEN);

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
				SelectEquipment();
			}
			else if (tempSelected == "4")
			{
				RemoveItem();
			}
			else if (tempSelected == "5")
			{
				return;
			}
			else
			{
				Print::Clear();
				Print::ColorText("Wrong input!", Color::RED);
				std::cin.get();
			}

		} while (true);
	}

	void Inventory::Show()
	{
		Print::Clear();
		Print::ColorText("Your inventory\n", Color::YELLOW);

		for (size_t i = 0; i < mypItems.size(); i++)
		{
			Print::ColorText(i + ". " + mypItems[i]->GetName() + "\n", Color::DARK_GREEN);
		}

		Print::ColorText("\nPress ENTER to go back\n", Color::YELLOW);
		std::cin.get();

		Print::Clear();
	}

	void Inventory::ShowItemList()
	{
		for (size_t i = 0; i < mypItems.size(); i++)
		{
			Print::ColorText((i + 1) + ". " + mypItems[i]->GetName() + "\n", Color::DARK_GREEN);
		}
	}

	void Inventory::UseItem()
	{
		do
		{
			Print::Clear();
			Print::ColorText("Choose an item\n", Color::YELLOW);
			Print::ColorText("Select 0 to go back\n\n", Color::YELLOW);

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
						Print::ColorText("You used item " + mypItems[i]->GetName() + "!\n", Color::YELLOW);
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

					Print::ColorText("Press ENTER to go back\n", Color::YELLOW);
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
			Print::ColorText("Choose an item to remove\n", Color::YELLOW);
			Print::ColorText("Select 0 to go back\n\n", Color::YELLOW);

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
					Print::ColorText("You removed item " + mypItems[i]->GetName() + "!\n", Color::YELLOW);
					mypItems.erase(mypItems.begin() + i);
					Print::ColorText("Press ENTER to go back", Color::YELLOW);
					std::cin.get();
					break;
				}
			}
		} while (true);
	}

	void Inventory::SelectEquipment()
	{
		Print::Clear();
		uint32_t tempHeight = 20;

		////////Frame////////
		Print::SetPosition(0, 0);
		for (size_t i = 0; i < BUFFER_WIDTH; i++)
		{
			Print::ColorText("-", Color::DARK_GREEN);
		}

		for (size_t i = 1; i < tempHeight + 1; i++)
		{
			Print::SetPosition(0, i);
			Print::ColorText("|", Color::DARK_GREEN);

			Print::SetPosition(BUFFER_WIDTH / 4, i);
			Print::ColorText("|", Color::DARK_GREEN);

			Print::SetPosition((BUFFER_WIDTH / 4) * 3, i);
			Print::ColorText("|", Color::DARK_GREEN);

			Print::SetPosition(BUFFER_WIDTH / 2, i);
			Print::ColorText("|", Color::DARK_GREEN);

			Print::SetPosition(BUFFER_WIDTH - 1, i);
			Print::ColorText("|", Color::DARK_GREEN);
		}

		Print::SetPosition(0, tempHeight);
		for (size_t i = 0; i < BUFFER_WIDTH; i++)
		{
			Print::ColorText("-", Color::DARK_GREEN);
		}
		/////////////////////

		////////Content////////
		int i = 1;
		for (auto& tempE : myEquipment)
		{
			if (Ref<Helmet> tempH = std::dynamic_pointer_cast<Helmet>(std::move(tempE)))
			{
				Print::SetPosition(2, i);
				if (tempH->GetEquiped())
				{
					Print::ColorText(Print::ToString(i) + ". " + tempH->GetName(), Color::PURPLE);
				}
				else 
				{
					Print::ColorText(Print::ToString(i) + ". " + tempH->GetName(), Color::BLUE);
				}
				i++;
			}
		}

		i = 1;
		for (auto& tempE : myEquipment)
		{
			if (Ref<Chestplate> tempC = std::dynamic_pointer_cast<Chestplate>(std::move(tempE)))
			{
				Print::SetPosition((BUFFER_WIDTH / 2) + 2, i);
				if (tempC->GetEquiped())
				{
					Print::ColorText(Print::ToString(i) + ". " + tempC->GetName(), Color::PURPLE);
				}
				else
				{
					Print::ColorText(Print::ToString(i) + ". " + tempC->GetName(), Color::BLUE);
				}
				i++;
			}
		}

		i = 1;
		for (auto& tempE : myEquipment)
		{
			if (Ref<Leggings> tempL = std::dynamic_pointer_cast<Leggings>(std::move(tempE)))
			{
				Print::SetPosition((BUFFER_WIDTH / 4) * 3 + 2, i);
				if (tempL->GetEquiped())
				{
					Print::ColorText(Print::ToString(i) + ". " + tempL->GetName(), Color::PURPLE);
				}
				else
				{
					Print::ColorText(Print::ToString(i) + ". " + tempL->GetName(), Color::BLUE);
				}
				i++;
			}
		}

		i = 1;
		for (auto& tempE : myEquipment)
		{
			if (Ref<Boots> tempB = std::dynamic_pointer_cast<Boots>(std::move(tempE)))
			{
				Print::SetPosition(BUFFER_WIDTH / 4 + 2, i);
				if (tempB->GetEquiped())
				{
					Print::ColorText(Print::ToString(i) + ". " + tempB->GetName(), Color::PURPLE);
				}
				else
				{
					Print::ColorText(Print::ToString(i) + ". " + tempB->GetName(), Color::BLUE);
				}
				i++;
			}
		}
		///////////////////////

		std::cin.get();
	}
}
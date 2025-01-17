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
		myEquipment[0]->Use();

		myEquipment.push_back(EquipmentFactory::CreateChestplate(3));
		myEquipment[1]->Use();

		myEquipment.push_back(EquipmentFactory::CreateLeggings(3));
		myEquipment[2]->Use();

		myEquipment.push_back(EquipmentFactory::CreateBoots(3));
		myEquipment[3]->Use();
		myEquipment.push_back(EquipmentFactory::CreateHelmet(2));
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
		bool tempRunning = true;

		do
		{
			Print::Clear();
			uint32_t tempHeight = 23;

			////////Frame////////
			Print::SetPosition(0, 3);
			for (size_t i = 0; i < BUFFER_WIDTH; i++)
			{
				Print::ColorText("-", Color::DARK_GREEN);
			}

			for (size_t i = 4; i < tempHeight + 1; i++)
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
			int i = 5;
			for (auto& tempE : myEquipment)
			{
				if (Ref<Helmet> tempH = std::dynamic_pointer_cast<Helmet>(tempE))
				{
					Print::SetPosition(2, i);
					if (tempH->GetEquiped())
					{
						Print::ColorText(Print::ToString(i - 4) + ". " + tempH->GetName(), Color::PURPLE);
					}
					else
					{
						Print::ColorText(Print::ToString(i - 4) + ". " + tempH->GetName(), Color::BLUE);
					}
					i++;
				}
			}

			i = 5;
			for (auto& tempE : myEquipment)
			{
				if (Ref<Chestplate> tempC = std::dynamic_pointer_cast<Chestplate>(tempE))
				{
					Print::SetPosition((BUFFER_WIDTH / 2) + 2, i);
					if (tempC->GetEquiped())
					{
						Print::ColorText(Print::ToString(i - 4) + ". " + tempC->GetName(), Color::PURPLE);
					}
					else
					{
						Print::ColorText(Print::ToString(i - 4) + ". " + tempC->GetName(), Color::BLUE);
					}
					i++;
				}
			}

			i = 5;
			for (auto& tempE : myEquipment)
			{
				if (Ref<Leggings> tempL = std::dynamic_pointer_cast<Leggings>(tempE))
				{
					Print::SetPosition((BUFFER_WIDTH / 4) * 3 + 2, i);
					if (tempL->GetEquiped())
					{
						Print::ColorText(Print::ToString(i - 4) + ". " + tempL->GetName(), Color::PURPLE);
					}
					else
					{
						Print::ColorText(Print::ToString(i - 4) + ". " + tempL->GetName(), Color::BLUE);
					}
					i++;
				}
			}

			i = 5;
			for (auto& tempE : myEquipment)
			{
				if (Ref<Boots> tempB = std::dynamic_pointer_cast<Boots>(tempE))
				{
					Print::SetPosition(BUFFER_WIDTH / 4 + 2, i);
					if (tempB->GetEquiped())
					{
						Print::ColorText(Print::ToString(i - 4) + ". " + tempB->GetName(), Color::PURPLE);
					}
					else
					{
						Print::ColorText(Print::ToString(i - 4) + ". " + tempB->GetName(), Color::BLUE);
					}
					i++;
				}
			}
			///////////////////////

			Print::SetPosition(0, 0);
			Print::ColorText("Use 0 to exit\n", Color::GREEN);
			Print::ColorText("Select using format '1,1'(column, row)\n", Color::GREEN);

			std::string tempInput = Input::GetInput();
			if (tempInput == "0")
			{
				tempRunning = false;
			}
			else if (tempInput.size() == 3)
			{
				int tempCol = tempInput[0] - 48;
				int tempRow = tempInput[2] - 48;

				if (tempCol == 1)
				{
					int i = 1;
					for (auto& tempE : myEquipment)
					{
						if (Ref<Helmet> tempH = std::dynamic_pointer_cast<Helmet>(tempE))
						{
							if (tempH->GetEquiped())
							{
								tempH->Unuse();
							}

							if (i == tempRow)
							{
								tempH->Use();
							}
							i++;
						}
					}
					if (tempInput[2] - 48 > i)
					{
						Print::Clear();
						Print::ColorText("Value does not exist!", Color::RED);
						std::cin.get();
					}
				}
				else if (tempCol == 2)
				{
					i = 1;
					for (auto& tempE : myEquipment)
					{
						if (Ref<Chestplate> tempC = std::dynamic_pointer_cast<Chestplate>(tempE))
						{
							if (tempC->GetEquiped())
							{
								tempC->Unuse();
							}

							if (i == tempRow)
							{
								tempC->Use();
							}
							i++;
						}
					}
					if (tempInput[2] - 48 > i)
					{
						Print::Clear();
						Print::ColorText("Value does not exist!", Color::RED);
						std::cin.get();
					}
				}
				else if (tempCol == 3)
				{
					i = 1;
					for (auto& tempE : myEquipment)
					{
						if (Ref<Leggings> tempL = std::dynamic_pointer_cast<Leggings>(tempE))
						{
							if (tempL->GetEquiped())
							{
								tempL->Unuse();
							}
							
							if (i == tempRow)
							{
								tempL->Use();
							}
							i++;
						}
					}
					if (tempInput[2] - 48 > i)
					{
						Print::Clear();
						Print::ColorText("Value does not exist!", Color::RED);
						std::cin.get();
					}
				}
				else if (tempCol == 4)
				{
					i = 1;
					for (auto& tempE : myEquipment)
					{
						if (Ref<Boots> tempB = std::dynamic_pointer_cast<Boots>(tempE))
						{
							if (tempB->GetEquiped())
							{
								tempB->Unuse();
							}

							if (i == tempRow)
							{
								tempB->Use();
							}
							i++;
						}
					}
					if (tempInput[2] - 48 > i)
					{
						Print::Clear();
						Print::ColorText("Value does not exist!", Color::RED);
						std::cin.get();
					}
				}
			}
			else 
			{
				Print::Clear();
				Print::ColorText("Wrong input!", Color::RED);
				std::cin.get();
			}
		} while (tempRunning);
	}
}
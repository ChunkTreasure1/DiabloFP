#pragma once

#include "Item.h"

namespace Diablo
{
	class HealthPotion : public Item
	{
	public:
		HealthPotion(float anAmount);

		virtual bool Use() override;

	private:
		float myHealthAdd;
	};
}
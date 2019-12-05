#pragma once

#include "Item.h"

namespace Diablo
{
	class HealthPotion : public Item
	{
	public:
		HealthPotion();

		inline void SetAddAmount(float anAmount) { myHealthAdd = anAmount; }

		virtual bool Use() override;

	public:
		static Item* CreateMethod() { return new HealthPotion(); }
		static std::string GetFactoryName() { return "HealthPotion"; }

	private:
		float myHealthAdd;

	private:
		static bool myRegistered;
	};
}
#pragma once

#include "Item.h"
#include "Core/Utility/Utility.h"

namespace Diablo
{
	class HealthPotion : public Item
	{
	public:
		HealthPotion();

		inline void SetAddAmount(float anAmount) { myHealthAdd = anAmount; }

		virtual bool Use() override;

	public:
		static Scope<Item> CreateMethod() { return CreateScope<HealthPotion>(); }
		static std::string GetFactoryName() { return "HealthPotion"; }

	private:
		float myHealthAdd;

	private:
		static bool myRegistered;
	};
}
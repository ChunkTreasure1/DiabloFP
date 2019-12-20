#pragma once

#include "Item.h"
#include "Core/Utility/Utility.h"

namespace Diablo
{
	class Tome : public Item
	{
	public:
		Tome();

		virtual bool Use() override;

		std::string GetStat();

	public:
		static Scope<Item> CreateMethod() { return CreateScope<Tome>(); }
		static std::string GetFactoryName() { return "Tome"; }

	private:
		std::string myStat;

	private:
		static bool myRegistered;
	};
}
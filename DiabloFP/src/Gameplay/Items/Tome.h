#pragma once

#include "Item.h"

namespace Diablo
{
	class Tome : public Item
	{
	public:
		Tome();

		virtual bool Use() override;

		std::string GetStat();

	public:
		static Item* CreateMethod() { return new Tome(); }
		static std::string GetFactoryName() { return "Tome"; }

	private:
		std::string myStat;
	};
}
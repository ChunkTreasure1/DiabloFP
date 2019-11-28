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

	private:
		std::string myStat;
	};
}
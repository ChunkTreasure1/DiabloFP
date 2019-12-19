#pragma once

#include "Gameplay/Items/Item.h"

namespace Diablo 
{

	class Equipment : public Item
	{
	public:
		Equipment(const std::string& aName)
			: Item(aName), myIsUsed(false)
		{}

		//Setting
		inline void SetStats(Stats someStats) { myStatIncrease = someStats; }

		virtual void Unuse() {}

	protected:
		Stats myStatIncrease;
		bool myIsUsed;
	};
}
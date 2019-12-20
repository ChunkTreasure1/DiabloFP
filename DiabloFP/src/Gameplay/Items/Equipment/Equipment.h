#pragma once

#include "Gameplay/Items/Item.h"

namespace Diablo 
{

	class Equipment : public Item
	{
	public:
		Equipment(const std::string& aName)
			: Item(aName), myEquiped(false)
		{}

		//Setting
		inline void SetStats(Stats someStats) { myStatIncrease = someStats; }
		inline void SetEquiped(bool someState) { myEquiped = someState; }
		
		//Getting
		inline const bool GetEquiped() { return myEquiped; }

		virtual void Unuse() {}

	protected:
		Stats myStatIncrease;
		bool myEquiped;
	};
}
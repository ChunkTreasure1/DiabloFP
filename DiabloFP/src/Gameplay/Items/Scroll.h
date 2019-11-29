#pragma once

#include "Item.h"
#include <string>

namespace Diablo
{
	class Scroll : public Item
	{
	public:
		Scroll();
		~Scroll() {}

		virtual void Update() override;
		virtual bool Use() override;

		//Getting
		inline void SetIsUsed(bool aValue) { myIsUsed = aValue; }

	public:
		static Item* CreateMethod() { return new Scroll(); }
		static std::string GetFactoryName() { return "Scroll"; }

	private:
		std::string GetStat();
		void Unuse();

	private:
		std::string myStat;
		uint8_t myLifeTime;
		bool myIsUsed = false;
	};
}
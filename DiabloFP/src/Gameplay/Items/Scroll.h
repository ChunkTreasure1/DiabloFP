#pragma once

#include "Item.h"
#include <string>

#include "Core/Utility/Utility.h"

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
		static Scope<Item> CreateMethod() { return CreateScope<Scroll>(); }
		static std::string GetFactoryName() { return "Scroll"; }

	private:
		std::string GetStat();
		void Unuse();

	private:
		std::string myStat;
		uint8_t myLifeTime;
		bool myIsUsed = false;

	private:
		static bool myRegistered;
	};
}
#pragma once

#include <map>
#include <string>

namespace Diablo
{
	class Item
	{
	public:
		virtual bool Use() { return true; }
		virtual void Update() {};

		//Getting
		inline virtual const std::string GetName() const { return myName; }
		inline bool GetIsScroll() const { return myIsScroll; }

	protected:
		Item(const std::string& aName)
			: myName(aName)
		{}

		bool myUsable = true;
		bool myIsScroll = false;
		std::string myName;
	};

}